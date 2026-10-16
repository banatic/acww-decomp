/* Music cues (clean/main/sound.h calls them SoundCue): a sequence played on a handle of its
 * own, in step with the music's beat (the current scene's MusicBeat, music_beat.h). Its mode
 * is 0 (off), 1 (playing) or 2 (waiting until the sound library's global variable 2, the beat
 * number, reaches `target`).
 *
 * While it plays, each update reads the beat (global variables 2 and 1) and the sequence's own
 * variables, picks the next marked step, gives the handle the volume and pan of a position and
 * a tempo from the beat's, and tells how far the cue is through its span. */
#ifndef CLEAN_AUTOLOAD_2_MUSIC_CUE_H
#define CLEAN_AUTOLOAD_2_MUSIC_CUE_H

#include "sound.h"
#include "types.h"
#include "vector.h"

typedef struct MusicCue {
    SoundHandle handle; /* 0x00 */
    u16 seq_no;         /* 0x04: the sequence it plays */
    u16 marks;          /* 0x06: variables 1 to 4 as four nibbles, bit 15 the first step */
    u8 mode;            /* 0x08: 0 off, 1 playing, 2 waiting */
    s8 layout;          /* 0x09: variable 0; the marks are read while it is 0 or less */
    s8 span;            /* 0x0a: variable 5: the steps of the span, or 0x63 for `length` */
    s8 target;          /* 0x0b: variable 8, or the beat number waited for */
    s8 start;           /* 0x0c: variable 7: the beat number the span starts at */
    s8 next;            /* 0x0d: variable 12: the step the cue goes to; -1 none */
    s8 length;          /* 0x0e: variable 6 */
    u8 started;         /* 0x0f: set once MusicCue_TakeStart has told of the start */
    u8 reached;         /* 0x10: set once the span's end is reached, until `target` is 0 */
    u8 pad_11[3];
} MusicCue;

int MusicCue_Progress(MusicCue *cue);
void MusicCue_ApplyPosition(MusicCue *cue, const Vec3 *pos);
void MusicCue_ReadMarks(MusicCue *cue);
void MusicCue_ReadVariables(MusicCue *cue);
void MusicCue_PickNext(MusicCue *cue);
int MusicCue_Update(MusicCue *cue, const Vec3 *pos);
int MusicCue_TakeStart(MusicCue *cue);
void MusicCue_SetTarget(MusicCue *cue, int value);

#endif
