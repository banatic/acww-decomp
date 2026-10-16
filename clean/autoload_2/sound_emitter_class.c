/* The sound emitter classes (sound_emitter_class.h). */
#include "sound_emitter_class.h"

#include <stddef.h>

#include "clean.h"
#include "heap.h"
#include "sound_system.h"

static_assert(offsetof(SoundEmitterObject, slots) == 0x04, "SoundEmitterObject.slots");
static_assert(offsetof(SoundEmitterObject, last_number) == 0x3c, "SoundEmitterObject.last_number");
static_assert(offsetof(SoundEmitterObject, alternation) == 0x3f, "SoundEmitterObject.alternation");
static_assert(offsetof(SoundEmitterObject, volume) == 0x40, "SoundEmitterObject.volume");
static_assert(sizeof(SoundEmitterObject) == 0x44, "SoundEmitterObject size");

/* The classes' vtables. */
extern const u8 data_0213f090[]; /* kind 2 */
extern const u8 data_0213f058[]; /* kind 99 */
extern const u8 data_020d8414[]; /* kind 1 */

extern SoundSystem data_021fd1bc;

extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int seq_arc, int index, int fade_frames);
/* The base class's constructor (its vtable, kind 0) and destructor (its vtable). */
extern void func_020f5970(SoundEmitterObject *emitter);
extern void func_020f5914(SoundEmitterObject *emitter);
/* The slots' update callback of kind 1's class (SoundEmitterClass_ApplyLowered); the game
 * stores this symbol. */
extern void func_020f555c(SoundSlots *slots, int index, int priority);

/* The player the second effects' handle plays on (SoundEmitterClass_Play, kind 99). */
#define EMITTER_EFFECT_B_PLAYER 10
#define EMITTER_EFFECT_B_VOLUME 100
/* The numbers whose index is varied among four (SoundEmitterClass_Play). */
#define EMITTER_VARIED_A 0x7b
#define EMITTER_VARIED_B 0x7f
/* The numbers that first stop sequence archive 2's sounds (SoundEmitterClass_StopSeqArc2). */
#define EMITTER_STOPS_FIRST 0x838
#define EMITTER_STOPS_LAST 0x83a
/* The number SoundEmitterClass_PlayHeld first stops them for. */
#define EMITTER_HELD_STOPS 0x7f6
/* The volume SoundEmitterClass_PlayAlternate plays at. */
#define EMITTER_ALTERNATE_VOLUME 0x7f
/* Percent of the emitter's volume its slots get while the players are lowered. */
#define EMITTER_LOWERED_PERCENT 0x28

/* The emitter's slots, as the C++ code adjusts a pointer to its base: NULL stays NULL. */
static SoundSlots *slots_of(SoundEmitterObject *emitter)
{
    return emitter != NULL ? &emitter->slots : NULL;
}

/* func_020f539c: kind 2's constructor. */
SoundEmitterObject *SoundEmitterClass_Construct2(SoundEmitterObject *emitter)
{
    func_020f5970(emitter);
    emitter->vtable = data_0213f090;
    emitter->kind = EMITTER_KIND_2;
    return emitter;
}
CLEAN_AS(func_020f539c, SoundEmitterClass_Construct2)

/* Kind 99's destruction: its vtable, kind 1's (whose destructor is inlined here), then the
 * base class's destructor. */
static void destruct_99(SoundEmitterObject *emitter)
{
    emitter->vtable = data_0213f058;
    emitter->vtable = data_020d8414;
    func_020f5914(emitter);
}

/* func_020f53c8: kind 99's destructor that also frees the object. */
SoundEmitterObject *SoundEmitterClass_Destruct99Delete(SoundEmitterObject *emitter)
{
    destruct_99(emitter);
    Heap_OperatorDeleteB(emitter);
    return emitter;
}
CLEAN_AS(func_020f53c8, SoundEmitterClass_Destruct99Delete)

/* func_020f5400: kind 99's destructor. */
SoundEmitterObject *SoundEmitterClass_Destruct99(SoundEmitterObject *emitter)
{
    destruct_99(emitter);
    return emitter;
}
CLEAN_AS(func_020f5400, SoundEmitterClass_Destruct99)

