/* The sound objects of overlay 4's field (the C++ classes with vtables 0x0213f0b0 to
 * 0x0213f230, all derived from the one at 0x0213f190): an object of one of twelve kinds, made
 * on a heap of its own, plays through two of NNS's sound handles (at 0x04 and 0x08). The base
 * class gives most slots: start (slot 0), stop and release the handles (slot 1), both handles
 * to full volume (slot 3) and to silence (slot 4); each kind has its own update (slot 2), which
 * takes a position in the world. */
#ifndef CLEAN_MAIN_SOUND_OBJECT_H
#define CLEAN_MAIN_SOUND_OBJECT_H

#include "autoload_2/vector.h"
#include "types.h"

struct SoundObject;

typedef struct SoundObjectVtable {
    void (*start)(struct SoundObject *obj);                        /* 0x00 */
    void *(*release)(struct SoundObject *obj);                     /* 0x04 */
    void (*update)(struct SoundObject *obj, int param, Vec3 *pos); /* 0x08 */
    void (*raise)(struct SoundObject *obj, int param);             /* 0x0c */
    int (*silence)(struct SoundObject *obj);                       /* 0x10 */
} SoundObjectVtable;

typedef struct SoundObject {
    const SoundObjectVtable *vtable;
    u32 handles[2]; /* 0x04: NNS sound handles */
    u8 param;       /* 0x0c: the value slot 3 was last given */
} SoundObject;

#define SOUND_OBJECT_KINDS 12
#define SOUND_OBJECT_KIND_LAST 255 /* the twelfth kind */

int SoundObject_Silence(SoundObject *obj);
void SoundObject_Raise(SoundObject *obj, int param);
void SoundObject_UpdateAt(SoundObject *obj, int param, const Vec3 *pos);
void *SoundObject_Release(SoundObject *obj);
void SoundObject_Start(SoundObject *obj);
u32 SoundObject_MaxSize(void);
SoundObject *SoundObject_New(void *heap, int kind);

#endif
