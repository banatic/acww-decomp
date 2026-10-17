/* The behaviour member of a villager out walking in the town (outdoor_villager_behaviour.h). */
#include "outdoor_villager_behaviour.h"

#include <stdint.h>

#include "clean.h"
#include "main/path_walker.h"
#include "main/scene_action.h"
#include "main/scene_object.h"
#include "main/scene_query.h"
#include "main/session_players.h"
#include "main/villager_entry.h"
#include "outdoor_villager_walks.h"

static_assert(sizeof(OutdoorVillagerBehaviourRow) == 0x10, "behaviour row");

/* The behaviours (filled when the overlay starts). */
extern OutdoorVillagerBehaviourRow data_ov068_02278484[OUTDOOR_VILLAGER_BEHAVIOURS];
/* Half the angle within which the villager must face this console's player to call it over
 * (set when the overlay starts). */
extern s16 data_ov068_02278264;

/* The parts of the member read here besides outdoor_villager.h's. */
#define BEHAVIOUR_BOX 0x00         /* OutdoorVillagerWalksBox */
#define BEHAVIOUR_WORD_28 0x28     /* s32 */
#define BEHAVIOUR_COUNT_2C 0x2c    /* s16: behaviour 17's countdown */
#define BEHAVIOUR_ITEM_CHECK 0x34  /* s16 */
#define BEHAVIOUR_ITEM_HOLD 0x36   /* s16 */
#define BEHAVIOUR_WALKER 0x3c      /* PathWalker */
#define BEHAVIOUR_WALK_TIME 0xd8   /* s16 */
#define BEHAVIOUR_STEP_TIME 0xda   /* s16 */
#define BEHAVIOUR_PAUSE 0xdc       /* s16 */
#define BEHAVIOUR_PAUSE_AGAIN 0xde /* s16 */
#define BEHAVIOUR_WORD_E4 0xe4     /* s32 */
#define BEHAVIOUR_RAISE 0xf8       /* s32 */

/* The box it is made with. */
#define BEHAVIOUR_BOX_LEFT 0x10000
#define BEHAVIOUR_BOX_RIGHT 0x10000
#define BEHAVIOUR_BOX_BACK 0x1a000
#define BEHAVIOUR_BOX_FRONT 0xa000

/* Behaviour 7's call: within 7.0 of the player and facing it. */
#define BEHAVIOUR_CALL_NEAR 0x7000

#define BEHAVIOUR_DEFAULT 0

static u8 *ovb_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static s16 *ovb_half(void *object, u32 offset)
{
    return (s16 *) (void *) ovb_at(object, offset);
}

static s32 *ovb_word(void *object, u32 offset)
{
    return (s32 *) (void *) ovb_at(object, offset);
}

static PathWalker *ovb_walker(OutdoorVillagerBehaviour *self)
{
    return (PathWalker *) (void *) ovb_at(self, BEHAVIOUR_WALKER);
}

/* The villager's town record (its vtable slot 0x64), or null. */
static u8 *ovb_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    uintptr_t code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) code)(villager);
}

/* Calls a start or an update of a behaviour with the villager. */
static void ovb_call(const MemberPointer *member, OutdoorVillagerBehaviour *self, u8 *villager)
{
    void *object = MemberPointer_Object(member, self);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
}

/* A countdown of 16 bits run down to 0. */
static void ovb_count_down(s16 *count)
{
    if (*count > 0) {
        (*count)--;
    }
}

/* func_ov068_0226cc00: whether it walks about (behaviour 0) with the pairing's cooldown out. */
int OutdoorVillagerBehaviour_IsIdle(OutdoorVillagerBehaviour *self)
{
    return OutdoorVillagerWalks_IsDoing(self, BEHAVIOUR_DEFAULT) && self->cooldown == 0;
}
CLEAN_AS(func_ov068_0226cc00, OutdoorVillagerBehaviour_IsIdle)

