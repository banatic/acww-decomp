/* The field actor's models, placed for drawing (field_actor.h).
 *
 * The body's model at 0x234 is drawn with callbacks on its node commands (func_02055de0
 * installs FieldActor_NodeBefore). They run in turn on each node, each installing the next:
 * FieldActor_NodeBefore at timing 1, FieldActor_NodeTransform at timing 2 and FieldActor_NodeAfter
 * at timing 3, which installs FieldActor_NodeBefore again. The head (node 0xf) is turned by
 * the actor's head angles; the root (node 0) is where the actor's start position is taken from. */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "field_actor_parts.h"
#include "main/model_matrix.h"

/* The render state the node callbacks are handed, as far as they read it. */
typedef struct NodeRenderObject {
    u8 unk_00[0x2c];
    FieldActor *actor; /* 0x2c: the actor the model belongs to, or NULL */
} NodeRenderObject;

typedef struct NodeJoint {
    u8 unk_00[0x28];
    Mtx33 rotation;   /* 0x28 */
    Vec3 translation; /* 0x4c */
} NodeJoint;

typedef struct NodeRenderState {
    const u8 *command;              /* 0x00: the node command being run; byte 1 is the node */
    const NodeRenderObject *object; /* 0x04 */
    u8 unk_08[0x24 - 0x08];
    u32 node_callback; /* 0x24: the callback of the node commands (a DS address) */
    u8 unk_28[0x92 - 0x28];
    u8 node_timing; /* 0x92: when in the command it runs: 1, 2 or 3 */
    u8 unk_93[0xb4 - 0x93];
    NodeJoint *joint; /* 0xb4: the node's transform */
} NodeRenderState;

static_assert(offsetof(NodeRenderObject, actor) == 0x2c, "render object actor");
static_assert(offsetof(NodeJoint, translation) == 0x4c, "joint translation");
static_assert(offsetof(NodeRenderState, node_callback) == 0x24, "node callback");
static_assert(offsetof(NodeRenderState, node_timing) == 0x92, "node timing");
static_assert(offsetof(NodeRenderState, joint) == 0xb4, "joint");

#define NODE_ROOT 0
#define NODE_HEAD 0xf

/* The current model matrix of main's 3D drawing (model_matrix.h). */
extern Mtx43 data_021cfe68;
/* The scene: 0 outdoors (overlay 3), else indoors (overlay 4). */
extern u8 data_020e54a8;
/* NitroSDK's table of sines and cosines, interleaved, for 4096 angles. */
extern const s16 FX_SinCosTable_[];

/* The placement modes (FieldActor.unk_7F8) as member pointers: a table of two filled from
 * constants on the first call (field_actor_parts.h). */
extern u32 data_021bfff4;
extern MemberPointer data_021c0008[2];
extern const MemberPointer data_020d747c, data_020d74b4;

extern int func_0200f290(FieldActor *actor, int bit);
extern int func_020310c8(int value);
extern int func_0200fbe0(FieldActor *actor);
/* A point on the flat ground to the curved ground drawn (func_0203f7d0), back
 * (func_0203f8d0, giving the angle of the slope), and the same with the slope's angle about X
 * (func_0203f844); func_0203f758 is the curve's radius. */
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern int func_0203f8d0(Vec3 *out, Vec3 *in);
extern int func_0203f844(Vec3 *out, Vec3 *in);
extern int func_0203f758(void);
/* The models. */
extern void func_02055d38(void *model, int value);
extern void func_02054848(void *model, int a);
extern int func_02055d0c(void *model, Mtx43 *out, int joint);
extern void func_02055e7c(void *model, void *a);
extern int func_0205e138(const u8 *part, int a);
extern int func_0205ddd4(u8 *part);
extern void func_020acbc8(Vec3 *point, int mark);
extern void func_0205e954(void *held, Mtx43 *hand);
extern void func_0205e8f8(Mtx43 *out, const u8 *held, u32 mode);
extern void func_02054f68(NodeRenderState *state, int a);
extern void func_0205490c(void *model, NodeRenderState *state);
extern void func_02054ed4(void *model, NodeRenderState *state, int a);
extern void func_02054988(void *model, NodeRenderState *state);
extern void MTX_RotY33_(Mtx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_RotX33_(Mtx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *out);
/* An item's model drawn at a point with a scale, outdoors and indoors. */
extern void func_ov003_0222462c(int item, const Vec3 *position, const Vec3 *scale, int a3, int a4, int a5);
extern void func_ov004_02233b10(int item, const Vec3 *position, const Vec3 *scale, int a3, int a4, int a5);

/* The node callbacks, installed by their DS addresses. */
extern void func_02005730(NodeRenderState *state);
extern void func_02005740(NodeRenderState *state);
extern void func_020058b4(NodeRenderState *state);

static u8 *at(FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

static Mtx43 *matrix_at(FieldActor *actor, u32 offset)
{
    return (Mtx43 *) at(actor, offset);
}

static fx32 sin_of(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4)];
}

