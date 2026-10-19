/* What the field actor's states and overlay 3 share (field_actor.h): the state requests, the
 * hooks of its message receiver, its flags, its sounds and footsteps, turning and easing it
 * towards a point, following the position another console reports for its actor, the sun level
 * sent to the session, and the targets on the map it acts on. */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/calendar.h"
#include "main/item_code.h"
#include "main/session.h"
#include "sound_emitter.h"
#include "acre_tile.h"
#include "actor_table.h"
#include "angle_sector.h"
#include "battery_warning.h"
#include "collision_map.h"
#include "control_mode_icon.h"
#include "date_time.h"
#include "effect_system.h"
#include "event_queue.h"
#include "frame_ctrl.h"
#include "game_variables.h"
#include "globe.h"
#include "ground_sound.h"
#include "held_item.h"
#include "item_info.h"
#include "layered_model.h"
#include "model_object.h"
#include "music_queue.h"
#include "name_texts.h"
#include "ov004/field_actor_room_states2.h"
#include "player_actor_ops.h"
#include "player_record.h"
#include "scene_claim.h"
#include "scene_exit.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session_players.h"
#include "talk_answers.h"
#include "talk_object.h"
#include "tile_requests.h"

static_assert(offsetof(FieldActor, flags) == 0x6ec, "flags");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, target) == 0x80c, "target");
static_assert(offsetof(FieldActor, unk_81C) == 0x81c, "talk progress");
static_assert(offsetof(FieldActor, unk_824) == 0x824, "eased point");
static_assert(offsetof(StateRequest, arg) == 8, "request arg");

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The scene: 0 outdoors (overlay 3), else indoors (overlay 4). */
extern u8 data_020e54a8;
/* The town map, NULL while there is none. */
extern void *data_021c80bc;
/* The object of the scene whose word at 0x248 a talk's end sets. */
extern u8 *data_021c526c;
/* The message shown when the player answered no (as ErrorMessage_EndTalk shows it). */
extern u8 data_021f43e8;
/* A copy of the actor's model matrix FieldActor_RebuildPose keeps. */
extern FieldActorBlock48 data_021cfe68;

/* Per-state bytes, indexed by the state. */
extern const u8 data_020c7ab4[]; /* FieldActor_StateGroup */
extern const u8 data_020c7a20[]; /* FieldActor_StateFlagA20 */
/* Per-tool values the target searches are given (FieldActor_FindTarget). */
extern const int data_020c7640[];
/* Distances ahead (20.12) for FieldActor_PointAhead. */
extern const fx32 data_020d7300;
extern const fx32 data_020c8094;

extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* No object on the point (func_02030890). */
#define NO_OBJECT (-1)

/* No target held (FieldActor.target, unk_810). */
#define NO_TARGET (-1)

/* FieldActor.unk_81C, the progress of a talk the actor opened: 15 and up is over. */
#define TALK_OVER 15

/* The word at 0x7d4 (the start of FieldActor.work) as a halfword. */
static u16 field_actor_support_work_halfword(const FieldActor *actor)
{
    return FIELD_ACTOR_FIELD(actor, u16, 0x7d4);
}

/* An arithmetic shift right, for negative values too. */
static int field_actor_support_shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The bit `bit` as the ARM shifts 1 left by a register: only the low byte of the count counts,
 * and 32 and more give 0. */
static u32 field_actor_support_flag_mask(int bit)
{
    u32 count = (u32) bit & 0xff;
    return count < 32 ? 1u << count : 0;
}

/* Whether an item code is nothing: for a code func_0204bcdc accepts, by comparing
 * func_0204bc64 of it with that of 0xfff1. */
static BOOL field_actor_support_item_is_nothing(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 nothing = ITEM_CODE_NONE;
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(&nothing);
    }
    return *item == ITEM_CODE_NONE;
}

/* Far and not drawn (Actor.cull_flags): then the actor plays no sound. */
static BOOL field_actor_support_is_silent(FieldActor *actor)
{
    u32 cull = FieldActor_Base(actor)->cull_flags;
    return (cull & ACTOR_CULL_FAR) != 0 && (cull & ACTOR_CULL_SKIP_DRAW) != 0;
}

/* The emitter that plays: 0x83c with flag 0x19, else 0x880. */
static SoundEmitter *field_actor_support_emitter(FieldActor *actor)
{
    int offset = FieldActor_TestFlag(actor, 0x19) ? FIELD_ACTOR_EMITTER_B : FIELD_ACTOR_EMITTER;
    return (SoundEmitter *) ((u8 *) actor + offset);
}

/* ---- State requests */

/* func_0200e90c: a request for `state` with its priority and argument (kept to 16 bits). */
void StateRequest_Set(StateRequest *request, int state, int priority, int arg)
{
    request->state = state;
    request->priority = priority;
    request->arg = (s16) arg;
}
CLEAN_AS(func_0200e90c, StateRequest_Set)

/* func_0200e914: an empty function the request's destructor runs. */
void StateRequest_DestructPart(void) {}
CLEAN_AS(func_0200e914, StateRequest_DestructPart)

/* func_0200e918: an empty function the request's constructor runs. */
void StateRequest_ConstructPart(void) {}
CLEAN_AS(func_0200e918, StateRequest_ConstructPart)

/* func_0200e91c: the request's destructor; the request back. */
int StateRequest_Destruct(StateRequest *request)
{
    StateRequest_DestructPart();
    return (int) (uintptr_t) request;
}
CLEAN_AS(func_0200e91c, StateRequest_Destruct)

/* func_0200e92c: the request's constructor; the request back. */
u32 StateRequest_Construct(StateRequest *request)
{
    StateRequest_ConstructPart();
    return (u32) (uintptr_t) request;
}
CLEAN_AS(func_0200e92c, StateRequest_Construct)

/* ---- Following another console's actor */

/* func_0200e93c: whether another console's actor walks towards the point (dx, dz) away, at the
 * square distance `distance2` (both from FX_MulFunc), its console reporting `yaw`: not nearer
 * than 0x108; from 0x2666 always; in between only when the direction is less than a quarter
 * turn from `yaw`. When it walks, the direction goes to `direction`. */
int FieldActor_ShouldWalkToward(FieldActor *actor, int dx, int dz, int distance2, s16 yaw, s16 *direction)
{
    (void) actor;
    if (distance2 < FX_MulFunc(0x108, 0x108)) {
        return 0;
    }
    s16 toward = Math_Atan2(dx, dz);
    int walks;
    if (distance2 >= FX_MulFunc(0x2666, 0x2666)) {
        walks = 1;
    } else {
        int diff = (s16) (toward - yaw);
        if (diff < 0) {
            diff = -diff;
        }
        walks = diff < 0x4000;
    }
    if (walks) {
        *direction = toward;
    }
    return walks;
}
CLEAN_AS(func_0200e93c, FieldActor_ShouldWalkToward)

/* func_0200e9a8: the scene, point (x and z) and yaw the session reports for the actor's player
 * (func_02096614, func_0209658c); 0, writing nothing, while either is missing. */
