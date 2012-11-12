/*
 * Door Bell project
 * timer.c
 */

#include  <msp430g2553.h>
#include "timer.h"

void timer_init(void)
{
	/* Set DCO to 1 MHz */
	DCOCTL = CALDCO_1MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_1MHZ;				//calibrate basic clock

	/* Set ACLK to 1MHz */
////	BCSCTL1 |= DIVA_0;					// ACLK = 1MHz ??? WHERE is the INPUT???

	/* Set SMCLK and MCLK to 1MHz */
	BCSCTL2 = SELM_0 | DIVM_0 | /*SELS |*/ DIVS_0; // MCLK = DCO/1. SMCLK = DCO/1

//DEBUG
	P1DIR |= BIT0;
}

void timer_unit_set(int ms)
{
	if (ms)
	{
		TA1CCR0 = ms*125l;
		TA1CCTL0 |= CCIE;
	}
	else
		TA1CCTL0 &= ~CCIE;
}

static char delay_length;

void timer_sleep_for(char units)
{
	delay_length = units;
 	_BIS_SR(LPM0_bits + GIE);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer1_isr(void)
{
//DEBUG
	P1OUT ^= BIT0;
	if (!(--delay_length))
	{
//		TA1CCTL0 &= ~CCIE;
		_BIC_SR_IRQ(LPM0_bits);
	}
}
