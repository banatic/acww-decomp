/* The music's beat, as the scene sound objects of kinds 10 and 41 follow it (their part at
 * 0x08, sound_scene.h).
 *
 * - MusicBeat (vtable 0x0213f25c): reads, every frame, the sound library's global variable 2
 *   (a beat number: a change marks a new beat), the music's variable 6 and the music's tempo
 *   (from the sound driver), from which it works out the frames a beat lasts. When the music
 *   stops it keeps a tempo of 120 instead; while nothing plays on the music's handle it starts
 *   sequence 0xf8 there. MelodySeq (sound_melody.h) and MusicCue (music_cue.h) read it.
 * - MusicBeatShow (vtable 0x0213f250), class 41's part: a MusicBeat that, while on, also fills
 *   a MusicShowState from the music's variables and tracks. The sound system keeps it as its
 *   owner (SoundSystem.owner), and hands its state to the overlays (SoundSystem_OwnerData:
 *   overlays 4 and 68 read it; overlay 68 keeps a copy of its own, set up by
 *   MusicShowState_Init). */
#ifndef CLEAN_AUTOLOAD_2_MUSIC_BEAT_H
#define CLEAN_AUTOLOAD_2_MUSIC_BEAT_H

#include "sound.h"
#include "types.h"

struct MusicBeat;

typedef struct MusicBeatVtable {
    void (*update)(struct MusicBeat *beat); /* 0x00: the frame's update */
} MusicBeatVtable;

typedef struct MusicBeat {
    const MusicBeatVtable *vtable; /* 0x00 */
    fx32 beat_frames;              /* 0x04: frames a beat lasts, 600 / tempo */
    u8 fixed_tempo;                /* 0x08: set while the music is stopped: the tempo stays 120 */
    u8 unk_09;                     /* 0x09: cleared by MusicBeat_Reset, not read here */
    u8 new_beat;                   /* 0x0a: set on the frames global variable 2 changes */
    s8 unk_0b;                     /* 0x0b: -1, not read here */
    s8 unk_0c;                     /* 0x0c: -1, not read here */
    u8 pad_0d;
    u16 tempo; /* 0x0e: beats a minute */
    s8 beat;   /* 0x10: global variable 2 as last read; -1 before */
    u8 pad_11;
    s16 var6; /* 0x12: the music's variable 6 as last read */
} MusicBeat;

/* What MusicBeatShow makes of the music (the overlays read it). */
typedef struct MusicShowState {
    s8 type;       /* 0x00: the music's variable 4, -1 until read */
    s8 track_kind; /* 0x01: by the first of tracks 2 to 13 that sounds (MusicBeatShow_FindTrack) */
    s8 var0;       /* 0x02: the music's variable 0 */
    s8 var2;       /* 0x03: the music's variable 2 */
    s8 var3;       /* 0x04: the music's variable 3 */
    u8 pad_05[3];
    fx32 frame_a; /* 0x08: the count (variable 1) / 3 */
    fx32 frame_b; /* 0x0c: 4.0 up to 20.0, from the count (MusicBeatShow_UpdateFrames) */
    fx32 frame_c; /* 0x10: 12.0 up to 32.0, from the count */
    u8 on;        /* 0x14: MusicBeatShow_Update does nothing while 0 */
    u8 unk_15;    /* 0x15: 1, or 2 for music 0x6e; not read here */
    u8 style;     /* 0x16: 0 to 3, by the music playing when the type is read */
    u8 pad_17;
    s16 count; /* 0x18: the music's variable 1 as last read; -1 before */
    u8 half;   /* 0x1a: flips each time the count goes down */
    u8 pad_1b;
} MusicShowState;

typedef struct MusicBeatShow {
    MusicBeat beat;      /* 0x00 */
    MusicShowState show; /* 0x14 */
} MusicBeatShow;

void MusicBeatShow_UpdateFrames(MusicBeatShow *part);
void MusicBeatShow_ReadVariables(MusicBeatShow *part);
void MusicBeatShow_FindTrack(MusicBeatShow *part);
void MusicBeatShow_Update(MusicBeatShow *part);
void MusicBeatShow_SetOn(MusicBeatShow *part, unsigned char on);
void *MusicBeatShow_Destruct(MusicBeatShow *part);
MusicBeatShow *MusicBeatShow_Construct(MusicBeatShow *part);
void MusicShowState_Init(MusicShowState *show);

void MusicBeat_ReadTempo(MusicBeat *beat);
void MusicBeat_Update(MusicBeat *beat);
void MusicBeat_Reset(MusicBeat *beat, unsigned char fixed_tempo);
MusicBeat *MusicBeat_DestructCopy(MusicBeat *beat);
MusicBeat *MusicBeat_Destruct(MusicBeat *beat);
MusicBeat *MusicBeat_Construct(MusicBeat *beat);
void *MusicBeat_ConstructCopy(MusicBeat *beat);

#endif
