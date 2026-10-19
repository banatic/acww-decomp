/* Three sound slots and their update (sound.h, SoundSlots). Each failure the game does not
 * expect stops it (OS_Terminate). */
#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "main/game_halt.h"
#include "sound.h"

static_assert(sizeof(SoundSlot) == 0xc, "a slot");
static_assert(offsetof(SoundSlots, slots) == 0x08, "the slots after the link");
static_assert(offsetof(SoundSlots, start) == 0x2c, "the start callback");
static_assert(offsetof(SoundSlots, flags) == 0x34, "the flags");
static_assert(offsetof(SoundSlots, count) == 0x36, "the count");
static_assert(offsetof(SoundParams, volume) == 0x14, "the volume");
static_assert(offsetof(SoundParams, priority) == 0x1c, "the priority");
static_assert(sizeof(SoundParams) == 0x24, "the parameters");

/* NNSSndSeqParam: a sequence's parameters in the sound archive. */
typedef struct SoundSeqParam {
    u16 bank_no;
    u8 volume;
    u8 channel_priority;
    u8 player_priority;
    u8 player_no;
    u16 reserved;
} SoundSeqParam;

/* The hooks SoundParams_Get asks (Sound_SetUnk10Hook, Sound_SetVolumeHook, Sound_SetPanHook). */
extern SoundHook data_021fd19c;
extern SoundHook data_021fd1a4;
extern SoundHook data_021fd1a0;
/* The sound group the game opens (func_020f4220); slots are set up only while it is open. */
extern SoundGroup data_021fd054;
/* The tracks the slots change: 0-3 (0x000f). */
extern const u16 data_0213e858;

extern int NNS_SndPlayerStopSeq(SoundHandle *handle, int fade_frames);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);
extern const SoundSeqParam *NNS_SndArcGetSeqArcParam(int seq_arc, int index);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, u16 track_mask, u8 volume);
extern void NNS_SndPlayerSetTrackPitch(SoundHandle *handle, u16 track_mask, s16 pitch);
extern int NNS_SndArcPlayerStartSeqArcEx(SoundHandle *handle, int player_no, int bank_no, int player_priority, int seq_arc,
                                         int index);
/* NNS_SndHandleInit: the handle made empty. */
extern void func_0210b7e0(SoundHandle *handle);
/* The player's priority (it passes the player to the SDK). */
extern void func_0210b734(SoundHandle *handle, int priority);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The callbacks SoundSlots_Init stores: SoundSlots_StartSlot and SoundSlots_ApplySlot. */
extern void func_020efbb8(SoundSlots *slots, int index, int priority);
extern void func_020efb64(SoundSlots *slots, int index, int priority);

#define PRIORITY_MAX 0x7f
/* A sequence's player priority is taken relative to this. */
#define PRIORITY_MIDDLE 0x40

/* 1 << bit as the ARM's shift by a register does it: the low byte of `bit` counts, and 32 or
 * more give 0. */
static u32 bit_of(int bit)
{
    u32 n = (u32) bit & 0xff;
    return n < 32 ? (u32) 1 << n : 0;
}

/* func_020ef144: the held slots stopped. */
void SoundSlots_StopHeld(SoundSlots *slots, int fade_frames)
{
    int i;

    for (i = 0; i < slots->count; i++) {
        if (SoundSlot_IsHeld(&slots->slots[i])) {
            SoundSlots_StopSlot(slots, i, fade_frames);
        }
    }
}
CLEAN_AS(func_020ef144, SoundSlots_StopHeld)

/* func_020ef1b0: every slot stopped. */
void SoundSlots_StopAll(SoundSlots *slots, int fade_frames)
{
    int i;

    for (i = 0; i < slots->count; i++) {
        SoundSlots_StopSlot(slots, i, fade_frames);
    }
}
CLEAN_AS(func_020ef1b0, SoundSlots_StopAll)