/* func_020f5430: kind 99's constructor, on kind 1's. */
SoundEmitterObject *SoundEmitterClass_Construct99(SoundEmitterObject *emitter)
{
    SoundEmitterClass_Construct1B(emitter);
    emitter->vtable = data_0213f058;
    emitter->kind = EMITTER_KIND_99;
    return emitter;
}
CLEAN_AS(func_020f5430, SoundEmitterClass_Construct99)

/* func_020f545c: `number` raised by 1, 2 or 3 in turn (SoundEmitterClass_NextAlternate) and
 * played at volume 0x7f. `flag` is not read. */
int SoundEmitterClass_PlayAlternate(SoundEmitterObject *emitter, unsigned int number, unsigned int flag)
{
    unsigned int next = SoundEmitterClass_NextAlternate(emitter, number);

    (void) flag;
    return SoundEmitterClass_Play(emitter, (int) next, EMITTER_ALTERNATE_VOLUME, 0);
}
CLEAN_AS(func_020f545c, SoundEmitterClass_PlayAlternate)

/* func_020f5484: the number to play for `number`, odd and even calls in turn. One time in four
 * at random (when the last call of the other parity did not raise it the same way) an odd call
 * raises it by 2 and an even one by 3; otherwise an odd call leaves it and an even one raises it
 * by 1.
 * QUIRK: a raised number is cut to 16 bits; one left as it is is returned whole. */
unsigned int SoundEmitterClass_NextAlternate(SoundEmitterObject *emitter, unsigned int number)
{
    unsigned int roll = SoundSystem_Random(&data_021fd1bc, 4);
    u8 flags = emitter->alternation;
    int lucky = roll == 0 && (flags & EMITTER_PLUS2) == 0 && (flags & EMITTER_PLUS3) == 0;

    if (flags & EMITTER_ODD) {
        if (lucky) {
            number = (u16) (number + 2);
            flags |= EMITTER_PLUS2;
        } else {
            flags &= (u8) ~EMITTER_PLUS2;
        }
    } else {
        if (lucky) {
            number = (u16) (number + 3);
            flags |= EMITTER_PLUS3;
        } else {
            flags &= (u8) ~EMITTER_PLUS3;
            number = (u16) (number + 1);
        }
    }
    emitter->alternation = flags ^ EMITTER_ODD;
    return number;
}
CLEAN_AS(func_020f5484, SoundEmitterClass_NextAlternate)

/* func_020f555c: kind 1's slots' update callback: while the sound system lowers both groups of
 * players, slot `index` gets 40% of the emitter's volume; otherwise nothing is changed.
 * REQUIRES: `slots` is an emitter's (the ROM reads the emitter's byte 0x40 through it). */
void SoundEmitterClass_ApplyLowered(SoundSlots *slots, int index, int priority)
{
    const SoundEmitterObject *emitter;

    (void) priority;
    if (data_021fd1bc.lowered == 0) {
        return;
    }
    emitter = (const SoundEmitterObject *) ((const u8 *) slots - offsetof(SoundEmitterObject, slots));
    NNS_SndPlayerSetVolume(&slots->slots[index].handle, emitter->volume * EMITTER_LOWERED_PERCENT / 100);
}
CLEAN_AS(func_020f555c, SoundEmitterClass_ApplyLowered)

/* Kind 1's construction: the base class's, then its vtable, its slots' update callback, kind
 * 1 and no alternation. */
static void construct_1(SoundEmitterObject *emitter)
{
    func_020f5970(emitter);
    emitter->vtable = data_020d8414;
    emitter->slots.update = func_020f555c;
    emitter->kind = EMITTER_KIND_1;
    emitter->alternation = 0;
}

/* func_020f55cc: kind 1's constructor. */
SoundEmitterObject *SoundEmitterClass_Construct1(SoundEmitterObject *emitter)
{
    construct_1(emitter);
    return emitter;
}
CLEAN_AS(func_020f55cc, SoundEmitterClass_Construct1)

/* func_020f560c: kind 1's constructor as kind 99's calls it; the same as func_020f55cc. */
SoundEmitterObject *SoundEmitterClass_Construct1B(SoundEmitterObject *emitter)
{
    construct_1(emitter);
    return emitter;
}
CLEAN_AS(func_020f560c, SoundEmitterClass_Construct1B)