int FieldActor_ReportedPosition(FieldActor *actor, u8 *scene, int *x, int *z, s16 *yaw)
{
    u8 reported_scene;
    fx32 reported_x;
    fx32 reported_z;
    s16 reported_yaw;

    if (SessionPlayers_ScenePoint(&reported_scene, (int *) &reported_x, (int *) &reported_z, -1, actor->player) == 0) {
        return 0;
    }
    if (SessionPlayers_Yaw(&reported_yaw, -1, actor->player) == 0) {
        return 0;
    }
    *scene = reported_scene;
    *x = reported_x;
    *z = reported_z;
    *yaw = reported_yaw;
    return 1;
}
CLEAN_AS(func_0200e9a8, FieldActor_ReportedPosition)

/* func_0200ea0c: the state's group (1: states another console's actor follows as state 2). */
u8 FieldActor_StateGroup(FieldActor *actor, int state)
{
    (void) actor;
    return data_020c7ab4[state];
}
CLEAN_AS(func_0200ea0c, FieldActor_StateGroup)

/* ---- The message receiver's hooks, by the progress of the talk (FieldActor.unk_81C) */

/* func_0200ea18 (the receiver's slot 0x70): ends the talk (progress 15) with func_02035638 and
 * func_02035684, by its progress:
 *   10 and 11: 0x39, then (0xc, 6, 0xb), or (0xc, 0x23, 0x28) for 11;
 *   7:  the work's first halfword, then (5 for halfwords 0x3c and 0x3d, else 0xc) with times 6
 *       and 0xb, or 0x1b and 0x20 when an item is held, func_0200fc90 has no number for it and
 *       the actor is outdoors;
 *   5 and 8: in state 0x57 its work's halfword at 4 (kind 5 for 0x3b), in state 0x54 its first
 *       (kind 5 for 0x3a), in state 0x5f 0x39; then (that kind or 0xc, 0x14, 0x19). Progress 5
 *       stays; any other state does nothing;
 *   9:  in state 0x57 its work's halfword at 4 and (0xc, 0x24, 0x29), else the first halfword
 *       and (0xc, 6, 0xb);
 *   12: 0x42, then (0xc, 6, 0xb).
 * Other progresses are left alone. */
