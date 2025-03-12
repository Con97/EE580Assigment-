#include "hellocfg.h"			//BIOS include file
#include "framework.h"
#include "math.h"


int16_t volatile sw1 = 0xffff;
int16_t volatile sw2 = 0xffff;
int16_t volatile sw6 = 0xffff;
int16_t volatile sw7 = 0xffff;
int16_t volatile sw8 = 0xffff;

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

	initAll();
	return;  		// return to BIOS scheduler
}


//---------------------------------------------------------
//---------------------------------------------------------

void check_led(){
    int16_t s16 = 1;

    if(sw1){
    // THIS IS THE LEFT CHANNEL!!!

    LED_turnOn(LED_1);
    LED_turnOff(LED_2);
    if(sw2)
    {
        LED_turnOn(LED_2);

//              s16 = get_buffer(); // get sample from buffer for processing

    }
    else
    {
        LED_turnOff(LED_2);

//              add_to_buffer(s16); // store sample in buffer
//              s16 &= sw2;    // zero sample so no audio out

    }
    }
    else
    {
        LED_turnOff(LED_2);
        LED_turnOff(LED_1);
        s16 &= sw1;    // zero sample so no audio out
        //turn everything off
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

    check_led();

}

void add_to_buffer(int16_t s16)
{


    i = i % buffer_len; // next buffer element
    buffer[i] = s16;
    i++;

}

int16_t get_buffer()
{

    n = n % buffer_len; // next buffer element
    n_temp = n;
    n++;
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

//            LED_turnOn(LED_1);
//            LED_turnOff(LED_2);
            if(sw2)
            {
//                LED_turnOn(LED_2);

                s16 = get_buffer(); // get sample from buffer for processing

            }
            else
            {
//                LED_turnOff(LED_2);

                add_to_buffer(s16); // store sample in buffer
                s16 &= sw2;    // zero sample so no audio out

            }
        }
        else
        {
//            LED_turnOff(LED_2);
//            LED_turnOff(LED_1);
            s16 &= sw1;    // zero sample so no audio out
            //turn everything off
        }

    }
//    else {
////       THIS IS THE RIGHT CHANNEL!!!
//        s16 = process(s16);
//        s16 &= sw1;
//    }
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