/* func_ov068_0226cc20: whether behaviour 7 calls this console's player over: there is a
 * player's object, the villager has a town record whose byte 0x1e is full
 * (VillagerEntry_IsByte1EFull), the current scene is not 31, the word at 0xf4 has run out, and
 * the player is within 7.0 of it and no further than data_ov068_02278264 either way of where it
 * faces. The town record is asked for twice. */
int OutdoorVillagerBehaviour_CallsPlayer(OutdoorVillagerBehaviour *self, u8 *villager)
{
    int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    int full = 0;
    if (ovb_record(villager) != NULL) {
        full = VillagerEntry_IsByte1EFull(ovb_record(villager), NULL) != 0;
    }
    if (SceneQuery_CurrentIs31() != 0) {
        return 0;
    }
    if (self->unk_f4 > 0 || !full || player == 0) {
        return 0;
    }
    u8 *object = (u8 *) (uintptr_t) (u32) player;
    if (SceneObject_DistanceTo(villager, object) > BEHAVIOUR_CALL_NEAR) {
        return 0;
    }
    int angle = SceneObject_AngleTo(villager, object);
    int half = data_ov068_02278264;
    return angle >= -half && angle <= half;
}
CLEAN_AS(func_ov068_0226cc20, OutdoorVillagerBehaviour_CallsPlayer)

/* func_ov068_0226ccb0: the behaviour saved to resume started, and none saved any more; whether
 * one was saved. */
int OutdoorVillagerBehaviour_Resume(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->resume >= OUTDOOR_VILLAGER_BEHAVIOURS) {
        return 0;
    }
    OutdoorVillagerBehaviour_Start(self, villager, self->resume);
    OutdoorVillagerBehaviour_ClearResume(self);
    return 1;
}
CLEAN_AS(func_ov068_0226ccb0, OutdoorVillagerBehaviour_Resume)

/* func_ov068_0226ccd0 */
void OutdoorVillagerBehaviour_ClearResume(OutdoorVillagerBehaviour *self)
{
    self->resume = OUTDOOR_VILLAGER_BEHAVIOURS;
}
CLEAN_AS(func_ov068_0226ccd0, OutdoorVillagerBehaviour_ClearResume)

/* func_ov068_0226ccd8: the behaviour running saved to resume. */
void OutdoorVillagerBehaviour_SaveResume(OutdoorVillagerBehaviour *self)
{
    OutdoorVillagerBehaviour_SetResume(self, self->current);
}
CLEAN_AS(func_ov068_0226ccd8, OutdoorVillagerBehaviour_SaveResume)

/* func_ov068_0226cce4 */
void OutdoorVillagerBehaviour_SetResume(OutdoorVillagerBehaviour *self, int index)
{
    self->resume = index;
}
CLEAN_AS(func_ov068_0226cce4, OutdoorVillagerBehaviour_SetResume)

/* func_ov068_0226cce8: behaviour `index` (0 to 23; others are ignored) started: it runs from
 * its first step, and its start (when the row has one) is called with the villager. */
void OutdoorVillagerBehaviour_Start(OutdoorVillagerBehaviour *self, u8 *villager, int index)
{
    if (index < 0 || index >= OUTDOOR_VILLAGER_BEHAVIOURS) {
        return;
    }
    const OutdoorVillagerBehaviourRow *row = &data_ov068_02278484[index];
    self->current = index;
    self->entry = row;
    self->step = 0;
    if (row->start.function != 0) {
        ovb_call(&row->start, self, villager);
    }
}
CLEAN_AS(func_ov068_0226cce8, OutdoorVillagerBehaviour_Start)

/* func_ov068_0226cd34: a frame. `shown` is cleared once this console's player no longer shows
 * an insect or a fish; the running behaviour's update is called; then the countdowns run down:
 * the wait, the walks' four, the pairing's cooldown and the hold at 0x3a, and (only while the
 * villager's action is idle) the word at 0xf4, or once it is out the raise timer, and the held
 * item's check and hold; last behaviour 17's countdown.
 * REQUIRES: the running behaviour's row has an update. */