void FieldActor_TalkClosing(FieldActor *actor)
{
    int progress = actor->unk_81C;
    int start = 6;

    if (progress >= TALK_OVER) {
        return;
    }
    switch (progress) {
        case 11:
            start = 0x23;
            /* fall through */
        case 10:
            Music_DropMusic(0x39);
            Music_AddValue(0xc, start, start + 5);
            actor->unk_81C = TALK_OVER;
            break;
        case 7: {
            u16 value = field_actor_support_work_halfword(actor);
            u16 item;
            Music_DropMusic(value);
            FieldActor_RecordHeldItem(&item, actor);
            if (!field_actor_support_item_is_nothing(&item) && FieldActor_HeldToolNumber(actor) == 0 && data_020e54a8 == 0) {
                start += 0x15;
            }
            if (value == 0x3c || value == 0x3d) {
                Music_AddValue(5, start, start + 5);
            } else {
                Music_AddValue(0xc, start, start + 5);
            }
            actor->unk_81C = TALK_OVER;
            break;
        }
        case 5:
        case 8: {
            int kind = 0xc;
            int value;
            if (actor->state == 0x57) {
                value = actor->work.s57.unk_04;
                if (value == 0x3b) {
                    kind = 5;
                }
            } else if (actor->state == 0x54) {
                value = actor->work.s54.unk_00;
                if (value == 0x3a) {
                    kind = 5;
                }
            } else if (actor->state == 0x5f) {
                value = 0x39;
            } else {
                break;
            }
            Music_DropMusic(value);
            Music_AddValue(kind, 0x14, 0x19);
            if (actor->unk_81C != 5) {
                actor->unk_81C = TALK_OVER;
            }
            break;
        }
        case 9: {
            int value;
            if (actor->state == 0x57) {
                value = actor->work.s57.unk_04;
                start += 0x1e;
            } else {
                value = field_actor_support_work_halfword(actor);
            }
            Music_DropMusic(value);
            Music_AddValue(0xc, start, start + 5);
            actor->unk_81C = TALK_OVER;
            break;
        }
        case 12:
            Music_DropMusic(0x42);
            Music_AddValue(0xc, start, 0xb);
            actor->unk_81C = TALK_OVER;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200ea18, FieldActor_TalkClosing)

/* func_0200ebbc (the receiver's slot 0x18): after the player chose, in progress 0, 2, 3 or 4,
 * the message data_021f43e8 is shown; then choice 0 makes the progress 5, else 9 from 0 and 4,
 * 0xb from 2 and 15 from 3. */
void FieldActor_TalkChoice(FieldActor *actor)
{
    int progress = actor->unk_81C;

    if (progress != 0 && progress != 2 && progress != 3 && progress != 4) {
        return;
    }
    unsigned int choice = TalkAnswers_Picked(TalkObject_Answers((TalkObject *) actor->link));
    u8 message = data_021f43e8;
    TalkObject_SetMessage((TalkObject *) actor->link, &message, NULL);

    if (choice == 0) {
        actor->unk_81C = 5;
        return;
    }
    switch (actor->unk_81C) {
        case 0:
        case 4:
            actor->unk_81C = 9;
            break;
        case 2:
            actor->unk_81C = 0xb;
            break;
        default:
            actor->unk_81C = TALK_OVER;
            break;
    }
}
CLEAN_AS(func_0200ebbc, FieldActor_TalkChoice)

/* Shows message `number` of the actor's talk. */
static void field_actor_support_show(FieldActor *actor, u8 number)
{
    TalkObject_SetMessage((TalkObject *) actor->link, &number, NULL);
}

/* Puts the name of `item` into the talk's text slot 0 (kind 7). */
static void field_actor_support_name_item(FieldActor *actor, u16 item)
{
    u8 text[0x28];
    NameText_ConstructItem((NameText *) (void *) text, &item);
    TalkObject_SetValue((TalkObject *) actor->link, 0, (TextBase *) (void *) text, 7);
    NameText_Destruct((NameText *) (void *) text);
}

/* func_0200ec4c (the receiver's slot 0x14): the message for the talk's progress: 0x3d for 0,
 * 0x3e for 4, 3 for 2, 0x3c for 1 (then progress 9); for 5 and 6 the word at 0x248 of
 * data_021c526c becomes 0xb; for 13 message 0x3f with the insect of state 0x57's kind (item
 * 0x12b0 + kind) and for 14 with the fish of state 0x54's kind (0x12e8 + kind), then
 * progress 8 (for 14 set before the item is named). */
void FieldActor_TalkMessage(FieldActor *actor)
{
    switch (actor->unk_81C) {
        case 0:
            field_actor_support_show(actor, 0x3d);
            break;
        case 4:
            field_actor_support_show(actor, 0x3e);
            break;
        case 2:
            field_actor_support_show(actor, 3);
            break;
        case 1:
            field_actor_support_show(actor, 0x3c);
            actor->unk_81C = 9;
            break;
        case 5:
        case 6:
            *(int *) (data_021c526c + 0x248) = 0xb;
            break;
        case 13:
            field_actor_support_show(actor, 0x3f);
            field_actor_support_name_item(actor, (u16) (actor->work.s57.kind + 0x12b0));
            actor->unk_81C = 8;
            break;
        case 14:
            field_actor_support_show(actor, 0x3f);
            actor->unk_81C = 8;
            field_actor_support_name_item(actor, (u16) (actor->work.s54.kind + 0x12e8));
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200ec4c, FieldActor_TalkMessage)

/* func_0200eda4 (the receiver's slot 0x10): nothing to do. */
void FieldActor_TalkIgnore(FieldActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_0200eda4, FieldActor_TalkIgnore)

/* func_0200edb0: in scenes 0xc, 0xd, 0xe, 0x2e and 0x2f (func_020b65b8), whether a taken slot
 * of the session has no yaw reported for it yet (func_0209658c). */
int FieldActor_AnyPlayerUnreported(FieldActor *actor)
{
    (void) actor;
    u8 scene = SceneQuery_Previous();
    if (scene != 0xc && scene != 0xd && scene != 0xe && scene != 0x2e && scene != 0x2f) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    for (int slot = 0; slot < 4; slot++) {
        if (Session_IsSlotTaken(session, slot)) {
            s16 yaw;
            if (SessionPlayers_Yaw(&yaw, -1, slot) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0200edb0, FieldActor_AnyPlayerUnreported)

/* func_0200ee0c: whether this console's slot is taken in the session and the actor's player is
 * not player 0. */
int FieldActor_LinkedNotPlayer0(FieldActor *actor)
{
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return 0;
    }
    return actor->player != 0;
}
CLEAN_AS(func_0200ee0c, FieldActor_LinkedNotPlayer0)

/* ---- The body */

/* func_0200ee40: the slope's angle at the position (the pitch, from the pivot), the model matrix
 * (kept at 0x298 and in data_021cfe68), and the body updated with joint 0xb's matrix at 0x698. */
void FieldActor_RebuildPose(FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    Mtx43 model;

    base->pitch = (u16) Globe_BendFar(&base->pivot, &base->position);
    Actor_ModelMatrix(base, &model);
    memcpy(&actor->unk_298, &model, sizeof(model));
    data_021cfe68 = actor->unk_298;
    ModelObject_SetAlpha((ModelObject *) (void *) actor->unk_234, 0);
    LayeredModel_DrawA((LayeredModel *) (void *) actor->unk_234, 0);
    ModelObject_JointMatrix((ModelObject *) (void *) actor->unk_234, (Mtx43 *) &actor->unk_698, 0xb);
}
CLEAN_AS(func_0200ee40, FieldActor_RebuildPose)

/* func_0200eebc: the held item's pose for the tool held (FieldActor_HeldTool): 9 for tool 4,
 * 0x13 for 3, 0x23 for 10, 0x21 for 6; nothing for the others. */
void FieldActor_PoseHeldTool(FieldActor *actor)
{
    switch (FieldActor_HeldTool(actor)) {
        case 4:
            HeldItem_Act(actor->held, 0, 9, 0);
            break;
        case 3:
            HeldItem_Act(actor->held, 0x13, 3, 0);
            break;
        case 10:
            HeldItem_Act(actor->held, 0x23, 3, 0);
            break;
        case 6:
            HeldItem_Act(actor->held, 0x21, 3, 0);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200eebc, FieldActor_PoseHeldTool)

/* func_0200ef1c: FieldActor_EnterContact (the actor's checks) with the position moved aside for a
 * moment. When the object at 0x174 met (0x1b0) a player's actor (kind 0x15 at 0x182, its player
 * at 0x183) that is this console's and stands (state 2 for player 4, func_020960f8), and the
 * point reported for this actor lies in the same direction (within 0x400) and not nearer than
 * that player's start position, the checks run data_020d7300's distance aside of the actor, a
 * quarter turn to the left of that direction when this actor's player number is not below the
 * other's, else to the right. The position is put back after.
 * REQUIRES: the player met has an actor (func_02095794 is not NULL). */
void FieldActor_RunChecksAside(FieldActor *actor)
{
    Vec3 saved = actor->position;

    if (FIELD_ACTOR_FIELD(actor, u8, 0x1b0) != 0 && FIELD_ACTOR_FIELD(actor, u8, 0x182) == 0x15) {
        int other = FIELD_ACTOR_FIELD(actor, u8, 0x183);
        u8 scene;
        Vec3 reported;
        if (Session_IsLocalPlayer(data_020ccf94, other) && PlayerActorOps_InState(2, 4) &&
            SessionPlayers_ScenePoint(&scene, (int *) &reported.x, (int *) &reported.z, -1, actor->player)) {
            const Vec3 *other_start = PlayerActorOps_StartPosition(other);
            Vec3 here = actor->position;
            int to_other = Math_Atan2(other_start->x - here.x, other_start->z - here.z);
            u16 to_reported = (u16) Math_Atan2(reported.x - here.x, reported.z - here.z);
            if (Math_AbsDiff16(to_other, (s16) to_reported) < 0x400) {
                fx32 other_distance = Vec_DistanceXZ(&here, other_start);
                if (other_distance <= Vec_DistanceXZ(&here, &reported)) {
                    u16 aside = actor->player >= other ? (u16) (to_reported + 0x4000) : (u16) (to_reported - 0x4000);
                    Vec3 moved;
                    FieldActor_PointAhead(&moved, actor, &here, &aside, &data_020d7300);
                    actor->position = moved;
                }
            }
        }
    }
    FieldActor_EnterContact(actor);
    actor->position = saved;
}
CLEAN_AS(func_0200ef1c, FieldActor_RunChecksAside)

/* func_0200f05c: the per-state byte at data_020c7a20, except that state 0x1e with the work's
 * second byte 0 and state 0x4f give 1 while the request queue is empty (its count at 0xc7c). */
int FieldActor_StateFlagA20(FieldActor *actor, int state)
{
    u32 queued = FIELD_ACTOR_FIELD(actor, u32, 0xc7c);
    if (state == 0x1e) {
        if (actor->work.bytes[1] == 0 && queued == 0) {
            return 1;
        }
    } else if (state == 0x4f) {
        if (queued == 0) {
            return 1;
        }
    }
    return data_020c7a20[state];
}
CLEAN_AS(func_0200f05c, FieldActor_StateFlagA20)

/* func_0200f098: while flag 0x15 is set the head turns (FieldActor_TurnAngle, by 0x400) towards the
 * pitch and yaw at 0x460 and 0x462; once all four are 0 the flag is cleared. */
void FieldActor_TurnHeadBack(FieldActor *actor)
{
    if (!FieldActor_TestFlag(actor, 0x15)) {
        return;
    }
    FieldActor_TurnAngle(&actor->head_pitch, FIELD_ACTOR_FIELD(actor, s16, 0x460), 0x400, 0x1770000, 0xc0000);
    FieldActor_TurnAngle(&actor->head_yaw, FIELD_ACTOR_FIELD(actor, s16, 0x462), 0x400, 0x1770000, 0xc0000);
    if (FIELD_ACTOR_FIELD(actor, s16, 0x460) == 0 && FIELD_ACTOR_FIELD(actor, s16, 0x462) == 0 && actor->head_pitch == 0 &&
        actor->head_yaw == 0) {
        FieldActor_ClearFlag(actor, 0x15);
    }
}
CLEAN_AS(func_0200f098, FieldActor_TurnHeadBack)

/* ---- Messages to the session */

/* func_0200f11c: while linked, the sun level (FieldActor_RecordSunLevel, a byte) goes to the session as
 * message 0x2e. */
void FieldActor_SendSunLevel(FieldActor *actor)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 level = (u8) FieldActor_RecordSunLevel(actor);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &level, 1);
    Session_EndMessage(session, 0x2e, 4);
}
CLEAN_AS(func_0200f11c, FieldActor_SendSunLevel)

/* func_0200f164: while linked, message 0x2d with a zero byte. */
void FieldActor_SendNoItem(FieldActor *actor)
{
    (void) actor;
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 zero = 0;
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &zero, 1);
    Session_EndMessage(session, 0x2d, 4);
}
CLEAN_AS(func_0200f164, FieldActor_SendNoItem)

/* func_0200f1a4: while linked, message 0x2b with the item packed (func_02096484) and its kind:
 * 3 bytes. */
void FieldActor_SendItem(FieldActor *actor, int kind, int item)
{
    (void) actor;
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 bytes[4];
    SessionPlayers_WriteItemKind(bytes, item, kind);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, bytes, 3);
    Session_EndMessage(session, 0x2b, 4);
}
CLEAN_AS(func_0200f1a4, FieldActor_SendItem)

/* func_0200f1ec: joint 0xb's translation (the last row of the matrix at 0x698) on the curved
 * ground, into `out`; 0, writing nothing, while it is all 0. */
int FieldActor_JointBPoint(FieldActor *actor, Vec3 *out)
{
    const Vec3 *joint = &FIELD_ACTOR_FIELD(actor, Vec3, 0x6bc);
    if (joint->x == 0 && joint->y == 0 && joint->z == 0) {
        return 0;
    }
    *out = *joint;
    Globe_Unbend(out, out);
    return 1;
}
CLEAN_AS(func_0200f1ec, FieldActor_JointBPoint)

/* func_0200f234: the aim mode (FieldActor.aim_mode) from the setting func_0208ffac and
 * func_0208ff98 read: 1, 2, else 0. */
void FieldActor_TakeAimMode(FieldActor *actor)
{
    if (ControlModeIcon_IsButtons()) {
        actor->aim_mode = 1;
    } else if (ControlModeIcon_IsTouch()) {
        actor->aim_mode = 2;
    } else {
        actor->aim_mode = 0;
    }
}
CLEAN_AS(func_0200f234, FieldActor_TakeAimMode)

/* ---- Flags (FieldActor.flags) */

/* func_0200f268 */
void FieldActor_ClearFlag(FieldActor *actor, int bit)
{
    actor->flags &= ~field_actor_support_flag_mask(bit);
}
CLEAN_AS(func_0200f268, FieldActor_ClearFlag)

/* func_0200f27c: the flags back. */
u32 *FieldActor_SetFlag(FieldActor *actor, int bit)
{
    actor->flags |= field_actor_support_flag_mask(bit);
    return &actor->flags;
}
CLEAN_AS(func_0200f27c, FieldActor_SetFlag)

/* func_0200f290: the flag's bit, in place (nonzero when set). */
int FieldActor_TestFlag(FieldActor *actor, int bit)
{
    return (int) (actor->flags & field_actor_support_flag_mask(bit));
}
CLEAN_AS(func_0200f290, FieldActor_TestFlag)

/* ---- Sounds */

/* func_0200f2a0: unless far and not drawn, sound `number` plays (SoundEmitter_PlayEx, 0x7f)
 * and the emitters' point becomes `at`. */
void FieldActor_PlaySoundAt(FieldActor *actor, int number, const Vec3 *at)
{
    if (field_actor_support_is_silent(actor)) {
        return;
    }
    SoundEmitter_PlayEx(field_actor_support_emitter(actor), number, 0x7f, 0);
    FIELD_ACTOR_SOUND_POINT(actor).x = at->x;
    FIELD_ACTOR_SOUND_POINT(actor).y = at->y;
    FIELD_ACTOR_SOUND_POINT(actor).z = at->z;
}
CLEAN_AS(func_0200f2a0, FieldActor_PlaySoundAt)

/* func_0200f328: unless far and not drawn (then 1), sound `number` plays (SoundEmitter_PlayB,
 * 0x7f) and its answer is returned. */
int FieldActor_PlaySound(FieldActor *actor, int number)
{
    if (field_actor_support_is_silent(actor)) {
        return 1;
    }
    return SoundEmitter_PlayB(field_actor_support_emitter(actor), number, 0x7f, 0);
}
CLEAN_AS(func_0200f328, FieldActor_PlaySound)

/* ---- Small moves */

/* Moves the position by `step` along the axis nearest the yaw (func_02064558: 0 is +Z, 1 +X,
 * 2 -Z, 3 -X). */
static void field_actor_support_nudge(FieldActor *actor, int step)
{
    switch (AngleSector_Four(actor->yaw)) {
        case 2:
            actor->position.z -= step;
            break;
        case 0:
            actor->position.z += step;
            break;
        case 3:
            actor->position.x -= step;
            break;
        case 1:
            actor->position.x += step;
            break;
        default:
            break;
    }
}

/* func_0200f394: the position moves along the facing axis by the player's number (0x800), which
 * keeps actors that start at one point apart.
 * QUIRK: the player number is used as a distance (at most 4/4096 of a unit). */
void FieldActor_NudgeByPlayer(FieldActor *actor)
{
    field_actor_support_nudge(actor, actor->player);
}
CLEAN_AS(func_0200f394, FieldActor_NudgeByPlayer)

/* func_0200f3e8: the position moves along the facing axis by 1. */
void FieldActor_NudgeOne(FieldActor *actor)
{
    field_actor_support_nudge(actor, 1);
}
CLEAN_AS(func_0200f3e8, FieldActor_NudgeOne)

/* func_0200f434: another console's actor heading for `point`: with nothing reported for it
 * here (FieldActor_ReportedPlace) 1. Its goal is the reported point and yaw, or, when that is
 * 0x4000 or more from `point`, the point 0x2000 short of `point` on the line from the actor,
 * facing along it. Within 0x200 of the goal and 0x100 of its yaw: 1. From 0xe000 away the
 * actor is put at the goal (and its position at the frame's start) with that yaw: 1. Else 0. */
int FieldActor_FollowReportedTo(FieldActor *actor, const Vec3 *point)
{
    Vec3 *position = &actor->position;
    Vec3 goal;
    s16 yaw;

    if (FieldActor_ReportedPlace(actor, &goal, &yaw) == 0) {
        return 1;
    }
    if (Vec_DistanceXZ(&goal, point) >= 0x4000) {
        yaw = Math_Atan2(point->x - position->x, point->z - position->z);
        int index = ((u16) yaw >> 4) * 2;
        goal.x = point->x - FX_MulFunc(0x2000, FX_SinCosTable_[index]);
        goal.z = point->z - FX_MulFunc(0x2000, FX_SinCosTable_[index + 1]);
    } else {
        yaw = actor->yaw;
    }
    if (Vec_DistanceXZ(position, &goal) <= 0x200 && Math_AbsDiff16(actor->yaw, yaw) < 0x100) {
        return 1;
    }
    if (Vec_DistanceXZ(position, &goal) >= 0xe000) {
        FieldActor_Base(actor)->last_position = goal;
        *position = FieldActor_Base(actor)->last_position;
        actor->yaw = yaw;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0200f434, FieldActor_FollowReportedTo)

/* func_0200f530: FieldActor_FollowReportedTo the point of the tile (x, z) (func_0204f794). */
int FieldActor_FollowReportedToTile(FieldActor *actor, const int *tile)
{
    Vec3 point;
    AcreTile_TileCentre(&point, (u32) tile[0], (u32) tile[1]);
    return FieldActor_FollowReportedTo(actor, &point);
}
CLEAN_AS(func_0200f530, FieldActor_FollowReportedToTile)

/* func_0200f554: another console's actor goes to the point and yaw reported for it here
 * (FieldActor_ReportedPlace): 1 when nothing is reported or it is there already; from 0xe000
 * away it is put there (and its position at the frame's start) with that yaw, else it eases
 * towards them (FieldActor_EaseToPose); 0 in both cases. */
int FieldActor_FollowReported(FieldActor *actor)
{
    Vec3 goal;
    s16 yaw;

    if (FieldActor_ReportedPlace(actor, &goal, &yaw) == 0) {
        return 1;
    }
    Vec3 *position = &actor->position;
    if (position->x == goal.x && position->z == goal.z && yaw == actor->yaw) {
        return 1;
    }
    if (Vec_DistanceXZ(position, &goal) >= 0xe000) {
        FieldActor_Base(actor)->last_position = goal;
        *position = FieldActor_Base(actor)->last_position;
        actor->yaw = yaw;
        return 0;
    }
    FieldActor_EaseToPose(actor, goal.x, goal.z, yaw);
    return 0;
}
CLEAN_AS(func_0200f554, FieldActor_FollowReported)

/* func_0200f5e4: for another console's actor not held by flag 0x10, the point (at the actor's
 * height) and yaw its console reports, when it reports this scene. 0 otherwise; the height is
 * written whenever the report is asked for. */
int FieldActor_ReportedPlace(FieldActor *actor, Vec3 *point, s16 *yaw)
{
    u8 scene;
    int x;
    int z;

    if (Session_IsLocalPlayer(data_020ccf94, actor->player)) {
        return 0;
    }
    if (FieldActor_TestFlag(actor, 0x10)) {
        return 0;
    }
    point->y = actor->position.y;
    if (FieldActor_ReportedPosition(actor, &scene, &x, &z, yaw) == 0) {
        return 0;
    }
    point->x = x;
    point->z = z;
    return scene == SceneQuery_Current();
}
CLEAN_AS(func_0200f5e4, FieldActor_ReportedPlace)

/* func_0200f650: the point at 0x824 eases (Approach_EaseS32MinMax: 0x800, at most 0x2000, at
 * least 0x333 a step) towards FieldActor_JointBOffsetPoint at `scale`. */
void FieldActor_EasePoint824(FieldActor *actor, fx32 scale)
{
    Vec3 target;
    FieldActor_JointBOffsetPoint(&target, actor, &scale);
    Approach_EaseS32MinMax((int *) &actor->unk_824.x, target.x, 0x800, 0x2000, 0x333);
    Approach_EaseS32MinMax((int *) &actor->unk_824.y, target.y, 0x800, 0x2000, 0x333);
    Approach_EaseS32MinMax((int *) &actor->unk_824.z, target.z, 0x800, 0x2000, 0x333);
}
CLEAN_AS(func_0200f650, FieldActor_EasePoint824)

/* func_0200f6bc: the point (0.5, -0.25, 0) times `*scale` in joint 0xb's frame (the matrix at
 * 0x698), on the curved ground (func_0203f7d0). */
void FieldActor_JointBOffsetPoint(Vec3 *out, FieldActor *actor, const fx32 *scale)
{
    Mtx43 joint;
    memcpy(&joint, &actor->unk_698, sizeof(joint));
    Vec3 translation = {joint.m[3][0], joint.m[3][1], joint.m[3][2]};
    joint.m[3][0] = 0;
    joint.m[3][1] = 0;
    joint.m[3][2] = 0;

    Vec3 offset;
    offset.x = FX_MulFunc(0x800, *scale);
    offset.y = FX_MulFunc(-0x400, *scale);
    offset.z = 0;
    Vec3 turned;
    MTX_MultVec43(&offset, &joint, &turned);

    Vec3 point = {translation.x + turned.x, translation.y + turned.y, translation.z + turned.z};
    Globe_Unbend(out, &point);
}
CLEAN_AS(func_0200f6bc, FieldActor_JointBOffsetPoint)

/* func_0200f748: for this console's actor, a low battery (func_0202f188) asks for state 0x84
 * (kind 0, priority 6) and a closed lid for state 0x83 (priority 1); whether one was asked for.
 * HW: reads the word the ARM7 keeps in the shared area (NitroSDK's PAD_DetectFold). */
int FieldActor_CheckBatteryAndLid(FieldActor *actor)
{
    if (!Session_IsLocalPlayer(data_020ccf94, actor->player)) {
        return 0;
    }
    if (BatteryWarning_IsLow()) {
        FieldActor_RequestState84(actor, 0, 6, -1);
        return 1;
    }
    u16 buttons = *(const volatile u16 *) 0x027fffa8;
    if ((buttons & 0x8000) != 0) {
        FieldActor_RequestState83(actor, 1, -1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0200f748, FieldActor_CheckBatteryAndLid)

/* ---- The sun level's date (FieldActor_UpdateSunLevel, overlay 3) */

/* The fields of a date packed into 16 bits: year (7 bits), month (4 bits) and day (5 bits). */
#define PACKED_YEAR(date) ((date) & 0x7f)
#define PACKED_MONTH(date) (((date) >> 7) & 0xf)
#define PACKED_DAY(date) (((date) >> 11) & 0x1f)

/* func_0200f7ac: the packed date goes into the player's record (func_02099794); the halfword
 * func_0209d358(0, 0x50) becomes the sun level plus the month times 1000 plus the day times 10;
 * unless FieldActor_LinkedNotPlayer0, the date is also kept at func_0209627c. */
void FieldActor_StoreSunDate(FieldActor *actor, int record, const u16 *date)
{
    PlayerRecord_SetSunDate((u8 *) (uintptr_t) record, (PlayerRecordSunDate){*date});
    u16 *summary = GameVariables_Slot(0, 0x50);
    *summary = (u16) (FieldActor_RecordSunLevel(actor) + PACKED_MONTH(*date) * 1000 + PACKED_DAY(*date) * 10);
    if (FieldActor_LinkedNotPlayer0(actor) == 0) {
        *SessionPlayers_SunDate() = *date;
    }
}
CLEAN_AS(func_0200f7ac, FieldActor_StoreSunDate)

/* func_0200f814: the clock's date and time into `now` (func_0209e474), a copy of it with the
 * day, month and year of the date in the player's record (the halfword func_020997a8 reads)
 * into `stored`, and their order (func_0209e3ac, fields 0x3f): -1, 0 or 1. */
int FieldActor_CompareSunDate(FieldActor *actor, DateTime *now, DateTime *stored)
{
    u16 date = (u16) PlayerRecord_SunDate(FieldActor_Record(actor));
    DateTime_Now(now);
    MI_CpuCopy8(now, stored, 8);
    stored->year = (u8) PACKED_YEAR(date);
    stored->month = (u8) PACKED_MONTH(date);
    stored->day = (u8) PACKED_DAY(date);
    return DateTime_Compare(now, stored, 0x3f);
}
CLEAN_AS(func_0200f814, FieldActor_CompareSunDate)

/* func_0200f86c: FieldActor_CompareSunDate with both dates zeroed first. */
int FieldActor_SunDatePassed(FieldActor *actor)
{
    DateTime now = {0};
    DateTime stored = {0};
    return FieldActor_CompareSunDate(actor, &now, &stored);
}
CLEAN_AS(func_0200f86c, FieldActor_SunDatePassed)

/* ---- Footsteps */

/* func_0200f888: with flag 0xa, unless far and not drawn, the footstep sound for the ground
 * between joints 7 and 4 (func_020b1cb0) plays, alternating (SoundEmitter_PlayAlternating),
 * marked as running in animation 2. */
void FieldActor_PlayFootstep(FieldActor *actor)
{
    if (field_actor_support_is_silent(actor)) {
        return;
    }
    if (!FieldActor_TestFlag(actor, 0xa)) {
        return;
    }
    u32 running = actor->animation == 2;
    const Vec3 *a = &FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7);
    const Vec3 *b = &FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4);
    Vec3 between;
    between.x = field_actor_support_shift_right(a->x + b->x, 1);
    between.y = field_actor_support_shift_right(a->y + b->y, 1);
    between.z = field_actor_support_shift_right(a->z + b->z, 1);

    SoundEmitter *emitter = field_actor_support_emitter(actor);
    int sound = GroundSound_AtPoint(&between);
    SoundEmitter_PlayAlternating(emitter, (u32) sound, running);
}
CLEAN_AS(func_0200f888, FieldActor_PlayFootstep)

/* func_0200f95c: at frames 1 and 9 of the body's animation a foot lands: at joint 7's point for
 * frame 9, else joint 4's, at the actor's height, effect 0x27 facing the yaw (and, running in
 * animation 2, effect 0 facing back) and the footstep sound. */
void FieldActor_Footfall(FieldActor *actor)
{
    if (!FrameCtrl_Passed(&actor->anim, 1) && !FrameCtrl_Passed(&actor->anim, 9)) {
        return;
    }
    s16 ahead = actor->yaw;
    s16 back = (s16) (ahead + 0x8000);
    Vec3 at;
    if (FrameCtrl_Passed(&actor->anim, 9)) {
        at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7);
    } else {
        at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4);
    }
    at.y = actor->position.y;
    if (actor->animation == 2) {
        EffectSystem_StartKind(0, &at, &back, 0);
    }
    EffectSystem_StartKind(0x27, &at, &ahead, 0);
    FieldActor_PlayFootstep(actor);
}
CLEAN_AS(func_0200f95c, FieldActor_Footfall)

