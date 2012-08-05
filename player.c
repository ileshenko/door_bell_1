
#include  <msp430g2553.h>
#include "player.h"

#define OUTPUT_PORT BIT6

static const int tones[] = {
	220, 233, 247,  262,  277,  294,  311,  330,  349,  370,  391,  415,
	440, 466, 494,  523,  554,  587,  622,  659,  698,  740,  784,  831,
	880, 932, 988, 1046, 1109, 1175, 1244, 1318, 1397, 1480, 1568, 1661,
	0xffff
};


void player_init()
{
	P1DIR |= OUTPUT_PORT;
	P1SEL |= OUTPUT_PORT;					//Use as TA0.1	
	
	TA0CTL = TASSEL_2 + ID_0 + MC_1;		//SMClock, full speed, upmode
	TA0CCTL1 = OUTMOD_4;					//TOGGLE
	TA0CCR1 = 10;							//Any small enough value for toggling
	
	
	TA1CTL = TASSEL_2 + ID_3 + MC_1;		//SMClock, 250kHz, up mode
}

static unsigned int tempo1;
static unsigned int tempo2;
static unsigned int tempo3;

void player_set_tempo(int ms)
{
	tempo1 = 125u*ms;
	tempo2 = 120u*ms;
	tempo3 = 5u*ms;
//	TA1CCR0 = 125u*ms;	
}

static char tone_length;

void play(char tone, char length, char stop)
{
	tone_length = length;

	if (stop)
		TA1CCR0 = tempo2;
	else	
		TA1CCR0 = tempo1;
	
	if (tone != PAUSE)
	{
		TA0CCR0 = 500000l/tones[tone];
		TA1CCTL0 = CCIE;
//		TA0CTL  &= ~MC_3;	// MC=00 - STOP mode 
		TA0CTL  |= MC_1;  // MC=01 - UP mode
	}
	else
		TA0CTL  &= ~MC_3;	// MC=00 - STOP mode 
	
    
 	_BIS_SR(LPM0_bits + GIE);
 	if (stop)
 	{
 		TA0CTL  &= ~MC_3; // stop playing
 		
 		tone_length = 1;
 		TA1CCTL0 = CCIE;
 		TA1CCR0 = tempo3;
		_BIS_SR(LPM0_bits + GIE);
 	}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void broadcast_signal_complete(void)
{
//	TA0CCR0--;
//	P1OUT ^= BIT0;
//	TA1CCTL0 &= ~CCIE;
	if (!(--tone_length))
		_BIC_SR_IRQ(LPM0_bits);
}
