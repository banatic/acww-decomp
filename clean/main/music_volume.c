/* The slots that move the music's volume (music_volume.h). */
#include "music_volume.h"

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "music_commands.h"
#include "ov004/member_pointer.h"
#include "sound.h"
#include "field_collision.h"
#include "player_actor_ops.h"
#include "scene_query.h"

static_assert(sizeof(MusicVolumeSlot) == 0x10, "slot size");
static_assert(offsetof(MusicVolumeSlot, state) == 0x0c, "slot state");
static_assert(sizeof(MusicVolume) == 0x88, "volume member size");
static_assert(offsetof(MusicVolume, countdown) == 0x84, "volume member countdown");
static_assert(offsetof(MusicRequest, unk_0c) == 0x0c, "request volume");
static_assert(offsetof(MusicRequest, unk_10) == 0x10, "request byte 0x10");
static_assert(offsetof(MusicRequest, music_started) == 0x14, "request music started");

/* The head slot's state while the queue is not empty. */
#define MUSIC_VOLUME_HEAD_STATE 0x12
/* The player's field actor (func_02095794(4)). */
#define MUSIC_VOLUME_PLAYER 4

/* MusicVolume_ClearStarted as a member function pointer. */
extern const MemberFn data_020da284;
/* The states slot 1 is set to (2: lowered, 3: full, 4: silent), by index. */
extern const u32 data_020c9f1c[];

/* What func_02034270 tells of the ground at a point; func_0203423c releases it. */
typedef struct MusicVolumeGround {
    u8 unk_00[0x30];
    s32 unk_30;
    s32 kind; /* 0x34 */
    u8 unk_38[8];
} MusicVolumeGround;

/* The game's slot destructor and constructor (which also returns the slot), handed to the
 * array helpers. */
extern void func_02036570(void *slot);
extern void func_02036574(void *slot);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

static MusicCommands *music_volume_commands(Obj021c526c *owner)
{
    return (MusicCommands *) (void *) owner->music_commands;
}

/* func_0203600c: no slot held. */
void MusicVolume_ClearHeld(MusicVolume *self)
{
    int i;

    for (i = 0; i < MUSIC_VOLUME_SLOTS; i++) {
        self->slots[i].held = 0;
    }
}
CLEAN_AS(func_0203600c, MusicVolume_ClearHeld)

/* func_02036020: no slot pending. */
void MusicVolume_ClearPending(MusicVolume *self)
{
    int i;

    for (i = 0; i < MUSIC_VOLUME_SLOTS; i++) {
        self->slots[i].pending = 0;
    }
}
CLEAN_AS(func_02036020, MusicVolume_ClearPending)

/* func_02036034: when the head request is current and has a music and some slot not held is
 * pending, the volume asked for: the frames of the pending slot of lowest index, the volume of
 * the active slot of lowest index (0 when none is active), both among the slots not held. */
void MusicVolume_Apply(MusicVolume *self)
{
    Obj021c526c *owner = self->owner;
    const MusicRequest *head = &owner->queue.requests[0];
    int pending = 0;
    int volume = 0;
    int frames = 0;
    int i;

    if (owner->queue.count <= 0 || head->current == 0 || head->music == MUSIC_NONE) {
        return;
    }
    for (i = MUSIC_VOLUME_SLOTS - 1; i >= 0; i--) {
        const MusicVolumeSlot *slot = &self->slots[i];
        if (slot->held != 0) {
            continue;
        }
        if (slot->pending != 0) {
            pending = 1;
            frames = slot->frames;
        }
        if (slot->state != 0) {
            volume = slot->volume;
        }
    }
    if (pending) {
        MusicCommands_SetVolume(music_volume_commands(owner), volume, frames);
    }
}
CLEAN_AS(func_02036034, MusicVolume_Apply)

/* func_020360a8: when the head request has its byte 0x10 set, slots 2 to 6 held for the frame.
 * QUIRK: slot 1 and the head slot 7 are not held. */
void MusicVolume_HoldForHead(MusicVolume *self)
{
    const MusicQueue *queue = &self->owner->queue;
    int i;

    if (queue->count <= 0 || queue->requests[0].unk_10 == 0) {
        return;
    }
    for (i = 2; i <= 6; i++) {
        self->slots[i].held = 1;
    }
}
CLEAN_AS(func_020360a8, MusicVolume_HoldForHead)

/* func_020360d0: slot 7's handler. While the queue is not empty it is active; when the head's
 * music has just been asked for and the head has a volume (word 0x0c), that volume is asked for
 * at once; then every request's "music started" mark is cleared. */
