#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "sddac.h"

//hardware configuration
//end hardware configuration

//global defines
#define PR_COUNT	100
#define WAVE0_STEP	3
#define WAVE1_STEP	10

//global variables
char wave0_index=0, wave1_index = 0;
//256point, 7-bit sin table
const char wave_sin[] = {
	64,66,67,69,70,72,73,75,
	76,78,80,81,83,84,86,87,
	88,90,91,93,94,96,97,98,
	100,101,102,103,105,106,107,108,
	109,110,111,112,113,114,115,116,
	117,118,119,120,120,121,122,123,
	123,124,124,125,125,126,126,126,
	127,127,127,128,128,128,128,128,
	128,128,128,128,128,128,127,127,
	127,126,126,126,125,125,124,124,
	123,123,122,121,120,120,119,118,
	117,116,115,114,113,112,111,110,
	109,108,107,106,105,103,102,101,
	100,98,97,96,94,93,91,90,
	88,87,86,84,83,81,80,78,
	76,75,73,72,70,69,67,66,
	64,62,61,59,58,56,55,53,
	52,50,48,47,45,44,42,41,
	40,38,37,35,34,32,31,30,
	28,27,26,25,23,22,21,20,
	19,18,17,16,15,14,13,12,
	11,10,9,8,8,7,6,5,
	5,4,4,3,3,2,2,2,
	1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,1,1,
	1,2,2,2,3,3,4,4,
	5,5,6,7,8,8,9,10,
	11,12,13,14,15,16,17,18,
	19,20,21,22,23,25,26,27,
	28,30,31,32,34,35,37,38,
	40,41,42,44,45,47,48,50,
	52,53,55,56,58,59,61,62,
};

int main(void) {
	uint16_t tmp=PR_COUNT;
	
	mcu_init();							    //initialize the mcu
	sddac_init();							//reset the dac
	//sddac_dc[0] = 10;						//reset the duty cycle
	//sddac_dc[1] = 100;
	while (1) {
		//generate two independent waveforms
		if (tmp-- == 0) {					//time is up
			tmp = PR_COUNT;					//reset tmp
			wave0_index += WAVE0_STEP;		//increment wave0 index
			//wave1_index += WAVE1_STEP;		//increment wave1 index
			sddac_dc[0] = wave_sin[wave0_index];
			sddac_dc[1] = wave_sin[(char) (wave0_index + 256 * 1 / 3)];
			sddac_dc[2] = wave_sin[(char) (wave0_index + 256 * 2 / 3)];
		}	

		sddac_run();						//run the sddac - can be called from a timer ISR
	}
}

