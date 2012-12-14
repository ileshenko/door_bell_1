/*
 * songs_lib.h
 * plays known songs
 */
#ifndef _SONGS_LIB_H_
#define _SONGS_LIB_H_

typedef enum {
	BELLS,
	HAPPY_NEW_YEAR,
	GAMMA,
	LADA,
	WALSE,
	PUST_VSEGDA,
	JINGLE_BELLS,
	SUROK,
} song_t;

void play_song(song_t song);

#endif /*_SONGS_LIB_H_*/
