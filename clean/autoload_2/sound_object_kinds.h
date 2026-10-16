/* The classes of the sound objects of overlay 4's field (clean/main/sound_object.h makes them,
 * by kind). An object plays through two handles; the field calls, each frame, its update with
 * a count of its own and the object's position relative to the listener (NULL: none).
 *
 * Their vtables (0x0213f0b0 to 0x0213f230) have six slots: 0 start (the handles made empty,
 * slot 5 called, both handles silent), 1 release, 2 update, 3 raise (both handles to full
 * volume, the value given kept), 4 silence and 5 play (the kind's sequences started). The
 * base class (0x0213f190) plays nothing and its update only gives both handles the volume and
 * pan of the position; every kind's update ends that way too.
 *
 * Each kind's update starts sequences and sets the sequences' variables or tracks' volumes
 * at given values of the count, some of them picked at random (SoundSystem_Random). The
 * sequences are numbered as point sounds are (seq_arc * 1000 + index); SoundObject_PlaySeq
 * always starts them from sequence archive 1. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_OBJECT_KINDS_H
#define CLEAN_AUTOLOAD_2_SOUND_OBJECT_KINDS_H

#include "sound.h"
#include "types.h"
#include "vector.h"

struct SoundObjectBody;

typedef struct SoundObjectClass {
    void (*start)(struct SoundObjectBody *obj);                              /* 0x00 */
    void (*release)(struct SoundObjectBody *obj);                            /* 0x04 */
    void (*update)(struct SoundObjectBody *obj, int count, const Vec3 *pos); /* 0x08 */
    void (*raise)(struct SoundObjectBody *obj, unsigned char raised);        /* 0x0c */
    void (*silence)(struct SoundObjectBody *obj);                            /* 0x10 */
    void (*play)(struct SoundObjectBody *obj);                               /* 0x14 */
} SoundObjectClass;

/* The base class's layout, with the two bytes after it as kinds 2, 3, 5, 6 and 255 use them. */
typedef struct SoundObjectBody {
    const SoundObjectClass *vtable; /* 0x00 */
    SoundHandle handle_a;           /* 0x04 */
    SoundHandle handle_b;           /* 0x08 */
    u8 raised;                      /* 0x0c: the value slot 3 was last given; 0 from a start */
    s8 step;                        /* 0x0d: the kind's own step or flag */
    u8 last_pick;                   /* 0x0e: kind 255: the piece last picked, 0 to 2 */
    u8 phase;                       /* 0x0f: kind 255: 0 to 2 */
} SoundObjectBody;

/* Kind 4 (0x14 bytes). */
typedef struct SoundObject4 {
    const SoundObjectClass *vtable; /* 0x00 */
    SoundHandle handle_a;           /* 0x04 */
    SoundHandle handle_b;           /* 0x08 */
    u8 raised;                      /* 0x0c */
    u8 pad_0d;
    s16 last_var; /* 0x0e: handle B's variable 0 as last read */
    s32 round;    /* 0x10: 0 or 1 */
} SoundObject4;

/* Kind 7 (0x18 bytes). */
typedef struct SoundObject7 {
    const SoundObjectClass *vtable; /* 0x00 */
    SoundHandle handle_a;           /* 0x04 */
    SoundHandle handle_b;           /* 0x08 */
    u8 raised;                      /* 0x0c: 1: the update starts over */
    u8 pad_0d;
    u16 mute_turn; /* 0x0e: 0 or 1; handle B's tracks 0-5 are muted at a change while 1 */
    u16 changes;   /* 0x10: changes of pattern counted towards the next turn */
    u16 shown;     /* 0x12: the pattern last seen */
    u16 pattern;   /* 0x14: the pair of sequences playing, 0 to 5 */
    u8 pad_16[2];
} SoundObject7;

/* Kind 8 (0x14 bytes). */
typedef struct SoundObject8 {
    const SoundObjectClass *vtable; /* 0x00 */
    SoundHandle handle_a;           /* 0x04 */
    SoundHandle handle_b;           /* 0x08 */
    u8 raised;                      /* 0x0c: 1: the update starts over */
    u8 pad_0d;
    u16 state;  /* 0x0e: 0 to 4, which of handle A's variables was last set */
    u16 frames; /* 0x10: updates since handle A's sequence started over */
    u8 pad_12[2];
} SoundObject8;

/* Kind 10 (0x14 bytes). */
typedef struct SoundObject10 {
    const SoundObjectClass *vtable; /* 0x00 */
    SoundHandle handle_a;           /* 0x04 */
    SoundHandle handle_b;           /* 0x08 */
    u8 raised;                      /* 0x0c */
    u8 change;                      /* 0x0d: 1 while a change of mode is being made */
    u16 mode;                       /* 0x0e: 0 to 16 */
    u16 prev_mode;                  /* 0x10 */
    u16 frames;                     /* 0x12: updates since the last change */
} SoundObject10;

void SoundObjectBase_Play(void);
void SoundObjectBase_ApplyPosition(SoundObjectBody *obj, const Vec3 *pos);
void SoundObjectBase_Silence(SoundObjectBody *obj);
void SoundObjectBase_Raise(SoundObjectBody *obj, unsigned char raised);
void SoundObjectBase_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObjectBase_Release(SoundObjectBody *obj);
void SoundObjectBase_Start(SoundObjectBody *obj);
int SoundObject_PlaySeq(SoundObjectBody *obj, int number, SoundHandle *handle);

void SoundObject255_PlayOther(SoundObjectBody *obj);
void SoundObject255_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObject255_Play(SoundObjectBody *obj);
void SoundObject9_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObject9_Play(SoundObjectBody *obj);
void SoundObject5_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObject5_Play(SoundObjectBody *obj);
void SoundObject3_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObject3_Play(SoundObjectBody *obj);
void SoundObject2_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
void SoundObject2_Play(SoundObjectBody *obj);
void SoundObject2_Start(SoundObjectBody *obj);
void SoundObject1_Play(SoundObjectBody *obj);
unsigned int SoundObject0_Play(SoundObjectBody *obj);
void SoundObject10_Play(SoundObject10 *obj);
void SoundObject10_Start(SoundObject10 *obj);
void SoundObject10_Update(SoundObject10 *obj, int count, const Vec3 *pos);
void SoundObject7_Play(SoundObject7 *obj);
void SoundObject7_Start(SoundObject7 *obj);
void SoundObject7_Update(SoundObject7 *obj, int count, const Vec3 *pos);
int SoundObject8_Play(SoundObject8 *obj);
void SoundObject8_Start(SoundObject8 *obj);
void SoundObject8_Update(SoundObject8 *obj, int count, const Vec3 *pos);
void SoundObject6_Play(SoundObjectBody *obj);
void SoundObject6_Update(SoundObjectBody *obj, int count, const Vec3 *pos);
int SoundObject4_ReadChange(SoundObject4 *obj);
void SoundObject4_Update(SoundObject4 *obj, int unused, const Vec3 *pos);
void SoundObject4_Play(SoundObject4 *obj);

#endif
