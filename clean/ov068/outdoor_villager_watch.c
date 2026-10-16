/* What a villager out walking in the town looks at while free (outdoor_villager_watch.h). */
#include "outdoor_villager_watch.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/scene_look.h"
#include "outdoor_villager.h"

static_assert(offsetof(OutdoorVillagerWatch, kind) == 0x08, "kind");
static_assert(offsetof(OutdoorVillagerWatch, slot) == 0x0c, "slot");
static_assert(offsetof(OutdoorVillagerWatch, thing) == 0x10, "thing");
static_assert(offsetof(OutdoorVillagerWatch, seen) == 0x14, "seen");
static_assert(sizeof(OutdoorVillagerWatch) <= OUTDOOR_VILLAGER_BEHAVIOUR - OUTDOOR_VILLAGER_WATCH, "size");

/* The range of its looks and the point a look at the player is given. */
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;

/* Overlay 3 (the town's field): the kind of the fish shadow in `slot` (0-5) when its state is
 * 3 or 4, else -1; its point (at 0x120) into `point`, and whether it is in such a state; the
 * kind of the insect in `slot` (its low four bits) and its point; the kind of the insect in
 * `slot`, with `*flag` set to whether its byte 0x254 has reached its byte 0x255 when the kind
 * is not negative. */
extern int func_ov003_02227638(int slot);
extern int func_ov003_02227608(Vec3 *point, int slot);
extern int func_ov003_0222f458(Vec3 *point, int slot);
extern int func_ov003_0222f524(u8 *flag, int slot);

/* No slot or kind. */
#define WATCH_NONE (-1)
/* The things looked for: how far, and how many of each. */
#define WATCH_RANGE 0x5000
#define WATCH_INSECTS 8
#define WATCH_FISH 6
/* The most frames counted in `seen`. */
#define WATCH_SEEN_MAX 2400
/* The requests' priority and whether the target must be in view. */
#define WATCH_PRIORITY 0
#define WATCH_IN_VIEW_ONLY 1

static SceneLook *watch_look(u8 *villager)
{
    return (SceneLook *) (void *) (villager + OUTDOOR_VILLAGER_LOOK);
}

static const Vec3 *watch_position(u8 *villager)
{
    return (const Vec3 *) (const void *) (villager + OUTDOOR_VILLAGER_POSITION);
}

/* func_ov068_0226687c: a frame: nothing while held. When the look's kind is no longer the
 * watch's, the watch is held. Looking at the player (kind 1) with byte 0x18 of its record's
 * state entry 0 or 1 and the player out of sight (SceneLook_CanSee), an insect within 0x5000
 * is looked at, else a fish shadow within 0x5000. Looking at a point (kind 3): a frame counted
 * while the point is in sight, then the insect or fish shadow followed, or the player looked at
 * again. */
