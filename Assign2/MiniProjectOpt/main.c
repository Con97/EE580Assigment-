#include "hellocfg.h"			//BIOS include file
#include "framework.h"
#include "Data.h"
#include <log.h> // Library for priniting to log
#include <clk.h> // CLK module - for time - using BIOS
#include <std.h>
 float this;
#undef TICKS_PER_SEC
#define TICKS_PER_SEC (300000000)

int16_t volatile sw1 = 0x0000;
int16_t volatile sw2 = 0x0000;
int16_t volatile sw6 = 0x0000;
int16_t volatile sw7 = 0x0000;
int16_t volatile sw8 = 0x0000;

// Circular buffers for past samples
float x_lp[N_LP_B] = {0}; // Input samples
float y_lp[N_LP_B] = {0}; // Output samples
float x_bp[N_BP_B] = {0}; // Input samples
float y_bp[N_BP_B] = {0}; // Output samples
float x_hp[N_BP_B] = {0}; // Input samples
float y_hp[N_BP_B] = {0}; // Output samples
uint16_t index_lp = 0; // Circular buffer index
uint16_t index_bp = 0; // Circular buffer index
uint16_t index_hp = 0; // Circular buffer index
uint16_t past_idx = 0;


float buffer[32000];
uint16_t buffer_len = 8000*4;
uint16_t n = 0;
uint16_t m = 0;
uint16_t i = 0;
uint16_t n_temp = 0;
float out_lp = 0.0f, out_bp = 0.0f, out_hp = 0.0f;
uint16_t j,k;
float B = 1.0f;  // Initial value
float sample_temp = 1.0f;


int index_lp_T = 0;
//---------------------------------------------------------
//---------------------------------------------------------

LgUns start_t, end_t, duration; // Define time metrics
uint16_t dur;

//extern FAR LOG_Obj trace;

void main(void)
{
    for(j = 0; j<buffer_len; j++)
    {
        buffer[j] = 0.0f;
    }
    for(j = 0; j<N_LP_A; j++)
        {
            x_lp[j] = 0.0f;
            y_lp[j] = 0.0f;
            x_hp[j] = 0.0f;
            y_hp[j] = 0.0f;
        }
    for(j = 0; j<N_BP_A; j++)
        {
            x_bp[j] = 0.0f;
            y_bp[j] = 0.0f;
        }
	initAll();
	return;  		// return to BIOS scheduler
}


//---------------------------------------------------------
//---------------------------------------------------------


void flash_LED_rec(void)
{

    if(sw1&&!sw2)
    {
      LED_toggle(LED_1);
      LED_toggle(LED_2);
    }
    else if(!sw1)
    {
      LED_turnOff(LED_1);
      LED_turnOff(LED_2);
    }

}

void flash_LED_playback(void)
{

    if(sw1&&sw2)
    {
      LED_toggle(LED_1);
      LED_turnOff(LED_2);
    }

}

void flash_LED_filtering(void)
{

    if(sw1&&sw2&&(sw6||sw7||sw8))
    {
      LED_toggle(LED_2);
    }

}


void dipPRD(void)
{
	uint8_t dip_status1;
    uint8_t dip_status2;
    uint8_t dip_status6;
    uint8_t dip_status7;
    uint8_t dip_status8;

	DIP_get(DIP_1, &dip_status1);
    DIP_get(DIP_2, &dip_status2);
    DIP_get(DIP_6, &dip_status6);
    DIP_get(DIP_7, &dip_status7);
    DIP_get(DIP_8, &dip_status8);

	if(dip_status1)
	{
		sw1 = 0xffff;
	}
	else
	{
		sw1 = 0x0000;
	}

	if(dip_status2)
    {
        sw2 = 0xffff;
    }
    else
    {
        sw2 = 0x0000;
    }
	if(dip_status6)
    {
        sw6 = 0xffff;
    }
    else
    {
        sw6 = 0x0000;
    }

    if(dip_status7)
    {
        sw7 = 0xffff;
    }
    else
    {
        sw7 = 0x0000;
    }
    if(dip_status8)
        {
        sw8 = 0xffff;
    }
    else
    {
        sw8 = 0x0000;
    }

}

void add_to_buffer(int16_t s16)
{


    i = i % buffer_len; // next buffer element
    buffer[i] = s16;
    i++;

}

