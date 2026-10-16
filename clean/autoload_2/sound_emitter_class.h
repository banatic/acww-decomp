/* The sound emitter classes (clean/main/sound_emitter.h calls them SoundEmitter): the base
 * class (vtable 0x0213f074, 0x44 bytes) holds three sound slots (sound.h, SoundSlots) at 0x04
 * and plays sounds on them by number (seq_arc * 1000 + index). Its derived classes add no
 * fields and are told apart by a byte, `kind`:
 *
 *   kind 0: the base class;
 *   kind 1: vtable 0x020d8414, whose slots' update callback turns the slots down while the
 *           sound system lowers its players;
 *   kind 2: vtable 0x0213f090 (overlay 9 keeps its own copy of the destructor);
 *   kind 99: vtable 0x0213f058, derived from kind 1's class (the field actor's emitter at
 *           0x83c); while the sound system lowers its players, it plays on the system's second
 *           effects handle instead of its slots. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_EMITTER_CLASS_H
#define CLEAN_AUTOLOAD_2_SOUND_EMITTER_CLASS_H

#include "sound.h"
#include "types.h"

/* SoundEmitterObject.alternation, by bit (SoundEmitterClass_NextAlternate). */
enum {
    EMITTER_ODD = 1 << 0,   /* the next call is an odd one */
    EMITTER_PLUS2 = 1 << 1, /* the last odd call raised the number by 2 */
    EMITTER_PLUS3 = 1 << 2, /* the last even call raised the number by 3 */
};

/* The kinds (SoundEmitterObject.kind). */
enum {
    EMITTER_KIND_BASE = 0,
    EMITTER_KIND_1 = 1,
    EMITTER_KIND_2 = 2,
    EMITTER_KIND_99 = 99,
};

typedef struct SoundEmitterObject {
    const void *vtable; /* 0x00 */
    SoundSlots slots;   /* 0x04 */
    u16 last_number;    /* 0x3c: the last of the varied sounds played (SoundEmitterClass_Play) */
    u8 kind;            /* 0x3e */
    u8 alternation;     /* 0x3f */
    u8 volume;          /* 0x40: in percent, used while the sound system lowers its players */
    u8 pad_41[3];
} SoundEmitterObject;

SoundEmitterObject *SoundEmitterClass_Construct2(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Destruct99Delete(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Destruct99(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Construct99(SoundEmitterObject *emitter);
int SoundEmitterClass_PlayAlternate(SoundEmitterObject *emitter, unsigned int number, unsigned int flag);
unsigned int SoundEmitterClass_NextAlternate(SoundEmitterObject *emitter, unsigned int number);
void SoundEmitterClass_ApplyLowered(SoundSlots *slots, int index, int priority);
SoundEmitterObject *SoundEmitterClass_Construct1(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Construct1B(SoundEmitterObject *emitter);
void SoundEmitterClass_StopSeqArc2(SoundEmitterObject *emitter);
void SoundEmitterClass_Finish(SoundEmitterObject *emitter);
int SoundEmitterClass_PlayHeld(SoundEmitterObject *emitter, int number, int volume, int pitch);
int SoundEmitterClass_Play(SoundEmitterObject *emitter, int number, int volume, int pitch);
void SoundEmitterClass_Update(SoundEmitterObject *emitter, void *source);
void SoundEmitterClass_Reset(SoundEmitterObject *emitter);
void SoundEmitterClass_DestructBase(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_DestructBaseDelete(SoundEmitterObject *emitter);
void SoundEmitterClass_DestructBaseB(SoundEmitterObject *emitter);
void SoundEmitterClass_ConstructBaseB(SoundEmitterObject *emitter);
void SoundEmitterClass_ConstructBase(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Destruct2(SoundEmitterObject *emitter);
SoundEmitterObject *SoundEmitterClass_Destruct2Delete(SoundEmitterObject *emitter);

#endif