/* ---- Points ahead and turning */

/* func_0200fa1c: `from` moved `*distance` along `*yaw` (sine on X, cosine on Z). */
void FieldActor_PointAhead(Vec3 *out, FieldActor *actor, const Vec3 *from, const u16 *yaw, const fx32 *distance)
{
    (void) actor;
    out->x = from->x;
    out->y = from->y;
    out->z = from->z;
    int index = (*yaw >> 4) * 2;
    fx32 along_z = FX_MulFunc(FX_SinCosTable_[index + 1], *distance);
    fx32 along_x = FX_MulFunc(FX_SinCosTable_[index], *distance);
    out->x += along_x;
    out->z += along_z;
}
CLEAN_AS(func_0200fa1c, FieldActor_PointAhead)

/* func_0200fa6c: the point data_020c8094 ahead of the actor along its yaw. */
void FieldActor_PointAheadOfSelf(Vec3 *out, FieldActor *actor)
{
    FieldActor_PointAhead(out, actor, &actor->position, (const u16 *) &actor->yaw, &data_020c8094);
}
CLEAN_AS(func_0200fa6c, FieldActor_PointAheadOfSelf)

/* func_0200fa8c: the point of the tile ahead of the actor (func_0204f7e0). */
void FieldActor_TileAhead(Vec3 *out, FieldActor *actor)
{
    Vec3 ahead;
    FieldActor_PointAheadOfSelf(&ahead, actor);
    AcreTile_SnapToTileCentre(out, &ahead);
}
CLEAN_AS(func_0200fa8c, FieldActor_TileAhead)