void MusicVolume_UpdateHeadSlot(MusicVolume *self, MusicVolumeSlot *slot)
{
    MusicQueue *queue = &self->owner->queue;

    if (queue->count > 0) {
        const MusicRequest *head = &queue->requests[0];
        if (head->music_started != 0 && head->unk_0c != 0) {
            MusicVolume_Request(slot, head->unk_0c, 0, 1);
        }
        MusicQueue_ForEach(queue, data_020da284);
        slot->state = MUSIC_VOLUME_HEAD_STATE;
    } else {
        slot->state = 0;
    }
}
CLEAN_AS(func_020360d0, MusicVolume_UpdateHeadSlot)

/* func_0203611c: called on each request through data_020da284. */
void MusicVolume_ClearStarted(MusicRequest *request)
{
    request->music_started = 0;
}
CLEAN_AS(func_0203611c, MusicVolume_ClearStarted)

/* func_02036124: slot 6's handler: in scenes 0x27 and 0x28 the volume lowered to 0x40 over
 * 0x28 frames (state 0x11), back to full over 0x28 frames in any other. */
void MusicVolume_UpdateSceneSlot(MusicVolume *self, MusicVolumeSlot *slot)
{
    int state = slot->state;
    int scene = SceneQuery_Current();
    int lowered = scene == 0x27 || scene == 0x28;

    (void) self;
    if (state == 0) {
        if (lowered) {
            MusicVolume_Request(slot, 0x40, 0x28, 1);
            slot->state = 0x11;
        }
    } else if (state == 0x11) {
        if (!lowered) {
            MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 0x28, 1);
            slot->state = 0;
        }
    }
}
CLEAN_AS(func_02036124, MusicVolume_UpdateSceneSlot)

/* func_02036188: slot 5's handler: while the player stands on ground of kind 0x13 or 0x16, or
 * the ground 0x2000 further along z has its word 0x30 at 1, the volume lowered to 0x28 over
 * 0x3c frames (state 0x10); back to full over 0x3c frames otherwise. Without a player it counts
 * as otherwise. */
void MusicVolume_UpdateGroundSlot(MusicVolume *self, MusicVolumeSlot *slot)
{
    int state = slot->state;
    int lowered = 0;
    const Vec3 *player = PlayerActorOps_StartPosition(MUSIC_VOLUME_PLAYER);

    (void) self;
    if (player != NULL) {
        MusicVolumeGround here;
        MusicVolumeGround ahead;
        Vec3 at;

        CollisionGround_Init((CollisionGround *) &here, player, 0, 0);
        at.x = player->x;
        at.y = player->y;
        at.z = (fx32) ((u32) player->z + 0x2000);
        CollisionGround_Init((CollisionGround *) &ahead, &at, 0, 0);
        if (here.kind == 0x13 || here.kind == 0x16 || ahead.unk_30 == 1) {
            lowered = 1;
        }
        CollisionGround_Destroy((CollisionGround *) &ahead);
        CollisionGround_Destroy((CollisionGround *) &here);
    }
    if (state == 0) {
        if (lowered) {
            MusicVolume_Request(slot, 0x28, 0x3c, 1);
            slot->state = 0x10;
        }
    } else if (state == 0x10) {
        if (!lowered) {
            MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 0x3c, 1);
            slot->state = 0;
        }
    }
}
CLEAN_AS(func_02036188, MusicVolume_UpdateGroundSlot)

/* func_02036228: slot 4's handler: state 13 lowers the volume to 0x28 over 15 frames and holds
 * it (14), state 15 brings it back to full over 15 frames. */
void MusicVolume_UpdateSlot4(MusicVolume *self, MusicVolumeSlot *slot)
{
    (void) self;
    if (slot->state == 13) {
        MusicVolume_Request(slot, 0x28, 15, 1);
        slot->state = 14;
    } else if (slot->state == 15) {
        MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 15, 1);
        slot->state = 0;
    }
}
CLEAN_AS(func_02036228, MusicVolume_UpdateSlot4)

/* func_02036264: slot 3's handler: the same with states 10, 11 and 12. */
void MusicVolume_UpdateSlot3(MusicVolume *self, MusicVolumeSlot *slot)
{
    (void) self;
    if (slot->state == 10) {
        MusicVolume_Request(slot, 0x28, 15, 1);
        slot->state = 11;
    } else if (slot->state == 12) {
        MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 15, 1);
        slot->state = 0;
    }
}
CLEAN_AS(func_02036264, MusicVolume_UpdateSlot3)

/* func_020362a0: slot 2's handler: state 7 lowers the volume to 0x28 over 5 frames, holds it (8)
 * and lowers the sound system's second fader; state 9 counts the countdown down and, once it is
 * not above 0, brings the volume back to full over 5 frames and the second fader back.
 * QUIRK: the countdown is set to 0 when state 7 starts and nothing here raises it, so state 9
 * ends on its first frame. */
