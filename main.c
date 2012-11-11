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
#include "timer.h"

char main_btn;

void main()
{
	WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
	
	timer_init();
	player_init();
	button_init();

	for (;;)
	{
		main_btn = 0;
		button_arm_trigger();
		_BIS_SR(LPM0_bits + GIE);
		if (main_btn)
//			play_song(BELLS);
//			play_song(HAPPY_NEW_YEAR);
			play_song(GAMMA);
	}	
}
