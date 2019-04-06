#include "sddac.h"							//sigma-delta DAC, software implementation


//sigma-delta DAC implementation - demonstration for 2-channel implementation

//hardware configuration
//#define SDDAC_PORT		GPIO
//#define SDDAC_DDR		TRISIO
//#define SDDAC_OUT0		(1<<0)				//1-bit output of the SD DAC ch1
//#define SDDAC_OUT1		(1<<2)				//1-bit output of the sd dac ch2
//#define SDDAC_N			2					//number of SDDAC channels. 1..256
//end hardware configuration

//global defines

//global variables
volatile char sddac_add[SDDAC_N]=0;					//sddac adder. 7-bit resolution, MSB as output
volatile char sddac_dc[SDDAC_N]=0;					//duty cycle. 7-bit max

//initialize
void sddac_init(void) {
	//reset the variables
#if defined(SDDAC_OUT0)
	sddac_add[0]=sddac_dc[0]=0; IO_CLR(SDDAC_PORT, SDDAC_OUT0); IO_OUT(SDDAC_DDR, SDDAC_OUT0);
#endif
#if defined(SDDAC_OUT1)
	sddac_add[1]=sddac_dc[1]=0; IO_CLR(SDDAC_PORT, SDDAC_OUT1); IO_OUT(SDDAC_DDR, SDDAC_OUT1);
#endif
#if defined(SDDAC_OUT2)
	sddac_add[2]=sddac_dc[2]=0; IO_CLR(SDDAC_PORT, SDDAC_OUT2); IO_OUT(SDDAC_DDR, SDDAC_OUT2);
#endif
}

//increment sddac adders
void sddac_run(void) {
	//increment sddac channels - loops unrolled
#if defined(SDDAC_OUT0)
	sddac_add[0] += sddac_dc[0]; if (sddac_add[0] & 0x80) {IO_SET(SDDAC_PORT, SDDAC_OUT0); sddac_add[0] &=~0x80;} else IO_CLR(SDDAC_PORT, SDDAC_OUT0);	//process ch1
#endif
#if defined(SDDAC_OUT1)
	sddac_add[1] += sddac_dc[1]; if (sddac_add[1] & 0x80) {IO_SET(SDDAC_PORT, SDDAC_OUT1); sddac_add[1] &=~0x80;} else IO_CLR(SDDAC_PORT, SDDAC_OUT1);	//process ch2
#endif
#if defined(SDDAC_OUT2)
	sddac_add[2] += sddac_dc[2]; if (sddac_add[2] & 0x80) {IO_SET(SDDAC_PORT, SDDAC_OUT2); sddac_add[2] &=~0x80;} else IO_CLR(SDDAC_PORT, SDDAC_OUT2);	//process ch3
#endif
	return;
}		
