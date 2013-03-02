/*
 * player.c
 *
 */

#include  <msp430g2553.h>
#include "player.h"
#include "timer.h"

#define OUTPUT_PORT BIT6

/* frequencies of tones,
 * use tones_t for access according to tone names
 */
static const int tones[] = {
	100, 117, 124,  131,  139,  147,  156,  165,  175,  185,  196,  208,
	220, 233, 247,  262,  277,  294,  311,  330,  349,  370,  391,  415,
	440, 466, 494,  523,  554,  587,  622,  659,  698,  740,  784,  831,
	880, 932, 988, 1046, 1109, 1175, 1244, 1318, 1397, 1480, 1568, 1661,
	0xffff
};

void player_init(void)
{
	P2DIR |= OUTPUT_PORT;

	P2SEL |= OUTPUT_PORT;					//Use as TA0.1
	P2SEL2 &= ~OUTPUT_PORT;
	P2SEL &= ~BIT7;
	P2SEL2 &= ~BIT7;

	TA0CTL = TASSEL_2 + ID_0 + MC_1;		//SMCLK/1 = 1 mHz, upmode
	TA0CCTL1 = OUTMOD_4;					//TOGGLE
	TA0CCR1 = 10;							//Any small enough value for toggling

	TA1CTL = TASSEL_2 + ID_3 + MC_1;		//SMCLK/8 = 125 kHz, up mode
}

void player_set_tempo(int ms)
{
	if (ms)
		P2SEL |= OUTPUT_PORT;					//Use as TA0.1
	else
	{
		P2SEL &= ~OUTPUT_PORT;					//Use as GPIO
		P2OUT &= ~OUTPUT_PORT;					// close output transistor in stand by mode
	}

	timer_unit_set(ms/8);
}

void play(char tone, char length, char stop)
{

	if (tone != PAUSE)
	{
		TA0CCR0 = 500000l/tones[tone];
		TA0R = TA0CCR0-2;
		/* assume that both of MC bits are cleared */
		TA0CTL  |= MC_1; // MC=01 - UP mode
	}
	else
		TA0CTL  &= ~MC_3; // MC=00 - STOP mode

	timer_sleep_for(length*8-stop);

 	if (stop)
 	{
 		TA0CTL &= ~MC_3; // stop playing
 		timer_sleep_for(stop);
 	}
}