/* func_020f564c: sequence archive 2's indices 0x52 to 0x60, then 0x36, stopped at once. */
void SoundEmitterClass_StopSeqArc2(SoundEmitterObject *emitter)
{
    (void) emitter;
    for (int index = 0x52; index < 0x61; index++) {
        NNS_SndPlayerStopSeqBySeqArcIdx(2, index, 0);
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(2, 0x36, 0);
}
CLEAN_AS(func_020f564c, SoundEmitterClass_StopSeqArc2)

/* func_020f5690: slot 4: the slots let go of. */
void SoundEmitterClass_Finish(SoundEmitterObject *emitter)
{
    SoundSlots_Finish(slots_of(emitter));
}
CLEAN_AS(func_020f5690, SoundEmitterClass_Finish)

/* func_020f56a4: sound `number` played on a held slot (kept while asked for every frame); for
 * 0x7f6, sequence archive 2's sounds are stopped first. The slot, or 0 while the sound system
 * is muted (its byte 0x4d is 1). */
int SoundEmitterClass_PlayHeld(SoundEmitterObject *emitter, int number, int volume, int pitch)
{
    if (data_021fd1bc.muted == 1) {
        return 0;
    }
    if (number == EMITTER_HELD_STOPS) {
        SoundEmitterClass_StopSeqArc2(emitter);
    }
    return SoundSlots_PlayHeld(slots_of(emitter), number / 1000, number % 1000, volume, (short) pitch);
}
CLEAN_AS(func_020f56a4, SoundEmitterClass_PlayHeld)

/* func_020f5748: sound `number` played once on a slot; the slot, or -1. Kind 99 plays it on
 * the system's second effects handle (player 10, volume 100) instead while both groups of
 * players are lowered, and returns 1. Numbers 0x838 to 0x83a first stop sequence archive 2's
 * sounds. Numbers 0x7b and 0x7f play one of the four indices from theirs at random; when that is
 * the one played last and the first or the last of the four, it is moved by one towards the
 * middle (a middle one is played again). */
int SoundEmitterClass_Play(SoundEmitterObject *emitter, int number, int volume, int pitch)
{
    int index_number;

    if (emitter->kind == EMITTER_KIND_99 && data_021fd1bc.lowered != 0) {
        SoundHandle *handle = &data_021fd1bc.effect_b;

        Sound_StartSeqArcEx(handle, EMITTER_EFFECT_B_PLAYER, -1, -1, number / 1000, number % 1000);
        NNS_SndPlayerSetVolume(handle, EMITTER_EFFECT_B_VOLUME);
        return 1;
    }
    if (number >= EMITTER_STOPS_FIRST && number <= EMITTER_STOPS_LAST) {
        SoundEmitterClass_StopSeqArc2(emitter);
    }
    index_number = number;
    if (number == EMITTER_VARIED_A || number == EMITTER_VARIED_B) {
        index_number = number + (int) SoundSystem_Random(&data_021fd1bc, 4);
        if (index_number == emitter->last_number) {
            if (index_number == number) {
                index_number++;
            } else if (index_number == number + 3) {
                index_number--;
            }
        }
        emitter->last_number = (u16) index_number;
    }
    return SoundSlots_Play(slots_of(emitter), number / 1000, index_number % 1000, volume, (short) pitch);
}
CLEAN_AS(func_020f5748, SoundEmitterClass_Play)

/* func_020f58cc: slot 3: the slots' frame update, with `source` handed on. */
void SoundEmitterClass_Update(SoundEmitterObject *emitter, void *source)
{
    SoundSlots_Update(slots_of(emitter), source);
}
CLEAN_AS(func_020f58cc, SoundEmitterClass_Update)

/* func_020f58e0: slot 2: the slots set up afresh and enabled; no varied sound played last. */
void SoundEmitterClass_Reset(SoundEmitterObject *emitter)
{
    SoundSlots_Init(slots_of(emitter));
    SoundSlots_SetEnabled(slots_of(emitter), 1);
    emitter->last_number = 0;
}
CLEAN_AS(func_020f58e0, SoundEmitterClass_Reset)
