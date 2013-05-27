/*
 * songs_lib.h
 * plays known songs
 */
#ifndef _SONGS_LIB_H_
#define _SONGS_LIB_H_

typedef enum {
	TUMBALALAYKA,
	YONATAN,
	PETER_N_WOLF,
	KALINKA,
	WALSE,
	PUST_VSEGDA,
	JINGLE_BELLS,
	SUROK,
	TODA,
	HABANERA,
} song_t;

void play_song(song_t song);

#endif /*_SONGS_LIB_H_*/
