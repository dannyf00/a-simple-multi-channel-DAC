#ifndef _SDDAC_H
#define _SDDAC_H

#include "gpio.h"                           //we use gpio functions

//sigma-delta DAC implementation - demonstration for 2-channel implementation

//hardware configuration
#define SDDAC_PORT		GPIO
#define SDDAC_DDR		TRISIO
#define SDDAC_OUT0		(1<<0)				//1-bit output of the SD DAC ch1
#define SDDAC_OUT1		(1<<2)				//1-bit output of the sd dac ch2
#define SDDAC_OUT2		(1<<5)				//1-bit output of the sd dac ch3
#define SDDAC_N			3					//number of SDDAC channels, 1..256
//end hardware configuration

//global defines

//global variables
//to allow duty cycles to be set directly in user code space
extern volatile char sddac_add[SDDAC_N];					//sddac adder. 7-bit resolution, MSB as output
extern volatile char sddac_dc[SDDAC_N];					//duty cycle. 7-bit max

//initialize
void sddac_init(void);

//increment sddac adders
void sddac_run(void);

#endif