/* Turns the body towards `target` at `rate` (FieldActor_TurnAngle); whether it is there. */
static int field_actor_support_turn_to(FieldActor *actor, int target, int rate)
{
    s16 yaw = actor->yaw;
    int arrived = FieldActor_TurnAngle(&yaw, target, rate, 0x1770000, 0xc0000) == 0;
    FieldActor_SetYaw(actor, &yaw);
    return arrived;
}

/* func_0200faa8: the body turns towards yaw 0x8000 at `rate`; whether it is there. */
int FieldActor_TurnToHalfTurn(FieldActor *actor, int rate)
{
    return field_actor_support_turn_to(actor, -0x8000, rate);
}
CLEAN_AS(func_0200faa8, FieldActor_TurnToHalfTurn)

/* func_0200faf0: the body turns towards yaw 0 at `rate`; whether it is there. */
int FieldActor_TurnToZero(FieldActor *actor, int rate)
{
    return field_actor_support_turn_to(actor, 0, rate);
}
CLEAN_AS(func_0200faf0, FieldActor_TurnToZero)

/* func_0200fb34: the body turns towards `yaw` (FieldActor_TurnAngleStep). */
void FieldActor_TurnTowards(FieldActor *actor, int yaw)
{
    s16 turned = actor->yaw;
    FieldActor_TurnAngleStep(&turned, yaw);
    FieldActor_SetYaw(actor, &turned);
}
CLEAN_AS(func_0200fb34, FieldActor_TurnTowards)

