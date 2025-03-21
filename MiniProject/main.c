#include "hellocfg.h"			//BIOS include file
#include "framework.h"
#include "math.h"
#include "Data.h"

#define N 10  // Number of feedback coefficients
#define M 10 // Number of feedforward coefficients
#define BUFFER_SIZE (M + 1)  // Minimum size required for circular buffer

//int16_t volatile sw1 = 0xffff;
//int16_t volatile sw2 = 0xffff;
//int16_t volatile sw6 = 0xffff;
//int16_t volatile sw7 = 0xffff;
//int16_t volatile sw8 = 0xffff;

int16_t volatile sw1 = 0x0000;
int16_t volatile sw2 = 0x0000;
int16_t volatile sw6 = 0x0000;
int16_t volatile sw7 = 0x0000;
int16_t volatile sw8 = 0x0000;

// Circular buffers for past samples
double x[BUFFER_SIZE] = {0}; // Input samples
double y[BUFFER_SIZE] = {0}; // Output samples
int index = 0; // Circular buffer index


uint16_t fs = 8000;
float buffer[32000];
uint16_t buffer_len = 8000*4;
float temp_lp[11];
uint16_t n = 0;
uint16_t m = 0;
uint16_t i = 0;
uint16_t n_temp = 0;
float y_lp = 0.0; //, ybp = 0, yhp = 0, den_lp = 0, den_bp = 0, den_hp = 0;
uint16_t j,k;


//---------------------------------------------------------
//---------------------------------------------------------
void main(void)
{
    for(j = 0; j<buffer_len; j++)
    {
        buffer[j] = 0;
    }
	initAll();
	return;  		// return to BIOS scheduler
}


//---------------------------------------------------------
//---------------------------------------------------------

void check_led(){

    if(sw1){
    // THIS IS THE LEFT CHANNEL!!!

   // LED_turnOn(LED_1);
    //LED_turnOff(LED_2);
    if(sw2)
    {
       // LED_turnOn(LED_2);

    }
    else
    {
       // LED_turnOff(LED_2);
    }
    }
    else
    {
   //     LED_turnOff(LED_2);
    //    LED_turnOff(LED_1);        //turn everything off
    }

}

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
//    else if(sw1&&!sw2&&(sw6||sw7||sw8))
//    {
//      LED_turnOff(LED_2);
//    }


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
//		LED_turnOn(LED_2);
	}
	else
	{
		sw1 = 0x0000;
//		LED_turnOff(LED_2);
	}

	if(dip_status2)
    {
        sw2 = 0xffff;
//      LED_turnOn(LED_2);
    }
    else
    {
        sw2 = 0x0000;
//      LED_turnOff(LED_2);
    }
	if(dip_status6)
    {
        sw6 = 0xffff;
//      LED_turnOn(LED_2);
    }
    else
    {
        sw6 = 0x0000;
//      LED_turnOff(LED_2);
    }

    if(dip_status7)
    {
        sw7 = 0xffff;
//      LED_turnOn(LED_2);
    }
    else
    {
        sw7 = 0x0000;
//      LED_turnOff(LED_2);
    }
    if(dip_status8)
        {
        sw8 = 0xffff;
//      LED_turnOn(LED_2);
    }
    else
    {
        sw8 = 0x0000;
//      LED_turnOff(LED_2);
    }

   // check_led();

}

void add_to_buffer(int16_t s16)
{


    i = i % buffer_len; // next buffer element
    buffer[i] = s16;
    i++;
   // LED_turnOn(LED_1);

}


double iir_filter(double input) {
    // Update circular buffer index
    index = (index + 1) % BUFFER_SIZE;

    // Store new input
    x[index] = input;

    // Compute output using circular buffer
    y[index] = 0;
    for (i = 0; i <= M; i++) {
        int xi = (index - i + BUFFER_SIZE) % BUFFER_SIZE;
        y[index] += LP_B[i] * x[xi];
    }
    for (j = 1; j <= N; j++) {
        int yj = (index - j + BUFFER_SIZE) % BUFFER_SIZE;
        y[index] -= LP_A[j] * y[yj];
    }

    return y[index]; // Return current filtered output
}




int16_t get_buffer()
{

    n = n % buffer_len; // next buffer element
    n_temp = n;
//
//
//    temp_lp[0] = 0;
//
//    // When next audio sample is to be filtered
//    temp_lp[n] = buffer[n];
//    for (k = 1; k<N_LP_A; k++){
//        temp[n] -= LP_A[k]*temp[n-k];
//    }
//    for (k = 0; k<N_LP_B; k++){
//        y_lp += LP_B[k]*temp[n-k];
//    }

    n++;

    y_lp = iir_filter(buffer[n_temp]);
    y_lp = iir_filter(buffer[n_temp]);
    y_lp = iir_filter(buffer[n_temp]);

    return buffer[n_temp];



    //* !(sw6||sw7||sw8) + y_lp * sw6;



    // Processing

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
              //add_to_buffer(s16); // store sample in buffer
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

//void audioHWI(void)
//{
//	int16_t s16;
//
//	s16 = read_audio_sample();
//	if (MCASP->RSLOT)
//	{
//		// THIS IS THE LEFT CHANNEL!!!
//	    i =  n%buff;
//		s16 = process(s16, i);
//		s16 &= mask;
//		n++;
//	}
//	else {
////		 THIS IS THE RIGHT CHANNEL!!!
//		s16 = process(s16);
//		s16 &= mask;
//
//	}
//	write_audio_sample(s16);
//}