void OutdoorVillagerWatch_Update(OutdoorVillagerWatch *watch, u8 *villager)
{
    Vec3 point;
    int slot;
    int kind;

    if (watch->held != 0) {
        return;
    }
    u8 look_kind = watch->kind;
    if (look_kind != watch_look(villager)->kind) {
        watch->held = 1;
        watch->mode = OUTDOOR_VILLAGER_WATCH_HELD;
        return;
    }
    switch (look_kind) {
        case SCENE_LOOK_PLAYER:
            if (func_ov068_0226cf8c(villager) > 1) {
                return;
            }
            if (SceneLook_CanSee(watch_look(villager), villager) != 0) {
                return;
            }
            slot = WATCH_NONE;
            kind = OutdoorVillagerWatch_FindInsect(watch, &point, &slot, watch_position(villager), WATCH_RANGE);
            if (kind != WATCH_NONE) {
                OutdoorVillagerWatch_LookAtInsect(watch, villager, slot, kind, &point);
            } else {
                slot = WATCH_NONE;
                kind = OutdoorVillagerWatch_FindFish(watch, &point, &slot, watch_position(villager), WATCH_RANGE);
                if (kind != WATCH_NONE) {
                    OutdoorVillagerWatch_LookAtFish(watch, villager, slot, kind, &point);
                }
            }
            break;
        case SCENE_LOOK_POINT:
            if (SceneLook_CanSee(watch_look(villager), villager) != 0) {
                OutdoorVillagerWatch_CountSeen(watch);
            }
            switch (watch->mode) {
                case OUTDOOR_VILLAGER_WATCH_INSECT:
                    OutdoorVillagerWatch_FollowInsect(watch, villager);
                    break;
                case OUTDOOR_VILLAGER_WATCH_FISH:
                    OutdoorVillagerWatch_FollowFish(watch, villager);
                    break;
                default:
                    OutdoorVillagerWatch_LookAtPlayer(watch, villager);
                    break;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_0226687c, OutdoorVillagerWatch_Update)

/* ---- Fish shadows */

/* func_ov068_02266968: while the fish shadow is still there and within the look's range, the
 * look follows its point; otherwise the player is looked at again. */
void OutdoorVillagerWatch_FollowFish(OutdoorVillagerWatch *watch, u8 *villager)
{
    Vec3 point;
    if (OutdoorVillagerWatch_FishStill(watch, watch->slot, watch->thing) &&
        OutdoorVillagerWatch_FishNear(watch, &point, watch->slot, watch_position(villager), watch_look(villager)->range)) {
        SceneLook_SetPoint(watch_look(villager), &point);
        return;
    }
    OutdoorVillagerWatch_LookAtPlayer(watch, villager);
}
CLEAN_AS(func_ov068_02266968, OutdoorVillagerWatch_FollowFish)

/* func_ov068_022669c4: the fish shadow in `slot`, of `kind`, looked at, at `point`. */
void OutdoorVillagerWatch_LookAtFish(OutdoorVillagerWatch *watch, u8 *villager, int slot, int kind, const Vec3 *point)
{
    watch->slot = slot;
    watch->thing = kind;
    OutdoorVillagerWatch_Request(watch, villager, SCENE_LOOK_POINT, WATCH_PRIORITY, 0, point, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                                 data_020c814c, WATCH_IN_VIEW_ONLY);
    watch->mode = OUTDOOR_VILLAGER_WATCH_FISH;
    watch->seen = 0;
}
CLEAN_AS(func_ov068_022669c4, OutdoorVillagerWatch_LookAtFish)

/* func_ov068_02266a00: whether the fish shadow in `slot` is in state 3 or 4 and still of
 * `kind`. */
int OutdoorVillagerWatch_FishStill(OutdoorVillagerWatch *watch, int slot, int kind)
{
    (void) watch;
    int now = func_ov003_02227638(slot);
    return now != WATCH_NONE && kind == now;
}
CLEAN_AS(func_ov068_02266a00, OutdoorVillagerWatch_FishStill)

/* func_ov068_02266a24: the first fish shadow in state 3 or 4 whose point (left in `point`) is
 * nearer than `range` to `from` in the ground plane: its kind, its slot in `*slot`; else -1
 * (`*slot` untouched). */
int OutdoorVillagerWatch_FindFish(OutdoorVillagerWatch *watch, Vec3 *point, int *slot, const Vec3 *from, fx32 range)
{
    for (int i = 0; i < WATCH_FISH; i++) {
        int kind = func_ov003_02227638(i);
        if (kind != WATCH_NONE && OutdoorVillagerWatch_FishNear(watch, point, i, from, range)) {
            *slot = i;
            return kind;
        }
    }
    return WATCH_NONE;
}
CLEAN_AS(func_ov068_02266a24, OutdoorVillagerWatch_FindFish)

/* func_ov068_02266a70: whether the fish shadow in `slot` is in state 3 or 4 and its point
 * (left in `point`) nearer than `range` to `from` in the ground plane. */
int OutdoorVillagerWatch_FishNear(OutdoorVillagerWatch *watch, Vec3 *point, int slot, const Vec3 *from, fx32 range)
{
    (void) watch;
    return func_ov003_02227608(point, slot) != 0 && Vec_DistanceXZ(from, point) < range;
}
CLEAN_AS(func_ov068_02266a70, OutdoorVillagerWatch_FishNear)

/* ---- Insects */

/* func_ov068_02266aa0: while the insect is still there and within the look's range, the look
 * follows its point; otherwise the player is looked at again. */
void OutdoorVillagerWatch_FollowInsect(OutdoorVillagerWatch *watch, u8 *villager)
{
    Vec3 point;
    if (OutdoorVillagerWatch_InsectStill(watch, watch->slot, watch->thing)) {
        int kind =
            OutdoorVillagerWatch_InsectNear(watch, &point, watch->slot, watch_position(villager), watch_look(villager)->range);
        if (kind != WATCH_NONE && kind == watch->thing) {
            SceneLook_SetPoint(watch_look(villager), &point);
            return;
        }
    }
    OutdoorVillagerWatch_LookAtPlayer(watch, villager);
}
CLEAN_AS(func_ov068_02266aa0, OutdoorVillagerWatch_FollowInsect)

/* func_ov068_02266b04: the insect in `slot`, of `kind`, looked at, at `point`. */
void OutdoorVillagerWatch_LookAtInsect(OutdoorVillagerWatch *watch, u8 *villager, int slot, int kind, const Vec3 *point)
{
    watch->slot = slot;
    watch->thing = kind;
    OutdoorVillagerWatch_Request(watch, villager, SCENE_LOOK_POINT, WATCH_PRIORITY, 0, point, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                                 data_020c814c, WATCH_IN_VIEW_ONLY);
    watch->mode = OUTDOOR_VILLAGER_WATCH_INSECT;
    watch->seen = 0;
}
CLEAN_AS(func_ov068_02266b04, OutdoorVillagerWatch_LookAtInsect)

/* func_ov068_02266b3c: whether `kind` is not -1 and the insect in `slot` is still of it. */
int OutdoorVillagerWatch_InsectStill(OutdoorVillagerWatch *watch, int slot, int kind)
{
    (void) watch;
    if (kind != WATCH_NONE) {
        u8 flag = 0;
        if (func_ov003_0222f524(&flag, (u8) slot) == kind) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov068_02266b3c, OutdoorVillagerWatch_InsectStill)

/* func_ov068_02266b6c: the first of the eight insects there (its kind not -1) whose point
 * (left in `point`) is nearer than `range` to `from` in the ground plane: its kind, its slot in
 * `*slot`; else -1 (`*slot` untouched). */
int OutdoorVillagerWatch_FindInsect(OutdoorVillagerWatch *watch, Vec3 *point, int *slot, const Vec3 *from, fx32 range)
{
    for (int i = 0; i < WATCH_INSECTS; i++) {
        int kind = OutdoorVillagerWatch_InsectNear(watch, point, i, from, range);
        if (kind != WATCH_NONE) {
            *slot = i;
            return kind;
        }
    }
    return WATCH_NONE;
}
CLEAN_AS(func_ov068_02266b6c, OutdoorVillagerWatch_FindInsect)

/* func_ov068_02266bac: the kind of the insect in `slot` (its point left in `point`) when it is
 * not -1 and the point is nearer than `range` to `from` in the ground plane, else -1. */
int OutdoorVillagerWatch_InsectNear(OutdoorVillagerWatch *watch, Vec3 *point, int slot, const Vec3 *from, fx32 range)
{
    (void) watch;
    int kind = func_ov003_0222f458(point, (u8) slot);
    if (kind == WATCH_NONE || Vec_DistanceXZ(from, point) >= range) {
        return WATCH_NONE;
    }
    return kind;
}
CLEAN_AS(func_ov068_02266bac, OutdoorVillagerWatch_InsectNear)

/* ---- The look */

/* func_ov068_02266be4: a request of the villager's look (SceneLook_Request), whose kind the
 * watch keeps. */
void OutdoorVillagerWatch_Request(OutdoorVillagerWatch *watch, u8 *villager, u8 kind, int priority, int target,
                                  const Vec3 *point, int actor, fx32 range, u8 in_view_only)
{
    SceneLook_Request(watch_look(villager), kind, priority, target, point, actor, range, in_view_only);
    watch->kind = kind;
}
CLEAN_AS(func_ov068_02266be4, OutdoorVillagerWatch_Request)

/* func_ov068_02266c1c: one more frame in sight.
 * QUIRK: the count is 16 bits and is held at 2400 after the step, so from 0xffff it wraps to
 * 0. */
void OutdoorVillagerWatch_CountSeen(OutdoorVillagerWatch *watch)
{
    watch->seen = (u16) (watch->seen + 1);
    if (watch->seen > WATCH_SEEN_MAX) {
        watch->seen = WATCH_SEEN_MAX;
    }
}
CLEAN_AS(func_ov068_02266c1c, OutdoorVillagerWatch_CountSeen)

/* func_ov068_02266c34: the watch held, with a request of the villager's look of its own (the
 * kind's low byte). */
void OutdoorVillagerWatch_Hold(OutdoorVillagerWatch *watch, u8 *villager, int kind, int priority, int target,
                               const Vec3 *point, int actor, fx32 range, u8 in_view_only)
{
    watch->held = 1;
    OutdoorVillagerWatch_Request(watch, villager, (u8) kind, priority, target, point, actor, range, in_view_only);
    watch->mode = OUTDOOR_VILLAGER_WATCH_HELD;
    watch->slot = WATCH_NONE;
    watch->thing = WATCH_NONE;
    watch->seen = 0;
}
CLEAN_AS(func_ov068_02266c34, OutdoorVillagerWatch_Hold)

/* func_ov068_02266c70: free again, looking at this console's player. */
void OutdoorVillagerWatch_LookAtPlayer(OutdoorVillagerWatch *watch, u8 *villager)
{
    watch->held = 0;
    OutdoorVillagerWatch_Request(watch, villager, SCENE_LOOK_PLAYER, WATCH_PRIORITY, 0, &data_021fbee8,
                                 OUTDOOR_VILLAGER_PLAYER_ACTOR, data_020c814c, WATCH_IN_VIEW_ONLY);
    watch->mode = OUTDOOR_VILLAGER_WATCH_PLAYER;
    watch->slot = WATCH_NONE;
    watch->thing = WATCH_NONE;
    watch->seen = 0;
}
CLEAN_AS(func_ov068_02266c70, OutdoorVillagerWatch_LookAtPlayer)

/* func_ov068_02266cb0: held, looking at this console's player. */
void OutdoorVillagerWatch_HoldOnPlayer(OutdoorVillagerWatch *watch, u8 *villager)
{
    OutdoorVillagerWatch_Hold(watch, villager, SCENE_LOOK_PLAYER, WATCH_PRIORITY, 0, &data_021fbee8,
                              OUTDOOR_VILLAGER_PLAYER_ACTOR, data_020c814c, WATCH_IN_VIEW_ONLY);
    watch->mode = OUTDOOR_VILLAGER_WATCH_PLAYER;
    watch->slot = WATCH_NONE;
    watch->thing = WATCH_NONE;
}
CLEAN_AS(func_ov068_02266cb0, OutdoorVillagerWatch_HoldOnPlayer)

/* func_ov068_02266cec: the destructor; nothing to release. */
void OutdoorVillagerWatch_Destruct(OutdoorVillagerWatch *watch)
{
    (void) watch;
}
CLEAN_AS(func_ov068_02266cec, OutdoorVillagerWatch_Destruct)

/* func_ov068_02266cf0: the constructor; nothing to set. */
void OutdoorVillagerWatch_Construct(OutdoorVillagerWatch *watch)
{
    (void) watch;
}
CLEAN_AS(func_ov068_02266cf0, OutdoorVillagerWatch_Construct)