static fx32 cos_of(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4) + 1];
}

static Vec3 translation_of(const Mtx43 *matrix)
{
    Vec3 point = {matrix->m[3][0], matrix->m[3][1], matrix->m[3][2]};
    return point;
}

/* func_02005338: vtable slot 0x24 (FieldActor_Vfunc24): the model placed by the mode at
 * FieldActor.unk_7F8 (0: FieldActor_PlaceAtPosition, 1: FieldActor_PlaceModel); then, with
 * flag 0xd, the item at unk_822 is drawn at unk_824 scaled by unk_830 (state 0x85).
 * REQUIRES: the mode is 0 or 1 (the ROM indexes its table unchecked). */
void FieldActor_PlaceForDraw(FieldActor *actor)
{
    static const MemberPointer *const constants[2] = {&data_020d747c, &data_020d74b4};

    MemberTable_InitOnce(&data_021bfff4, data_021c0008, constants, 2);
    MemberPointer place = data_021c0008[actor->unk_7F8];
    FieldActor_CallUpdate(&place, actor);
    if (func_0200f290(actor, 0xd)) {
        Vec3 position = actor->unk_824;
        Vec3 scale = {actor->unk_830[0], actor->unk_830[1], actor->unk_830[2]};
        if (data_020e54a8 == 0) {
            func_ov003_0222462c(actor->unk_822, &position, &scale, 0, 0, 0);
        } else {
            func_ov004_02233b10(actor->unk_822, &position, &scale, 0, 0, 0);
        }
    }
}
CLEAN_AS(func_02005338, FieldActor_PlaceForDraw)

/* func_0200545c: the height the model's root is placed at: `y`, except indoors with flag 3,
 * where it is func_020310c8(0). */
int FieldActor_ModelY(FieldActor *actor, int y)
{
    if (data_020e54a8 != 0 && func_0200f290(actor, 3)) {
        return func_020310c8(0);
    }
    return y;
}
CLEAN_AS(func_0200545c, FieldActor_ModelY)

/* func_02005490: placement mode 1. The actor's model matrix becomes the current one and the
 * body is updated; the matrices of joints 0xf, 0xe and 0xb are kept, and the points of joints 7,
 * 4 and 0x10 on the curved ground. The models at 0x38c, 0x464 and 0x500 take joint 0xf's matrix
 * (the second unless the part at 0x428 gives 0x9e or more, the third unless the part at 0x59c
 * gives 0x4b). With a mark (FieldActor_SetMarkForState) joint 1's point goes to func_020acbc8.
 * With flag 0 the held item is placed in the hand (joint 0xe) and its matrices are kept: one
 * for the tool's mode (2 for tools 4 and 10, 1 for 1, 5 and 9, else 0), and for tool 4 also
 * the one of mode 3. */
