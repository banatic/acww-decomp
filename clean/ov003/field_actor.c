/* Overlay 3's part of the field actor (field_actor.h). */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/fx_math.h" /* Math_Atan2 */
#include "autoload_2/input.h"   /* PadState */
#include "clean.h"
#include "main/calendar.h"     /* DateTime */
#include "main/group_params.h" /* GroupParams_CanOpen, GroupParams_C4CIs1 */
#include "main/session.h"      /* NetSession */
#include "snowman.h"           /* Snowman_Knock */
#include "autoload_2/vector.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/block_020b220c.h"
#include "main/block_020ba298.h"
#include "main/block_021d27ac.h"
#include "main/board_notices.h"
#include "main/camera_control.h"
#include "main/camera_modes.h"
#include "main/catch_panel.h"
#include "main/catch_sphere.h"
#include "main/collision_map.h"
#include "main/collision_query.h"
#include "main/current_pockets.h"
#include "main/date_time.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/face_texture.h"
#include "main/field_actor.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/fish_disp.h"
#include "main/fishing_float.h"
#include "main/frame_ctrl.h"
#include "main/globe.h"
#include "main/held_item.h"
#include "main/item_code.h"
#include "main/item_record.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/music_volume.h"
#include "main/name_texts.h"
#include "main/packed_bytes.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_exit.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/screen_panels.h"
#include "main/session_players.h"
#include "main/sky.h"
#include "main/sound.h"
#include "main/talk_object.h"
#include "main/tile_changes.h"
#include "main/tile_effects.h"
#include "main/tile_requests.h"
#include "main/touch_pick_shapes.h"
#include "main/town_objects.h"
#include "main/villager_events.h"
#include "fish_shadow.h"
#include "growth_model.h"
#include "object_actors.h"
#include "thrown_bottle.h"
#include "tile_event.h"
#include "town_insect.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, unk_098) == 0x98, "0x98");
static_assert(offsetof(FieldActor, unk_140) == 0x140, "0x140");
static_assert(offsetof(FieldActor, unk_144) == 0x144, "0x144");
static_assert(offsetof(FieldActor, unk_148) == 0x148, "0x148");
static_assert(offsetof(FieldActor, aim_point) == 0x158, "aim point");
static_assert(offsetof(FieldActor, other) == 0x168, "other");
static_assert(offsetof(FieldActor, other_result) == 0x16c, "other result");
static_assert(offsetof(FieldActor, aim_mode) == 0x170, "aim mode");
static_assert(offsetof(FieldActor, other_kind) == 0x1d2, "other kind");
static_assert(offsetof(FieldActor, has_other) == 0x200, "has other");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "animation");
static_assert(offsetof(FieldActor, anim.frame) == 0x2d8, "animation frame");
static_assert(offsetof(FieldActor, head_pitch) == 0x45c, "head");
static_assert(offsetof(FieldActor, held) == 0x5a0, "held");
static_assert(offsetof(FieldActor, unk_62C) == 0x62c, "0x62c");
static_assert(offsetof(FieldActor, unk_68C) == 0x68c, "0x68c");
static_assert(offsetof(FieldActor, flags) == 0x6ec, "flags");
static_assert(offsetof(FieldActor, start_position) == 0x6f4, "start position");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, work) == 0x7d4, "work");
static_assert(offsetof(FieldActor, work.effect.count) == 0x7d8, "work count");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, unk_7F8) == 0x7f8, "0x7f8");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, target) == 0x80c, "target");
static_assert(offsetof(FieldActor, unk_814) == 0x814, "0x814");
static_assert(offsetof(FieldActor, unk_818) == 0x818, "0x818");
static_assert(offsetof(FieldActor, unk_822) == 0x822, "0x822");
static_assert(offsetof(FieldActor, unk_830) == 0x830, "0x830");
static_assert(offsetof(FieldActor, front_tile) == 0x8d0, "front tile");
static_assert(offsetof(FieldActor, tile) == 0x8d8, "tile");
static_assert(offsetof(FieldActor, pending_tile) == 0x8e0, "pending tile");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(offsetof(FieldActor, receiver_unk_1E) == 0x10a, "receiver 0x1e");
static_assert(offsetof(FieldActor, link) == 0x12c, "link");
static_assert(offsetof(FieldActor, unk_234) == 0x234, "0x234");
static_assert(offsetof(FieldActor, anim.speed) == 0x2e0, "animation speed");
static_assert(offsetof(FieldActor, anim.flags) == 0x2e4, "animation flags");
static_assert(offsetof(FieldActor, effect_point) == 0x6e0, "effect point");
static_assert(offsetof(FieldActor, unk_70D) == 0x70d, "0x70d");
static_assert(offsetof(FieldActor, work.s74.move_angle) == 0x7e8, "state 0x74 angle");
static_assert(offsetof(FieldActor, work.s74.effect) == 0x7ec, "state 0x74 effect");
static_assert(offsetof(FieldActor, work.s73.effect) == 0x7dc, "state 0x73 effect");
static_assert(offsetof(FieldActor, work.s71.done) == 0x7d8, "state 0x71 done");
static_assert(offsetof(FieldActor, work.s6d.kind) == 0x7d8, "state 0x6d kind");
static_assert(offsetof(FieldActor, unk_8E8) == 0x8e8, "0x8e8");
static_assert(offsetof(FieldActor, unk_C84) == 0xc84, "0xc84");
static_assert(offsetof(FieldActor, work.s69.yaw) == 0x7d6, "state 0x69 yaw");
static_assert(offsetof(FieldActor, work.s69.tile_x) == 0x7d8, "state 0x69 tile");
static_assert(offsetof(FieldActor, work.s69.then_77) == 0x7e0, "state 0x69 flags");
static_assert(offsetof(FieldActor, work.s68.yaw) == 0x7dc, "state 0x68 yaw");
static_assert(offsetof(FieldActor, work.s68.count) == 0x7de, "state 0x68 count");
static_assert(offsetof(FieldActor, work.s68.then_69) == 0x7e0, "state 0x68 flags");
static_assert(offsetof(FieldActor, work.s67.point) == 0x7d8, "state 0x67 point");
static_assert(offsetof(FieldActor, work.s66.yaw) == 0x7e0, "state 0x66 yaw");
static_assert(offsetof(FieldActor, work.s66.next) == 0x7e3, "state 0x66 next");
static_assert(offsetof(FieldActor, unk_8F8) == 0x8f8, "0x8f8");
static_assert(sizeof(XZArgs) == 0xc, "XZ arguments");
static_assert(sizeof(FieldActorWork) == 0x1c, "work");
static_assert(sizeof(StateRequest) == 0x1c, "request");

/* The held item code of nothing. */
#define ITEM_NONE 0xfff1

/* An object that answers a query about an item in vtable slot 24 (offset 0x60). */
typedef struct GameObject {
    const u32 *vtable;
} GameObject;

typedef int (*ItemQuery)(GameObject *object, u16 *item);
typedef void (*FieldActorSlot23)(FieldActor *actor, void *arg);

/* ---- Data */

/* The session; func_02073908 says whether a player number is the one at this console. */
extern void *data_020ccf94;
/* The town map (func_0204f5e0, func_0204f5a8). */
extern void *data_021c80bc;
extern u8 *data_021c526c;
/* Distances ahead of the actor (20.12) for func_0200fa1c. */
extern const fx32 data_ov003_02236608[];
extern const fx32 data_ov003_0223810c;
extern const fx32 data_ov003_02238124;
extern const fx32 data_ov003_02238128;
extern const fx32 data_ov003_02238130;
/* A flag and a point state 0x81 leaves for other code. */
extern u8 data_ov003_02260540;
extern Vec3 data_ov003_02260558;

/* ---- Functions of the game */

/* What func_02034270 tells of the ground at a point; func_0203423c releases it. */
typedef struct GroundInfo {
    u8 unk_00[0x30];
    int unk_30; /* state 0x56 takes the swing's base as its end where this is 0 */
    int kind;   /* 0x13 makes the splash effects of states 0x73 and 0x75 the other ones */
    u8 unk_38[8];
} GroundInfo;

/* The buttons whose presses push state 0x74 on (autoload_2/input.h). */
#define BUTTON_A 0x0001
#define BUTTON_B 0x0002
#define BUTTON_SELECT 0x0004
#define BUTTON_START 0x0008
#define BUTTON_R 0x0100
#define BUTTON_L 0x0200
#define BUTTON_X 0x0400
#define BUTTON_Y 0x0800

extern PadState data_021fbe40;
extern const s16 FX_SinCosTable_[];
extern u8 data_021c75b8;
/* Distances ahead of the actor (forward, up) for the effects of state 0x71. */
extern const fx32 data_ov003_02238110[];
extern const fx32 data_ov003_02238118[];
/* "obj_etc_player": the receiver's name in state 0x78. */
extern const char data_ov003_02238134[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 VEC_Mag(const Vec3 *v);

/* ---- Helpers */

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* The whole frame the animation is on. QUIRK: only the low 16 bits of the frame number. */
static int anim_frame(const FieldActor *actor)
{
    return (int) (((u32) actor->anim.frame >> 12) & 0xffff);
}

static BOOL is_local_player(const FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player) != 0;
}

/* The map object on a tile: the acre is the tile over 16, the tile in it the remainder. */
static u16 *map_object_at(int x, int z)
{
    return AcreTile_ItemInAcre(data_021c80bc, x >> 4, z >> 4, x & 15, z & 15, 0);
}

static BOOL in_range(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* The map objects of families A, B and C and the codes after them (main/map_item.h), except
 * 0x1b: 0x00-0x1a, 0x1c-0x1d and 0x6e-0xa5. */
static BOOL is_family_object(u16 code)
{
    return in_range(code, 0x00, 0x1a) || in_range(code, 0x1c, 0x1d) || in_range(code, 0x6e, 0xa5);
}

/* The growth lines and the codes at their last stage only (main/map_item.h). */
static BOOL is_growth_object(u16 code)
{
    return in_range(code, 0x26, 0x2a) || in_range(code, 0x2f, 0x5b) || in_range(code, 0x5d, 0x61) ||
           in_range(code, 0x66, 0x6d) || in_range(code, 0xc8, 0xcf);
}

/* The four short lines (main/map_item.h). */
static BOOL is_short_line_object(u16 code)
{
    return in_range(code, 0x2b, 0x2e) || in_range(code, 0xff, 0x102) || in_range(code, 0x62, 0x65) ||
           in_range(code, 0xd0, 0xd3);
}

/* Whether a held item code is one of 0x1376 and 0x1377. */
static BOOL is_item_1376(u16 item)
{
    return item == 0x1376 || item == 0x1377;
}

static const Vec3 ORIGIN = {0, 0, 0};

/* Builds a request for `state` and queues it; whether it was queued.
 * BUG: the bytes of the request nothing sets (the two after `arg`, and the payload past
 * `payload_size`) are whatever the stack held, and the queue copies them into the actor. */
static int request_state(FieldActor *actor, int state, int priority, int arg, const u8 *payload, int payload_size)
{
    StateRequest request;

#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    for (int i = 0; i < payload_size; i++) {
        request.payload[i] = payload[i];
    }
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* ---- Tools and targets */

/* func_ov003_0220c328: an action on what lies at the tool's point, for func_02010004.
 * FieldActor_TryTargetMode2 comes first; failing that, the point (ahead of the actor at
 * 0x0ccd, or aim_point when it is within range 0xc) is tried with mode 0. Whether an action
 * started. Only the first argument after `actor` is read. */
int FieldActor_TryTarget(FieldActor *actor, int tool, ...)
{
    Vec3 point;

    if (FieldActor_TryTargetMode2(actor, &tool)) {
        return 1;
    }
    if (actor->aim_mode == 1) {
        FieldActor_PointAhead(&point, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov003_02238130);
    } else {
        point = actor->aim_point;
        if (!FieldActor_InToolReach(actor, &point, 0xc)) {
            return 0;
        }
    }
    return FieldActor_FindTarget(actor, &point, 0, tool) && FieldActor_ActOnTarget(actor, &point, 0);
}
CLEAN_AS(func_ov003_0220c328, FieldActor_TryTarget)

/* func_ov003_0220c3d0: starts the action of `tool` at `point` (each by queueing its state with
 * priority 6); whether one started. Tools 3, 0 and 10 replace a point at the origin: tool 3
 * with the actor's position, tools 0 and 10 with the tile ahead. Tools 0 and 10 act on the
 * tile ahead when `point` is within 0x2334 and func_0200ff28 finds something there (mode 1);
 * otherwise tool 10 queues its own state and tool 0 does nothing. */
int FieldActor_UseTool(FieldActor *actor, int tool, Vec3 *point)
{
    Vec3 ahead;
    Vec3 tile;

    switch (tool) {
        case 1:
            FieldActor_RequestState59AtAim(actor, 6, -1);
            return 1;
        case 2:
            FieldActor_RequestState46(actor, 6, -1);
            return 1;
        case 3:
            if (Vec_Equal(point, &ORIGIN)) {
                *point = actor->position;
            }
            if (FieldActor_PointsAhead(actor, &ahead, point)) {
                Vec3 copy = ahead;
                FieldActor_RequestState4D(actor, &copy, 6, -1);
            } else {
                FieldActor_RequestState4E(actor, 6, -1);
            }
            return 1;
        case 4:
            FieldActor_RequestState56(actor, 6, -1);
            return 1;
        case 5:
            FieldActor_RequestState63(actor, 6, -1);
            return 1;
        case 6:
            FieldActor_RequestState64(actor, 6, -1);
            return 1;
        case 7:
            FieldActor_RequestState82(actor, 6, -1);
            return 1;
        case 8:
            FieldActor_RequestState80(actor, 6, -1);
            return 1;
        case 9:
            FieldActor_RequestState81(actor, 6, -1);
            return 1;
        case 0:
        case 10:
            if (Vec_Equal(point, &ORIGIN)) {
                FieldActor_TileAhead(&tile, actor);
                *point = tile;
            }
            FieldActor_TileAhead(&tile, actor);
            if (Vec_DistanceXZ(&actor->position, point) < 0x2334 && FieldActor_FindTarget(actor, &tile, 1, 0)) {
                int not_kind_1 = FieldActor_TargetKind(actor) == 1 ? 0 : 1;
                FieldActor_RequestState68(actor, tile.x, tile.z, not_kind_1, 0, 6, -1);
                return 1;
            }
            if (tool == 10) {
                FieldActor_RequestState45(actor, 6, -1);
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_ov003_0220c3d0, FieldActor_UseTool)

/* func_ov003_0220c57c: what the held tool does this frame, if anything; whether an action
 * started. In order:
 *  - with 0x140 set, the tool's action at the origin;
 *  - when aim_point is out of the tool's range: func_02010004 when 0x144 is 1 or 0x148 is set,
 *    then the last check;
 *  - with 0x144 = 1, FieldActor_TryTargetMode2, then for tools 0, 1, 2 and 10 the action at
 *    aim_point (tool 10 as tool 0) while 0x144 is still set; with 0x144 = 2, tool 4's action;
 *  - with aim_mode 2, tool 5 on a map object of families A, B or C at aim_point;
 *  - with 0x148 set, func_02010004;
 *  - with aim_mode 2: tool 1 at the point ahead towards aim_point (aim_point stands in for it
 *    meanwhile), tool 5 at the origin, tool 3 at aim_point if func_02031614 accepts it;
 *  - last, with no tool, 0x140 set and func_020ba310, state 0x72. */
int FieldActor_TryTool(FieldActor *actor)
{
    int tool = FieldActor_HeldTool(actor);
    Vec3 point;

    if (actor->unk_140 != 0) {
        point = ORIGIN;
        if (FieldActor_UseTool(actor, tool, &point)) {
            return 1;
        }
    }

    if (!FieldActor_InToolReach(actor, &actor->aim_point, tool)) {
        if ((actor->unk_144 == 1 || actor->unk_148 != 0) && FieldActor_TryTargetInScene(actor, tool)) {
            return 1;
        }
        goto last;
    }

    switch (actor->unk_144) {
        case 1:
            if (FieldActor_TryTargetMode2(actor, &tool)) {
                return 1;
            }
            if ((tool == 2 || tool == 1 || tool == 10 || tool == 0) && actor->unk_144 != 0) {
                point = actor->aim_point;
                if (FieldActor_UseTool(actor, tool == 10 ? 0 : tool, &point)) {
                    return 1;
                }
            }
            break;
        case 2:
            if (tool == 4) {
                point = ORIGIN;
                if (FieldActor_UseTool(actor, tool, &point)) {
                    return 1;
                }
            }
            break;
        default:
            break;
    }

    if (actor->aim_mode == 2 && tool == 5) {
        int x;
        int z;
        Position_Tile(&x, &z, (const Position *) &actor->aim_point);
        u16 *object = map_object_at(x, z);
        if (object != NULL && is_family_object(*object)) {
            point = ORIGIN;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
        }
    }

    if (actor->unk_148 != 0 && FieldActor_TryTargetInScene(actor, tool)) {
        return 1;
    }
    if (actor->aim_mode != 2) {
        goto last;
    }

    switch (tool) {
        case 1: {
            s16 angle = Math_Atan2(sub32(actor->aim_point.x, actor->start_position.x),
                                   sub32(actor->aim_point.z, actor->start_position.z));
            Vec3 ahead;
            FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &angle, data_ov003_02236608);
            if (!FieldActor_InToolReach(actor, &ahead, tool)) {
                goto last;
            }
            Vec3 saved = actor->aim_point;
            actor->aim_point = ahead;
            point = ORIGIN;
            int started = FieldActor_UseTool(actor, tool, &point);
            actor->aim_point = saved;
            if (started) {
                return 1;
            }
            goto last;
        }
        case 5:
            point = ORIGIN;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
            goto last;
        case 3:
            if (!CollisionQuery_IsWaterAroundPoint(&actor->aim_point)) {
                goto last;
            }
            point = actor->aim_point;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
            goto last;
        default:
            break;
    }

last:
    if (tool == 0 && actor->unk_140 != 0 && Block020ba298_Byte10()) {
        FieldActor_RequestState72(actor, 6, -1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0220c57c, FieldActor_TryTool)

/* func_ov003_0220c934: looks up the object the actor has met (has_other, other_kind,
 * other_id) and records the verdict in other_result: 0 none met, 1 met but not found, 2 found
 * in main's tables (kinds 2 and 3), 3 found among overlay 3's eight (kinds 0x11 and 0x12),
 * 4 a kind 2 or 3 object accepted the held item 0x1376 or 0x1377 (its vtable slot 24 said 1).
 * A found object is kept in `other` unless the held item is 0x1376 or 0x1377. Whether one was
 * met. */
int FieldActor_CheckOther(FieldActor *actor)
{
    actor->other_result = 0;
    if (actor->has_other == 0) {
        return 0;
    }
    actor->other_result = 1;

    int kind = actor->other_kind;
    int id = actor->other_id;
    u16 item;
    FieldActor_RecordHeldItem(&item, actor);

    switch (kind) {
        case 2:
        case 3: {
            GameObject *object = Actors_GetByIndex(kind, id);
            if (object != NULL) {
                if (is_item_1376(item)) {
                    ItemQuery query = (ItemQuery) (uintptr_t) object->vtable[24];
                    if (query(object, &item) == 1) {
                        actor->other_result = 4;
                        break;
                    }
                } else {
                    actor->other = object;
                }
                actor->other_result = 2;
            }
            break;
        }
        case 0x11:
        case 0x12: {
            GameObject *object = (GameObject *) Snowman_Find(id);
            if (object != NULL) {
                if (!is_item_1376(item)) {
                    actor->other = object;
                }
                actor->other_result = 3;
            }
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov003_0220c934, FieldActor_CheckOther)

/* func_ov003_0220ca24: a level from 0 to 7 kept in the player's record that rises by one
 * after 0x4650 frames (five minutes) spent outside from 10:00 to 16:59 between 16 July and
 * 15 September, unless func_020ba4d4 says 3 or more or the held item is in 0x1380-0x13a7; by
 * all appearances the summer tan. The countdown (func_02096274) and the flags
 * (func_0209626c) live outside the actor; nothing happens unless 0x7f8 is set. While flag 0
 * is set, func_0200f86c must return 1 for the update to go on, and the flag is cleared (and
 * flag 4 with it unless func_0200ee0c). On a rise the date goes to func_0200f7ac packed as
 * year (7 bits), month (4 bits) and day (5 bits), and flags 0 and 1 are set, 2 cleared.
 * QUIRK: a level of 255 rises to 0. */
void FieldActor_UpdateSunLevel(FieldActor *actor)
{
    if (actor->unk_7F8 == 0) {
        return;
    }
    BOOL keep_flag_4 = FieldActor_LinkedNotPlayer0(actor) != 0;

    u16 *countdown = SessionPlayers_SunCountdown();
    if (*countdown == 0) {
        *countdown = 1;
    }
    u8 *flags = SessionPlayers_SunFlags();
    void *record = FieldActor_Record(actor);

    DateTime now = {0};
    DateTime_Now(&now);

    if ((*flags & 1) != 0) {
        if (FieldActor_SunDatePassed(actor) != 1) {
            return;
        }
        *flags &= keep_flag_4 ? 0xfe : 0xee;
    }

    BOOL summer = now.month == 8 || (now.month == 7 && now.day >= 16) || (now.month == 9 && now.day <= 15);
    if (!summer) {
        return;
    }
    if (now.hour < 10 || now.hour >= 17) {
        return;
    }
    if (Sky_WeatherNow() >= 3) {
        return;
    }
    u16 item;
    FieldActor_RecordHeldItem(&item, actor);
    if (in_range(item, 0x1380, 0x139f)) {
        return;
    }
    FieldActor_RecordHeldItem(&item, actor);
    if (in_range(item, 0x13a0, 0x13a7)) {
        return;
    }

    *countdown -= 1;
    if (*countdown != 0) {
        return;
    }
    u16 date = (u16) ((now.year & 0x7f) | (now.month & 0xf) << 7 | (now.day & 0x1f) << 11);
    u8 level = (u8) (FieldActor_RecordSunLevel(actor) + 1);
    if (level > 7) {
        level = 7;
    }
    PlayerRecord_SetSunLevel(record, level);
    FieldActor_StoreSunDate(actor, (int) (uintptr_t) record, &date);
    *countdown = 0x4650;
    *flags &= 0xfb;
    *flags |= 3;
    FieldActor_SendSunLevel(actor);
}
CLEAN_AS(func_ov003_0220ca24, FieldActor_UpdateSunLevel)

/* func_ov003_0220cbb4: with a tile pending (flag 0x16), what func_0200fea0 left in 0x818
 * decides: 1 acts on the tile (state 0x73) and drops it, 2 drops it; dropping it
 * clears flags 0x16 and 0x13. */
void FieldActor_FinishPendingTile(FieldActor *actor)
{
    if (!FieldActor_TestFlag(actor, FIELD_ACTOR_FLAG_PENDING_TILE)) {
        return;
    }
    switch (actor->unk_818) {
        case 1: {
            int tile[2] = {actor->pending_tile[0], actor->pending_tile[1]};
            FieldActor_RequestState73(actor, tile, 6, -1);
            FieldActor_ClearFlag(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
            FieldActor_ClearFlag(actor, 0x13);
            break;
        }
        case 2:
            FieldActor_ClearFlag(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
            FieldActor_ClearFlag(actor, 0x13);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0220cbb4, FieldActor_FinishPendingTile)

/* func_ov003_0220cc24: unless flag 11 or 0x16 is set, func_0200ea0c refuses the state or a
 * target is held already, looks for a target on the actor's tile with func_020438dc (mode by
 * tool: 1 -> 2, 2 -> 1, 4 -> 3, 5 -> 4, others 0) and keeps it. A target of kind 0x19 makes the
 * tile pending (func_0200e854, flags 0x16 and 0x13). */
void FieldActor_FindTileTarget(FieldActor *actor)
{
    if (FieldActor_TestFlag(actor, 11)) {
        return;
    }
    if (FieldActor_TestFlag(actor, FIELD_ACTOR_FLAG_PENDING_TILE)) {
        return;
    }
    if (!FieldActor_StateGroup(actor, actor->state)) {
        return;
    }
    if (actor->target != -1) {
        return;
    }

    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) &actor->position);

    int mode;
    switch (FieldActor_HeldTool(actor)) {
        case 1:
            mode = 2;
            break;
        case 2:
            mode = 1;
            break;
        case 4:
            mode = 3;
            break;
        case 5:
            mode = 4;
            break;
        default:
            mode = 0;
            break;
    }

    int tile[2] = {x, z};
    actor->target = TileRequests_AskMarked1566For(actor->player, (const TileRequestTile *) tile, mode);
    if (actor->target == -1) {
        return;
    }
    if (FieldActor_TargetKind(actor) != 0x19) {
        return;
    }
    FieldActor_ClearQueue(actor);
    FieldActor_SetFlag(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
    FieldActor_SetFlag(actor, 0x13);
    actor->pending_tile[0] = x;
    actor->pending_tile[1] = z;
}
CLEAN_AS(func_ov003_0220cc24, FieldActor_FindTileTarget)

/* func_ov003_0220cd08: when 0x98 is above 0x53f, follows the tile under the actor: a tile
 * other than the last one seen goes to func_020448b8. */
void FieldActor_TrackTile(FieldActor *actor)
{
    if (actor->unk_098 <= 0x53f) {
        return;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) &actor->position);
    BOOL same = x == actor->tile[0] && z == actor->tile[1];
    actor->tile[0] = x;
    actor->tile[1] = z;
    if (!same) {
        int tile[2] = {x, z};
        TileEffects_Brush((const TileEffectsTile *) tile);
    }
}
CLEAN_AS(func_ov003_0220cd08, FieldActor_TrackTile)

/* func_ov003_0220cd84: follows the tile 0x10cd ahead of the actor: on reaching a new one that
 * holds a map object of a growth line (or one at its last stage only), tells
 * func_ov003_02224384. */
void FieldActor_TrackFrontTile(FieldActor *actor)
{
    Vec3 ahead;
    int x = 0;
    int z = 0;

    FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov003_02238128);
    Position_Tile(&x, &z, (const Position *) &ahead);
    BOOL same = x == actor->front_tile[0] && z == actor->front_tile[1];
    actor->front_tile[0] = x;
    actor->front_tile[1] = z;
    if (same) {
        return;
    }
    u16 *object = map_object_at(x, z);
    if (object == NULL || !is_growth_object(*object)) {
        return;
    }
    int tile[2] = {x, z};
    GrowthModel_RequestHit(actor->player, (const TileChangesTile *) tile, 1);
}
CLEAN_AS(func_ov003_0220cd84, FieldActor_TrackFrontTile)

/* func_ov003_0220ced4: the point 0x6000 ahead of the actor in the direction of `toward` (the
 * way it faces when `toward` is its own position) goes to `ahead`; whether func_02031614
 * accepts both it and the point 0x5000 ahead. */
int FieldActor_PointsAhead(FieldActor *actor, Vec3 *ahead, const Vec3 *toward)
{
    s16 angle;
    Vec3 point;

    if (Vec_Equal(toward, &actor->position)) {
        angle = actor->yaw;
    } else {
        angle = Math_Atan2(sub32(toward->x, actor->position.x), sub32(toward->z, actor->position.z));
    }
    FieldActor_PointAhead(&point, actor, &actor->position, (const u16 *) &angle, &data_ov003_02238124);
    *ahead = point;
    int far_ok = CollisionQuery_IsWaterAroundPoint(ahead);
    FieldActor_PointAhead(&point, actor, &actor->position, (const u16 *) &angle, &data_ov003_0223810c);
    return far_ok && CollisionQuery_IsWaterAroundPoint(&point);
}
CLEAN_AS(func_ov003_0220ced4, FieldActor_PointsAhead)

/* func_ov003_0220cf68: a verdict 0-9 on the tile of `at` for func_ov003_02212574. With
 * `*check_other`, an object met gives 2 and func_0200fdd0 on the tile (2, 3) may decide
 * (0 -> 7, 1 -> 0, 2 -> 2). Otherwise 0x818 decides: 2 -> 7, 0 -> 0, else 0x814 picks it. */
int FieldActor_ClassifyAt(FieldActor *actor, const Vec3 *at, const u8 *check_other)
{
    int x;
    int z;

    Position_Tile(&x, &z, (const Position *) at);
    if (*check_other) {
        if (FieldActor_CheckOther(actor)) {
            return 2;
        }
        int tile[2] = {x, z};
        switch (FieldActor_FindMapTarget(actor, tile, 2, 3)) {
            case 0:
                return 7;
            case 1:
                return 0;
            case 2:
                return 2;
            default:
                break;
        }
    }
    if (actor->unk_818 == 2) {
        return 7;
    }
    if (actor->unk_818 == 0) {
        return 0;
    }
    switch (actor->unk_814) {
        case 23:
            return 1;
        case 12:
        case 13:
            return 2;
        case 14:
            return 8;
        case 19:
        case 20:
            return 6;
        case 9:
        case 21:
            return 5;
        case 10:
        case 22:
            return 9;
        case 11:
            return 4;
        default:
            return 3;
    }
}
CLEAN_AS(func_ov003_0220cf68, FieldActor_ClassifyAt)

/* func_ov003_0220d040: a verdict 0-6 on the ground ahead of the actor for
 * func_ov003_02216c9c; its tile goes to `tile` when that is not null. With `*check_other`, an
 * object met gives 4. Ground of a surface other than 4 and 6 gives 4 when 0x1000 or higher,
 * else 1; surface 6 holding a map object of a short line gives 1. Then, with `*check_other`,
 * ground below 0x1000 gives 1 and func_0200fdd0 on the tile (1, `*mode`) may decide (0 -> 5,
 * 1 -> 0, 2 -> 4); otherwise 0x818 decides: 1 lets 0x814 pick it, 2 -> 5, others 0.
 * REQUIRES: func_0204f5a8 finds an object on surface 6 (the ROM reads through its result
 * unchecked). */
int FieldActor_ClassifyAhead(FieldActor *actor, const u8 *check_other, const u8 *mode, int *tile)
{
    Vec3 ahead;
    int x;
    int z;
    int surface;

    if (*check_other != 0 && FieldActor_CheckOther(actor)) {
        return 4;
    }
    FieldActor_PointAheadOfSelf(&ahead, actor);
    Position_Tile(&x, &z, (const Position *) &ahead);
    if (tile != NULL) {
        tile[0] = x;
        tile[1] = z;
    }

    fx32 height = CollisionQuery_GroundY(&ahead, &surface, 0x19);
    if (surface != 4 && surface != 6) {
        return height >= 0x1000 ? 4 : 1;
    }
    if (surface == 6 && data_021c80bc != NULL) {
        u16 *object = AcreTile_ItemAt(data_021c80bc, &ahead, 0);
        if (is_short_line_object(*object)) {
            return 1;
        }
    }

    if (*check_other != 0) {
        if (height < 0x1000) {
            return 1;
        }
        int pair[2] = {x, z};
        switch (FieldActor_FindMapTarget(actor, pair, 1, *mode)) {
            case 0:
                return 5;
            case 1:
                return 0;
            case 2:
                return 4;
            default:
                break;
        }
    }

    if (actor->unk_818 == 1) {
        switch (actor->unk_814) {
            case 6:
                return 2;
            case 7:
                return 3;
            case 12:
            case 13:
                return 4;
            case 14:
                return 6;
            default:
                return 1;
        }
    }
    return actor->unk_818 == 2 ? 5 : 0;
}
CLEAN_AS(func_ov003_0220d040, FieldActor_ClassifyAhead)

/* func_ov003_0220d1a8: an action on what lies at the point (ahead of the actor at the first
 * distance of 0x02236608, or aim_point), when it is within range 0xd and func_0200ff28 finds
 * something there for `*tool` (mode 2); whether one started. */
int FieldActor_TryTargetMode2(FieldActor *actor, int *tool)
{
    Vec3 point;

    if (actor->aim_mode == 1) {
        FieldActor_PointAhead(&point, actor, &actor->position, (const u16 *) &actor->yaw, data_ov003_02236608);
    } else {
        point = actor->aim_point;
    }
    return FieldActor_InToolReach(actor, &point, 0xd) && FieldActor_FindTarget(actor, &point, 2, *tool) &&
           FieldActor_ActOnTarget(actor, &point, 0);
}
CLEAN_AS(func_ov003_0220d1a8, FieldActor_TryTargetMode2)

/* func_ov003_0220d268: leaves the current state: when func_02010718 is positive, for state 3
 * (func_0200d1a0) after storing the state's next one; otherwise through func_02010538. */
int FieldActor_ResumeMoving(FieldActor *actor)
{
    if (FieldActor_WalkSpeed(actor) > 0) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return FieldActor_RequestState3(actor, 0, 1, -1);
    }
    return FieldActor_TryAct(actor);
}
CLEAN_AS(func_ov003_0220d268, FieldActor_ResumeMoving)

/* ---- State 0x8f: the head follows a target */

/* func_ov003_0220d2a4: state 0x8f's update. */
void FieldActor_UpdateLook(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FieldActor_FollowReported(actor)) {
        FieldActor_MoveWithCollision(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_TrackLookTarget(actor);
}
CLEAN_AS(func_ov003_0220d2a4, FieldActor_UpdateLook)

/* func_ov003_0220d2d0: while tracking, turns the head towards the player's target
 * (func_ov003_0222a918) from 0x1b33 above the actor: the pitch held within -0x1000..0x1800, the
 * head reset when the target is more than about 60 degrees to the side. Without a target the
 * head is reset and the actor leaves the state (state 5 or 2, by exit_kind). */
void FieldActor_TrackLookTarget(FieldActor *actor)
{
    if (actor->work.look.track == 0) {
        return;
    }
    int player = actor->player;
    if (PlayerFish_IsBusy(player)) {
        Vec3 target = *PlayerFish_PositionOf(player);
        Vec3 head = actor->position;
        head.y = add32(head.y, 0x1b33);

        int yaw = Math_Atan2(sub32(target.x, head.x), sub32(target.z, head.z));
        int distance = Vec_DistanceXZ(&target, &head);
        int pitch = Math_Atan2(sub32(target.y, head.y), distance);
        if (pitch >= 0x1800) {
            pitch = 0x1800;
        } else if (pitch <= -0x1000) {
            pitch = -0x1000;
        }
        yaw = (s16) (yaw - actor->yaw);
        if ((u16) (yaw + 0x2aaa) >= 0x5554) {
            PlayerActorOps_SetLook(0, 0, actor->player);
        } else {
            FieldActor_TurnAngle(&actor->head_pitch, pitch, 0x400, 0x1770000, 0xc0000);
            FieldActor_TurnAngle(&actor->head_yaw, yaw, 0x400, 0x1770000, 0xc0000);
        }
    } else {
        PlayerActorOps_SetLook(0, 0, actor->player);
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        if (actor->work.look.exit_kind != 0) {
            FieldActor_RequestState5(actor, 3, 5, -1);
        } else {
            FieldActor_RequestState2(actor, 3, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_0220d2d0, FieldActor_TrackLookTarget)

/* func_ov003_0220d410: state 0x8f's message handler: asks for state 0x8f again with the saved
 * arguments, priority 6 and `arg`. */
void FieldActor_LookMessage(FieldActor *actor, int arg)
{
    u8 track;
    u8 exit_kind;

    LookArgs_Get(&actor->saved.look, &track, &exit_kind);
    FieldActor_RequestLook(actor, &track, exit_kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220d410, FieldActor_LookMessage)

/* func_ov003_0220d444: entering state 0x8f: the request's two bytes become the state's
 * arguments, and are saved; with exit_kind 0 animation 0 starts. */
void FieldActor_EnterLook(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 track = request->payload[0];
    u8 exit_kind = request->payload[1];

    if (exit_kind == 0) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
    }
    actor->work.look.track = track;
    actor->work.look.exit_kind = exit_kind;
    LookArgs_Set(&actor->saved.look, track, exit_kind);
}
CLEAN_AS(func_ov003_0220d444, FieldActor_EnterLook)

/* func_ov003_0220d484 */
void LookArgs_Get(const LookArgs *args, u8 *track, u8 *exit_kind)
{
    *track = args->track;
    *exit_kind = args->exit_kind;
}
CLEAN_AS(func_ov003_0220d484, LookArgs_Get)

/* func_ov003_0220d490 */
void LookArgs_Set(LookArgs *args, int track, int exit_kind)
{
    args->track = (u8) track;
    args->exit_kind = (u8) exit_kind;
}
CLEAN_AS(func_ov003_0220d490, LookArgs_Set)

/* func_ov003_0220d498: asks for state 0x8f with the two bytes; whether it was queued. */
int FieldActor_RequestLook(FieldActor *actor, const u8 *track, int exit_kind, int priority, s16 arg)
{
    const u8 payload[2] = {*track, (u8) exit_kind};
    return request_state(actor, 0x8f, priority, arg, payload, 2);
}
CLEAN_AS(func_ov003_0220d498, FieldActor_RequestLook)

/* ---- State 0x89 */

/* func_ov003_0220d4dc: state 0x89's update. */
void FieldActor_UpdateState89(FieldActor *actor)
{
    FieldActor_AnimateState89(actor);
    FieldActor_EnterContact(actor);
    FieldActor_FaceState89Target(actor);
}
CLEAN_AS(func_ov003_0220d4dc, FieldActor_UpdateState89)

/* func_ov003_0220d4f8: once the animation is over, animation 0 starts. Before, while 0x704 is
 * 0: the actor turns towards the player's point of func_ov003_0222c1f4 and the pitch to it
 * (never upwards) goes to func_02095518 for player 4; without one (func_ov003_0222c364) the
 * pitch is reset and the actor leaves for state 5. */
void FieldActor_FaceState89Target(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
        return;
    }
    if (actor->animation != 0) {
        return;
    }
    if (!ThrownBottle_IsActive(actor->player)) {
        PlayerActorOps_SetLook(0, 0, 4);
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState5(actor, 3, 5, -1);
        return;
    }

    Vec3 target = *ThrownBottle_PositionOf(actor->player);
    Vec3 here = actor->position;
    int yaw = Math_Atan2(sub32(target.x, here.x), sub32(target.z, here.z));
    int distance = Vec_DistanceXZ(&target, &here);
    int pitch = Math_Atan2(sub32(target.y, here.y), distance);
    if (pitch > 0) {
        pitch = 0;
    }
    PlayerActorOps_SetLook(pitch, 0, 4);
    s16 body = actor->yaw;
    FieldActor_TurnAngleStep(&body, yaw);
    FieldActor_SetYaw(actor, &body);
}
CLEAN_AS(func_ov003_0220d4f8, FieldActor_FaceState89Target)

/* func_ov003_0220d5d8: while 0x704 is 0x8f, frames 6 to 25 of the animation set flag 13, call
 * the actor's vtable slot 23 with 0x824 and grow the values at 0x830 from 0 at frame 6 to 1.0
 * at frame 11 (0x333 a frame); frame 25 clears flag 13 and calls func_ov003_0222c214. */
void FieldActor_AnimateState89(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (actor->animation != 0x8f) {
        return;
    }
    int frame = anim_frame(actor);
    if (frame < 6 || frame > 25) {
        return;
    }
    FieldActor_SetFlag(actor, 13);
    ((FieldActorSlot23) (uintptr_t) actor->vtable[23])(actor, &actor->unk_824);
    actor->unk_822 = 0x1520;
    fx32 value = frame >= 11 ? 0x1000 : (frame - 6) * 0x333;
    actor->unk_830[0] = value;
    actor->unk_830[1] = value;
    actor->unk_830[2] = value;
    if (frame == 25) {
        FieldActor_ClearFlag(actor, 13);
        ThrownBottle_Throw(actor->player);
    }
}
CLEAN_AS(func_ov003_0220d5d8, FieldActor_AnimateState89)

/* func_ov003_0220d674: state 0x89's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State89Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState89(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220d674, FieldActor_State89Message)

/* func_ov003_0220d680: entering state 0x89: animation 0x8f and sound 0x4f. */
void FieldActor_EnterState89(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x8f, 0, 0);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_0220d680, FieldActor_EnterState89)

/* func_ov003_0220d69c: asks for state 0x89; whether it was queued. */
void *FieldActor_RequestState89(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x89, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220d69c, FieldActor_RequestState89)

/* ---- State 0x82: the held item is used up with effect 0x31 */

/* func_ov003_0220d6d4: state 0x82's update. */
void FieldActor_UpdateState82(FieldActor *actor)
{
    FieldActor_AnimateState82(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState82(actor);
}
CLEAN_AS(func_ov003_0220d6d4, FieldActor_UpdateState82)

/* func_ov003_0220d6f4: at the animation's end the actor leaves for state 2; the player at
 * this console may leave from frame 0x18 on (FieldActor_ResumeMoving). */
void FieldActor_EndState82(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
    if (is_local_player(actor) && anim_frame(actor) >= 0x18) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220d6f4, FieldActor_EndState82)

/* func_ov003_0220d760: effect 0x31 at the point 0x68c (through func_0203f7d0) during frames 14
 * to 24, started on the first; on reaching frame 0x18 the player's held item and what the
 * actor holds become nothing. */
void FieldActor_AnimateState82(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    int frame = anim_frame(actor);
    if (frame >= 14 && frame <= 24) {
        Vec3 at = actor->unk_68C;
        Globe_Unbend(&at, &at);
        if (actor->work.effect.effect == -1) {
            actor->work.effect.effect = EffectSystem_StartKind(0x31, &at, &actor->yaw, 0);
        } else {
            EffectSystem_MoveHandle(actor->work.effect.effect, &at, &actor->yaw, 0);
        }
    }
    if (FrameCtrl_Passed(&actor->anim, 0x18)) {
        void *record = PlayerRecords_OfPlayer(actor->player);
        u16 none = ITEM_NONE;
        PlayerRecord_SetHeldItem(record, &none);
        u16 held_none = ITEM_NONE;
        HeldItem_Take((HeldItemObject *) actor->held, &held_none, 0);
    }
}
CLEAN_AS(func_ov003_0220d760, FieldActor_AnimateState82)

/* func_ov003_0220d820: for the player at this console the held item goes to func_0200f1a4;
 * the effect ends. */
void FieldActor_FinishState82(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = PlayerRecord_HeldItem(PlayerRecords_OfPlayer(actor->player));
        if (item != NULL) {
            FieldActor_SendItem(actor, 3, *item);
        }
    }
    if (actor->work.effect.effect != -1) {
        EffectSystem_EndHandle(actor->work.effect.effect);
    }
}
CLEAN_AS(func_ov003_0220d820, FieldActor_FinishState82)

/* func_ov003_0220d874: state 0x82's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State82Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState82(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220d874, FieldActor_State82Message)

/* func_ov003_0220d880: entering state 0x82: no effect yet, animation 125, the held object in
 * pose 42, sound 0x85d. */
void FieldActor_EnterState82(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.effect.effect = -1;
    FieldActor_PlayAnimationOnce(actor, 125, 3, 0);
    HeldItem_Act(actor->held, 42, 0, 0);
    FieldActor_PlaySound(actor, 0x85d);
}
CLEAN_AS(func_ov003_0220d880, FieldActor_EnterState82)

/* func_ov003_0220d8bc: asks for state 0x82; whether it was queued. */
void *FieldActor_RequestState82(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x82, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220d8bc, FieldActor_RequestState82)

/* ---- State 0x81: an effect by the held item 0x137f or another */

/* func_ov003_0220d8f4: state 0x81's update. */
void FieldActor_UpdateState81(FieldActor *actor)
{
    FieldActor_AnimateState81(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState81(actor);
}
CLEAN_AS(func_ov003_0220d8f4, FieldActor_UpdateState81)

/* func_ov003_0220d914: each frame the held object's animation is over, `count` and then
 * `count2` run down; when both are 0 the player's held item and what the actor holds become
 * nothing and the actor leaves for state 2. */
void FieldActor_EndState81(FieldActor *actor)
{
    if (!FrameCtrl_IsDone((const FrameCtrl *) (HeldItem_Model(actor->held) + 0x9c))) {
        return;
    }
    u8 *count = &actor->work.effect.count;
    if (*count != 0) {
        (*count)--;
    }
    if (*count != 0) {
        return;
    }
    u8 *count2 = &actor->work.effect.count2;
    if (*count2 != 0) {
        (*count2)--;
    }
    if (*count2 != 0) {
        return;
    }
    void *record = PlayerRecords_OfPlayer(actor->player);
    u16 none = ITEM_NONE;
    PlayerRecord_SetHeldItem(record, &none);
    u16 held_none = ITEM_NONE;
    HeldItem_Take((HeldItemObject *) actor->held, &held_none, 0);
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, 9, 1, -1);
}
CLEAN_AS(func_ov003_0220d914, FieldActor_EndState81)

/* func_ov003_0220d9b8: the effect follows the point 0x62c (through func_0203f7d0). Before it
 * exists, `count` counts frames: the 10th plays sound 0x85a (held item 0x137f) or 0x859 and
 * leaves the point ahead of the actor in 0x02260558 with 0x02260540 set; from the 10th on, the
 * effect is started (0x35 for item 0x137f, else 0x36). QUIRK: `count` is a byte; past 255 it
 * wraps to 0 and the wait starts again. */
void FieldActor_AnimateState81(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    Vec3 at = actor->unk_62C;
    Globe_Unbend(&at, &at);

    if (actor->work.effect.effect != -1) {
        EffectSystem_MoveHandle(actor->work.effect.effect, &at, &actor->yaw, 0);
        return;
    }
    u8 *count = &actor->work.effect.count;
    (*count)++;
    if (*count <= 9) {
        return;
    }
    u16 item;
    if (*count == 10) {
        FieldActor_RecordHeldItem(&item, actor);
        FieldActor_PlaySound(actor, item == 0x137f ? 0x85a : 0x859);
        Vec3 ahead;
        FieldActor_PointAheadOfSelf(&ahead, actor);
        data_ov003_02260540 = 1;
        data_ov003_02260558 = ahead;
    }
    FieldActor_RecordHeldItem(&item, actor);
    actor->work.effect.effect = EffectSystem_StartKind(item == 0x137f ? 0x35 : 0x36, &at, &actor->yaw, 0);
}
CLEAN_AS(func_ov003_0220d9b8, FieldActor_AnimateState81)

/* func_ov003_0220daac: for the player at this console the held item goes to func_0200f1a4,
 * then func_0203b144 and func_02036448 run; the effect ends; the point ahead of the actor goes
 * to 0x02260558 with 0x02260540 cleared. */
void FieldActor_FinishState81(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = PlayerRecord_HeldItem(PlayerRecords_OfPlayer(actor->player));
        if (item != NULL) {
            FieldActor_SendItem(actor, 3, *item);
        }
        CameraControl_ResetMode();
        MusicVolume_EndSlot4((MusicVolume *) (data_021c526c + 0x1c4));
    }
    if (actor->work.effect.effect != -1) {
        EffectSystem_EndHandle(actor->work.effect.effect);
    }
    Vec3 ahead;
    FieldActor_PointAheadOfSelf(&ahead, actor);
    data_ov003_02260540 = 0;
    data_ov003_02260558 = ahead;
}
CLEAN_AS(func_ov003_0220daac, FieldActor_FinishState81)

/* func_ov003_0220db40: state 0x81's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State81Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState81(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220db40, FieldActor_State81Message)

/* func_ov003_0220db4c: entering state 0x81: no effect yet, `count` from 0, `count2` from 20,
 * animation 0x7c, the held object in pose 0x28; for the player at this console func_0203ae98
 * and func_02036450 run. */
void FieldActor_EnterState81(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.effect.effect = -1;
    actor->work.effect.count = 0;
    actor->work.effect.count2 = 20;
    FieldActor_PlayAnimationLoop(actor, 0x7c, 9, 0);
    HeldItem_Act(actor->held, 0x28, 0, 1);
    if (is_local_player(actor)) {
        CameraControl_SetMode4();
        MusicVolume_BeginSlot4((MusicVolume *) (data_021c526c + 0x1c4));
    }
}
CLEAN_AS(func_ov003_0220db4c, FieldActor_EnterState81)

/* func_ov003_0220dbb4: asks for state 0x81; whether it was queued. */
int FieldActor_RequestState81(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x81, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220dbb4, FieldActor_RequestState81)

/* ---- State 0x80: the held item is used up with effect 0x24 */

/* func_ov003_0220dbec: state 0x80's update. */
void FieldActor_UpdateState80(FieldActor *actor)
{
    FieldActor_AnimateState80(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState80(actor);
}
CLEAN_AS(func_ov003_0220dbec, FieldActor_UpdateState80)

/* func_ov003_0220dc0c: at the animation's end the actor moves on. The player at this console
 * who has the item 0x137d (func_02099e9c finds its slot) uses it instead: flag 0 is cleared,
 * the slot goes to func_0209a050 and FieldActor_RequestState3D starts the next action. */
void FieldActor_EndState80(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    u16 item = 0x137d;
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (is_local_player(actor)) {
        int slot = CurrentPockets_FindItem(&item);
        if (slot != -1) {
            FieldActor_ClearFlag(actor, 0);
            PlayerActorOps_SetHeldModel(0x15, actor->player);
            CurrentPockets_Empty(slot);
            FieldActor_RequestState3D(actor, 2, 2, 0, 0, 0, 6, -1);
            return;
        }
    }
    FieldActor_RequestState2(actor, 3, 1, -1);
}
CLEAN_AS(func_ov003_0220dc0c, FieldActor_EndState80)

/* func_ov003_0220dcb0: on reaching frame 13 the player's held item and what the actor holds
 * become nothing, sound 0x850 plays, effect 0x24 starts at the point 0x68c (through
 * func_0203f7d0) and flag 9 is set. */
void FieldActor_AnimateState80(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_Passed(&actor->anim, 13)) {
        return;
    }
    void *record = PlayerRecords_OfPlayer(actor->player);
    u16 none = ITEM_NONE;
    PlayerRecord_SetHeldItem(record, &none);
    u16 held_none = ITEM_NONE;
    HeldItem_Take((HeldItemObject *) actor->held, &held_none, 0);
    FieldActor_PlaySound(actor, 0x850);
    Vec3 at = actor->unk_68C;
    Globe_Unbend(&at, &at);
    EffectSystem_StartKind(0x24, &at, &actor->yaw, 0);
    FieldActor_SetFlag(actor, 9);
}
CLEAN_AS(func_ov003_0220dcb0, FieldActor_AnimateState80)

/* func_ov003_0220dd50: for the player at this console the held item goes to func_0200f1a4. */
void FieldActor_FinishState80(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = PlayerRecord_HeldItem(PlayerRecords_OfPlayer(actor->player));
        if (item != NULL) {
            FieldActor_SendItem(actor, 3, *item);
        }
    }
}
CLEAN_AS(func_ov003_0220dd50, FieldActor_FinishState80)

/* func_ov003_0220dd90: state 0x80's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State80Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState80(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220dd90, FieldActor_State80Message)

/* func_ov003_0220dd9c: entering state 0x80: animation 0x7b. */
void FieldActor_EnterState80(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x7b, 3, 0);
}
CLEAN_AS(func_ov003_0220dd9c, FieldActor_EnterState80)

/* func_ov003_0220ddb0: asks for state 0x80; whether it was queued. */
int FieldActor_RequestState80(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x80, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220ddb0, FieldActor_RequestState80)

/* ---- State 0x78: five animations in a row, then a message under the name "obj_etc_player" */

/* func_ov003_0220dde8: state 0x78's update. */
void FieldActor_UpdateState78(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState78(actor);
}
CLEAN_AS(func_ov003_0220dde8, FieldActor_UpdateState78)

/* func_ov003_0220de04: animations 0x71 to 0x75 follow each other as each ends; during 0x72
 * func_0200faa8 runs (0x3ae), and the start of 0x74 plays sound 0x817 and, when the player's
 * record exists (func_020984e8), marks it (func_02099740, flag 0x19 once flag 0x17 is set) and
 * writes its value plus 0x10 at 0x70d. During 0x75 the actor turns to yaw 0 (func_0200faf0,
 * 0x59a), which on arrival runs func_02035624 and func_020356c4, and `step` goes:
 *   0: the receiver at 0xec is registered (SceneObjectBase_TakeReceiver) as "obj_etc_player",
 *      flag 0x11 set, its byte 0x1e set to 20, the link's request raised and func_0203ae98 run;
 *      then as 1;
 *   1: once the link reports itself open, 2;
 *   2: once it is closed, the receiver is released (SceneObjectBase_ReleaseReceiver), flags 0x11
 *      and 7 cleared, the actor moves on and func_0203e19c, func_0203b144, func_02035638 and
 *      func_02035684 run.
 * REQUIRES: the link is set when `step` is 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState78(FieldActor *actor)
{
    switch (actor->animation) {
        case 0x71:
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlayAnimationOnce(actor, 0x72, 0, 0);
            }
            break;
        case 0x72:
            FieldActor_TurnToHalfTurn(actor, 0x3ae);
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlayAnimationOnce(actor, 0x73, 0, 0);
            }
            break;
        case 0x73:
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlaySound(actor, 0x817);
                FieldActor_PlayAnimationOnce(actor, 0x74, 0, 0);
                void *record = PlayerRecords_Current();
                if (record != NULL) {
                    PlayerRecord_SetFlag0(record, 1);
                    FaceTexture_Load(actor->unk_70D, (int) (PlayerRecord_Face(record) + 0x10));
                    if (PlayerRecord_TestFlag(record, 0x17)) {
                        PlayerRecord_SetFlag(record, 0x19);
                    }
                }
            }
            break;
        case 0x74:
            if (FrameCtrl_IsDone(&actor->anim)) {
                FieldActor_PlayAnimationOnce(actor, 0x75, 0, 0);
            }
            break;
        case 0x75: {
            s16 yaw_before = actor->yaw;
            FieldActor_TurnToZero(actor, 0x59a);
            if (yaw_before != 0 && actor->yaw == 0) {
                Music_DropPriority(0x19);
                Music_Add(0xd, 0x40, 0x7f, 1);
            }
            switch (actor->work.step) {
                case 0:
                    actor->work.step = 1;
                    SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
                    FieldActor_SetFlag(actor, 0x11);
                    MessageReceiver_SetName((MessageReceiver *) actor->receiver, data_ov003_02238134);
                    actor->receiver_unk_1E = 20;
                    actor->link->requested = 1;
                    CameraControl_SetMode4();
                    /* fall through */
                case 1:
                    if (actor->link != NULL && actor->link->open != 0) {
                        actor->work.step = 2;
                    }
                    break;
                case 2:
                    if (actor->link != NULL && actor->link->open == 0) {
                        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
                        FieldActor_ClearFlag(actor, 0x11);
                        EventQueue_FinishKind9();
                        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                        FieldActor_RequestState2(actor, 3, 1, -1);
                        FieldActor_ClearFlag(actor, 7);
                        CameraControl_ResetMode();
                        Music_DropMusic(0x40);
                        Music_AddValue(0xc, 0xf, 5);
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0220de04, FieldActor_RunState78)

/* func_ov003_0220e004: state 0x78's message handler: messages are ignored. */
void FieldActor_State78Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220e004, FieldActor_State78Message)

/* func_ov003_0220e008: entering state 0x78: animation 0x71, `step` 0, the held object in pose
 * 0x13 with tool 3, flag 0x1a cleared, func_02035638 and func_02035684. */
void FieldActor_EnterState78(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x71, 3, 0);
    actor->work.step = 0;
    if (FieldActor_HeldTool(actor) == 3) {
        HeldItem_Act(actor->held, 0x13, 3, 0);
    }
    FieldActor_ClearFlag(actor, 0x1a);
    Music_DropMusic(0x3f);
    Music_AddValue(0x19, 0xf, 0);
}
CLEAN_AS(func_ov003_0220e008, FieldActor_EnterState78)

/* func_ov003_0220e05c: asks for state 0x78, setting flag 7 when it is queued; whether it was.
 * BUG: as in request_state, the bytes of the request nothing sets are the stack's. */
int FieldActor_RequestState78(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, 0x78, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request) != 0;
    if (queued) {
        FieldActor_SetFlag(actor, 7);
    }
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov003_0220e05c, FieldActor_RequestState78)

/* ---- State 0x75: the end of state 0x74, with a splash */

/* func_ov003_0220e0a8: state 0x75's update. */
void FieldActor_UpdateState75(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState75(actor);
}
CLEAN_AS(func_ov003_0220e0a8, FieldActor_UpdateState75)

/* func_ov003_0220e0c4: at the animation's end the actor moves on (func_0200d4e8 with 3, or 9
 * holding tool 4). */
void FieldActor_EndState75(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, FieldActor_HeldTool(actor) == 4 ? 9 : 3, 1, -1);
}
CLEAN_AS(func_ov003_0220e0c4, FieldActor_EndState75)

/* func_ov003_0220e11c: state 0x75's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State75Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState75(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220e11c, FieldActor_State75Message)

/* func_ov003_0220e128: entering state 0x75: animation 0x94 with tools 3, 4 and 10 (the held
 * object in pose 0x12 with tool 4), else 0x93; effect 0x91 at the actor (0x90 unless the
 * ground there is of kind 0x13), flag 9, func_ov003_02220b44 with the position, sound 0x7e9. */
void FieldActor_EnterState75(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    int tool = FieldActor_HeldTool(actor);
    if (tool == 10 || tool == 3 || tool == 4) {
        FieldActor_PlayAnimationOnce(actor, 0x94, 3, 0);
        if (FieldActor_HeldTool(actor) == 4) {
            HeldItem_Act(actor->held, 0x12, 3, 1);
        }
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x93, 3, 0);
    }

    Vec3 at = actor->position;
    GroundInfo ground;
    CollisionGround_Init((CollisionGround *) &ground, &at, 0, 0);
    EffectSystem_StartOneShotSetNumberCopy(ground.kind == 0x13 ? 0x91 : 0x90, &at, 0, 0);
    FieldActor_SetFlag(actor, 9);
    Vec3 position = actor->position;
    TileEvent_StartKindE(actor->player, &position);
    FieldActor_PlaySound(actor, 0x7e9);
    CollisionGround_Destroy((CollisionGround *) &ground);
}
CLEAN_AS(func_ov003_0220e128, FieldActor_EnterState75)

/* func_ov003_0220e1f0: asks for state 0x75; whether it was queued. */
void *FieldActor_RequestState75(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x75, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220e1f0, FieldActor_RequestState75)

/* ---- State 0x74: the pad and the movement push a progress on to state 0x75 */

/* The effect at effect_point: started (kind `kind`) when there is none, else moved there. */
static void follow_effect(FieldActor *actor, int *effect, int kind)
{
    if (*effect == -1) {
        *effect = EffectSystem_StartKind(kind, &actor->effect_point, NULL, 0);
    } else {
        EffectSystem_MoveHandle(*effect, &actor->effect_point, NULL, 0);
    }
}

/* A velocity of `speed` in the direction `angle`, on the ground plane. */
static void velocity(Vec3 *out, fx32 speed, u16 angle)
{
    out->y = 0;
    out->x = FX_MulFunc(FX_SinCosTable_[(angle >> 4) * 2], speed);
    out->z = FX_MulFunc(FX_SinCosTable_[(angle >> 4) * 2 + 1], speed);
}

/* An arithmetic shift right by 12 (whole units of a 20.12 value). */
static int whole(fx32 value)
{
    return value < 0 ? ~(~value >> 12) : value >> 12;
}

/* func_ov003_0220e228: state 0x74's update. */
void FieldActor_UpdateState74(FieldActor *actor)
{
    FieldActor_AnimateState74(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState74(actor);
}
CLEAN_AS(func_ov003_0220e228, FieldActor_UpdateState74)

/* func_ov003_0220e244: for the player at this console, each frame's push is the change of the
 * actor's velocity since the frame before (from a length of 0x59a on, scaled so that 0x59a is
 * 25.0) plus 20.0 for each of A, B, X, Y, L, R, START and SELECT pressed, or 2.0 when it is 0.
 * It adds to `progress` (never below 0) and its whole part goes to `effort`; when the actor
 * moves or a button was pressed sound 0x7ef plays. min_anim_speed becomes 0.5 plus
 * 1.75 * 0.65 * progress / 400. Flag 11 or a progress of 400.0 asks for state 0x75. */
void FieldActor_RunState74(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        return;
    }
    State74Work *work = &actor->work.s74;

    Vec3 before;
    velocity(&before, work->move_speed, work->move_angle);
    fx32 speed = (fx32) FieldActor_Push(actor);
    u16 angle = (u16) FieldActor_PushAngle(actor);
    Vec3 now;
    velocity(&now, speed, angle);
    work->move_speed = speed;
    work->move_angle = angle;

    Vec3 change;
    Vec_Subtract(&change, &before, &now);
    fx32 push = 0;
    if (VEC_Mag(&change) >= 0x59a) {
        push = FX_Div(FX_MulFunc(VEC_Mag(&change), 0x6400), 0x59a);
    }

    static const u16 buttons[] = {BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_L, BUTTON_R, BUTTON_START, BUTTON_SELECT};
    int bonus = 0;
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        if (data_021fbe40.pressed & buttons[i]) {
            bonus += 20;
        }
    }
    push = add32(push, bonus << 12);
    if (push == 0) {
        push = 0x2000;
    }

    work->progress = add32(work->progress, push);
    work->effort = whole(push);
    if (work->progress < 0) {
        work->progress = 0;
    }
    /* The ROM tests the push for 0 here again; it cannot be by now. */
    if (speed != 0 || bonus != 0) {
        FieldActor_PlaySound(actor, 0x7ef);
    }
    work->min_anim_speed = add32(FX_Div(FX_MulFunc(FX_MulFunc(0x1c00, work->progress), 0xa66), 0x190000), 0x800);

    if (FieldActor_TestFlag(actor, 11) || work->progress >= 0x190000) {
        FieldActor_RequestState75(actor, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220e244, FieldActor_RunState74)

/* func_ov003_0220e424: the animation speeds up by 1.2 a frame while `effort` is 10 or more,
 * else slows by 0.3, kept within min_anim_speed..2.25 (the held object follows with tool 4);
 * effect 0x4c follows effect_point and func_0200f2a0 runs with the position. */
void FieldActor_AnimateState74(FieldActor *actor)
{
    State74Work *work = &actor->work.s74;

    work->anim_speed = add32(work->anim_speed, work->effort >= 10 ? 0x1333 : -0x4cd);
    if (work->anim_speed > 0x2400) {
        work->anim_speed = 0x2400;
    } else if (work->anim_speed < work->min_anim_speed) {
        work->anim_speed = work->min_anim_speed;
    }
    actor->anim.speed = work->anim_speed;
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_SetAnimSpeed(actor->held, work->anim_speed);
    }
    FieldActor_UpdateBody(actor);
    follow_effect(actor, &work->effect, 0x4c);
    FieldActor_PlaySoundAt(actor, 0x8a, &actor->position);
}
CLEAN_AS(func_ov003_0220e424, FieldActor_AnimateState74)

/* func_ov003_0220e4d0: leaving state 0x74 for `next`: the effect ends; unless for state 0x75,
 * func_ov003_02220b44 gets the position. */
void FieldActor_ExitState74(FieldActor *actor, int next)
{
    if (actor->work.s74.effect != -1) {
        EffectSystem_EndHandle(actor->work.s74.effect);
    }
    if (next == 0x75) {
        return;
    }
    Vec3 position = actor->position;
    TileEvent_StartKindE(actor->player, &position);
}
CLEAN_AS(func_ov003_0220e4d0, FieldActor_ExitState74)

/* func_ov003_0220e518: state 0x74's message handler: in state 0x73 nothing happens, in state
 * 0x74 `arg` is kept at 0xc84, else state 0x74 is asked for (no effect, priority 6, `arg`). */
void FieldActor_State74Message(FieldActor *actor, int arg)
{
    switch (actor->state) {
        case 0x73:
            break;
        case 0x74:
            actor->unk_C84 = (s16) arg;
            break;
        default:
            FieldActor_RequestState74(actor, -1, 6, arg);
            break;
    }
}
CLEAN_AS(func_ov003_0220e518, FieldActor_State74Message)

/* func_ov003_0220e548: entering state 0x74: animation 0x92 at speed 0.5, the work cleared to
 * the actor's movement now, the request's effect kept, flag 9 cleared; with tool 4 the held
 * object in pose 0x11 at speed 0.5. */
void FieldActor_EnterState74(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    State74Work *work = &actor->work.s74;
    int effect;
    memcpy(&effect, request->payload, sizeof(effect));

    FieldActor_PlayAnimationLoop(actor, 0x92, 3, 0);
    actor->anim.speed = 0x800;
    work->anim_speed = 0x800;
    work->min_anim_speed = 0x800;
    work->effort = 0;
    work->progress = 0;
    work->move_speed = (fx32) FieldActor_Push(actor);
    work->move_angle = (u16) FieldActor_PushAngle(actor);
    work->effect = effect;
    FieldActor_ClearFlag(actor, 9);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 0x11, 3, 0);
        HeldItem_SetAnimSpeed(actor->held, 0x800);
    }
}
CLEAN_AS(func_ov003_0220e548, FieldActor_EnterState74)

/* func_ov003_0220e5c4: asks for state 0x74 carrying an effect handle; whether it was queued. */
int FieldActor_RequestState74(FieldActor *actor, int effect, int priority, int arg)
{
    u8 payload[sizeof(effect)];
    memcpy(payload, &effect, sizeof(effect));
    return request_state(actor, 0x74, priority, arg, payload, (int) sizeof(payload));
}
CLEAN_AS(func_ov003_0220e5c4, FieldActor_RequestState74)

/* ---- State 0x73: the actor steps onto a tile and starts state 0x74 there */

/* func_ov003_0220e600: state 0x73's update. */
void FieldActor_UpdateState73(FieldActor *actor)
{
    FieldActor_AnimateState73(actor);
    FieldActor_RunState73(actor);
}
CLEAN_AS(func_ov003_0220e600, FieldActor_UpdateState73)

/* func_ov003_0220e614: during animation 0x90 the actor moves to the tile's point
 * (func_0200fbc4), and nothing else happens until it is there; then the animation is made to
 * stop at its end. At the end of animation 0x91, state 0x74 is asked for with the effect and
 * flag 9 is set; at the end of the other, animation 0x91 starts with effect 0x8f at the
 * actor (0x8e unless the ground is of kind 0x13), sound 0x7e8, flag 9, func_ov003_02221228
 * with the position, flag 0x12 cleared and, with tool 4, the held object in pose 0x10. */
void FieldActor_RunState73(FieldActor *actor)
{
    if (actor->animation == 0x90) {
        fx32 x = actor->work.s73.x;
        fx32 z = actor->work.s73.z;
        FieldActor_MoveToPose(actor, x, z, actor->yaw);
        if (actor->position.x != x || actor->position.z != z) {
            return;
        }
        actor->anim.flags = FRAME_CTRL_ONCE;
    }
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x91) {
        FieldActor_RequestState74(actor, actor->work.s73.effect, 6, -1);
        FieldActor_SetFlag(actor, 9);
        return;
    }

    FieldActor_PlayAnimationOnce(actor, 0x91, 3, 0);
    Vec3 at = actor->position;
    GroundInfo ground;
    CollisionGround_Init((CollisionGround *) &ground, &at, 0, 0);
    EffectSystem_StartOneShotSetNumberCopy(ground.kind == 0x13 ? 0x8f : 0x8e, &at, 0, 0);
    FieldActor_PlaySound(actor, 0x7e8);
    FieldActor_SetFlag(actor, 9);
    Vec3 copy = at;
    TileEvent_StartUnitKind2(actor->player, &copy);
    FieldActor_ClearFlag(actor, 0x12);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 0x10, 3, 1);
    }
    CollisionGround_Destroy((CollisionGround *) &ground);
}
CLEAN_AS(func_ov003_0220e614, FieldActor_RunState73)

/* func_ov003_0220e738: effect 0x4c follows effect_point and func_0200f2a0 runs with the
 * position. */
void FieldActor_AnimateState73(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    follow_effect(actor, &actor->work.s73.effect, 0x4c);
    FieldActor_PlaySoundAt(actor, 0x8a, &actor->position);
}
CLEAN_AS(func_ov003_0220e738, FieldActor_AnimateState73)

/* func_ov003_0220e788: leaving state 0x73 for `next`: the actor is put on the tile's point.
 * With flag 0x12 set it is cleared, after func_ov003_02221228 with the position when `next`
 * is 0x74 or 0x75; for other states func_ov003_02220b44 gets the position. The effect ends
 * unless state 0x74 takes it over. */
void FieldActor_ExitState73(FieldActor *actor, int next)
{
    actor->position.x = actor->work.s73.x;
    actor->position.z = actor->work.s73.z;
    BOOL continues = next == 0x74 || next == 0x75;

    if (FieldActor_TestFlag(actor, 0x12)) {
        if (continues) {
            Vec3 position = actor->position;
            TileEvent_StartUnitKind2(actor->player, &position);
        }
        FieldActor_ClearFlag(actor, 0x12);
    }
    if (!continues) {
        Vec3 position = actor->position;
        TileEvent_StartKindE(actor->player, &position);
    }
    if (next != 0x74 && actor->work.s73.effect != -1) {
        EffectSystem_EndHandle(actor->work.s73.effect);
    }
}
CLEAN_AS(func_ov003_0220e788, FieldActor_ExitState73)

/* func_ov003_0220e828: state 0x73's message handler: asks for it again with the saved tile,
 * priority 6 and `arg`. */
void FieldActor_State73Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;

    TileArgs_Get(&actor->saved.tile, &x, &z);
    int tile[2] = {x, z};
    FieldActor_RequestState73(actor, tile, 6, arg);
}
CLEAN_AS(func_ov003_0220e828, FieldActor_State73Message)

/* func_ov003_0220e860: entering state 0x73: the request's tile gives the point to reach, no
 * effect yet, animation 0x90 (the held object in pose 0xf with tool 4), the tile is saved and
 * sound 0x7ee plays. */
void FieldActor_EnterState73(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 x = request->payload[0];
    u8 z = request->payload[1];
    Vec3 point;

    AcreTile_TileCentre(&point, x, z);
    actor->work.s73.x = point.x;
    actor->work.s73.z = point.z;
    actor->work.s73.effect = -1;
    FieldActor_PlayAnimationLoop(actor, 0x90, 3, 0);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 0xf, 3, 0);
    }
    TileArgs_Set(&actor->saved.tile, x, z);
    FieldActor_PlaySound(actor, 0x7ee);
}
CLEAN_AS(func_ov003_0220e860, FieldActor_EnterState73)

/* func_ov003_0220e8e0 */
void TileArgs_Get(const TileArgs *args, u8 *x, u8 *z)
{
    *x = args->x;
    *z = args->z;
}
CLEAN_AS(func_ov003_0220e8e0, TileArgs_Get)

/* func_ov003_0220e8ec */
void TileArgs_Set(TileArgs *args, int x, int z)
{
    args->x = (u8) x;
    args->z = (u8) z;
}
CLEAN_AS(func_ov003_0220e8ec, TileArgs_Set)

/* func_ov003_0220e8f4: asks for state 0x73 for a tile (its low bytes); whether it was
 * queued. */
int FieldActor_RequestState73(FieldActor *actor, const int *tile, int priority, int arg)
{
    const u8 payload[2] = {(u8) tile[0], (u8) tile[1]};
    return request_state(actor, 0x73, priority, arg, payload, 2);
}
CLEAN_AS(func_ov003_0220e8f4, FieldActor_RequestState73)

/* ---- State 0x72 */

/* func_ov003_0220e938: state 0x72's update. */
void FieldActor_UpdateState72(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_SlowDown(actor);
    FieldActor_EndState72(actor);
}
CLEAN_AS(func_ov003_0220e938, FieldActor_UpdateState72)

/* func_ov003_0220e960: the actor turns to yaw 0 (func_0200faf0, 0x59a); at the animation's end
 * it moves on, and the player at this console may leave from frame 0x1a on
 * (FieldActor_ResumeMoving). */
void FieldActor_EndState72(FieldActor *actor)
{
    FieldActor_TurnToZero(actor, 0x59a);
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
    if (is_local_player(actor) && anim_frame(actor) >= 0x1a) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220e960, FieldActor_EndState72)

/* func_ov003_0220e9d8: the word at 0x98, while not 0, comes down by 0x171 a frame to 0
 * (func_0201107c stores it). */
void FieldActor_SlowDown(FieldActor *actor)
{
    if (actor->unk_098 != 0) {
        int value = FieldActor_StepDown(actor->unk_098, 0, 0x171);
        FieldActor_SetSpeed(actor, &value);
    }
}
CLEAN_AS(func_ov003_0220e9d8, FieldActor_SlowDown)

/* func_ov003_0220ea04: state 0x72's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State72Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState72(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220ea04, FieldActor_State72Message)

/* func_ov003_0220ea10: entering state 0x72: animation 0x9c; for the player at this console
 * func_020ba2ec runs. */
void FieldActor_EnterState72(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x9c, 3, 0);
    if (is_local_player(actor)) {
        Block020ba298_SetPlayerFlag32();
    }
}
CLEAN_AS(func_ov003_0220ea10, FieldActor_EnterState72)

/* func_ov003_0220ea40: asks for state 0x72; whether it was queued. */
void *FieldActor_RequestState72(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x72, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220ea40, FieldActor_RequestState72)

/* ---- State 0x71: two animations by the tool held, with effects */

/* func_ov003_0220ea78: state 0x71's update. */
void FieldActor_UpdateState71(FieldActor *actor)
{
    FieldActor_RunState71(actor);
    FieldActor_AnimateState71(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState71(actor);
}
CLEAN_AS(func_ov003_0220ea78, FieldActor_UpdateState71)

/* func_ov003_0220eaa0: until `done`, the word at 0x98 comes down by 0x7b a frame to 0; once it
 * is 0 and the first animation is over, the second starts by the tool: 0x8e for tools 4 (the
 * held object in pose 8), 3 (pose 0x1e) and 10, else 0x8c. For the player at this console the
 * record's flag 0x1a is then set once flag 0x17 is. */
void FieldActor_RunState71(FieldActor *actor)
{
    if (actor->work.s71.done) {
        return;
    }
    int value = FieldActor_StepDown(actor->unk_098, 0, 0x7b);
    FieldActor_SetSpeed(actor, &value);
    if (actor->unk_098 != 0) {
        return;
    }
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }

    switch (actor->work.s71.tool) {
        case 4:
            HeldItem_Act(actor->held, 8, 3, 0);
            FieldActor_PlayAnimationOnce(actor, 0x8e, 3, 0);
            break;
        case 3:
            HeldItem_Act(actor->held, 0x1e, 3, 0);
            FieldActor_PlayAnimationOnce(actor, 0x8e, 3, 0);
            break;
        case 10:
            FieldActor_PlayAnimationOnce(actor, 0x8e, 3, 0);
            break;
        default:
            FieldActor_PlayAnimationOnce(actor, 0x8c, 3, 0);
            break;
    }
    actor->work.s71.done = 1;

    if (!is_local_player(actor)) {
        return;
    }
    void *record = PlayerRecords_Current();
    if (record != NULL && PlayerRecord_TestFlag(record, 0x17)) {
        PlayerRecord_SetFlag(record, 0x1a);
    }
}
CLEAN_AS(func_ov003_0220eaa0, FieldActor_RunState71)

/* func_ov003_0220eb8c: at the end of the second animation the actor moves on and 0x8e8 is set
 * to 60. */
void FieldActor_EndState71(FieldActor *actor)
{
    if (actor->work.s71.done == 1 && FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
        actor->unk_8E8 = 60;
    }
}
CLEAN_AS(func_ov003_0220eb8c, FieldActor_EndState71)

/* func_ov003_0220ebe0: during the first animation: on reaching frame 10 with the item 0x137c
 * held, effect 0x32 at the point 0x68c (through func_0203f7d0; the actor's position while
 * that point is the origin) and func_02095694; on reaching frames 7 and 9, effects 0x39 and
 * 0x37 at points ahead of the actor (0x02238110, 0x02238118), facing its way. */
void FieldActor_AnimateState71(FieldActor *actor)
{
    LayeredModel_UpdateA((LayeredModel *) actor->unk_234);
    s16 yaw = actor->yaw;
    if (actor->work.s71.done) {
        return;
    }

    if (FrameCtrl_Passed(&actor->anim, 10)) {
        u16 item;
        FieldActor_RecordHeldItem(&item, actor);
        if (item == 0x137c) {
            Vec3 at;
            if (actor->unk_68C.x == 0 && actor->unk_68C.y == 0 && actor->unk_68C.z == 0) {
                at = actor->position;
            } else {
                at = actor->unk_68C;
                Globe_Unbend(&at, &at);
            }
            EffectSystem_StartKind(0x32, &at, NULL, 0);
            PlayerActorOps_SetHeldModel(0, actor->player);
        }
    }

    if (FrameCtrl_Passed(&actor->anim, 7)) {
        Vec3 ahead;
        FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &yaw, data_ov003_02238110);
        Vec3 at = ahead;
        EffectSystem_StartKind(0x39, &at, &yaw, 0);
    }
    if (FrameCtrl_Passed(&actor->anim, 9)) {
        Vec3 ahead;
        FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &yaw, data_ov003_02238118);
        Vec3 at = ahead;
        EffectSystem_StartKind(0x37, &at, &yaw, 0);
    }
}
CLEAN_AS(func_ov003_0220ebe0, FieldActor_AnimateState71)

/* func_ov003_0220ed24: state 0x71's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State71Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState71(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220ed24, FieldActor_State71Message)

/* func_ov003_0220ed30: entering state 0x71: the tool is kept and the first animation starts
 * by it: 0x8d for tools 4 (the held object in pose 7), 3 (pose 0x1d) and 10, else 0x8b; flag 9
 * is set and sound 0x7db plays. */
void FieldActor_EnterState71(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    int tool = FieldActor_HeldTool(actor);
    actor->work.s71.tool = tool;

    switch (tool) {
        case 4:
            HeldItem_Act(actor->held, 7, 2, 1);
            FieldActor_PlayAnimationOnce(actor, 0x8d, 2, 0);
            break;
        case 3:
            HeldItem_Act(actor->held, 0x1d, 2, 1);
            FieldActor_PlayAnimationOnce(actor, 0x8d, 2, 0);
            break;
        case 10:
            FieldActor_PlayAnimationOnce(actor, 0x8d, 2, 0);
            break;
        default:
            FieldActor_PlayAnimationOnce(actor, 0x8b, 2, 0);
            break;
    }
    actor->work.s71.done = 0;
    FieldActor_SetFlag(actor, 9);
    FieldActor_PlaySound(actor, 0x7db);
}
CLEAN_AS(func_ov003_0220ed30, FieldActor_EnterState71)

/* func_ov003_0220edcc: asks for state 0x71; whether it was queued. */
int FieldActor_RequestState71(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x71, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220edcc, FieldActor_RequestState71)

/* ---- State 0x6e: the actor turns to face yaw 0 */

/* func_ov003_0220ee04: state 0x6e's update. */
void FieldActor_UpdateState6E(FieldActor *actor)
{
    FieldActor_AnimateState6E(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState6E(actor);
}
CLEAN_AS(func_ov003_0220ee04, FieldActor_UpdateState6E)

/* Whether a held item code is nothing; for a code func_0204bcdc accepts, by comparing
 * func_0204bc64 of it and of nothing. */
static BOOL holds_nothing(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        item[1] = ITEM_NONE;
        int held = ItemCode_VariantItem(&item[0]);
        return held == ItemCode_VariantItem(&item[1]);
    }
    return item[0] == ITEM_NONE;
}

/* func_ov003_0220ee20: once the animation is over, animation 1 starts and the actor turns to
 * yaw 0 (func_0200faf0, 0x59a); when it faces that way func_02035a70, func_0200f3e8 and
 * func_0203e110 run and the actor moves on: holding an item, through FieldActor_RequestState3D,
 * else with func_0200d4e8 (3) and flag 0 set. */
void FieldActor_RunState6E(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->work.step = 1;
        FieldActor_PlayAnimationLoop(actor, 1, 3, 0);
    }
    if (actor->work.step == 0) {
        return;
    }
    if (!FieldActor_TurnToZero(actor, 0x59a)) {
        return;
    }
    Music2e4_End((Music2e4 *) (data_021c526c + 0x2e4));
    FieldActor_NudgeOne(actor);
    EventQueue_FinishKind4Or12();
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);

    u16 item[2];
    FieldActor_RecordHeldItem(&item[0], actor);
    if (!holds_nothing(item)) {
        FieldActor_RequestState3D(actor, 2, 2, 0, 0, 0, 6, -1);
    } else {
        FieldActor_RequestState2(actor, 3, 1, -1);
        FieldActor_SetFlag(actor, 0);
    }
}
CLEAN_AS(func_ov003_0220ee20, FieldActor_RunState6E)

/* func_ov003_0220ef1c: only while the byte 0x021c75b8 is 2: during animation 0x6a frames 0x13,
 * 0x19 and 0x1e run func_0200f888; during any other func_0200f95c runs each frame. */
void FieldActor_AnimateState6E(FieldActor *actor)
{
    if (data_021c75b8 != 2) {
        return;
    }
    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x6a) {
        int frame = anim_frame(actor);
        if (frame == 0x13 || frame == 0x19 || frame == 0x1e) {
            FieldActor_PlayFootstep(actor);
        }
    } else {
        FieldActor_Footfall(actor);
    }
}
CLEAN_AS(func_ov003_0220ef1c, FieldActor_AnimateState6E)

/* func_ov003_0220ef74: state 0x6e's message handler: asks for it again (priority 7, `arg`). */
void FieldActor_State6EMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6E(actor, 7, arg);
}
CLEAN_AS(func_ov003_0220ef74, FieldActor_State6EMessage)

/* func_ov003_0220ef80: entering state 0x6e: the actor faces yaw -0x8000 (away from yaw 0),
 * flag 0 is cleared, animation 0x6a starts and sound 0x818 plays. */
void FieldActor_EnterState6E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.step = 0;
    s16 yaw = -0x8000;
    FieldActor_SetYaw(actor, &yaw);
    FieldActor_ClearFlag(actor, 0);
    FieldActor_PlayAnimationOnce(actor, 0x6a, 0, 0);
    FieldActor_PlaySound(actor, 0x818);
}
CLEAN_AS(func_ov003_0220ef80, FieldActor_EnterState6E)

/* func_ov003_0220efc8: asks for state 0x6e; whether it was queued. */
void *FieldActor_RequestState6E(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x6e, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220efc8, FieldActor_RequestState6E)

/* ---- State 0x6d */

/* func_ov003_0220f000: state 0x6d's update. */
void FieldActor_UpdateState6D(FieldActor *actor)
{
    FieldActor_AnimateState6D(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState6D(actor);
}
CLEAN_AS(func_ov003_0220f000, FieldActor_UpdateState6D)

/* func_ov003_0220f01c: on reaching frame 0x2e with `kind` 2 or more, func_02035624 and
 * func_02035ac8 run. Otherwise, on reaching frame 0x2f, for the player at this console, the
 * point func_0204e108 gives (0x2000 further on z for player 0 with a nonzero kind), or
 * func_0204e08c for the other players with a nonzero kind, goes to func_020b63f4 with
 * func_020b5e10's object; with kind 0 the actor's own position goes there once
 * func_0204e108 succeeds. */
void FieldActor_RunState6D(FieldActor *actor)
{
    Vec3 point;

    if (FrameCtrl_Passed(&actor->anim, 0x2e)) {
        if (actor->work.s6d.kind >= 2) {
            Music_DropPriority(0xc);
            Music2e4_PlayMusic41((Music2e4 *) (data_021c526c + 0x2e4));
        }
        return;
    }
    if (!FrameCtrl_Passed(&actor->anim, 0x2f)) {
        return;
    }
    u32 source = AcreMap_Town();
    if (!is_local_player(actor)) {
        return;
    }
    if (actor->work.s6d.kind == 0) {
        if (AcreMap_HasBuilding5014((int) source, (int) (uintptr_t) &point, 0, 0)) {
            SceneExit_SetTo((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0, &actor->position, 0x1b800000, 0, 2, 2);
        }
    } else if (actor->player == 0) {
        if (AcreMap_HasBuilding5014((int) source, (int) (uintptr_t) &point, 0, 0)) {
            point.z = add32(point.z, 0x2000);
            SceneExit_SetTo((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0, &point, 0x1b800000, 0, 2, 2);
        }
    } else {
        if (AcreMap_HasBuilding500b((int) source, (int) (uintptr_t) &point, 0, 0)) {
            SceneExit_SetTo((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0, &point, 0x1b800000, 0, 2, 2);
        }
    }
}
CLEAN_AS(func_ov003_0220f01c, FieldActor_RunState6D)

/* func_ov003_0220f128: effect 0x34 follows effect_point. */
void FieldActor_AnimateState6D(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    follow_effect(actor, &actor->work.s6d.effect, 0x34);
}
CLEAN_AS(func_ov003_0220f128, FieldActor_AnimateState6D)

/* func_ov003_0220f16c: state 0x6d's message handler: asks for it again with kind 0, priority 7
 * and `arg`. */
void FieldActor_State6DMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6D(actor, 0, 7, arg);
}
CLEAN_AS(func_ov003_0220f16c, FieldActor_State6DMessage)

/* func_ov003_0220f180: entering state 0x6d with the request's kind: animation 0x69 for tools 3
 * (the held object in pose 0x14), 4 (pose 2) and 10, else 0x68; func_0203e420; effect 0x34 at
 * effect_point. A kind of 2 or more also runs SoundSys_PlaySe(0x51), sound 0x839 (kind 2) or
 * 0x838 and func_02035684. Sound 0x816 plays. */
void FieldActor_EnterState6D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 kind = request->payload[0];
    int tool = FieldActor_HeldTool(actor);

    if (tool == 3 || tool == 4 || tool == 10) {
        FieldActor_PlayAnimationOnce(actor, 0x69, 3, 6);
        if (tool == 3) {
            HeldItem_Act(actor->held, 0x14, 3, 1);
        } else if (tool == 4) {
            HeldItem_Act(actor->held, 2, 9, 1);
        }
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x68, 3, 6);
    }
    EventQueue_RequestKind8();
    actor->work.s6d.effect = EffectSystem_StartKind(0x34, &actor->effect_point, NULL, 0);
    actor->work.s6d.kind = kind;
    if (kind >= 2) {
        SoundSys_PlaySe(0x51);
        FieldActor_PlaySound(actor, kind == 2 ? 0x839 : 0x838);
        Music_AddValue(0xc, 0, 0);
    }
    FieldActor_PlaySound(actor, 0x816);
}
CLEAN_AS(func_ov003_0220f180, FieldActor_EnterState6D)

/* func_ov003_0220f244: asks for state 0x6d with `kind`; whether it was queued. */
int FieldActor_RequestState6D(FieldActor *actor, char kind, int priority, int arg)
{
    const u8 payload[1] = {(u8) kind};
    return request_state(actor, 0x6d, priority, arg, payload, 1);
}
CLEAN_AS(func_ov003_0220f244, FieldActor_RequestState6D)

/* ---- Requests built in steps: the payload is written by a function of its own */

/* The start of a request for `state` (see request_state, whose BUG applies here too). */
static void begin_request(StateRequest *request, int state, int priority, int arg)
{
#ifdef BUGFIX
    *request = (StateRequest){0};
#endif
    StateRequest_Construct(request);
    StateRequest_Set(request, state, priority, arg);
}

/* Queues a request begun with begin_request; whether it was queued. */
static int finish_request(FieldActor *actor, StateRequest *request)
{
    int queued = FieldActor_QueueRequest(actor, request);
    StateRequest_Destruct(request);
    return queued;
}

/* Copies a point word by word in order x, y, z, as the game does: when `dst` overlaps `src`
 * (never in the game's calls) the words read are then the ones just written. */
static void copy_point(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* The whole number of frames in the animation. QUIRK: only the low 16 bits. */
static u32 anim_frames(const FieldActor *actor)
{
    return ((u32) actor->anim.end >> 12) & 0xffff;
}

/* ---- State 0x6c: animation 0x7a played backwards */

/* func_ov003_0220f280: state 0x6c's update. */
void FieldActor_UpdateState6C(FieldActor *actor)
{
    FieldActor_RunState6C(actor);
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov003_0220f280, FieldActor_UpdateState6C)

/* func_ov003_0220f294: at the animation's end animation 0 starts, and the actors of the other
 * players note the state after this one (the actor of this console is moved on elsewhere). */
void FieldActor_RunState6C(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
        if (!is_local_player(actor)) {
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        }
    }
}
CLEAN_AS(func_ov003_0220f294, FieldActor_RunState6C)

/* func_ov003_0220f2ec: state 0x6c's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State6CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6C(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220f2ec, FieldActor_State6CMessage)

/* func_ov003_0220f2f8: entering state 0x6c: animation 0x7a (unless it is already playing) is
 * restarted to play once backwards from its last frame. */
void FieldActor_EnterState6C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (actor->animation != 0x7a) {
        FieldActor_PlayAnimationOnce(actor, 0x7a, 3, 0);
    }
    u32 frames = anim_frames(actor);
    FrameCtrl_Init(&actor->anim, frames, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) (frames - 1));
}
CLEAN_AS(func_ov003_0220f2f8, FieldActor_EnterState6C)

/* func_ov003_0220f344: asks for state 0x6c; whether it was queued. */
int FieldActor_RequestState6C(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x6c, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220f344, FieldActor_RequestState6C)

/* ---- State 0x6b: an animation held on its last frame */

/* func_ov003_0220f37c: state 0x6b's update. */
void FieldActor_UpdateState6B(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov003_0220f37c, FieldActor_UpdateState6B)

/* func_ov003_0220f390: state 0x6b's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State6BMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6B(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220f390, FieldActor_State6BMessage)

/* func_ov003_0220f39c: entering state 0x6b: animation 0x7a if it is playing (state 0x6a's),
 * else animation 0x38, is put on its last frame. */
void FieldActor_EnterState6B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (actor->animation != 0x7a) {
        FieldActor_PlayAnimationOnce(actor, 0x38, 3, 0);
    }
    actor->anim.frame = (fx32) (((anim_frames(actor) - 1) & 0xffff) << 12);
}
CLEAN_AS(func_ov003_0220f39c, FieldActor_EnterState6B)

/* func_ov003_0220f3d8: asks for state 0x6b; whether it was queued. */
int FieldActor_RequestState6B(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x6b, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220f3d8, FieldActor_RequestState6B)

/* ---- State 0x6a: animation 0x7a at a point, facing yaw -0x8000; state 0x6b follows */

/* func_ov003_0220f410: state 0x6a's update. */
void FieldActor_UpdateState6A(FieldActor *actor)
{
    FieldActor_PlaceState6A(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState6A(actor);
}
CLEAN_AS(func_ov003_0220f410, FieldActor_UpdateState6A)

/* func_ov003_0220f430: at the animation's end, asks for state 0x6b. */
void FieldActor_EndState6A(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_RequestState6B(actor, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220f430, FieldActor_EndState6A)

/* func_ov003_0220f458: the actor is put on the point (x and z), facing yaw -0x8000. */
void FieldActor_PlaceState6A(FieldActor *actor)
{
    FieldActor_MoveToPose(actor, actor->work.s6a_point.x, actor->work.s6a_point.z, -0x8000);
}
CLEAN_AS(func_ov003_0220f458, FieldActor_PlaceState6A)

/* func_ov003_0220f478: state 0x6a's message handler: asks for it again with the saved point,
 * priority 6 and `arg`. */
void FieldActor_State6AMessage(FieldActor *actor, int arg)
{
    Vec3 point;

    PackedPoint_Get(actor->saved.packed, &point);
    FieldActor_RequestState6A(actor, point, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220f478, FieldActor_State6AMessage)

/* func_ov003_0220f4a8: entering state 0x6a: animation 0x7a; the request's point is kept and
 * saved packed. */
void FieldActor_EnterState6A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x7a, 3, 0);
    Vec3 point = *(const Vec3 *) (const void *) request->payload;
    State6A_SetPoint(&actor->work.s6a_point, point);
    PackedPoint_Set(actor->saved.packed, &point);
}
CLEAN_AS(func_ov003_0220f4a8, FieldActor_EnterState6A)

/* func_ov003_0220f4f0: unpacks a point packed by PackedPoint_Set (its nibble is dropped). */
void PackedPoint_Get(const u8 *packed, Vec3 *point)
{
    u8 nibble;
    PackedBytes_UnpackPointAndValue(packed, (u32 *) &point->x, &point->y, (u32 *) &point->z, &nibble);
}
CLEAN_AS(func_ov003_0220f4f0, PackedPoint_Get)

/* func_ov003_0220f508: packs a point, with nibble 0. */
void PackedPoint_Set(u8 *packed, const Vec3 *point)
{
    PackedBytes_PackPointAndValue(packed, point->x, point->y, point->z, 0);
}
CLEAN_AS(func_ov003_0220f508, PackedPoint_Set)

/* func_ov003_0220f524 */
void State6A_SetPoint(Vec3 *dst, Vec3 value)
{
    *dst = value;
}
CLEAN_AS(func_ov003_0220f524, State6A_SetPoint)

/* func_ov003_0220f538: asks for state 0x6a at a point; whether it was queued (as a pointer). */
void *FieldActor_RequestState6A(FieldActor *actor, Vec3 point, u32 priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x6a, (int) priority, arg);
    State6A_SetRequestPoint((Vec3 *) (void *) request.payload, point);
    return (void *) (intptr_t) finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220f538, FieldActor_RequestState6A)

/* func_ov003_0220f57c */
void State6A_SetRequestPoint(Vec3 *dst, Vec3 value)
{
    *dst = value;
}
CLEAN_AS(func_ov003_0220f57c, State6A_SetRequestPoint)

/* ---- State 0x69: animation 0x67 turned towards a point; state 0x77 or func_0200d4e8 follows */

/* func_ov003_0220f590: state 0x69's update: the actor of this console turns; another player's
 * actor first walks to the tile's middle and turns once it is there. */
void FieldActor_UpdateState69(FieldActor *actor)
{
    FieldActor_AnimateState69(actor);
    if (is_local_player(actor)) {
        FieldActor_TurnState69(actor);
        FieldActor_EnterContact(actor);
    } else {
        int tile[2] = {actor->work.s69.tile_x, actor->work.s69.tile_z};
        if (FieldActor_FollowReportedToTile(actor, tile)) {
            FieldActor_TurnState69(actor);
        }
        FieldActor_EnterContact(actor);
    }
    FieldActor_EndState69(actor);
}
CLEAN_AS(func_ov003_0220f590, FieldActor_UpdateState69)

/* func_ov003_0220f5f8: at the animation's end the actor moves on: to state 0x77 with its yaw
 * when then_77 is set, else through func_0200d4e8. */
void FieldActor_EndState69(FieldActor *actor)
{
    u8 then_77 = actor->work.s69.then_77;

    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        if (then_77) {
            FieldActor_RequestState77(actor, (u16) actor->yaw, 6, -1);
        } else {
            FieldActor_RequestState2(actor, 3, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_0220f5f8, FieldActor_EndState69)

/* func_ov003_0220f658: the actor turns towards the work's yaw. */
void FieldActor_TurnState69(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, (s16) actor->work.s69.yaw);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_ov003_0220f658, FieldActor_TurnState69)

/* func_ov003_0220f684: on reaching frame 5 the tile goes to func_ov003_02224384 (3), flag 0x12
 * is cleared and flag 9 set. */
void FieldActor_AnimateState69(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_Passed(&actor->anim, 5)) {
        return;
    }
    int tile[2] = {actor->work.s69.tile_x, actor->work.s69.tile_z};
    GrowthModel_RequestHit(actor->player, (const TileChangesTile *) tile, 3);
    FieldActor_ClearFlag(actor, 0x12);
    FieldActor_SetFlag(actor, 9);
}
CLEAN_AS(func_ov003_0220f684, FieldActor_AnimateState69)

/* func_ov003_0220f6d8: state 0x69's message handler does nothing. */
void FieldActor_State69Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220f6d8, FieldActor_State69Message)

/* func_ov003_0220f6dc: entering state 0x69: the yaw towards the request's point and the tile it
 * is on are kept with the flags, and animation 0x67 starts. */
void FieldActor_EnterState69(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const XZArgs *args = (const XZArgs *) (const void *) request->payload;
    u8 then_77 = args->then_77;
    u8 then_69 = args->then_69;
    Vec3 target = {args->x, actor->position.y, args->z};
    s16 yaw = Math_Atan2(sub32(target.x, actor->position.x), sub32(target.z, actor->position.z));
    int tile_x = 0;
    int tile_z = 0;

    Position_Tile(&tile_x, &tile_z, (const Position *) &target);
    State69Work_Set(&actor->work.s69, (u16) yaw, (u32) tile_x, (u32) tile_z, then_77, then_69);
    FieldActor_PlayAnimationOnce(actor, 0x67, 3, 0);
}
CLEAN_AS(func_ov003_0220f6dc, FieldActor_EnterState69)

/* func_ov003_0220f744 */
void State69Work_Set(State69Work *work, u16 yaw, u32 tile_x, u32 tile_z, u8 then_77, u8 then_69)
{
    work->unk_00 = 0;
    work->yaw = yaw;
    work->tile_x = (int) tile_x;
    work->tile_z = (int) tile_z;
    work->then_77 = then_77;
    work->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220f744, State69Work_Set)

/* func_ov003_0220f768: asks for state 0x69 towards (x, z); whether it was queued. */
int FieldActor_RequestState69(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x69, priority, arg);
    XZArgs_Set69((XZArgs *) (void *) request.payload, x, z, (u8) then_77, then_69);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220f768, FieldActor_RequestState69)

/* func_ov003_0220f7b8 */
void XZArgs_Set69(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    args->x = x;
    args->z = z;
    args->then_77 = then_77;
    args->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220f7b8, XZArgs_Set69)

/* ---- State 0x68: animation 0x66 turned towards a point; state 0x69 may follow */

/* The tile under the work's point. */
static void state68_tile(const FieldActor *actor, int *tile)
{
    Vec3 at = {actor->work.s68.x, 0, actor->work.s68.z};

    tile[0] = 0;
    tile[1] = 0;
    Position_Tile(&tile[0], &tile[1], (const Position *) &at);
}

/* func_ov003_0220f7cc: state 0x68's update. In the fifth frame the tile goes to
 * func_ov003_02224384 (2), from the seventh on to func_ov003_022235d8 each frame. The actor of
 * this console turns; another player's actor turns only once func_0200f554 says it is in
 * place. */
void FieldActor_UpdateState68(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;
    int tile[2];

    state68_tile(actor, tile);
    if (work->count > 5) {
        int copy[2] = {tile[0], tile[1]};
        GrowthModel_Loop(actor->player, (const TileChangesTile *) copy);
    } else {
        work->count++;
        if (work->count == 5) {
            int copy[2] = {tile[0], tile[1]};
            GrowthModel_RequestHit(actor->player, (const TileChangesTile *) copy, 2);
        }
    }
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_TurnState68(actor);
        FieldActor_EnterContact(actor);
        FieldActor_EndState68Local(actor);
    } else {
        if (FieldActor_FollowReported(actor)) {
            FieldActor_TurnState68(actor);
        }
        FieldActor_EnterContact(actor);
        FieldActor_EndState68Remote(actor);
    }
}
CLEAN_AS(func_ov003_0220f7cc, FieldActor_UpdateState68)

/* func_ov003_0220f884: another player's actor: the state after this one is noted, and with
 * then_69 set, state 0x69 is asked for at the animation's end. */
void FieldActor_EndState68Remote(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;

    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (work->then_69 && FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_RequestState69(actor, work->x, work->z, work->then_77, 1, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220f884, FieldActor_EndState68Remote)

/* func_ov003_0220f8e0: the actor of this console: with then_69 set, state 0x69 is asked for at
 * the animation's end. Otherwise the word at 0x818 decides: 1 sets then_69 and makes the
 * animation stop at its end, 2 moves on through func_0200d4e8. */
void FieldActor_EndState68Local(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;

    if (work->then_69) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FieldActor_RequestState69(actor, work->x, work->z, work->then_77, 1, 6, -1);
        }
    } else if (actor->unk_818 == 1) {
        work->then_69 = 1;
        actor->anim.flags = FRAME_CTRL_ONCE;
    } else if (actor->unk_818 == 2) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220f8e0, FieldActor_EndState68Local)

/* func_ov003_0220f968: the actor turns towards the work's yaw. */
void FieldActor_TurnState68(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, (s16) actor->work.s68.yaw);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_ov003_0220f968, FieldActor_TurnState68)

/* func_ov003_0220f994: leaving state 0x68: another player's actor that leaves before its fifth
 * frame sends the tile to func_ov003_02224384 (2) now. */
void FieldActor_ExitState68(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (actor->work.s68.count >= 5) {
        return;
    }
    int tile[2];
    state68_tile(actor, tile);
    int copy[2] = {tile[0], tile[1]};
    GrowthModel_RequestHit(actor->player, (const TileChangesTile *) copy, 2);
}
CLEAN_AS(func_ov003_0220f994, FieldActor_ExitState68)

/* func_ov003_0220f9f8: state 0x68's message handler: in state 0x68 `arg` is kept at 0xc84;
 * otherwise state 0x68 is asked for again with the saved point and flags, priority 6.
 * BUG: then_77 is taken as the whole flags byte being nonzero, so a request with only then_69
 * set comes back with then_77 set too. */
void FieldActor_State68Message(FieldActor *actor, int arg)
{
    fx32 x;
    fx32 z;
    u8 flags;

    if (actor->state == 0x68) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    PackedXZ_Get(actor->saved.packed, &x, &z, &flags);
#ifdef BUGFIX
    int then_77 = (flags & 0xf) != 0;
#else
    int then_77 = flags != 0;
#endif
    FieldActor_RequestState68(actor, x, z, then_77, (flags >> 4) != 0, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220f9f8, FieldActor_State68Message)

/* func_ov003_0220fa5c: entering state 0x68: the request's point, the yaw towards it and the
 * flags are kept, the point and flags saved packed; animation 0x66 starts (by func_020109a0
 * when state 0x69 follows, else by func_020109fc) and flag 9 is set. */
void FieldActor_EnterState68(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const XZArgs *args = (const XZArgs *) (const void *) request->payload;
    u8 then_77 = args->then_77;
    u8 then_69 = args->then_69;
    fx32 x = args->x;
    fx32 z = args->z;
    s16 yaw = Math_Atan2(sub32(x, actor->position.x), sub32(z, actor->position.z));

    State68Work_Set(&actor->work.s68, yaw, x, z, then_77, then_69);
    PackedXZ_Set(actor->saved.packed, x, z, (u8) (then_77 | then_69 << 4));
    if (then_69) {
        FieldActor_PlayAnimationOnce(actor, 0x66, 3, 0);
    } else {
        FieldActor_PlayAnimationLoop(actor, 0x66, 3, 0);
    }
    FieldActor_SetFlag(actor, 9);
}
CLEAN_AS(func_ov003_0220fa5c, FieldActor_EnterState68)

/* func_ov003_0220fae4: unpacks x and z and the byte after them. */
void PackedXZ_Get(u8 *packed, fx32 *x, fx32 *z, u8 *flags)
{
    PackedBytes_UnpackPoint(packed, (u32 *) x, (u32 *) z);
    *flags = packed[5];
}
CLEAN_AS(func_ov003_0220fae4, PackedXZ_Get)

/* func_ov003_0220fafc: packs x and z and the byte after them. */
void PackedXZ_Set(u8 *packed, fx32 x, fx32 z, int flags)
{
    PackedBytes_PackPoint(packed, x, z);
    packed[5] = (u8) flags;
}
CLEAN_AS(func_ov003_0220fafc, PackedXZ_Set)

/* func_ov003_0220fb14 */
void State68Work_Set(State68Work *work, int yaw, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    work->yaw = (u16) yaw;
    work->x = x;
    work->z = z;
    work->then_77 = then_77;
    work->then_69 = then_69;
    work->count = 0;
}
CLEAN_AS(func_ov003_0220fb14, State68Work_Set)

/* func_ov003_0220fb30: asks for state 0x68 towards (x, z); whether it was queued. */
int FieldActor_RequestState68(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x68, priority, arg);
    XZArgs_Set68((XZArgs *) (void *) request.payload, x, z, (u8) then_77, then_69);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220fb30, FieldActor_RequestState68)

/* func_ov003_0220fb80 */
void XZArgs_Set68(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    args->x = x;
    args->z = z;
    args->then_77 = then_77;
    args->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220fb80, XZArgs_Set68)

/* ---- State 0x67: animation 0x65 walking to a point, with effects */

/* func_ov003_0220fb94: state 0x67's update: the actor walks to the point and turns once
 * there. */
void FieldActor_UpdateState67(FieldActor *actor)
{
    FieldActor_AnimateState67(actor);
    Vec3 point = actor->work.s67.point;
    if (FieldActor_FollowReportedTo(actor, &point)) {
        FieldActor_TurnState67(actor);
    }
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState67Local(actor);
    } else {
        FieldActor_EndState67Remote(actor);
    }
}
CLEAN_AS(func_ov003_0220fb94, FieldActor_UpdateState67)

/* func_ov003_0220fbf8: another player's actor: the state after this one is noted; at the
 * animation's end it moves on through func_0200d4e8. */
void FieldActor_EndState67Remote(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220fbf8, FieldActor_EndState67Remote)

/* func_ov003_0220fc34: the actor of this console moves on at the animation's end, and may
 * leave from frame 22 on (FieldActor_ResumeMoving). */
void FieldActor_EndState67Local(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
    if (anim_frame(actor) >= 22) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220fc34, FieldActor_EndState67Local)

/* func_ov003_0220fc88: the actor turns towards the work's yaw. */
void FieldActor_TurnState67(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, actor->work.s67.yaw);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_ov003_0220fc88, FieldActor_TurnState67)

/* func_ov003_0220fcb4: during animation 0x65, on reaching frame 3 or 13, effect 0x23 starts at
 * the actor's position and yaw. */
void FieldActor_AnimateState67(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x65) {
        if (FrameCtrl_Passed(&actor->anim, 3) || FrameCtrl_Passed(&actor->anim, 13)) {
            EffectSystem_StartKind(0x23, &actor->position, &actor->yaw, 0);
        }
    }
}
CLEAN_AS(func_ov003_0220fcb4, FieldActor_AnimateState67)

/* func_ov003_0220fd00: state 0x67's message handler does nothing. */
void FieldActor_State67Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220fd00, FieldActor_State67Message)

/* func_ov003_0220fd04: entering state 0x67: the request's point and the yaw towards it are
 * kept, animation 0x65 starts, the point goes to func_ov003_02220db4, flag 0x1c is cleared,
 * sound 0x7da plays and flag 9 is set. */
void FieldActor_EnterState67(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    Vec3 point = *(const Vec3 *) (const void *) request->payload;
    s16 yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    Vec3 copy = point;

    State67Work_Set(&actor->work.s67, yaw, &copy);
    FieldActor_PlayAnimationOnce(actor, 0x65, 3, 0);
    copy = point;
    TileEvent_StartKindA(actor->player, &copy);
    FieldActor_ClearFlag(actor, 0x1c);
    FieldActor_PlaySound(actor, 0x7da);
    FieldActor_SetFlag(actor, 9);
}
CLEAN_AS(func_ov003_0220fd04, FieldActor_EnterState67)

/* func_ov003_0220fd90 */
void State67Work_Set(State67Work *work, s16 yaw, const Vec3 *point)
{
    work->yaw = yaw;
    copy_point(&work->point, point);
}
CLEAN_AS(func_ov003_0220fd90, State67Work_Set)

/* func_ov003_0220fda0: asks for state 0x67 at the middle of the tile `at` is on (at its
 * height); whether it was queued. */
int FieldActor_RequestState67(FieldActor *actor, const Vec3 *at, int priority, int arg)
{
    StateRequest request;
    Vec3 middle;

    begin_request(&request, 0x67, priority, arg);
    AcreTile_SnapToTileCentre(&middle, at);
    Vec3 copy = middle;
    State67_CopyPoint((Vec3 *) (void *) request.payload, &copy);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220fda0, FieldActor_RequestState67)

/* func_ov003_0220fdf4 */
void State67_CopyPoint(Vec3 *dst, const Vec3 *src)
{
    copy_point(dst, src);
}
CLEAN_AS(func_ov003_0220fdf4, State67_CopyPoint)

/* ---- State 0x66: animation 0x64 walking to a tile's middle; state 0x67 may follow */

/* func_ov003_0220fe04: state 0x66's update: the actor walks to the point and turns once
 * there. */
void FieldActor_UpdateState66(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    Vec3 point = actor->work.s66.point;
    if (FieldActor_FollowReportedTo(actor, &point)) {
        FieldActor_TurnState66(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_EndState66(actor);
}
CLEAN_AS(func_ov003_0220fe04, FieldActor_UpdateState66)

/* func_ov003_0220fe4c: for the actor of this console with nothing decided yet, the word at
 * 0x818 decides (1: state 0x67, 2: func_0200d4e8). The first two frames are only counted;
 * after them another player's actor notes the state after this one, and what was decided is
 * done. */
void FieldActor_EndState66(FieldActor *actor)
{
    State66Work *work = &actor->work.s66;

    if (is_local_player(actor) && work->next == 0) {
        if (actor->unk_818 == 1) {
            work->next = 1;
        } else if (actor->unk_818 == 2) {
            work->next = 2;
        }
    }
    if (work->count < 2) {
        work->count++;
        return;
    }
    if (!is_local_player(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
    if (work->next == 1) {
        Vec3 point = work->point;
        FieldActor_RequestState67(actor, &point, 6, -1);
    } else if (work->next == 2) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220fe4c, FieldActor_EndState66)

/* func_ov003_0220ff14: the actor turns towards the work's yaw. */
void FieldActor_TurnState66(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, (s16) actor->work.s66.yaw);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_ov003_0220ff14, FieldActor_TurnState66)

/* func_ov003_0220ff40: leaving state 0x66 for `next`: flag 0x1c is cleared. Another player's
 * actor leaving for neither state 2 nor 0x67 with the flag set first sends the point to
 * func_ov003_02220db4 (as entering state 0x67 would); with the flag clear nothing is done. */
void FieldActor_ExitState66(FieldActor *actor, int next)
{
    if (!is_local_player(actor) && next != 2 && next != 0x67) {
        if (FieldActor_TestFlag(actor, 0x1c)) {
            Vec3 point = actor->work.s66.point;
            TileEvent_StartKindA(actor->player, &point);
            FieldActor_ClearFlag(actor, 0x1c);
        }
        return;
    }
    FieldActor_ClearFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_0220ff40, FieldActor_ExitState66)

/* func_ov003_0220ffc0: state 0x66's message handler: in state 0x66 `arg` is kept at 0xc84;
 * otherwise state 0x66 is asked for again for the saved tile (next 0), priority 6. */
void FieldActor_State66Message(FieldActor *actor, int arg)
{
    if (actor->state == 0x66) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    int tile[2] = {0, 0};
    TileArgs_GetInts(&actor->saved.tile, tile);
    int copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState66(actor, copy, 0, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220ffc0, FieldActor_State66Message)

/* func_ov003_02210010: entering state 0x66: the middle of the request's tile, the yaw towards
 * it and `next` are kept, the tile saved, animation 0x64 starts, and with `next` 1 flag 0x1c is
 * set. */
void FieldActor_EnterState66(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileNextArgs *args = (const TileNextArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;
    int next = args->next;
    Vec3 point;

    AcreTile_TileCentre(&point, (u32) x, (u32) z);
    s16 yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    Vec3 copy = point;
    State66Work_Set(&actor->work.s66, (u8) next, (u16) yaw, &copy);
    int tile[2] = {x, z};
    TileArgs_SetInts(&actor->saved.tile, tile);
    FieldActor_PlayAnimationLoop(actor, 0x64, 3, 0);
    if (actor->work.s66.next == 1) {
        FieldActor_SetFlag(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_02210010, FieldActor_EnterState66)

/* func_ov003_02210094 */
void TileArgs_GetInts(const TileArgs *args, int *tile)
{
    tile[0] = args->x;
    tile[1] = args->z;
}
CLEAN_AS(func_ov003_02210094, TileArgs_GetInts)

/* func_ov003_022100a0 */
void TileArgs_SetInts(TileArgs *args, const int *tile)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_022100a0, TileArgs_SetInts)

/* func_ov003_022100ac */
void State66Work_Set(State66Work *work, u8 next, u16 yaw, const Vec3 *point)
{
    work->next = next;
    work->count = 0;
    work->yaw = yaw;
    copy_point(&work->point, point);
}
CLEAN_AS(func_ov003_022100ac, State66Work_Set)

/* ---- States 0x66 (request) and 0x65 to 0x5e */

static_assert(offsetof(FieldActor, unk_0C4) == 0xc4, "0xc4");
static_assert(offsetof(FieldActor, unk_0D0) == 0xd0, "0xd0");
static_assert(offsetof(FieldActor, unk_298) == 0x298, "0x298");
static_assert(offsetof(FieldActor, unk_698) == 0x698, "0x698");
static_assert(offsetof(FieldActor, unk_81C) == 0x81c, "0x81c");
static_assert(offsetof(FieldActor, item) == 0x820, "item");
static_assert(offsetof(FieldActor, unk_824) == 0x824, "0x824");
static_assert(offsetof(FieldActor, work.s62.point) == 0x7d8, "state 0x62 point");
static_assert(offsetof(FieldActor, work.s62.yaw) == 0x7e4, "state 0x62 yaw");
static_assert(offsetof(FieldActor, work.s62.kind) == 0x7e6, "state 0x62 kind");
static_assert(offsetof(FieldActor, work.s61.yaw) == 0x7d6, "state 0x61 yaw");
static_assert(offsetof(FieldActor, work.s61.done) == 0x7db, "state 0x61 done");
static_assert(offsetof(FieldActor, work.s5f.step) == 0x7e0, "state 0x5f step");
static_assert(offsetof(FieldActor, work.s5f.kind) == 0x7e1, "state 0x5f kind");
static_assert(offsetof(FieldActor, work.s5e.point) == 0x7d8, "state 0x5e point");
static_assert(offsetof(PointItemArgs, item) == 0xc, "point item args");
static_assert(offsetof(PointItemArgs, kind) == 0xe, "point item args kind");
static_assert(sizeof(PointItemArgs) <= sizeof(((StateRequest *) 0)->payload), "payload");

/* The effect handle state 0x63 keeps (func_020912d4), -1 for none. */
#define STATE63_EFFECT(actor) ((actor)->work.effect.effect)

/* Starts a request for `state` (func_0200e92c, func_0200e90c); the caller fills the payload and
 * sends it with send_request.
 * BUG: as in request_state, the bytes of the request nothing sets are the stack's. */
static void open_request(StateRequest *request, int state, int priority, int arg)
{
#ifdef BUGFIX
    memset(request, 0, sizeof(*request));
#endif
    StateRequest_Construct(request);
    StateRequest_Set(request, state, priority, arg);
}

/* Queues the request (func_0200e894) and ends it (func_0200e91c); whether it was queued. */
static int send_request(FieldActor *actor, StateRequest *request)
{
    int queued = FieldActor_QueueRequest(actor, request);
    StateRequest_Destruct(request);
    return queued;
}

/* Whether an item code is nothing: for a code func_0204bcdc accepts, by comparing func_0204bc64
 * of it and of ITEM_NONE (held in a temporary); otherwise by the code itself. */
static BOOL item_is_nothing(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = ITEM_NONE;
        int code = ItemCode_VariantItem(item);
        return code == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_NONE;
}

/* Releases the receiver at 0xec when flag 0x11 says it is registered. */
static void release_receiver(FieldActor *actor)
{
    if (FieldActor_TestFlag(actor, 0x11)) {
        FieldActor_ClearFlag(actor, 0x11);
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
    }
}

/* Ends a state the usual way: the state after it is noted and func_0200d4e8 (3) moves on. */
static void move_on(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, 3, 1, -1);
}

/* Ends state 0x63's effect, if any. */
static void end_state63_effect(FieldActor *actor)
{
    if (STATE63_EFFECT(actor) != -1) {
        EffectSystem_EndHandle(STATE63_EFFECT(actor));
        STATE63_EFFECT(actor) = -1;
    }
}

/* func_ov003_022100c4: asks for state 0x66 for a tile and what follows it (State66Work.next);
 * whether it was queued. */
int FieldActor_RequestState66(FieldActor *actor, const int *tile, int next, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x66, priority, arg);
    int copy[2] = {tile[0], tile[1]};
    TileNextArgs_Set((TileNextArgs *) (void *) request.payload, copy, (u8) next);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022100c4, FieldActor_RequestState66)

/* func_ov003_02210114 */
void TileNextArgs_Set(TileNextArgs *args, const int *tile, u8 next)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->next = next;
}
CLEAN_AS(func_ov003_02210114, TileNextArgs_Set)

/* ---- State 0x65: animation 0 */

/* func_ov003_02210120: state 0x65's update. */
void FieldActor_UpdateState65(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
}
CLEAN_AS(func_ov003_02210120, FieldActor_UpdateState65)

/* func_ov003_0221013c: state 0x65's message handler: messages are ignored. */
void FieldActor_State65Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0221013c, FieldActor_State65Message)

/* func_ov003_02210140: entering state 0x65: animation 0 starts. */
void FieldActor_EnterState65(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
}
CLEAN_AS(func_ov003_02210140, FieldActor_EnterState65)

/* func_ov003_02210154: asks for state 0x65; whether it was queued. */
int FieldActor_RequestState65(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x65, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02210154, FieldActor_RequestState65)

/* ---- State 0x64: animation 0x5f with the held object in pose 0x22, then 0x60 */

/* func_ov003_0221018c: state 0x64's update. */
void FieldActor_UpdateState64(FieldActor *actor)
{
    FieldActor_RunState64(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState64(actor);
}
CLEAN_AS(func_ov003_0221018c, FieldActor_UpdateState64)

/* func_ov003_022101a8: once the animation is over animation 0x60 starts; another player's
 * actor notes the state after this one. */
void FieldActor_EndState64(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    FieldActor_PlayAnimationLoop(actor, 0x60, 3, 3);
    if (is_local_player(actor)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
}
CLEAN_AS(func_ov003_022101a8, FieldActor_EndState64)

/* func_ov003_022101fc: the actor turns to yaw 0 (func_0200faa8, 0x400). During animation
 * 0x5f, at a point 0xb00 above and 0x300 beyond (z) where the frame's update began, the frames
 * before 11 run func_0200f2a0 (0x851); on frame 11 the object at 0x5c8 is set up there (9),
 * sounds 0x852 and 0x853 play and flag 9 is set. */
void FieldActor_RunState64(FieldActor *actor)
{
    FieldActor_TurnToHalfTurn(actor, 0x400);
    FieldActor_UpdateBody(actor);
    if (actor->animation != 0x5f) {
        return;
    }
    Vec3 point = actor->start_position;
    point.y = add32(point.y, 0xb00);
    point.z = add32(point.z, 0x300);
    if (anim_frame(actor) < 11) {
        FieldActor_PlaySoundAt(actor, 0x851, &point);
        return;
    }
    if (FrameCtrl_Passed(&actor->anim, 11)) {
        void *object = &actor->held[0x28];
        FishingFloat_SetState(object, 9);
        FishingFloat_SetPosition(object, &point);
        FieldActor_PlaySound(actor, 0x852);
        FieldActor_PlaySound(actor, 0x853);
        FieldActor_SetFlag(actor, 9);
    }
}
CLEAN_AS(func_ov003_022101fc, FieldActor_RunState64)

/* func_ov003_022102d0: state 0x64's message handler: state 0x64 is asked for again, priority
 * 6. */
void FieldActor_State64Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState64(actor, 6, arg);
}
CLEAN_AS(func_ov003_022102d0, FieldActor_State64Message)

/* func_ov003_022102dc: entering state 0x64: the actor of this console moves on at once when
 * func_0203e168 says no; otherwise func_020ba35c runs for the player, animation 0x5f starts
 * and the held object takes pose 0x22. */
void FieldActor_EnterState64(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (is_local_player(actor) && EventQueue_RequestKind14() == 0) {
        move_on(actor);
        return;
    }
    Sky_Objects020bdf68(actor->player);
    FieldActor_PlayAnimationOnce(actor, 0x5f, 3, 0);
    HeldItem_Act(actor->held, 0x22, 3, 1);
}
CLEAN_AS(func_ov003_022102dc, FieldActor_EnterState64)

/* func_ov003_02210354: asks for state 0x64; whether it was queued. */
void *FieldActor_RequestState64(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x64, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02210354, FieldActor_RequestState64)

/* ---- State 0x63: animation 0x61 with effect 0x26 */

/* func_ov003_0221038c: state 0x63's update. */
void FieldActor_UpdateState63(FieldActor *actor)
{
    FieldActor_RunState63(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState63Local(actor);
    } else {
        FieldActor_EndState63Remote(actor);
    }
}
CLEAN_AS(func_ov003_0221038c, FieldActor_UpdateState63)

/* func_ov003_022103cc: for another player's actor: the state after this one is noted. When the
 * saved flag says the actor at that player's console left the state early and the session
 * reports state 0x63 for the player (func_02096518), state 0x63 is asked for again (the flag
 * kept set) and the effect ends; otherwise the actor moves on once the animation is over. */
void FieldActor_EndState63Remote(FieldActor *actor)
{
    u8 left_early;
    u32 state;

    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    SavedFlag_Get(&actor->saved.left_early, &left_early);
    if (left_early && SessionPlayers_State((int *) &state, -1, actor->player) && state == 0x63) {
        FieldActor_RequestState63(actor, 6, -1);
        SavedFlag_Set(&actor->saved.left_early, 1);
        end_state63_effect(actor);
    } else if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_022103cc, FieldActor_EndState63Remote)

/* func_ov003_02210474: for the actor of this console: it moves on once the animation is over.
 * The saved flag is cleared, and from frame 0x21 on, when FieldActor_ResumeMoving leaves the
 * state, it is set and the effect ends. */
void FieldActor_EndState63Local(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        move_on(actor);
    }
    SavedFlag_Set(&actor->saved.left_early, 0);
    if (anim_frame(actor) >= 0x21 && FieldActor_ResumeMoving(actor)) {
        SavedFlag_Set(&actor->saved.left_early, 1);
        end_state63_effect(actor);
    }
}
CLEAN_AS(func_ov003_02210474, FieldActor_EndState63Local)

/* func_ov003_02210504: from frame 5 to 0x23 the effect follows the point at 0x62c (through
 * func_0203f7d0): the first of those frames starts it (0x26, with sound 0x854) and leaves the
 * point ahead of the actor and flag 1 for other code (02260558, 02260540). On frame 0x14
 * func_0200ff28 acts on the point ahead (mode 1, tool 5); on frame 0x23 the effect ends. */
void FieldActor_RunState63(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    int frame = anim_frame(actor);
    if (frame < 5 || frame > 0x23) {
        return;
    }
    Vec3 at = actor->unk_62C;
    Globe_Unbend(&at, &at);
    if (STATE63_EFFECT(actor) == -1) {
        STATE63_EFFECT(actor) = EffectSystem_StartKind(0x26, &at, &actor->yaw, 0);
        FieldActor_PlaySound(actor, 0x854);
        Vec3 ahead;
        FieldActor_PointAheadOfSelf(&ahead, actor);
        data_ov003_02260540 = 1;
        data_ov003_02260558 = ahead;
    } else {
        EffectSystem_MoveHandle(STATE63_EFFECT(actor), &at, NULL, 0);
    }
    if (frame == 0x14) {
        Vec3 ahead;
        FieldActor_PointAheadOfSelf(&ahead, actor);
        FieldActor_FindTarget(actor, &ahead, 1, 5);
    } else if (frame == 0x23) {
        end_state63_effect(actor);
    }
}
CLEAN_AS(func_ov003_02210504, FieldActor_RunState63)

/* func_ov003_022105ec: leaving state 0x63: the effect ends, and flag 0 and the point ahead of
 * the actor are left for other code (02260540, 02260558).
 * QUIRK: the effect's handle is not reset to -1. */
void FieldActor_ExitState63(FieldActor *actor)
{
    if (STATE63_EFFECT(actor) != -1) {
        EffectSystem_EndHandle(STATE63_EFFECT(actor));
    }
    Vec3 ahead;
    FieldActor_PointAheadOfSelf(&ahead, actor);
    data_ov003_02260540 = 0;
    data_ov003_02260558 = ahead;
}
CLEAN_AS(func_ov003_022105ec, FieldActor_ExitState63)

/* func_ov003_02210634: state 0x63's message handler: state 0x63 is asked for again, priority
 * 6. */
void FieldActor_State63Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState63(actor, 6, arg);
}
CLEAN_AS(func_ov003_02210634, FieldActor_State63Message)

/* func_ov003_02210640: entering state 0x63: animation 0x61, no effect yet. */
void FieldActor_EnterState63(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x61, 3, 0);
    STATE63_EFFECT(actor) = -1;
}
CLEAN_AS(func_ov003_02210640, FieldActor_EnterState63)

/* func_ov003_02210660 */
void SavedFlag_Get(const u8 *saved, u8 *value)
{
    *value = *saved;
}
CLEAN_AS(func_ov003_02210660, SavedFlag_Get)

/* func_ov003_02210668 */
void SavedFlag_Set(u8 *saved, int value)
{
    *saved = (u8) value;
}
CLEAN_AS(func_ov003_02210668, SavedFlag_Set)

/* func_ov003_0221066c: asks for state 0x63; whether it was queued. */
int FieldActor_RequestState63(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x63, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221066c, FieldActor_RequestState63)

/* ---- State 0x62: animation 0x49 then 0x51, acting with an item on a tile */

/* func_ov003_022106a4: state 0x62's update: the actor turns towards the tile and moves to it. */
void FieldActor_UpdateState62(FieldActor *actor)
{
    FieldActor_TurnState62(actor);
    FieldActor_AnimateState62(actor);
    Vec3 point = actor->work.s62.point;
    FieldActor_FollowReportedTo(actor, &point);
    FieldActor_EnterContact(actor);
    FieldActor_EndState62(actor);
}
CLEAN_AS(func_ov003_022106a4, FieldActor_UpdateState62)

/* func_ov003_022106e4: when the animation is over: after animation 0x49 comes 0x51; after
 * that the state after this one is noted and the kind decides: 1 func_0200c9a8 (3, priority 5);
 * 3 for the actor of this console, the receiver released (flag 0x11) and func_02008380; any
 * other func_0200d4e8. */
void FieldActor_EndState62(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x49) {
        FieldActor_PlayAnimationOnce(actor, 0x51, 3, 0);
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    u8 kind = actor->work.s62.kind;
    if (kind == 1) {
        FieldActor_RequestState5(actor, 3, 5, -1);
        return;
    }
    if (is_local_player(actor) && kind == 3) {
        release_receiver(actor);
        FieldActor_RequestState90(actor, 3, 1, -1);
    } else {
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_022106e4, FieldActor_EndState62)

/* func_ov003_022107ac: except during animation 0x49, by frame: 1 effect 9 at the point (at the
 * actor's yaw); 5 the point goes to func_ov003_022211bc for the actor of this console, or, for
 * another's, to func_ov003_02221150 when the map object there is 0xfc or 0xfd, and flag 0x1c is
 * cleared; 7 sound 0x843 and flag 9; 0x15 effect 0xa at the point.
 * REQUIRES: func_0204f5a8 finds a map object at the point (the ROM reads it unchecked). */
void FieldActor_AnimateState62(FieldActor *actor)
{
    if (actor->animation != 0x49) {
        Vec3 point = actor->work.s62.point;
        s16 yaw = actor->yaw;
        switch (anim_frame(actor)) {
            case 1:
                EffectSystem_StartKind(9, &point, &yaw, 0);
                break;
            case 5:
                if (is_local_player(actor)) {
                    Vec3 copy = point;
                    TileEvent_StartUnitKind3(actor->player, &copy);
                } else {
                    u16 *object = AcreTile_ItemAt(data_021c80bc, &point, 0);
                    if (in_range(*object, 0xfc, 0xfd)) {
                        Vec3 copy = point;
                        TileEvent_StartKind3(actor->player, &copy);
                    }
                }
                FieldActor_ClearFlag(actor, 0x1c);
                break;
            case 7:
                FieldActor_PlaySound(actor, 0x843);
                FieldActor_SetFlag(actor, 9);
                break;
            case 0x15:
                EffectSystem_StartKind(0xa, &point, NULL, 0);
                break;
            default:
                break;
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov003_022107ac, FieldActor_AnimateState62)

/* func_ov003_022108b0 */
void FieldActor_TurnState62(FieldActor *actor)
{
    FieldActor_TurnTowards(actor, actor->work.s62.yaw);
}
CLEAN_AS(func_ov003_022108b0, FieldActor_TurnState62)

/* func_ov003_022108c0: leaving state 0x62: another player's actor with flag 0x1c still set
 * sends the point on as frame 5 would have, and the flag is cleared.
 * QUIRK: whose actor it is gets asked a second time, and the answer, always "another's" here,
 * picks func_ov003_02221150 (without the map object check). */
void FieldActor_ExitState62(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    Vec3 point = actor->work.s62.point;
    if (is_local_player(actor)) {
        TileEvent_StartUnitKind3(actor->player, &point);
    } else {
        TileEvent_StartKind3(actor->player, &point);
    }
    FieldActor_ClearFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_022108c0, FieldActor_ExitState62)

/* func_ov003_0221094c: state 0x62's message handler: messages are ignored. */
void FieldActor_State62Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0221094c, FieldActor_State62Message)

/* func_ov003_02210950: entering state 0x62: the request's item and kind, the middle of its
 * tile and the yaw towards it are kept. Animation 0x49 starts, unless it is playing already
 * (then 0x51 follows once it is over) or animation 0x4a is (0x51 at once). Flag 0xd is cleared
 * and 0x1c set. */
void FieldActor_EnterState62(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const ItemTileArgs *args = (const ItemTileArgs *) (const void *) request->payload;
    State62Work *work = &actor->work.s62;
    u8 kind = args->kind;
    Vec3 point;

    AcreTile_TileCentre(&point, args->x, args->z);
    work->item = args->item;
    work->kind = kind;
    work->point = point;
    work->yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    if (actor->animation == 0x49) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FieldActor_PlayAnimationOnce(actor, 0x51, 3, 0);
        }
    } else if (actor->animation == 0x4a) {
        FieldActor_PlayAnimationOnce(actor, 0x51, 3, 0);
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x49, 3, 0);
    }
    FieldActor_ClearFlag(actor, 0xd);
    FieldActor_SetFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02210950, FieldActor_EnterState62)

/* func_ov003_022109f8: asks for state 0x62 with a kind, a tile and an item; whether it was
 * queued. */
void *FieldActor_RequestState62(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x62, (int) priority, arg);
    ItemTileArgs *args = (ItemTileArgs *) (void *) request.payload;
    args->kind = (u8) kind;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->item = item;
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_022109f8, FieldActor_RequestState62)

/* ---- State 0x61: animation 0x49 then 0x4a, turning towards a tile before state 0x62 */

/* func_ov003_02210a44: state 0x61's update. */
void FieldActor_UpdateState61(FieldActor *actor)
{
    FieldActor_TurnState61(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState61(actor);
}
CLEAN_AS(func_ov003_02210a44, FieldActor_UpdateState61)

/* func_ov003_02210a64: another player's actor only notes the state after this one. The actor of
 * this console marks `done` when the word at 0x818 is 1; when the animation is over animation
 * 0x4a starts, and during it (or at that end) the actor goes on to state 0x62 with the same
 * kind, tile and item, unless the kind is 2 and nothing is done yet. */
void FieldActor_EndState61(FieldActor *actor)
{
    State61Work *work = &actor->work.s61;

    if (!is_local_player(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return;
    }
    if (actor->unk_818 == 1) {
        work->done = 1;
    }
    if (FrameCtrl_IsDone(&actor->anim) || actor->animation == 0x4a) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FieldActor_PlayAnimationLoop(actor, 0x4a, 3, 0);
        }
        if (work->kind != 2 || work->done != 0) {
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            u32 tile[2] = {work->x, work->z};
            FieldActor_RequestState62(actor, work->kind, tile, work->item, 6, -1);
        }
    }
}
CLEAN_AS(func_ov003_02210a64, FieldActor_EndState61)

/* func_ov003_02210b28 */
void FieldActor_TurnState61(FieldActor *actor)
{
    FieldActor_TurnTowards(actor, actor->work.s61.yaw);
}
CLEAN_AS(func_ov003_02210b28, FieldActor_TurnState61)

/* func_ov003_02210b38: state 0x61's message handler: messages are ignored. */
void FieldActor_State61Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02210b38, FieldActor_State61Message)

/* func_ov003_02210b3c: entering state 0x61: with kind 2 the actor of this console gets a target
 * from func_02043d18 for its item; another kind turns into 3 during animation 0x6c. The item,
 * the yaw towards the tile's middle, the kind and the tile are kept and saved, animation 0x49
 * starts and flag 0xd is cleared. */
void FieldActor_EnterState61(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const ItemTileArgs *args = (const ItemTileArgs *) (const void *) request->payload;
    State61Work *work = &actor->work.s61;
    int kind = args->kind;
    u8 x = args->x;
    u8 z = args->z;
    Vec3 point;

    AcreTile_TileCentre(&point, x, z);
    u16 item = args->item;
    if (kind == 2) {
        if (is_local_player(actor)) {
            actor->target = TileRequests_AskAtActorTileOpFor(actor->player, 2, 0, actor->item);
        }
    } else if (actor->animation == 0x6c) {
        kind = 3;
    }
    work->item = item;
    work->x = x;
    work->z = z;
    work->kind = (u8) kind;
    work->done = 0;
    work->yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    SavedItemTile_Set(&actor->saved.item_tile, item, (char) x, (char) z, (u8) kind);
    FieldActor_PlayAnimationOnce(actor, 0x49, 7, 0);
    FieldActor_ClearFlag(actor, 0xd);
}
CLEAN_AS(func_ov003_02210b3c, FieldActor_EnterState61)

/* func_ov003_02210c08 */
void SavedItemTile_Set(SavedItemTile *saved, int item, char x, char z, u8 kind)
{
    PackedBytes_WriteItem(saved->item, item);
    saved->x = (u8) x;
    saved->z = (u8) z;
    saved->kind = kind;
}
CLEAN_AS(func_ov003_02210c08, SavedItemTile_Set)

/* func_ov003_02210c24: asks for state 0x61 with a kind, a tile and an item; whether it was
 * queued. */
void *FieldActor_RequestState61(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x61, (int) priority, arg);
    ItemTileArgs *args = (ItemTileArgs *) (void *) request.payload;
    args->item = item;
    args->kind = (u8) kind;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02210c24, FieldActor_RequestState61)

/* ---- State 0x60: animation 0x50 shrinking the actor, then 0x6c */

/* func_ov003_02210c70: state 0x60's update. */
void FieldActor_UpdateState60(FieldActor *actor)
{
    FieldActor_ScaleState60(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState60(actor);
}
CLEAN_AS(func_ov003_02210c70, FieldActor_UpdateState60)

/* func_ov003_02210c8c: by `step`:
 *   0: once the animation is over the actor moves on, and the actor of this console runs
 *      func_0209a110 on its item;
 *   1: after animation 0x50 animation 0x6c starts. Another player's actor notes the state after
 *      this one and flag 0xd is cleared. The actor of this console follows the word at 0x81c:
 *      at 5 it becomes 6 once func_0206f6b0 accepts the item; at 6, once group 9 can open, it
 *      becomes 0xf and, when GroupParams_C4CIs1, the actor moves on (flag 0xd cleared, the
 *      receiver released, func_0203e19c). Otherwise from 0xf on the receiver is released,
 *      func_0203e19c runs and `step` goes on;
 *   2: once no target is held, state 0x61 (kind 2) is asked for with the tile and the item, and
 *      flag 0xd is cleared. */
void FieldActor_RunState60(FieldActor *actor)
{
    TileStepArgs *work = &actor->work.s60;

    switch (work->step) {
        case 0:
            if (!FrameCtrl_IsDone(&actor->anim)) {
                break;
            }
            move_on(actor);
            if (is_local_player(actor)) {
                CurrentPockets_Receive(&actor->item);
            }
            break;
        case 1:
            if (actor->animation == 0x50) {
                if (!FrameCtrl_IsDone(&actor->anim)) {
                    break;
                }
                FieldActor_PlayAnimationLoop(actor, 0x6c, 3, 3);
            }
            if (!is_local_player(actor)) {
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                FieldActor_ClearFlag(actor, 0xd);
                break;
            }
            if (actor->unk_81C == 5) {
                if (GroupParams_OpenWithItem2a(actor->item)) {
                    actor->unk_81C = 6;
                }
                break;
            }
            if (actor->unk_81C == 6) {
                if (!GroupParams_CanOpen()) {
                    break;
                }
                actor->unk_81C = 0xf;
                if (GroupParams_C4CIs1()) {
                    FieldActor_ClearFlag(actor, 0xd);
                    release_receiver(actor);
                    EventQueue_FinishKind9();
                    move_on(actor);
                    break;
                }
            } else if (actor->unk_81C < 0xf) {
                break;
            }
            release_receiver(actor);
            EventQueue_FinishKind9();
            work->step++;
            break;
        case 2: {
            if (actor->target != -1) {
                break;
            }
            u32 tile[2] = {work->x, work->z};
            FieldActor_RequestState61(actor, 2, tile, actor->item, 6, -1);
            FieldActor_ClearFlag(actor, 0xd);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02210c8c, FieldActor_RunState60)

/* func_ov003_02210e4c: during animation 0x50 the actor shrinks from 1.0 by a sixth per frame
 * (func_0200f650 and the three words at 0x830); at 0 flag 0xd is cleared. Other animations
 * leave it at 0. */
void FieldActor_ScaleState60(FieldActor *actor)
{
    fx32 scale = 0;

    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x50) {
        scale = 0x1000 - (anim_frame(actor) << 12) / 6;
        if (scale < 0) {
            scale = 0;
            FieldActor_ClearFlag(actor, 13);
        }
    }
    actor->unk_830[0] = scale;
    actor->unk_830[1] = scale;
    actor->unk_830[2] = scale;
    FieldActor_EasePoint824(actor, scale);
}
CLEAN_AS(func_ov003_02210e4c, FieldActor_ScaleState60)

/* func_ov003_02210eb8: state 0x60's message handler: state 0x60 is asked for again with the
 * saved tile and step, priority 6. */
void FieldActor_State60Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;
    u8 step;

    TileStepArgs_Get(&actor->saved.tile_step, &x, &z, &step);
    int tile[2] = {x, z};
    FieldActor_RequestState60(actor, tile, step, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02210eb8, FieldActor_State60Message)

/* func_ov003_02210ef8: entering state 0x60: the request's tile and step are kept and saved,
 * animation 0x50 starts and sound 0x4f plays. */
void FieldActor_EnterState60(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileStepArgs *args = (const TileStepArgs *) (const void *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    u8 step = args->step;

    actor->work.s60.step = step;
    actor->work.s60.x = x;
    actor->work.s60.z = z;
    TileStepArgs_Set(&actor->saved.tile_step, x, z, step);
    FieldActor_PlayAnimationOnce(actor, 0x50, 3, 0);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_02210ef8, FieldActor_EnterState60)

/* func_ov003_02210f3c */
void TileStepArgs_Get(const TileStepArgs *args, u8 *x, u8 *z, u8 *step)
{
    *x = args->x;
    *z = args->z;
    *step = args->step;
}
CLEAN_AS(func_ov003_02210f3c, TileStepArgs_Get)

/* func_ov003_02210f50 */
void TileStepArgs_Set(TileStepArgs *args, int x, int z, int step)
{
    args->x = (u8) x;
    args->z = (u8) z;
    args->step = (u8) step;
}
CLEAN_AS(func_ov003_02210f50, TileStepArgs_Set)

/* func_ov003_02210f58: asks for state 0x60 with a tile and the step to start at; whether it was
 * queued. */
int FieldActor_RequestState60(FieldActor *actor, const int *tile, int step, int priority, s16 arg)
{
    const u8 payload[3] = {(u8) tile[0], (u8) tile[1], (u8) step};
    return request_state(actor, 0x60, priority, arg, payload, 3);
}
CLEAN_AS(func_ov003_02210f58, FieldActor_RequestState60)

/* ---- State 0x5f: animation 0x49 or 0x4f acting with an item on a point, then state 0x60 */

/* func_ov003_02210fa0: state 0x5f's update: the actor of this console moves from frame 0x19
 * on (func_0201100c); another player's actor moves to the point. */
void FieldActor_UpdateState5F(FieldActor *actor)
{
    FieldActor_AnimateState5F(actor);
    if (is_local_player(actor)) {
        if (anim_frame(actor) >= 0x19) {
            FieldActor_MoveWithCollision(actor);
        }
    } else {
        Vec3 point = actor->work.s5f.point;
        FieldActor_FollowReportedTo(actor, &point);
    }
    FieldActor_EnterContact(actor);
    FieldActor_RunState5F(actor);
}
CLEAN_AS(func_ov003_02210fa0, FieldActor_UpdateState5F)

/* State 0x60 at the tile of state 0x5f's point, with a step. */
static void request_state60_at_point(FieldActor *actor, int step)
{
    int tile[2] = {0, 0};
    Vec3 point = actor->work.s5f.point;
    Position_Tile(&tile[0], &tile[1], (const Position *) &point);
    FieldActor_RequestState60(actor, tile, step, 6, -1);
}

/* func_ov003_0221100c: animation 0x49 is followed by 0x4f. Otherwise the actor of this console
 * runs func_0203ae98 on frame 0x13; from frame 0x19, once the actor faces yaw 0 (func_0200faf0,
 * 0x400) and the animation is over, another player's actor clears flag 0x12 and notes the state
 * after this one, and the actor of this console goes by `step`:
 *   0: once func_0203e1c4 allows, the receiver at 0xec is registered as "obj_etc_player" (flag
 *      0x11) with byte 0x1e: 0x21 for item 0x136a the first time (record flag 0x27), 0x23 for
 *      item 0x137b the first time (record flag 0x28), else 1 with the item's text handed to
 *      the link (func_02062f90, func_020683b4 kind 7); the link's request is raised, sounds are
 *      set up and the word at 0x81c becomes 10; then 1;
 *   1: once the link reports itself open, 2;
 *   2: when func_02099fe8 gives -1, 3 with the word at 0x81c at 2; else once the link is
 *      closed the receiver is released and state 0x60 is asked for at the point's tile with
 *      step 0;
 *   3: when the word at 0x81c is 0xf or more, 4; else once the link is closed the receiver is
 *      released and state 0x60 is asked for with step 1;
 *   4: once the link is closed and group 9 can open, the receiver is released; then 5;
 *   5: once no target is held, state 0x61 (kind 2) is asked for at the point's tile with the
 *      item.
 * REQUIRES: the link is set when `step` is 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState5F(FieldActor *actor)
{
    State5FWork *work = &actor->work.s5f;

    if (actor->animation == 0x49) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FieldActor_PlayAnimationOnce(actor, 0x4f, 3, 0);
        }
        return;
    }
    int frame = anim_frame(actor);
    if (is_local_player(actor) && FrameCtrl_Passed(&actor->anim, 0x13)) {
        CameraControl_SetMode4();
    }
    if (frame < 0x19) {
        return;
    }
    if (!FieldActor_TurnToZero(actor, 0x400)) {
        return;
    }
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (!is_local_player(actor)) {
        FieldActor_ClearFlag(actor, 0x12);
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return;
    }

    switch (work->step) {
        case 0: {
            if (EventQueue_RequestKind9() == 0) {
                return;
            }
            work->step = 1;
            SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
            FieldActor_SetFlag(actor, 0x11);
            void *record = PlayerRecords_Current();
            MessageReceiver_SetName((MessageReceiver *) actor->receiver, data_ov003_02238134);
            if (actor->item == 0x136a && !PlayerRecord_TestFlag(record, 0x27)) {
                actor->receiver_unk_1E = 0x21;
                PlayerRecord_SetFlag(record, 0x27);
            } else if (actor->item == 0x137b && !PlayerRecord_TestFlag(record, 0x28)) {
                actor->receiver_unk_1E = 0x23;
                PlayerRecord_SetFlag(record, 0x28);
            } else {
                u8 text[0x28];
                actor->receiver_unk_1E = 1;
                NameText_ConstructItem((NameText *) text, &actor->item);
                TalkObject_SetValue((TalkObject *) actor->link, 0, (TextBase *) text, 7);
                NameText_Destruct((NameText *) text);
            }
            actor->link->requested = 1;
            Music_DropPriority(0x12);
            Music_AddValue(0xc, 0, 1);
            Music_Add(0xd, 0x39, 0x7f, 1);
            actor->unk_81C = 10;
            break;
        }
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                work->step = 2;
            }
            break;
        case 2:
            if (CurrentPockets_FreeSlot() == -1) {
                work->step = 3;
                actor->unk_81C = 2;
                break;
            }
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
            FieldActor_ClearFlag(actor, 0x11);
            EventQueue_FinishKind9();
            request_state60_at_point(actor, 0);
            CameraControl_ResetMode();
            break;
        case 3:
            if (actor->unk_81C >= 0xf) {
                work->step = 4;
                break;
            }
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
            FieldActor_ClearFlag(actor, 0x11);
            request_state60_at_point(actor, 1);
            CameraControl_ResetMode();
            break;
        case 4:
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            if (!GroupParams_CanOpen()) {
                break;
            }
            SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
            FieldActor_ClearFlag(actor, 0x11);
            EventQueue_FinishKind9();
            work->step = 5;
            break;
        case 5: {
            if (actor->target != -1) {
                break;
            }
            int tile[2] = {0, 0};
            Vec3 point = work->point;
            Position_Tile(&tile[0], &tile[1], (const Position *) &point);
            u32 at[2] = {(u32) tile[0], (u32) tile[1]};
            FieldActor_RequestState61(actor, 2, at, actor->item, 6, -1);
            CameraControl_ResetMode();
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221100c, FieldActor_RunState5F)

/* func_ov003_0221138c: except during animation 0x49, by frame: 5 effect 6 at the point; 6
 * sound 0x841 and flag 9; 0xc effect 8 at the point, func_02030db8 for its tile, the point and
 * kind to func_ov003_02221294, flag 0xd set and 0x1c cleared. From frame 0x18 on flag 9 is
 * cleared and func_0200ee40 and func_0200f650 (1.0) run with the words at 0xc4 to 0xd0, 0x298
 * and 0x698 kept across them; before it the point at 0x62c goes through func_0203f7d0 into
 * 0x824. */
void FieldActor_AnimateState5F(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x49) {
        return;
    }
    Vec3 point = actor->work.s5f.point;
    switch (anim_frame(actor)) {
        case 5:
            EffectSystem_StartKind(6, &point, NULL, 0);
            break;
        case 6:
            FieldActor_PlaySound(actor, 0x841);
            FieldActor_SetFlag(actor, 9);
            break;
        case 0xc: {
            int x;
            int z;
            EffectSystem_StartKind(8, &point, NULL, 0);
            Position_Tile(&x, &z, (const Position *) &point);
            CollisionMap_AddExtraPost(x, z);
            Vec3 copy = point;
            TileEvent_StartUnitKind1(actor->player, &copy, actor->work.s5f.kind);
            FieldActor_SetFlag(actor, 0xd);
            FieldActor_ClearFlag(actor, 0x1c);
            break;
        }
        default:
            break;
    }
    if (anim_frame(actor) >= 0x18) {
        FieldActor_ClearFlag(actor, 9);
        Vec3 kept_0C4 = actor->unk_0C4;
        s16 kept_0D0 = actor->unk_0D0;
        FieldActorBlock48 kept_298 = actor->unk_298;
        FieldActorBlock48 kept_698 = actor->unk_698;
        FieldActor_RebuildPose(actor);
        FieldActor_EasePoint824(actor, 0x1000);
        actor->unk_0C4 = kept_0C4;
        actor->unk_0D0 = kept_0D0;
        actor->unk_298 = kept_298;
        actor->unk_698 = kept_698;
    } else {
        actor->unk_824 = actor->unk_62C;
        Globe_Unbend(&actor->unk_824, &actor->unk_824);
    }
}
CLEAN_AS(func_ov003_0221138c, FieldActor_AnimateState5F)

/* func_ov003_02211530: leaving state 0x5f for `next`: another player's actor with flag 0x1c
 * still set sends the point and kind on as frame 0xc would have (flags 0x1c and 9 cleared), and
 * leaving for neither state 0x60 nor 0x61 clears flag 0xd. */
void FieldActor_ExitState5F(FieldActor *actor, int next)
{
    if (is_local_player(actor)) {
        return;
    }
    if (FieldActor_TestFlag(actor, 0x1c)) {
        Vec3 point = actor->work.s5f.point;
        TileEvent_StartUnitKind1(actor->player, &point, actor->work.s5f.kind);
        FieldActor_ClearFlag(actor, 0x1c);
        FieldActor_ClearFlag(actor, 9);
    }
    if (next != 0x60 && next != 0x61) {
        FieldActor_ClearFlag(actor, 0xd);
    }
}
CLEAN_AS(func_ov003_02211530, FieldActor_ExitState5F)

/* func_ov003_022115a4: state 0x5f's message handler: in state 0 only, state 0x5f is asked for
 * again at the middle of the saved tile with the saved item and kind, priority 6. */
void FieldActor_State5FMessage(FieldActor *actor, int arg)
{
    if (actor->state != 0) {
        return;
    }
    u32 tile[2] = {0, 0};
    u16 item;
    u8 kind;
    SavedItemTile_Get(&actor->saved.item_tile, tile, &item, &kind);
    Vec3 point;
    AcreTile_TileCentre(&point, tile[0], tile[1]);
    FieldActor_RequestState5F(actor, &point, item, kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022115a4, FieldActor_State5FMessage)

/* func_ov003_02211604: entering state 0x5f: the request's point and kind are kept (step 0).
 * Animation 0x4f starts when 0x49 or 0x4a is playing or an item is given, else 0x49. The point
 * at 0x62c goes through func_0203f7d0 into 0x824, the words at 0x830 become 1.0 and flag 0xd is
 * cleared; the point's tile, the actor's item and the kind are saved. With an item given it
 * becomes the actor's item, and on map object 0xfc or 0xfd the animation jumps to its last
 * frame and flag 0xd is set. Without one, when the actor holds nothing or is another player's,
 * the map object's code (ITEM_NONE without one) becomes its item. The actor of this console
 * runs func_02035684 and, with item 0x1549, func_02079750. Then the word at 0x81c is 7 and
 * flag 0x1c is set.
 * REQUIRES: with an item given, func_0204f5e0 finds a map object for the tile (the ROM reads it
 * unchecked there). */
void FieldActor_EnterState5F(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const PointItemArgs *args = (const PointItemArgs *) (const void *) request->payload;
    State5FWork *work = &actor->work.s5f;
    Vec3 point = args->point;
    u16 item = args->item;
    int kind = args->kind;

    work->step = 0;
    work->point = point;
    work->kind = (u8) kind;
    if (actor->animation == 0x49 || actor->animation == 0x4a || !item_is_nothing(&item)) {
        FieldActor_PlayAnimationOnce(actor, 0x4f, 3, 0);
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x49, 3, 0);
    }
    actor->unk_824 = actor->unk_62C;
    Globe_Unbend(&actor->unk_824, &actor->unk_824);
    actor->unk_830[0] = 0x1000;
    actor->unk_830[1] = 0x1000;
    actor->unk_830[2] = 0x1000;
    FieldActor_ClearFlag(actor, 0xd);

    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) &point);
    SavedItemTile_SetTile(&actor->saved.item_tile, tile, actor->item, kind);
    u16 *object = map_object_at(tile[0], tile[1]);
    if (!item_is_nothing(&item)) {
        actor->unk_822 = item;
        actor->item = item;
        if (in_range(*object, 0xfc, 0xfd)) {
            /* QUIRK: the whole frames of the frame count are taken to 16 bits, and none of them
             * wraps to frame 0xffff. */
            u16 frames = (u16) ((u32) actor->anim.end >> 12);
            actor->anim.frame = (fx32) ((u32) (u16) (frames - 1) << 12);
            FieldActor_SetFlag(actor, 0xd);
        }
    } else if (item_is_nothing(&actor->item) || !is_local_player(actor)) {
        u16 code = object != NULL ? *object : ITEM_NONE;
        actor->unk_822 = code;
        actor->item = code;
    }
    if (is_local_player(actor)) {
        Music_AddValue(0x12, 0xf, 0);
        if (actor->item == 0x1549) {
            VillagerEvent_Item1549(&actor->position);
        }
    }
    actor->unk_81C = 7;
    FieldActor_SetFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211604, FieldActor_EnterState5F)

/* func_ov003_022118b8 */
void SavedItemTile_Get(const SavedItemTile *saved, u32 *tile, u16 *item, u8 *kind)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
    *item = PackedBytes_ReadItem(saved->item);
    *kind = saved->kind;
}
CLEAN_AS(func_ov003_022118b8, SavedItemTile_Get)

/* func_ov003_022118d8 */
void SavedItemTile_SetTile(SavedItemTile *saved, const int *tile, int item, int kind)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
    PackedBytes_WriteItem(saved->item, item);
    saved->kind = (u8) kind;
}
CLEAN_AS(func_ov003_022118d8, SavedItemTile_SetTile)

/* func_ov003_022118f8: asks for state 0x5f with a point, an item and a kind; for another
 * player's actor the item at 0x820 and 0x822 is cleared first. Whether it was queued. */
int FieldActor_RequestState5F(FieldActor *actor, const Vec3 *point, int item, int kind, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5f, priority, arg);
    Vec3 copy = *point;
    PointItemArgs_Set((PointItemArgs *) (void *) request.payload, &copy, (u16) item, (u8) kind);
    if (!is_local_player(actor)) {
        actor->unk_822 = ITEM_NONE;
        actor->item = ITEM_NONE;
    }
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022118f8, FieldActor_RequestState5F)

/* func_ov003_02211980: asks for state 0x5f with a point and a kind and no item; whether it was
 * queued. */
int FieldActor_RequestState5FNoItem(FieldActor *actor, const Vec3 *point, int kind, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5f, priority, arg);
    Vec3 copy = *point;
    PointItemArgs_Set((PointItemArgs *) (void *) request.payload, &copy, ITEM_NONE, (u8) kind);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02211980, FieldActor_RequestState5FNoItem)

/* func_ov003_022119d8 */
void PointItemArgs_Set(PointItemArgs *args, const Vec3 *point, u16 item, u8 kind)
{
    /* Word by word, x first, as the original copies (it matters only when the two overlap). */
    args->point.x = point->x;
    args->point.y = point->y;
    args->point.z = point->z;
    args->item = item;
    args->kind = kind;
}
CLEAN_AS(func_ov003_022119d8, PointItemArgs_Set)

/* ---- State 0x5e: animation 0x49, then 0x4b or 0x4e, at a point */

/* func_ov003_022119f0: state 0x5e's update: the actor of this console moves (func_0201100c);
 * another player's actor moves to the point. */
void FieldActor_UpdateState5E(FieldActor *actor)
{
    FieldActor_AnimateState5E(actor);
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
    } else {
        Vec3 point = actor->work.s5e.point;
        FieldActor_FollowReportedTo(actor, &point);
    }
    FieldActor_EnterContact(actor);
    FieldActor_EndState5E(actor);
}
CLEAN_AS(func_ov003_022119f0, FieldActor_UpdateState5E)

/* func_ov003_02211a4c: when the animation is over: after animation 0x49 comes 0x4e when the
 * work's flag is set, else 0x4b; after those the actor moves on. */
void FieldActor_EndState5E(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x49) {
        if (actor->work.s5e.flag != 0) {
            FieldActor_PlayAnimationOnce(actor, 0x4e, 3, 0);
        } else {
            FieldActor_PlayAnimationOnce(actor, 0x4b, 3, 0);
        }
    } else {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02211a4c, FieldActor_EndState5E)

/* func_ov003_02211ac0: except during animation 0x49, by frame. During animation 0x4b: 2 effect
 * 6 at the point; 5 sound 0x841 and flag 9; 7 effect 7 at the point (at the actor's yaw), the
 * point to func_ov003_02221294 (kind 0), flag 0x1c cleared and func_02030db8 for its tile.
 * During the others: 5 sound 0x85b and flag 9; 12 effect 6; 18 effect 8 (at the yaw); 21 the
 * point and yaw to func_ov003_02220f40, the point to func_ov003_02221294, sound 0x85c and flag
 * 0x1c cleared. */
void FieldActor_AnimateState5E(FieldActor *actor)
{
    if (actor->animation != 0x49) {
        Vec3 point = actor->work.s5e.point;
        s16 yaw = actor->yaw;
        if (actor->animation == 0x4b) {
            switch (anim_frame(actor)) {
                case 2:
                    EffectSystem_StartKind(6, &point, NULL, 0);
                    break;
                case 5:
                    FieldActor_PlaySound(actor, 0x841);
                    FieldActor_SetFlag(actor, 9);
                    break;
                case 7: {
                    int x;
                    int z;
                    EffectSystem_StartKind(7, &point, &yaw, 0);
                    Vec3 copy = point;
                    TileEvent_StartUnitKind1(actor->player, &copy, 0);
                    FieldActor_ClearFlag(actor, 0x1c);
                    Position_Tile(&x, &z, (const Position *) &point);
                    CollisionMap_AddExtraPost(x, z);
                    break;
                }
                default:
                    break;
            }
        } else {
            switch (anim_frame(actor)) {
                case 5:
                    FieldActor_PlaySound(actor, 0x85b);
                    FieldActor_SetFlag(actor, 9);
                    break;
                case 12:
                    EffectSystem_StartKind(6, &point, NULL, 0);
                    break;
                case 18:
                    EffectSystem_StartKind(8, &point, &yaw, 0);
                    break;
                case 21: {
                    Vec3 copy = point;
                    TileEvent_StartKind8(actor->player, &copy, actor->yaw);
                    Vec3 copy2 = point;
                    TileEvent_StartUnitKind1(actor->player, &copy2, 0);
                    FieldActor_PlaySound(actor, 0x85c);
                    FieldActor_ClearFlag(actor, 0x1c);
                    break;
                }
                default:
                    break;
            }
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov003_02211ac0, FieldActor_AnimateState5E)

/* func_ov003_02211c20: leaving state 0x5e: another player's actor with flag 0x1c still set
 * sends the point on as the animation would have (during 0x4b to func_ov003_02221294 only;
 * otherwise first with the yaw to func_ov003_02220f40), and the flag is cleared. */
void FieldActor_ExitState5E(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    Vec3 point = actor->work.s5e.point;
    if (actor->animation == 0x4b) {
        Vec3 copy = point;
        TileEvent_StartUnitKind1(actor->player, &copy, 0);
    } else {
        Vec3 copy = point;
        TileEvent_StartKind8(actor->player, &copy, actor->yaw);
        Vec3 copy2 = point;
        TileEvent_StartUnitKind1(actor->player, &copy2, 0);
    }
    FieldActor_ClearFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211c20, FieldActor_ExitState5E)

/* func_ov003_02211cbc: state 0x5e's message handler: nothing. */
void FieldActor_State5EMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02211cbc, FieldActor_State5EMessage)

/* func_ov003_02211cc0: entering state 0x5e: the request's flag and point become the work.
 * Coming from animation 0x49 or 0x4a, animation 0x4e (with the flag) or 0x4b follows at once;
 * otherwise animation 0x49 starts. Flag 0x1c is set. */
void FieldActor_EnterState5E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State5EWork *args = (const State5EWork *) (const void *) request->payload;
    Vec3 point = args->point;

    State5EWork_Set(&actor->work.s5e, (char) args->flag, &point);
    if (actor->animation == 0x49 || actor->animation == 0x4a) {
        if (actor->work.s5e.flag != 0) {
            FieldActor_PlayAnimationOnce(actor, 0x4e, 3, 0);
        } else {
            FieldActor_PlayAnimationOnce(actor, 0x4b, 3, 0);
        }
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x49, 3, 0);
    }
    FieldActor_SetFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211cc0, FieldActor_EnterState5E)

/* func_ov003_02211d3c: returns `work`. */
State5EWork *State5EWork_Set(State5EWork *work, char flag, const Vec3 *point)
{
    work->flag = (u8) flag;
    copy_point(&work->point, point);
    return work;
}
CLEAN_AS(func_ov003_02211d3c, State5EWork_Set)

/* func_ov003_02211d4c: asks for state 0x5e with a flag and a point; whether it was queued. */
int FieldActor_RequestState5E(FieldActor *actor, int flag, const Vec3 *point, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5e, priority, arg);
    Vec3 copy = *point;
    State5EArgs_Set((State5EWork *) (void *) request.payload, (char) flag, &copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02211d4c, FieldActor_RequestState5E)

/* func_ov003_02211da0 */
void State5EArgs_Set(State5EWork *args, char flag, const Vec3 *point)
{
    args->flag = (u8) flag;
    copy_point(&args->point, point);
}
CLEAN_AS(func_ov003_02211da0, State5EArgs_Set)

/* ---- State 0x5d: animation 0x4c at a tile, with what was met there */

static_assert(offsetof(FieldActor, unk_14C) == 0x14c, "0x14c");
static_assert(offsetof(FieldActor, unk_1C4) == 0x1c4, "0x1c4");
static_assert(offsetof(FieldActor, work.s59.yaw) == 0x7e0, "state 0x59 yaw");
static_assert(offsetof(FieldActor, work.s59.fixed) == 0x7e2, "state 0x59 fixed");
static_assert(offsetof(FieldActor, work.s5a.has_target) == 0x7d6, "state 0x5a target");
static_assert(offsetof(FieldActor, saved.s5d.other_result) == 0x8f3, "state 0x5d saved");
static_assert(offsetof(FieldActor, saved.s58.angle) == 0x8f2, "state 0x58 angle");
static_assert(sizeof(State59Work) == 0x10, "state 0x59 work");
static_assert(sizeof(State5EWork) <= sizeof(((StateRequest *) 0)->payload), "state 0x5e payload");

/* The absolute value as the ARM computes it (-0x80000000 stays itself). */
static int abs32(int value)
{
    return value < 0 ? sub32(0, value) : value;
}

/* func_ov003_02211db0: state 0x5d's update. The speed at 0x98 slows by 0x9c a frame, towards 0,
 * and is stored negated. */
void FieldActor_UpdateState5D(FieldActor *actor)
{
    FieldActor_AnimateState5D(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    int speed = sub32(0, FieldActor_Slow(abs32(actor->unk_098), 0));
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState5D(actor);
}
CLEAN_AS(func_ov003_02211db0, FieldActor_UpdateState5D)

/* func_ov003_02211df8: at the animation's end the actor moves on. */
void FieldActor_EndState5D(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02211df8, FieldActor_EndState5D)

/* func_ov003_02211e38: on reaching frame 5: with the work's flag, the tile goes to
 * func_ov003_022241a4 and flags 0x12 and 0x1c are cleared; the speed becomes -0x333; on a map
 * object of a growth line ahead the tile ahead goes to func_ov003_02224384 (1); flag 9 is set.
 * Then a sound by what was met (other_result): nothing met (0) gives sound 0x7df when the map
 * object ahead is of kind 0 to 4 (outside 0xe3-0xfb and the growth lines) or of kind 10, 13 or
 * 14, else sound 0x844 and effect 5 0.8 ahead and 0.5 to the side of the actor; an object of
 * main's tables (2) is told the held item (its vtable slot 24) after sound 0x7df; an object of
 * overlay 3 (3) gets Snowman_Knock for the actor of this console, sound 0x7df when that
 * fails or for another player's actor; 1 gives sound 0x7df. What was met is forgotten. */
void FieldActor_AnimateState5D(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_Passed(&actor->anim, 5)) {
        return;
    }
    const TileFlagArgs *work = &actor->work.s5d;
    if (work->flag != 0) {
        int tile[2] = {work->x, work->z};
        TileEvent_StartFromChanges((const TileChangesTile *) tile);
        FieldActor_ClearFlag(actor, 0x12);
        FieldActor_ClearFlag(actor, 0x1c);
    }
    int speed = -0x333;
    FieldActor_SetSpeed(actor, &speed);

    Vec3 ahead;
    int x = 0;
    int z = 0;
    FieldActor_TileAhead(&ahead, actor);
    Position_Tile(&x, &z, (const Position *) &ahead);
    u16 *object = map_object_at(x, z);
    if (object != NULL && is_growth_object(*object)) {
        int tile[2] = {x, z};
        GrowthModel_RequestHit(actor->player, (const TileChangesTile *) tile, 1);
    }
    FieldActor_SetFlag(actor, 9);

    int object_kind = object != NULL ? (*object & 0xf000) >> 12 : 0xf;
    switch (actor->other_result) {
        case 0: {
            BOOL plain = FALSE;
            if (object != NULL) {
                if (object_kind <= 4 && !in_range(*object, 0xe3, 0xfb) && !is_growth_object(*object)) {
                    plain = TRUE;
                } else if (object_kind == 10 || object_kind == 13 || object_kind == 14) {
                    plain = TRUE;
                }
            }
            if (plain) {
                FieldActor_PlaySound(actor, 0x7df);
                break;
            }
            FieldActor_PlaySound(actor, 0x844);
            Vec3 at = actor->position;
            s16 angle = actor->yaw;
            int index = ((u16) angle >> 4) * 2;
            fx32 sine = FX_SinCosTable_[index];
            fx32 cosine = FX_SinCosTable_[index + 1];
            fx32 forward_z = FX_MulFunc(cosine, 0xccd);
            fx32 side_z = FX_MulFunc(sine, 0x800);
            fx32 dz = sub32(forward_z, side_z);
            fx32 forward_x = FX_MulFunc(sine, 0xccd);
            fx32 side_x = FX_MulFunc(cosine, 0x800);
            fx32 dx = add32(forward_x, side_x);
            at.x = add32(at.x, dx);
            at.z = add32(at.z, dz);
            angle = (s16) (angle - 0x2000);
            EffectSystem_StartKind(5, &at, &angle, 0);
            break;
        }
        case 1:
            FieldActor_PlaySound(actor, 0x7df);
            break;
        case 2:
            FieldActor_PlaySound(actor, 0x7df);
            if (actor->other != NULL) {
                u16 item;
                FieldActor_RecordHeldItem(&item, actor);
                GameObject *other = (GameObject *) actor->other;
                ItemQuery query = (ItemQuery) (uintptr_t) other->vtable[24];
                query(other, &item);
            }
            break;
        case 3:
            if (is_local_player(actor) && Snowman_Knock(actor->other, 1)) {
                break;
            }
            FieldActor_PlaySound(actor, 0x7df);
            break;
        default:
            break;
    }
    actor->other = NULL;
    actor->other_result = 0;
}
CLEAN_AS(func_ov003_02211e38, FieldActor_AnimateState5D)

/* func_ov003_02212158: leaving state 0x5d: another player's actor with flag 0x1c still set does
 * what frame 5 would have (with the work's flag, the tile to func_ov003_022241a4 and flags 0x12
 * and 0x1c cleared). */
void FieldActor_ExitState5D(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    const TileFlagArgs *work = &actor->work.s5d;
    if (work->flag != 0) {
        int tile[2] = {work->x, work->z};
        TileEvent_StartFromChanges((const TileChangesTile *) tile);
        FieldActor_ClearFlag(actor, 0x12);
        FieldActor_ClearFlag(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_02212158, FieldActor_ExitState5D)

/* func_ov003_022121b8: state 0x5d's message handler: the saved verdict on what was met comes
 * back, and without the flag the state is asked for again at the saved tile. */
void FieldActor_State5DMessage(FieldActor *actor, int arg)
{
    u8 flag;
    u8 x;
    u8 z;
    u8 other_result;

    State5DSaved_Get(&actor->saved.s5d, &flag, &x, &z, &other_result);
    actor->other_result = other_result;
    if (flag == 0) {
        int tile[2] = {x, z};
        FieldActor_RequestState5D(actor, 0, tile, 6, (s16) arg);
    }
}
CLEAN_AS(func_ov003_022121b8, FieldActor_State5DMessage)

/* func_ov003_0221220c: entering state 0x5d: the request's tile and flag become the work and
 * are saved with the verdict on what was met; animation 0x4c starts; with the flag, flag 0x1c
 * is set. */
void FieldActor_EnterState5D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileFlagArgs *args = (const TileFlagArgs *) (const void *) request->payload;
    u8 flag = args->flag;
    u8 x = args->x;
    u8 z = args->z;
    u32 tile[2] = {x, z};

    State5DWork_Set(&actor->work.s5d, tile, flag);
    State5DSaved_Set(&actor->saved.s5d, flag, x, z, actor->other_result);
    FieldActor_PlayAnimationOnce(actor, 0x4c, 3, 0);
    if (flag != 0) {
        FieldActor_SetFlag(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_0221220c, FieldActor_EnterState5D)

/* func_ov003_02212270 */
void State5DSaved_Get(const State5DSaved *saved, u8 *flag, u8 *x, u8 *z, u8 *other_result)
{
    *flag = saved->flag;
    *x = saved->x;
    *z = saved->z;
    *other_result = saved->other_result;
}
CLEAN_AS(func_ov003_02212270, State5DSaved_Get)

/* func_ov003_0221228c */
void State5DSaved_Set(State5DSaved *saved, u8 flag, u8 x, u8 z, u8 other_result)
{
    saved->flag = flag;
    saved->x = x;
    saved->z = z;
    saved->other_result = other_result;
}
CLEAN_AS(func_ov003_0221228c, State5DSaved_Set)

/* func_ov003_022122a0 */
void State5DWork_Set(TileFlagArgs *work, const u32 *tile, u8 flag)
{
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
    work->flag = flag;
}
CLEAN_AS(func_ov003_022122a0, State5DWork_Set)

/* func_ov003_022122ac: asks for state 0x5d with a flag and a tile; whether it was queued. */
int FieldActor_RequestState5D(FieldActor *actor, int flag, const int *tile, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5d, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    State5DArgs_Set((TileFlagArgs *) (void *) request.payload, copy, (u8) flag);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022122ac, FieldActor_RequestState5D)

/* func_ov003_022122fc */
void State5DArgs_Set(TileFlagArgs *args, const u32 *tile, u8 flag)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->flag = flag;
}
CLEAN_AS(func_ov003_022122fc, State5DArgs_Set)

/* ---- State 0x5c: animation 0x5e while the actor slows down */

/* func_ov003_02212308: state 0x5c's update: the speed at 0x98 slows by 0x171 a frame. */
void FieldActor_UpdateState5C(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState5C(actor);
}
CLEAN_AS(func_ov003_02212308, FieldActor_UpdateState5C)

/* func_ov003_02212348: at the animation's end the actor moves on. */
void FieldActor_EndState5C(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02212348, FieldActor_EndState5C)

/* func_ov003_02212388: state 0x5c's message handler: the state is asked for again. */
void FieldActor_State5CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState5C(actor, 6, arg);
}
CLEAN_AS(func_ov003_02212388, FieldActor_State5CMessage)

/* func_ov003_02212394: entering state 0x5c: animation 0x5e. */
void FieldActor_EnterState5C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x5e, 3, 0);
}
CLEAN_AS(func_ov003_02212394, FieldActor_EnterState5C)

/* func_ov003_022123a8: asks for state 0x5c; whether it was queued. */
int FieldActor_RequestState5C(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x5c, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_022123a8, FieldActor_RequestState5C)

/* ---- State 0x5b: animation 0x4d with sound 0x842 */

/* func_ov003_022123e0: state 0x5b's update. */
void FieldActor_UpdateState5B(FieldActor *actor)
{
    FieldActor_AnimateState5B(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState5B(actor);
}
CLEAN_AS(func_ov003_022123e0, FieldActor_UpdateState5B)

/* func_ov003_022123fc: at the animation's end the actor moves on. */
void FieldActor_EndState5B(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_022123fc, FieldActor_EndState5B)

/* func_ov003_0221243c: sound 0x842 on reaching frame 5. */
void FieldActor_AnimateState5B(FieldActor *actor)
{
    if (FrameCtrl_Passed(&actor->anim, 5)) {
        FieldActor_PlaySound(actor, 0x842);
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov003_0221243c, FieldActor_AnimateState5B)

/* func_ov003_0221246c: state 0x5b's message handler: the state is asked for again. */
void FieldActor_State5BMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState5B(actor, 6, arg);
}
CLEAN_AS(func_ov003_0221246c, FieldActor_State5BMessage)

/* func_ov003_02212478: entering state 0x5b: animation 0x4d. */
void FieldActor_EnterState5B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x4d, 3, 0);
}
CLEAN_AS(func_ov003_02212478, FieldActor_EnterState5B)

/* func_ov003_0221248c: asks for state 0x5b; whether it was queued. */
int FieldActor_RequestState5B(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x5b, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221248c, FieldActor_RequestState5B)

/* ---- State 0x5a: the actor faces a tile and acts on it */

/* func_ov003_022124c4: state 0x5a's update: the speed at 0x98 slows by 0x9c a frame; the actor
 * of this console acts on the work's tile (FieldActor_ActAt), another player's actor notes the
 * state after this one. The actor turns to the tile, and effect 0x2a marks the frame it stops. */
void FieldActor_UpdateState5A(FieldActor *actor)
{
    int speed_before = actor->unk_098;
    int speed = FieldActor_Slow(speed_before, 0);
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        Vec3 zero = {0, 0, 0};
        FieldActor_ActAt(actor, &zero, 0);
    } else {
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
        FieldActor_EnterContact(actor);
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
    FieldActor_FaceState5ATile(actor);
    if (speed_before != 0 && actor->unk_098 == 0) {
        EffectSystem_StartKind(0x2a, &actor->position, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_022124c4, FieldActor_UpdateState5A)

/* func_ov003_02212574: once the actor has stopped (the speed at 0x98 is 0; else -1), asks for
 * the state FieldActor_ClassifyAt picks for a point and returns that verdict: 1 state 0x5b, 2
 * state 0x5d at the point's tile, 3 and 4 state 0x5e at the point (flag 0 and 1), 5 and 9 state
 * 0x5f at the point (kind 0 and 1), 6 state 0x62 at the tile with no item, 7 state 0x5c, 8
 * state 0x5d with the flag; 0 nothing.
 * With `use_point` the point is `*point` and objects met are checked. Without it (state 0x5a)
 * the point is the middle of the work's tile, and objects met are checked only while no target
 * was known; a target found then is remembered in the work. */
int FieldActor_ActAt(FieldActor *actor, Vec3 *point, u8 use_point)
{
    if (actor->unk_098 != 0) {
        return -1;
    }

    State5AWork *work = &actor->work.s5a;
    BOOL first_look = FALSE;
    Vec3 at;
    if (use_point) {
        copy_point(&at, point);
    } else {
        AcreTile_TileCentre(&at, work->x, work->z);
        if (work->has_target == 0) {
            first_look = TRUE;
            use_point = 1;
        }
    }

    int verdict = FieldActor_ClassifyAt(actor, &at, &use_point);
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) &at);
    if (first_look && actor->target != -1) {
        work->has_target = 1;
    }

    switch (verdict) {
        case 1:
            FieldActor_RequestState5B(actor, 6, -1);
            break;
        case 2:
        case 8: {
            int copy[2] = {tile[0], tile[1]};
            FieldActor_RequestState5D(actor, verdict == 8, copy, 6, -1);
            break;
        }
        case 3:
        case 4: {
            Vec3 copy = at;
            FieldActor_RequestState5E(actor, verdict == 4, &copy, 6, -1);
            break;
        }
        case 5:
        case 9: {
            Vec3 copy = at;
            FieldActor_RequestState5FNoItem(actor, &copy, verdict == 9, 6, -1);
            break;
        }
        case 6: {
            int x = 0;
            int z = 0;
            Position_Tile(&x, &z, (const Position *) &at);
            u32 copy[2] = {(u32) x, (u32) z};
            FieldActor_RequestState62(actor, 0, copy, ITEM_NONE, 6, -1);
            break;
        }
        case 7:
            FieldActor_RequestState5C(actor, 6, -1);
            break;
        default:
            break;
    }
    return verdict;
}
CLEAN_AS(func_ov003_02212574, FieldActor_ActAt)

/* func_ov003_02212728: the actor turns towards the middle of the work's tile. */
void FieldActor_FaceState5ATile(FieldActor *actor)
{
    Vec3 middle;
    AcreTile_TileCentre(&middle, actor->work.s5a.x, actor->work.s5a.z);
    FieldActor_SetContactBSized(actor, &middle, 0xf33, 0x1000);
    FieldBody_Enter((FieldBody *) actor->unk_1C4);
}
CLEAN_AS(func_ov003_02212728, FieldActor_FaceState5ATile)

/* func_ov003_02212768: state 0x5a's message handler: the state is asked for again at the saved
 * tile. */
void FieldActor_State5AMessage(FieldActor *actor, int arg)
{
    int tile[2] = {0, 0};
    State5ASaved_Get(&actor->saved.tile, tile);
    int copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState5A(actor, copy, 6, arg);
}
CLEAN_AS(func_ov003_02212768, FieldActor_State5AMessage)

/* func_ov003_022127a0: entering state 0x5a: the request's tile becomes the work's and is saved;
 * whether a target is known goes to the work; during animation 0x4a it is set again
 * (func_020109fc). */
void FieldActor_EnterState5A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileArgs *args = (const TileArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;

    int tile[2] = {x, z};
    State5AWork_SetTile(&actor->work.s5a, tile);
    actor->work.s5a.has_target = actor->target != -1;
    int copy[2] = {x, z};
    State5ASaved_Set(&actor->saved.tile, copy);
    if (actor->animation == 0x4a) {
        FieldActor_PlayAnimationLoop(actor, 0x4a, 3, 0);
    }
}
CLEAN_AS(func_ov003_022127a0, FieldActor_EnterState5A)

/* func_ov003_0221280c */
void State5ASaved_Get(const TileArgs *saved, int *tile)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
}
CLEAN_AS(func_ov003_0221280c, State5ASaved_Get)

/* func_ov003_02212818 */
void State5ASaved_Set(TileArgs *saved, const int *tile)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212818, State5ASaved_Set)

/* func_ov003_02212824 */
void State5AWork_SetTile(State5AWork *work, const int *tile)
{
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212824, State5AWork_SetTile)

/* func_ov003_02212830: asks for state 0x5a at a tile; whether it was queued. */
void *FieldActor_RequestState5A(FieldActor *actor, const int *tile, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x5a, priority, arg);
    int copy[2] = {tile[0], tile[1]};
    State5AArgs_Set((TileArgs *) (void *) request.payload, copy);
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212830, FieldActor_RequestState5A)

/* func_ov003_02212878 */
void State5AArgs_Set(TileArgs *args, const int *tile)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212878, State5AArgs_Set)

/* ---- State 0x59: animation 0x49 then 0x4a while the actor slides to a point */

/* func_ov003_02212884: state 0x59's update: the speed at 0x98 slows by 0x171 a frame. The actor
 * of this console turns to the point (FieldActor_TurnState59) and acts there once stopped
 * (FieldActor_RunState59); another player's actor follows the state it is told
 * (FieldActor_EndState59Remote). Effect 0x2a marks the frame the actor stops. */
void FieldActor_UpdateState59(FieldActor *actor)
{
    int speed_before = actor->unk_098;
    int speed = FieldActor_StepDown(speed_before, 0, 0x171);
    FieldActor_SetSpeed(actor, &speed);
    if (is_local_player(actor)) {
        FieldActor_TurnState59(actor);
        FieldActor_UpdateBody(actor);
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        FieldActor_RunState59(actor);
        FieldActor_FaceState59Point(actor);
    } else {
        FieldActor_UpdateBody(actor);
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
        FieldActor_EnterContact(actor);
        FieldActor_EndState59Remote(actor);
    }
    if (speed_before != 0 && actor->unk_098 == 0) {
        EffectSystem_StartKind(0x2a, &actor->position, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_02212884, FieldActor_UpdateState59)

/* func_ov003_0221292c: another player's actor notes the state after this one; at the
 * animation's end animation 0x4a is set (func_020109fc). */
void FieldActor_EndState59Remote(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActor_PlayAnimationLoop(actor, 0x4a, 3, 0);
    }
}
CLEAN_AS(func_ov003_0221292c, FieldActor_EndState59Remote)

/* func_ov003_02212968: once animation 0x49 is over (it gives way to 0x4a) or during 0x4a: when
 * the actor has stopped and faces the work's yaw, it acts at the work's point
 * (FieldActor_ActAt); with nothing to do there, state 0x5a follows at the point's tile. */
void FieldActor_RunState59(FieldActor *actor)
{
    State59Work *work = &actor->work.s59;

    if (!FrameCtrl_IsDone(&actor->anim) && actor->animation != 0x4a) {
        return;
    }
    if (actor->animation == 0x49) {
        FieldActor_PlayAnimationLoop(actor, 0x4a, 3, 0);
    }
    if (actor->unk_098 != 0) {
        return;
    }
    if (work->yaw != actor->yaw) {
        return;
    }
    Vec3 point = work->point;
    Vec3 copy = point;
    if (FieldActor_ActAt(actor, &copy, 1) != 0) {
        return;
    }
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) &point);
    int tile_copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState5A(actor, tile_copy, 6, -1);
}
CLEAN_AS(func_ov003_02212968, FieldActor_RunState59)

/* func_ov003_02212a14: the actor turns towards the work's point. */
void FieldActor_FaceState59Point(FieldActor *actor)
{
    Vec3 point = actor->work.s59.point;
    FieldActor_SetContactBSized(actor, &point, 0xf33, 0x1000);
    FieldBody_Enter((FieldBody *) actor->unk_1C4);
}
CLEAN_AS(func_ov003_02212a14, FieldActor_FaceState59Point)

/* func_ov003_02212a54: the actor turns towards the work's yaw. Once it has stopped while the
 * point is not fixed, the point becomes the tile ahead and the yaw the direction to it from the
 * frame's start position, and the point is fixed. */
void FieldActor_TurnState59(FieldActor *actor)
{
    State59Work *work = &actor->work.s59;
    s16 yaw;

    if (actor->unk_098 == 0 && work->fixed == 0) {
        Vec3 ahead;
        FieldActor_TileAhead(&ahead, actor);
        yaw = Math_Atan2(sub32(ahead.x, actor->start_position.x), sub32(ahead.z, actor->start_position.z));
        work->yaw = yaw;
        work->fixed = 1;
        work->point = ahead;
    } else {
        yaw = work->yaw;
    }
    FieldActor_TurnTowards(actor, yaw);
}
CLEAN_AS(func_ov003_02212a54, FieldActor_TurnState59)

/* func_ov003_02212ac0: state 0x59's message handler: the state is asked for again with the
 * saved tile and flag. */
void FieldActor_State59Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;
    u8 fixed;

    State59Saved_Get(&actor->saved.s59, &x, &z, &fixed);
    FieldActor_RequestState59(actor, &x, &z, &fixed, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02212ac0, FieldActor_State59Message)

/* func_ov003_02212afc: entering state 0x59: the request is saved and animation 0x49 starts. The
 * point is the middle of the request's tile when its flag is set; otherwise it is where the
 * actor's slide ends (0x2000 ahead plus each frame's speed as it slows by 0x171 a frame), at
 * the middle of that tile. The work gets the point, the direction to it from the frame's start
 * position and the flag. */
void FieldActor_EnterState59(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileFlagArgs *args = (const TileFlagArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;
    int fixed = args->flag;

    State59Saved_Set(&actor->saved.s59, x, z, fixed);
    FieldActor_PlayAnimationOnce(actor, 0x49, 3, 0);
    Vec3 point;
    AcreTile_TileCentre(&point, (u32) x, (u32) z);
    if (fixed == 0) {
        /* QUIRK: the speed is taken as it is: a negative one adds nothing, and one within 0x171
         * of -0x80000000 wraps round to a large positive one. */
        int speed = actor->unk_098;
        fx32 distance = 0x2000;
        while (speed != 0) {
            speed = sub32(speed, 0x171);
            if (speed > 0) {
                distance = add32(distance, speed);
            } else {
                speed = 0;
            }
        }
        Vec3 end;
        FieldActor_PointAhead(&end, actor, &actor->position, (const u16 *) &actor->yaw, &distance);
        point = end;
        AcreTile_SnapToTileCentre(&point, &point);
    }
    s16 yaw = Math_Atan2(sub32(point.x, actor->start_position.x), sub32(point.z, actor->start_position.z));
    Vec3 copy = point;
    State59Work_Set(&actor->work.s59, &copy, yaw, (char) fixed);
}
CLEAN_AS(func_ov003_02212afc, FieldActor_EnterState59)

/* func_ov003_02212bd8 */
void State59Saved_Get(const TileFlagArgs *saved, u8 *x, u8 *z, u8 *fixed)
{
    *x = saved->x;
    *z = saved->z;
    *fixed = saved->flag;
}
CLEAN_AS(func_ov003_02212bd8, State59Saved_Get)

/* func_ov003_02212bec */
void State59Saved_Set(TileFlagArgs *saved, int x, int z, int fixed)
{
    saved->x = (u8) x;
    saved->z = (u8) z;
    saved->flag = (u8) fixed;
}
CLEAN_AS(func_ov003_02212bec, State59Saved_Set)

/* func_ov003_02212bf4 */
void State59Work_Set(State59Work *work, const Vec3 *point, s16 yaw, char fixed)
{
    copy_point(&work->point, point);
    work->yaw = yaw;
    work->fixed = (u8) fixed;
    work->unk_0F = 0;
}
CLEAN_AS(func_ov003_02212bf4, State59Work_Set)

/* func_ov003_02212c10: asks for state 0x59 with a tile and a flag; whether it was queued. */
int FieldActor_RequestState59(FieldActor *actor, const u8 *x, const u8 *z, const u8 *fixed, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x59, priority, arg);
    State59Args_Set((TileFlagArgs *) (void *) request.payload, *x, *z, *fixed);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212c10, FieldActor_RequestState59)

/* func_ov003_02212c58: asks for state 0x59 at the tile of the point the actor aims at:
 * aim_point with the flag when unk_148 is set, else the point at 0x14c with the flag when
 * unk_144 is nonzero (both at height 0). Whether it was queued. */
int FieldActor_RequestState59AtAim(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
    Vec3 point;
    int fixed;

    open_request(&request, 0x59, priority, arg);
    if (actor->unk_148 != 0) {
        point.x = actor->aim_point.x;
        point.y = 0;
        point.z = actor->aim_point.z;
        fixed = 1;
    } else {
        point.x = actor->unk_14C.x;
        point.y = 0;
        point.z = actor->unk_14C.z;
        fixed = actor->unk_144 != 0;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) &point);
    State59Args_Set((TileFlagArgs *) (void *) request.payload, (u8) x, (u8) z, fixed);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212c58, FieldActor_RequestState59AtAim)

/* func_ov003_02212d04 */
void State59Args_Set(TileFlagArgs *args, int x, int z, int fixed)
{
    args->x = (u8) x;
    args->z = (u8) z;
    args->flag = (u8) fixed;
}
CLEAN_AS(func_ov003_02212d04, State59Args_Set)

/* ---- State 0x58: animation 0x5d with pose 6, then 0x6c, then the head follows a point */

/* func_ov003_02212d0c: state 0x58's update. */
void FieldActor_UpdateState58(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState58(actor);
}
CLEAN_AS(func_ov003_02212d0c, FieldActor_UpdateState58)

/* Ends state 0x58: the state after it is noted and func_0200d4e8 (6) moves on. */
static void leave_state58(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, 6, 1, -1);
}

/* func_ov003_02212d2c: state 0x58 by the work's step. Each frame a block (a copy of the one at
 * 0x698) goes through func_ov003_02219668, and unless the frame ends early, to
 * func_ov003_0222d83c with three equal angles (100 falling by 16 a frame over the first six
 * frames of animation 0x5d, else 0) and a flag.
 *   Step 0: at the animation's end func_ov003_0222e6c4 (1), the actor moves on (6), the actor
 *     of this console gives the item 0x12b0 + kind to func_0209a110; the flag is 1.
 *   Step 1: during animation 0x5d, at its end animation 0x6c starts with pose 0 in hand. The
 *     block's point is a point by the actor. The actor of this console waits on the word at
 *     0x81c: at 5 it becomes 6 once func_0206f728 accepts the item; at 6 it becomes 0xf once
 *     func_0206fbc0 says so, and when func_0206fc6c then says so the receiver is released and
 *     the actor moves on (6); from 0xf an angle is drawn (-0x1555 to 0x1554) for
 *     func_ov003_0222eabc and saved, the receiver is released, and step 2 starts with animation
 *     0 (func_020109fc). Another player's actor notes the state after this one and goes to step
 *     2 when the saved step is 2, with the saved angle.
 *   Step 2: while func_ov003_0222ea84 is 3 the head turns to the point func_ov003_0222e970
 *     gives (the pitch at most 0x1800); otherwise the head turns back to 0 and once there the
 *     actor moves on (6). */
void FieldActor_RunState58(FieldActor *actor)
{
    int flag = 0;
    Vec3 beside = actor->position;
    int player = actor->player;

    s16 angle = 0;
    if (actor->animation == 0x5d) {
        u32 frame = (u32) anim_frame(actor);
        if (frame < 6) {
            angle = (s16) (0x64 - (frame << 4));
        }
    }
    s16 angles[3] = {angle, angle, angle};

    FieldActorBlock48 block = actor->unk_698;
    FieldActor_OffsetMatrix(&block, NULL);

    State58Args *work = &actor->work.s58;
    State58Saved *saved = &actor->saved.s58;
    int item = (u16) (work->kind + 0x12b0);
    switch (work->step) {
        case 0:
            if (!FrameCtrl_IsDone(&actor->anim)) {
                break;
            }
            TownInsect_EndHeld((u8) actor->player, 1);
            leave_state58(actor);
            if (is_local_player(actor)) {
                u16 code = (u16) item;
                CurrentPockets_Receive(&code);
            }
            flag = 1;
            break;
        case 1:
            if (actor->animation == 0x5d) {
                if (!FrameCtrl_IsDone(&actor->anim)) {
                    break;
                }
                FieldActor_PlayAnimationLoop(actor, 0x6c, 3, 3);
                HeldItem_Act(actor->held, 0, 3, 0);
            }
            beside.x = sub32(beside.x, 0x400);
            beside.y = add32(beside.y, 0x1b34);
            beside.z = add32(beside.z, 0x1400);
            Globe_BendFar(&beside, &beside);
            /* The block's last three words are its point. */
            block.words[9] = (u32) beside.x;
            block.words[10] = (u32) beside.y;
            block.words[11] = (u32) beside.z;
            if (is_local_player(actor)) {
                if (actor->unk_81C == 5) {
                    if (GroupParams_OpenWithItem2b(item)) {
                        actor->unk_81C = 6;
                    }
                    break;
                }
                if (actor->unk_81C == 6) {
                    if (!GroupParams_CanOpen()) {
                        break;
                    }
                    actor->unk_81C = 0xf;
                    if (GroupParams_C4CIs1()) {
                        release_receiver(actor);
                        EventQueue_FinishKind9();
                        leave_state58(actor);
                        return;
                    }
                } else if (actor->unk_81C < 0xf) {
                    break;
                }
                int drawn = (s16) sub32(MainRandom_Below(0x2aaa), 0x1555);
                TownInsect_LetGo((u8) player, drawn);
                State58Saved_SetAngle(saved, drawn);
                release_receiver(actor);
                EventQueue_FinishKind9();
                work->step = 2;
                State58Saved_SetStep(saved, 2);
                FieldActor_PlayAnimationLoop(actor, 0, 4, 4);
                return;
            }
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            if (State58Saved_Step(saved) != 2) {
                return;
            }
            TownInsect_LetGo((u8) player, State58Saved_Angle(saved));
            work->step = 2;
            FieldActor_PlayAnimationLoop(actor, 0, 4, 4);
            return;
        case 2: {
            if (TownInsect_HeldState((u8) player) != 3) {
                if (actor->head_pitch == 0 && actor->head_yaw == 0) {
                    leave_state58(actor);
                    return;
                }
                FieldActor_TurnAngle(&actor->head_pitch, 0, 0x400, 0x1770000, 0xc0000);
                FieldActor_TurnAngle(&actor->head_yaw, 0, 0x400, 0x1770000, 0xc0000);
                return;
            }
            const Vec3 *target = TownInsect_HeldPosition((u8) player);
            Vec3 eye = actor->position;
            eye.y = add32(eye.y, 0x1b33);
            int yaw = Math_Atan2(sub32(target->x, eye.x), sub32(target->z, eye.z));
            int pitch = Math_Atan2(sub32(target->y, eye.y), Vec_DistanceXZ(target, &eye));
            actor->head_yaw = (s16) yaw;
            if (pitch >= 0x1800) {
                pitch = 0x1800;
            }
            actor->head_pitch = (s16) pitch;
            return;
        }
        default:
            break;
    }
    TownInsect_HeldFromMatrix((u8) player, angles, (Mtx43 *) &block, flag);
}
CLEAN_AS(func_ov003_02212d2c, FieldActor_RunState58)

/* func_ov003_022130c8: leaving state 0x58: the head faces ahead. */
void FieldActor_ExitState58(FieldActor *actor)
{
    actor->head_pitch = 0;
    actor->head_yaw = 0;
}
CLEAN_AS(func_ov003_022130c8, FieldActor_ExitState58)

/* func_ov003_022130dc: state 0x58's message handler: the state is asked for again with the
 * saved kind and step (func_ov003_022131c8). */
void FieldActor_State58Message(FieldActor *actor, int arg)
{
    u8 kind;
    u8 step;
    /* QUIRK: the original reads the saved angle into a one-byte local, its second byte landing
     * past it in the stack frame; it is not used. */
    u16 angle;

    State58Saved_Get(&actor->saved.s58, &kind, &step, &angle);
    FieldActor_RequestState58(actor, (char) kind, (char) step, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022130dc, FieldActor_State58Message)

/* func_ov003_02213114: entering state 0x58: the request's kind and step become the work and are
 * saved with angle 0; animation 0x5d starts with pose 6 in hand, and sound 0x4f. */
void FieldActor_EnterState58(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State58Args *args = (const State58Args *) (const void *) request->payload;
    u8 kind = args->kind;
    u8 step = args->step;

    actor->work.s58.kind = kind;
    actor->work.s58.step = step;
    State58Saved_Set(&actor->saved.s58, kind, step, 0);
    FieldActor_PlayAnimationOnce(actor, 0x5d, 3, 0);
    HeldItem_Act(actor->held, 6, 3, 1);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_02213114, FieldActor_EnterState58)

/* func_ov003_02213168 */
int State58Saved_Angle(const State58Saved *saved)
{
    return PackedBytes_ReadS16(saved->angle);
}
CLEAN_AS(func_ov003_02213168, State58Saved_Angle)

/* func_ov003_02213174 */
int State58Saved_Step(const State58Saved *saved)
{
    return saved->step;
}
CLEAN_AS(func_ov003_02213174, State58Saved_Step)

/* func_ov003_02213178 */
void State58Saved_Get(const State58Saved *saved, u8 *kind, u8 *step, u16 *angle)
{
    *kind = saved->kind;
    *step = (u8) State58Saved_Step(saved);
    *angle = (u16) State58Saved_Angle(saved);
}
CLEAN_AS(func_ov003_02213178, State58Saved_Get)

/* func_ov003_02213198 */
void State58Saved_SetAngle(State58Saved *saved, int angle)
{
    PackedBytes_WriteS16(saved->angle, angle);
}
CLEAN_AS(func_ov003_02213198, State58Saved_SetAngle)

/* func_ov003_022131a4 */
void State58Saved_SetStep(State58Saved *saved, int step)
{
    saved->step = (u8) step;
}
CLEAN_AS(func_ov003_022131a4, State58Saved_SetStep)

/* func_ov003_022131a8 */
void State58Saved_Set(State58Saved *saved, u8 kind, int step, int angle)
{
    saved->kind = kind;
    State58Saved_SetStep(saved, step);
    State58Saved_SetAngle(saved, angle);
}
CLEAN_AS(func_ov003_022131a8, State58Saved_Set)

/* func_ov003_022131c8: asks for state 0x58 with a kind and a step; whether it was queued. */
int FieldActor_RequestState58(FieldActor *actor, char kind, char step, int priority, s16 arg)
{
    StateRequest request;
    open_request(&request, 0x58, priority, arg);
    State58Args *args = (State58Args *) (void *) request.payload;
    args->kind = (u8) kind;
    args->step = (u8) step;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022131c8, FieldActor_RequestState58)

/* ---- States 0x57 to 0x51: an insect or a fish caught */

static_assert(offsetof(FieldActor, unk_5D0) == 0x5d0, "0x5d0");
static_assert(offsetof(FieldActor, unk_810) == 0x810, "0x810");
static_assert(offsetof(FieldActor, unk_8C4) == 0x8c4, "0x8c4");
static_assert(offsetof(FieldActor, unk_1C4) == 0x1c4, "0x1c4");
static_assert(offsetof(FieldActor, unk_14C) == 0x14c, "0x14c");
static_assert(offsetof(FieldActor, work.s57.unk_04) == 0x7d8, "state 0x57 0x04");
static_assert(offsetof(FieldActor, work.s57.step) == 0x7dd, "state 0x57 step");
static_assert(offsetof(FieldActor, work.s57.unk_0A) == 0x7de, "state 0x57 0x0a");
static_assert(offsetof(FieldActor, work.s56.yaw) == 0x7d6, "state 0x56 yaw");
static_assert(offsetof(FieldActor, work.s56.slot) == 0x7d8, "state 0x56 slot");
static_assert(offsetof(FieldActor, work.s56.tip) == 0x7dc, "state 0x56 tip");
static_assert(offsetof(FieldActor, work.s54.unk_05) == 0x7d9, "state 0x54 0x05");
static_assert(offsetof(FieldActor, saved.s57.angle) == 0x8f4, "state 0x57 angle");
static_assert(offsetof(GroundInfo, unk_30) == 0x30, "ground 0x30");
static_assert(offsetof(GroundInfo, kind) == 0x34, "ground kind");

/* What func_02032adc makes for func_020311bc to test a segment against the scenery, with the
 * ground found at its start (func_02034270); func_02032acc ends it. */
typedef struct SegmentTest {
    u8 unk_00[0x14];
    GroundInfo ground;
} SegmentTest;

static_assert(sizeof(SegmentTest) == 0x54, "segment test");

/* The fish hanging from what the actor holds (func_020604f8). */
typedef struct HookedFish {
    u8 unk_00[0x7e];
    s8 kind; /* the item is 0x12e8 + kind */
    u8 unk_7F[0x1ff - 0x7f];
    u8 size; /* a row of the table at 0x0223c024 */
} HookedFish;

/* Rows of 0x14 bytes; the byte at 2 of each is a size in percent. */
extern const u8 data_ov003_0223c026[];
/* The receivers' names: "obj_etc_getinsect" and "obj_etc_getfish". */
extern const char data_ov003_02238144[];
extern const char data_ov003_02238158[];
/* Distances ahead of the actor (20.12) for func_0200fa1c in state 0x56: 2.85 (a stop at frame 4,
 * twice) and 2.0 (frame 3). */
extern const fx32 data_ov003_02238114;
extern const fx32 data_ov003_0223811c;
extern const fx32 data_ov003_02238120;
/* The `track` byte (1) of the requests for state 0x8f that states 0x55 and 0x54 end with. */
extern const u8 data_ov003_02238100;
extern const u8 data_ov003_02238104;
extern const u8 data_ov003_02238108;
/* The speed (-1049) state 0x52 starts with. */
extern int data_ov003_0223812c;

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * -0x80000000 / -1 gives -0x80000000. */
static int div_s32(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return sub32(0, numerator);
    }
    return numerator / divisor;
}

/* What hangs from the held item: the last word of `held`. */
static void *held_line(FieldActor *actor)
{
    return &actor->held[0x28];
}

/* Animation frame `frame` was reached (func_02056f28). */
static BOOL anim_passed(FieldActor *actor, int frame)
{
    return FrameCtrl_Passed(&actor->anim, frame) != 0;
}

static BOOL anim_done(FieldActor *actor)
{
    return FrameCtrl_IsDone(&actor->anim) != 0;
}

/* The point of a block (its last three words). */
static Vec3 block_point(const FieldActorBlock48 *block)
{
    Vec3 point = {(fx32) block->words[9], (fx32) block->words[10], (fx32) block->words[11]};
    return point;
}

/* Whether the link of the receiver is up and what it opened is closed. */
static BOOL link_closed(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open == 0;
}

/* Releases the receiver without testing flag 0x11 first. */
static void close_receiver(FieldActor *actor)
{
    SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
    FieldActor_ClearFlag(actor, 0x11);
}

/* The items 0x1320 to 0x1322: kinds 0x38 to 0x3a past the fish of 0x12e8 to 0x131f. */
static BOOL is_item_1320(u16 item)
{
    return item >= 0x1320 && item <= 0x1322;
}

/* The work of states 0x57 and 0x54 that func_0200ee40 would rewrite. */
typedef struct KeptAcrossEE40 {
    Vec3 unk_0C4;
    s16 unk_0D0;
    FieldActorBlock48 unk_298;
    FieldActorBlock48 unk_698;
} KeptAcrossEE40;

static void keep_across_ee40(const FieldActor *actor, KeptAcrossEE40 *kept)
{
    kept->unk_0C4 = actor->unk_0C4;
    kept->unk_0D0 = actor->unk_0D0;
    kept->unk_298 = actor->unk_298;
    kept->unk_698 = actor->unk_698;
}

static void restore_after_ee40(FieldActor *actor, const KeptAcrossEE40 *kept)
{
    actor->unk_0C4 = kept->unk_0C4;
    actor->unk_0D0 = kept->unk_0D0;
    actor->unk_298 = kept->unk_298;
    actor->unk_698 = kept->unk_698;
}

/* ---- State 0x57: the insect caught is shown */

/* func_ov003_0221320c: state 0x57's update: func_0200ee40 runs between func_02010f5c and the
 * others, with the points and blocks it would change kept. */
void FieldActor_UpdateState57(FieldActor *actor)
{
    KeptAcrossEE40 kept;

    FieldActor_UpdateBody(actor);
    keep_across_ee40(actor, &kept);
    FieldActor_RebuildPose(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_RunState57(actor);
    restore_after_ee40(actor, &kept);
}
CLEAN_AS(func_ov003_0221320c, FieldActor_UpdateState57)

/* func_ov003_022132bc: state 0x57 by the work's step. In mode 0 the actor holds still
 * (func_0200faf0). On the first frame the actor of this console goes to step 1 and another
 * player's to step 9 (telling func_ov003_0222e5fc the slot); kinds 0x18, 0x30, 0x32 and 0x33
 * get effect 0x25 at the block's point; func_ov003_0222e898 learns the kind.
 * Each frame the block at 0x698 is moved by an offset that grows over the end of animation 0x5c
 * (from frame 0x24) and the effect follows its point. Unless the frame ends early, the block
 * goes to func_ov003_0222d83c with three equal values: 0 before frame 0x17 of animation 0x5c,
 * then rising by 10 a frame to 100.
 *   Another player's actor notes the state after this one, and when its step is below 6 or 9
 *   and the saved step is 6, takes the saved angle (func_ov003_0222eabc), starts animation 0
 *   and goes to step 7.
 *   Step 1: once func_0203e1c4 says so the receiver is registered under "obj_etc_getinsect"
 *     with the item 0x12b0 + kind, its link is asked for, and the sounds are set; step 2.
 *   Step 2: once the link is open: step 8 (0x81c = 0xd) when func_0203cc1c says so and it did
 *     not on entering, else step 3 (0x81c = 8).
 *   Step 3: with func_02099fe8 at -1, step 4 (0x81c = 0) when func_02043368 accepts, else step
 *     5 (0x81c = 1). Otherwise once the link closes the receiver is released and state 0x58
 *     is asked for at step 0.
 *   Step 4: from 0x81c = 0xf on step 5; otherwise once the link closes the receiver is
 *     released and state 0x58 is asked for at step 1.
 *   Step 5: once the link closes the effect ends, an angle is drawn (-0x1555 to 0x1554) for
 *     func_ov003_0222eabc and saved, the receiver is released, animation 0 starts and the
 *     step (6) is saved.
 *   Step 6: while func_ov003_0222ea84 is 3 the head turns to the point func_ov003_0222e970
 *     gives (the pitch at most 0x1800); otherwise the head turns back to 0, and once there the
 *     actor moves on by its mode (in mode 2 the actor of this console first releases the
 *     receiver).
 *   Step 7: waits for func_ov003_0222ea84 to be 3 or 0, then step 6.
 *   Step 8: once the link closes the receiver is released and func_020094a0 runs. */
void FieldActor_RunState57(FieldActor *actor)
{
    State57Work *work = &actor->work.s57;
    State57Saved *saved = &actor->saved.s57;
    int mode = work->mode;
    int kind = work->kind;

    if (mode == 0) {
        FieldActor_TurnToZero(actor, 0x400);
    }
    int player = actor->player;
    if (work->step == 0) {
        if (Session_IsLocalPlayer(data_020ccf94, player)) {
            work->step = 1;
        } else {
            work->step = 9;
            if (work->slot != 0xff) {
                TownInsect_Caught(work->slot);
            }
        }
        if (kind == 0x18 || kind == 0x30 || kind == 0x32 || kind == 0x33) {
            FieldActorBlock48 start = actor->unk_698;
            FieldActor_OffsetMatrix(&start, NULL);
            Vec3 at = block_point(&start);
            Globe_Unbend(&at, &at);
            work->effect = EffectSystem_StartKind(0x25, &at, NULL, 0);
        }
        TownInsect_TakeHeld(kind, (u8) player);
    }

    FieldActorBlock48 block = actor->unk_698;
    Vec3 offset = {0x4cd, 0, 0};
    if (actor->animation != 0x5c) {
        offset.x = 0x800;
        offset.y = 0x19a;
        offset.z = -0x19a;
    } else {
        int frame = anim_frame(actor);
        if (frame >= 0x24) {
            /* QUIRK: on the last frame of a 0x24-frame animation the divisor is 0, which the
             * ROM's division answers with the numerator. */
            int d = div_s32((frame - 0x23) * 0x19a, (int) anim_frames(actor) - 0x24);
            offset.x = add32(offset.x, d * 2);
            offset.y = add32(offset.y, d);
            offset.z = sub32(offset.z, d);
        }
    }
    FieldActor_OffsetMatrix(&block, &offset);
    if (work->effect != -1) {
        Vec3 at = block_point(&block);
        Globe_Unbend(&at, &at);
        EffectSystem_MoveHandle(work->effect, &at, NULL, 0);
    }

    s16 values[3] = {0, 0, 0};
    if (anim_frame(actor) < 0x17 && actor->animation == 0x5c) {
        TownInsect_HeldFromMatrix((u8) player, values, (Mtx43 *) &block, 0);
        return;
    }
    if (!is_local_player(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        if (work->step < 6 || work->step == 9) {
            if (State57Saved_Step(saved) == 6) {
                TownInsect_LetGo((u8) player, State57Saved_Angle(saved));
                FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
                work->step = 7;
            }
        }
    }
    s16 value = 100;
    if (actor->animation == 0x5c) {
        u32 frame = (u32) anim_frame(actor);
        if (frame <= 0x21) {
            value = (s16) ((frame - 0x17) * 10);
            if (value >= 100) {
                value = 100;
            }
        }
    }
    values[0] = values[1] = values[2] = value;

    switch (work->step) {
        case 1: {
            if (!EventQueue_RequestKind9()) {
                break;
            }
            work->step = 2;
            SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
            FieldActor_SetFlag(actor, 0x11);
            MessageReceiver_SetName((MessageReceiver *) actor->receiver, data_ov003_02238144);
            actor->receiver_unk_1E = (u8) kind;
            u16 item = (u16) (kind + 0x12b0);
            ItemRecord_MarkHadByCurrent(&item);
            actor->link->requested = 1;
            CameraControl_SetMode4();
            if (FieldActor_TestFlag(actor, 0x1a)) {
                Music_DropMusic(0x3f);
                FieldActor_ClearFlag(actor, 0x1a);
            }
            Music_DropPriority(0x12);
            Music_AddValue(0xc, 0, 0xe);
            Music_Add(0xd, 0x39, 0x7f, 1);
            break;
        }
        case 2:
            if (actor->link == NULL || actor->link->open == 0) {
                break;
            }
            if (ItemRecord_HasAllInsects() && work->unk_0A == 0) {
                work->step = 8;
                actor->unk_81C = 0xd;
            } else {
                work->step = 3;
                actor->unk_81C = 8;
            }
            break;
        case 3:
            if (CurrentPockets_FreeSlot() == -1) {
                int point[2] = {0, 0};
                if (TileRequests_FindDropTile(0x10, (TileRequestTile *) point, NULL)) {
                    work->step = 4;
                    actor->unk_81C = 0;
                } else {
                    work->step = 5;
                    actor->unk_81C = 1;
                }
                return;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            EventQueue_FinishKind9();
            FieldActor_RequestState58(actor, (char) kind, 0, 6, -1);
            CameraControl_ResetMode();
            break;
        case 4:
            if (actor->unk_81C >= 0xf) {
                work->step = 5;
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            FieldActor_RequestState58(actor, (char) kind, 1, 6, -1);
            CameraControl_ResetMode();
            break;
        case 5: {
            if (!link_closed(actor)) {
                break;
            }
            if (work->effect != -1) {
                EffectSystem_EndHandle(work->effect);
            }
            int angle = (s16) sub32(MainRandom_Below(0x2aaa), 0x1555);
            TownInsect_LetGo((u8) player, angle);
            State57Saved_SetAngle(saved, angle);
            close_receiver(actor);
            EventQueue_FinishKind9();
            FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
            work->step = 6;
            State57Saved_SetStep(saved, 6);
            CameraControl_ResetMode();
            return;
        }
        case 6: {
            if (TownInsect_HeldState((u8) player) != 3) {
                if (actor->head_pitch != 0 || actor->head_yaw != 0) {
                    FieldActor_TurnAngle(&actor->head_pitch, 0, 0x400, 0x1770000, 0xc0000);
                    FieldActor_TurnAngle(&actor->head_yaw, 0, 0x400, 0x1770000, 0xc0000);
                    return;
                }
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                switch (mode) {
                    case 2:
                        if (is_local_player(actor)) {
                            release_receiver(actor);
                            EventQueue_FinishKind9();
                        }
                        FieldActor_RequestState2(actor, 3, 1, -1);
                        return;
                    case 0:
                    case 3:
                        FieldActor_RequestState2(actor, 3, 1, -1);
                        return;
                    case 1:
                        FieldActor_RequestState5(actor, 3, 5, -1);
                        return;
                    default:
                        return;
                }
            }
            const Vec3 *target = TownInsect_HeldPosition((u8) player);
            Vec3 eye = actor->position;
            eye.y = add32(eye.y, 0x1b33);
            int yaw = Math_Atan2(sub32(target->x, eye.x), sub32(target->z, eye.z));
            int pitch = Math_Atan2(sub32(target->y, eye.y), Vec_DistanceXZ(target, &eye));
            if (pitch >= 0x1800) {
                pitch = 0x1800;
            }
            yaw = (s16) (yaw - actor->yaw);
            FieldActor_TurnAngle(&actor->head_pitch, pitch, 0x400, 0x1770000, 0xc0000);
            FieldActor_TurnAngle(&actor->head_yaw, yaw, 0x400, 0x1770000, 0xc0000);
            return;
        }
        case 7: {
            int ready = TownInsect_HeldState((u8) player);
            if (ready == 3 || ready == 0) {
                work->step = 6;
            }
            return;
        }
        case 8:
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            EventQueue_FinishKind9();
            FieldActor_RequestState76(actor, 0, (u8) kind, work->slot, 6, -1);
            return;
        default:
            break;
    }
    TownInsect_HeldFromMatrix((u8) player, values, (Mtx43 *) &block, 0);
}
CLEAN_AS(func_ov003_022132bc, FieldActor_RunState57)

/* func_ov003_02213914: leaving state 0x57: the effect ends and the head faces ahead. */
void FieldActor_ExitState57(FieldActor *actor)
{
    if (actor->work.s57.effect != -1) {
        EffectSystem_EndHandle(actor->work.s57.effect);
    }
    actor->head_pitch = 0;
    actor->head_yaw = 0;
}
CLEAN_AS(func_ov003_02213914, FieldActor_ExitState57)

/* func_ov003_02213944: state 0x57's message handler: the state is asked for again with the
 * saved mode, slot and kind. */
void FieldActor_State57Message(FieldActor *actor, int arg)
{
    u8 step;
    u8 slot;
    u8 kind;
    u8 mode;
    /* QUIRK: the original reads the saved angle into a one-byte local, its second byte landing
     * past it in the stack frame; it is not used. */
    u16 angle;

    State57Saved_Get(&actor->saved.s57, &step, &slot, &kind, &mode, &angle);
    FieldActor_RequestState57(actor, mode, slot, kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02213944, FieldActor_State57Message)

/* func_ov003_02213988: entering state 0x57 with the request's slot, kind and mode. Mode 0 (the
 * insect is caught here) starts animation 0x5c with pose 5 in hand at step 0; for the actor of
 * this console sound 0x12 starts and func_0208d07c and func_02079774 note the catch. Mode 3
 * waits at step 3 (0x81c = 8); the others wait at step 7, mode 2 taken for any mode while
 * animation 0x6c plays (which then gives way to animation 0). The actor of this console saves
 * the step, slot, kind and mode (as requested) with angle 0. */
void FieldActor_EnterState57(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 slot = request->payload[0];
    u8 kind = request->payload[1];
    u8 mode = request->payload[2];
    State57Work *work = &actor->work.s57;

    if (mode == 0) {
        FieldActor_PlayAnimationOnce(actor, 0x5c, 3, 0);
        HeldItem_Act(actor->held, 5, 3, 1);
    }
    work->slot = slot;
    work->kind = kind;
    work->mode = mode;
    work->unk_04 = 0x39;
    work->unk_0A = (u8) ItemRecord_HasAllInsects();
    if (mode == 0) {
        if (is_local_player(actor)) {
            Music_AddValue(0x12, 0, 0);
            CatchPanel_CountInsect((void *) (uintptr_t) ScreenPanels_SecondPanel());
            VillagerEvent_InsectCaught(&actor->position);
        }
        work->step = 0;
    } else if (mode == 3) {
        work->step = 3;
        work->unk_04 = 0x3b;
        actor->unk_81C = 8;
    } else {
        if (actor->animation == 0x6c) {
            work->mode = 2;
            FieldActor_PlayAnimationLoop(actor, 0, 3, 3);
        }
        work->step = 7;
    }
    work->effect = -1;
    if (is_local_player(actor)) {
        State57Saved_Set(&actor->saved.s57, work->step, slot, kind, mode, 0);
    }
}
CLEAN_AS(func_ov003_02213988, FieldActor_EnterState57)

/* func_ov003_02213a80 */
int State57Saved_Angle(const State57Saved *saved)
{
    return PackedBytes_ReadS16(saved->angle);
}
CLEAN_AS(func_ov003_02213a80, State57Saved_Angle)

/* func_ov003_02213a8c */
int State57Saved_Step(const State57Saved *saved)
{
    return saved->step;
}
CLEAN_AS(func_ov003_02213a8c, State57Saved_Step)

/* func_ov003_02213a90 */
void State57Saved_Get(const State57Saved *saved, u8 *step, u8 *slot, u8 *kind, u8 *mode, u16 *angle)
{
    *step = saved->step;
    *slot = saved->slot;
    *kind = saved->kind;
    *mode = saved->mode;
    *angle = (u16) State57Saved_Angle(saved);
}
CLEAN_AS(func_ov003_02213a90, State57Saved_Get)

/* func_ov003_02213ab4 */
void State57Saved_SetAngle(State57Saved *saved, int angle)
{
    PackedBytes_WriteS16(saved->angle, angle);
}
CLEAN_AS(func_ov003_02213ab4, State57Saved_SetAngle)

/* func_ov003_02213ac0 */
void State57Saved_SetStep(State57Saved *saved, int step)
{
    saved->step = (u8) step;
}
CLEAN_AS(func_ov003_02213ac0, State57Saved_SetStep)

/* func_ov003_02213ac4 */
void State57Saved_Set(State57Saved *saved, u8 step, u8 slot, u8 kind, u8 mode, s16 angle)
{
    saved->step = step;
    saved->slot = slot;
    saved->kind = kind;
    saved->mode = mode;
    State57Saved_SetAngle(saved, angle);
}
CLEAN_AS(func_ov003_02213ac4, State57Saved_Set)

/* func_ov003_02213ae4: asks for state 0x57 with a mode, a slot and a kind; whether it was
 * queued. */
void *FieldActor_RequestState57(FieldActor *actor, u8 mode, u8 slot, u8 kind, u32 priority, s16 arg)
{
    StateRequest request;
    open_request(&request, 0x57, (int) priority, arg);
    request.payload[0] = slot;
    request.payload[1] = kind;
    request.payload[2] = mode;
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02213ae4, FieldActor_RequestState57)

/* ---- State 0x56: a swing of the held item, animation 0x5b */

/* func_ov003_02213b28: state 0x56's update. The actor of this console faces the request's yaw
 * and sweeps; another player's actor only checks what the swing hits. Then both slow down,
 * end the swing when it is over and turn towards the point ahead, and the tip of what the actor
 * holds is noted. */
void FieldActor_UpdateState56(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_FaceState56(actor);
        FieldActor_SweepState56(actor);
        FieldActor_AnimateState56(actor);
        FieldActor_MoveWithCollision(actor);
    } else {
        FieldActor_SweepState56Remote(actor);
        FieldActor_AnimateState56(actor);
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
    }
    FieldActor_EnterContact(actor);
    FieldActor_SlowState56(actor);
    FieldActor_EndState56(actor);
    FieldActor_TurnState56(actor);

    Vec3 tip = actor->unk_62C;
    Vec3 out;
    Globe_Unbend(&out, &tip);
    actor->work.s56.tip = out;
}
CLEAN_AS(func_ov003_02213b28, FieldActor_UpdateState56)

/* func_ov003_02213bf0: once the animation is over or stopped: with something caught, state 0x57
 * is asked for (mode 0) with the slot and the kind func_ov003_0222e5fc gives for it when
 * func_ov003_0222e538 answers 0, or forgotten when it answers 1; slot 0xff asks with kind 0x30.
 * With nothing caught, once the held item's animation (at 0x9c in it) is over the state after
 * this one is noted and the actor of this console moves on (9). */
void FieldActor_EndState56(FieldActor *actor)
{
    if (!anim_done(actor) && actor->anim.speed != 0) {
        return;
    }
    State56Work *work = &actor->work.s56;
    if (work->caught) {
        u8 slot = work->slot;
        if (slot == 0xff) {
            FieldActor_RequestState57(actor, 0, slot, 0x30, 6, -1);
            return;
        }
        u8 answer = TownInsect_Release(slot, (u8) actor->player);
        if (answer == 0) {
            u8 kind = (u8) TownInsect_Caught(slot);
            FieldActor_RequestState57(actor, 0, slot, kind, 6, -1);
        } else if (answer == 1) {
            work->caught = 0;
        }
        return;
    }
    const FrameCtrl *held_anim = (const FrameCtrl *) (const void *) (HeldItem_Model(actor->held) + 0x9c);
    if (FrameCtrl_IsDone(held_anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        if (is_local_player(actor)) {
            FieldActor_RequestState2(actor, 9, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_02213bf0, FieldActor_EndState56)

/* func_ov003_02213cd0: the speed at 0x98 slows by 0x171 a frame towards 0; effect 0x2b marks the
 * actor's stop. */
void FieldActor_SlowState56(FieldActor *actor)
{
    if (actor->unk_098 == 0) {
        return;
    }
    int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
    FieldActor_SetSpeed(actor, &speed);
    if (actor->unk_098 != 0) {
        return;
    }
    EffectSystem_StartKind(0x2b, &actor->position, &actor->yaw, 0);
}
CLEAN_AS(func_ov003_02213cd0, FieldActor_SlowState56)

/* func_ov003_02213d18: another player's swing, from frame 3 while it moves: unless it hits at
 * frame 4, the line from the swing's base to its tip is traced. */
void FieldActor_SweepState56Remote(FieldActor *actor)
{
    if (actor->anim.speed == 0) {
        return;
    }
    if (anim_frame(actor) < 3) {
        return;
    }
    if (FieldActor_HitState56(actor)) {
        return;
    }
    Vec3 at = actor->unk_68C;
    Globe_Unbend(&at, &at);
    Vec3 sweep = at;
    Vec3 base;
    Vec3 tip;
    FieldActor_State56Points(actor, &sweep, &base, &tip);
    Vec3 from = at;
    FieldActor_TraceState56(actor, &from, &base, &tip);
}
CLEAN_AS(func_ov003_02213d18, FieldActor_SweepState56Remote)

/* Stops the swing: flag 9, sound 0x846, the animation stops and the held item takes pose 4. */
static void stop_state56(FieldActor *actor)
{
    FieldActor_SetFlag(actor, 9);
    FieldActor_PlaySound(actor, 0x846);
    actor->anim.speed = 0;
    HeldItem_Act(actor->held, 4, 3, 1);
}

/* func_ov003_02213da0: tests the segment between `to` and `at` (func_020311bc). When it hits, the
 * swing stops, and at frame 5 the tile at `to` goes to func_0204489c; that counts as a hit
 * before frame 5. Otherwise at frame 5 another player's actor takes `from` as `to` and stops
 * when the ground there (func_02034270) has 0 at 0x30; failing that, and always for the actor
 * of this console, effect 0xb marks `from`, flag 9 is set and the held item takes pose 4
 * without the stop. Whether a hit counted. */
int FieldActor_TraceState56(FieldActor *actor, Vec3 *at, Vec3 *from, Vec3 *to)
{
    SegmentTest test;
    BOOL hit;

    CollisionSegmentHit_Construct((CollisionSegmentHit *) &test);
    if (CollisionQuery_Trace((CollisionTraceHit *) &test, to, at, 0x1b)) {
        hit = TRUE;
    } else {
        if (!anim_passed(actor, 5)) {
            CollisionSegmentHit_Destroy((CollisionSegmentHit *) &test);
            return 0;
        }
        hit = FALSE;
        if (!is_local_player(actor)) {
            CollisionGround_Init((CollisionGround *) &test.ground, from, 0, 0);
            if (test.ground.unk_30 == 0) {
                copy_point(to, from);
                hit = TRUE;
            }
            CollisionGround_Destroy((CollisionGround *) &test.ground);
        }
    }
    if (hit) {
        stop_state56(actor);
        if (anim_passed(actor, 5)) {
            int x = 0;
            int z = 0;
            Position_Tile(&x, &z, (const Position *) to);
            int tile[2] = {x, z};
            TileEffects_Strike((const TileEffectsTile *) tile);
        }
        if (anim_frame(actor) <= 4) {
            CollisionSegmentHit_Destroy((CollisionSegmentHit *) &test);
            return 1;
        }
    } else {
        EffectSystem_StartKind(0xb, from, NULL, 0);
        FieldActor_SetFlag(actor, 9);
        HeldItem_Act(actor->held, 4, 3, 1);
    }
    CollisionSegmentHit_Destroy((CollisionSegmentHit *) &test);
    return 0;
}
CLEAN_AS(func_ov003_02213da0, FieldActor_TraceState56)

/* func_ov003_02213ec0: at frame 4 the swing stops when FieldActor_CheckOther meets an object or
 * the ground 2.85 ahead is high (func_020310d0 at least 0x400); whether it stopped. */
int FieldActor_HitState56(FieldActor *actor)
{
    if (!anim_passed(actor, 4)) {
        return 0;
    }
    if (!FieldActor_CheckOther(actor)) {
        Vec3 ahead;
        int surface;
        FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov003_02238114);
        if (CollisionQuery_GroundY(&ahead, &surface, 0x19) < 0x400) {
            return 0;
        }
    }
    stop_state56(actor);
    return 1;
}
CLEAN_AS(func_ov003_02213ec0, FieldActor_HitState56)

/* func_ov003_02213f74: whether a swing stopped at `hit` still reaches the insect at `insect`.
 * Always on map objects 0x1b and 0x89 at `hit`. With the insect's flag set, when the insect's z
 * lies between the actor's and `hit`'s (the actor's side included). Otherwise by the directions
 * from the actor, each folded to 0-0x8000 (func_020e8b4c): equal ones compare by z as above;
 * the insect's above 0x4000 with `hit`'s beyond it, or `hit`'s below 0x4000 and not beyond the
 * insect's, reach; else the insect is reached when the squared distance to `hit` less its part
 * along the insect's direction is at least 0x900000. */
int FieldActor_State56Reaches(FieldActor *actor, const Vec3 *hit, const Vec3 *insect, const u8 *insect_flag)
{
    Vec3 here = actor->position;

    const u16 *object = AcreTile_ItemAt(data_021c80bc, hit, 0);
    if (object != NULL && (*object == 0x1b || *object == 0x89)) {
        return 1;
    }
    if (*insect_flag == 0) {
        int a1 = Math_Atan2(sub32(insect->x, here.x), sub32(insect->z, here.z));
        int a2 = Math_Atan2(sub32(hit->x, here.x), sub32(hit->z, here.z));
        /* QUIRK: a fold of 0x8000 is kept as an s16, -0x8000. */
        a1 = (s16) Math_AbsDiff16(a1, 0);
        a2 = (s16) Math_AbsDiff16(a2, 0);
        if (a1 != a2) {
            if ((a1 >= 0x4000 && a2 > a1) || (a2 < 0x4000 && a2 <= a1)) {
                return 1;
            }
            int dx = sub32(hit->x, here.x);
            int dz = sub32(hit->z, here.z);
            int d = (int) ((u32) dx * (u32) dx + (u32) dz * (u32) dz);
            s16 c = FX_SinCosTable_[((u16) (a1 - a2) >> 4) * 2 + 1];
            int t = FX_MulFunc(d, c);
            t = FX_MulFunc(t, c);
            return sub32(d, t) >= 0x900000;
        }
    }
    int z = insect->z;
    return (here.z >= z && z > hit->z) || (here.z <= z && z < hit->z);
}
CLEAN_AS(func_ov003_02213f74, FieldActor_State56Reaches)

/* func_ov003_022140a8: what the swing meets. At frame 4: an object FieldActor_CheckOther meets
 * stops the swing and gives 3 for verdict 4, else 1 with an insect and 2 without; high ground
 * (func_020310d0 at least 0x400) at the tile of the point 2.85 ahead stops it and gives 1 when
 * there is an insect the swing still reaches, else 2. At frame 3, with an insect, high ground
 * at the tile 2.0 ahead gives the same 1 or 2 without stopping. Otherwise 0. */
int FieldActor_ClassifyState56(FieldActor *actor, const u8 *has_insect, const Vec3 *insect, const u8 *insect_flag)
{
    Vec3 ahead;
    int surface;

    if (anim_passed(actor, 4)) {
        if (FieldActor_CheckOther(actor)) {
            stop_state56(actor);
            if (actor->other_result == 4) {
                return 3;
            }
            return *has_insect ? 1 : 2;
        }
        FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov003_0223811c);
        AcreTile_SnapToTileCentre(&ahead, &ahead);
        if (CollisionQuery_GroundY(&ahead, &surface, 0x19) >= 0x400) {
            stop_state56(actor);
            if (*has_insect && FieldActor_State56Reaches(actor, &ahead, insect, insect_flag)) {
                return 1;
            }
            return 2;
        }
    } else if (anim_passed(actor, 3)) {
        if (*has_insect) {
            FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov003_02238120);
            AcreTile_SnapToTileCentre(&ahead, &ahead);
            if (CollisionQuery_GroundY(&ahead, &surface, 0x19) >= 0x400) {
                return FieldActor_State56Reaches(actor, &ahead, insect, insect_flag) ? 1 : 2;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_022140a8, FieldActor_ClassifyState56)

/* func_ov003_02214200: the points of the swing by the frame, from the actor's position and yaw:
 * `base` starts at the position and `sweep` is the caller's. Frame 3 plays sound 0x845, raises
 * `sweep` by 1.87 and puts `base` 1.9 ahead and 2.3 up; frame 4 puts `sweep` there and `base`
 * 2.65 ahead; frame 5 puts `sweep` 2.65 ahead and `base` 2.5 ahead and 0.4 down. `tip` is the
 * tip of what the actor holds (func_0203f7d0). */
void FieldActor_State56Points(FieldActor *actor, Vec3 *sweep, Vec3 *base, Vec3 *tip)
{
    const Vec3 *position = &actor->position;
    copy_point(base, position);

    int index = ((u16) actor->yaw >> 4) * 2;
    fx32 sin = FX_SinCosTable_[index];
    fx32 cos = FX_SinCosTable_[index + 1];

    switch (anim_frame(actor)) {
        case 3:
            FieldActor_PlaySound(actor, 0x845);
            sweep->y = add32(sweep->y, 0x1dd3);
            base->x = add32(base->x, FX_MulFunc(sin, 0x1e66));
            base->y = add32(base->y, 0x24cd);
            base->z = add32(base->z, FX_MulFunc(cos, 0x1e66));
            break;
        case 4:
            copy_point(sweep, position);
            sweep->x = add32(sweep->x, FX_MulFunc(sin, 0x1e66));
            sweep->y = add32(sweep->y, 0x24cd);
            sweep->z = add32(sweep->z, FX_MulFunc(cos, 0x1e66));
            base->x = add32(base->x, FX_MulFunc(sin, 0x2a66));
            base->z = add32(base->z, FX_MulFunc(cos, 0x2a66));
            break;
        case 5:
            copy_point(sweep, position);
            sweep->x = add32(sweep->x, FX_MulFunc(sin, 0x2a66));
            sweep->z = add32(sweep->z, FX_MulFunc(cos, 0x2a66));
            base->x = add32(base->x, FX_MulFunc(sin, 0x2800));
            base->y = sub32(base->y, 0x666);
            base->z = add32(base->z, FX_MulFunc(cos, 0x2800));
            break;
        default:
            break;
    }
    Vec3 at = actor->unk_62C;
    Globe_Unbend(&at, &at);
    copy_point(tip, &at);
}
CLEAN_AS(func_ov003_02214200, FieldActor_State56Points)

/* func_ov003_02214384: the swing of the actor of this console, from frame 3 while it moves and
 * until it is over. Before frame 6, until something is caught, func_020899a8 looks for an
 * insect along the sweep (radius 0xa00 with the held item 0x1376, else 0xd1f) and gives its
 * slot; its point (func_ov003_0222f458) moves 0x100 in z when func_ov003_0222f490 flags it.
 * Then by FieldActor_ClassifyState56: 1 catches the insect if func_ov003_0222e3a4 lets it, 2
 * ends here, 3 catches slot 0xff unless something is caught; 0 traces the line, and with an
 * insect found catches it as above when the line hit nothing or the insect lies more than a
 * quarter turn from the tip's direction (func_020e8b4c). A catch plays sound 0x847. */
void FieldActor_SweepState56(FieldActor *actor)
{
    if (actor->anim.speed == 0) {
        return;
    }
    if (anim_done(actor)) {
        return;
    }
    if (anim_frame(actor) < 3) {
        return;
    }

    u8 has_insect = 0;
    u8 insect_flag = 0;
    u8 slot = 0;
    Vec3 insect = {0, 0, 0};

    Vec3 at = actor->unk_68C;
    Globe_Unbend(&at, &at);
    Vec3 sweep = at;
    Vec3 base;
    Vec3 tip;
    FieldActor_State56Points(actor, &sweep, &base, &tip);

    State56Work *work = &actor->work.s56;
    if (work->caught == 0 && anim_frame(actor) < 6) {
        u16 item;
        FieldActor_RecordHeldItem(&item, actor);
        int radius = item == 0x1376 ? 0xa00 : 0xd1f;
        if (CatchSphere_FindAlong(&sweep, &base, radius, &slot, 0)) {
            has_insect = 1;
            TownInsect_GetPosition(&insect, slot);
            insect_flag = (u8) TownInsect_KindHighPlace(slot);
            if (insect_flag) {
                insect.z = add32(insect.z, 0x100);
            }
        }
    }

    switch (FieldActor_ClassifyState56(actor, &has_insect, &insect, &insect_flag)) {
        case 1:
            break;
        case 2:
            return;
        case 3:
            if (work->caught) {
                return;
            }
            work->caught = 1;
            work->slot = 0xff;
            FieldActor_PlaySound(actor, 0x847);
            return;
        default: {
            Vec3 from = at;
            int traced = FieldActor_TraceState56(actor, &from, &base, &tip);
            if (!has_insect) {
                return;
            }
            int angle = 0x7fff;
            if (traced) {
                angle = Math_Atan2(sub32(insect.x, tip.x), sub32(insect.z, tip.z));
            }
            if (Math_AbsDiff16(angle, 0) <= 0x4000) {
                return;
            }
            break;
        }
    }
    if (TownInsect_Catch(slot)) {
        work->caught = 1;
        work->slot = slot;
        FieldActor_PlaySound(actor, 0x847);
    }
}
CLEAN_AS(func_ov003_02214384, FieldActor_SweepState56)

/* func_ov003_02214568: the actor turns towards the point ahead of it. */
void FieldActor_TurnState56(FieldActor *actor)
{
    Vec3 ahead;
    FieldActor_PointAheadOfSelf(&ahead, actor);
    FieldActor_SetContactBSized(actor, &ahead, 0x99a, 0x1000);
    FieldBody_Enter((FieldBody *) actor->unk_1C4);
}
CLEAN_AS(func_ov003_02214568, FieldActor_TurnState56)

/* func_ov003_022145a0: the actor faces the request's yaw. */
void FieldActor_FaceState56(FieldActor *actor)
{
    FieldActor_TurnTowards(actor, actor->work.s56.yaw);
}
CLEAN_AS(func_ov003_022145a0, FieldActor_FaceState56)

/* func_ov003_022145b0: the animation steps; sound 0x848 when it has just ended. */
void FieldActor_AnimateState56(FieldActor *actor)
{
    BOOL was_done = anim_done(actor);
    FieldActor_UpdateBody(actor);
    if (!was_done && anim_done(actor)) {
        FieldActor_PlaySound(actor, 0x848);
    }
}
CLEAN_AS(func_ov003_022145b0, FieldActor_AnimateState56)

/* func_ov003_022145f8: state 0x56's message handler: the state is asked for again. */
void FieldActor_State56Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState56(actor, 6, arg);
}
CLEAN_AS(func_ov003_022145f8, FieldActor_State56Message)

/* func_ov003_02214604: entering state 0x56 with the request's yaw: nothing caught, animation
 * 0x5b with pose 3 in hand. */
void FieldActor_EnterState56(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    State56Work *work = &actor->work.s56;
    s16 yaw;
    memcpy(&yaw, request->payload, sizeof(yaw));

    work->caught = 0;
    work->yaw = yaw;
    work->slot = 0xff;
    FieldActor_PlayAnimationOnce(actor, 0x5b, 3, 0);
    HeldItem_Act(actor->held, 3, 3, 0);
}
CLEAN_AS(func_ov003_02214604, FieldActor_EnterState56)

/* func_ov003_02214644: asks for state 0x56 with a yaw: towards unk_14C from where the frame
 * began when unk_144 is 2, else the actor's own; whether it was queued. */
int FieldActor_RequestState56(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
    s16 yaw;

    open_request(&request, 0x56, priority, arg);
    if (actor->unk_144 == 2) {
        yaw = Math_Atan2(sub32(actor->unk_14C.x, actor->start_position.x), sub32(actor->unk_14C.z, actor->start_position.z));
    } else {
        yaw = actor->yaw;
    }
    memcpy(request.payload, &yaw, sizeof(yaw));
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02214644, FieldActor_RequestState56)

/* ---- State 0x55: the fish caught is put away (animation 0x5a) */

/* func_ov003_022146bc: state 0x55's update. */
void FieldActor_UpdateState55(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState55(actor);
    } else {
        FieldActor_EndState55Remote(actor);
    }
}
CLEAN_AS(func_ov003_022146bc, FieldActor_UpdateState55)

/* func_ov003_022146fc: another player's actor: at the animation's end the state after this one
 * is noted and animation 0x6c starts with pose 0x13 in hand. */
void FieldActor_EndState55Remote(FieldActor *actor)
{
    if (anim_done(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_PlayAnimationLoop(actor, 0x6c, 6, 6);
        HeldItem_Act(actor->held, 0x13, 6, 0);
    }
}
CLEAN_AS(func_ov003_022146fc, FieldActor_EndState55Remote)

/* The fish placed at the hand point with its own scale (func_ov003_0222aaa0). */
static void place_fish_default(HookedFish *fish, const Vec3 *hand, Vec3 *scale)
{
    PlayerFish_KindScale(scale, fish->kind);
    Vec3 at = *hand;
    Vec3 sized = *scale;
    PlayerFish_PlaceForShadow((FishShadow *) fish, &at, &sized);
}

/* func_ov003_0221474c: state 0x55 for the actor of this console, by the work's step. The fish
 * hangs at the block's point; during the first six frames of animation 0x5a it shrinks from its
 * size (the table's percent of the fish's row, or 1.0 with no fish) to 0, when
 * func_ov003_0222a8a8 runs.
 *   Step 0: at the animation's end the actor moves on (6), gives the fish's item to
 *     func_0209a110, and func_02060460 lets the fish go.
 *   Step 1: after animation 0x5a, animation 0x6c with pose 0x13. The word at 0x81c: at 5 it
 *     becomes 6 once func_0206f6f8 accepts the item; at 6 it becomes 0xf once func_0206fbc0
 *     says so, and when func_0206fc6c then says so the fish is let go (func_020604fc), the
 *     receiver is released and the actor moves on: to state 0x8f when func_0206f6a4 gives a
 *     fish item (0x12e8-0x131f), else (6) at step 2. From 0xf the items 0x1320-0x1322 go to
 *     step 3; others get their own scale back and state 0x8f with step 2 saved. Then
 *     func_02060448 and the receiver is released.
 *   Step 2: the actor moves on (6).
 *   Step 3: waits for func_02043554 to give a value other than -1, then step 2. */
void FieldActor_RunState55(FieldActor *actor)
{
    HookedFish *fish = (HookedFish *) FishingFloat_Fish(held_line(actor));
    int size = 0;
    if (actor->animation == 0x5a) {
        int frame = anim_frame(actor);
        if (frame < 6) {
            if (fish != NULL) {
                int full = (data_ov003_0223c026[fish->size * 0x14] << 12) / 100;
                size = (s16) (full - full * frame / 6);
            } else {
                size = (s16) (0x1000 - 0x2ab * frame);
            }
        }
    }
    Vec3 scale = {size, size, size};
    FieldActorBlock48 block = actor->unk_698;
    FieldActor_OffsetMatrix(&block, NULL);
    Vec3 hand = block_point(&block);

    u16 item = ITEM_NONE;
    if (fish != NULL) {
        Globe_Unbend(&hand, &hand);
        Vec3 at = hand;
        Vec3 sized = scale;
        PlayerFish_PlaceForShadow((FishShadow *) fish, &at, &sized);
        item = (u16) (fish->kind + 0x12e8);
        if (size == 0) {
            PlayerFish_AnnounceHeld(actor->player);
        }
    }

    u8 *step = &actor->work.step;
    switch (*step) {
        case 0:
            if (!anim_done(actor)) {
                break;
            }
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestState2(actor, 6, 1, -1);
            if (is_local_player(actor)) {
                u16 code = item;
                CurrentPockets_Receive(&code);
            }
            FishingFloat_LetFishGo(held_line(actor));
            break;
        case 1:
            if (actor->animation == 0x5a) {
                if (!anim_done(actor)) {
                    break;
                }
                FieldActor_PlayAnimationLoop(actor, 0x6c, 6, 6);
                HeldItem_Act(actor->held, 0x13, 6, 0);
            }
            if (is_local_player(actor)) {
                if (actor->unk_81C == 5) {
                    if (GroupParams_OpenWithItemAndObject(item, fish)) {
                        actor->unk_81C = 6;
                    }
                    break;
                }
                if (actor->unk_81C == 6) {
                    if (!GroupParams_CanOpen()) {
                        break;
                    }
                    actor->unk_81C = 0xf;
                    if (GroupParams_C4CIs1()) {
                        FishingFloat_SetFish(held_line(actor), 0);
                        release_receiver(actor);
                        EventQueue_FinishKind9();
                        u16 got = GroupParams_ItemC();
                        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                        if (got >= 0x12e8 && got <= 0x131f) {
                            FieldActor_RequestLook(actor, &data_ov003_02238104, 0, 6, -1);
                            break;
                        }
                        FieldActor_RequestState2(actor, 6, 1, -1);
                        *step = 2;
                        break;
                    }
                } else if (actor->unk_81C < 0xf) {
                    break;
                }
                if (is_item_1320(item)) {
                    *step = 3;
                    if (actor->unk_810 == -1) {
                        actor->unk_810 = TileRequests_AskDropFor(actor->player, item);
                        if (actor->unk_810 != -1) {
                            *step = 2;
                        }
                    }
                } else {
                    if (fish != NULL) {
                        place_fish_default(fish, &hand, &scale);
                    }
                    FieldActor_RequestLook(actor, &data_ov003_02238108, 0, 6, -1);
                    State55Saved_SetStep(&actor->saved.step55, 2);
                }
                FishingFloat_TellPlayerFish(held_line(actor));
                release_receiver(actor);
                EventQueue_FinishKind9();
                break;
            }
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            if (State55Saved_Step(&actor->saved.step55) == 2) {
                if (fish != NULL) {
                    place_fish_default(fish, &hand, &scale);
                }
                FishingFloat_TellPlayerFish(held_line(actor));
                *step = 2;
                FieldActor_PlayAnimationLoop(actor, 0, 6, 6);
            }
            break;
        case 2:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestState2(actor, 6, 1, -1);
            break;
        case 3:
            if (actor->unk_810 == -1) {
                actor->unk_810 = TileRequests_AskDropFor(actor->player, item);
                if (actor->unk_810 != -1) {
                    *step = 2;
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221474c, FieldActor_RunState55)

/* func_ov003_02214ba0: state 0x55's message handler: the state is asked for again at the saved
 * step. */
void FieldActor_State55Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState55(actor, (char) State55Saved_Step(&actor->saved.step55), 6, arg);
}
CLEAN_AS(func_ov003_02214ba0, FieldActor_State55Message)

/* func_ov003_02214bc8: entering state 0x55 at the request's step (saved too): animation 0x5a and
 * sound 0x4f. */
void FieldActor_EnterState55(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 step = request->payload[0];
    actor->work.step = step;
    State55Saved_SetStep(&actor->saved.step55, step);
    FieldActor_PlayAnimationOnce(actor, 0x5a, 3, 3);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_02214bc8, FieldActor_EnterState55)

/* func_ov003_02214bfc */
int State55Saved_Step(const u8 *saved)
{
    return *saved;
}
CLEAN_AS(func_ov003_02214bfc, State55Saved_Step)

/* func_ov003_02214c00 */
void State55Saved_SetStep(u8 *saved, int step)
{
    *saved = (u8) step;
}
CLEAN_AS(func_ov003_02214c00, State55Saved_SetStep)

/* func_ov003_02214c04: asks for state 0x55 at a step; whether it was queued. */
int FieldActor_RequestState55(FieldActor *actor, char step, int priority, int arg)
{
    StateRequest request;
    open_request(&request, 0x55, priority, arg);
    request.payload[0] = (u8) step;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02214c04, FieldActor_RequestState55)

/* ---- State 0x54: the fish caught is shown (animation 0x59) */

/* func_ov003_02214c40: state 0x54's update: func_0200ee40 runs between func_02010f5c and the
 * others, with the points and blocks it would change kept. Another player's actor notes the
 * state after this one and holds still. */
void FieldActor_UpdateState54(FieldActor *actor)
{
    KeptAcrossEE40 kept;

    FieldActor_UpdateBody(actor);
    keep_across_ee40(actor, &kept);
    FieldActor_RebuildPose(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState54(actor);
    } else {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_TurnToZero(actor, 0x400);
    }
    restore_after_ee40(actor, &kept);
}
CLEAN_AS(func_ov003_02214c40, FieldActor_UpdateState54)

/* func_ov003_02214d2c: state 0x54 for the actor of this console. The actor holds still; the
 * fish hangs, at its own scale, at the block's point moved by an offset that grows over the end
 * of the animation (from frame 0x10; fixed when the mode is not 0). Frame 3 of animation 0x59
 * plays func_0203ae98. Before frame 0x11, in mode 0, steps below 5 wait.
 *   Step 0: once func_0203e1c4 says so the receiver is registered under "obj_etc_getfish" with
 *     the item 0x12e8 + kind (what func_0203cbd0 leaves of it becomes `item`), its link is
 *     asked for, the sounds are set, and step 1 follows at once.
 *   Step 1: once the link is open: step 5 (0x81c = 0xe) when func_0203cc38 says so and it did
 *     not on entering, else step 2 (0x81c = 8).
 *   Step 2: with func_02099fe8 at -1, step 3 when func_02043368 accepts (0x81c = 4 for the items
 *     0x1320-0x1322, else 0), else step 4 (0x81c = 1). Otherwise once the link closes the
 *     receiver is released and state 0x55 is asked for at step 0.
 *   Step 3: from 0x81c = 0xf on: the items 0x1320-0x1322 go to step 6 and on as there, others to
 *     step 4. Before, once the link closes the receiver is released and state 0x55 is asked for
 *     at step 1.
 *   Step 4: once the link closes func_02060448 runs, the receiver is released, the state after
 *     this one is noted and state 0x8f asked for.
 *   Step 5: once the link closes the receiver is released and func_020094a0 runs.
 *   Step 6: waits for func_02043554 to give a value other than -1, then step 4. */
void FieldActor_RunState54(FieldActor *actor)
{
    State54Work *work = &actor->work.s54;

    FieldActor_TurnToZero(actor, 0x400);
    HookedFish *fish = (HookedFish *) FishingFloat_Fish(held_line(actor));
    if (fish != NULL) {
        FieldActorBlock48 block = actor->unk_698;
        Vec3 scale;
        PlayerFish_KindScale(&scale, fish->kind);
        Vec3 offset = {0x4cd, 0, 0};
        int frame = anim_frame(actor);
        if (work->mode != 0) {
            offset.x = 0x800;
            offset.y = 0x19a;
            offset.z = -0x19a;
        } else if (frame >= 0x10) {
            /* QUIRK: on the last frame of a 0x10-frame animation the divisor is 0, which the
             * ROM's division answers with the numerator. */
            int d = div_s32((frame - 0xf) * 0x19a, (int) anim_frames(actor) - 0x10);
            offset.x = add32(offset.x, d * 2);
            offset.y = add32(offset.y, d);
            offset.z = sub32(offset.z, d);
        }
        FieldActor_OffsetMatrix(&block, &offset);
        Vec3 at = block_point(&block);
        Globe_Unbend(&at, &at);
        Vec3 sized = scale;
        PlayerFish_PlaceForShadow((FishShadow *) fish, &at, &sized);
    }

    if (actor->animation == 0x59 && anim_passed(actor, 3)) {
        CameraControl_SetMode4();
    }
    if (anim_frame(actor) < 0x11 && work->step < 5 && work->mode == 0) {
        return;
    }

    switch (work->step) {
        case 0:
            if (EventQueue_RequestKind9()) {
                work->step = 1;
                SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
                FieldActor_SetFlag(actor, 0x11);
                MessageReceiver_SetName((MessageReceiver *) actor->receiver, data_ov003_02238158);
                u8 kind = work->kind;
                actor->receiver_unk_1E = kind;
                u16 code = (u16) (kind + 0x12e8);
                ItemRecord_MarkHadByCurrent(&code);
                actor->unk_822 = code;
                actor->item = actor->unk_822;
                actor->link->requested = 1;
                Music_DropPriority(0x12);
                Music_AddValue(0xc, 0, 4);
                Music_Add(0xd, 0x39, 0x7f, 1);
            }
            /* fall through */
        case 1:
            if (actor->link == NULL || actor->link->open == 0) {
                break;
            }
            if (ItemRecord_HasAllFish() && work->unk_05 == 0) {
                work->step = 5;
                actor->unk_81C = 0xe;
                break;
            }
            work->step = 2;
            actor->unk_81C = 8;
            break;
        case 2:
            if (CurrentPockets_FreeSlot() == -1) {
                int point[2] = {0, 0};
                if (TileRequests_FindDropTile(0x10, (TileRequestTile *) point, NULL)) {
                    work->step = 3;
                    actor->unk_81C = is_item_1320(actor->item) ? 4 : 0;
                    break;
                }
                work->step = 4;
                actor->unk_81C = 1;
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            EventQueue_FinishKind9();
            FieldActor_RequestState55(actor, 0, 6, -1);
            CameraControl_ResetMode();
            break;
        case 3:
            if (actor->unk_81C >= 0xf) {
                if (!is_item_1320(actor->item)) {
                    work->step = 4;
                    break;
                }
                work->step = 6;
                if (actor->unk_810 != -1) {
                    break;
                }
                actor->unk_810 = TileRequests_AskDropFor(actor->player, actor->item);
                if (actor->unk_810 != -1) {
                    work->step = 4;
                }
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            FieldActor_RequestState55(actor, 1, 6, -1);
            CameraControl_ResetMode();
            break;
        case 4:
            if (!link_closed(actor)) {
                break;
            }
            FishingFloat_TellPlayerFish(held_line(actor));
            close_receiver(actor);
            EventQueue_FinishKind9();
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestLook(actor, &data_ov003_02238100, 0, 6, -1);
            CameraControl_ResetMode();
            break;
        case 5:
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            EventQueue_FinishKind9();
            FieldActor_RequestState76(actor, 1, work->kind, 0, 6, -1);
            break;
        case 6:
            if (actor->unk_810 != -1) {
                break;
            }
            actor->unk_810 = TileRequests_AskDropFor(actor->player, actor->item);
            if (actor->unk_810 != -1) {
                work->step = 4;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02214d2c, FieldActor_RunState54)

/* func_ov003_02215164: state 0x54's message handler: the state is asked for again with the saved
 * mode. */
void FieldActor_State54Message(FieldActor *actor, int arg)
{
    u8 mode;
    State54Saved_Get(&actor->saved.mode54, &mode);
    FieldActor_RequestState54(actor, (char) mode, 6, arg);
}
CLEAN_AS(func_ov003_02215164, FieldActor_State54Message)

/* func_ov003_02215190: entering state 0x54 with the request's mode (saved too). Mode 0 starts at
 * step 0 with animation 0x59 and pose 0x1c in hand; the actor of this console takes the hooked
 * fish's kind, and for kinds below 0x38 func_02079798 and func_0208d09c note the catch. Other
 * modes start at step 2 (0x81c = 8).
 * REQUIRES: in mode 0 a fish hangs from the held item for the actor of this console (the
 * original reads its kind without a check). */
void FieldActor_EnterState54(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 mode = request->payload[0];
    State54Work *work = &actor->work.s54;

    work->mode = mode;
    work->unk_00 = 0x39;
    work->unk_05 = (u8) ItemRecord_HasAllFish();
    if (mode == 0) {
        if (is_local_player(actor)) {
            s8 kind = ((HookedFish *) FishingFloat_Fish(held_line(actor)))->kind;
            work->kind = (u8) kind;
            if (kind < 0x38) {
                VillagerEvent_FishCaught(&actor->position);
                CatchPanel_CountFish((void *) (uintptr_t) ScreenPanels_SecondPanel());
            }
        }
        work->step = 0;
        FieldActor_PlayAnimationOnce(actor, 0x59, 3, 0);
        HeldItem_Act(actor->held, 0x1c, 3, 1);
    } else {
        work->step = 2;
        work->unk_00 = 0x3a;
        actor->unk_81C = 8;
    }
    State54Saved_Set(&actor->saved.mode54, mode);
}
CLEAN_AS(func_ov003_02215190, FieldActor_EnterState54)

/* func_ov003_02215234 */
void State54Saved_Get(const u8 *saved, u8 *mode)
{
    *mode = *saved;
}
CLEAN_AS(func_ov003_02215234, State54Saved_Get)

/* func_ov003_0221523c */
void State54Saved_Set(u8 *saved, int mode)
{
    *saved = (u8) mode;
}
CLEAN_AS(func_ov003_0221523c, State54Saved_Set)

/* func_ov003_02215240: asks for state 0x54 with a mode; whether it was queued. */
int FieldActor_RequestState54(FieldActor *actor, char mode, int priority, int arg)
{
    StateRequest request;
    open_request(&request, 0x54, priority, arg);
    request.payload[0] = (u8) mode;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02215240, FieldActor_RequestState54)

/* ---- State 0x53: animation 0x58 */

/* func_ov003_0221527c: state 0x53's update. */
void FieldActor_UpdateState53(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState53(actor);
    }
}
CLEAN_AS(func_ov003_0221527c, FieldActor_UpdateState53)

/* func_ov003_022152b4: at the animation's end, once func_02060474 says so of what hangs from the
 * held item, state 0x54 is asked for (mode 0). */
void FieldActor_EndState53(FieldActor *actor)
{
    if (anim_done(actor) && FishingFloat_FishFlag80(held_line(actor))) {
        FieldActor_RequestState54(actor, 0, 6, -1);
    }
}
CLEAN_AS(func_ov003_022152b4, FieldActor_EndState53)

/* func_ov003_022152ec: state 0x53's message handler: the state is asked for again. */
void FieldActor_State53Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState53(actor, 6, arg);
}
CLEAN_AS(func_ov003_022152ec, FieldActor_State53Message)

/* func_ov003_022152f8: entering state 0x53: animation 0x58 with pose 0x1b in hand, sounds 0x84c
 * and 0x84e, and unk_5D0 kept at unk_8C4. */
void FieldActor_EnterState53(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x58, 3, 0);
    HeldItem_Act(actor->held, 0x1b, 3, 1);
    FieldActor_PlaySound(actor, 0x84c);
    FieldActor_PlaySound(actor, 0x84e);
    copy_point(&actor->unk_8C4, &actor->unk_5D0);
}
CLEAN_AS(func_ov003_022152f8, FieldActor_EnterState53)

/* func_ov003_0221535c: asks for state 0x53; whether it was queued. */
void *FieldActor_RequestState53(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x53, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221535c, FieldActor_RequestState53)

/* ---- State 0x52: animation 0x57 */

/* func_ov003_02215394: state 0x52's update. The speed at 0x98 slows by 0xc5 a frame towards 0,
 * as a magnitude, and is stored negated. */
void FieldActor_UpdateState52(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FieldActor_FollowReported(actor)) {
        FieldActor_MoveWithCollision(actor);
    }
    FieldActor_EnterContact(actor);
    int speed = sub32(0, FieldActor_StepDown(abs32(actor->unk_098), 0, 0xc5));
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState52(actor);
}
CLEAN_AS(func_ov003_02215394, FieldActor_UpdateState52)

/* func_ov003_022153e8: at the animation's end the actor of this console runs func_0203b144, the
 * actor moves on and the held item takes pose 0x13. */
void FieldActor_EndState52(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    if (is_local_player(actor)) {
        CameraControl_ResetMode();
    }
    move_on(actor);
    HeldItem_Act(actor->held, 0x13, 3, 0);
}
CLEAN_AS(func_ov003_022153e8, FieldActor_EndState52)

/* func_ov003_02215454: state 0x52's message handler: the state is asked for again. */
void FieldActor_State52Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState52(actor, 6, arg);
}
CLEAN_AS(func_ov003_02215454, FieldActor_State52Message)

/* func_ov003_02215460: entering state 0x52: the speed at 0x98 starts at -1049 (the word at
 * 0x0223812c), animation 0x57 with pose 0x1a in hand. */
void FieldActor_EnterState52(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_SetSpeed(actor, &data_ov003_0223812c);
    FieldActor_PlayAnimationOnce(actor, 0x57, 3, 0);
    HeldItem_Act(actor->held, 0x1a, 3, 0);
}
CLEAN_AS(func_ov003_02215460, FieldActor_EnterState52)

/* func_ov003_02215494: asks for state 0x52; whether it was queued. */
void *FieldActor_RequestState52(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x52, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02215494, FieldActor_RequestState52)

/* ---- State 0x51: animation 0x56 */

/* func_ov003_022154cc: state 0x51's update. */
void FieldActor_UpdateState51(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState51(actor);
}
CLEAN_AS(func_ov003_022154cc, FieldActor_UpdateState51)

/* func_ov003_022154ec: at the animation's end the state after this one is noted and the actor
 * moves on: func_02008c40 (5) with the request's byte, else func_0200d4e8 (3). The result is
 * theirs, 0 before the end. */
int FieldActor_EndState51(FieldActor *actor)
{
    int done = FrameCtrl_IsDone(&actor->anim);
    if (done == 0) {
        return done;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (actor->work.s51_flag != 0) {
        return FieldActor_RequestState79(actor, 5, -1);
    }
    return FieldActor_RequestState2(actor, 3, 1, -1);
}
CLEAN_AS(func_ov003_022154ec, FieldActor_EndState51)

/* func_ov003_02215544: state 0x51's message handler: the state is asked for again with the saved
 * byte. */
void FieldActor_State51Message(FieldActor *actor, int arg)
{
    u8 flag;
    State51Saved_Get(&actor->saved.flag51, &flag);
    FieldActor_RequestState51(actor, flag, 6, arg);
}
CLEAN_AS(func_ov003_02215544, FieldActor_State51Message)

/* func_ov003_02215570: entering state 0x51 with the request's byte (kept in the work and saved):
 * animation 0x56 with pose 0x19 in hand, sounds 0x84c and 0x84e, unk_5D0 kept at unk_8C4; the
 * actor of this console runs func_0203b144. */
void FieldActor_EnterState51(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 flag = request->payload[0];

    FieldActor_SetState51Work(&actor->work.s51_flag, flag);
    FieldActor_SetState51Saved(&actor->saved.flag51, flag);
    FieldActor_PlayAnimationOnce(actor, 0x56, 3, 0);
    HeldItem_Act(actor->held, 0x19, 3, 0);
    FieldActor_PlaySound(actor, 0x84c);
    FieldActor_PlaySound(actor, 0x84e);
    copy_point(&actor->unk_8C4, &actor->unk_5D0);
    if (is_local_player(actor)) {
        CameraControl_ResetMode();
    }
}
CLEAN_AS(func_ov003_02215570, FieldActor_EnterState51)

/* func_ov003_02215614 */
void State51Saved_Get(const u8 *saved, u8 *flag)
{
    *flag = *saved;
}
CLEAN_AS(func_ov003_02215614, State51Saved_Get)

/* func_ov003_0221561c */
void FieldActor_SetState51Saved(u8 *saved, int flag)
{
    *saved = (u8) flag;
}
CLEAN_AS(func_ov003_0221561c, FieldActor_SetState51Saved)

/* func_ov003_02215620 */
void FieldActor_SetState51Work(u8 *work, int flag)
{
    *work = (u8) flag;
}
CLEAN_AS(func_ov003_02215620, FieldActor_SetState51Work)

/* func_ov003_02215624: asks for state 0x51 with a byte; whether it was queued. */
void *FieldActor_RequestState51(FieldActor *actor, int flag, int priority, int arg)
{
    StateRequest request;
    open_request(&request, 0x51, priority, arg);
    FieldActor_SetState51Args(request.payload, flag);
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02215624, FieldActor_RequestState51)

/* func_ov003_02215664 */
void FieldActor_SetState51Args(u8 *args, int flag)
{
    *args = (u8) flag;
}
CLEAN_AS(func_ov003_02215664, FieldActor_SetState51Args)

/* ---- State 0x50: animation 0x55, after something takes the line of state 0x4f */

extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);

static_assert(offsetof(FieldActor, line_mode) == 0x5cc, "line mode");
static_assert(offsetof(FieldActor, unk_600) == 0x600, "0x600");
static_assert(offsetof(FieldActor, unk_668) == 0x668, "0x668");
static_assert(offsetof(FieldActor, unk_698) == 0x698, "0x698");
static_assert(offsetof(FieldActor, work.s4b.unk_03) == 0x7d7, "state 0x4a 0x03");

static int mul32(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

/* func_ov003_02215668: state 0x50's update. */
void FieldActor_UpdateState50(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState50(actor);
}
CLEAN_AS(func_ov003_02215668, FieldActor_UpdateState50)

/* func_ov003_02215688: for the actor of this console, what func_020604b0 says of the line picks
 * what follows: 0 func_0200f2a0 (0x7f6) at unk_5D0, 1 state 0x52 (with func_02035624(0x12)), 2
 * state 0x53. Another player's actor always runs func_0200f2a0. */
void FieldActor_EndState50(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        FieldActor_PlaySoundAt(actor, 0x7f6, &actor->unk_5D0);
        return;
    }
    switch (FishingFloat_FishBite(held_line(actor))) {
        case 0:
            FieldActor_PlaySoundAt(actor, 0x7f6, &actor->unk_5D0);
            break;
        case 1:
            FieldActor_RequestState52(actor, 6, -1);
            Music_DropPriority(0x12);
            break;
        case 2:
            FieldActor_RequestState53(actor, 6, -1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02215688, FieldActor_EndState50)

/* func_ov003_0221570c: state 0x50's message handler: the state is asked for again. */
void FieldActor_State50Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState50(actor, 6, arg);
}
CLEAN_AS(func_ov003_0221570c, FieldActor_State50Message)

/* func_ov003_02215718: entering state 0x50: animation 0x55 with pose 0x18 in hand; the actor of
 * this console runs func_02035684(0x12, 0, 0). */
void FieldActor_EnterState50(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0x55, 3, 0);
    HeldItem_Act(actor->held, 0x18, 3, 0);
    if (is_local_player(actor)) {
        Music_AddValue(0x12, 0, 0);
    }
}
CLEAN_AS(func_ov003_02215718, FieldActor_EnterState50)

/* func_ov003_02215760: asks for state 0x50; whether it was queued. */
void *FieldActor_RequestState50(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x50, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02215760, FieldActor_RequestState50)

/* ---- State 0x4f: animation 0x54, the line out at unk_5D0 */

/* func_ov003_02215798: state 0x4f's update. The actor turns towards unk_5D0; the actor of this
 * console runs FieldActor_RunState4F, another player's notes the state after this one. */
void FieldActor_UpdateState4F(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_SyncState4FPoint(actor);
    FieldActor_FollowReported(actor);
    FieldActor_FaceState4FPoint(actor);
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState4F(actor);
    } else {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
}
CLEAN_AS(func_ov003_02215798, FieldActor_UpdateState4F)

/* func_ov003_022157f4: the actor of this console, once the held item's animation is over: with
 * flag 0xb set, func_ov003_0222ad2c on what hangs from the line (func_ov003_02228400 at unk_5D0
 * when nothing does) and state 0x51 (byte 0). Otherwise, when unk_140 is set or
 * func_020b758c(func_020b6590(), 0) answers, state 0x50 if func_020604c8 says so of the line,
 * else state 0x51 (byte 0). */
void FieldActor_RunState4F(FieldActor *actor)
{
    FieldActor_CheckState4FLine(actor);
    if (!HeldItem_LineState4Or5((HeldItemObject *) actor->held)) {
        return;
    }
    if (FieldActor_TestFlag(actor, 0xb)) {
        HookedFish *fish = (HookedFish *) FishingFloat_Fish(held_line(actor));
        if (fish != NULL) {
            FishShadowHook_LetGo((FishShadow *) fish);
        } else {
            FishShadow_ScareNear(&actor->unk_5D0, 0x1000);
        }
        FieldActor_RequestState51(actor, 0, 6, -1);
        return;
    }
    if (actor->unk_140 == 0 && TouchPick_GetGround((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), NULL) == 0) {
        return;
    }
    if (FishingFloat_FishPull(held_line(actor))) {
        FieldActor_RequestState50(actor, 6, -1);
    } else {
        FieldActor_RequestState51(actor, 0, 6, -1);
    }
}
CLEAN_AS(func_ov003_022157f4, FieldActor_RunState4F)

/* func_ov003_02215894: once the held item's animation is over and unk_600 is set: sound 0x84b,
 * unk_5D0 kept at unk_8C4, and for the actor of this console func_02036460 on the object at
 * 0x1c4 of data_021c526c. */
void FieldActor_CheckState4FLine(FieldActor *actor)
{
    if (!HeldItem_LineState4Or5((HeldItemObject *) actor->held)) {
        return;
    }
    if (actor->unk_600 == 0) {
        return;
    }
    FieldActor_PlaySound(actor, 0x84b);
    copy_point(&actor->unk_8C4, &actor->unk_5D0);
    if (!is_local_player(actor)) {
        return;
    }
    MusicVolume_BeginSlot3((MusicVolume *) (data_021c526c + 0x1c4));
}
CLEAN_AS(func_ov003_02215894, FieldActor_CheckState4FLine)

/* func_ov003_02215918: the body turns a step towards unk_5D0. */
void FieldActor_FaceState4FPoint(FieldActor *actor)
{
    int target = Math_Atan2(sub32(actor->unk_5D0.x, actor->position.x), sub32(actor->unk_5D0.z, actor->position.z));
    s16 yaw = actor->yaw;
    FieldActor_TurnAngleStep(&yaw, target);
    FieldActor_SetYaw(actor, &yaw);
}
CLEAN_AS(func_ov003_02215918, FieldActor_FaceState4FPoint)

/* func_ov003_02215958: the actor of this console saves unk_5D0 and the line's mode (packed).
 * Another player's actor follows the saved copy: in line mode 4, a saved point 0x800 (2.0) or
 * more away (in x and z) moves the line there, and a saved mode of 5 sets mode 5 with sound
 * 0x84f and keeps the point at unk_8C4; in mode 3 nothing; in any other mode a saved mode of 4
 * sets mode 4 and moves the line to the point, else from mode 6 up mode 0 is set. */
void FieldActor_SyncState4FPoint(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_SetPackedPointMode(actor->saved.packed, &actor->unk_5D0, (u8) actor->line_mode);
        return;
    }

    Vec3 point;
    u8 saved_mode;
    FieldActor_GetPackedPointMode(actor->saved.packed, &point, &saved_mode);
    int mode = actor->line_mode;
    if (mode == 4) {
        int dx = sub32(actor->unk_5D0.x, point.x);
        int dz = sub32(actor->unk_5D0.z, point.z);
        if (add32(mul32(dx, dx), mul32(dz, dz)) >= 0x400000) {
            Vec3 copy = point;
            FishingFloat_SetPosition(held_line(actor), &copy);
        }
        if (saved_mode == 5) {
            FishingFloat_SetState(held_line(actor), 5);
            FieldActor_PlaySound(actor, 0x84f);
            actor->unk_8C4 = point;
        }
    } else if (mode != 3) {
        if (saved_mode == 4) {
            FishingFloat_SetState(held_line(actor), 4);
            Vec3 copy = point;
            FishingFloat_SetPosition(held_line(actor), &copy);
        } else if (mode >= 6) {
            FishingFloat_SetState(held_line(actor), 0);
        }
    }
}
CLEAN_AS(func_ov003_02215958, FieldActor_SyncState4FPoint)

/* func_ov003_02215a70: leaving state 0x4f: the actor of this console runs func_02036458 on the
 * object at 0x1c4 of data_021c526c; another player's actor sets line mode 1 unless the next
 * state is 0x50 or 0x51. */
void FieldActor_ExitState4F(FieldActor *actor, int next)
{
    if (is_local_player(actor)) {
        MusicVolume_EndSlot3((MusicVolume *) (data_021c526c + 0x1c4));
        return;
    }
    if (next == 0x50 || next == 0x51) {
        return;
    }
    FishingFloat_SetState(held_line(actor), 1);
}
CLEAN_AS(func_ov003_02215a70, FieldActor_ExitState4F)

/* func_ov003_02215ac4: state 0x4f's message handler: nothing in state 0x4d; in state 0x4f the
 * argument is kept at unk_C84; otherwise state 0x4f is asked for. */
void FieldActor_State4FMessage(FieldActor *actor, u16 arg)
{
    int state = actor->state;
    if (state == 0x4d) {
        return;
    }
    if (state == 0x4f) {
        actor->unk_C84 = (s16) arg;
    } else {
        FieldActor_RequestState4F(actor, 6, arg);
    }
}
CLEAN_AS(func_ov003_02215ac4, FieldActor_State4FMessage)

/* func_ov003_02215af0: entering state 0x4f: animation 0x54 with pose 0x17 in hand. Another
 * player's actor moves the line to the saved point when the saved mode is 3; the actor of this
 * console saves unk_5D0 and the line's mode. */
void FieldActor_EnterState4F(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0x54, 3, 0);

    void *session = data_020ccf94;
    if (!Session_IsLocalPlayer(session, actor->player)) {
        Vec3 point;
        u8 mode;
        FieldActor_GetPackedPointMode(actor->saved.packed, &point, &mode);
        if (mode == 3) {
            Vec3 copy = point;
            FishingFloat_SetPosition(held_line(actor), &copy);
        }
    }
    HeldItem_Act(actor->held, 0x17, 3, 0);
    if (Session_IsLocalPlayer(session, actor->player)) {
        FieldActor_SetPackedPointMode(actor->saved.packed, &actor->unk_5D0, (u8) actor->line_mode);
    }
}
CLEAN_AS(func_ov003_02215af0, FieldActor_EnterState4F)

/* func_ov003_02215b90: unpacks a point and a mode (func_02077928). */
void FieldActor_GetPackedPointMode(const u8 *packed, Vec3 *point, u8 *mode)
{
    PackedBytes_UnpackPointAndValue(packed, (u32 *) &point->x, &point->y, (u32 *) &point->z, mode);
}
CLEAN_AS(func_ov003_02215b90, FieldActor_GetPackedPointMode)

/* func_ov003_02215ba8: packs a point and a mode (func_02077950). */
void FieldActor_SetPackedPointMode(u8 *packed, const Vec3 *point, int mode)
{
    PackedBytes_PackPointAndValue(packed, point->x, point->y, point->z, (u8) mode);
}
CLEAN_AS(func_ov003_02215ba8, FieldActor_SetPackedPointMode)

/* func_ov003_02215bc0: asks for state 0x4f; whether it was queued. */
int FieldActor_RequestState4F(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x4f, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02215bc0, FieldActor_RequestState4F)

/* ---- State 0x4e: animation 0x53, a cast with no point ahead */

/* func_ov003_02215bf8: state 0x4e's update. The speed at 0x98 slows by 0x171 a frame towards
 * 0. */
void FieldActor_UpdateState4E(FieldActor *actor)
{
    FieldActor_RunState4E(actor);
    if (FieldActor_FollowReported(actor)) {
        FieldActor_MoveWithCollision(actor);
    }
    FieldActor_EnterContact(actor);
    int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState4E(actor);
}
CLEAN_AS(func_ov003_02215bf8, FieldActor_UpdateState4E)

/* func_ov003_02215c44: at the animation's end the actor moves on. */
void FieldActor_EndState4E(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    move_on(actor);
}
CLEAN_AS(func_ov003_02215c44, FieldActor_EndState4E)

/* func_ov003_02215c84: sound 0x84a at frame 0xc. */
void FieldActor_RunState4E(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 0xc)) {
        FieldActor_PlaySound(actor, 0x84a);
    }
}
CLEAN_AS(func_ov003_02215c84, FieldActor_RunState4E)

/* func_ov003_02215cb0: state 0x4e's message handler: the state is asked for again. */
void FieldActor_State4EMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState4E(actor, 6, arg);
}
CLEAN_AS(func_ov003_02215cb0, FieldActor_State4EMessage)

/* func_ov003_02215cbc: entering state 0x4e: animation 0x53 with pose 0x16 in hand. */
void FieldActor_EnterState4E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x53, 3, 0);
    HeldItem_Act(actor->held, 0x16, 3, 0);
}
CLEAN_AS(func_ov003_02215cbc, FieldActor_EnterState4E)

/* func_ov003_02215ce4: asks for state 0x4e; whether it was queued. */
int FieldActor_RequestState4E(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x4e, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02215ce4, FieldActor_RequestState4E)

/* ---- State 0x4d: animation 0x52, a cast towards a point */

/* func_ov003_02215d1c: state 0x4d's update. The actor of this console turns to the point's yaw
 * and always runs func_0201100c; the speed at 0x98 slows by 0x171 a frame towards 0. */
void FieldActor_UpdateState4D(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_TurnState4D(actor);
        FieldActor_RunState4D(actor);
        FieldActor_MoveWithCollision(actor);
    } else {
        FieldActor_RunState4D(actor);
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
    }
    FieldActor_EnterContact(actor);
    int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState4D(actor);
}
CLEAN_AS(func_ov003_02215d1c, FieldActor_UpdateState4D)

/* func_ov003_02215db8: at the animation's end state 0x4f is asked for; the actor of this console
 * also runs func_0203ae84. */
void FieldActor_EndState4D(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    FieldActor_RequestState4F(actor, 6, -1);
    if (is_local_player(actor)) {
        CameraControl_SetMode5();
    }
}
CLEAN_AS(func_ov003_02215db8, FieldActor_EndState4D)

/* func_ov003_02215dfc */
void FieldActor_TurnState4D(FieldActor *actor)
{
    FieldActor_TurnTowards(actor, actor->work.s4d_yaw);
}
CLEAN_AS(func_ov003_02215dfc, FieldActor_TurnState4D)

/* func_ov003_02215e0c: sound 0x849 at frame 0x11. */
void FieldActor_RunState4D(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 0x11)) {
        FieldActor_PlaySound(actor, 0x849);
    }
}
CLEAN_AS(func_ov003_02215e0c, FieldActor_RunState4D)

/* func_ov003_02215e38: state 0x4d's message handler: the state is asked for again at the saved
 * x and z, at the actor's height. */
void FieldActor_State4DMessage(FieldActor *actor, int arg)
{
    fx32 x;
    fx32 z;
    FieldActor_GetState4DSaved(actor->saved.packed, &x, &z);
    Vec3 point = {x, actor->position.y, z};
    FieldActor_RequestState4D(actor, &point, 6, arg);
}
CLEAN_AS(func_ov003_02215e38, FieldActor_State4DMessage)

/* func_ov003_02215e78: entering state 0x4d with the request's x and z: animation 0x52 with pose
 * 0x15 in hand, the line aimed at the point (at height 0), the point saved and the yaw towards
 * it kept. */
void FieldActor_EnterState4D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const XZArgs *args = (const XZArgs *) (const void *) request->payload;

    FieldActor_PlayAnimationOnce(actor, 0x52, 3, 0);
    HeldItem_Act(actor->held, 0x15, 3, 0);
    fx32 x = args->x;
    fx32 z = args->z;
    Vec3 point = {x, 0, z};
    FishingFloat_SetTarget(held_line(actor), &point);
    FieldActor_SetState4DSaved(actor->saved.packed, x, z);
    actor->work.s4d_yaw = Math_Atan2(sub32(x, actor->position.x), sub32(z, actor->position.z));
}
CLEAN_AS(func_ov003_02215e78, FieldActor_EnterState4D)

/* func_ov003_02215ef0: unpacks x and z (func_02077978). */
void FieldActor_GetState4DSaved(const u8 *packed, fx32 *x, fx32 *z)
{
    PackedBytes_UnpackPoint(packed, (u32 *) x, (u32 *) z);
}
CLEAN_AS(func_ov003_02215ef0, FieldActor_GetState4DSaved)

/* func_ov003_02215ef8: packs x and z (func_020779b8). */
void FieldActor_SetState4DSaved(u8 *packed, fx32 x, fx32 z)
{
    PackedBytes_PackPoint(packed, x, z);
}
CLEAN_AS(func_ov003_02215ef8, FieldActor_SetState4DSaved)

/* func_ov003_02215f00: asks for state 0x4d towards a point (its x and z); whether it was
 * queued. */
int FieldActor_RequestState4D(FieldActor *actor, const Vec3 *point, int priority, int arg)
{
    StateRequest request;
    XZArgs args;

    open_request(&request, 0x4d, priority, arg);
    Vec3 copy = *point;
    FieldActor_SetState4DArgs(&args, &copy);
    memcpy(request.payload, &args, 2 * sizeof(fx32));
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02215f00, FieldActor_RequestState4D)

/* func_ov003_02215f4c: x and z of a point (the rest of `args` is left as it is). */
void FieldActor_SetState4DArgs(XZArgs *args, const Vec3 *point)
{
    args->x = point->x;
    args->z = point->z;
}
CLEAN_AS(func_ov003_02215f4c, FieldActor_SetState4DArgs)

/* ---- State 0x4c: animation 0x48, the receiver "obj_etc_player" */

/* func_ov003_02215f58: state 0x4c's update. The actor of this console runs
 * FieldActor_RunState4C; another player's notes the state after this one. */
void FieldActor_UpdateState4C(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState4C(actor);
    } else {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
}
CLEAN_AS(func_ov003_02215f58, FieldActor_UpdateState4C)

/* func_ov003_02215fa4: leaving state 0x4c, another player's actor: func_02095694(0) and flag 0
 * set. */
void FieldActor_ExitState4C(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        PlayerActorOps_SetHeldModel(0, actor->player);
        FieldActor_SetFlag(actor, 0);
    }
}
CLEAN_AS(func_ov003_02215fa4, FieldActor_ExitState4C)

/* func_ov003_02215fd8: step 0 waits for what the receiver opened to be up (0x81c = 0xc then);
 * step 1 waits for it to close, then releases the receiver, clears flag 0x11, runs
 * func_0203e19c, func_02095694(0), sets flag 0, moves on and runs func_0203b144. */
void FieldActor_RunState4C(FieldActor *actor)
{
    switch (actor->work.step) {
        case 0:
            if (actor->link != NULL && actor->link->open != 0) {
                actor->work.step = 1;
                actor->unk_81C = 0xc;
            }
            break;
        case 1:
            if (actor->link != NULL && actor->link->open == 0) {
                SceneObjectBase_ReleaseReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
                FieldActor_ClearFlag(actor, 0x11);
                EventQueue_FinishKind9();
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                PlayerActorOps_SetHeldModel(0, actor->player);
                FieldActor_SetFlag(actor, 0);
                FieldActor_RequestState2(actor, 3, 1, -1);
                CameraControl_ResetMode();
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02215fd8, FieldActor_RunState4C)

/* func_ov003_02216080: state 0x4c's message handler: the state is asked for again. */
void FieldActor_State4CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState4C(actor, 6, arg);
}
CLEAN_AS(func_ov003_02216080, FieldActor_State4CMessage)

/* func_ov003_0221608c (Obj_020d82b4::func_ov003_0221608c): entering state 0x4c: animation 0x48,
 * step 0. The actor of this console registers its receiver as "obj_etc_player" (byte 0x1e = 0xa)
 * and asks for it to open, then runs func_0203ae98, func_02035624(0x12), func_02035684(0xc, 0, 1)
 * and func_020356c4(0xd, 0x42, 0x7f, 1). */
void FieldActor_EnterState4C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0x48, 3, 0);
    FieldActor_ResetState4CStep(&actor->work.step);
    if (is_local_player(actor)) {
        SceneObjectBase_TakeReceiver((SceneObjectBase *) actor, (TalkReceiver *) actor->receiver);
        MessageReceiver_SetName((MessageReceiver *) actor->receiver, data_ov003_02238134);
        actor->receiver_unk_1E = 0xa;
        actor->link->requested = 1;
        CameraControl_SetMode4();
        Music_DropPriority(0x12);
        Music_AddValue(0xc, 0, 1);
        Music_Add(0xd, 0x42, 0x7f, 1);
    }
}
CLEAN_AS(_ZN12Obj_020d82b419func_ov003_0221608cEP12Msg_02007364i, FieldActor_EnterState4C)

/* func_ov003_0221611c */
void FieldActor_ResetState4CStep(u8 *step)
{
    *step = 0;
}
CLEAN_AS(func_ov003_0221611c, FieldActor_ResetState4CStep)

/* func_ov003_02216124: asks for state 0x4c; whether it was queued. */
int FieldActor_RequestState4C(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x4c, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02216124, FieldActor_RequestState4C)

/* ---- State 0x4b: animation 0x47, two effects at frame 8 */

/* func_ov003_0221615c: state 0x4b's update. */
void FieldActor_UpdateState4B(FieldActor *actor)
{
    FieldActor_RunState4B(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState4B(actor);
}
CLEAN_AS(func_ov003_0221615c, FieldActor_UpdateState4B)

/* func_ov003_0221617c: once the yaw is 0 and the animation is over, state 0x4c is asked for; the
 * actor of this console waits for func_0203e1c4 too. */
void FieldActor_EndState4B(FieldActor *actor)
{
    if (actor->yaw != 0) {
        return;
    }
    if (!anim_done(actor)) {
        return;
    }
    if (is_local_player(actor) && EventQueue_RequestKind9() == 0) {
        return;
    }
    FieldActor_RequestState4C(actor, 6, -1);
}
CLEAN_AS(func_ov003_0221617c, FieldActor_EndState4B)

/* func_ov003_022161cc: nothing before frame 8. At frame 8: the work's tile goes to
 * func_02045f08 (clearing flag 0x12) when its flag is set, then sound 0x840, flag 0 cleared,
 * flag 9 set, effect 0x8c at unk_668's translation and effect 0x8b at 0xab8 (0.67) along
 * unk_668's z axis from it (each point passed through func_0203f7d0 first). From frame 8 on,
 * func_0200faf0(0x200). */
void FieldActor_RunState4B(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_frame(actor) < 8) {
        return;
    }
    if (anim_passed(actor, 8)) {
        State4BWork *work = &actor->work.s4b;
        if (work->flag) {
            int tile[2] = {work->x, work->z};
            TileChanges_FinishAtTile((const TileChangesTile *) tile, 0);
            FieldActor_ClearFlag(actor, 0x12);
            work->flag = 0;
        }
        FieldActor_PlaySound(actor, 0x840);
        FieldActor_ClearFlag(actor, 0);
        FieldActor_SetFlag(actor, 9);

        Mtx43 mtx = actor->unk_668;
        const Vec3 origin = {mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]};
        Vec3 at = origin;
        Globe_Unbend(&at, &at);
        EffectSystem_StartOneShotSetNumberCopy(0x8c, &at, 0, 0);

        at = origin;
        mtx.m[3][0] = 0;
        mtx.m[3][1] = 0;
        mtx.m[3][2] = 0;
        const Vec3 ahead = {0, 0, 0xab8};
        Vec3 turned;
        MTX_MultVec43(&ahead, &mtx, &turned);
        at.x = add32(at.x, turned.x);
        at.y = add32(at.y, turned.y);
        at.z = add32(at.z, turned.z);
        Globe_Unbend(&at, &at);
        EffectSystem_StartOneShotSetNumberCopy(0x8b, &at, 0, 0);
    }
    FieldActor_TurnToZero(actor, 0x200);
}
CLEAN_AS(func_ov003_022161cc, FieldActor_RunState4B)

/* func_ov003_022162ec: leaving state 0x4b: the actor of this console runs func_0200f1a4 (3) with
 * the item of its player's record, if any; another player's actor sends the work's tile to
 * func_02045f08 (and clears flag 0x12) if its flag is still set. */
void FieldActor_ExitState4B(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = PlayerRecord_HeldItem(PlayerRecords_OfPlayer(actor->player));
        if (item != NULL) {
            FieldActor_SendItem(actor, 3, *item);
        }
        return;
    }
    State4BWork *work = &actor->work.s4b;
    if (work->flag != 0) {
        int tile[2] = {work->x, work->z};
        TileChanges_FinishAtTile((const TileChangesTile *) tile, 0);
        FieldActor_ClearFlag(actor, 0x12);
    }
}
CLEAN_AS(func_ov003_022162ec, FieldActor_ExitState4B)

/* func_ov003_02216358: state 0x4b's message handler: when the saved flag is 0, the state is asked
 * for again with flag 0 and tile (0, 0).
 * QUIRK: the tile is not kept, and with the flag set nothing is asked for. */
void FieldActor_State4BMessage(FieldActor *actor, int arg)
{
    u8 flag;
    FieldActor_GetState4BSaved(&actor->saved.flag4b, &flag);
    if (flag == 0) {
        int tile[2] = {0, 0};
        FieldActor_RequestState4B(actor, 0, tile, 6, (s16) arg);
    }
}
CLEAN_AS(func_ov003_02216358, FieldActor_State4BMessage)

/* func_ov003_02216390: entering state 0x4b with the request's tile and flag (the flag saved
 * too): animation 0x47; the actor of this console runs func_02035684(0x12, 0xf, 0). */
void FieldActor_EnterState4B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 flag = request->payload[2];
    const u32 tile[2] = {request->payload[0], request->payload[1]};

    FieldActor_SetState4BWork(&actor->work.s4b, flag, tile);
    FieldActor_SetState4BSaved(&actor->saved.flag4b, flag);
    FieldActor_PlayAnimationOnce(actor, 0x47, 3, 0);
    if (is_local_player(actor)) {
        Music_AddValue(0x12, 0xf, 0);
    }
}
CLEAN_AS(func_ov003_02216390, FieldActor_EnterState4B)

/* func_ov003_022163f8 */
void FieldActor_GetState4BSaved(const u8 *saved, u8 *flag)
{
    *flag = *saved;
}
CLEAN_AS(func_ov003_022163f8, FieldActor_GetState4BSaved)

/* func_ov003_02216400 */
void FieldActor_SetState4BSaved(u8 *saved, int flag)
{
    *saved = (u8) flag;
}
CLEAN_AS(func_ov003_02216400, FieldActor_SetState4BSaved)

/* func_ov003_02216404 */
void FieldActor_SetState4BWork(State4BWork *work, u8 flag, const u32 *tile)
{
    work->flag = flag;
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02216404, FieldActor_SetState4BWork)

/* func_ov003_02216410: asks for state 0x4b with a flag and a tile; whether it was queued. */
int FieldActor_RequestState4B(FieldActor *actor, int flag, const int *tile, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x4b, priority, arg);
    const u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetState4BArgs(request.payload, (u8) flag, copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02216410, FieldActor_RequestState4B)

/* func_ov003_02216460: the request's bytes: x, z and the flag. */
void FieldActor_SetState4BArgs(u8 *args, u8 flag, const u32 *tile)
{
    args[2] = flag;
    args[0] = (u8) tile[0];
    args[1] = (u8) tile[1];
}
CLEAN_AS(func_ov003_02216460, FieldActor_SetState4BArgs)

/* ---- State 0x4a: acting on a tile at frame 8 */

/* func_ov003_0221646c: state 0x4a's update. */
void FieldActor_UpdateState4A(FieldActor *actor)
{
    FieldActor_RunState4A(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActor_EndState4A(actor);
}
CLEAN_AS(func_ov003_0221646c, FieldActor_UpdateState4A)

/* func_ov003_0221648c: at the animation's end the state after this one is noted and the actor
 * moves on: to state 0x77 facing its yaw (func_02008dc0) when the work's byte 3 is set, else
 * through func_0200d4e8. Without that byte, the actor of this console also resumes moving
 * (FieldActor_ResumeMoving) after frame 8. */
void FieldActor_EndState4A(FieldActor *actor)
{
    u8 face = actor->work.s4b.unk_03;
    if (anim_done(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        if (face != 0) {
            FieldActor_RequestState77(actor, (u16) actor->yaw, 6, -1);
        } else {
            FieldActor_RequestState2(actor, 3, 1, -1);
        }
    }
    if (face != 0) {
        return;
    }
    if (!is_local_player(actor)) {
        return;
    }
    if (anim_frame(actor) > 8) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0221648c, FieldActor_EndState4A)

/* func_ov003_02216520: the act on the work's tile: a count from func_0200fc90 (one more with the
 * work's flag, which also plays sound 0x83e at 7 and 0x83f at 9) goes to func_02095694; flag 9
 * set, sound 0x83b, effect 2 at the tile turned by the yaw plus 0x2000, func_ov003_02224234 on
 * the tile with 5 when the tile's x is at or past the actor's (else 4), and flag 0x1c
 * cleared. */
void FieldActor_ActState4A(FieldActor *actor)
{
    const State4BWork *work = &actor->work.s4b;
    int count = FieldActor_HeldToolNumber(actor);

    if (work->flag != 0) {
        count++;
        if (count == 7) {
            FieldActor_PlaySound(actor, 0x83e);
        } else if (count == 9) {
            FieldActor_PlaySound(actor, 0x83f);
        }
    }
    PlayerActorOps_SetHeldModel(count, actor->player);
    FieldActor_SetFlag(actor, 9);
    FieldActor_PlaySound(actor, 0x83b);

    u8 x = work->x;
    u8 z = work->z;
    Vec3 point;
    AcreTile_TileCentre(&point, x, z);
    s16 angle = (s16) (actor->yaw + 0x2000);
    EffectSystem_StartKind(2, &point, &angle, 0);

    int tile[2] = {x, z};
    GrowthModel_RequestChop(actor->player, (const TileChangesTile *) tile, point.x >= actor->position.x ? 5 : 4);
    FieldActor_ClearFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02216520, FieldActor_ActState4A)

/* func_ov003_022165e4: the act at frame 8. */
void FieldActor_RunState4A(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 8)) {
        FieldActor_ActState4A(actor);
    }
}
CLEAN_AS(func_ov003_022165e4, FieldActor_RunState4A)

/* func_ov003_0221660c: leaving state 0x4a, another player's actor acts if flag 0x1c is still set
 * (the act clears it). */
void FieldActor_ExitState4A(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    FieldActor_ActState4A(actor);
}
CLEAN_AS(func_ov003_0221660c, FieldActor_ExitState4A)

/* func_ov003_02216640: state 0x4a's message handler does nothing. */
void FieldActor_State4AMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02216640, FieldActor_State4AMessage)

/* func_ov003_02216644: entering state 0x4a with the request's tile and flags: animation 0x44,
 * flag 0x1c set (the act clears it). */
void FieldActor_EnterState4A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const u8 *args = request->payload;
    const u32 tile[2] = {args[0], args[1]};

    FieldActor_SetState4AWork(&actor->work.s4b, args[2], args[3], tile);
    FieldActor_PlayAnimationOnce(actor, 0x44, 3, 0);
    FieldActor_SetFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_02216644, FieldActor_EnterState4A)

/* func_ov003_02216688: the flags first, then the tile (read after them). */
void FieldActor_SetState4AWork(State4BWork *work, u8 flag, u8 face, const u32 *tile)
{
    work->flag = flag;
    work->unk_03 = face;
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02216688, FieldActor_SetState4AWork)

/* func_ov003_02216698: asks for state 0x4a on a tile, with the count's flag and whether to end
 * in state 0x77; whether it was queued. */
int FieldActor_RequestState4A(FieldActor *actor, int flag, int face, const int *tile, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x4a, priority, arg);
    const u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetState4AArgs(request.payload, (u8) flag, (u8) face, copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02216698, FieldActor_RequestState4A)

/* func_ov003_022166e8: the request's bytes: x, z, the flag and whether to end in state 0x77. */
void FieldActor_SetState4AArgs(u8 *args, u8 flag, u8 face, const u32 *tile)
{
    args[2] = flag;
    args[3] = face;
    args[0] = (u8) tile[0];
    args[1] = (u8) tile[1];
}
CLEAN_AS(func_ov003_022166e8, FieldActor_SetState4AArgs)

/* ---- State 0x49: dealing with what was met, at frame 8 */

static_assert(offsetof(FieldActor, work.s49.on_tile) == 0x7d7, "state 0x49 work");
static_assert(sizeof(State49Saved) == 5, "state 0x49 saved");
static_assert(sizeof(State49Work) <= sizeof(((StateRequest *) 0)->payload), "state 0x49 payload");

/* func_ov003_022166f8: state 0x49's update. The speed at 0x98 slows by 0x9c a frame, towards 0,
 * and is stored negated. */
void FieldActor_UpdateState49(FieldActor *actor)
{
    FieldActor_RunState49(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    int speed = sub32(0, FieldActor_Slow(abs32(actor->unk_098), 0));
    FieldActor_SetSpeed(actor, &speed);
    FieldActor_EndState49(actor);
}
CLEAN_AS(func_ov003_022166f8, FieldActor_UpdateState49)

/* func_ov003_02216740: at the animation's end the actor moves on. */
void FieldActor_EndState49(FieldActor *actor)
{
    if (anim_done(actor)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02216740, FieldActor_EndState49)

/* func_ov003_02216780: the act: the speed becomes -0x333; a count from func_0200fc90 (one more
 * with the work's flag, which also plays sound 0x83e at 7 and 0x83f at 9) goes to
 * func_02095694; flag 9 is set; with on_tile the tile goes to func_ov003_022241a4 and flags 0x12
 * and 0x1c are cleared. Then by what was met (other_result): nothing (0) gives effect 4 at 0.8
 * ahead, 0.5 to the side and 0.8 above the actor, turned by the yaw plus 0x2000, and sound
 * 0x83c; an object of main's tables (2) is told the held item (its vtable slot 24) after sound
 * 0x7df; an object of overlay 3 (3) gets Snowman_Knock for the actor of this console,
 * sound 0x7df when that fails or for another player's actor; 1 gives sound 0x7df. What was met
 * is forgotten. */
void FieldActor_ActState49(FieldActor *actor)
{
    const State49Work *work = &actor->work.s49;
    int speed = -0x333;
    FieldActor_SetSpeed(actor, &speed);

    int count = FieldActor_HeldToolNumber(actor);
    if (work->flag != 0) {
        count++;
        if (count == 7) {
            FieldActor_PlaySound(actor, 0x83e);
        } else if (count == 9) {
            FieldActor_PlaySound(actor, 0x83f);
        }
    }
    PlayerActorOps_SetHeldModel(count, actor->player);
    FieldActor_SetFlag(actor, 9);
    if (work->on_tile != 0) {
        int tile[2] = {work->x, work->z};
        TileEvent_StartFromChanges((const TileChangesTile *) tile);
        FieldActor_ClearFlag(actor, 0x12);
        FieldActor_ClearFlag(actor, 0x1c);
    }

    switch (actor->other_result) {
        case 0: {
            Vec3 at = actor->position;
            s16 angle = actor->yaw;
            int index = ((u16) angle >> 4) * 2;
            fx32 sine = FX_SinCosTable_[index];
            fx32 cosine = FX_SinCosTable_[index + 1];
            fx32 forward_z = FX_MulFunc(cosine, 0xccd);
            fx32 side_z = FX_MulFunc(sine, -0x800);
            fx32 dz = sub32(forward_z, side_z);
            fx32 forward_x = FX_MulFunc(sine, 0xccd);
            fx32 side_x = FX_MulFunc(cosine, -0x800);
            fx32 dx = add32(forward_x, side_x);
            at.x = add32(at.x, dx);
            at.z = add32(at.z, dz);
            at.y = add32(at.y, 0xccd);
            angle = (s16) (angle + 0x2000);
            EffectSystem_StartKind(4, &at, &angle, 0);
            FieldActor_PlaySound(actor, 0x83c);
            break;
        }
        case 1:
            FieldActor_PlaySound(actor, 0x7df);
            break;
        case 2:
            FieldActor_PlaySound(actor, 0x7df);
            if (actor->other != NULL) {
                u16 item;
                FieldActor_RecordHeldItem(&item, actor);
                GameObject *other = (GameObject *) actor->other;
                ItemQuery query = (ItemQuery) (uintptr_t) other->vtable[24];
                query(other, &item);
            }
            break;
        case 3:
            if (is_local_player(actor) && Snowman_Knock(actor->other, 1)) {
                break;
            }
            FieldActor_PlaySound(actor, 0x7df);
            break;
        default:
            break;
    }
    actor->other = NULL;
    actor->other_result = 0;
}
CLEAN_AS(func_ov003_02216780, FieldActor_ActState49)

/* func_ov003_02216948: the act at frame 8. */
void FieldActor_RunState49(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 8)) {
        FieldActor_ActState49(actor);
    }
}
CLEAN_AS(func_ov003_02216948, FieldActor_RunState49)

/* func_ov003_02216970: leaving state 0x49, another player's actor acts if flag 0x1c is still set
 * (an act with on_tile clears it). */
void FieldActor_ExitState49(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    FieldActor_ActState49(actor);
}
CLEAN_AS(func_ov003_02216970, FieldActor_ExitState49)

/* func_ov003_022169a4: state 0x49's message handler: the saved verdict on what was met comes
 * back, and without on_tile the state is asked for again with the saved flag and tile. */
void FieldActor_State49Message(FieldActor *actor, int arg)
{
    u8 flag;
    u8 on_tile;
    u8 other_result;
    u8 x;
    u8 z;

    FieldActor_GetState49Saved(&actor->saved.s49, &flag, &on_tile, &other_result, &x, &z);
    actor->other_result = other_result;
    if (on_tile == 0) {
        int tile[2] = {x, z};
        FieldActor_RequestState49(actor, flag, 0, tile, 6, (s16) arg);
    }
}
CLEAN_AS(func_ov003_022169a4, FieldActor_State49Message)

/* func_ov003_02216a00: entering state 0x49 with the request's tile and flags (saved with the
 * verdict on what was met): animation 0x45; with on_tile, flag 0x1c is set. */
void FieldActor_EnterState49(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State49Work *args = (const State49Work *) (const void *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    u8 flag = args->flag;
    u8 on_tile = args->on_tile;
    const u32 tile[2] = {x, z};

    FieldActor_SetState49Work(&actor->work.s49, flag, on_tile, tile);
    FieldActor_SetState49Saved(&actor->saved.s49, flag, on_tile, actor->other_result, x, z);
    FieldActor_PlayAnimationOnce(actor, 0x45, 3, 0);
    if (on_tile != 0) {
        FieldActor_SetFlag(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_02216a00, FieldActor_EnterState49)

/* func_ov003_02216a70: each byte is read just before its output is written. */
void FieldActor_GetState49Saved(const State49Saved *saved, u8 *flag, u8 *on_tile, u8 *other_result, u8 *x, u8 *z)
{
    *flag = saved->flag;
    *on_tile = saved->on_tile;
    *other_result = saved->other_result;
    *x = saved->x;
    *z = saved->z;
}
CLEAN_AS(func_ov003_02216a70, FieldActor_GetState49Saved)

/* func_ov003_02216a90 */
void FieldActor_SetState49Saved(State49Saved *saved, u8 flag, u8 on_tile, u8 other_result, u8 x, u8 z)
{
    saved->flag = flag;
    saved->on_tile = on_tile;
    saved->other_result = other_result;
    saved->x = x;
    saved->z = z;
}
CLEAN_AS(func_ov003_02216a90, FieldActor_SetState49Saved)

/* func_ov003_02216aa8: the flags first, then the tile (read after them). */
void FieldActor_SetState49Work(State49Work *work, u8 flag, u8 on_tile, const u32 *tile)
{
    work->flag = flag;
    work->on_tile = on_tile;
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02216aa8, FieldActor_SetState49Work)

/* func_ov003_02216ab8: asks for state 0x49 on a tile with the count's flag and on_tile; whether
 * it was queued. */
int FieldActor_RequestState49(FieldActor *actor, int flag, int on_tile, const int *tile, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x49, priority, arg);
    const u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActor_SetState49Args((State49Work *) (void *) request.payload, (u8) flag, (u8) on_tile, copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02216ab8, FieldActor_RequestState49)

/* func_ov003_02216b08: the request's bytes, as FieldActor_SetState49Work writes them. */
void FieldActor_SetState49Args(State49Work *args, u8 flag, u8 on_tile, const u32 *tile)
{
    args->flag = flag;
    args->on_tile = on_tile;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02216b08, FieldActor_SetState49Args)

/* ---- State 0x48: animation 0x46, sound 0x83d at frame 6 */

/* func_ov003_02216b18: state 0x48's update. */
void FieldActor_UpdateState48(FieldActor *actor)
{
    FieldActor_RunState48(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState48(actor);
}
CLEAN_AS(func_ov003_02216b18, FieldActor_UpdateState48)

/* func_ov003_02216b34: at the animation's end the actor moves on. */
void FieldActor_EndState48(FieldActor *actor)
{
    if (anim_done(actor)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02216b34, FieldActor_EndState48)

/* func_ov003_02216b74: sound 0x83d on passing frame 6 (tested before the animation steps). */
void FieldActor_RunState48(FieldActor *actor)
{
    if (anim_passed(actor, 6)) {
        FieldActor_PlaySound(actor, 0x83d);
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov003_02216b74, FieldActor_RunState48)

/* func_ov003_02216ba4: state 0x48's message handler asks for the state again. */
void FieldActor_State48Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState48(actor, 6, arg);
}
CLEAN_AS(func_ov003_02216ba4, FieldActor_State48Message)

/* func_ov003_02216bb0: entering state 0x48: animation 0x46. */
void FieldActor_EnterState48(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x46, 3, 0);
}
CLEAN_AS(func_ov003_02216bb0, FieldActor_EnterState48)

/* func_ov003_02216bc4: asks for state 0x48; whether it was queued. */
int FieldActor_RequestState48(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x48, priority, arg);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02216bc4, FieldActor_RequestState48)

/* ---- State 0x47: waiting for something to act on ahead */

/* func_ov003_02216bfc: state 0x47's update. The speed at 0x98 slows by 0x9c a frame, towards 0.
 * The actor of this console then tries to act ahead (FieldActor_ActAhead, without checking for
 * objects); another player's actor notes the state after this one. Both turn towards the point
 * ahead. */
void FieldActor_UpdateState47(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        int speed = FieldActor_Slow(actor->unk_098, 0);
        FieldActor_SetSpeed(actor, &speed);
        FieldActor_ActAhead(actor, 0);
    } else {
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
        FieldActor_EnterContact(actor);
        int speed = FieldActor_Slow(actor->unk_098, 0);
        FieldActor_SetSpeed(actor, &speed);
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
    FieldActor_TurnState47(actor);
}
CLEAN_AS(func_ov003_02216bfc, FieldActor_UpdateState47)

/* func_ov003_02216c9c: once the actor has stopped (else -1), acts by the verdict of
 * FieldActor_ClassifyAhead on the ground ahead (with objects when `check_other`), which it
 * returns. The mode it is given: 0, or with flag 0x14 set and a count (func_0200fc90) other than
 * 0xb, 1 below 0xa and 2 at 0xa; another player's actor acts with mode 0 whatever the verdict
 * saw. By verdict: 1 asks for state 0x48; 2 and 3 for state 0x4a (ending in state 0x77 for 3);
 * 4 and 6 for state 0x49 (on the tile for 6); in mode 2 those are state 0x4b (flag 0 for 4, else
 * 1) instead; 5 moves on; 0 does nothing. The requests carry the tile ahead and, as their flag,
 * whether the mode is not 0.
 * QUIRK: ClassifyAhead reads its first flag as a byte, so only the low byte of `check_other`
 * counts. */
int FieldActor_ActAhead(FieldActor *actor, int check_other)
{
    if (actor->unk_098 != 0) {
        return -1;
    }

    int count = FieldActor_HeldToolNumber(actor);
    u8 mode = 0;
    if (count != 0xb && FieldActor_TestFlag(actor, 0x14)) {
        mode = count != 0xa ? 1 : 2;
    }

    int tile[2] = {0, 0};
    u8 check = (u8) check_other;
    int verdict = FieldActor_ClassifyAhead(actor, &check, &mode, tile);
    if (!is_local_player(actor)) {
        mode = 0;
    }

    switch (verdict) {
        case 1:
            FieldActor_RequestState48(actor, 6, -1);
            break;
        case 2:
        case 3:
            if (mode == 2) {
                FieldActor_RequestState4B(actor, 1, tile, 6, -1);
            } else {
                FieldActor_RequestState4A(actor, mode != 0, verdict == 3, tile, 6, -1);
            }
            break;
        case 4:
            if (mode == 2) {
                FieldActor_RequestState4B(actor, 0, tile, 6, -1);
            } else {
                FieldActor_RequestState49(actor, mode != 0, 0, tile, 6, -1);
            }
            break;
        case 5:
            move_on(actor);
            break;
        case 6:
            if (mode == 2) {
                FieldActor_RequestState4B(actor, 1, tile, 6, -1);
            } else {
                FieldActor_RequestState49(actor, mode != 0, 1, tile, 6, -1);
            }
            break;
        default:
            break;
    }
    return verdict;
}
CLEAN_AS(func_ov003_02216c9c, FieldActor_ActAhead)

/* func_ov003_02216e5c: turns the actor towards the point ahead of it (func_02010d88). */
void FieldActor_TurnState47(FieldActor *actor)
{
    Vec3 ahead;
    FieldActor_PointAheadOfSelf(&ahead, actor);
    FieldActor_SetContactBSized(actor, &ahead, 0xf33, 0x1000);
    FieldBody_Enter((FieldBody *) actor->unk_1C4);
}
CLEAN_AS(func_ov003_02216e5c, FieldActor_TurnState47)

/* func_ov003_02216e94: state 0x47's message handler asks for the state again. */
void FieldActor_State47Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState47(actor, 6, arg);
}
CLEAN_AS(func_ov003_02216e94, FieldActor_State47Message)

/* func_ov003_02216ea0: entering state 0x47: animation 0x43 (func_020109fc). */
void FieldActor_EnterState47(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, 0x43, 3, 0);
}
CLEAN_AS(func_ov003_02216ea0, FieldActor_EnterState47)

/* func_ov003_02216eb4: asks for state 0x47; whether it was queued. */
int FieldActor_RequestState47(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x47, priority, arg);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02216eb4, FieldActor_RequestState47)

/* ---- State 0x46: a slide towards a point */

static_assert(offsetof(FieldActor, work.s46.yaw) == 0x7e0, "state 0x46 yaw");
static_assert(offsetof(FieldActor, start_position.z) == 0x6fc, "start position z");

/* func_ov003_02216eec: state 0x46's update. The speed at 0x98 slows by 0x171 a frame, towards 0
 * (func_020113a4); when it reaches 0 here, effect 0x2c starts at the actor. The actor of this
 * console faces the work's yaw first and turns towards its point last. */
void FieldActor_UpdateState46(FieldActor *actor)
{
    int before = actor->unk_098;

    if (is_local_player(actor)) {
        FieldActor_FaceState46(actor);
        FieldActor_UpdateBody(actor);
        FieldActor_MoveWithCollision(actor);
        FieldActor_EnterContact(actor);
        int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
        FieldActor_SetSpeed(actor, &speed);
        FieldActor_EndState46Local(actor);
        FieldActor_TurnState46(actor);
    } else {
        FieldActor_UpdateBody(actor);
        if (FieldActor_FollowReported(actor)) {
            FieldActor_MoveWithCollision(actor);
        }
        FieldActor_EnterContact(actor);
        int speed = FieldActor_StepDown(actor->unk_098, 0, 0x171);
        FieldActor_SetSpeed(actor, &speed);
        FieldActor_EndState46Remote(actor);
    }

    if (before != 0 && actor->unk_098 == 0) {
        EffectSystem_StartKind(0x2c, &actor->position, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_02216eec, FieldActor_UpdateState46)

/* func_ov003_02216fb0: another player's actor notes the state after this one each frame and asks
 * for state 0x47 at the animation's end. */
void FieldActor_EndState46Remote(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (anim_done(actor)) {
        FieldActor_RequestState47(actor, 6, -1);
    }
}
CLEAN_AS(func_ov003_02216fb0, FieldActor_EndState46Remote)

/* func_ov003_02216fec: at the animation's end the actor of this console acts ahead (objects
 * included), or asks for state 0x47 when there is nothing to act on. */
void FieldActor_EndState46Local(FieldActor *actor)
{
    if (anim_done(actor)) {
        if (FieldActor_ActAhead(actor, 1) == 0) {
            FieldActor_RequestState47(actor, 6, -1);
        }
    }
}
CLEAN_AS(func_ov003_02216fec, FieldActor_EndState46Local)

/* func_ov003_02217020: turns the actor towards the work's point (func_02010d88). */
void FieldActor_TurnState46(FieldActor *actor)
{
    Vec3 point = actor->work.s46.point;
    FieldActor_SetContactBSized(actor, &point, 0xf33, 0x1000);
    FieldBody_Enter((FieldBody *) actor->unk_1C4);
}
CLEAN_AS(func_ov003_02217020, FieldActor_TurnState46)

/* func_ov003_02217060: the actor faces the work's yaw (func_0200fb34). */
void FieldActor_FaceState46(FieldActor *actor)
{
    FieldActor_TurnTowards(actor, actor->work.s46.yaw);
}
CLEAN_AS(func_ov003_02217060, FieldActor_FaceState46)

/* func_ov003_02217070: state 0x46's message handler asks for the state again with the saved
 * point and flag. */
void FieldActor_State46Message(FieldActor *actor, int arg)
{
    fx32 x;
    fx32 z;
    u8 at_point;

    FieldActor_GetState46Saved(actor->saved.packed, &x, &z, &at_point);
    FieldActor_RequestState46Saved(actor, &x, &z, &at_point, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02217070, FieldActor_State46Message)

/* func_ov003_022170a4: entering state 0x46 (the request saved): animation 0x42. The point is the
 * request's with at_point, else the point ahead of the actor, snapped to its tile when the
 * ground there is at 0x1000 or higher (func_020310d0). The work holds the point and the yaw
 * from where the frame's update began towards it. Then the actor of this console clears flag
 * 0x14 and, unless the count (func_0200fc90) is 0xb, sets it again when func_020644cc(8) gives
 * 0.
 * BUG: with at_point the point's y is never set, so the work's y is whatever the stack held. */
void FieldActor_EnterState46(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State46Args *args = (const State46Args *) (const void *) request->payload;
    fx32 x = args->x;
    fx32 z = args->z;
    u8 at_point = args->at_point;
    Vec3 point;

    FieldActor_SetState46Saved(actor->saved.packed, x, z, at_point);
    FieldActor_PlayAnimationOnce(actor, 0x42, 3, 0);

    if (at_point != 0) {
#ifdef BUGFIX
        point.y = 0;
#endif
        point.x = x;
        point.z = z;
    } else {
        Vec3 ahead;
        int surface;
        FieldActor_PointAheadOfSelf(&ahead, actor);
        if (CollisionQuery_GroundY(&ahead, &surface, 0x19) >= 0x1000) {
            FieldActor_TileAhead(&point, actor);
        } else {
            FieldActor_PointAheadOfSelf(&point, actor);
        }
    }

    s16 yaw = Math_Atan2(sub32(point.x, actor->start_position.x), sub32(point.z, actor->start_position.z));
    Vec3 copy = point;
    FieldActor_SetState46Work(&actor->work.s46, &copy, (u16) yaw);

    if (is_local_player(actor)) {
        FieldActor_ClearFlag(actor, 0x14);
        if (FieldActor_HeldToolNumber(actor) != 0xb && MainRandom_Below(8) == 0) {
            FieldActor_SetFlag(actor, 0x14);
        }
    }
}
CLEAN_AS(func_ov003_022170a4, FieldActor_EnterState46)

/* func_ov003_022171ac: the saved point (func_02077978) and the flag in byte 5. */
void FieldActor_GetState46Saved(const u8 *saved, fx32 *x, fx32 *z, u8 *at_point)
{
    PackedBytes_UnpackPoint(saved, (u32 *) x, (u32 *) z);
    *at_point = saved[5];
}
CLEAN_AS(func_ov003_022171ac, FieldActor_GetState46Saved)

/* func_ov003_022171c4: the point packed by func_020779b8 and the flag in byte 5. */
void FieldActor_SetState46Saved(u8 *saved, fx32 x, fx32 z, u8 at_point)
{
    PackedBytes_PackPoint(saved, x, z);
    saved[5] = at_point;
}
CLEAN_AS(func_ov003_022171c4, FieldActor_SetState46Saved)

/* func_ov003_022171dc: the point copied word by word (x, y, z), then the yaw. */
void FieldActor_SetState46Work(State46Work *work, const Vec3 *point, u16 yaw)
{
    copy_point(&work->point, point);
    work->yaw = (s16) yaw;
}
CLEAN_AS(func_ov003_022171dc, FieldActor_SetState46Work)

/* func_ov003_022171ec: asks for state 0x46 with a point and flag read through pointers; whether
 * it was queued. */
int FieldActor_RequestState46Saved(FieldActor *actor, const fx32 *x, const fx32 *z, const u8 *at_point, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x46, priority, arg);
    FieldActor_SetState46Args((State46Args *) (void *) request.payload, *x, *z, *at_point);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022171ec, FieldActor_RequestState46Saved)

/* func_ov003_02217234: asks for state 0x46 (tool 2 of FieldActor_UseTool): towards aim_point
 * when unk_148 is set, else towards unk_14C with at_point when unk_144 is set; whether it was
 * queued. */
int FieldActor_RequestState46(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x46, priority, arg);
    State46Args *args = (State46Args *) (void *) request.payload;
    if (actor->unk_148 != 0) {
        FieldActor_SetState46Args(args, actor->aim_point.x, actor->aim_point.z, 1);
    } else {
        FieldActor_SetState46Args(args, actor->unk_14C.x, actor->unk_14C.z, actor->unk_144 != 0);
    }
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02217234, FieldActor_RequestState46)

/* func_ov003_022172bc */
void FieldActor_SetState46Args(State46Args *args, fx32 x, fx32 z, int at_point)
{
    args->x = x;
    args->z = z;
    args->at_point = (u8) at_point;
}
CLEAN_AS(func_ov003_022172bc, FieldActor_SetState46Args)

/* ---- State 0x45: animation 0x63 with effect 0x33 at the held item's tip */

static_assert(offsetof(FieldActor, work.s45.effect) == 0x7d8, "state 0x45 effect");

/* func_ov003_022172c4: state 0x45's update. */
void FieldActor_UpdateState45(FieldActor *actor)
{
    FieldActor_RunState45(actor);
    if (is_local_player(actor)) {
        FieldActor_MoveWithCollision(actor);
    } else {
        FieldActor_FollowReported(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActor_EndState45(actor);
}
CLEAN_AS(func_ov003_022172c4, FieldActor_UpdateState45)

/* func_ov003_0221730c: at the animation's end the actor moves on; from frame 14 on the actor of
 * this console resumes moving (FieldActor_ResumeMoving). */
void FieldActor_EndState45(FieldActor *actor)
{
    if (anim_done(actor)) {
        move_on(actor);
    }
    if (anim_frame(actor) >= 14 && is_local_player(actor)) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0221730c, FieldActor_EndState45)

/* func_ov003_02217378: effect 0x33 starts at, or follows, the tip of what the actor holds
 * (passed through func_0203f7d0), turned by the yaw. */
void FieldActor_RunState45(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    int *effect = &actor->work.s45.effect;
    Vec3 at = actor->unk_62C;
    Globe_Unbend(&at, &at);
    if (*effect == -1) {
        *effect = EffectSystem_StartKind(0x33, &at, &actor->yaw, 0);
    } else {
        EffectSystem_MoveHandle(*effect, &at, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_02217378, FieldActor_RunState45)

/* func_ov003_022173e0: leaving state 0x45 ends its effect, if any.
 * QUIRK: the handle is not reset to -1. */
void FieldActor_ExitState45(FieldActor *actor)
{
    if (actor->work.s45.effect != -1) {
        EffectSystem_EndHandle(actor->work.s45.effect);
    }
}
CLEAN_AS(func_ov003_022173e0, FieldActor_ExitState45)

/* func_ov003_02217400: state 0x45's message handler asks for the state again. */
void FieldActor_State45Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState45(actor, 6, arg);
}
CLEAN_AS(func_ov003_02217400, FieldActor_State45Message)

/* func_ov003_0221740c: entering state 0x45: animation 0x63, the work reset (no effect), sound
 * 0x856 and flag 9 set. */
void FieldActor_EnterState45(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, 0x63, 3, 0);
    FieldActor_InitState45Work(&actor->work.s45);
    FieldActor_PlaySound(actor, 0x856);
    FieldActor_SetFlag(actor, 9);
}
CLEAN_AS(func_ov003_0221740c, FieldActor_EnterState45)

/* func_ov003_02217440 */
void FieldActor_InitState45Work(State45Work *work)
{
    work->unk_00 = 0;
    work->unk_02 = 0x20;
    work->effect = -1;
}
CLEAN_AS(func_ov003_02217440, FieldActor_InitState45Work)

/* func_ov003_02217450: asks for state 0x45 (tool 10 of FieldActor_UseTool); whether it was
 * queued. */
void *FieldActor_RequestState45(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x45, priority, arg);
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02217450, FieldActor_RequestState45)

/* ---- State 0x3e: animation 0x62, then the state the request names */

static_assert(offsetof(FieldActor, work.s3e.flags) == 0x7e2, "state 0x3e flags");
static_assert(sizeof(State3ESaved) == 8, "state 0x3e saved");

/* func_ov003_02217488: state 0x3e's update. */
void FieldActor_UpdateState3E(FieldActor *actor)
{
    FieldActor_RunState3E(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState3E(actor);
}
CLEAN_AS(func_ov003_02217488, FieldActor_UpdateState3E)

/* func_ov003_022174a4: at the animation's end flag 1 is set and the actor goes to the work's next
 * state with its point and value: 0x38 (FieldActor_RequestState38) and 0x39 (FieldActor_RequestState39,
 * with the kind in bits 2-3 of the flags) clearing flag 0 first; 0x10 clears flag 0 and moves on
 * through func_0200c3b0 (3, 5); 2 runs func_0203e110 and moves on the usual way. */
void FieldActor_EndState3E(FieldActor *actor)
{
    const State3EWork *work = &actor->work.s3e;
    if (!anim_done(actor)) {
        return;
    }
    FieldActor_SetFlag(actor, 1);
    switch (work->next) {
        case 0x38:
            FieldActor_ClearFlag(actor, 0);
            FieldActor_RequestState38(actor, work->x, work->z, work->value, 6, -1);
            break;
        case 0x39:
            FieldActor_ClearFlag(actor, 0);
            FieldActor_RequestState39(actor, (work->flags & 0xc) >> 2, work->x, work->z, work->value, 6, -1);
            break;
        case 0x10:
            FieldActor_ClearFlag(actor, 0);
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestState10(actor, 3, 5, -1);
            break;
        case 2:
            EventQueue_FinishKind4Or12();
            move_on(actor);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022174a4, FieldActor_EndState3E)

/* func_ov003_02217590: played backwards (flags other than 2), flag 0 is cleared on passing frame
 * 5; played forwards (2), flag 0 is set and sound 0x857 plays on passing frame 7. */
void FieldActor_RunState3E(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if ((actor->work.s3e.flags & 3) != 2) {
        if (anim_frame(actor) < 6 && anim_passed(actor, 5)) {
            FieldActor_ClearFlag(actor, 0);
        }
    } else {
        if (anim_frame(actor) < 8 && anim_passed(actor, 7)) {
            FieldActor_SetFlag(actor, 0);
            FieldActor_PlaySound(actor, 0x857);
        }
    }
}
CLEAN_AS(func_ov003_02217590, FieldActor_RunState3E)

/* func_ov003_02217608: state 0x3e's message handler asks for the state again with the saved
 * point, value and flags, the next state decoded from the flags' high nibble (0: 0x38, 1: 0x39,
 * 2: 0x10, others 2). */
void FieldActor_State3EMessage(FieldActor *actor, int arg)
{
    u8 flags;
    fx32 x;
    fx32 z;
    u16 value;
    int next;

    FieldActor_GetState3ESaved(&actor->saved.s3e, &flags, &x, &z, &value);
    switch (flags & 0xf0) {
        case 0x00:
            next = 0x38;
            break;
        case 0x10:
            next = 0x39;
            break;
        case 0x20:
            next = 0x10;
            break;
        default:
            next = 2;
            break;
    }
    FieldActor_RequestState3E(actor, next, flags & 0xf, x, z, (s16) value, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02217608, FieldActor_State3EMessage)

/* func_ov003_02217678: entering state 0x3e: the held item takes pose 0x24 (func_0205eae0).
 * Unless the flags' low bits are 2, animation 0x62 and the held item's own animation run
 * backwards from their last frames, with sound 0x858; with 2, animation 0x62 starts while the
 * player's record holds no item (ITEM_NONE, the item put back after) and flag 0 is cleared. The
 * request becomes the work, and is saved with the next state coded into the flags; sound 0x4f. */
void FieldActor_EnterState3E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State3EWork *args = (const State3EWork *) (const void *) request->payload;
    u8 flags = args->flags;

    HeldItem_Act(actor->held, 0x24, 3, 1);
    if ((flags & 3) != 2) {
        FieldActor_PlayAnimationOnce(actor, 0x62, 3, 0);
        u32 frames = anim_frames(actor);
        FrameCtrl_Init(&actor->anim, frames, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) (frames - 1));

        FrameCtrl *held_anim = (FrameCtrl *) (void *) (HeldItem_Model(actor->held) + 0x9c);
        u32 held_frames = ((u32) held_anim->end >> 12) & 0xffff;
        FrameCtrl_Init(held_anim, held_frames, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) (held_frames - 1));

        FieldActor_PlaySound(actor, 0x858);
    } else {
        u16 items[2];
        FieldActor_RecordHeldItem(&items[0], actor);
        void *record = FieldActor_Record(actor);
        items[1] = ITEM_NONE;
        PlayerRecord_SetHeldItem(record, &items[1]);
        FieldActor_PlayAnimationOnce(actor, 0x62, 3, 0);
        PlayerRecord_SetHeldItem(record, &items[0]);
        FieldActor_ClearFlag(actor, 0);
    }

    int next = args->next;
    fx32 x = args->x;
    fx32 z = args->z;
    s16 value = args->value;
    FieldActor_SetState3EWork(&actor->work.s3e, next, (char) flags, x, z, value);

    switch (next) {
        case 0x39:
            flags |= 0x10;
            break;
        case 0x10:
            flags |= 0x20;
            break;
        case 2:
            flags |= 0x30;
            break;
        default:
            break;
    }
    FieldActor_SetState3ESaved(&actor->saved.s3e, (char) flags, x, z, value);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_02217678, FieldActor_EnterState3E)

/* func_ov003_022177d0: the saved flags (read first), point and value; returns the value. */
u16 FieldActor_GetState3ESaved(const State3ESaved *saved, u8 *flags, fx32 *x, fx32 *z, u16 *value)
{
    *flags = saved->flags;
    PackedBytes_UnpackPoint(saved->xz, (u32 *) x, (u32 *) z);
    u16 v = (u16) PackedBytes_ReadS16(saved->value);
    *value = v;
    return v;
}
CLEAN_AS(func_ov003_022177d0, FieldActor_GetState3ESaved)

/* func_ov003_022177f4: the flags first, then the point and the value packed. */
void FieldActor_SetState3ESaved(State3ESaved *saved, char flags, fx32 x, fx32 z, s16 value)
{
    saved->flags = (u8) flags;
    PackedBytes_PackPoint(saved->xz, x, z);
    PackedBytes_WriteS16(saved->value, value);
}
CLEAN_AS(func_ov003_022177f4, FieldActor_SetState3ESaved)

/* func_ov003_0221781c */
void FieldActor_SetState3EWork(State3EWork *work, int next, char flags, fx32 x, fx32 z, s16 value)
{
    work->next = next;
    work->flags = (u8) flags;
    work->x = x;
    work->z = z;
    work->value = value;
}
CLEAN_AS(func_ov003_0221781c, FieldActor_SetState3EWork)

/* func_ov003_02217838: asks for state 0x3e, flag 1 cleared before the request is queued; whether
 * it was queued. */
int FieldActor_RequestState3E(FieldActor *actor, int next, int flags, fx32 x, fx32 z, s16 value, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x3e, priority, arg);
    FieldActor_SetState3EArgs((State3EWork *) (void *) request.payload, next, (char) flags, x, z, value);
    FieldActor_ClearFlag(actor, 1);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02217838, FieldActor_RequestState3E)

/* func_ov003_02217894: the request's payload, laid out as the work. */
void FieldActor_SetState3EArgs(State3EWork *args, int next, char flags, fx32 x, fx32 z, s16 value)
{
    args->next = next;
    args->flags = (u8) flags;
    args->x = x;
    args->z = z;
    args->value = value;
}
CLEAN_AS(func_ov003_02217894, FieldActor_SetState3EArgs)

/* ---- State 0x3d */

/* func_ov003_022178b0: state 0x3d's update. */
void FieldActor_UpdateState3D(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_StepState3D(actor);
}
CLEAN_AS(func_ov003_022178b0, FieldActor_UpdateState3D)

/* The weight the held item is given (its word at 4) while state 0x3d runs and when it ends. */
static void set_held_weight(FieldActor *actor, fx32 weight)
{
    memcpy(&actor->held[4], &weight, sizeof(weight));
}

/* Whether a held item code is in 0x1380-0x13a7. */
static BOOL is_item_1380(u16 item)
{
    return item >= 0x1380 && item <= 0x13a7;
}

static_assert(offsetof(FieldActor, work.s3d.weight) == 0x7e0, "state 0x3d weight");
static_assert(offsetof(FieldActor, work.s3d.yaw) == 0x7e4, "state 0x3d yaw");
static_assert(offsetof(FieldActor, work.s3d.flags) == 0x7e6, "state 0x3d flags");

/* func_ov003_022178cc: state 0x3d's step. With flags 2 (the animation playing backwards from
 * its end) the weight rises by 0x249 a frame up to 1.0 while the frame is below 8, and frame 7
 * runs func_020108cc (0, 7); otherwise it falls by 0x249 a frame down to 0. The held item takes
 * the weight. Once the animation is over and the weight has arrived, flag 1 is set and the actor
 * goes on to the work's next state, as at the end of state 0x3e. */
void FieldActor_StepState3D(FieldActor *actor)
{
    State3DWork *work = &actor->work.s3d;
    fx32 target;

    if ((work->flags & 3) == 2) {
        target = 0x1000;
        if (anim_frame(actor) < 8) {
            if (anim_passed(actor, 7)) {
                FieldActor_AnimateHeldItem(actor, 0, 7);
            }
            if (work->weight != 0x1000) {
                work->weight = add32(work->weight, 0x249);
                if (work->weight > 0x1000) {
                    work->weight = 0x1000;
                }
            }
        }
    } else {
        target = 0;
        if (work->weight != 0) {
            work->weight = sub32(work->weight, 0x249);
            if (work->weight < 0) {
                work->weight = 0;
            }
        }
    }
    set_held_weight(actor, work->weight);

    if (!anim_done(actor) || work->weight != target) {
        return;
    }
    FieldActor_SetFlag(actor, 1);
    switch (work->next) {
        case 0x38:
            FieldActor_ClearFlag(actor, 0);
            FieldActor_RequestState38(actor, work->x, work->z, work->yaw, 6, -1);
            break;
        case 0x39:
            FieldActor_ClearFlag(actor, 0);
            FieldActor_RequestState39(actor, (work->flags & 0xc) >> 2, work->x, work->z, work->yaw, 6, -1);
            break;
        case 0x10:
            FieldActor_ClearFlag(actor, 0);
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestState10(actor, 3, 5, -1);
            break;
        case 2:
            EventQueue_FinishKind4Or12();
            move_on(actor);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022178cc, FieldActor_StepState3D)

/* func_ov003_02217a38: leaving state 0x3d, the held item takes the weight 1.0 with flags 2;
 * otherwise 0, and flag 0 is cleared. */
void FieldActor_ExitState3D(FieldActor *actor)
{
    if ((actor->work.s3d.flags & 3) == 2) {
        set_held_weight(actor, 0x1000);
    } else {
        set_held_weight(actor, 0);
        FieldActor_ClearFlag(actor, 0);
    }
}
CLEAN_AS(func_ov003_02217a38, FieldActor_ExitState3D)

/* func_ov003_02217a6c: state 0x3d's message handler asks for the state again with the saved
 * point, yaw and flags, the next state decoded from the flags' high nibble as for state 0x3e. */
void FieldActor_State3DMessage(FieldActor *actor, int arg)
{
    u8 flags;
    fx32 x;
    fx32 z;
    u16 yaw;
    int next;

    FieldActor_GetState3DSaved(&actor->saved.s3d, &flags, &x, &z, &yaw);
    switch (flags & 0xf0) {
        case 0x00:
            next = 0x38;
            break;
        case 0x10:
            next = 0x39;
            break;
        case 0x20:
            next = 0x10;
            break;
        default:
            next = 2;
            break;
    }
    FieldActor_RequestState3D(actor, next, flags & 0xf, x, z, (s16) yaw, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02217a6c, FieldActor_State3DMessage)

/* func_ov003_02217adc: entering state 0x3d: animation 0x6b starts while the player's record
 * holds no item (ITEM_NONE, the item put back after). With flags 2, flag 0 is set, the weight
 * starts at 0 and the animation plays backwards from its last frame; otherwise the weight starts
 * at 1.0. The request becomes the work, and is saved with the next state coded into the flags
 * as state 0x3e does; sound 0x4f. */
void FieldActor_EnterState3D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State3EWork *args = (const State3EWork *) (const void *) request->payload;
    u16 items[2];
    fx32 weight;

    FieldActor_RecordHeldItem(&items[0], actor);
    void *record = FieldActor_Record(actor);
    items[1] = ITEM_NONE;
    PlayerRecord_SetHeldItem(record, &items[1]);
    FieldActor_PlayAnimationOnce(actor, 0x6b, 3, 0);
    PlayerRecord_SetHeldItem(record, &items[0]);

    if ((args->flags & 3) == 2) {
        FieldActor_SetFlag(actor, 0);
        weight = 0;
        u32 frames = anim_frames(actor);
        FrameCtrl_Init(&actor->anim, frames, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) (frames - 1));
    } else {
        weight = 0x1000;
    }

    int next = args->next;
    u8 flags = args->flags;
    fx32 x = args->x;
    fx32 z = args->z;
    s16 yaw = args->value;
    FieldActor_SetState3DWork(&actor->work.s3d, next, flags, x, z, yaw, weight);

    switch (next) {
        case 0x39:
            flags |= 0x10;
            break;
        case 0x10:
            flags |= 0x20;
            break;
        case 2:
            flags |= 0x30;
            break;
        default:
            break;
    }
    FieldActor_SetState3DSaved(&actor->saved.s3d, (char) flags, x, z, yaw);
    FieldActor_PlaySound(actor, 0x4f);
}
CLEAN_AS(func_ov003_02217adc, FieldActor_EnterState3D)

/* func_ov003_02217bf0: the saved flags (read first), point and yaw. */
void FieldActor_GetState3DSaved(const State3ESaved *saved, u8 *flags, fx32 *x, fx32 *z, u16 *yaw)
{
    *flags = saved->flags;
    PackedBytes_UnpackPoint(saved->xz, (u32 *) x, (u32 *) z);
    *yaw = (u16) PackedBytes_ReadS16(saved->value);
}
CLEAN_AS(func_ov003_02217bf0, FieldActor_GetState3DSaved)

/* func_ov003_02217c14: the flags first, then the point and the yaw packed. */
void FieldActor_SetState3DSaved(State3ESaved *saved, char flags, fx32 x, fx32 z, s16 yaw)
{
    saved->flags = (u8) flags;
    PackedBytes_PackPoint(saved->xz, x, z);
    PackedBytes_WriteS16(saved->value, yaw);
}
CLEAN_AS(func_ov003_02217c14, FieldActor_SetState3DSaved)

/* func_ov003_02217c3c */
void FieldActor_SetState3DWork(State3DWork *work, int next, int flags, fx32 x, fx32 z, s16 yaw, fx32 weight)
{
    work->next = next;
    work->flags = (u8) flags;
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->weight = weight;
}
CLEAN_AS(func_ov003_02217c3c, FieldActor_SetState3DWork)

/* func_ov003_02217c5c: asks for state 0x3d, flag 1 cleared before the request is queued; while
 * the held item is in 0x1380-0x13a7 asks for state 0x3e with the same arguments instead.
 * Whether it was queued. */
int FieldActor_RequestState3D(FieldActor *actor, int next, int flags, fx32 x, fx32 z, s16 yaw, int priority, s16 arg)
{
    StateRequest request;
    u16 item;

    FieldActor_RecordHeldItem(&item, actor);
    if (is_item_1380(item)) {
        return FieldActor_RequestState3E(actor, next, flags, x, z, yaw, priority, arg);
    }
    open_request(&request, 0x3d, priority, arg);
    FieldActor_SetState3DArgs((State3EWork *) (void *) request.payload, next, (char) flags, x, z, yaw);
    FieldActor_ClearFlag(actor, 1);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02217c5c, FieldActor_RequestState3D)

/* func_ov003_02217d1c: the request's payload, laid out as state 0x3e's. */
void FieldActor_SetState3DArgs(State3EWork *args, int next, char flags, fx32 x, fx32 z, s16 yaw)
{
    args->next = next;
    args->flags = (u8) flags;
    args->x = x;
    args->z = z;
    args->value = yaw;
}
CLEAN_AS(func_ov003_02217d1c, FieldActor_SetState3DArgs)

/* ---- State 0x3c: animation 0x34 or 0x35, held until another state is asked for */

/* func_ov003_02217d38: state 0x3c's update does nothing. */
void FieldActor_UpdateState3C(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov003_02217d38, FieldActor_UpdateState3C)

/* func_ov003_02217d3c: leaving state 0x3c for any state but 0x3b and 0x3d sets flag 0. */
void FieldActor_ExitState3C(FieldActor *actor, int next)
{
    if (next == 0x3b || next == 0x3d) {
        return;
    }
    FieldActor_SetFlag(actor, 0);
}
CLEAN_AS(func_ov003_02217d3c, FieldActor_ExitState3C)

/* func_ov003_02217d54: state 0x3c's message handler asks for the state again.
 * QUIRK: with priority 1, not the 6 of the other handlers. */
void FieldActor_State3CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState3C(actor, 1, arg);
}
CLEAN_AS(func_ov003_02217d54, FieldActor_State3CMessage)

/* func_ov003_02217d60: entering state 0x3c: flag 0 is cleared, animation 0x34 starts if
 * func_ov003_022203ac says so, else 0x35, and the word at 0x7f8 is cleared. When bit 0 or bit 5
 * of func_0208602c's flags is set, the player at this console gets func_02035684 (0x12, 0xf). */
void FieldActor_EnterState3C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_ClearFlag(actor, 0);
    if (ObjectActors_PoseFlag()) {
        FieldActor_PlayAnimationOnce(actor, 0x34, 0, 0);
    } else {
        FieldActor_PlayAnimationOnce(actor, 0x35, 0, 0);
    }
    actor->unk_7F8 = 0;
    if (Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), 0) || Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), 5)) {
        if (is_local_player(actor)) {
            Music_AddValue(0x12, 0xf, 0);
        }
    }
}
CLEAN_AS(func_ov003_02217d60, FieldActor_EnterState3C)

/* func_ov003_02217ddc: asks for state 0x3c; whether it was queued. */
int FieldActor_RequestState3C(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x3c, priority, arg);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02217ddc, FieldActor_RequestState3C)

/* ---- State 0x3b: animation 0x34, 0x35 or 0x36, then an end by its kind */

static_assert(offsetof(FieldActor, work.s3b.count) == 0x7d5, "state 0x3b count");

/* func_ov003_02217e14: state 0x3b's update. */
void FieldActor_UpdateState3B(FieldActor *actor)
{
    FieldActor_RunState3B(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState3B(actor);
}
CLEAN_AS(func_ov003_02217e14, FieldActor_UpdateState3B)

/* func_ov003_02217e30: at the animation's end func_0200f3e8 runs, the state after this one is
 * noted, and flag 0x1d is cleared for kinds 0 and 1 while the held item is in 0x1380-0x13a7.
 * Then by the kind:
 *   0: holding an item, unless func_020b22dc or flag 0x1d, the actor asks for state 0x3d (next
 *      state 2, flags 2); otherwise flag 0 is set for the player at this console holding
 *      nothing, and kind 1 follows;
 *   1: flag 0 is set when holding nothing, func_0203e110 runs, flag 0x1d is cleared and
 *      func_0200d4e8 (3) moves on;
 *   2: for the player at this console bit 0 of func_0208602c's flags goes to func_020860d4;
 *      unless func_020b22dc, state 0x76 (2) is asked for; otherwise func_0203e110 runs, flag 0
 *      is set for the player at this console or another holding nothing, and the actor moves
 *      on as for kind 1;
 *   3: for the player at this console func_020860d4 (bit 5), func_02098fd0 (bit 1 of the
 *      record) and func_02042500 run; state 0x76 (3) is asked for. */
void FieldActor_EndState3B(FieldActor *actor)
{
    u16 item;

    if (!anim_done(actor)) {
        return;
    }
    FieldActor_NudgeOne(actor);
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    u8 kind = actor->work.s3b.kind;
    FieldActor_RecordHeldItem(&item, actor);
    if (kind <= 1 && is_item_1380(item)) {
        FieldActor_ClearFlag(actor, 0x1d);
    }

    switch (actor->work.s3b.kind) {
        case 0:
            if (!item_is_nothing(&item) && !Block020b220c_Flag4b1c() && !FieldActor_TestFlag(actor, 0x1d)) {
                FieldActor_RequestState3D(actor, 2, 2, 0, 0, 0, 6, -1);
                break;
            }
            if (is_local_player(actor) && item_is_nothing(&item)) {
                FieldActor_SetFlag(actor, 0);
            }
            /* fall through */
        case 1:
            if (item_is_nothing(&item)) {
                FieldActor_SetFlag(actor, 0);
            }
            EventQueue_FinishKind4Or12();
            FieldActor_ClearFlag(actor, 0x1d);
            FieldActor_RequestState2(actor, 3, 1, -1);
            break;
        case 2: {
            void *session = data_020ccf94;
            if (Session_IsLocalPlayer(session, actor->player)) {
                Block021d27ac_ClearFlag((u32 *) Block021d27ac_Get(), 0);
            }
            if (!Block020b220c_Flag4b1c()) {
                FieldActor_RequestState76(actor, 2, 0, 0, 6, -1);
                break;
            }
            EventQueue_FinishKind4Or12();
            BOOL set_flag = TRUE;
            if (!Session_IsLocalPlayer(session, actor->player)) {
                u16 held;
                FieldActor_RecordHeldItem(&held, actor);
                set_flag = item_is_nothing(&held);
            }
            if (set_flag) {
                FieldActor_SetFlag(actor, 0);
            }
            FieldActor_ClearFlag(actor, 0x1d);
            FieldActor_RequestState2(actor, 3, 1, -1);
            break;
        }
        case 3:
            if (is_local_player(actor)) {
                Block021d27ac_ClearFlag((u32 *) Block021d27ac_Get(), 5);
                PlayerRecord_ClearFlag(PlayerRecords_Current(), 1);
                BoardNotices_Update();
            }
            FieldActor_RequestState76(actor, 3, 0, 0, 6, -1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02217e30, FieldActor_EndState3B)

/* func_ov003_02218108: while the count runs, it falls by one a frame, and animation 0x36 gives
 * way to 0x35 (5) when it reaches 0. With no count func_0200f888 runs at frames 0xd, 0x11,
 * 0x17, 0x1c, 0x25 and 0x28 of animation 0x34 and frames 4, 9, 0xe and 0x14 of animation
 * 0x35. */
void FieldActor_RunState3B(FieldActor *actor)
{
    u8 *count = &actor->work.s3b.count;

    FieldActor_UpdateBody(actor);
    if (*count != 0) {
        *count = (u8) (*count - 1);
        if (*count == 0 && actor->animation == 0x36) {
            FieldActor_PlayAnimationOnce(actor, 0x35, 5, 0);
        }
        return;
    }
    if (actor->animation == 0x34) {
        switch (anim_frame(actor)) {
            case 0xd:
            case 0x11:
            case 0x17:
            case 0x1c:
            case 0x25:
            case 0x28:
                FieldActor_PlayFootstep(actor);
                break;
            default:
                break;
        }
    } else if (actor->animation == 0x35) {
        switch (anim_frame(actor)) {
            case 4:
            case 9:
            case 0xe:
            case 0x14:
                FieldActor_PlayFootstep(actor);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov003_02218108, FieldActor_RunState3B)

/* func_ov003_022181c8: state 0x3b's message handler stores its argument at 0xc84 when the actor
 * is in state 0x3b; otherwise it asks for the state again with the saved bytes. */
void FieldActor_State3BMessage(FieldActor *actor, int arg)
{
    if (actor->state == 0x3b) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    u8 alt;
    u8 kind;
    FieldActor_GetState3BSaved(&actor->saved.s3b, &alt, &kind);
    FieldActor_RequestState3B(actor, alt, kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022181c8, FieldActor_State3BMessage)

/* func_ov003_02218210: entering state 0x3b: flag 0 is cleared. For the player at this console
 * `alt` is func_ov003_022203ac, and the kind is 1 when func_020b65c4 is 0, the player's record
 * has bit 0x23 and func_020b67e8 accepts func_020b65b8 or it is 6; else 2 or 3 for bit 0 or
 * bit 5 of func_0208602c's flags; else 0. Other actors take both from the request. With `alt`
 * animation 0x34 starts and the count is 0; otherwise the count is func_020b29c0 of the
 * position (its low byte): up to 1 animation 0x35 starts, above it animation 0x36
 * (func_020109fc). The word at 0x7f8 is set, the kind and count become the work, `alt` and the
 * kind are saved, and func_ov003_02220368 runs on the position. */
void FieldActor_EnterState3B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State3BArgs *args = (const State3BArgs *) (const void *) request->payload;
    void *session;
    int alt;
    int kind = 0;
    u8 count;

    FieldActor_ClearFlag(actor, 0);
    session = data_020ccf94;
    if (Session_IsLocalPlayer(session, actor->player)) {
        alt = ObjectActors_PoseFlag();
    } else {
        alt = args->alt;
    }

    if (Session_IsLocalPlayer(session, actor->player)) {
        void *record = PlayerRecords_Current();
        if (!SceneQuery_Current() && record != NULL && PlayerRecord_TestFlag(record, 0x23) &&
            (SceneKinds_IsHouseRoom(SceneQuery_Previous()) || SceneQuery_Previous() == 6)) {
            kind = 1;
        } else if (Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), 0)) {
            kind = 2;
        } else if (Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), 5)) {
            kind = 3;
        }
    } else {
        kind = args->kind;
    }

    if (alt != 0) {
        FieldActor_PlayAnimationOnce(actor, 0x34, 0, 0);
        count = 0;
    } else {
        count = (u8) TownObjects_NearbyActorValue(&actor->position);
        if (count <= 1) {
            FieldActor_PlayAnimationOnce(actor, 0x35, 0, 0);
        } else {
            FieldActor_PlayAnimationLoop(actor, 0x36, 0, 0);
        }
    }
    actor->unk_7F8 = 1;

    actor->work.s3b.count = count;
    actor->work.s3b.kind = (u8) kind;
    FieldActor_SetState3BSaved(&actor->saved.s3b, alt, kind);
    ObjectActors_SetNearModeA(&actor->position);
}
CLEAN_AS(func_ov003_02218210, FieldActor_EnterState3B)

/* func_ov003_02218330 */
void FieldActor_GetState3BSaved(const State3BArgs *saved, u8 *alt, u8 *kind)
{
    *alt = saved->alt;
    *kind = saved->kind;
}
CLEAN_AS(func_ov003_02218330, FieldActor_GetState3BSaved)

/* func_ov003_0221833c */
void FieldActor_SetState3BSaved(State3BArgs *saved, int alt, int kind)
{
    saved->alt = (u8) alt;
    saved->kind = (u8) kind;
}
CLEAN_AS(func_ov003_0221833c, FieldActor_SetState3BSaved)

/* func_ov003_02218344: asks for state 0x3b; whether it was queued. */
int FieldActor_RequestState3B(FieldActor *actor, int alt, int kind, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x3b, priority, arg);
    State3BArgs *args = (State3BArgs *) (void *) request.payload;
    args->alt = (u8) alt;
    args->kind = (u8) kind;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02218344, FieldActor_RequestState3B)

/* func_ov003_02218388: asks for state 0x3b with `alt` and the kind 0 (what other actors take;
 * the player at this console picks its own); whether it was queued. */
int FieldActor_RequestState3BPlain(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x3b, priority, arg);
    State3BArgs *args = (State3BArgs *) (void *) request.payload;
    args->alt = 0;
    args->kind = 0;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02218388, FieldActor_RequestState3BPlain)

/* ---- State 0x3a: nothing but the word at 0x7f8 cleared */

/* func_ov003_022183c8: state 0x3a's update does nothing. */
void FieldActor_UpdateState3A(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov003_022183c8, FieldActor_UpdateState3A)

/* func_ov003_022183cc: state 0x3a's message handler asks for the state again. */
void FieldActor_State3AMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState3A(actor, 6, arg);
}
CLEAN_AS(func_ov003_022183cc, FieldActor_State3AMessage)

/* func_ov003_022183d8: entering state 0x3a clears flag 0 and the word at 0x7f8. */
void FieldActor_EnterState3A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_ClearFlag(actor, 0);
    actor->unk_7F8 = 0;
}
CLEAN_AS(func_ov003_022183d8, FieldActor_EnterState3A)

/* func_ov003_022183f4: asks for state 0x3a; whether it was queued. */
int FieldActor_RequestState3A(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x3a, priority, arg);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022183f4, FieldActor_RequestState3A)

/* ---- State 0x39: animation 0x32 or 0x33 at a point and yaw, then state 0x3a */

static_assert(offsetof(FieldActor, work.s39.kind) == 0x7de, "state 0x39 kind");
static_assert(offsetof(FieldActor, work.s39.count) == 0x7df, "state 0x39 count");

/* func_ov003_0221842c: state 0x39's update. */
void FieldActor_UpdateState39(FieldActor *actor)
{
    FieldActor_RunState39(actor);
    FieldActor_SoundState39(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState39(actor);
}
CLEAN_AS(func_ov003_0221842c, FieldActor_UpdateState39)

/* func_ov003_0221844c: at the animation's end the actor asks for state 0x3a. */
void FieldActor_EndState39(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    FieldActor_RequestState3A(actor, 6, -1);
}
CLEAN_AS(func_ov003_0221844c, FieldActor_EndState39)

/* func_ov003_02218474: func_0200f888 runs at frames 8, 12, 22, 27 and 34 of animation 0x32 and
 * frames 9, 17 and 26 of animation 0x33. */
void FieldActor_SoundState39(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (actor->animation == 0x32) {
        switch (anim_frame(actor)) {
            case 8:
            case 12:
            case 22:
            case 27:
            case 34:
                FieldActor_PlayFootstep(actor);
                break;
            default:
                break;
        }
    } else if (actor->animation == 0x33) {
        switch (anim_frame(actor)) {
            case 9:
            case 17:
            case 26:
                FieldActor_PlayFootstep(actor);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov003_02218474, FieldActor_SoundState39)

/* func_ov003_022184e8: while the count runs it falls by one a frame, and animation 0x33 starts
 * when it reaches 0; with no count the actor is held at the work's point and yaw
 * (func_0200fbc4). */
void FieldActor_RunState39(FieldActor *actor)
{
    State39Work *work = &actor->work.s39;

    if (work->count != 0) {
        work->count = (u8) (work->count - 1);
        if (work->count == 0) {
            FieldActor_PlayAnimationOnce(actor, 0x33, 3, 0);
        }
    } else {
        FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
    }
}
CLEAN_AS(func_ov003_022184e8, FieldActor_RunState39)

/* func_ov003_02218524: state 0x39's message handler stores its argument at 0xc84 when the actor
 * is in state 0x38, 0x39 or 0x3a. Otherwise the actor takes, as its x and z, the point
 * func_02096614 gives for its player (if any) and the saved yaw, and asks for state 0x39 again
 * with the saved kind, point and yaw. */
void FieldActor_State39Message(FieldActor *actor, int arg)
{
    u8 kind;
    u8 unused;
    u16 yaw;
    fx32 x;
    fx32 z;
    fx32 at_x;
    fx32 at_z;

    if ((u32) actor->state - 0x38u <= 2) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    FieldActor_GetState39Saved(&actor->saved.s39, &kind, &x, &z, &yaw);
    if (SessionPlayers_ScenePoint(&unused, (int *) &at_x, (int *) &at_z, -1, actor->player)) {
        actor->position.x = at_x;
        actor->position.z = at_z;
    }
    actor->yaw = (s16) yaw;
    FieldActor_RequestState39(actor, kind, x, z, (s16) yaw, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02218524, FieldActor_State39Message)

/* func_ov003_022185b0: entering state 0x39: flag 4 is set and the animation chosen by the kind
 * starts (0: 0x33; 1: 0x32; 2: animation 0 by func_020109fc, with a count of 12 frames). The
 * request becomes the work and is saved, and func_ov003_02220384 runs on the position.
 * QUIRK: the ROM also passes func_ov003_02220384 whether the actor is the player at this
 * console (func_02073908), an argument that function does not take. */
void FieldActor_EnterState39(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State39Work *args = (const State39Work *) (const void *) request->payload;
    u8 count = 0;

    FieldActor_SetFlag(actor, 4);
    switch (args->kind) {
        case 0:
            FieldActor_PlayAnimationOnce(actor, 0x33, 3, 0);
            break;
        case 1:
            FieldActor_PlayAnimationOnce(actor, 0x32, 3, 0);
            break;
        case 2:
            count = 12;
            FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
            break;
        default:
            break;
    }
    u8 kind = args->kind;
    fx32 x = args->x;
    fx32 z = args->z;
    s16 yaw = args->yaw;
    FieldActor_SetState39Work(&actor->work.s39, (char) kind, x, z, yaw, count);
    FieldActor_SetState39Saved(&actor->saved.s39, (char) kind, x, z, yaw);
    (void) is_local_player(actor);
    ObjectActors_SetNearModeB(&actor->position);
}
CLEAN_AS(func_ov003_022185b0, FieldActor_EnterState39)

/* func_ov003_02218664: the saved kind (read first), point and yaw. */
void FieldActor_GetState39Saved(const State3ESaved *saved, u8 *kind, fx32 *x, fx32 *z, u16 *yaw)
{
    *kind = saved->flags;
    PackedBytes_UnpackPoint(saved->xz, (u32 *) x, (u32 *) z);
    *yaw = (u16) PackedBytes_ReadS16(saved->value);
}
CLEAN_AS(func_ov003_02218664, FieldActor_GetState39Saved)

/* func_ov003_02218688: the kind first, then the point and the yaw packed. */
void FieldActor_SetState39Saved(State3ESaved *saved, char kind, fx32 x, fx32 z, s16 yaw)
{
    saved->flags = (u8) kind;
    PackedBytes_PackPoint(saved->xz, x, z);
    PackedBytes_WriteS16(saved->value, yaw);
}
CLEAN_AS(func_ov003_02218688, FieldActor_SetState39Saved)

/* func_ov003_022186b0 */
void FieldActor_SetState39Work(State39Work *work, char kind, fx32 x, fx32 z, s16 yaw, u8 count)
{
    work->kind = (u8) kind;
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->count = count;
}
CLEAN_AS(func_ov003_022186b0, FieldActor_SetState39Work)

/* func_ov003_022186cc: asks for state 0x39; whether it was queued. */
int FieldActor_RequestState39(FieldActor *actor, int kind, fx32 x, fx32 z, s16 yaw, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x39, priority, arg);
    FieldActor_SetState39Args((State39Work *) (void *) request.payload, (char) kind, x, z, yaw);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022186cc, FieldActor_RequestState39)

/* func_ov003_0221871c: the request's payload (no count). */
void FieldActor_SetState39Args(State39Work *args, char kind, fx32 x, fx32 z, s16 yaw)
{
    args->kind = (u8) kind;
    args->x = x;
    args->z = z;
    args->yaw = yaw;
}
CLEAN_AS(func_ov003_0221871c, FieldActor_SetState39Args)

/* ---- State 0x38: animation 0x37 at a point and yaw, then state 0x39 (kind 1) */

/* func_ov003_02218734: state 0x38's update. */
void FieldActor_UpdateState38(FieldActor *actor)
{
    FieldActor_FaceState38(actor);
    FieldActor_RunState38(actor);
    FieldActor_EnterContact(actor);
    FieldActor_EndState38(actor);
}
CLEAN_AS(func_ov003_02218734, FieldActor_UpdateState38)

/* func_ov003_02218754: at the animation's end the actor asks for state 0x39 (kind 1) with the
 * work's point and yaw. */
void FieldActor_EndState38(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    const State38Work *work = &actor->work.s38;
    FieldActor_RequestState39(actor, 1, work->x, work->z, work->yaw, 6, -1);
}
CLEAN_AS(func_ov003_02218754, FieldActor_EndState38)

/* func_ov003_02218798: sound 0x7d5 at frames 8 and 13. */
void FieldActor_RunState38(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 8) || anim_passed(actor, 0xd)) {
        FieldActor_PlaySound(actor, 0x7d5);
    }
}
CLEAN_AS(func_ov003_02218798, FieldActor_RunState38)

/* func_ov003_022187d4: the actor is held at the work's point and yaw (func_0200fbc4). */
void FieldActor_FaceState38(FieldActor *actor)
{
    const State38Work *work = &actor->work.s38;
    FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
}
CLEAN_AS(func_ov003_022187d4, FieldActor_FaceState38)

/* func_ov003_022187f0: state 0x38's message handler moves the actor to the saved point (its
 * height kept) and yaw, and asks for the state again with them. */
void FieldActor_State38Message(FieldActor *actor, int arg)
{
    fx32 x;
    fx32 z;
    s16 yaw;

    FieldActor_GetState38Saved(&actor->saved.s38, &x, &z, &yaw);
    Vec3 point = {x, actor->position.y, z};
    copy_point(&actor->position, &point);
    actor->yaw = yaw;
    FieldActor_RequestState38(actor, x, z, yaw, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022187f0, FieldActor_State38Message)

/* func_ov003_02218844: entering state 0x38: animation 0x37; the request becomes the work and is
 * saved. */
void FieldActor_EnterState38(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State38Work *args = (const State38Work *) (const void *) request->payload;

    FieldActor_PlayAnimationOnce(actor, 0x37, 3, 0);
    fx32 x = args->x;
    fx32 z = args->z;
    s16 yaw = args->yaw;
    FieldActor_SetState38Work(&actor->work.s38, x, z, yaw);
    FieldActor_SetState38Saved(&actor->saved.s38, x, z, yaw);
}
CLEAN_AS(func_ov003_02218844, FieldActor_EnterState38)

/* func_ov003_02218890: the saved point and yaw. */
void FieldActor_GetState38Saved(const State3ESaved *saved, fx32 *x, fx32 *z, s16 *yaw)
{
    PackedBytes_UnpackPoint(saved->xz, (u32 *) x, (u32 *) z);
    *yaw = PackedBytes_ReadS16(saved->value);
}
CLEAN_AS(func_ov003_02218890, FieldActor_GetState38Saved)

/* func_ov003_022188ac: the point and the yaw packed. */
void FieldActor_SetState38Saved(State3ESaved *saved, fx32 x, fx32 z, int yaw)
{
    PackedBytes_PackPoint(saved->xz, x, z);
    PackedBytes_WriteS16(saved->value, yaw);
}
CLEAN_AS(func_ov003_022188ac, FieldActor_SetState38Saved)

/* func_ov003_022188c8 */
void FieldActor_SetState38Work(State38Work *work, fx32 x, fx32 z, int yaw)
{
    work->x = x;
    work->z = z;
    work->yaw = (s16) yaw;
}
CLEAN_AS(func_ov003_022188c8, FieldActor_SetState38Work)

/* func_ov003_022188d0: asks for state 0x38; whether it was queued. */
int FieldActor_RequestState38(FieldActor *actor, fx32 x, fx32 z, int yaw, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x38, priority, arg);
    FieldActor_SetState38Args((State38Work *) (void *) request.payload, x, z, yaw);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022188d0, FieldActor_RequestState38)

/* func_ov003_02218918 */
void FieldActor_SetState38Args(State38Work *args, fx32 x, fx32 z, int yaw)
{
    args->x = x;
    args->z = z;
    args->yaw = (s16) yaw;
}
CLEAN_AS(func_ov003_02218918, FieldActor_SetState38Args)

/* ---- State 0x17: animation 0x14 towards a tile, acting on its map object at frame 10 */

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

static_assert(offsetof(FieldActor, work.s17.unk_0C) == 0x7e0, "state 0x17 byte");
static_assert(offsetof(FieldActor, work.s16.outcome) == 0x7d6, "state 0x16 outcome");

/* Where effect 0x2d starts for the map objects 0x21 to 0x24, from their point. */
static const Vec3 STATE17_OFFSETS[4] = {
    {0, 0, -0x800},
    {-0x800, 0, 0},
    {0x800, 0, 0xc00},
    {-0x800, 0, 0},
};

/* func_ov003_02218920: state 0x17's update: the actor walks to the work's point
 * (func_0200f434). */
void FieldActor_UpdateState17(FieldActor *actor)
{
    FieldActor_RunState17(actor);
    Vec3 point = actor->work.s17.point;
    FieldActor_FollowReportedTo(actor, &point);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActor_EndState17(actor);
}
CLEAN_AS(func_ov003_02218920, FieldActor_UpdateState17)

/* func_ov003_02218960: at the animation's end the actor moves on; from frame 14 on the player at
 * this console resumes moving (FieldActor_ResumeMoving) and other actors clear flag 0x12. */
void FieldActor_EndState17(FieldActor *actor)
{
    if (anim_done(actor)) {
        move_on(actor);
    }
    if (anim_frame(actor) >= 0xe) {
        if (is_local_player(actor)) {
            FieldActor_ResumeMoving(actor);
        } else {
            FieldActor_ClearFlag(actor, 0x12);
        }
    }
}
CLEAN_AS(func_ov003_02218960, FieldActor_EndState17)

/* func_ov003_022189d8: acts on the map object at the work's point, whose code was noted on
 * entering (FieldActor.item): 0x1f and 0x20 start effects 0x2e and 0x2f there, 0x21 to 0x24
 * effect 0x2d a little off it (STATE17_OFFSETS), all turned by the actor's yaw; the codes of
 * families B and C and those after them (0x6e-0xa5) start effect 0x54 (func_02091230) and go to
 * func_02044a14 with the tile, the yaw and 2, with sound 0x7d8. Sound 0x7d8 also follows 0x1f
 * and 0x20, 0x7ec the codes 0x21 to 0x24; then func_02045f08 runs on the tile and flag 0x1c is
 * cleared. */
void FieldActor_ActState17(FieldActor *actor)
{
    Vec3 at;
    int tile[2] = {0, 0};
    s16 yaw;

    copy_point(&at, &actor->work.s17.point);
    Position_Tile(&tile[0], &tile[1], (const Position *) &at);
    yaw = actor->yaw;

    switch (actor->item) {
        case 0x1f:
            EffectSystem_StartKind(0x2e, &at, &yaw, 0);
            break;
        case 0x20:
            EffectSystem_StartKind(0x2f, &at, &yaw, 0);
            break;
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
            VEC_Add(&at, &STATE17_OFFSETS[actor->item - 0x21], &at);
            EffectSystem_StartKind(0x2d, &at, &yaw, 0);
            break;
        default:
            if (actor->item >= 0x6e && actor->item <= 0xa5) {
                EffectSystem_StartOneShotSetNumber(0x54, &at, 0, 0);
                u16 code = actor->item;
                int code_tile[2] = {tile[0], tile[1]};
                TileEffects_StartTurned(&code, (const TileEffectsTile *) code_tile, actor->yaw, 2);
                FieldActor_PlaySound(actor, 0x7d8);
            }
            break;
    }

    switch (actor->item) {
        case 0x1f:
        case 0x20:
            FieldActor_PlaySound(actor, 0x7d8);
            break;
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
            FieldActor_PlaySound(actor, 0x7ec);
            break;
        default:
            break;
    }

    int end_tile[2] = {tile[0], tile[1]};
    TileChanges_FinishAtTile((const TileChangesTile *) end_tile, 0);
    FieldActor_ClearFlag(actor, 0x1c);
}
CLEAN_AS(func_ov003_022189d8, FieldActor_ActState17)

/* func_ov003_02218bc8: frame 10 acts on the map object (FieldActor_ActState17). */
void FieldActor_RunState17(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_passed(actor, 10)) {
        FieldActor_ActState17(actor);
    }
}
CLEAN_AS(func_ov003_02218bc8, FieldActor_RunState17)

/* func_ov003_02218bf0: another player's actor that leaves state 0x17 with flag 0x1c still set
 * acts on the map object then. */
void FieldActor_ExitState17(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0x1c)) {
        return;
    }
    FieldActor_ActState17(actor);
}
CLEAN_AS(func_ov003_02218bf0, FieldActor_ExitState17)

/* func_ov003_02218c24: state 0x17's message handler does nothing. */
void FieldActor_State17Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02218c24, FieldActor_State17Message)

/* func_ov003_02218c28: entering state 0x17: the middle of the request's tile becomes the work's
 * point, animation 0x14 starts, the held item takes pose 0xe when func_0200fbe0 says 4, and the
 * map object at the point is noted (at 0x822, then copied to `item`).
 * REQUIRES: func_0204f5a8 finds a map object at the point (the ROM reads it unchecked). */
void FieldActor_EnterState17(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileArgs *args = (const TileArgs *) (const void *) request->payload;
    Vec3 point;

    AcreTile_TileCentre(&point, args->x, args->z);
    copy_point(&actor->work.s17.point, &point);
    actor->work.s17.unk_0C = 0;
    FieldActor_PlayAnimationOnce(actor, 0x14, 3, 0);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 0xe, 3, 0);
    }
    actor->unk_822 = *AcreTile_ItemAt(data_021c80bc, &point, 0);
    actor->item = actor->unk_822;
}
CLEAN_AS(func_ov003_02218c28, FieldActor_EnterState17)

/* func_ov003_02218ca8: asks for state 0x17 on a tile (the low bytes of its two words); whether
 * it was queued. */
int FieldActor_RequestState17(FieldActor *actor, const u32 *tile, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x17, priority, arg);
    TileArgs *args = (TileArgs *) (void *) request.payload;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02218ca8, FieldActor_RequestState17)

/* ---- State 0x16: waiting on a tile, then state 0x17 or the usual end */

/* func_ov003_02218cec: state 0x16's update: the player at this console waits for the outcome;
 * other actors walk to the work's tile (func_0200f530). */
void FieldActor_UpdateState16(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_RunState16Local(actor);
    } else {
        FieldActor_UpdateBody(actor);
        int tile[2] = {actor->work.s16.x, actor->work.s16.z};
        FieldActor_FollowReportedToTile(actor, tile);
    }
    FieldActor_EnterContact(actor);
    FieldActor_EndState16(actor);
}
CLEAN_AS(func_ov003_02218cec, FieldActor_UpdateState16)

/* func_ov003_02218d44: other actors note the state after this one each frame. Outcome 1 asks
 * for state 0x17 on the work's tile, outcome 2 moves on the usual way. */
void FieldActor_EndState16(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
    switch (actor->work.s16.outcome) {
        case 1: {
            u32 tile[2] = {actor->work.s16.x, actor->work.s16.z};
            FieldActor_RequestState17(actor, tile, 6, -1);
            break;
        }
        case 2:
            move_on(actor);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02218d44, FieldActor_EndState16)

/* func_ov003_02218dcc: until the outcome is known it is taken from the word at 0x818 (1 or 2). */
void FieldActor_RunState16Local(FieldActor *actor)
{
    u8 *outcome = &actor->work.s16.outcome;

    if (*outcome == 0) {
        if (actor->unk_818 == 2) {
            *outcome = 2;
        } else if (actor->unk_818 == 1) {
            *outcome = 1;
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov003_02218dcc, FieldActor_RunState16Local)

/* func_ov003_02218dfc: state 0x16's message handler: an actor already in it keeps the argument
 * at 0xc84; otherwise state 0x16 is asked for on the saved tile. */
void FieldActor_State16Message(FieldActor *actor, int arg)
{
    if (actor->state == 0x16) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    int tile[2] = {0, 0};
    FieldActor_GetState16Saved(&actor->saved.tile, tile);
    FieldActor_RequestState16(actor, tile, 6, arg);
}
CLEAN_AS(func_ov003_02218dfc, FieldActor_State16Message)

/* func_ov003_02218e4c: entering state 0x16: the request's tile becomes the work's and is saved,
 * the outcome is not known yet, animation 0x15 starts and the held item takes pose 0xb when
 * func_0200fbe0 says 4. */
void FieldActor_EnterState16(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileArgs *args = (const TileArgs *) (const void *) request->payload;
    u8 x = args->x;
    u8 z = args->z;

    actor->work.s16.x = x;
    actor->work.s16.z = z;
    actor->work.s16.outcome = 0;
    int tile[2] = {x, z};
    FieldActor_SetState16Saved(&actor->saved.tile, tile);
    FieldActor_PlayAnimationLoop(actor, 0x15, 3, 0);
    if (FieldActor_HeldTool(actor) == 4) {
        HeldItem_Act(actor->held, 0xb, 3, 0);
    }
}
CLEAN_AS(func_ov003_02218e4c, FieldActor_EnterState16)

/* func_ov003_02218eac: the saved tile, as two words. */
void FieldActor_GetState16Saved(const TileArgs *saved, int *tile)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
}
CLEAN_AS(func_ov003_02218eac, FieldActor_GetState16Saved)

/* func_ov003_02218eb8: saves a tile (the low bytes of its two words). */
void FieldActor_SetState16Saved(TileArgs *saved, const int *tile)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02218eb8, FieldActor_SetState16Saved)

/* func_ov003_02218ec4: asks for state 0x16 on a tile; whether it was queued. */
int FieldActor_RequestState16(FieldActor *actor, const int *tile, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x16, priority, arg);
    int copy[2] = {tile[0], tile[1]};
    FieldActor_SetState16Args((TileArgs *) (void *) request.payload, copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02218ec4, FieldActor_RequestState16)

/* func_ov003_02218f0c: a request's tile (the low bytes of two words). */
void FieldActor_SetState16Args(TileArgs *args, const int *tile)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02218f0c, FieldActor_SetState16Args)

/* ---- State 0x11: animation 0x9a, then animation 0 */

/* func_ov003_02218f18: state 0x11's update: the player at this console goes on through
 * func_0200c2c8, other actors through func_0200f554. */
void FieldActor_UpdateState11(FieldActor *actor)
{
    FieldActor_RunState11(actor);
    if (is_local_player(actor)) {
        FieldActor_FaceState10Target(actor);
    } else {
        FieldActor_FollowReported(actor);
    }
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov003_02218f18, FieldActor_UpdateState11)

/* func_ov003_02218f54: animation 0 follows once animation 0x9a is over. */
void FieldActor_RunState11(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (anim_done(actor)) {
        FieldActor_PlayAnimationLoop(actor, 0, 3, 0);
    }
}
CLEAN_AS(func_ov003_02218f54, FieldActor_RunState11)

/* func_ov003_02218f80: state 0x11's message handler asks for it in mode 3, at priority 5. */
void FieldActor_State11Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState11(actor, 3, 5, arg);
}
CLEAN_AS(func_ov003_02218f80, FieldActor_State11Message)

/* func_ov003_02218f94: entering state 0x11 starts animation 0x9a in the request's mode. */
void FieldActor_EnterState11(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 mode;
    memcpy(&mode, request->payload, sizeof(mode));
    FieldActor_PlayAnimationOnce(actor, 0x9a, mode, 0);
}
CLEAN_AS(func_ov003_02218f94, FieldActor_EnterState11)

/* func_ov003_02218fac: asks for state 0x11 with the mode of animation 0x9a; whether it was
 * queued. */
int FieldActor_RequestState11(FieldActor *actor, int mode, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x11, priority, arg);
    FieldActor_SetState11Args((u16 *) (void *) request.payload, mode);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02218fac, FieldActor_RequestState11)

/* func_ov003_02218fec: a request's mode. */
void FieldActor_SetState11Args(u16 *args, int mode)
{
    *args = (u16) mode;
}
CLEAN_AS(func_ov003_02218fec, FieldActor_SetState11Args)

/* ---- State 6: holding up an insect or a fish */

/* The first insect and the first fish (main/museum_record.h: 56 of each). */
#define INSECT_FIRST 0x12b0
#define FISH_FIRST 0x12e8

static_assert(offsetof(FieldActor, work.s6.effect) == 0x7d8, "state 6 effect");
static_assert(offsetof(FieldActor, work.s6.model) == 0x7dc, "state 6 model");
static_assert(offsetof(FieldActor, work.s6.is_fish) == 0x7e0, "state 6 fish");
static_assert(offsetof(FieldActor, work.s6.step) == 0x7e1, "state 6 step");
static_assert(offsetof(FieldActor, saved.s6.progress) == 0x8f2, "state 6 progress");

/* The kind of an insect (item 0x12b0 + kind) or of a fish (0x12e8 + kind); -1 for another
 * item. */
static int insect_kind(u16 item)
{
    return in_range(item, INSECT_FIRST, INSECT_FIRST + 0x37) ? item - INSECT_FIRST : -1;
}

static int fish_kind(u16 item)
{
    return in_range(item, FISH_FIRST, FISH_FIRST + 0x37) ? item - FISH_FIRST : -1;
}

/* func_ov003_02218ff0: state 6's update: func_0200ee40 runs with the points and blocks it would
 * change kept, the creature is placed in the meantime (FieldActor_PlaceState6), and the step
 * runs last. */
void FieldActor_UpdateState6(FieldActor *actor)
{
    KeptAcrossEE40 kept;

    FieldActor_UpdateBody(actor);
    keep_across_ee40(actor, &kept);
    FieldActor_RebuildPose(actor);
    FieldActor_PlaceState6(actor);
    restore_after_ee40(actor, &kept);
    if (FieldActor_FollowReported(actor)) {
        FieldActor_MoveWithCollision(actor);
    }
    FieldActor_EnterContact(actor);
    FieldActor_RunState6(actor);
}
CLEAN_AS(func_ov003_02218ff0, FieldActor_UpdateState6)

/* func_ov003_022190b0: state 6 by the work's step.
 *   Step 0: sound 0x63 at frame 10, else 0x7f2 at frame 25; at the animation's end step 1, and
 *     the saved progress becomes 1.
 *   Step 1: the actor of this console waits for FieldActor_PlayerPutAwayShown; another player's
 *     waits for the saved progress to reach 2. Then step 2.
 *   Step 2: the effect ends, the actor of this console saves progress 2, animation 0xa0 and
 *     sound 0x7f1 start; step 3.
 *   Step 3: at the animation's end func_0200c9a8 (3) moves on.
 * BUG: the effect's handle is kept after step 2 ends the effect: later frames still move it
 * (FieldActor_PlaceState6) and leaving the state ends it again. BUGFIX marks it as gone. */
void FieldActor_RunState6(FieldActor *actor)
{
    State6Work *work = &actor->work.s6;
    State6Saved *saved = &actor->saved.s6;

    switch (work->step) {
        case 0:
            if (anim_passed(actor, 10)) {
                FieldActor_PlaySound(actor, 0x63);
            } else if (anim_passed(actor, 25)) {
                FieldActor_PlaySound(actor, 0x7f2);
            }
            if (anim_done(actor)) {
                work->step = 1;
                FieldActor_SetState6Progress(saved, 1);
            }
            break;
        case 1:
            if (!is_local_player(actor) && FieldActor_GetState6Progress(saved) >= 2) {
                work->step = 2;
            }
            break;
        case 2:
            if (work->effect > -1) {
                EffectSystem_EndHandle(work->effect);
#ifdef BUGFIX
                work->effect = -2;
#endif
            }
            if (is_local_player(actor)) {
                FieldActor_SetState6Progress(saved, 2);
            }
            FieldActor_PlayAnimationOnce(actor, 0xa0, 3, 0);
            FieldActor_PlaySound(actor, 0x7f1);
            work->step = 3;
            break;
        case 3:
            if (anim_done(actor)) {
                FieldActor_RequestState5(actor, 3, 5, -1);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022190b0, FieldActor_RunState6)

/* func_ov003_022191c0: places what the actor holds up, by the matrix at 0x698 moved by an offset
 * that grows from frame 0x10 (but in animation 0xa0); the actor turns to yaw 0 meanwhile
 * (func_0200faf0). The insects 0x18, 0x30, 0x32 and 0x33 get effect 0x5a at the matrix's
 * point the first time (the handle becomes -2 when there is none) and it follows the point.
 * A size in percent grows from frame 11 to 100 at frame 16, and in animation 0xa0 shrinks from
 * 100 to 0 over its first 6 frames: an insect goes to func_ov003_0222d83c with three equal
 * sizes, a fish's model (func_0204fdec) is scaled by it. */
void FieldActor_PlaceState6(FieldActor *actor)
{
    State6Work *work = &actor->work.s6;
    u16 item = work->item;

    FieldActor_TurnToZero(actor, 0x400);
    FieldActorBlock48 matrix = actor->unk_698;
    Vec3 offset = {0x4cd, 0, 0};
    int frame = anim_frame(actor);
    if (actor->animation != 0xa0 && frame >= 0x10) {
        int d = 0x19a * (frame - 0xf) / 0xc;
        offset.x += d * 2;
        offset.y += d;
        offset.z -= d;
    }
    FieldActor_OffsetMatrix(&matrix, &offset);

    Vec3 at;
    if (work->effect > -1) {
        at = block_point(&matrix);
        Globe_Unbend(&at, &at);
        EffectSystem_MoveHandle(work->effect, &at, NULL, 0);
    } else if (work->effect == -1) {
        work->effect = -2;
        if (!work->is_fish) {
            int kind = insect_kind(item);
            if (kind == 0x18 || kind == 0x30 || kind == 0x32 || kind == 0x33) {
                at = block_point(&matrix);
                Globe_Unbend(&at, &at);
                work->effect = EffectSystem_StartKeptSetNumber(0x5a, &at, NULL, 0);
            }
        }
    }

    int percent;
    if (actor->animation != 0xa0) {
        if (frame <= 10) {
            percent = 0;
        } else if (frame < 0x10) {
            percent = 0x11 * (frame - 10);
        } else {
            percent = 100;
        }
    } else {
        percent = frame < 6 ? 100 - 0x11 * frame : 0;
    }

    if (!work->is_fish) {
        s16 sizes[3] = {(s16) percent, (s16) percent, (s16) percent};
        TownInsect_HeldFromMatrix((u8) actor->player, sizes, (Mtx43 *) &matrix, 0);
        return;
    }

    /* The ROM rounds 4096 * (percent / 100.0f) half away from zero in single precision; for the
     * sizes 0 to 100 that is the same as this. */
    fx32 factor = (2048 * percent + 25) / 50;
    Vec3 scale;
    PlayerFish_KindScale(&scale, fish_kind(item));
    scale.x = FX_MulFunc(scale.x, factor);
    scale.y = FX_MulFunc(scale.y, factor);
    scale.z = FX_MulFunc(scale.z, factor);
    at = block_point(&matrix);
    Globe_Unbend(&at, &at);
    FishDisp_ShowModel(work->model, fish_kind(item), &at, &scale, 0, 0, 0, 1, 1, 0x1f);
}
CLEAN_AS(func_ov003_022191c0, FieldActor_PlaceState6)

/* func_ov003_02219438: leaving state 6 ends the effect, and lets an insect go
 * (func_ov003_0222e6c4) or frees the fish's model. */
void FieldActor_ExitState6(FieldActor *actor)
{
    State6Work *work = &actor->work.s6;

    if (work->effect > -1) {
        EffectSystem_EndHandle(work->effect);
    }
    if (!work->is_fish) {
        TownInsect_EndHeld((u8) actor->player, 1);
    } else {
        FishDisp_ReleaseModel(work->model);
    }
}
CLEAN_AS(func_ov003_02219438, FieldActor_ExitState6)

/* func_ov003_0221947c: state 6's message handler asks for it with the saved item, at priority
 * 5. */
void FieldActor_State6Message(FieldActor *actor, int arg)
{
    u16 item;
    FieldActor_GetState6SavedItem(&actor->saved.s6, &item);
    FieldActor_RequestState6(actor, item, 5, arg);
}
CLEAN_AS(func_ov003_0221947c, FieldActor_State6Message)

/* func_ov003_022194a8: entering state 6 with the request's item. An insect is told to
 * func_ov003_0222e898 (its kind, 0xff for another item) and animation 0x9f starts; a fish gets
 * a model (func_0204fea4) and animation 0x9e. Sound 0x4f plays. The actor of this console saves
 * the item and progress 0; another player's actor that its console reports past step 0 starts
 * at step 1 on the animation's last frame. */
void FieldActor_EnterState6(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    State6Work *work = &actor->work.s6;
    State6Saved *saved = &actor->saved.s6;
    u16 item;
    int animation;

    memcpy(&item, request->payload, sizeof(item));
    work->item = item;
    work->effect = -1;
    work->model = 0;
    work->is_fish = (u8) in_range(item, FISH_FIRST, FISH_FIRST + 0x37);
    work->step = 0;

    if (!work->is_fish) {
        TownInsect_TakeHeld((u8) insect_kind(item), (u8) actor->player);
        animation = 0x9f;
    } else {
        work->model = FishDisp_TakeModel();
        animation = 0x9e;
    }
    FieldActor_PlayAnimationOnce(actor, animation, 3, 3);
    FieldActor_PlaySound(actor, 0x4f);

    if (is_local_player(actor)) {
        FieldActor_SetState6SavedItem(saved, item);
        FieldActor_SetState6Progress(saved, 0);
    } else if (FieldActor_GetState6Progress(saved) >= 1) {
        work->step = 1;
        u16 last = (u16) (((u32) actor->anim.end >> 12) - 1);
        actor->anim.frame = last << 12;
    }
}
CLEAN_AS(func_ov003_022194a8, FieldActor_EnterState6)

/* func_ov003_022195a8: the saved progress (0 to 2). */
int FieldActor_GetState6Progress(const State6Saved *saved)
{
    return saved->progress;
}
CLEAN_AS(func_ov003_022195a8, FieldActor_GetState6Progress)

/* func_ov003_022195ac */
void FieldActor_SetState6Progress(State6Saved *saved, int progress)
{
    saved->progress = (u8) progress;
}
CLEAN_AS(func_ov003_022195ac, FieldActor_SetState6Progress)

/* func_ov003_022195b0: the saved item (packed by func_020778b0). */
void FieldActor_GetState6SavedItem(const State6Saved *saved, u16 *item)
{
    *item = PackedBytes_ReadItem(saved->item);
}
CLEAN_AS(func_ov003_022195b0, FieldActor_GetState6SavedItem)

/* func_ov003_022195c0 */
void FieldActor_SetState6SavedItem(State6Saved *saved, int item)
{
    PackedBytes_WriteItem(saved->item, item);
}
CLEAN_AS(func_ov003_022195c0, FieldActor_SetState6SavedItem)

/* func_ov003_022195c8: asks for state 6 with an item; whether it was queued. */
int FieldActor_RequestState6(FieldActor *actor, u16 item, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 6, priority, arg);
    memcpy(request.payload, &item, sizeof(item));
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022195c8, FieldActor_RequestState6)

/* ---- A player's actor, as other code asks about it or asks for its states. Player 4 is the
 *      player at this console; func_02096718 finds the actor (NULL when there is none). */

#define THIS_PLAYER 4

/* func_ov003_02219604: whether the player at this console holds item 0x1376 or 0x1377
 * (func_02095764 gives ITEM_NONE without an actor). */
int FieldActor_PlayerHolds1376(void)
{
    u16 item;
    PlayerActorOps_HeldItem(&item, THIS_PLAYER);
    return is_item_1376(item);
}
CLEAN_AS(func_ov003_02219604, FieldActor_PlayerHolds1376)

/* func_ov003_02219648: the actor of this console starts animation 0x99. */
void FieldActor_PlayerAnimation99(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor != NULL) {
        FieldActor_PlayAnimationOnce(actor, 0x99, 3, 0);
    }
}
CLEAN_AS(func_ov003_02219648, FieldActor_PlayerAnimation99)

/* func_ov003_02219668: moves a 4x3 matrix by `offset` (0.3 along x when NULL) taken in its own
 * axes: the offset turned by the matrix's rotation is added to its translation. */
void FieldActor_OffsetMatrix(FieldActorBlock48 *matrix, const Vec3 *offset)
{
    Vec3 origin = block_point(matrix);
    matrix->words[9] = 0;
    matrix->words[10] = 0;
    matrix->words[11] = 0;

    Mtx43 rotation;
    memcpy(&rotation, matrix, sizeof(rotation));
    Vec3 by = {0x4cd, 0, 0};
    if (offset != NULL) {
        by = *offset;
    }
    Vec3 turned;
    MTX_MultVec43(&by, &rotation, &turned);
    matrix->words[9] = (u32) add32(turned.x, origin.x);
    matrix->words[10] = (u32) add32(turned.y, origin.y);
    matrix->words[11] = (u32) add32(turned.z, origin.z);
}
CLEAN_AS(func_ov003_02219668, FieldActor_OffsetMatrix)

/* func_ov003_022196e0: where a player's camera looks: the float at the end of the line while
 * the actor fishes (tool 3) with a line mode above 1, else the actor's position at the start of
 * the frame (func_02095794). */
Vec3 *FieldActor_PlayerFocus(int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor != NULL && FieldActor_HeldTool(actor) == 3 && actor->line_mode > 1) {
        return &actor->unk_5D0;
    }
    return PlayerActorOps_StartPosition(player);
}
CLEAN_AS(func_ov003_022196e0, FieldActor_PlayerFocus)

/* func_ov003_02219718: lets the actor of this console put away what it holds up (state 6, step
 * 1 to 2); whether it was waiting for that. */
int FieldActor_PlayerPutAwayShown(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor != NULL && actor->state == 6 && actor->work.s6.step == 1) {
        actor->work.s6.step = 2;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02219718, FieldActor_PlayerPutAwayShown)

/* func_ov003_02219750: asks for state 6 (holding up `item`) for the actor of this console, at
 * priority 5; whether it was queued. */
int FieldActor_PlayerShowItem(int item)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState6(actor, (u16) item, 5, -1);
}
CLEAN_AS(func_ov003_02219750, FieldActor_PlayerShowItem)

/* func_ov003_02219774: the actor of this console stops what it does: after func_0203e140,
 * unless it is in state 0x77, it notes the state after this one and moves on (func_0200d4e8),
 * and its head turns back to the front (func_02095518); whether there is an actor. */
int FieldActor_PlayerStop(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    EventQueue_FinishKind14();
    int state = actor->state;
    if (state != 0x77) {
        actor->next_state = FieldActor_StateEndPriority(actor, state);
        FieldActor_RequestState2(actor, 3, 1, -1);
    }
    PlayerActorOps_SetLook(0, 0, THIS_PLAYER);
    return 1;
}
CLEAN_AS(func_ov003_02219774, FieldActor_PlayerStop)

/* func_ov003_022197c4: a player's actor (player 4: this console's) stops what it does when its
 * player is at this console: the state after this one is noted, then `how` 0 runs func_0203e140
 * and moves on (func_0200d4e8), 1 asks for state 0x65; whether there is an actor. */
int FieldActor_PlayerEndState(int how, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (player == THIS_PLAYER) {
        player = ((NetSession *) data_020ccf94)->local_player;
    }
    if (actor == NULL) {
        return 0;
    }
    if (Session_IsLocalPlayer(data_020ccf94, player)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        switch (how) {
            case 0:
                EventQueue_FinishKind14();
                FieldActor_RequestState2(actor, 3, 1, -1);
                break;
            case 1:
                FieldActor_RequestState65(actor, 6, -1);
                break;
            default:
                break;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_022197c4, FieldActor_PlayerEndState)

/* func_ov003_02219840: asks for state 0x89 for the actor of this console unless it is in it;
 * whether it was queued. */
int FieldActor_PlayerRequestState89(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL || actor->state == 0x89) {
        return 0;
    }
    return (int) (uintptr_t) FieldActor_RequestState89(actor, 6, -1);
}
CLEAN_AS(func_ov003_02219840, FieldActor_PlayerRequestState89)

/* func_ov003_02219874: the actor of this console notes the state after this one and asks for
 * state 0x11 (mode 3, priority 5); whether it was queued. */
int FieldActor_PlayerRequestState11(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    return FieldActor_RequestState11(actor, 3, 5, -1);
}
CLEAN_AS(func_ov003_02219874, FieldActor_PlayerRequestState11)

/* func_ov003_022198b0: asks for state 0x78 (priority 5) for the actor of this console when
 * func_0203e21c does not forbid it, flag 0xb is clear, nothing of priority 5 or more is queued
 * or running (func_0200e7f8) and func_0203e1c4 allows. When something of priority 5 or more is,
 * an actor in state 0x4f asks for state 0x51 instead. Whether state 0x78 was queued. */
int FieldActor_PlayerRequestState78(void)
{
    if (EventQueue_IsKind5Unfinished()) {
        return 0;
    }
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, 0xb)) {
        return 0;
    }
    if (FieldActor_QueuePriorityAbove(actor) >= 5) {
        if (actor->state == 0x4f) {
            FieldActor_RequestState51(actor, 0, 6, -1);
        }
        return 0;
    }
    if (!EventQueue_RequestKind9()) {
        return 0;
    }
    return FieldActor_RequestState78(actor, 5, -1);
}
CLEAN_AS(func_ov003_022198b0, FieldActor_PlayerRequestState78)

/* func_ov003_02219930: the actor of this console asks to turn towards a point (state 0x77,
 * func_02008dc0); whether it was queued. */
int FieldActor_PlayerFacePoint(const Vec3 *point)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    s16 yaw = Math_Atan2(sub32(point->x, actor->position.x), sub32(point->z, actor->position.z));
    return FieldActor_RequestState77(actor, (u16) yaw, 6, -1);
}
CLEAN_AS(func_ov003_02219930, FieldActor_PlayerFacePoint)

/* func_ov003_0221996c: asks for state 0x6d of kind `kind` + 2 (priority 7) for the actor of
 * this console, unless something of priority 5 or more is queued or running (func_0200e7f8) or
 * it is in state 0x78; once queued flag 0x1a is cleared, with func_02035638 (0x3f), when it was
 * set. Whether it was queued. */
int FieldActor_PlayerRequestState6D(int kind)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_QueuePriorityAbove(actor) >= 5) {
        return 0;
    }
    if (actor->state == 0x78) {
        return 0;
    }
    if (!FieldActor_RequestState6D(actor, (char) (u8) (kind + 2), 7, -1)) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, 0x1a)) {
        FieldActor_ClearFlag(actor, 0x1a);
        Music_DropMusic(0x3f);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221996c, FieldActor_PlayerRequestState6D)

/* func_ov003_022199d8: asks for state 0x6b (`which` 1) or 0x6c (2) for the actor of this
 * console; whether it was queued. */
int FieldActor_PlayerRequestState6BOr6C(int which)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    switch (which) {
        case 1:
            return FieldActor_RequestState6B(actor, 6, -1);
        case 2:
            return FieldActor_RequestState6C(actor, 6, -1);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov003_022199d8, FieldActor_PlayerRequestState6BOr6C)

/* func_ov003_02219a14: asks for state 0x6a at a point for the actor of this console; whether it
 * was queued. */
int FieldActor_PlayerRequestState6A(Vec3 *point)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    return (int) (uintptr_t) FieldActor_RequestState6A(actor, *point, 6, -1);
}
CLEAN_AS(func_ov003_02219a14, FieldActor_PlayerRequestState6A)

/* func_ov003_02219a40: asks for state 0x3b for the actor of this console; whether it was
 * queued. */
int FieldActor_PlayerRequestState3B(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_RequestState3BPlain(actor, 6, -1);
}
CLEAN_AS(func_ov003_02219a40, FieldActor_PlayerRequestState3B)

/* func_ov003_02219a64: the actor of this console goes to a point and yaw in state 0x39 of
 * `kind`: when func_0200fc90 says so through state 0x3d (or 0x3e) first, which goes on to 0x39
 * (the kind in bits 2-3 of its flags); otherwise directly, setting flag 1. Whether it was
 * queued. */
int FieldActor_PlayerRequestState39(u32 kind, int *x, int *z, int yaw)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_HeldToolNumber(actor)) {
        return FieldActor_RequestState3D(actor, 0x39, (int) ((kind & 0x3f) << 2), *x, *z, (s16) yaw, 6, -1);
    }
    FieldActor_SetFlag(actor, 1);
    return FieldActor_RequestState39(actor, (int) kind, *x, *z, (s16) yaw, 6, -1);
}
CLEAN_AS(func_ov003_02219a64, FieldActor_PlayerRequestState39)

/* func_ov003_02219ad0: the same for state 0x38 (a point and a yaw). */
int FieldActor_PlayerRequestState38(int *x, int *z, short *yaw)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    if (FieldActor_HeldToolNumber(actor)) {
        return FieldActor_RequestState3D(actor, 0x38, 0, *x, *z, *yaw, 6, -1);
    }
    FieldActor_SetFlag(actor, 1);
    return FieldActor_RequestState38(actor, *x, *z, *yaw, 6, -1);
}
CLEAN_AS(func_ov003_02219ad0, FieldActor_PlayerRequestState38)

/* func_ov003_02219b38: the actor of this console looks (state 0x8f with `flag`'s low byte as
 * LookArgs.track, going back to state 5 after it when it is in state 5 now) when that byte is
 * nonzero, else asks for state 0x57 in mode 1. Only the low byte of `flag` is read (the source
 * declares a 12-byte structure passed by value, of which the callers fill the first register).
 * Whether it was queued. */
int FieldActor_PlayerLook(int flag)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    u8 track = (u8) flag;
    if (track != 0) {
        return FieldActor_RequestLook(actor, &track, actor->state == 5, 6, -1);
    }
    return (int) (uintptr_t) FieldActor_RequestState57(actor, 1, 0, 0, 6, -1);
}
CLEAN_AS(func_ov003_02219b38, FieldActor_PlayerLook)

/* func_ov003_02219b90: asks for state 0x61 (kind 1) on the tile of a point with an item for the
 * actor of this console; whether it was queued. */
int FieldActor_PlayerRequestState61(const Vec3 *point, u16 *item)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) point);
    u32 tile[2] = {(u32) x, (u32) z};
    return (int) (uintptr_t) FieldActor_RequestState61(actor, 1, tile, *item, 6, -1);
}
CLEAN_AS(func_ov003_02219b90, FieldActor_PlayerRequestState61)

/* func_ov003_02219be0: the item the actor of this console shows: the insect of state 0x57 or the
 * fish of state 0x54 caught there (mode 0), or item 0x1549 in state 0x5f; ITEM_NONE otherwise.
 * QUIRK: an insect kind of 0x38 or more gives 0x12b0, a fish kind of 0x38 or more ITEM_NONE. */
u32 FieldActor_PlayerShownItem(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    u32 item = ITEM_NONE;
    if (actor == NULL) {
        return item;
    }
    switch (actor->state) {
        case 0x57:
            if (actor->work.s57.mode == 0) {
                u8 kind = actor->work.s57.kind;
                item = kind < 0x38 ? (u32) (INSECT_FIRST + kind) : INSECT_FIRST;
            }
            break;
        case 0x54:
            if (actor->work.s54.mode == 0 && actor->work.s54.kind < 0x38) {
                item = (u32) (FISH_FIRST + actor->work.s54.kind);
            }
            break;
        case 0x5f:
            if (actor->item == 0x1549) {
                item = actor->item;
            }
            break;
        default:
            break;
    }
    return item;
}
CLEAN_AS(func_ov003_02219be0, FieldActor_PlayerShownItem)

/* func_ov003_02219c80: whether the actor of this console holds something up and waits to put it
 * away (state 6, step 1). */
int FieldActor_PlayerShowing(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    return actor != NULL && actor->state == 6 && actor->work.s6.step == 1;
}
CLEAN_AS(func_ov003_02219c80, FieldActor_PlayerShowing)

/* func_ov003_02219cb4: whether the actor of this console strikes the tile of `point` this frame:
 * frame 5 of animation 0x67 or frame 8 of animation 0x44, on the tile ahead (func_0200fa8c). */
int FieldActor_PlayerStrikesTile(const Vec3 *point)
{
    FieldActor *actor = SessionPlayers_FieldActor(THIS_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    int frame = anim_frame(actor);
    int animation = actor->animation;
    if ((animation == 0x67 && frame == 5) || (animation == 0x44 && frame == 8)) {
        Vec3 ahead;
        FieldActor_TileAhead(&ahead, actor);
        return FieldActor_SameTile(point, &ahead);
    }
    return 0;
}
CLEAN_AS(func_ov003_02219cb4, FieldActor_PlayerStrikesTile)

/* func_ov003_02219d04: how many frames a player's actor has left before it acts on the tile of
 * `point` in state 0x49 (at frame 8) or 0x5d (at frame 5); 0 when it does not or is past it. */
int FieldActor_PlayerFramesToActOnTile(const Vec3 *point, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    int frame = anim_frame(actor);
    int left = 0;
    Vec3 at = {0, 0, 0};
    if (actor->state == 0x49) {
        AcreTile_TileCentre(&at, actor->work.s49.x, actor->work.s49.z);
        left = 8 - frame;
    } else if (actor->state == 0x5d) {
        AcreTile_TileCentre(&at, actor->work.s5d.x, actor->work.s5d.z);
        left = 5 - frame;
    }
    if (left > 0 && FieldActor_SameTile(point, &at)) {
        return left;
    }
    return 0;
}
CLEAN_AS(func_ov003_02219d04, FieldActor_PlayerFramesToActOnTile)

/* func_ov003_02219d8c: the same for state 0x5e and its point: frame 0x16 of animation 0x4e or
 * frame 9 of animation 0x4b. */
int FieldActor_PlayerFramesToState5E(const Vec3 *point, int player)
{
    FieldActor *actor = SessionPlayers_FieldActor(player);
    if (actor == NULL) {
        return 0;
    }
    int frame = anim_frame(actor);
    int left = 0;
    Vec3 at = {0, 0, 0};
    if (actor->state == 0x5e) {
        at = actor->work.s5e.point;
        if (actor->animation == 0x4e) {
            left = 0x16 - frame;
        } else if (actor->animation == 0x4b) {
            left = 9 - frame;
        }
    }
    if (left > 0 && FieldActor_SameTile(point, &at)) {
        return left;
    }
    return 0;
}
CLEAN_AS(func_ov003_02219d8c, FieldActor_PlayerFramesToState5E)

/* func_ov003_02219e14: whether two points are on the same tile. */
int FieldActor_SameTile(const Vec3 *a, const Vec3 *b)
{
    int bx = 0;
    int bz = 0;
    int ax = 0;
    int az = 0;
    Position_Tile(&bx, &bz, (const Position *) b);
    Position_Tile(&ax, &az, (const Position *) a);
    return bx == ax && bz == az;
}
CLEAN_AS(func_ov003_02219e14, FieldActor_SameTile)

/* func_ov003_02219e58: whether a player's actor has flag 9. */
int FieldActor_PlayerFlag9(int player)
{
    return PlayerActorOps_TestFlag(9, player);
}
CLEAN_AS(func_ov003_02219e58, FieldActor_PlayerFlag9)
