
#include "button.h"
#include  "msp430g2553.h"

#define DOOR_BTN (BIT3)


void button_init(void)
{
	P1OUT |=  DOOR_BTN;
	P1REN |= DOOR_BTN; 							// Poll UP resistor
	P1IES |= DOOR_BTN;                            // Hi/lo edge
}

void button_arm_trigger(void)
{
	P1IFG &= ~DOOR_BTN;                           // IFG cleared
	P1IE |= DOOR_BTN;                             // interrupt enabled
}
//void sm_toggle(void);

int button_status_get(void)
{
	return 0;
}

extern char main_btn;

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1IE &= ~DOOR_BTN;
	main_btn++;
	_BIC_SR_IRQ(LPM0_bits);
	
//	sm_toggle();
//	P1IFG &= ~BTN_TOGGLE;
}
