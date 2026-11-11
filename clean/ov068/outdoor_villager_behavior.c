/* The behavior member of a villager out walking in the town (outdoor_villager_behavior.h). */
#include "outdoor_villager_behavior.h"

#include <stdint.h>

#include "clean.h"
#include "main/path_walker.h"
#include "main/scene_action.h"
#include "main/scene_object.h"
#include "main/scene_query.h"
#include "main/session_players.h"
#include "main/villager_entry.h"
#include "outdoor_villager_walks.h"

static_assert(sizeof(OutdoorVillagerBehaviorRow) == 0x10, "behavior row");

/* The behaviors (filled when the overlay starts). */
extern OutdoorVillagerBehaviorRow data_ov068_02278484[OUTDOOR_VILLAGER_BEHAVIORS];
/* Half the angle within which the villager must face this console's player to call it over
 * (set when the overlay starts). */
extern s16 data_ov068_02278264;

/* The parts of the member read here besides outdoor_villager.h's. */
#define BEHAVIOR_BOX 0x00         /* OutdoorVillagerWalksBox */
#define BEHAVIOR_WORD_28 0x28     /* s32 */
#define BEHAVIOR_COUNT_2C 0x2c    /* s16: behavior 17's countdown */
#define BEHAVIOR_ITEM_CHECK 0x34  /* s16 */
#define BEHAVIOR_ITEM_HOLD 0x36   /* s16 */
#define BEHAVIOR_WALKER 0x3c      /* PathWalker */
#define BEHAVIOR_WALK_TIME 0xd8   /* s16 */
#define BEHAVIOR_STEP_TIME 0xda   /* s16 */
#define BEHAVIOR_PAUSE 0xdc       /* s16 */
#define BEHAVIOR_PAUSE_AGAIN 0xde /* s16 */
#define BEHAVIOR_WORD_E4 0xe4     /* s32 */
#define BEHAVIOR_RAISE 0xf8       /* s32 */

/* The box it is made with. */
#define BEHAVIOR_BOX_LEFT 0x10000
#define BEHAVIOR_BOX_RIGHT 0x10000
#define BEHAVIOR_BOX_BACK 0x1a000
#define BEHAVIOR_BOX_FRONT 0xa000

/* Behavior 7's call: within 7.0 of the player and facing it. */
#define BEHAVIOR_CALL_NEAR 0x7000

#define BEHAVIOR_DEFAULT 0

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

static PathWalker *ovb_walker(OutdoorVillagerBehavior *self)
{
    return (PathWalker *) (void *) ovb_at(self, BEHAVIOR_WALKER);
}

/* The villager's town record (its vtable slot 0x64), or null. */
static u8 *ovb_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    uintptr_t code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) code)(villager);
}

/* Calls a start or an update of a behavior with the villager. */
static void ovb_call(const MemberPointer *member, OutdoorVillagerBehavior *self, u8 *villager)
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

/* func_ov068_0226cc00: whether it walks about (behavior 0) with the pairing's cooldown out. */
int OutdoorVillagerBehavior_IsIdle(OutdoorVillagerBehavior *self)
{
    return OutdoorVillagerWalks_IsDoing(self, BEHAVIOR_DEFAULT) && self->cooldown == 0;
}
CLEAN_AS(func_ov068_0226cc00, OutdoorVillagerBehavior_IsIdle)

/* func_ov068_0226cc20: whether behavior 7 calls this console's player over: there is a
 * player's object, the villager has a town record whose byte 0x1e is full
 * (VillagerEntry_IsByte1eFull), the current scene is not 31, `call_cooldown` has run out, and
 * the player is within 7.0 of it and no further than data_ov068_02278264 either way of where it
 * faces. The town record is asked for twice. */
int OutdoorVillagerBehavior_CallsPlayer(OutdoorVillagerBehavior *self, u8 *villager)
{
    int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    int full = 0;
    if (ovb_record(villager) != NULL) {
        full = VillagerEntry_IsByte1eFull(ovb_record(villager), NULL) != 0;
    }
    if (SceneQuery_CurrentIs31() != 0) {
        return 0;
    }
    if (self->call_cooldown > 0 || !full || player == 0) {
        return 0;
    }
    u8 *object = (u8 *) (uintptr_t) (u32) player;
    if (SceneObject_DistanceTo(villager, object) > BEHAVIOR_CALL_NEAR) {
        return 0;
    }
    int angle = SceneObject_AngleTo(villager, object);
    int half = data_ov068_02278264;
    return angle >= -half && angle <= half;
}
CLEAN_AS(func_ov068_0226cc20, OutdoorVillagerBehavior_CallsPlayer)

/* func_ov068_0226ccb0: the behavior saved to resume started, and none saved any more; whether
 * one was saved. */
int OutdoorVillagerBehavior_Resume(OutdoorVillagerBehavior *self, u8 *villager)
{
    if (self->resume >= OUTDOOR_VILLAGER_BEHAVIORS) {
        return 0;
    }
    OutdoorVillagerBehavior_Start(self, villager, self->resume);
    OutdoorVillagerBehavior_ClearResume(self);
    return 1;
}
CLEAN_AS(func_ov068_0226ccb0, OutdoorVillagerBehavior_Resume)

/* func_ov068_0226ccd0 */
void OutdoorVillagerBehavior_ClearResume(OutdoorVillagerBehavior *self)
{
    self->resume = OUTDOOR_VILLAGER_BEHAVIORS;
}
CLEAN_AS(func_ov068_0226ccd0, OutdoorVillagerBehavior_ClearResume)

/* func_ov068_0226ccd8: the behavior running saved to resume. */
void OutdoorVillagerBehavior_SaveResume(OutdoorVillagerBehavior *self)
{
    OutdoorVillagerBehavior_SetResume(self, self->current);
}
CLEAN_AS(func_ov068_0226ccd8, OutdoorVillagerBehavior_SaveResume)