/* func_020ef1f8: slot `index` stopped; the game stops for an index past the count. */
void SoundSlots_StopSlot(SoundSlots *slots, int index, int fade_frames)
{
    if (index >= slots->count) {
        GameHalt_Terminate();
    }
    SoundSlot_Stop(&slots->slots[index], fade_frames);
}
CLEAN_AS(func_020ef1f8, SoundSlots_StopSlot)

/* func_020ef238: every slot's handle let go of its sequence; the game stops without slots. */
void SoundSlots_ReleaseAll(SoundSlots *slots)
{
    int i;

    if (slots == NULL) {
        GameHalt_Terminate();
    }
    for (i = 0; i < slots->count; i++) {
        NNS_SndHandleReleaseSeq(&slots->slots[i].handle);
    }
}
CLEAN_AS(func_020ef238, SoundSlots_ReleaseAll)

/* func_020ef284: every slot stopped at once and its handle released. */
void SoundSlots_Shutdown(SoundSlots *slots)
{
    SoundSlots_StopAll(slots, 0);
    SoundSlots_ReleaseAll(slots);
}
CLEAN_AS(func_020ef284, SoundSlots_Shutdown)

/* func_020ef2a4: a held sequence asked for: a held slot playing it is kept for this frame and
 * given the new volume and pitch, else a free slot is set to start it, held. The slot, or -1
 * when the slots are disabled or none is free.
 * REQUIRES: seq_arc 0 to 255 and index 0 to 0xffff (the game's numbers are
 * seq_arc * 1000 + index): SoundSlot_Plays takes them as a byte and a halfword, where the ROM
 * compares the whole words it is passed. */
int SoundSlots_PlayHeld(SoundSlots *slots, int seq_arc, int index, int volume, short pitch)
{
    int i;

    if ((slots->flags & (1 << SLOTS_ENABLED)) == 0) {
        return -1;
    }
    for (i = 0; i < slots->count; i++) {
        SoundSlot *slot = &slots->slots[i];
        if (SoundSlot_IsHeld(slot) && SoundSlot_Plays(slot, seq_arc, index)) {
            SoundSlot_SetFlag(slot, SLOT_REQUESTED, 1);
            SoundSlot_SetVolumePitch(slot, volume, pitch);
            return i;
        }
    }
    i = SoundSlots_FindFree(slots);
    if (i == slots->count) {
        return -1;
    }
    SoundSlot_SetHeld(&slots->slots[i], seq_arc, index, volume, pitch);
    return i;
}
CLEAN_AS(func_020ef2a4, SoundSlots_PlayHeld)

/* func_020ef3ac: a sequence asked for once: a slot playing it is stopped and set to start it
 * again, else a free slot is. The slot, or -1 when the slots are disabled or none is free.
 * REQUIRES: seq_arc 0 to 255 and index 0 to 0xffff, as for SoundSlots_PlayHeld. */
int SoundSlots_Play(SoundSlots *slots, int seq_arc, int index, int volume, short pitch)
{
    int found = SOUND_NONE;
    int i;

    if ((slots->flags & (1 << SLOTS_ENABLED)) == 0) {
        return -1;
    }
    for (i = 0; i < slots->count; i++) {
        if (SoundSlot_Plays(&slots->slots[i], seq_arc, index)) {
            found = i;
            SoundSlots_StopSlot(slots, i, 0);
            break;
        }
    }
    if (found == SOUND_NONE) {
        found = SoundSlots_FindFree(slots);
    }
    if (found == slots->count) {
        return -1;
    }
    SoundSlot_Set(&slots->slots[found], seq_arc, index, volume, pitch);
    return found;
}
CLEAN_AS(func_020ef3ac, SoundSlots_Play)

/* The player priority a slot's sequence starts with: the archive's, moved by `base` - 0x40 and
 * kept within 0 to 0x7f. The game stops when the sequence is not in the archive. */