void MusicVolume_UpdateSlot2(MusicVolume *self, MusicVolumeSlot *slot)
{
    if (slot->state == 7) {
        MusicVolume_Request(slot, 0x28, 5, 1);
        slot->state = 8;
        self->countdown = 0;
        SoundSys_LowerSecond();
    } else if (slot->state == 9) {
        if (self->countdown > 0) {
            self->countdown--;
        }
        if (self->countdown <= 0) {
            MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 5, 1);
            slot->state = 0;
            SoundSys_RestoreSecond();
        }
    }
}
CLEAN_AS(func_020362a0, MusicVolume_UpdateSlot2)

/* func_02036310: slot 1's handler: states 2, 3 and 4 move the volume over 5 frames to 0x28,
 * full or 0 and hold it (5); state 6 brings it back to full over 5 frames. */
void MusicVolume_UpdateSlot1(MusicVolume *self, MusicVolumeSlot *slot)
{
    (void) self;
    switch (slot->state) {
        case 2:
            MusicVolume_Request(slot, 0x28, 5, 1);
            slot->state = 5;
            break;
        case 3:
            MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 5, 1);
            slot->state = 5;
            break;
        case 4:
            MusicVolume_Request(slot, 0, 5, 1);
            slot->state = 5;
            break;
        case 6:
            MusicVolume_Request(slot, MUSIC_VOLUME_FULL, 5, 1);
            slot->state = 0;
            break;
    }
}
CLEAN_AS(func_02036310, MusicVolume_UpdateSlot1)

/* func_02036378: slot 0's handler: nothing. */
void MusicVolume_UpdateSlot0(MusicVolume *self, MusicVolumeSlot *slot)
{
    (void) self;
    (void) slot;
}
CLEAN_AS(func_02036378, MusicVolume_UpdateSlot0)

/* The slots' handlers func_0203637c calls through: a function-local static the game fills from
 * these constants on its first call (ov004/member_pointer.h). */
extern u32 data_021c5270;
extern MemberPointer data_021c5274[8];
extern const MemberPointer data_020da2a4, data_020da25c, data_020da28c, data_020da254, data_020da274, data_020da264,
    data_020da294, data_020da29c;

/* func_0203637c: each slot's handler, from slot 0 to slot 7 (the ROM calls them through a table
 * of member function pointers). */
void MusicVolume_UpdateSlots(MusicVolume *self)
{
    static const MemberPointer *const handlers[8] = {
        &data_020da2a4, &data_020da25c, &data_020da28c, &data_020da254,
        &data_020da274, &data_020da264, &data_020da294, &data_020da29c,
    };
    MemberTable_InitOnce(&data_021c5270, data_021c5274, handlers, 8);
    MusicVolume_UpdateSlot0(self, &self->slots[0]);
    MusicVolume_UpdateSlot1(self, &self->slots[1]);
    MusicVolume_UpdateSlot2(self, &self->slots[2]);
    MusicVolume_UpdateSlot3(self, &self->slots[3]);
    MusicVolume_UpdateSlot4(self, &self->slots[4]);
    MusicVolume_UpdateGroundSlot(self, &self->slots[5]);
    MusicVolume_UpdateSceneSlot(self, &self->slots[6]);
    MusicVolume_UpdateHeadSlot(self, &self->slots[7]);
}
CLEAN_AS(func_0203637c, MusicVolume_UpdateSlots)

/* func_02036448: slot 4 brought back (field actor). */
void MusicVolume_EndSlot4(MusicVolume *self)
{
    self->slots[4].state = 15;
}
CLEAN_AS(func_02036448, MusicVolume_EndSlot4)

/* func_02036450: slot 4 lowered (field actor). */
void MusicVolume_BeginSlot4(MusicVolume *self)
{
    self->slots[4].state = 13;
}
CLEAN_AS(func_02036450, MusicVolume_BeginSlot4)

/* func_02036458: slot 3 brought back (field actor, leaving its state 0x4f). */
void MusicVolume_EndSlot3(MusicVolume *self)
{
    self->slots[3].state = 12;
}
CLEAN_AS(func_02036458, MusicVolume_EndSlot3)

/* func_02036460: slot 3 lowered (field actor). */
void MusicVolume_BeginSlot3(MusicVolume *self)
{
    self->slots[3].state = 10;
}
CLEAN_AS(func_02036460, MusicVolume_BeginSlot3)

/* func_02036468: slot 1 brought back. */
void MusicVolume_EndSlot1(MusicVolume *self)
{
    self->slots[1].state = 6;
}
CLEAN_AS(func_02036468, MusicVolume_EndSlot1)