/* func_0200fb58: the position eases towards (x, z) (FieldActor_EaseValue). */
void FieldActor_EaseToXZ(FieldActor *actor, int x, int z)
{
    FieldActor_EaseValue(&actor->position.x, x);
    FieldActor_EaseValue(&actor->position.z, z);
}
CLEAN_AS(func_0200fb58, FieldActor_EaseToXZ)

/* func_0200fb7c: the position eases towards (x, z) (FieldActor_EaseValueBy: 0xe66 of the way, at most
 * 0x4cd, the rest when within 0x31) and the body turns towards `yaw`. */
void FieldActor_EaseToPose(FieldActor *actor, int x, int z, int yaw)
{
    FieldActor_EaseValueBy(&actor->position.x, x, 0x0e66, 0x04cd, 0x31);
    FieldActor_EaseValueBy(&actor->position.z, z, 0x0e66, 0x04cd, 0x31);
    FieldActor_TurnTowards(actor, yaw);
}
CLEAN_AS(func_0200fb7c, FieldActor_EaseToPose)

/* func_0200fbc4: FieldActor_EaseToXZ, then FieldActor_TurnTowards. */
void FieldActor_MoveToPose(FieldActor *actor, int x, int z, int yaw)
{
    FieldActor_EaseToXZ(actor, x, z);
    FieldActor_TurnTowards(actor, yaw);
}
CLEAN_AS(func_0200fbc4, FieldActor_MoveToPose)

/* ---- The held tool */

/* func_0200fbe0: the kind of tool held, from FieldActor_HeldToolNumber n (item 0x1368 + n):
 * 0 for none, 1 for 0x1369-0x136a, 2 to 0x1373, 3 to 0x1375, 4 to 0x1377, 5 to 0x1379, 6 to
 * 0x137b, 7 for 0x137c, 8 for 0x137d, 9 to 0x137f, 10 to 0x13a7, else 0.
 * QUIRK: the item is kept to 16 bits. */