static int priority_of(const SoundSlot *slot, int base)
{
    const SoundSeqParam *param = NNS_SndArcGetSeqArcParam(slot->seq_arc, slot->index);
    int priority;

    if (param == NULL) {
        GameHalt_Terminate();
    }
    priority = base + (param->player_priority - PRIORITY_MIDDLE);
    if (priority <= 0) {
        return 0;
    }
    return priority >= PRIORITY_MAX ? PRIORITY_MAX : priority;
}

/* func_020ef498: the slots' frame. Disabled, they are stopped once (the held ones). Enabled,
 * each slot in turn: a held one not asked for again is stopped; a pending one is started with
 * the hooks' priority when their volume is above 0; one started, held or following and playing
 * then gets the hooks' volume, the priority and the pan, and the slots' update callback. The
 * hooks are asked once, at the first slot that needs them. The game stops without slots. */
void SoundSlots_Update(SoundSlots *slots, void *source)
{
    SoundParams params;
    int asked = 0;
    int i;

    if (slots->count == 0) {
        GameHalt_Terminate();
    }
    if ((slots->flags & (1 << SLOTS_ENABLED)) == 0) {
        if ((slots->flags & (1 << SLOTS_UPDATED)) != 0) {
            SoundSlots_StopHeld(slots, 0);
            SoundSlots_SetFlag(slots, SLOTS_UPDATED, 0);
        }
        return;
    }

    params.slots = slots;
    params.source = source;
    params.unk_20 = 0;
    params.volume = 0;
    params.priority = 0;
    params.pan = 0;
    for (i = 0; i < slots->count; i++) {
        SoundSlot *slot = &slots->slots[i];
        int priority = -1;
        int apply = 0;

        if (SoundSlot_IsHeld(slot)) {
            if ((slot->flags & (1 << SLOT_REQUESTED)) == 0) {
                SoundSlots_StopSlot(slots, i, 0);
                continue;
            }
            SoundSlot_SetFlag(slot, SLOT_REQUESTED, 0);
            apply = 1;
        }
        if ((slot->flags & (1 << SLOT_PENDING)) != 0) {
            if (!asked) {
                SoundParams_Get(&params);
                asked = 1;
            }
            if (params.volume > 0) {
                priority = priority_of(slot, params.priority);
                slots->start(slots, i, priority);
                apply = 1;
            }
            SoundSlot_SetFlag(slot, SLOT_PENDING, 0);
        }
        if (!apply) {
            apply = (slot->flags & (1 << SLOT_FOLLOW)) != 0;
        }
        if (apply && slot->handle.player != NULL) {
            if (!asked) {
                SoundParams_Get(&params);
                asked = 1;
            }
            if (priority == -1) {
                priority = priority_of(slot, params.priority);
            }
            NNS_SndPlayerSetVolume(&slot->handle, params.volume);
            func_0210b734(&slot->handle, priority);
            func_0210b634(&slot->handle, data_0213e858, params.pan);
            slots->update(slots, i, priority);
        }
    }
    SoundSlots_SetFlag(slots, SLOTS_UPDATED, 1);
}
CLEAN_AS(func_020ef498, SoundSlots_Update)

/* func_020ef754: the slots let go of (SoundSlots_Shutdown). */
void SoundSlots_Finish(SoundSlots *slots)
{
    SoundSlots_Shutdown(slots);
}
CLEAN_AS(func_020ef754, SoundSlots_Finish)

/* func_020ef760: three empty slots with the game's start and update callbacks, disabled. The
 * game stops unless the sound group data_021fd054 is open (state 1 to 3). */
void SoundSlots_Init(SoundSlots *slots)
{
    int i;

    slots->count = 3;
    slots->start = func_020efbb8;
    slots->update = func_020efb64;
    slots->flags = 0;
    for (i = 0; i < slots->count; i++) {
        SoundSlot_Init(&slots->slots[i]);
    }
    if (data_021fd054.state < 1 || data_021fd054.state >= 4) {
        GameHalt_Terminate();
    }
}
CLEAN_AS(func_020ef760, SoundSlots_Init)