/* func_ov068_0226cce4 */
void OutdoorVillagerBehavior_SetResume(OutdoorVillagerBehavior *self, int index)
{
    self->resume = index;
}
CLEAN_AS(func_ov068_0226cce4, OutdoorVillagerBehavior_SetResume)

/* func_ov068_0226cce8: behavior `index` (0 to 23; others are ignored) started: it runs from
 * its first step, and its start (when the row has one) is called with the villager. */
void OutdoorVillagerBehavior_Start(OutdoorVillagerBehavior *self, u8 *villager, int index)
{
    if (index < 0 || index >= OUTDOOR_VILLAGER_BEHAVIORS) {
        return;
    }
    const OutdoorVillagerBehaviorRow *row = &data_ov068_02278484[index];
    self->current = index;
    self->entry = row;
    self->step = 0;
    if (row->start.function != 0) {
        ovb_call(&row->start, self, villager);
    }
}
CLEAN_AS(func_ov068_0226cce8, OutdoorVillagerBehavior_Start)

/* func_ov068_0226cd34: a frame. `shown` is cleared once this console's player no longer shows
 * an insect or a fish; the running behavior's update is called; then the countdowns run down:
 * the wait, the walks' four, the pairing's cooldown and `net_hits_timer`, and (only while the
 * villager's action is idle) `call_cooldown`, or once it is out the raise timer, and the held
 * item's check and hold; last behavior 17's countdown.
 * REQUIRES: the running behavior's row has an update. */
void OutdoorVillagerBehavior_Tick(OutdoorVillagerBehavior *self, u8 *villager)
{
    if (self->shown != 0 && OutdoorVillagerWalks_PlayerShowsCatch(self) == 0) {
        self->shown = 0;
    }
    if (self->entry != NULL) {
        ovb_call(&((const OutdoorVillagerBehaviorRow *) self->entry)->update, self, villager);
    }
    if (self->wait > 0) {
        self->wait--;
    }
    ovb_count_down(ovb_half(self, BEHAVIOR_WALK_TIME));
    ovb_count_down(ovb_half(self, BEHAVIOR_STEP_TIME));
    ovb_count_down(ovb_half(self, BEHAVIOR_PAUSE));
    ovb_count_down(ovb_half(self, BEHAVIOR_PAUSE_AGAIN));
    if (self->cooldown > 0) {
        self->cooldown--;
    }
    if (self->net_hits_timer != 0) {
        self->net_hits_timer--;
    }
    if (SceneAction_IsBusy((const SceneAction *) (void *) ovb_at(villager, OUTDOOR_VILLAGER_ACTION)) == 0) {
        s32 *raise = ovb_word(self, BEHAVIOR_RAISE);
        if (self->call_cooldown > 0) {
            self->call_cooldown--;
        } else if (*raise > 0) {
            (*raise)--;
        }
        ovb_count_down(ovb_half(self, BEHAVIOR_ITEM_CHECK));
        ovb_count_down(ovb_half(self, BEHAVIOR_ITEM_HOLD));
    }
    ovb_count_down(ovb_half(self, BEHAVIOR_COUNT_2C));
}
CLEAN_AS(func_ov068_0226cd34, OutdoorVillagerBehavior_Tick)

/* func_ov068_0226ce48: the destructor: its walker's. */
OutdoorVillagerBehavior *OutdoorVillagerBehavior_Destruct(OutdoorVillagerBehavior *self)
{
    PathWalker_Destruct(ovb_walker(self));
    return self;
}
CLEAN_AS(func_ov068_0226ce48, OutdoorVillagerBehavior_Destruct)

/* func_ov068_0226ce5c: the constructor: the walker made and set up, the on-screen box
 * (16.0 either side along x, 26.0 below and 10.0 above along z), no behavior to resume, and
 * every counter cleared but the walk's time and the held item's hold (-1). */
OutdoorVillagerBehavior *OutdoorVillagerBehavior_Construct(OutdoorVillagerBehavior *self)
{
    s32 *box = ovb_word(self, BEHAVIOR_BOX);
    PathWalker_Construct(ovb_walker(self));
    *ovb_word(self, BEHAVIOR_WORD_E4) = 0;
    self->resume = OUTDOOR_VILLAGER_BEHAVIORS;
    box[0] = BEHAVIOR_BOX_LEFT;
    box[1] = BEHAVIOR_BOX_RIGHT;
    box[2] = BEHAVIOR_BOX_BACK;
    box[3] = BEHAVIOR_BOX_FRONT;
    self->cooldown = 0;
    PathWalker_Init(ovb_walker(self));
    self->wait = 0;
    *ovb_half(self, BEHAVIOR_WALK_TIME) = -1;
    *ovb_half(self, BEHAVIOR_STEP_TIME) = 0;
    self->call_cooldown = 0;
    *ovb_word(self, BEHAVIOR_RAISE) = 0;
    *ovb_word(self, BEHAVIOR_WORD_28) = 0;
    *ovb_half(self, BEHAVIOR_ITEM_CHECK) = 0;
    *ovb_half(self, BEHAVIOR_ITEM_HOLD) = -1;
    *ovb_half(self, BEHAVIOR_COUNT_2C) = 0;
    self->net_hits = 0;
    self->net_hits_timer = 0;
    *ovb_half(self, BEHAVIOR_PAUSE) = 0;
    *ovb_half(self, BEHAVIOR_PAUSE_AGAIN) = 0;
    self->shown = 0;
    return self;
}
CLEAN_AS(func_ov068_0226ce5c, OutdoorVillagerBehavior_Construct)
