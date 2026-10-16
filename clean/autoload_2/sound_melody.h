/* Melodies: 16 steps, each a note or a mark, played one sequence of a sequence archive per
 * note (sequence note + 1; sequence 0 of the archive sets the player's variables that say how
 * to play). A step is
 *
 *   0 to 12  a note;
 *   13       a note picked at random among sequences 14 to 19;
 *   14       hold: the note before goes on;
 *   15       rest: the note before is stopped, unless the player's "sustain" variable is 1.
 *
 * Two players use them:
 *
 * - MelodySeq (clean/main/sound.h calls it SoundSeq; overlay 4's field and room objects own
 *   one): steps on the music's beat as the current scene's sound object reports it, each note
 *   lasting a percentage of a beat, with the volume and pan of a position. It plays the
 *   melody of the current sound set.
 * - MelodyPlayer: steps every few frames, the counts read from its sequence's variables, in
 *   one of four layouts (MelodyPlayer_NoteAt).
 *
 * The sound set (MelodySet; data_021fd1bc's sound_set, clean/main/sound.h's SoundSet) holds two
 * MelodyPlayers, a melody of its own, a preset melody index and a volume and pan. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_MELODY_H
#define CLEAN_AUTOLOAD_2_SOUND_MELODY_H

#include "sound.h"
#include "types.h"
#include "vector.h"

#define MELODY_STEPS 16
/* The marks a step may hold instead of a note. */
#define MELODY_RANDOM 13
#define MELODY_HOLD 14
#define MELODY_REST 15

/* MelodySet.state: what the set is doing. */
enum {
    MELODY_SET_IDLE = 0,
    MELODY_SET_PLAYER_B = 1, /* its second player plays a melody loaded by number */
    MELODY_SET_SEQ = 2,      /* a MelodySeq plays the set's melody */
    MELODY_SET_AT = 4,       /* its second player plays a melody at a position */
};

typedef struct MelodySeq {
    SoundHandle handle; /* 0x00 */
    u16 seq_arc;        /* 0x04: the sequence archive of its notes */
    s8 step;            /* 0x06: the step playing, -1 before the first */
    u8 frame;           /* 0x07: frames since the step began or its note was looked at */
    s8 note_percent;    /* 0x08: a note's length in percent of a beat (variable 4); -1 unread */
    s8 sustain;         /* 0x09: variable 3; 1: a rest does not stop the note */
    u8 active;          /* 0x0a */
    u8 note_frames;     /* 0x0b: frames from a note's start to the look at the next step */
} MelodySeq;

typedef struct MelodyPlayer {
    SoundHandle handle; /* 0x00 */
    const u8 *melody;   /* 0x04 */
    u16 seq_arc;        /* 0x08: the sequence archive of its notes */
    u8 active;          /* 0x0a */
    s8 step;            /* 0x0b: the step playing, -1 before the first */
    u8 frame;           /* 0x0c: frames into the step */
    u8 pad_0d;
    s8 step_frames; /* 0x0e: frames a step lasts (variable 0); -1 unread */
    s8 end_frame;   /* 0x0f: the frame of a step at which its note may end (variable 1) */
    s8 layout;      /* 0x10: how the steps map to the melody (variable 2), 0 to 3 */
    s8 sustain;     /* 0x11: variable 3; 1: a rest does not stop the note */
    u8 pad_12[2];
} MelodyPlayer;

typedef struct MelodySet {
    MelodyPlayer player_a;   /* 0x00 */
    MelodyPlayer player_b;   /* 0x14 */
    u8 melody[MELODY_STEPS]; /* 0x28 */
    u8 a_playing;            /* 0x38: the first player's last update had a step playing */
    s8 volume;               /* 0x39: the tracks' volume of a player in layout 3 */
    s8 pan;                  /* 0x3a: the tracks' pan of a player in layout 3 */
    u8 preset;               /* 0x3b: the preset melody last picked */
    u8 state;                /* 0x3c: MELODY_SET_* */
} MelodySet;

int MelodySeq_EndNote(MelodySeq *seq);
void MelodySeq_PlayStep(MelodySeq *seq, const Vec3 *pos);
void MelodySeq_ReadVariables(MelodySeq *seq);
void MelodySeq_Update(MelodySeq *seq, const Vec3 *pos);
void MelodySeq_Start(MelodySeq *seq, unsigned short seq_arc);
void MelodySeq_Stop(MelodySeq *seq);
void MelodySeq_Init(MelodySeq *seq);
void MelodySeq_Destruct(MelodySeq *seq);
void MelodySeq_Construct(MelodySeq *seq);

int MelodySet_LoadSeqArc(MelodySet *set, int seq_arc);
void MelodySet_ResetHeapAndLoad(MelodySet *set, int number);
void MelodySet_SetSeqArcA(MelodySet *set, unsigned short seq_arc);
unsigned char MelodySet_APlaying(MelodySet *set);
int MelodySet_Update(MelodySet *set);
void MelodySet_PlaySeqD3B(MelodySet *set, int index);
void MelodySet_PlayAt(MelodySet *set, const Vec3 *pos, unsigned int kind);
void MelodySet_StartA(MelodySet *set);
void MelodySet_StopB(MelodySet *set);
u8 *MelodySet_LoadPreset(MelodySet *set);
int MelodySet_PlayRandomPreset(MelodySet *set, unsigned int number);
void MelodySet_PlayOwn(MelodySet *set, unsigned int number);
void MelodySet_PlayWith(MelodySet *set, unsigned int number, const u8 *melody);
u8 *MelodySet_Melody(MelodySet *set);
void MelodySet_SetMelody(MelodySet *set, const u8 *melody);
const u8 *MelodySet_DefaultMelody(void);
void MelodySet_MakeCurrent(MelodySet *set);

int MelodyPlayer_Update(MelodyPlayer *player);
int MelodyPlayer_EndNote(MelodyPlayer *player);
void MelodyPlayer_PlayStep(MelodyPlayer *player);
u8 MelodyPlayer_NoteAt(MelodyPlayer *player, u8 step);
void MelodyPlayer_ReadVariables(MelodyPlayer *player);
void MelodyPlayer_Reset(MelodyPlayer *player);
void MelodyPlayer_FadeOut(MelodyPlayer *player);
void MelodyPlayer_SetSeqArc(MelodyPlayer *player, unsigned short seq_arc);
void MelodyPlayer_PlaySeqD3(MelodyPlayer *player, int index);
void MelodyPlayer_Start(MelodyPlayer *player, const u8 *melody);
int MelodyPlayer_StartArc(MelodyPlayer *player, unsigned short seq_arc, const u8 *melody);
void MelodyPlayer_Init(MelodyPlayer *player);

#endif
