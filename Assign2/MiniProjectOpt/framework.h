//-----------------------------------------------------------------------------
// \file   framework.h
// \brief   common functions and definitions
//
//-----------------------------------------------------------------------------

#ifndef MAIN_H_
#define MAIN_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <std.h>
#include "types.h"
#include "stdio.h"
#include "evmc6748.h"
//#include "evmc6748_timer.h"
#include "evmc6748_gpio.h"
#include "evmc6748_i2c.h"
#include "evmc6748_mcasp.h"
#include "evmc6748_aic3106.h"
#include "evmc6748_led.h"
#include "evmc6748_dip.h"

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define PINMUX_MCASP_REG_17   17
#define PINMUX_MCASP_MASK_17  0x0000ff00
#define PINMUX_MCASP_VAL_17   0x00000800

//#define FS_48KHZ
#define FS_8KHZ
//#define FS_10KHZ
//#define FS_24KHZ
//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
void initAll(void);
void isrAudio(void);
void McASP_Init();
void AIC3106_Init();
void McASP_Start();
void USTIMER_delay(uint32_t time);
void SetGpio();
int16_t read_audio_sample();
void write_audio_sample(int16_t);
extern LgUns CLK_gethtime(void);

//-----------------------------------------------------------------------------
// Externs
//-----------------------------------------------------------------------------
extern	cregister volatile unsigned int	CSR;	// control status register
extern	cregister volatile unsigned int	ICR;	// interrupt clear register
extern	cregister volatile unsigned int	IER;	// interrupt enable reg.
extern	cregister volatile unsigned int	AMR;	// Addressing Mode reg

#endif

