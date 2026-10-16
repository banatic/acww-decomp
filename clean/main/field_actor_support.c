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

/* Items. */
extern void func_020110c4(u16 *item, FieldActor *actor);
extern int func_0204bcdc(const u16 *item);
extern int func_0204bc64(const u16 *item);
extern u32 func_02062148(const u16 *item);

/* What the session reports of a player's actor: its scene and tile point, its yaw; the actor of
 * a player (NULL for none) and its start position; whether a player's actor is in a state. */
extern int func_02096614(u8 *scene, fx32 *x, fx32 *z, int a, int player);
extern int func_0209658c(s16 *yaw, int a, int player);
extern const Vec3 *func_02095794(int player);
extern int func_020960f8(int state, int player);
extern u8 func_020b65c4(void); /* the current scene */
extern u8 func_020b65b8(void); /* the scene byte at data_020e54b0 */

/* The receiver's conversation (as the ATM's): the player's choice, a message, a text slot. */
extern void *func_0206837c(void *talk);
extern unsigned int func_020ab504(void *menu);
extern void func_0206844c(void *talk, const u8 *message, const char *name);
extern void *func_02062f90(void *text, const u16 *item);
extern void func_020683b4(void *talk, int slot, void *text, int kind);
extern void *func_02062f4c(void *text);
extern void func_02035638(int value);
extern void func_02035684(int kind, int a, int b);

/* The body's model and the held item. */
extern int func_0203f8d0(Vec3 *pivot, Vec3 *position);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern void func_02055d38(void *model, int value);
extern void func_02054848(void *model, int a);
extern int func_02055d0c(void *model, void *out, int joint);
extern void func_0205eae0(void *held, int pose, int a, int b);
extern void func_02010d64(FieldActor *actor);

/* Turning and easing. */
extern int func_02011404(s16 *angle, int target, int rate, int max_step, int min_step);
extern int func_020113e0(s16 *angle, int target);
extern void func_020110a0(FieldActor *actor, s16 *yaw);
extern void func_02011490(fx32 *value, int target);
extern void func_020114b0(fx32 *value, int target, fx32 rate, int max_step, int min_step);
extern int func_02064558(int angle);

/* Sounds and effects. */
extern int func_02056f28(const FrameCtrl *ctrl, int frame);
extern int func_020912d4(int kind, Vec3 *position, s16 *angle, int a);
extern int func_020b1cb0(const Vec3 *point);

/* The battery and the record of the player at this console. */
extern int func_0202f188(void);
extern int func_0208ffac(void);
extern int func_0208ff98(void);
extern void *func_02011368(FieldActor *actor);
extern u32 func_020112bc(FieldActor *actor);
extern s16 func_020997a8(void *record);
extern void func_02099794(int record, u16 date);
extern u16 *func_0209d358(int a, int b);
extern u16 *func_0209627c(void);
extern void func_0209e474(DateTime *now);
extern int func_0209e3ac(const DateTime *a, const DateTime *b, int fields);
extern void func_02096484(u8 *out, int item, int kind);