void OutdoorVillagerBehaviour_Tick(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->shown != 0 && OutdoorVillagerWalks_PlayerShowsCatch(self) == 0) {
        self->shown = 0;
    }
    if (self->entry != NULL) {
        ovb_call(&((const OutdoorVillagerBehaviourRow *) self->entry)->update, self, villager);
    }
    if (self->wait > 0) {
        self->wait--;
    }
    ovb_count_down(ovb_half(self, BEHAVIOUR_WALK_TIME));
    ovb_count_down(ovb_half(self, BEHAVIOUR_STEP_TIME));
    ovb_count_down(ovb_half(self, BEHAVIOUR_PAUSE));
    ovb_count_down(ovb_half(self, BEHAVIOUR_PAUSE_AGAIN));
    if (self->cooldown > 0) {
        self->cooldown--;
    }
    if (self->hold_3a != 0) {
        self->hold_3a--;
    }
    if (SceneAction_IsBusy((const SceneAction *) (void *) ovb_at(villager, OUTDOOR_VILLAGER_ACTION)) == 0) {
        s32 *raise = ovb_word(self, BEHAVIOUR_RAISE);
        if (self->unk_f4 > 0) {
            self->unk_f4--;
        } else if (*raise > 0) {
            (*raise)--;
        }
        ovb_count_down(ovb_half(self, BEHAVIOUR_ITEM_CHECK));
        ovb_count_down(ovb_half(self, BEHAVIOUR_ITEM_HOLD));
    }
    ovb_count_down(ovb_half(self, BEHAVIOUR_COUNT_2C));
}
CLEAN_AS(func_ov068_0226cd34, OutdoorVillagerBehaviour_Tick)

/* func_ov068_0226ce48: the destructor: its walker's. */
OutdoorVillagerBehaviour *OutdoorVillagerBehaviour_Destruct(OutdoorVillagerBehaviour *self)
{
    PathWalker_Destruct(ovb_walker(self));
    return self;
}
CLEAN_AS(func_ov068_0226ce48, OutdoorVillagerBehaviour_Destruct)

/* func_ov068_0226ce5c: the constructor: the walker made and set up, the on-screen box
 * (16.0 either side along x, 26.0 below and 10.0 above along z), no behaviour to resume, and
 * every counter cleared but the walk's time and the held item's hold (-1). */
OutdoorVillagerBehaviour *OutdoorVillagerBehaviour_Construct(OutdoorVillagerBehaviour *self)
{
    s32 *box = ovb_word(self, BEHAVIOUR_BOX);
    PathWalker_Construct(ovb_walker(self));
    *ovb_word(self, BEHAVIOUR_WORD_E4) = 0;
    self->resume = OUTDOOR_VILLAGER_BEHAVIOURS;
    box[0] = BEHAVIOUR_BOX_LEFT;
    box[1] = BEHAVIOUR_BOX_RIGHT;
    box[2] = BEHAVIOUR_BOX_BACK;
    box[3] = BEHAVIOUR_BOX_FRONT;
    self->cooldown = 0;
    PathWalker_Init(ovb_walker(self));
    self->wait = 0;
    *ovb_half(self, BEHAVIOUR_WALK_TIME) = -1;
    *ovb_half(self, BEHAVIOUR_STEP_TIME) = 0;
    self->unk_f4 = 0;
    *ovb_word(self, BEHAVIOUR_RAISE) = 0;
    *ovb_word(self, BEHAVIOUR_WORD_28) = 0;
    *ovb_half(self, BEHAVIOUR_ITEM_CHECK) = 0;
    *ovb_half(self, BEHAVIOUR_ITEM_HOLD) = -1;
    *ovb_half(self, BEHAVIOUR_COUNT_2C) = 0;
    self->count_38 = 0;
    self->hold_3a = 0;
    *ovb_half(self, BEHAVIOUR_PAUSE) = 0;
    *ovb_half(self, BEHAVIOUR_PAUSE_AGAIN) = 0;
    self->shown = 0;
    return self;
}
CLEAN_AS(func_ov068_0226ce5c, OutdoorVillagerBehaviour_Construct)