void FieldActor_PlaceModel(FieldActor *actor)
{
    u8 *body = at(actor, FIELD_ACTOR_BODY);
    Mtx43 joint;
    Vec3 point;

    data_021cfe68 = *matrix_at(actor, FIELD_ACTOR_MATRIX_MODEL);
    func_02055d38(body, FIELD_ACTOR_BODY_ARG(actor));
    func_02054848(body, 0);
    func_02055d0c(body, matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_F), 0xf);
    func_02055d0c(body, matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_E), 0xe);
    func_02055d0c(body, matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_B), 0xb);
    func_02055d0c(body, &joint, 7);
    point = translation_of(&joint);
    func_0203f7d0((Vec3 *) at(actor, FIELD_ACTOR_POINT_JOINT_7), &point);
    func_02055d0c(body, &joint, 4);
    point = translation_of(&joint);
    func_0203f7d0((Vec3 *) at(actor, FIELD_ACTOR_POINT_JOINT_4), &point);
    func_02055d0c(body, &joint, 0x10);
    point = translation_of(&joint);
    func_0203f7d0(&actor->effect_point, &point);

    *matrix_at(actor, FIELD_ACTOR_MODEL_A + FIELD_ACTOR_MODEL_MATRIX) = *matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_F);
    func_02055d38(at(actor, FIELD_ACTOR_MODEL_A), FIELD_ACTOR_BODY_ARG(actor));
    func_02055e7c(at(actor, FIELD_ACTOR_MODEL_A), NULL);
    if (func_0205e138(at(actor, FIELD_ACTOR_PART_B), 1) < 0x9e) {
        *matrix_at(actor, FIELD_ACTOR_MODEL_B + FIELD_ACTOR_MODEL_MATRIX) = *matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_F);
        func_02055d38(at(actor, FIELD_ACTOR_MODEL_B), FIELD_ACTOR_BODY_ARG(actor));
        func_02055e7c(at(actor, FIELD_ACTOR_MODEL_B), NULL);
    }
    if (func_0205ddd4(at(actor, FIELD_ACTOR_PART_C)) != 0x4b) {
        *matrix_at(actor, FIELD_ACTOR_MODEL_C + FIELD_ACTOR_MODEL_MATRIX) = *matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_F);
        func_02055d38(at(actor, FIELD_ACTOR_MODEL_C), FIELD_ACTOR_BODY_ARG(actor));
        func_02055e7c(at(actor, FIELD_ACTOR_MODEL_C), NULL);
    }

    if (FIELD_ACTOR_MARK(actor) > 0) {
        Vec3 ground;
        func_02055d0c(body, &joint, 1);
        point = translation_of(&joint);
        func_0203f7d0(&ground, &point);
        func_020acbc8(&ground, FIELD_ACTOR_MARK(actor));
    }

    if (func_0200f290(actor, 0)) {
        Mtx43 placement;
        int mode;
        func_0205e954(actor->held, matrix_at(actor, FIELD_ACTOR_MATRIX_JOINT_E));
        switch (func_0200fbe0(actor)) {
            case 4:
            case 10:
                mode = 2;
                break;
            case 1:
            case 5:
            case 9:
                mode = 1;
                break;
            default:
                mode = 0;
                break;
        }
        func_0205e8f8(&placement, actor->held, (u32) mode);
        *matrix_at(actor, FIELD_ACTOR_MATRIX_HELD) = placement;
        if (func_0200fbe0(actor) == 4) {
            func_0205e8f8(&placement, actor->held, 3);
            *matrix_at(actor, FIELD_ACTOR_MATRIX_HELD_ALT) = placement;
        }
    }
}
CLEAN_AS(func_02005490, FieldActor_PlaceModel)

/* func_0200570c: placement mode 0: the start position is the position. */
void FieldActor_PlaceAtPosition(FieldActor *actor)
{
    actor->start_position = actor->position;
}
CLEAN_AS(func_0200570c, FieldActor_PlaceAtPosition)

