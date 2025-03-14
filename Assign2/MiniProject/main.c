#include "hellocfg.h"			//BIOS include file
#include "framework.h"
#include "math.h"


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

uint16_t fs = 8000;
int16_t buffer[32000];
uint16_t buffer_len = 8000*4;
uint16_t n = 0;
uint16_t i = 0;
uint16_t n_temp = 0;


//---------------------------------------------------------
//---------------------------------------------------------
void main(void)
{
    for(int j =0; j<buffer_len: j++)
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

int16_t get_buffer()
{

    n = n % buffer_len; // next buffer element
    n_temp = n;
    n++;

    for(m = 0; (n<=m)&&(m<9); m++){
               ylp[n] += (blp[n-m] * x[m]);
               ybp[n] += (bbp[n-m] * x[m]);
               yhp[n] += (bhp[n-m] * x[m]);

               wlp[n] += (alp[m-m]*ylp[m]);
               wbp[n] += (abp[m-m]*ybp[m]);
               whp[n] += (ahp[m-m]*yhp[m]);
           }
    int output = ((xlp-ylp)*sw6+(xbp-ybp)sw7+(xhp-yhp)sw8)/a0
      return output

//
//      for(v = 0; (v<=n)&&(v<28); v++){
//          filtered_FC[n] += FC_sig_mu[n-v] * filter_b[v];
//          filtered_AL[n] += AL_sig_mu[n-v] * filter_a[v];
//      }


    // Processing
    return buffer[n_temp];

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