/* func_020ef7fc: the first slot without a sequence and not pending, or the count when none. */
int SoundSlots_FindFree(SoundSlots *slots)
{
    int count = slots->count;
    int i;

    for (i = 0; i < count; i++) {
        const SoundSlot *slot = &slots->slots[i];
        if (slot->handle.player == NULL && (slot->flags & (1 << SLOT_PENDING)) == 0) {
            return i;
        }
    }
    return count;
}
CLEAN_AS(func_020ef7fc, SoundSlots_FindFree)

/* func_020ef840: the slots enabled or disabled (1 / else); the game stops without slots. */
void SoundSlots_SetEnabled(SoundSlots *slots, int enabled)
{
    if (slots == NULL) {
        GameHalt_Terminate();
    }
    SoundSlots_SetFlag(slots, SLOTS_ENABLED, enabled);
}
CLEAN_AS(func_020ef840, SoundSlots_SetEnabled)

/* func_020ef874: flag `bit` of the slots set when `on` is 1, else cleared; the game stops
 * without slots. */
void SoundSlots_SetFlag(SoundSlots *slots, int bit, int on)
{
    if (slots == NULL) {
        GameHalt_Terminate();
    }
    if (on == 1) {
        slots->flags |= bit_of(bit);
    } else {
        slots->flags &= ~bit_of(bit);
    }
}
CLEAN_AS(func_020ef874, SoundSlots_SetFlag)

/* func_020efb64: the slots' update callback: slot `index`'s volume and pitch applied to its
 * tracks. The game stops without slots in use. */
void SoundSlots_ApplySlot(SoundSlots *slots, int index, int priority)
{
    SoundSlot *slot = &slots->slots[index];

    (void) priority;
    if (slots->count == 0) {
        GameHalt_Terminate();
    }
    NNS_SndPlayerSetTrackVolume(&slot->handle, data_0213e858, slot->volume);
    NNS_SndPlayerSetTrackPitch(&slot->handle, data_0213e858, (s16) slot->pitch);
}
CLEAN_AS(func_020efb64, SoundSlots_ApplySlot)

/* func_020efbb8: the slots' start callback: slot `index`'s sequence started on its handle with
 * `priority`, on the archive's player and bank. The game stops without slots in use. */
void SoundSlots_StartSlot(SoundSlots *slots, int index, int priority)
{
    SoundSlot *slot = &slots->slots[index];

    if (slots->count == 0) {
        GameHalt_Terminate();
    }
    NNS_SndArcPlayerStartSeqArcEx(&slot->handle, -1, -1, priority, slot->seq_arc, slot->index);
}
CLEAN_AS(func_020efbb8, SoundSlots_StartSlot)

/* func_020ef8bc: whether the slot is held. */
int SoundSlot_IsHeld(SoundSlot *slot)
{
    return (slot->flags & (1 << SLOT_HELD)) != 0;
}
CLEAN_AS(func_020ef8bc, SoundSlot_IsHeld)

/* func_020ef8d0: flag `bit` of the slot set when `on` is 1, else cleared; the game stops
 * without a slot. */
void SoundSlot_SetFlag(SoundSlot *slot, int bit, int on)
{
    if (slot == NULL) {
        GameHalt_Terminate();
    }
    if (on == 1) {
        slot->flags |= bit_of(bit);
    } else {
        slot->flags &= ~bit_of(bit);
    }
}
CLEAN_AS(func_020ef8d0, SoundSlot_SetFlag)

/* func_020ef918: the slot's sequence stopped, fading over `fade_frames`, and the slot neither
 * held, asked for nor pending. */
void SoundSlot_Stop(SoundSlot *slot, int fade_frames)
{
    if (slot->handle.player != NULL) {
        NNS_SndPlayerStopSeq(&slot->handle, fade_frames);
    }
    SoundSlot_SetFlag(slot, SLOT_HELD, 0);
    SoundSlot_SetFlag(slot, SLOT_REQUESTED, 0);
    SoundSlot_SetFlag(slot, SLOT_PENDING, 0);
}
CLEAN_AS(func_020ef918, SoundSlot_Stop)

