/* 
 * songs_lib.c
 * Songs collection
 */

#include "songs_lib.h"
#include "player.h"

typedef struct {
	char tone;
	unsigned char length:5;
	unsigned char stop:3;
} note_t;

typedef struct {
	int tempo; // min unit length in ms
	int len; // notes count
	const note_t *notes; // pointer to the song
} song_ctx_t;

#include "songs/sng_bells.c"
#include "songs/sng_happy_new_year.c"
#include "songs/sng_gamma.c"
#include "songs/sng_lada.c"
#include "songs/sng_wals.c"
#include "songs/pust_vsegda.c"
#include "songs/jingle_bells.c"
#include "songs/surok.c"

#define SNG_ENTRY(name) [name] = {name##_T, sizeof(name##_S)/ sizeof(note_t), name##_S}

static const song_ctx_t songs[] = {
	SNG_ENTRY(BELLS),
	SNG_ENTRY(HAPPY_NEW_YEAR),
	SNG_ENTRY(GAMMA),
	SNG_ENTRY(LADA),
	SNG_ENTRY(WALSE),
	SNG_ENTRY(PUST_VSEGDA),
	SNG_ENTRY(JINGLE_BELLS),
	SNG_ENTRY(SUROK),
};

void play_song(song_t song)
{
#if 1
	int len = songs[song].len;
	const note_t *note = songs[song].notes;
	
	player_set_tempo(songs[song].tempo);
	while (len--)
	{
		play(note->tone, note->length, note->stop);
		note++;
	}
	play(PAUSE, 1, 1);
	player_set_tempo(0);
#endif
}