/* Tiles and the targets on them. */
extern void func_0204f794(Vec3 *point, u32 x, u32 z);
extern void func_0204f7e0(Vec3 *out, const Vec3 *point);
extern void func_0204f818(int *x, int *z, const Vec3 *point);
extern u16 *func_0204f5e0(void *map, int acre_x, int acre_z, int x, int z, int layer);
extern int func_02043a4c(int player, const int *tile, int value);
extern int func_02043d84(int player, const int *tile, int a, int b, int item);
extern int func_02043990(int player, const int *tile, int value);
extern int func_020436a8(int target);
extern int func_020431c8(int request);
extern void func_020431b8(int target);
extern const u8 *func_02042fc4(int target);
extern int func_ov004_0222ac24(FieldActor *actor, const int *tile, int number, int priority, int arg);

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
    if (func_0204bcdc(item)) {
        u16 nothing = ITEM_CODE_NONE;
        return func_0204bc64(item) == func_0204bc64(&nothing);
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

    if (func_02096614(&reported_scene, &reported_x, &reported_z, -1, actor->player) == 0) {
        return 0;
    }
    if (func_0209658c(&reported_yaw, -1, actor->player) == 0) {
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
            func_02035638(0x39);
            func_02035684(0xc, start, start + 5);
            actor->unk_81C = TALK_OVER;
            break;
        case 7: {
            u16 value = field_actor_support_work_halfword(actor);
            u16 item;
            func_02035638(value);
            func_020110c4(&item, actor);
            if (!field_actor_support_item_is_nothing(&item) && FieldActor_HeldToolNumber(actor) == 0 && data_020e54a8 == 0) {
                start += 0x15;
            }
            if (value == 0x3c || value == 0x3d) {
                func_02035684(5, start, start + 5);
            } else {
                func_02035684(0xc, start, start + 5);
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
            func_02035638(value);
            func_02035684(kind, 0x14, 0x19);
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
            func_02035638(value);
            func_02035684(0xc, start, start + 5);
            actor->unk_81C = TALK_OVER;
            break;
        }
        case 12:
            func_02035638(0x42);
            func_02035684(0xc, start, 0xb);
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
    unsigned int choice = func_020ab504(func_0206837c(actor->link));
    u8 message = data_021f43e8;
    func_0206844c(actor->link, &message, NULL);

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
    func_0206844c(actor->link, &number, NULL);
}

/* Puts the name of `item` into the talk's text slot 0 (kind 7). */
static void field_actor_support_name_item(FieldActor *actor, u16 item)
{
    u8 text[0x28];
    func_02062f90(text, &item);
    func_020683b4(actor->link, 0, text, 7);
    func_02062f4c(text);
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
    u8 scene = func_020b65b8();
    if (scene != 0xc && scene != 0xd && scene != 0xe && scene != 0x2e && scene != 0x2f) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    for (int slot = 0; slot < 4; slot++) {
        if (Session_IsSlotTaken(session, slot)) {
            s16 yaw;
            if (func_0209658c(&yaw, -1, slot) == 0) {
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

    base->pitch = (u16) func_0203f8d0(&base->pivot, &base->position);
    Actor_ModelMatrix(base, &model);
    memcpy(&actor->unk_298, &model, sizeof(model));
    data_021cfe68 = actor->unk_298;
    func_02055d38(actor->unk_234, 0);
    func_02054848(actor->unk_234, 0);
    func_02055d0c(actor->unk_234, &actor->unk_698, 0xb);
}
CLEAN_AS(func_0200ee40, FieldActor_RebuildPose)

/* func_0200eebc: the held item's pose for the tool held (FieldActor_HeldTool): 9 for tool 4,
 * 0x13 for 3, 0x23 for 10, 0x21 for 6; nothing for the others. */
void FieldActor_PoseHeldTool(FieldActor *actor)
{
    switch (FieldActor_HeldTool(actor)) {
        case 4:
            func_0205eae0(actor->held, 0, 9, 0);
            break;
        case 3:
            func_0205eae0(actor->held, 0x13, 3, 0);
            break;
        case 10:
            func_0205eae0(actor->held, 0x23, 3, 0);
            break;
        case 6:
            func_0205eae0(actor->held, 0x21, 3, 0);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0200eebc, FieldActor_PoseHeldTool)

/* func_0200ef1c: func_02010d64 (the actor's checks) with the position moved aside for a
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
        if (Session_IsLocalPlayer(data_020ccf94, other) && func_020960f8(2, 4) &&
            func_02096614(&scene, &reported.x, &reported.z, -1, actor->player)) {
            const Vec3 *other_start = func_02095794(other);
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
    func_02010d64(actor);
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

/* func_0200f098: while flag 0x15 is set the head turns (func_02011404, by 0x400) towards the
 * pitch and yaw at 0x460 and 0x462; once all four are 0 the flag is cleared. */
void FieldActor_TurnHeadBack(FieldActor *actor)
{
    if (!FieldActor_TestFlag(actor, 0x15)) {
        return;
    }
    func_02011404(&actor->head_pitch, FIELD_ACTOR_FIELD(actor, s16, 0x460), 0x400, 0x1770000, 0xc0000);
    func_02011404(&actor->head_yaw, FIELD_ACTOR_FIELD(actor, s16, 0x462), 0x400, 0x1770000, 0xc0000);
    if (FIELD_ACTOR_FIELD(actor, s16, 0x460) == 0 && FIELD_ACTOR_FIELD(actor, s16, 0x462) == 0 && actor->head_pitch == 0 &&
        actor->head_yaw == 0) {
        FieldActor_ClearFlag(actor, 0x15);
    }
}
CLEAN_AS(func_0200f098, FieldActor_TurnHeadBack)

/* ---- Messages to the session */

/* func_0200f11c: while linked, the sun level (func_020112bc, a byte) goes to the session as
 * message 0x2e. */
void FieldActor_SendSunLevel(FieldActor *actor)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 level = (u8) func_020112bc(actor);
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
    func_02096484(bytes, item, kind);
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
    func_0203f7d0(out, out);
    return 1;
}
CLEAN_AS(func_0200f1ec, FieldActor_JointBPoint)

/* func_0200f234: the aim mode (FieldActor.aim_mode) from the setting func_0208ffac and
 * func_0208ff98 read: 1, 2, else 0. */
void FieldActor_TakeAimMode(FieldActor *actor)
{
    if (func_0208ffac()) {
        actor->aim_mode = 1;
    } else if (func_0208ff98()) {
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
    switch (func_02064558(actor->yaw)) {
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
    func_0204f794(&point, (u32) tile[0], (u32) tile[1]);
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
    return scene == func_020b65c4();
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
    func_0203f7d0(out, &point);
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
    if (func_0202f188()) {
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
    func_02099794(record, *date);
    u16 *summary = func_0209d358(0, 0x50);
    *summary = (u16) (func_020112bc(actor) + PACKED_MONTH(*date) * 1000 + PACKED_DAY(*date) * 10);
    if (FieldActor_LinkedNotPlayer0(actor) == 0) {
        *func_0209627c() = *date;
    }
}
CLEAN_AS(func_0200f7ac, FieldActor_StoreSunDate)

/* func_0200f814: the clock's date and time into `now` (func_0209e474), a copy of it with the
 * day, month and year of the date in the player's record (the halfword func_020997a8 reads)
 * into `stored`, and their order (func_0209e3ac, fields 0x3f): -1, 0 or 1. */
int FieldActor_CompareSunDate(FieldActor *actor, DateTime *now, DateTime *stored)
{
    u16 date = (u16) func_020997a8(func_02011368(actor));
    func_0209e474(now);
    MI_CpuCopy8(now, stored, 8);
    stored->year = (u8) PACKED_YEAR(date);
    stored->month = (u8) PACKED_MONTH(date);
    stored->day = (u8) PACKED_DAY(date);
    return func_0209e3ac(now, stored, 0x3f);
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
    int sound = func_020b1cb0(&between);
    SoundEmitter_PlayAlternating(emitter, (u32) sound, running);
}
CLEAN_AS(func_0200f888, FieldActor_PlayFootstep)

/* func_0200f95c: at frames 1 and 9 of the body's animation a foot lands: at joint 7's point for
 * frame 9, else joint 4's, at the actor's height, effect 0x27 facing the yaw (and, running in
 * animation 2, effect 0 facing back) and the footstep sound. */
void FieldActor_Footfall(FieldActor *actor)
{
    if (!func_02056f28(&actor->anim, 1) && !func_02056f28(&actor->anim, 9)) {
        return;
    }
    s16 ahead = actor->yaw;
    s16 back = (s16) (ahead + 0x8000);
    Vec3 at;
    if (func_02056f28(&actor->anim, 9)) {
        at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_7);
    } else {
        at = FIELD_ACTOR_FIELD(actor, Vec3, FIELD_ACTOR_POINT_JOINT_4);
    }
    at.y = actor->position.y;
    if (actor->animation == 2) {
        func_020912d4(0, &at, &back, 0);
    }
    func_020912d4(0x27, &at, &ahead, 0);
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
    func_0204f7e0(out, &ahead);
}
CLEAN_AS(func_0200fa8c, FieldActor_TileAhead)

/* Turns the body towards `target` at `rate` (func_02011404); whether it is there. */
static int field_actor_support_turn_to(FieldActor *actor, int target, int rate)
{
    s16 yaw = actor->yaw;
    int arrived = func_02011404(&yaw, target, rate, 0x1770000, 0xc0000) == 0;
    func_020110a0(actor, &yaw);
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

/* func_0200fb34: the body turns towards `yaw` (func_020113e0). */
void FieldActor_TurnTowards(FieldActor *actor, int yaw)
{
    s16 turned = actor->yaw;
    func_020113e0(&turned, yaw);
    func_020110a0(actor, &turned);
}
CLEAN_AS(func_0200fb34, FieldActor_TurnTowards)

/* func_0200fb58: the position eases towards (x, z) (func_02011490). */
void FieldActor_EaseToXZ(FieldActor *actor, int x, int z)
{
    func_02011490(&actor->position.x, x);
    func_02011490(&actor->position.z, z);
}
CLEAN_AS(func_0200fb58, FieldActor_EaseToXZ)

/* func_0200fb7c: the position eases towards (x, z) (func_020114b0: 0xe66 of the way, at most
 * 0x4cd, the rest when within 0x31) and the body turns towards `yaw`. */
void FieldActor_EaseToPose(FieldActor *actor, int x, int z, int yaw)
{
    func_020114b0(&actor->position.x, x, 0x0e66, 0x04cd, 0x31);
    func_020114b0(&actor->position.z, z, 0x0e66, 0x04cd, 0x31);
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

/* func_0200fc90: with flag 0 and an item held (func_020110c4), one more than func_02062148 gives
 * for it; else 0. */
int FieldActor_HeldToolNumber(FieldActor *actor)
{
    u16 item;
    func_020110c4(&item, actor);
    if (FieldActor_TestFlag(actor, 0) && !field_actor_support_item_is_nothing(&item)) {
        return (int) (func_02062148(&item) + 1);
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
    func_0204f818(&tile[0], &tile[1], point);

    switch (kind) {
        case 3:
        case 4:
        case 0x15:
        case 0x16:
            if (overlay4) {
                func_ov004_0222ac24(actor, tile, -2, 6, -1);
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
    u16 *on_map = func_0204f5e0(data_021c80bc, field_actor_support_shift_right(x, 4), field_actor_support_shift_right(z, 4),
                                x & 0xf, z & 0xf, 0);
    if (on_map == NULL) {
        actor->unk_822 = ITEM_CODE_NONE;
        actor->item = actor->unk_822;
        return 2;
    }
    actor->unk_822 = *on_map;
    actor->item = actor->unk_822;

    int at[2] = {tile[0], tile[1]};
    actor->target = func_02043d84(actor->player, at, a, b, ITEM_CODE_NONE);
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
        answer = func_020436a8(actor->target);
        if (answer == 1 || answer == 2) {
            actor->unk_814 = FieldActor_TargetKind(actor);
            func_020431b8(actor->target);
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
    int answer = func_020431c8(actor->unk_810);
    if (answer != 1 && answer != 2) {
        return;
    }
    func_020431b8(actor->unk_810);
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
        func_0204f818(&tile[0], &tile[1], point);
        switch (mode) {
            case 0:
                actor->target = func_02043a4c(actor->player, tile, data_020c7640[tool]);
                break;
            case 1:
                actor->target = func_02043d84(actor->player, tile, data_020c7640[tool], 0, ITEM_CODE_NONE);
                break;
            case 2:
                actor->target = func_02043990(actor->player, tile, data_020c7640[tool]);
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
    return *(const int *) (func_02042fc4(actor->target) + 0xc);
}
CLEAN_AS(func_0200ffec, FieldActor_TargetKind)
