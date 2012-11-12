/*
 * button.h
 * processes button and returns selected song
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "songs_lib.h"

void button_init(void);
song_t button_wait_for(void);

#endif /*_BUTTON_H_*/
