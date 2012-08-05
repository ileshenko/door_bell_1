/*
 * Simple door bell
 * by Igor Leshenko
 * 
 * main.c
 * ================
 * Entry point
 */

#include  <msp430g2553.h>

#include "songs_lib.h"
#include "player.h"
#include "button.h"

char main_btn;

void main()
{
	WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
	
	DCOCTL = CALDCO_1MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_1MHZ;				//calibrate basic clock
	BCSCTL1 |= DIVA_0;					// ACLK = 1MHz
	BCSCTL2 = DIVS_0;					//set SMClock to 1MHz

	
	player_init();
	button_init();

	for (;;)
	{
		main_btn = 0;
		button_arm_trigger();
		_BIS_SR(LPM0_bits + GIE);
		if (main_btn)
			play_song(BELLS);
//			play_song(HAPPY_NEW_YEAR);
	}	
//	play_song(HAPPY_NEW_YEAR);
//	play_song(BELLS);
}
