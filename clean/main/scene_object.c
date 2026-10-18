/* The scene object class with vtable 0x020d8c64: its own vtable slots (scene_object.h). */
#include "scene_object.h"

#include "act_effects.h"
#include "actor.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "footsteps.h"
#include "held_item_link.h"
#include "layered_model.h"
#include "obj_020d8c64.h"
#include "scene_action.h"
#include "scene_base.h"
#include "scene_face.h"
#include "scene_look.h"
#include "scene_motion.h"
#include "scene_motion_core.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_probe.h"
#include "scene_share.h"
#include "scene_talk_state.h"
#include "session.h"
#include "shadow.h"
#include "sound_emitter.h"
#include "speaker_anim.h"
#include "collision_query.h"
#include "field_body.h"
#include "globe.h"
#include "link_global.h"
#include "npc_lookup.h"
#include "player_actor_ops.h"
#include "scene_object_base.h"
#include "session_players.h"
#include "model_object.h"

/* The object's parts used here. */
#define SCENE_OBJECT_SPAWN_ARG 0x08     /* u32: what it was made with; its low half is the person */
#define SCENE_OBJECT_POSITION 0x5c      /* Vec3 */
#define SCENE_OBJECT_LAST_POSITION 0x68 /* Vec3 */
#define SCENE_OBJECT_ANGLE 0x8e         /* s16: where it faces */
#define SCENE_OBJECT_WALK_ANGLE 0x94    /* s16: where it walks */
#define SCENE_OBJECT_GRAVITY 0x9c       /* fx32 */
#define SCENE_OBJECT_MIN_Y_VELOCITY 0xa0
#define SCENE_OBJECT_PIVOT 0xc4  /* Vec3 */
#define SCENE_OBJECT_PITCH 0xd0  /* u16 */
#define SCENE_OBJECT_PERSON 0xea /* u16: the person it is (scene_share.h) */
#define SCENE_OBJECT_MODEL 0xec
#define SCENE_OBJECT_MODEL_MATRIX 0x150 /* Mtx43 */
#define SCENE_OBJECT_ANIM_FRAME 0x190   /* fx32: the body animation's frame */
#define SCENE_OBJECT_FACE 0x2ac
#define SCENE_OBJECT_ANIM 0x334
#define SCENE_OBJECT_MOVER 0x350
#define SCENE_OBJECT_PROBE 0x3a8
#define SCENE_OBJECT_LOOK 0x3b0
#define SCENE_OBJECT_TALK_STATE 0x418
#define SCENE_OBJECT_EFFECTS 0x420
#define SCENE_OBJECT_EMITTER_LINK 0x438   /* u8 *: the sound emitter */
#define SCENE_OBJECT_PERSON_BYTE 0x447    /* u8: func_0208239c's answer for the person */
#define SCENE_OBJECT_JOINT_11 0x448       /* Mtx43 */
#define SCENE_OBJECT_JOINT_11_POINT 0x46c /* its translation */
#define SCENE_OBJECT_JOINT_16_POINT 0x478 /* Vec3, on the drawn ground */
#define SCENE_OBJECT_JOINT_7_POINT 0x484
#define SCENE_OBJECT_JOINT_4_POINT 0x490
#define SCENE_OBJECT_COLLIDER 0x49c
#define SCENE_OBJECT_CARRIER 0x4cc
#define SCENE_OBJECT_FLAGS 0x4e8  /* u32 */
#define SCENE_OBJECT_SOLID 0x510  /* u8: it collides and moves with its carrier */
#define SCENE_OBJECT_SHADOW 0x511 /* u8: its shadow is drawn */
#define SCENE_OBJECT_EMITTER 0x514
#define SCENE_OBJECT_FOOTSTEPS 0x558
#define SCENE_OBJECT_UNK_560 0x560
#define SCENE_OBJECT_ENABLED 0x561 /* u8: 0 stops the frame after the mover, and the drawing */
#define SCENE_OBJECT_POSED 0x562   /* u8: 0 keeps the joints' points at the position */
#define SCENE_OBJECT_LOCAL 0x563   /* u8: nonzero: not shared (scene_share.h) */
#define SCENE_OBJECT_MOTION 0x564
#define SCENE_OBJECT_ACTION 0x618
#define SCENE_OBJECT_HELD_BY_SHARE 0x62c /* u8: 1 while the record's holder set the held flag */
#define SCENE_OBJECT_EXTRA 0x62d
#define SCENE_OBJECT_HELD_ITEM 0x628     /* HeldItemLink *, or null */
#define SCENE_OBJECT_SCENE 0x634         /* SceneBase *, or null */
#define SCENE_OBJECT_COLLIDER_SIZE 0x638 /* s32 */

/* The vtable slots called here. */
#define SCENE_OBJECT_SLOT_68 0x68
#define SCENE_OBJECT_SLOT_SORT 0x78

/* Bit 2 of the flags: the object is held (scene_action.h). */
#define SCENE_OBJECT_HELD 2

/* The mode SceneObject_ChangeState starts with. */
#define SCENE_OBJECT_STATE_START 2

