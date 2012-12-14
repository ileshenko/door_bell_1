/*
 * button.c
 * Process button pressing and state machine for song selection.
 */
#include  "msp430g2553.h"
#include "button.h"
#include "timer.h"

#define DOOR_BTN (BIT3)
typedef struct {
	song_t song;
	char dot;
	char dash;
} song_select_t;

#define DFL BELLS

static song_select_t map[] = {
		[0] = {DFL, 1, 2},
		[1] = {HAPPY_NEW_YEAR, 3, 8}, // .
		[2] = {GAMMA, 0, 6}, // -
		[3] = {WALSE,4,7}, // . .
		[4] = {DFL,0,5}, // . . .
		[5] = {LADA,0,0}, // . . . -
		[6] = {PUST_VSEGDA, 0, 0}, // - -
		[7] = {JINGLE_BELLS, 0, 0}, // . . -
		[8] = {SUROK, 0, 0} // . -
};

typedef enum {
	BTN_DOT,
	BTN_DASH,
	BTN_TIMEOUT,
} btn_sm_event_t;

void button_init(void)
{
	P1OUT |= DOOR_BTN;
	P1REN |= DOOR_BTN; 							// Poll UP resistor
}

static void button_arm_trigger(void)
{
	P1IFG &= ~DOOR_BTN;                         // IFG cleared
	P1IE |= DOOR_BTN;                           // interrupt enabled
	P1IES |= DOOR_BTN;							// Hi/lo edge
}

static inline int button_status_get(void)
{
	return P1IN & DOOR_BTN;
}

/* Song select state machine */
static char map_idx;

static inline void btn_sm_reset(void)
{
	map_idx = 0;
}

/* process event from button. Returns nonzero if end state is reached */
static int btn_sm_step(btn_sm_event_t event)
{
	if (event == BTN_TIMEOUT)
		return 1;

	map_idx = event == BTN_DOT ? map[map_idx].dot : map[map_idx].dash;
	return !map_idx;
}

static inline song_t btn_sm_song_get(void)
{
	return map[map_idx].song;
}

static void wait_for_btn_press(void)
{
	button_arm_trigger();
 	_BIS_SR(LPM0_bits + GIE);
}

/* If after 10 ms the signal is changed - this was noise */
static int is_btn_noise(void)
{
	timer_unit_set(10);
	timer_sleep_for(1);
	timer_unit_set(0);

	return button_status_get();
}

/* Recognizes dot, dash or timeout (sleep on button) */
static btn_sm_event_t btn_event(void)
{
	int ticks, released;

	ticks = 0;
	timer_unit_set(1);
	while (ticks++ < 1600)
	{
		timer_sleep_for(1);
		if (button_status_get())
		{
			if (++released > 10)
				break;
		}
		else
			released = 0;
	}
	timer_unit_set(0);

	if (!released)
		return BTN_TIMEOUT;

	return ticks < 500 ? BTN_DOT : BTN_DASH;
}

/* returns true if the button is pressed */
static int btn_next(void)
{
	int ticks, pressed;

	ticks = pressed = 0;
	timer_unit_set(1);
	while (ticks ++ < 500 || pressed)
	{
		timer_sleep_for(1);
		if (!button_status_get())
		{
			if (++pressed > 10)
				break;
		}
		else
			pressed = 0;
	}
	timer_unit_set(0);
	return pressed;
}

song_t button_wait_for(void)
{
	btn_sm_event_t press_event;
	/* Initial state - button released */
	while (!button_status_get());

	btn_sm_reset();
	do {
		wait_for_btn_press();
	} while (is_btn_noise());

	/* Yes, it is really pressed */
	for (;;)
	{
		press_event = btn_event();
		if (btn_sm_step(press_event))
			return btn_sm_song_get();


		if (!btn_next())
			return btn_sm_song_get();
	}
//	return DFL;
}

//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1IE &= ~DOOR_BTN;
	_BIC_SR_IRQ(LPM0_bits);
}
