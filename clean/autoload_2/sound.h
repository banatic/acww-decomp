/* The game's use of NitroSystem's sound library (NNS_Snd*): the sound heap, the sound archive
 * and its players, and the objects the game builds over them.
 *
 * - The sound heap (data_021fd048): groups of the sound archive are loaded into it with its
 *   level saved before, so that they can be unloaded by going back to that level.
 * - Sequences of a sequence archive are started on a player handle; the game numbers them
 *   seq_arc * 1000 + index (func_020f1da4, func_020f1ed4).
 * - SoundGroup (data_021fd054): a group of the archive loaded for a while, with a list of
 *   SoundSlots playing from it.
 * - SoundSlots (sound_slots.c): three slots, each a handle and the sequence it plays. A
 *   sequence asked for is started at the next SoundSlots_Update with the volume, pan and priority
 *   three hooks give (Sound_Set*Hook); a "held" one is stopped by the first update after a frame
 *   it was not asked for again.
 * - SoundFader: a level moved to a target over a number of frames, in 1/4096ths.
 * - SoundSystem (data_021fd1bc): the game's sound state; it plays the sound effects and the
 *   speaking voice (voice.h). */
#ifndef CLEAN_AUTOLOAD_2_SOUND_H
#define CLEAN_AUTOLOAD_2_SOUND_H

#include "links.h"
#include "types.h"

/* NNSSndHandle: the player a sequence plays on, NULL when none. */
typedef struct SoundHandle {
    void *player;
} SoundHandle;

/* NNSFndList: a list of objects whose link sits `offset` bytes into each. */
typedef struct SoundList {
    void *first;
    void *last;
    u16 count;
    u16 offset;
} SoundList;

/* "No group" and "no level" (0xff). */
#define SOUND_NONE 0xff

/* What a SoundGroup is opened with (passed by value, and kept at 0x15 of the group). */
typedef struct SoundGroupKey {
    u8 group; /* the archive's group, SOUND_NONE: none (the game stops) */
    u8 unk_1;
    u8 unk_2;
    u8 keep_heap; /* non-zero: the group is not loaded */
} SoundGroupKey;

/* A group of the sound archive loaded for a while (SoundGroup_Open, SoundGroup_Close). */
typedef struct SoundGroup {
    SoundList playing; /* 0x00: the SoundSlots playing from it */
    s32 state;         /* 0x0c: 0 closed, 1 open */
    void *unk_10;      /* 0x10: given at opening */
    u8 unk_14;         /* 0x14: given at opening */
    SoundGroupKey key; /* 0x15 */
    u8 pad_19[3];
    s32 heap_level;       /* 0x1c: the heap's level before the group, SOUND_NONE when none */
    SoundHandle handle_a; /* 0x20 */
    SoundHandle handle_b; /* 0x24 */
} SoundGroup;

/* SoundSlot.flags, by bit number (SoundSlot_SetFlag). */
enum SoundSlotBit {
    SLOT_FOLLOW = 0,    /* its parameters are applied at every update (set outside these files) */
    SLOT_PENDING = 1,   /* to be started at the next update */
    SLOT_HELD = 2,      /* stopped by an update unless asked for again since the last one */
    SLOT_REQUESTED = 3, /* asked for since the last update (a held slot) */
};

/* One sequence of a sequence archive and the handle it plays on. */
typedef struct SoundSlot {
    SoundHandle handle; /* 0x00 */
    u16 pitch;          /* 0x04: the tracks' pitch, signed */
    u16 index;          /* 0x06: the sequence in its archive */
    u8 seq_arc;         /* 0x08: the sequence archive */
    u8 flags;           /* 0x09: 1 << SoundSlotBit */
    u8 volume;          /* 0x0a: the tracks' volume, 0x7f full */
    u8 pad_0b;
} SoundSlot;

struct SoundSlots;
typedef void (*SoundSlotsFn)(struct SoundSlots *slots, int index, int priority);

/* SoundSlots.flags, by bit number (SoundSlots_SetFlag). */
enum SoundSlotsBit {
    SLOTS_ENABLED = 0, /* updates start and follow the slots */
    SLOTS_UPDATED = 1, /* updated while enabled; the first update after disabling stops them */
};

/* Three slots, kept in a SoundGroup's list (the link first). Other objects hold one at 4. */
typedef struct SoundSlots {
    ListNode link;       /* 0x00 */
    SoundSlot slots[3];  /* 0x08 */
    SoundSlotsFn start;  /* 0x2c: starts a pending slot (func_020efbb8) */
    SoundSlotsFn update; /* 0x30: applies a slot's volume and pitch (func_020efb64) */
    u16 flags;           /* 0x34: 1 << SoundSlotsBit */
    u8 count;            /* 0x36: the slots in use, 3 */
} SoundSlots;

/* What the hooks are asked for and answer at an update (SoundParams_Get). */
typedef struct SoundParams {
    SoundSlots *slots; /* 0x00 */
    void *source;      /* 0x04: SoundSlots_Update's second argument; NULL: the defaults */
    s32 unk_08[2];
    s32 unk_10;   /* 0x10: from hook data_021fd19c, not used here */
    s32 volume;   /* 0x14: from hook data_021fd1a4; 0 or less: nothing pending is started */
    s32 pan;      /* 0x18: from hook data_021fd1a0 */
    s32 priority; /* 0x1c: the volume again, added to each sequence's player priority */
    s32 unk_20;
} SoundParams;