/* The person's kinds of motion and their priority while it follows the shared record. */
#define SCENE_OBJECT_FOLLOW_PRIORITY 3
#define SCENE_OBJECT_MOTION_STAND 0
#define SCENE_OBJECT_MOTION_WALK 1
#define SCENE_OBJECT_MOTION_WALK_2 2
#define SCENE_OBJECT_MOTION_TURN 3
#define SCENE_OBJECT_MOTION_ANIMATION 0x0c
#define SCENE_OBJECT_MOTION_GO_TO_SPOT 0x15
/* The animation and item a note fills in, when it does not. */
#define SCENE_OBJECT_DEFAULT_ANIMATION 0x137
#define SCENE_OBJECT_DEFAULT_ITEM 0xfff1

/* The joints whose matrix or point the drawing reads, and the shadow. */
#define SCENE_OBJECT_JOINT_A 11
#define SCENE_OBJECT_JOINT_B 16
#define SCENE_OBJECT_JOINT_C 7
#define SCENE_OBJECT_JOINT_D 4
#define SCENE_OBJECT_SHADOW_SIZE 0xb00
#define SCENE_OBJECT_SHADOW_FADE 0x4000
#define SCENE_OBJECT_SHADOW_SCALE 0x1000

#define SCENE_OBJECT_MIN_Y_VELOCITY_START (-0x1400) /* -1.25 */
#define SCENE_OBJECT_SET_UP_WORD 0xd00              /* what func_0201c3f4 is given */
#define SCENE_OBJECT_COLLIDER_LAYER 0xf
#define SCENE_OBJECT_EVENT_8 8

extern u16 data_020c80f8;          /* the standard word of the motions (4) */
extern const s32 data_020c8178[2]; /* slot 0x94's animation by sort */
extern const s32 data_020c8190[2]; /* slot 0x98's animation by sort */
extern const Vec3 data_021c16c0;   /* the side point tried when the first probe point is blocked */
extern const Vec3 data_021c16b4;   /* and when the second is */
extern NetSession *data_020ccf94;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static void *scene_object_at(u8 *object, u32 offset)
{
    return object + offset;
}

static Vec3 *scene_object_position(u8 *object)
{
    return (Vec3 *) scene_object_at(object, SCENE_OBJECT_POSITION);
}

static s16 scene_object_angle(u8 *object)
{
    return *(const s16 *) scene_object_at(object, SCENE_OBJECT_ANGLE);
}

static SceneMotion *scene_object_motion(u8 *object)
{
    return (SceneMotion *) scene_object_at(object, SCENE_OBJECT_MOTION);
}

static u32 *scene_object_flags(u8 *object)
{
    return (u32 *) scene_object_at(object, SCENE_OBJECT_FLAGS);
}

/* The code of vtable slot `slot` of the object. */
static u32 scene_object_slot(void *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (const void *) (vtable + slot);
}