int FieldActor_HeldTool(FieldActor *actor)
{
    int number = FieldActor_HeldToolNumber(actor);
    if (number <= 0) {
        return 0;
    }
    u16 item = (u16) (number + 0x1368);
    if (item <= 0x136a) {
        return 1;
    }
    if (item <= 0x1373) {
        return 2;
    }
    if (item <= 0x1375) {
        return 3;
    }
    if (item <= 0x1377) {
        return 4;
    }
    if (item <= 0x1379) {
        return 5;
    }
    if (item <= 0x137b) {
        return 6;
    }
    if (item == 0x137c) {
        return 7;
    }
    if (item == 0x137d) {
        return 8;
    }
    if (item <= 0x137f) {
        return 9;
    }
    if (item <= 0x13a7) {
        return 10;
    }
    return 0;
}
CLEAN_AS(func_0200fbe0, FieldActor_HeldTool)

/* func_0200fc90: with flag 0 and an item held (FieldActor_RecordHeldItem), one more than func_02062148 gives
 * for it; else 0. */
int FieldActor_HeldToolNumber(FieldActor *actor)
{
    u16 item;
    FieldActor_RecordHeldItem(&item, actor);
    if (FieldActor_TestFlag(actor, 0) && !field_actor_support_item_is_nothing(&item)) {
        return (int) (ItemInfo_HeldModelNumber(&item) + 1);
    }
    return 0;
}
CLEAN_AS(func_0200fc90, FieldActor_HeldToolNumber)

/* ---- Targets on the map */

/* func_0200fd04: acts on the target's kind (FieldActor_TargetKind) at the tile of `point`:
 * kinds 3, 4, 0x15 and 0x16 ask for state 0x18 (or, with `overlay4`, overlay 4's
 * func_ov004_0222ac24), kind 5 for state 0x16, kind 0x14 for state 0x66, all at priority 6;
 * whether it acted. */
int FieldActor_ActOnTarget(FieldActor *actor, const Vec3 *point, int overlay4)
{
    int kind = FieldActor_TargetKind(actor);
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) point);

    switch (kind) {
        case 3:
        case 4:
        case 0x15:
        case 0x16:
            if (overlay4) {
                FieldActorRoomStates2_RequestTakeItem(actor, tile, -2, 6, -1);
            } else {
                FieldActor_RequestState18(actor, tile, -1, 6, -1);
            }
            return 1;
        case 5:
            FieldActor_RequestState16(actor, tile, 6, -1);
            return 1;
        case 0x14:
            FieldActor_RequestState66(actor, tile, 0, 6, -1);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_0200fd04, FieldActor_ActOnTarget)

/* func_0200fdd0: with no target held, finds one on the map at the tile (x, z): the item there
 * (func_0204f5e0, its acre and the place in it) goes to 0x822 and `item` (0xfff1 and 2 when
 * there is no map entry); then func_02043d84 with `a` and `b` gives the target (0 when none);
 * FieldActor_PollTarget's answer is kept at 0x818 and gives 1 for 0, 0 for 2, else 3. With a
 * target held: 1. */
int FieldActor_FindMapTarget(FieldActor *actor, const int *tile, int a, int b)
{
    if (actor->target != NO_TARGET) {
        return 1;
    }
    int x = tile[0];
    int z = tile[1];
    u16 *on_map = AcreTile_ItemInAcre(data_021c80bc, field_actor_support_shift_right(x, 4),
                                      field_actor_support_shift_right(z, 4), x & 0xf, z & 0xf, 0);
    if (on_map == NULL) {
        actor->unk_822 = ITEM_CODE_NONE;
        actor->item = actor->unk_822;
        return 2;
    }
    actor->unk_822 = *on_map;
    actor->item = actor->unk_822;

    int at[2] = {tile[0], tile[1]};
    actor->target = TileRequests_AskOpFor(actor->player, (const TileRequestTile *) at, a, b, ITEM_CODE_NONE);
    if (actor->target == NO_TARGET) {
        return 0;
    }
    actor->unk_818 = FieldActor_PollTarget(actor);
    switch (actor->unk_818) {
        case 0:
            return 1;
        case 2:
            return 0;
        default:
            return 3;
    }
}
CLEAN_AS(func_0200fdd0, FieldActor_FindMapTarget)

/* func_0200fea0: the target's answer (func_020436a8; 0 with none held). On 1 or 2 its kind is
 * kept at 0x814 and it is released (func_020431b8); 0x814 is 0 otherwise. */
int FieldActor_PollTarget(FieldActor *actor)
{
    int answer = 0;
    actor->unk_814 = 0;
    if (actor->target != NO_TARGET) {
        answer = TileRequests_Answer(actor->target);
        if (answer == 1 || answer == 2) {
            actor->unk_814 = FieldActor_TargetKind(actor);
            TileRequests_Release(actor->target);
            actor->target = NO_TARGET;
        }
    }
    return answer;
}
CLEAN_AS(func_0200fea0, FieldActor_PollTarget)

/* func_0200fef0: the request at 0x810 is released (func_020431b8) once func_020431c8 answers 1
 * or 2. */
void FieldActor_PollRequest810(FieldActor *actor)
{
    if (actor->unk_810 == NO_TARGET) {
        return;
    }
    int answer = TileRequests_Carry(actor->unk_810);
    if (answer != 1 && answer != 2) {
        return;
    }
    TileRequests_Release(actor->unk_810);
    actor->unk_810 = NO_TARGET;
}
CLEAN_AS(func_0200fef0, FieldActor_PollRequest810)

/* func_0200ff28: with no target held and a map, looks for one at the tile of `point`, given the
 * tool's value (data_020c7640): mode 0 func_02043a4c, 1 func_02043d84, 2 func_02043990;
 * whether a target is held. */
int FieldActor_FindTarget(FieldActor *actor, const Vec3 *point, int mode, int tool)
{
    if (actor->target == NO_TARGET && data_021c80bc != NULL) {
        int tile[2] = {0, 0};
        Position_Tile(&tile[0], &tile[1], (const Position *) point);
        switch (mode) {
            case 0:
                actor->target =
                    TileRequests_AskForTool0For(actor->player, (const TileRequestTile *) tile, data_020c7640[tool]);
                break;
            case 1:
                actor->target = TileRequests_AskOpFor(actor->player, (const TileRequestTile *) tile, data_020c7640[tool], 0,
                                                      ITEM_CODE_NONE);
                break;
            case 2:
                actor->target = TileRequests_AskFcFdFor(actor->player, (const TileRequestTile *) tile, data_020c7640[tool]);
                break;
            default:
                break;
        }
    }
    return actor->target != NO_TARGET;
}
CLEAN_AS(func_0200ff28, FieldActor_FindTarget)

/* func_0200ffec: the kind of the target held (the word at 0xc of its 0x24-byte entry). */
int FieldActor_TargetKind(FieldActor *actor)
{
    return TileRequests_At(actor->target)->kind;
}
CLEAN_AS(func_0200ffec, FieldActor_TargetKind)

/* ---- Speeds, angles and values moved a step towards a target */

