/* 
 * player.h
 * play tone 
 * 
 * 
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef enum {
	A2, AB2, B2, C3, CD3, D3, DE3, E3, F3, FG3, G3, GA3,
	A3, AB3, B3, C4, CD4, D4, DE4, E4, F4, FG4, G4, GA4,
	A4, AB4, B4, C5, CD5, D5, DE5, E5, F5, FG5, G5, GA5,
	A5, AB5, B5, C6, CD6, D6, DE6, E6, F6, FG6, G6, GA6,
	PAUSE
} tones_t;

void player_init(void);
void player_set_tempo(int ms);
void play(char tone, char length, char stop);

#endif /*_PLAYER_H_*/
