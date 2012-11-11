#ifndef _TIMER_H_
#define _TIMER_H_

void timer_init(void);
void timer_unit_set(int ms);

void timer_sleep_for(char units);

#endif /*_TIMER_H_*/