float iir_filter_lp(float input) {

    // Update index_lp with faster wrap
    index_lp_T = (index_lp + 1) % N_LP_A;
//    index_lp = (index_lp + 1) & (N_LP_A - 1);
//    index = (index + 1) & (size - 1);

    // Store new input
    x_lp[index_lp] = input;

    // Initialize output with b[0]*x_lp[n] term (current input)
    float output = LP_B[0] * input;

    // Single loop for both feedforward and feedback
    #pragma UNROLL(N_LP_A-1);
    for (i = 1; i <= N_LP_A-1; i++) {
//        past_idx = (index_lp - i + N_LP_A) & (N_LP_A - 1);
        past_idx = (index_lp - i + N_LP_A) % N_LP_A;
        output += LP_B[i] * x_lp[past_idx];    // Feedforward term
        output -= LP_A[i] * y_lp[past_idx];    // Feedback term
    }


    // Store result
    y_lp[index_lp] = output;
    return output;
}

float iir_filter_bp(float input) {

    // Update index_bp with faster wrap
//    index_bp = (index_bp + 1) & (N_BP_A - 1);
      index_bp = (index_bp + 1) % N_BP_A;


    // Store new input
    x_bp[index_bp] = input;

    // Initialize output with b[0]*x_bp[n] term (current input)
    float output = BP_B[0] * input;

    // Single loop for both feedforward and feedback
    #pragma UNROLL(N_BP_A-1);
    for (i = 1; i <= N_BP_A-1; i++) {
//        past_idx = (index_bp - i + N_BP_A) & (N_BP_A - 1);
        past_idx = (index_bp - i + N_BP_A) % N_BP_A;
        output += BP_B[i] * x_bp[past_idx];    // Feedforward term
        output -= BP_A[i] * y_bp[past_idx];    // Feedback term
    }

    // Store result
    y_bp[index_bp] = output;
    return output;
}

float iir_filter_hp(float input) {

    // Update index_hp with faster wrap
//    index_hp = (index_hp + 1) & (N_HP_A - 1);
    index_hp = (index_hp + 1) % N_HP_A;


    // Store new input
    x_hp[index_hp] = input;

    // Initialize output with b[0]*x_hp[n] term (current input)
    float output = HP_B[0] * input;

    // Single loop for both feedforward and feedback
    #pragma UNROLL(N_HP_A-1);
    for (i = 1; i <= N_HP_A-1; i++) {
//        past_idx = (index_hp - i + N_HP_A) & (N_HP_A - 1);
        past_idx = (index_hp - i + N_HP_A) % N_HP_A;
        output += HP_B[i] * x_hp[past_idx];    // Feedforward term
        output -= HP_A[i] * y_hp[past_idx];    // Feedback term
    }

    // Store result
    y_hp[index_hp] = output;
    return output;
}
int16_t get_buffer()
{


    start_t = CLK_gethtime(); // Get current time


    n = n % buffer_len; // next buffer element
    n_temp = n;
    n++;

    sample_temp = buffer[n_temp];

    B = 1.0f;

//    out_lp = iir_filter_lp_single_loop(sample_temp);
    out_lp = iir_filter_lp(sample_temp);
    out_bp = iir_filter_bp(sample_temp);
    out_hp = iir_filter_hp(sample_temp);

    out_lp *= (sw6 != 0x00000);
    out_bp *= (sw7 != 0x00000);
    out_hp *= (sw8 != 0x00000);

    // Multiply by a condition that evaluates to 0 if any switch is off, otherwise 1
    sample_temp *= (sw6 == 0x00000) * (sw7 == 0x00000) * (sw8 == 0x00000);

    end_t = CLK_gethtime(); // Get current time

    // Calculate difference
    if(start_t>end_t) duration = start_t - end_t;
    else duration = end_t - start_t;

     LOG_printf(&trace,"ms: %d --- Ticks: %d", duration/CLK_countspms(), duration);

    return  sample_temp + out_bp + out_lp  + out_hp;

}



//---------------------------------------------------------
//---------------------------------------------------------

void audioHWI(void)
{
    int16_t s16;

    s16 = read_audio_sample();
   if (MCASP->RSLOT)
    {
        if(sw1){
            // THIS IS THE LEFT CHANNEL!!!

            if(sw2)
            {
                s16 = get_buffer(); // get sample from buffer for processing
            }
            else
            {
                add_to_buffer(s16); // store sample in buffer
               // s16 = 0;    // zero sample so no audio out
            }
       }
       else
       {
              s16 = 0; //sw1;    // zero sample so no audio out
//            //turn everything off
        }

    }
    else {
      // THIS IS THE RIGHT CHANNEL!!!

        s16 = 0;
//
//       //turn everything off
               }


    write_audio_sample(s16);
}