/* func_02005730: after a node: FieldActor_NodeBefore at timing 1 for the next. */
void FieldActor_NodeAfter(NodeRenderState *state)
{
    state->node_callback = (u32) (uintptr_t) func_020058b4;
    state->node_timing = 1;
}
CLEAN_AS(func_02005730, FieldActor_NodeAfter)

/* func_02005740: a node's transform (func_02054f68). The head is turned by the actor's head
 * angles: about Y by the one at 0x45c (FieldActor.head_pitch), then about X by the one at
 * 0x45e (head_yaw), when either is not 0. With the actor known, the transform is applied
 * (func_0205490c), and at the root: during animations 0x82 and 0x83 the root is bent onto the
 * curved ground (its height less the radius, turned about X by the slope's angle); the root's
 * transform is applied (func_02054ed4) and the start position is the current matrix's
 * translation, at FieldActor_ModelY's height, on the curved ground. Then FieldActor_NodeAfter at
 * timing 3. */
void FieldActor_NodeTransform(NodeRenderState *state)
{
    func_02054f68(state, 0);
    FieldActor *actor = state->object->actor;
    if (state->command[1] == NODE_HEAD && actor != NULL) {
        int turn = actor->head_pitch;
        if (turn != 0 || actor->head_yaw != 0) {
            Mtx33 *rotation = &state->joint->rotation;
            Mtx33 step;
            MTX_RotY33_(&step, sin_of((u16) turn), cos_of((u16) turn));
            MTX_Concat33(rotation, &step, rotation);
            MTX_RotX33_(&step, sin_of((u16) actor->head_yaw), cos_of((u16) actor->head_yaw));
            MTX_Concat33(rotation, &step, rotation);
        }
    }

    actor = state->object->actor;
    if (actor != NULL) {
        u8 *body = at(actor, FIELD_ACTOR_BODY);
        func_0205490c(body, state);
        if (state->command[1] == NODE_ROOT) {
            if (actor->animation == 0x82 || actor->animation == 0x83) {
                NodeJoint *joint = state->joint;
                Vec3 bent = joint->translation;
                Vec3 flat = joint->translation;
                int slope = func_0203f844(&bent, &flat);
                joint->translation.z = bent.z;
                joint->translation.y = bent.y - func_0203f758();
                if (slope != 0) {
                    Mtx33 step;
                    MTX_RotX33_(&step, sin_of((u16) slope), cos_of((u16) slope));
                    MTX_Concat33(&joint->rotation, &step, &joint->rotation);
                }
            }
            func_02054ed4(body, state, 0);
            Mtx43 current = data_021cfe68;
            Vec3 root = translation_of(&current);
            root.y = FieldActor_ModelY(actor, root.y);
            func_0203f7d0(&actor->start_position, &root);
        }
    }
    state->node_callback = (u32) (uintptr_t) func_02005730;
    state->node_timing = 3;
}
CLEAN_AS(func_02005740, FieldActor_NodeTransform)

/* func_020058b4: before a node: func_02054988 with the body, when the actor is known; then
 * FieldActor_NodeTransform at timing 2. */
void FieldActor_NodeBefore(NodeRenderState *state)
{
    FieldActor *actor = state->object->actor;
    if (actor != NULL) {
        func_02054988(at(actor, FIELD_ACTOR_BODY), state);
    }
    state->node_callback = (u32) (uintptr_t) func_02005740;
    state->node_timing = 2;
}
CLEAN_AS(func_020058b4, FieldActor_NodeBefore)

/* func_020082ac: the pivot is the position taken back to the flat ground, the pitch the
 * ground's slope there; then the actor's model matrix (Actor_ModelMatrix) is kept at 0x298. */
void FieldActor_UpdateModelMatrix(FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    Mtx43 matrix;
    base->pitch = (u16) func_0203f8d0(&base->pivot, &base->position);
    Actor_ModelMatrix(base, &matrix);
    *matrix_at(actor, FIELD_ACTOR_MATRIX_MODEL) = matrix;
}
CLEAN_AS(func_020082ac, FieldActor_UpdateModelMatrix)