/* func_020ef968: whether the slot plays sequence `index` of `seq_arc`. */
int SoundSlot_Plays(SoundSlot *slot, unsigned char seq_arc, unsigned short index)
{
    return slot->handle.player != NULL && slot->index == index && slot->seq_arc == seq_arc;
}
CLEAN_AS(func_020ef968, SoundSlot_Plays)

/* func_020ef998: the slot set to start a sequence (SoundSlot_Set), held and asked for. */
void SoundSlot_SetHeld(SoundSlot *slot, int seq_arc, int index, int volume, short pitch)
{
    SoundSlot_Set(slot, seq_arc, index, volume, pitch);
    SoundSlot_SetFlag(slot, SLOT_HELD, 1);
    SoundSlot_SetFlag(slot, SLOT_REQUESTED, 1);
}
CLEAN_AS(func_020ef998, SoundSlot_SetHeld)

/* func_020ef9dc: the slot set to start sequence `index` of `seq_arc` at the next update, with
 * a volume and pitch; the game stops without a slot. */
void SoundSlot_Set(SoundSlot *slot, unsigned char seq_arc, unsigned short index, int volume, signed short pitch)
{
    if (slot == NULL) {
        GameHalt_Terminate();
    }
    slot->seq_arc = seq_arc;
    slot->index = index;
    SoundSlot_SetFlag(slot, SLOT_PENDING, 1);
    SoundSlot_SetVolumePitch(slot, volume, pitch);
}
CLEAN_AS(func_020ef9dc, SoundSlot_Set)

/* func_020efa30 */
void SoundSlot_SetVolumePitch(SoundSlot *slot, unsigned char volume, unsigned short pitch)
{
    slot->volume = volume;
    slot->pitch = pitch;
}
CLEAN_AS(func_020efa30, SoundSlot_SetVolumePitch)

/* func_020efa3c: an empty slot at full volume. */
void SoundSlot_Init(SoundSlot *slot)
{
    func_0210b7e0(&slot->handle);
    slot->seq_arc = 0;
    slot->index = 0;
    slot->flags = 0;
    slot->pitch = 0;
    slot->volume = 0x7f;
}
CLEAN_AS(func_020efa3c, SoundSlot_Init)

/* func_020efa6c: the hooks asked for the parameters of an update; without a source, nothing at
 * full volume and priority. The game stops when a hook is missing. */
void SoundParams_Get(SoundParams *params)
{
    if (params->source == NULL) {
        params->unk_10 = 0;
        params->volume = 0x7f;
        params->priority = 0x7f;
        params->pan = 0;
        return;
    }
    if (data_021fd19c == NULL) {
        GameHalt_Terminate();
    }
    if (data_021fd1a4 == NULL) {
        GameHalt_Terminate();
    }
    if (data_021fd1a0 == NULL) {
        GameHalt_Terminate();
    }
    params->unk_10 = data_021fd19c(params);
    params->volume = data_021fd1a4(params);
    params->priority = params->volume;
    params->pan = data_021fd1a0(params);
}
CLEAN_AS(func_020efa6c, SoundParams_Get)

/* func_020efb34: the volume hook (NULL: none). */
void Sound_SetVolumeHook(SoundHook hook)
{
    data_021fd1a4 = hook;
}
CLEAN_AS(func_020efb34, Sound_SetVolumeHook)

/* func_020efb44: the hook giving SoundParams.unk_10 (NULL: none). */
void Sound_SetUnk10Hook(SoundHook hook)
{
    data_021fd19c = hook;
}
CLEAN_AS(func_020efb44, Sound_SetUnk10Hook)

/* func_020efb54: the pan hook (NULL: none). */
void Sound_SetPanHook(SoundHook hook)
{
    data_021fd1a0 = hook;
}
CLEAN_AS(func_020efb54, Sound_SetPanHook)