static void scene_object_copy(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* ---- Slots that do nothing or give a constant */

/* func_0201b6dc (slot 0x64): no villager record. */
int SceneObject_VillagerRecord(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0201b6dc, SceneObject_VillagerRecord)

/* func_0201b6e0 (slot 0x60) */
int SceneObject_Vfunc60(void *object)
{
    (void) object;
    return 0;
}
CLEAN_AS(func_0201b6e0, SceneObject_Vfunc60)

/* func_0201b78c (slot 0x30) */
void SceneObject_Vfunc30(void) {}
CLEAN_AS(func_0201b78c, SceneObject_Vfunc30)

/* func_0201bce8 (slot 0x68, called first in each frame) */
int SceneObject_Vfunc68(void *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_0201bce8, SceneObject_Vfunc68)

/* func_0201c144 (slot 0xa4) */
void SceneObject_VfuncA4(void) {}
CLEAN_AS(func_0201c144, SceneObject_VfuncA4)

/* func_0201c148 (slot 0x9c): the word of act 0 (scene_motion_kinds.h): the standard word. */
u16 SceneObject_Act0Word(void *object)
{
    (void) object;
    return data_020c80f8;
}
CLEAN_AS(func_0201c148, SceneObject_Act0Word)

/* func_0201c244 (slot 0x90): told that a talk it was in ended (scene_action.h); nothing. */
void SceneObject_OnTalkEnd(void *object)
{
    (void) object;
}
CLEAN_AS(func_0201c244, SceneObject_OnTalkEnd)

/* func_0201c248 (slot 0x8c, scene_base.h) */
void SceneObject_Vfunc8c(void *object)
{
    (void) object;
}
CLEAN_AS(func_0201c248, SceneObject_Vfunc8c)

/* func_0201c24c (slot 0x88): told of frame 8 of an animation (SceneMotion_FinishAnimation);
 * nothing. */
void SceneObject_OnFrame8(void) {}
CLEAN_AS(func_0201c24c, SceneObject_OnFrame8)

/* ---- The slots of the object's life */

/* func_0201b6e4 (slot 0x4c): with `event` 8, func_02095eec(0, 4). */
void SceneObject_Vfunc4c(void *object, int event, int participant)
{
    (void) object;
    (void) participant;
    if (event == SCENE_OBJECT_EVENT_8) {
        PlayerActorOps_SwitchFlag0e(0, 4);
    }
}
CLEAN_AS(func_0201b6e4, SceneObject_Vfunc4c)

/* func_0201b6fc (slot 0x5c): joint 11's point (the translation of its matrix at 0x448, read
 * when the object is drawn) onto the curved ground drawn, into `out`. 0 while it is the origin
 * (nothing written). */
int SceneObject_Joint11Point(u8 *object, Vec3 *out)
{
    const Vec3 *point = (const Vec3 *) scene_object_at(object, SCENE_OBJECT_JOINT_11_POINT);
    if (point->x == 0 && point->y == 0 && point->z == 0) {
        return 0;
    }
    scene_object_copy(out, point);
    Globe_Unbend(out, out);
    return 1;
}
CLEAN_AS(func_0201b6fc, SceneObject_Joint11Point)

/* func_0201b744 (slot 0x0c): leaving: the model, the face, the animations and the sound
 * emitter let go, and the state published once more unless the object is not shared.
 * Returns 1. */
int SceneObject_Leave(u8 *object)
{
    SceneObject_ReleaseModel(object);
    SceneFace_Release((SceneFace *) scene_object_at(object, SCENE_OBJECT_FACE));
    SpeakerAnim_Release((SpeakerAnim *) scene_object_at(object, SCENE_OBJECT_ANIM));
    SoundEmitter_Vfunc10((SoundEmitter *) scene_object_at(object, SCENE_OBJECT_EMITTER));
    if (object[SCENE_OBJECT_LOCAL] == 0) {
        SceneShare_Publish(object, 1);
    }
    return 1;
}
CLEAN_AS(func_0201b744, SceneObject_Leave)

/* The point of `joint` onto the curved ground drawn, into `out`. The matrix is read into
 * `joint_matrix`, which keeps what it held when the model has no such joint. */
static void scene_object_joint_point(u8 *object, Mtx43 *joint_matrix, int joint, Vec3 *out)
{
    ModelObject_JointMatrix(scene_object_at(object, SCENE_OBJECT_MODEL), joint_matrix, joint);
    Vec3 point;
    point.x = joint_matrix->m[3][0];
    point.y = joint_matrix->m[3][1];
    point.z = joint_matrix->m[3][2];
    Globe_Unbend(out, &point);
}

/* func_0201b790 (slot 0x24): drawing. While disabled or not posed, the points of joints 16,
 * 7 and 4 are the object's position. Else the model is drawn, the look reads the head, joint
 * 11's matrix is kept at 0x448, the points of joints 16, 7 and 4 are put on the curved ground
 * drawn, and the shadow is drawn when the object has one. Returns 1.
 * REQUIRES: the model has joints 16, 7 and 4. Without joint 16 the ROM reads whatever its stack
 * held, where Clean reads zeros. */
int SceneObject_Draw(u8 *object)
{
    Vec3 *position = scene_object_position(object);
    Vec3 *point_b = (Vec3 *) scene_object_at(object, SCENE_OBJECT_JOINT_16_POINT);
    Vec3 *point_c = (Vec3 *) scene_object_at(object, SCENE_OBJECT_JOINT_7_POINT);
    Vec3 *point_d = (Vec3 *) scene_object_at(object, SCENE_OBJECT_JOINT_4_POINT);

    if (object[SCENE_OBJECT_ENABLED] == 0 || object[SCENE_OBJECT_POSED] == 0) {
        scene_object_copy(point_b, position);
        scene_object_copy(point_c, position);
        scene_object_copy(point_d, position);
        return 1;
    }

    void *model = scene_object_at(object, SCENE_OBJECT_MODEL);
    LayeredModel_DrawA((LayeredModel *) model, NULL);
    SceneLook_ReadHead((SceneLook *) scene_object_at(object, SCENE_OBJECT_LOOK), object);
    ModelObject_JointMatrix(model, (Mtx43 *) scene_object_at(object, SCENE_OBJECT_JOINT_11), SCENE_OBJECT_JOINT_A);

    Mtx43 joint_matrix = {{{0}}};
    scene_object_joint_point(object, &joint_matrix, SCENE_OBJECT_JOINT_B, point_b);
    scene_object_joint_point(object, &joint_matrix, SCENE_OBJECT_JOINT_C, point_c);
    scene_object_joint_point(object, &joint_matrix, SCENE_OBJECT_JOINT_D, point_d);

    if (object[SCENE_OBJECT_SHADOW] != 0) {
        CharaShadow_Draw(position, SCENE_OBJECT_SHADOW_SIZE, SCENE_OBJECT_SHADOW_FADE, SCENE_OBJECT_SHADOW_SCALE);
    }
    return 1;
}
CLEAN_AS(func_0201b790, SceneObject_Draw)

/* Another system runs the object: the motion its record notes (SceneShare_ReadNote) is asked
 * for. A go-to-spot of priority 1 noted as kind 0, 1 or 2 asks for kind 21 (unless it runs)
 * and keeps the walking pace (1 or 2, else 0). Any other kind that is not the one running is
 * asked for at priority 3 with the note's values: 0 stands, 1 and 2 walk, 3 turns, 12 plays
 * an animation and 20 is kind 20 with an item.
 * BUG: a walk's note is unpacked with the start point's x and z into one value and the end
 * point's into another, so each holds its z, and the request gets those as the points' x with
 * z 0. BUGFIX: the four values are kept apart. */
static void scene_object_follow(u8 *object)
{
    SceneMotion *motion = scene_object_motion(object);
    u8 note[SCENE_SHARE_NOTE_SIZE + 3];
    int kind = SCENE_MOTION_KIND_NONE;
    int priority = 0;

    if (SceneShare_ReadNote(object, &kind, &priority, note) == 0) {
        return;
    }

    if (priority == 1 && (u32) kind <= SCENE_OBJECT_MOTION_WALK_2) {
        if (SceneMotion_Kind(motion) != SCENE_OBJECT_MOTION_GO_TO_SPOT) {
            SceneMotion_Request(motion, SCENE_OBJECT_MOTION_GO_TO_SPOT, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        if (kind == SCENE_OBJECT_MOTION_WALK || kind == SCENE_OBJECT_MOTION_WALK_2) {
            motion->pace = kind;
        } else {
            motion->pace = 0;
        }
        return;
    }

    if (kind == SceneMotion_Kind(motion)) {
        return;
    }
    u32 from = 0;
    u32 to = 0;
    s16 rate = 0;
    s16 angle = 0;
    u16 word = 0;
    u16 frame = 0;
    switch (kind) {
        case SCENE_OBJECT_MOTION_STAND:
            SceneMotion_RequestStand(motion, SCENE_OBJECT_FOLLOW_PRIORITY, data_020c80f8);
            break;
        case SCENE_OBJECT_MOTION_WALK:
        case SCENE_OBJECT_MOTION_WALK_2: {
#ifdef BUGFIX
            u32 from_z = 0;
            u32 to_z = 0;
            SceneMotionNote_UnpackPath(&from, &from_z, &to, &to_z, &rate, (s16 *) &word, note);
            SceneMotion_Request(motion, kind, SCENE_OBJECT_FOLLOW_PRIORITY, (int) from, (int) from_z, rate, angle, (int) to,
                                (int) to_z, word, 0);
#else
            SceneMotionNote_UnpackPath(&from, &from, &to, &to, &rate, (s16 *) &word, note);
            SceneMotion_Request(motion, kind, SCENE_OBJECT_FOLLOW_PRIORITY, (int) from, 0, rate, angle, (int) to, 0, word, 0);
#endif
            break;
        }
        case SCENE_OBJECT_MOTION_TURN:
            SceneMotionNote_UnpackTurn(&rate, &angle, &word, note);
            SceneMotion_Request(motion, kind, SCENE_OBJECT_FOLLOW_PRIORITY, (int) from, 0, rate, angle, (int) to, 0, word, 0);
            break;
        case SCENE_OBJECT_MOTION_ANIMATION: {
            u32 animation = SCENE_OBJECT_DEFAULT_ANIMATION;
            u8 mode = 0;
            SceneMotionNote_UnpackAnimation(&animation, &mode, &word, &frame, note);
            SceneMotion_RequestAnimation(motion, SCENE_OBJECT_FOLLOW_PRIORITY, (int) animation, (char) mode, word, frame);
            break;
        }
        case SCENE_MOTION_KIND_20: {
            u16 item = SCENE_OBJECT_DEFAULT_ITEM;
            SceneMotionNote_UnpackItem(&item, note);
            SceneMotion_RequestKind20(motion, SCENE_OBJECT_FOLLOW_PRIORITY, &item);
            break;
        }
        default:
            break;
    }
}

/* func_0201b910 (slot 0x18): the frame. The object moves (SceneMover_Update) and its slot 0x68
 * runs; unless disabled it then follows the shared record when another system runs it, runs
 * its action and motion, updates its act effects at joint 16's point, steers, collides (when
 * solid, with a size, and func_020a7278 agrees), stands at the ground's height, looks, probes
 * ahead, takes its pitch and model matrix, is held while the record names a holder (and let go
 * once not, when it was the record that held it; both only when func_020a7278 agrees), moves
 * with its carrier or not, plays its animations, sounds from its position, moves its held item,
 * steps, moves its face, ends its motion's step and publishes its state unless not shared.
 * Returns 1. */
int SceneObject_Update(u8 *object)
{
    SceneMover_Update((SceneMover *) scene_object_at(object, SCENE_OBJECT_MOVER), object);
    ((void (*)(u8 *))(uintptr_t) scene_object_slot(object, SCENE_OBJECT_SLOT_68))(object);
    if (object[SCENE_OBJECT_ENABLED] == 0) {
        return 1;
    }
    if (SceneShare_IsOurs(object) == 0) {
        scene_object_follow(object);
    }

    Vec3 *position = scene_object_position(object);
    SceneAction_Run((SceneAction *) scene_object_at(object, SCENE_OBJECT_ACTION), object);
    SceneMotion_Run(scene_object_motion(object), object);
    int animation = SpeakerAnim_Number((SpeakerAnim *) scene_object_at(object, SCENE_OBJECT_ANIM), 0);
    fx32 anim_frame = *(const fx32 *) scene_object_at(object, SCENE_OBJECT_ANIM_FRAME);
    ActEffects_Update((ActEffects *) scene_object_at(object, SCENE_OBJECT_EFFECTS),
                      (Vec3 *) scene_object_at(object, SCENE_OBJECT_JOINT_16_POINT), scene_object_angle(object), animation,
                      (u16) (anim_frame >> 12));
    SceneMover_Steer((SceneMover *) scene_object_at(object, SCENE_OBJECT_MOVER), object);
    if (LinkGlobal_HoldsScene() != 0 && object[SCENE_OBJECT_SOLID] != 0 &&
        *(const s32 *) scene_object_at(object, SCENE_OBJECT_COLLIDER_SIZE) > 0) {
        CollisionQuery_Move(scene_object_at(object, SCENE_OBJECT_COLLIDER), position,
                            (Vec3 *) scene_object_at(object, SCENE_OBJECT_LAST_POSITION), scene_object_angle(object),
                            *(const s32 *) scene_object_at(object, SCENE_OBJECT_COLLIDER_SIZE), object,
                            SCENE_OBJECT_COLLIDER_LAYER);
    }
    position->y = CollisionQuery_FloorHeight(0);
    SceneLook_Update((SceneLook *) scene_object_at(object, SCENE_OBJECT_LOOK), object);
    SceneProbe_Clear((u8 *) scene_object_at(object, SCENE_OBJECT_PROBE));
    SceneProbe_Update((u8 *) scene_object_at(object, SCENE_OBJECT_PROBE), object);
    *(u16 *) scene_object_at(object, SCENE_OBJECT_PITCH) =
        (u16) Globe_BendFar((Vec3 *) scene_object_at(object, SCENE_OBJECT_PIVOT), position);

    Mtx43 matrix;
    Actor_ModelMatrix((const Actor *) (const void *) object, &matrix);
    *(Mtx43 *) scene_object_at(object, SCENE_OBJECT_MODEL_MATRIX) = matrix;

    u32 *flags = scene_object_flags(object);
    if (SceneShare_IsHeld(object) != 0) {
        if ((*flags & SCENE_OBJECT_HELD) == 0 && LinkGlobal_HoldsScene() != 0) {
            *flags |= SCENE_OBJECT_HELD;
            object[SCENE_OBJECT_HELD_BY_SHARE] = 1;
        }
    } else if (object[SCENE_OBJECT_HELD_BY_SHARE] == 1 && LinkGlobal_HoldsScene() != 0) {
        *flags &= ~(u32) SCENE_OBJECT_HELD;
        object[SCENE_OBJECT_HELD_BY_SHARE] = 0;
    }

    if (object[SCENE_OBJECT_SOLID] != 0) {
        FieldBody_Enter(scene_object_at(object, SCENE_OBJECT_CARRIER));
    } else {
        FieldBody_Clear(scene_object_at(object, SCENE_OBJECT_CARRIER));
    }
    SpeakerAnim_Update((SpeakerAnim *) scene_object_at(object, SCENE_OBJECT_ANIM), object);
    LayeredModel_UpdateB((LayeredModel *) scene_object_at(object, SCENE_OBJECT_MODEL));
    Vec3 at;
    scene_object_copy(&at, position);
    SoundEmitter_UpdateAt((SoundEmitter *) scene_object_at(object, SCENE_OBJECT_EMITTER), &at);
    HeldItemLink *held = *(HeldItemLink **) scene_object_at(object, SCENE_OBJECT_HELD_ITEM);
    if (held != NULL) {
        HeldItemLink_UpdateFromOwner(held, object);
    }
    Footsteps_Update((Footsteps *) scene_object_at(object, SCENE_OBJECT_FOOTSTEPS), object);
    SceneFace_Step((SceneFace *) scene_object_at(object, SCENE_OBJECT_FACE), object);
    SceneMotion_After(scene_object_motion(object), object);
    if (object[SCENE_OBJECT_LOCAL] == 0) {
        SceneShare_Publish(object, 1);
    }
    return 1;
}
CLEAN_AS(func_0201b910, SceneObject_Update)

/* func_0201bcec (slot 0x08): with mode 2 (a start) the object is held unless func_020a7278
 * agrees or it already was (then marked as held by the record), and its state is published
 * unless not shared; then the scene object's slot (func_0203f004) with the mode. */
void SceneObject_ChangeState(u8 *object, int mode)
{
    if (mode == SCENE_OBJECT_STATE_START) {
        u32 *flags = scene_object_flags(object);
        if (LinkGlobal_HoldsScene() == 0 && (*flags & SCENE_OBJECT_HELD) == 0) {
            *flags |= SCENE_OBJECT_HELD;
            object[SCENE_OBJECT_HELD_BY_SHARE] = 1;
        }
        if (object[SCENE_OBJECT_LOCAL] == 0) {
            SceneShare_Publish(object, 1);
        }
    }
    SceneObjectBase_AfterCreate((SceneObjectBase *) (void *) object, mode);
}
CLEAN_AS(func_0201bcec, SceneObject_ChangeState)

/* func_0201bd48 (slot 0x00): starting. When func_020a7278 agrees, this system becomes the
 * record's owner (no holder). Then the model is loaded (0 when that fails); the object falls
 * at most 1.25 a step without gravity, the mover's angle is the object's, and byte 0x447 is
 * func_0208239c's answer for the person. Returns 1. */
int SceneObject_Start(u8 *object)
{
    if (LinkGlobal_HoldsScene() != 0) {
        SceneShare_SetSlots(object, 1, (u32) data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
    }
    if (SceneObject_LoadModel(object) == 0) {
        return 0;
    }
    *(fx32 *) scene_object_at(object, SCENE_OBJECT_MIN_Y_VELOCITY) = SCENE_OBJECT_MIN_Y_VELOCITY_START;
    *(fx32 *) scene_object_at(object, SCENE_OBJECT_GRAVITY) = 0;
    SceneMover_SetAngle((SceneMover *) scene_object_at(object, SCENE_OBJECT_MOVER), scene_object_angle(object));
    object[SCENE_OBJECT_PERSON_BYTE] = (u8) NpcLookup_SpeciesByte((u16 *) scene_object_at(object, SCENE_OBJECT_PERSON));
    return 1;
}
CLEAN_AS(func_0201bd48, SceneObject_Start)

/* func_0201bdb4 (slot 0x04): the set-up once the scene object's (func_0203f030) agrees (else
 * 0): the person from the low half of the spawn argument, no scene, the members reset, solid
 * with a shadow, enabled and posed, no held item, no extra bytes, and the set-up ended
 * (func_0203ed98). Returns 1. */
int SceneObject_Init(u8 *object)
{
    if (SceneObjectBase_CanCreate((SceneObjectBase *) (void *) object) == 0) {
        return 0;
    }
    u16 person = (u16) * (const u32 *) scene_object_at(object, SCENE_OBJECT_SPAWN_ARG);
    SceneObject_SetPerson(object, &person);
    *(u32 *) scene_object_at(object, SCENE_OBJECT_SCENE) = 0;
    SceneObject_SetColliderSize(object, SCENE_OBJECT_SET_UP_WORD);
    SceneTalkState_Reset((SceneTalkState *) scene_object_at(object, SCENE_OBJECT_TALK_STATE));
    SceneAction_Init((SceneAction *) scene_object_at(object, SCENE_OBJECT_ACTION));
    ActEffects_Init((ActEffects *) scene_object_at(object, SCENE_OBJECT_EFFECTS));
    object[SCENE_OBJECT_UNK_560] = 0;
    SceneMover_Reset((SceneMover *) scene_object_at(object, SCENE_OBJECT_MOVER));
    object[SCENE_OBJECT_HELD_BY_SHARE] = 0;
    MI_CpuFill8(scene_object_at(object, SCENE_OBJECT_EXTRA), 0, SCENE_SHARE_EXTRA_SIZE);
    SoundEmitter_Stop((SoundEmitter *) scene_object_at(object, SCENE_OBJECT_EMITTER));
    *(u8 **) scene_object_at(object, SCENE_OBJECT_EMITTER_LINK) = object + SCENE_OBJECT_EMITTER;
    Footsteps_Init((Footsteps *) scene_object_at(object, SCENE_OBJECT_FOOTSTEPS));
    object[SCENE_OBJECT_SOLID] = 1;
    object[SCENE_OBJECT_SHADOW] = 1;
    Obj020d8c64_ClearLastMotionNumber(object);
    object[SCENE_OBJECT_ENABLED] = 1;
    object[SCENE_OBJECT_POSED] = 1;
    *(u32 *) scene_object_at(object, SCENE_OBJECT_HELD_ITEM) = 0;
    SceneObjectBase_MarkPerson((SceneObjectBase *) (void *) object);
    return 1;
}
CLEAN_AS(func_0201bdb4, SceneObject_Init)

/* func_0201bea4 */
u8 SceneObject_IsEnabled(const u8 *object)
{
    return object[SCENE_OBJECT_ENABLED];
}
CLEAN_AS(func_0201bea4, SceneObject_IsEnabled)

/* ---- What the object's sort (its slot 0x78) picks */

static int scene_object_sort(u8 *object)
{
    return ((int (*)(u8 *))(uintptr_t) scene_object_slot(object, SCENE_OBJECT_SLOT_SORT))(object);
}

/* func_0201c154 (slot 0x98): kind 11's second animation by the sort (227 or 225; sort 0 for
 * 2 and more).
 * REQUIRES: slot 0x78 gives no negative sort (the ROM would read before the table). */
int SceneObject_Kind11SecondAnimation(u8 *object)
{
    int sort = scene_object_sort(object);
    if (sort >= 2) {
        sort = 0;
    }
    return data_020c8190[sort];
}
CLEAN_AS(func_0201c154, SceneObject_Kind11SecondAnimation)

/* func_0201c174 (slot 0x94): kind 11's first animation by the sort (226 or 224), as
 * SceneObject_Kind11SecondAnimation.
 * REQUIRES: slot 0x78 gives no negative sort. */
int SceneObject_Kind11FirstAnimation(u8 *object)
{
    int sort = scene_object_sort(object);
    if (sort >= 2) {
        sort = 0;
    }
    return data_020c8178[sort];
}
CLEAN_AS(func_0201c174, SceneObject_Kind11FirstAnimation)

/* func_0201c250: the sort (slot 0x78) when 0 or 1, else 2; handed to the talk with the
 * object's name (scene_action.h, scene_talk.h). */
int SceneObject_Sort(u8 *object)
{
    int sort = scene_object_sort(object);
    if (sort == 0 || sort == 1) {
        return sort;
    }
    return 2;
}
CLEAN_AS(func_0201c250, SceneObject_Sort)

/* ---- Stepping aside */

/* func_0201c194: `out` is the object's position, or a free point to the side when the probe
 * ahead (scene_probe.h) found one of its points blocked: data_021c16c0 when the first is,
 * data_021c16b4 when the second is. SCENE_OBJECT_CLEAR when neither is blocked,
 * SCENE_OBJECT_BLOCKED when both are or the side point is blocked too, SCENE_OBJECT_SIDE_POINT
 * when `out` is the side point. */
int SceneObject_SideStep(u8 *object, Vec3 *out)
{
    int blocked = SceneProbe_Bits((u8 *) scene_object_at(object, SCENE_OBJECT_PROBE));
    scene_object_copy(out, scene_object_position(object));
    switch (blocked) {
        case 3:
            return SCENE_OBJECT_BLOCKED;
        case 1:
            return SceneObject_TrySidePoint(object, out, &data_021c16c0) ? SCENE_OBJECT_SIDE_POINT : SCENE_OBJECT_BLOCKED;
        case 2:
            return SceneObject_TrySidePoint(object, out, &data_021c16b4) ? SCENE_OBJECT_SIDE_POINT : SCENE_OBJECT_BLOCKED;
        default:
            return SCENE_OBJECT_CLEAR;
    }
}
CLEAN_AS(func_0201c194, SceneObject_SideStep)

/* func_0201c208: the point `offset` from the object turned by its walking angle, into `out`
 * when it is not blocked (SceneProbe_IsBlocked other than 1); whether it was. */
int SceneObject_TrySidePoint(u8 *object, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;
    SceneProbe_PointAt(&point, scene_object_position(object), offset,
                       *(const s16 *) scene_object_at(object, SCENE_OBJECT_WALK_ANGLE));
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    scene_object_copy(out, &point);
    return 1;
}
CLEAN_AS(func_0201c208, SceneObject_TrySidePoint)

/* ---- The scene it talks in, and other objects */

/* func_0201c274: the scene the object talks in (its address), or 0. */
u32 SceneObject_Scene(u8 *object)
{
    return *(const u32 *) scene_object_at(object, SCENE_OBJECT_SCENE);
}
CLEAN_AS(func_0201c274, SceneObject_Scene)

/* func_0201c280: the scene the object talks in; the object becomes its first speaker. */
void SceneObject_SetScene(u8 *object, struct SceneBase *scene)
{
    *(SceneBase **) scene_object_at(object, SCENE_OBJECT_SCENE) = scene;
    if (scene != NULL) {
        SceneBase_SetFirstSpeaker(scene, object);
    }
}
CLEAN_AS(func_0201c280, SceneObject_SetScene)

/* func_0201c2a4: the object of field actor `actor`, or 0. */
int SceneObject_ActorObject(u8 *object, int actor)
{
    (void) object;
    return SessionPlayers_ActorHandle(actor);
}
CLEAN_AS(func_0201c2a4, SceneObject_ActorObject)

/* func_0201c2b0: the angle to `target` from where the object faces, as 16 bits. */
int SceneObject_AngleTo(u8 *object, u8 *target)
{
    return (s16) (SceneObject_YawTo(object, target) - scene_object_angle(object));
}
CLEAN_AS(func_0201c2b0, SceneObject_AngleTo)

/* func_0201c2c8: the angle (Vec_YawTo) from the object to the place of field actor `actor`
 * when it is known (func_02096614), else to the actor's object (0 without one). The matching
 * source gives it as a pointer. */
void *SceneObject_YawToActor(u8 *object, int actor)
{
    int yaw = 0;
    u8 scene = 0;
    Vec3 place = {0, 0, 0};
    if (SessionPlayers_ScenePoint(&scene, (int *) &place.x, (int *) &place.z, -1, actor) != 0) {
        yaw = Vec_YawTo(scene_object_position(object), &place);
    } else {
        int other = SessionPlayers_ActorHandle(actor);
        if (other != 0) {
            yaw = SceneObject_YawTo(object, (u8 *) (uintptr_t) other);
        }
    }
    return (void *) (intptr_t) yaw;
}
CLEAN_AS(func_0201c2c8, SceneObject_YawToActor)

/* func_0201c314: the angle (Vec_YawTo) from the object to `target`, 0 without one. */
int SceneObject_YawTo(u8 *object, u8 *target)
{
    if (target == NULL) {
        return 0;
    }
    return Vec_YawTo(scene_object_position(object), scene_object_position(target));
}
CLEAN_AS(func_0201c314, SceneObject_YawTo)

/* func_0201c330: whether field actor `actor`'s object is nearer the object than `distance`. */
int SceneObject_IsNearActor(u8 *object, int distance, int actor)
{
    return SceneObject_IsNear(object, (u8 *) (uintptr_t) SessionPlayers_ActorHandle(actor), distance);
}
CLEAN_AS(func_0201c330, SceneObject_IsNearActor)

/* ---- Distances, facing, the person and the model */

#define SCENE_OBJECT_PERSON_INDEX 0x632 /* u16: the person code without its top 4 bits */
#define SCENE_OBJECT_PERSON_MASK 0x0fff
#define SCENE_OBJECT_SLOT_MODEL_PATH 0x70 /* gives the model's file */
#define SCENE_OBJECT_QUARTER_TURN 0x4000

/* The unit heap models are loaded from (resource_pools.h). */
extern Heap *data_021c9ab8;

/* Whether `value` is nearer 0 than `limit` either way.
 * QUIRK: as the ROM's negation, the most negative value stays negative and counts as near. */
static int scene_object_is_within(s32 value, s32 limit)
{
    u32 magnitude = value < 0 ? 0u - (u32) value : (u32) value;
    return (s32) magnitude < limit;
}

/* func_0201c350: whether `other` (an object, or null) is nearer the object than `distance`. */
int SceneObject_IsNear(u8 *object, u8 *other, int distance)
{
    if (other == NULL) {
        return 0;
    }
    return scene_object_is_within(SceneObject_DistanceTo(object, other), distance);
}
CLEAN_AS(func_0201c350, SceneObject_IsNear)

/* func_0201c378: the distance to field actor `actor`'s object (0 without one). */
int SceneObject_DistanceToActor(u8 *object, int actor)
{
    return SceneObject_DistanceTo(object, (u8 *) (uintptr_t) SessionPlayers_ActorHandle(actor));
}
CLEAN_AS(func_0201c378, SceneObject_DistanceToActor)

/* func_0201c390: the distance between the positions of `other` and the object, 0 without
 * `other`. */
int SceneObject_DistanceTo(u8 *object, u8 *other)
{
    if (other == NULL) {
        return 0;
    }
    return Vec_Distance(scene_object_position(other), scene_object_position(object));
}
CLEAN_AS(func_0201c390, SceneObject_DistanceTo)

/* func_0201c3b0: the angle from the object to `point` into `yaw`; whether it is less than a
 * quarter turn from where the object faces. */
int SceneObject_FacesPoint(u8 *object, s16 *yaw, const Vec3 *point)
{
    *yaw = Vec_YawTo(scene_object_position(object), point);
    return SceneObject_IsWithinQuarterTurn((s16) (*yaw - scene_object_angle(object)));
}
CLEAN_AS(func_0201c3b0, SceneObject_FacesPoint)

/* func_0201c3dc: whether a turn of `angle` is less than a quarter turn either way. */
int SceneObject_IsWithinQuarterTurn(int angle)
{
    return scene_object_is_within(angle, SCENE_OBJECT_QUARTER_TURN);
}
CLEAN_AS(func_0201c3dc, SceneObject_IsWithinQuarterTurn)

/* func_0201c3f4 */
void SceneObject_SetColliderSize(u8 *object, int size)
{
    *(s32 *) scene_object_at(object, SCENE_OBJECT_COLLIDER_SIZE) = size;
}
CLEAN_AS(func_0201c3f4, SceneObject_SetColliderSize)

/* func_0201c400: the person code (0xea) from `code`, its index (the low 12 bits, read back
 * from 0xea) and the object's word at 0xdc from the index. */
void SceneObject_SetPerson(u8 *object, u16 *code)
{
    u16 *person = (u16 *) scene_object_at(object, SCENE_OBJECT_PERSON);
    *person = *code;
    SceneObject_SetPersonIndex(object, (u16) (*person & SCENE_OBJECT_PERSON_MASK));
    SceneObjectBase_SetId((SceneObjectBase *) (void *) object, SceneObject_PersonIndex(object));
}
CLEAN_AS(func_0201c400, SceneObject_SetPerson)

/* func_0201c438 */
void SceneObject_SetPersonIndex(u8 *object, u16 index)
{
    *(u16 *) scene_object_at(object, SCENE_OBJECT_PERSON_INDEX) = index;
}
CLEAN_AS(func_0201c438, SceneObject_SetPersonIndex)

/* func_0201c444 */
u16 SceneObject_PersonIndex(u8 *object)
{
    return *(const u16 *) scene_object_at(object, SCENE_OBJECT_PERSON_INDEX);
}
CLEAN_AS(func_0201c444, SceneObject_PersonIndex)

/* func_0201c450: the model (0xec) let go; the model's answer. */
int SceneObject_ReleaseModel(u8 *object)
{
    return ModelObject_Release((ModelObject *) scene_object_at(object, SCENE_OBJECT_MODEL));
}
CLEAN_AS(func_0201c450, SceneObject_ReleaseModel)

/* func_0201c45c: the model (0xec) loaded from the file vtable slot 0x70 gives, from the unit
 * heap data_021c9ab8; whether it was. */
int SceneObject_LoadModel(u8 *object)
{
    int path = ((int (*)(void *))(uintptr_t) scene_object_slot(object, SCENE_OBJECT_SLOT_MODEL_PATH))(object);
    if (ModelObject_Load((ModelObject *) scene_object_at(object, SCENE_OBJECT_MODEL), (const char *) (uintptr_t) path,
                         data_021c9ab8) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0201c45c, SceneObject_LoadModel)