/* func_02036470: slot 1 set to the state at `index` of data_020c9f1c (0: lowered, 1: full,
 * 2: silent). */
void MusicVolume_SetSlot1(MusicVolume *self, int index)
{
    self->slots[1].state = (s32) data_020c9f1c[index];
}
CLEAN_AS(func_02036470, MusicVolume_SetSlot1)

/* func_02036480: slot 2 brought back. */
void MusicVolume_EndSlot2(MusicVolume *self)
{
    self->slots[2].state = 9;
}
CLEAN_AS(func_02036480, MusicVolume_EndSlot2)

/* func_02036488: slot 2 lowered. */
void MusicVolume_BeginSlot2(MusicVolume *self)
{
    self->slots[2].state = 7;
}
CLEAN_AS(func_02036488, MusicVolume_BeginSlot2)

/* func_02036490: the second fader brought back when slot 2 holds it lowered (states 8 and 9),
 * then every slot and the countdown cleared. */
void MusicVolume_Reset(MusicVolume *self)
{
    int i;

    if (self->slots[2].state == 8 || self->slots[2].state == 9) {
        SoundSys_RestoreSecond();
    }
    for (i = 0; i < MUSIC_VOLUME_SLOTS; i++) {
        MusicVolume_ClearSlot(&self->slots[i]);
    }
    self->countdown = 0;
}
CLEAN_AS(func_02036490, MusicVolume_Reset)

/* func_020364c0: the frame: the handlers, the slots held for the head, the volume asked for,
 * then the pending and held marks cleared. */
void MusicVolume_Execute(MusicVolume *self)
{
    MusicVolume_UpdateSlots(self);
    MusicVolume_HoldForHead(self);
    MusicVolume_Apply(self);
    MusicVolume_ClearPending(self);
    MusicVolume_ClearHeld(self);
}
CLEAN_AS(func_020364c0, MusicVolume_Execute)

/* func_020364e8: the deletion: nothing. */
void MusicVolume_Delete(MusicVolume *self)
{
    (void) self;
}
CLEAN_AS(func_020364e8, MusicVolume_Delete)

/* func_020364ec: the creation: every slot and the countdown cleared. */
void MusicVolume_Create(MusicVolume *self)
{
    int i;

    for (i = 0; i < MUSIC_VOLUME_SLOTS; i++) {
        MusicVolume_ClearSlot(&self->slots[i]);
    }
    self->countdown = 0;
}
CLEAN_AS(func_020364ec, MusicVolume_Create)

/* func_02036510: the destructor: the slots (with the game's slot destructor). */
MusicVolume *MusicVolume_Destruct(MusicVolume *self)
{
    __cxa_vec_cleanup(self->slots, MUSIC_VOLUME_SLOTS, sizeof(MusicVolumeSlot), func_02036570);
    return self;
}
CLEAN_AS(func_02036510, MusicVolume_Destruct)

/* func_0203652c: the constructor: the owner kept, then the slots (with the game's slot
 * constructor and destructor). The countdown is left as it is. */
MusicVolume *MusicVolume_Construct(MusicVolume *self, Obj021c526c *owner)
{
    self->owner = owner;
    __cxa_vec_ctor(self->slots, MUSIC_VOLUME_SLOTS, sizeof(MusicVolumeSlot), func_02036574, func_02036570);
    return self;
}
CLEAN_AS(func_0203652c, MusicVolume_Construct)

/* func_02036558: a volume over `frames` frames asked for, pending as `pending` says. */
void MusicVolume_Request(MusicVolumeSlot *slot, int volume, int frames, int pending)
{
    slot->volume = volume;
    slot->frames = frames;
    slot->pending = (u8) pending;
}
CLEAN_AS(func_02036558, MusicVolume_Request)

/* func_02036560: a slot cleared. */
void MusicVolume_ClearSlot(MusicVolumeSlot *slot)
{
    slot->pending = 0;
    slot->held = 0;
    slot->volume = 0;
    slot->frames = 0;
    slot->state = 0;
}
CLEAN_AS(func_02036560, MusicVolume_ClearSlot)

/* func_02036570: a slot's destructor: nothing. */
void MusicVolume_DestructSlot(MusicVolumeSlot *slot)
{
    (void) slot;
}
CLEAN_AS(func_02036570, MusicVolume_DestructSlot)

/* func_02036574: a slot's constructor: the slot cleared. */
MusicVolumeSlot *MusicVolume_ConstructSlot(MusicVolumeSlot *slot)
{
    MusicVolume_ClearSlot(slot);
    return slot;
}
CLEAN_AS(func_02036574, MusicVolume_ConstructSlot)
