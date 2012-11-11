/* 
 * songs_lib.c
 * Songs collection
 */

#include "songs_lib.h"
#include "player.h"

typedef struct {
	char tone;
	char length:7;
	char stop:1;
} note_t;

typedef struct {
	int tempo; // min unit length in ms
	int len; // notes count
	const note_t *notes; // pointer to the song
} song_ctx_t;

#include "songs/sng_bells.c"
#include "songs/sng_happy_new_year.c"
#include "songs/sng_gamma.c"

#define SNG_ENTRY(name) [name] = {name##_T, sizeof(name##_S)/ sizeof(note_t), name##_S}

static const song_ctx_t songs[] = {
	SNG_ENTRY(BELLS),
	SNG_ENTRY(HAPPY_NEW_YEAR),
	SNG_ENTRY(GAMMA),
};

void play_song(song_t song)
{
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
}