/* Sums and differences of 32-bit values wrap as the ARM's do. */
static int field_actor_support_add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int field_actor_support_sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int field_actor_support_abs32(int a)
{
    return a < 0 ? (int) (0u - (u32) a) : a;
}

/* A turn, and half of one, in 20.12 angle units (an angle of 0x10000 is a turn). */
#define FULL_TURN_FX 0x10000000
#define HALF_TURN_FX 0x08000000

/* func_0201138c: `value` less 0x8f, not below `floor` (a speed slowing gently). */
int FieldActor_SlowGently(int value, int floor)
{
    return FieldActor_StepDown(value, floor, 0x8f);
}
CLEAN_AS(func_0201138c, FieldActor_SlowGently)

/* func_02011398: `value` less 0x9c, not below `floor` (a speed slowing). */
int FieldActor_Slow(int value, int floor)
{
    return FieldActor_StepDown(value, floor, 0x9c);
}
CLEAN_AS(func_02011398, FieldActor_Slow)

/* func_020113a4: `value` less `step`, not below `floor`. */
int FieldActor_StepDown(int value, int floor, int step)
{
    int lowered = field_actor_support_sub32(value, step);
    return lowered >= floor ? lowered : floor;
}
CLEAN_AS(func_020113a4, FieldActor_StepDown)

/* func_020113b0: `value` plus 0x93, not above `ceiling` (a speed rising). */
int FieldActor_SpeedUp(int value, int ceiling)
{
    int raised = field_actor_support_add32(value, 0x93);
    return raised <= ceiling ? raised : ceiling;
}
CLEAN_AS(func_020113b0, FieldActor_SpeedUp)

/* func_020113bc: FieldActor_TurnAngle at the rate 0x666, by at most 0xbb8 and at least 0xc0. */
int FieldActor_TurnAngleSlowly(s16 *angle, int target)
{
    return FieldActor_TurnAngle(angle, target, 0x666, 0x00bb8000, 0x000c0000);
}
CLEAN_AS(func_020113bc, FieldActor_TurnAngleSlowly)

/* func_020113e0: FieldActor_TurnAngle at the rate 0x800, by at most 0x1770 and at least 0xc0. */
int FieldActor_TurnAngleStep(s16 *angle, int target)
{
    return FieldActor_TurnAngle(angle, target, 0x800, 0x01770000, 0x000c0000);
}
CLEAN_AS(func_020113e0, FieldActor_TurnAngleStep)

/* func_02011404: `angle` turned towards `target` the short way round, by the fraction `rate`
 * (20.12) of the distance, at most `max_step` (20.12); a step of `min_step` or less lands on the
 * target. What is left to turn (`target` less the new angle, as 16 bits); 0 once there.
 * QUIRK: the angles are compared as they are, so a `target` outside -0x8000..0x7fff never
 * equals the angle; the arithmetic is in 20.12 units of the 16-bit angle. */
int FieldActor_TurnAngle(s16 *angle, int target, int rate, int max_step, int min_step)
{
    s16 current = *angle;
    if (current == target) {
        return 0;
    }
    int from = current * 0x1000;
    int to = (int) ((u32) target << 12);
    int distance = field_actor_support_abs32(field_actor_support_sub32(to, from));
    int the_other_way = distance > HALF_TURN_FX;
    int step = FX_MulFunc(rate, the_other_way ? FULL_TURN_FX - distance : distance);
    if (step <= min_step) {
        *angle = (s16) target;
        return 0;
    }
    if (step > max_step) {
        step = max_step;
    }
    int up = to >= from;
    if (the_other_way) {
        up = !up;
    }
    int turned = up ? field_actor_support_add32(from, step) : field_actor_support_sub32(from, step);
    *angle = (s16) (turned >> 12);
    return (s16) field_actor_support_sub32(target, *angle);
}
CLEAN_AS(func_02011404, FieldActor_TurnAngle)

/* func_02011490: FieldActor_EaseValueBy with 0xe66 of the distance, at most 0x1ec and at least
 * 0x31. */
void FieldActor_EaseValue(fx32 *value, int target)
{
    FieldActor_EaseValueBy(value, target, 0x0e66, 0x01ec, 0x31);
}
CLEAN_AS(func_02011490, FieldActor_EaseValue)

/* func_020114b0: `value` moved towards `target` by the fraction `rate` (20.12) of the distance,
 * at most `max_step` and at least `min_step`; closer than `min_step` it lands on the target.
 * QUIRK: a step that rounds to 0 counts as one upwards (only possible with a small `rate`). */
void FieldActor_EaseValueBy(fx32 *value, int target, fx32 rate, int max_step, int min_step)
{
    if (*value == target) {
        return;
    }
    int distance = field_actor_support_sub32(target, *value);
    if (field_actor_support_abs32(distance) < min_step) {
        *value = target;
        return;
    }
    int step = FX_MulFunc(distance, rate);
    int size = field_actor_support_abs32(step);
    if (size > max_step) {
        size = max_step;
    } else if (size < min_step) {
        size = min_step;
    } else {
        *value = field_actor_support_add32(*value, step);
        return;
    }
    *value = step >= 0 ? field_actor_support_add32(*value, size) : field_actor_support_sub32(*value, size);
}
CLEAN_AS(func_020114b0, FieldActor_EaseValueBy)

/* func_02011520: run after each frame's update. For this console's player, unless its actor has
 * flag 0xb, 0x13 or 5 (PlayerActorOps_TestFlag): the object at the position of player 4's actor
 * (func_02030890, -1 for none) is noted (func_020953c4), its kind looked up in func_020b5e10's
 * table (func_020b6044) and noted (func_020953a4). For kinds 1, 2 and 4, or an object
 * func_0209d780 accepts, func_0203e110 (only while func_020b67ac) and func_0203e420 run;
 * otherwise func_0203e444 with func_02096190(4) and the object. The result is the answer that
 * stopped it (0, a flag, -1) or the last call's; the caller drops it. */
int FieldActor_NoteObjectUnderfoot(int player)
{
    static const int blocking_flags[] = {0xb, 0x13, 5};

    int result = Session_IsLocalPlayer(data_020ccf94, player);
    if (result == 0) {
        return result;
    }
    for (size_t i = 0; i < sizeof blocking_flags / sizeof blocking_flags[0]; i++) {
        result = PlayerActorOps_TestFlag(blocking_flags[i], player);
        if (result != 0) {
            return result;
        }
    }
    const Vec3 *position = PlayerActorOps_StartPosition(4);
    if (position == NULL) {
        return 0;
    }
    int object = CollisionMap_UnclaimedObjectAtPoint(position);
    if (object == NO_OBJECT) {
        return object;
    }
    PlayerActorOps_NoteObject((unsigned int *) &object);
    int kind;
    int other;
    if (SceneExit_DoorInfo((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), object, &kind, (s16 *) &other) == 0) {
        return 0;
    }
    PlayerActorOps_NoteObjectKind(&kind);
    if (kind == 1 || kind == 2 || kind == 4 || SceneClaim_IsClaimedExit(object) != 0) {
        if (SceneKinds_CurrentIn6To8() != 0) {
            EventQueue_FinishKind4Or12();
        }
        return EventQueue_RequestKind8();
    }
    return EventQueue_RequestUnderfoot((void *) (uintptr_t) SessionPlayers_ActorHandle(4), object);
}
CLEAN_AS(func_02011520, FieldActor_NoteObjectUnderfoot)
