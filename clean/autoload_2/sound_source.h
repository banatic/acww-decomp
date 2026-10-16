/* The sound source class (vtable 0x0213efe8; 12 bytes; clean/main/sound_emitter.h calls it
 * SoundSource): a sound asked for by number, frame by frame, and played on its own handle at a
 * volume, pan and priority that follow its position. Its derived classes (vtables 0x0213f004,
 * 0x0213f020 and 0x0213f03c) have their own copies of some of its slots.
 *
 * A number is seq_arc * 1000 + index. Each frame the owner asks for the sound (Play, or
 * PlayHeld to keep it playing while it is not asked for) and then updates it with its position
 * relative to the listener (Update): the sound is started or followed while asked for and near
 * enough, and stopped otherwise. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_SOURCE_H
#define CLEAN_AUTOLOAD_2_SOUND_SOURCE_H

#include "sound.h"
#include "types.h"
#include "vector.h"

/* SoundSourceObject.flags. */
enum {
    SOURCE_ASKED = 1 << 0,   /* asked for since the last update */
    SOURCE_HOLD = 1 << 1,    /* keep playing while it is not asked for */
    SOURCE_CHANGED = 1 << 2, /* the number changed: what plays is stopped at the next update */
};

typedef struct SoundSourceObject {
    const void *vtable; /* 0x00 */
    SoundHandle handle; /* 0x04 */
    u16 number;         /* 0x08 */
    u8 flags;           /* 0x0a */
    u8 pad_0b;
} SoundSourceObject;

void SoundSourceClass_UpdateB(SoundSourceObject *source, const Vec3 *pos);
void SoundSourceClass_PlayB(SoundSourceObject *source, unsigned short number);
void SoundSourceClass_PlayHeldB(SoundSourceObject *source, unsigned short number);
void SoundSourceClass_InitB(SoundSourceObject *source);
void SoundSourceClass_InitC(SoundSourceObject *source);
void SoundSourceClass_InitD(SoundSourceObject *source);
void SoundSourceClass_Update(SoundSourceObject *source, const Vec3 *pos);
int SoundSourceClass_Priority(int number, int volume);
void SoundSourceClass_Play(SoundSourceObject *source, unsigned short number);
void SoundSourceClass_PlayHeld(SoundSourceObject *source, unsigned short number);
void SoundSourceClass_Release(SoundSourceObject *source);
void SoundSourceClass_Init(SoundSourceObject *source);

#endif
