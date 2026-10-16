/* Three kinds of objects that play sounds through a handle of NNS's sound player, and the
 * main program's calls into them. Positions handed on are taken relative to data_021c67b8,
 * and only while the camera (data_021c67a4) exists.
 *
 * - SoundSource (the C++ class with vtable 0x0213f03c, derived from 0x0213efe8; 12 bytes):
 *   a sound asked for by number each frame. Its handle is at 0x04, the number at 0x08 and its
 *   flags at 0x0a: asked for this frame (1), keep playing when not asked (2), the number
 *   changed (4). Overlay 3 and the main program keep arrays of them.
 * - SoundEmitter (the C++ class with vtable 0x0213f074, 0x44 bytes, and its derived classes
 *   0x020d8414 and 0x0213f058): the field actor's two at 0x83c and 0x880 play its sounds.
 * - PointSound (overlay 4's room objects): a sound at a point in a list kept by the sound
 *   layer, with its handle at 0x08. */
#ifndef CLEAN_MAIN_SOUND_EMITTER_H
#define CLEAN_MAIN_SOUND_EMITTER_H

#include "autoload_2/vector.h"
#include "types.h"

struct SoundSource;

typedef struct SoundSourceVtable {
    int (*init)(struct SoundSource *source);                     /* 0x00: returns nothing (SoundSource_Init) */
    void (*release)(struct SoundSource *source);                 /* 0x04 */
    void (*play_held)(struct SoundSource *source, int number);   /* 0x08 */
    void (*play)(struct SoundSource *source, int number);        /* 0x0c */
    void (*update)(struct SoundSource *source, const Vec3 *pos); /* 0x10 */
} SoundSourceVtable;

typedef struct SoundSource {
    const SoundSourceVtable *vtable;
    u32 handle; /* 0x04: an NNS sound handle */
    u16 number; /* 0x08 */
    u8 flags;   /* 0x0a */
} SoundSource;

struct SoundEmitter;

typedef struct SoundEmitterVtable {
    const void *destruct[2];                                       /* 0x00 */
    void (*stop)(struct SoundEmitter *emitter);                    /* 0x08 */
    void (*update)(struct SoundEmitter *emitter, const Vec3 *pos); /* 0x0c */
    int (*vfunc_10)(struct SoundEmitter *emitter);                 /* 0x10 */
} SoundEmitterVtable;

typedef struct SoundEmitter {
    const SoundEmitterVtable *vtable;
    u8 unk_04[0x40];
} SoundEmitter;

void SoundSource_Release(SoundSource *source);
void SoundSource_Play(SoundSource *source, int number);
void SoundSource_PlayHeld(SoundSource *source, int number);
void SoundSource_Update(SoundSource *source, const Vec3 *pos);
void SoundSource_UpdateAt(SoundSource *source, const Vec3 *pos);
int SoundSource_Init(SoundSource *source);

int SoundEmitter_Vfunc10(SoundEmitter *emitter);
int SoundEmitter_Play(SoundEmitter *emitter, int number, int volume, int arg);
void SoundEmitter_PlayAlternating(SoundEmitter *emitter, u32 number, u32 flag);
void SoundEmitter_UpdateAt(SoundEmitter *emitter, const Vec3 *pos);
void SoundEmitter_Stop(SoundEmitter *emitter);
int SoundEmitter_Vfunc10B(SoundEmitter *emitter);
int SoundEmitter_PlayEx(SoundEmitter *emitter, int number, int arg2, int arg3);
int SoundEmitter_PlayB(SoundEmitter *emitter, int number, int volume, int arg);
void SoundEmitter_UpdateAtB(SoundEmitter *emitter, const Vec3 *pos);
void SoundEmitter_StopB(SoundEmitter *emitter);

int PointSound_CanStartList(void);
void PointSound_SetVariable(void *sound, s16 value);
void PointSound_Release(char *sound);
void PointSound_UpdateVolumeAt(void *sound, const Vec3 *pos);
void PointSound_PlayAt(void *sound, int number, const Vec3 *pos);
void PointSound_PlayAtB(void *sound, int number, const Vec3 *pos);
void PointSound_Init(void *sound, int owner);
void PointSound_FlushList(void *list);
void PointSound_StartList(char *list);

#endif
