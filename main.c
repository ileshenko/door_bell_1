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


void main()
{
	WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
	
	timer_init();
	player_init();
	button_init();

	for (;;)
		play_song(button_wait_for());
}