typedef u32 (*SoundHook)(SoundParams *params);

/* A level moving to a target, in 1/4096ths. */
typedef struct SoundFader {
    s16 target; /* 0x00 */
    u16 frames; /* 0x02: frames left; 0 when still */
    fx32 level; /* 0x04 */
    fx32 step;  /* 0x08: added each frame */
} SoundFader;

/* The game's sound state (data_021fd1bc), as far as these files use it. */
typedef struct SoundSystem {
    u8 unk_00[0x38];
    SoundHandle effect; /* 0x38: the sound effects' handle */
    u8 unk_3c[8];
    s32 voice_type;    /* 0x44: the speaking voice's kind, 0 to 4 */
    SoundHandle voice; /* 0x48: the speaking voice's handle */
} SoundSystem;

void Sound_InitHandle(SoundHandle *handle);
void Sound_StartSeqArcEx(SoundHandle *handle, int player_no, int bank_no, int player_priority, int seq_arc, int index);
int Sound_StartSeqArc(int index, int seq_arc, SoundHandle *handle);
int Sound_StartSeqArcDefault(int index, int seq_arc);
void Sound_Main(void);
void Sound_AllocEffectBuffer(void);
void Sound_StartOutputEffect(int type);
void Sound_DisposeNothing(void *memory, unsigned int size, unsigned int data1, unsigned int data2);
void Sound_Init(void *heap_memory, unsigned int heap_size, const void *arc_path, const void *arc_in_memory);
unsigned int Sound_GetHeap(void);
int Sound_GetHeapLevel(void);
void Sound_RestoreHeapLevel(int level);
int Sound_LoadGroup(int group);
int Sound_StopSequence(void *handle, int fade_frames);

void SoundGroup_StopAll(SoundGroup *group);
void SoundGroup_Unload(SoundGroup *group);
int SoundGroup_Close(SoundGroup *group, int unload);
int SoundGroup_Open(SoundGroup *group, void *unk_10, u8 unk_14, SoundGroupKey key);
int SoundGroup_Load(SoundGroup *group);

int SoundList_Last(SoundList *list);
unsigned long SoundList_First(const SoundList *list);
void *SoundList_Prev(SoundList *list, void *object);
void *SoundList_Next(SoundList *list, void *object);
void SoundList_Remove(SoundList *list, void *object);
void SoundList_Append(SoundList *list, void *object);
void SoundLink_Clear(ListNode *link);

void SoundSystem_UpdateNothing(SoundSystem *system);
int SoundFader_Step(SoundFader *fader);
void SoundFader_Start(SoundFader *fader, short target, short frames);
void SoundFader_Set(SoundFader *fader, int level);
void SoundSystem_PlayEffectWithPan(SoundSystem *system, int index, int pan);
void SoundSystem_StopEffect45(SoundSystem *system);
void SoundSystem_PlayEffect45(SoundSystem *system);

void SoundSlots_StopHeld(SoundSlots *slots, int fade_frames);
void SoundSlots_StopAll(SoundSlots *slots, int fade_frames);
void SoundSlots_StopSlot(SoundSlots *slots, int index, int fade_frames);
void SoundSlots_ReleaseAll(SoundSlots *slots);
void SoundSlots_Shutdown(SoundSlots *slots);
int SoundSlots_PlayHeld(SoundSlots *slots, int seq_arc, int index, int volume, short pitch);
int SoundSlots_Play(SoundSlots *slots, int seq_arc, int index, int volume, short pitch);
void SoundSlots_Update(SoundSlots *slots, void *source);
void SoundSlots_Finish(SoundSlots *slots);
void SoundSlots_Init(SoundSlots *slots);
int SoundSlots_FindFree(SoundSlots *slots);
void SoundSlots_SetEnabled(SoundSlots *slots, int enabled);
void SoundSlots_SetFlag(SoundSlots *slots, int bit, int on);
void SoundSlots_ApplySlot(SoundSlots *slots, int index, int priority);
void SoundSlots_StartSlot(SoundSlots *slots, int index, int priority);

int SoundSlot_IsHeld(SoundSlot *slot);
void SoundSlot_SetFlag(SoundSlot *slot, int bit, int on);
void SoundSlot_Stop(SoundSlot *slot, int fade_frames);
int SoundSlot_Plays(SoundSlot *slot, unsigned char seq_arc, unsigned short index);
void SoundSlot_SetHeld(SoundSlot *slot, int seq_arc, int index, int volume, short pitch);
void SoundSlot_Set(SoundSlot *slot, unsigned char seq_arc, unsigned short index, int volume, signed short pitch);
void SoundSlot_SetVolumePitch(SoundSlot *slot, unsigned char volume, unsigned short pitch);
void SoundSlot_Init(SoundSlot *slot);

void SoundParams_Get(SoundParams *params);
void Sound_SetVolumeHook(SoundHook hook);
void Sound_SetUnk10Hook(SoundHook hook);
void Sound_SetPanHook(SoundHook hook);

#endif
