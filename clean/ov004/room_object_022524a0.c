/* The room objects of vtable 0x022524a0 (room_object_022524a0.h). */
#include "room_object_022524a0.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject022524a0, state) == 0x844, "state");
static_assert(sizeof(RoomObject022524a0) == 0x848, "the size of one");

#define ROOM_OBJECT_022524A0_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* RoomObject_PlayAnimsFrom: stop at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The joint being drawn (NitroSystem's NNSG3dJntAnmResult), as NodeHookState.unk_B4 points to
 * it: its translation at 0x4c. */
typedef struct RoomObject022524a0Joint {
    u32 flags;
    u8 unk_04[0x48]; /* its scales and rotation */
    Vec3 translation;
} RoomObject022524a0Joint;

static_assert(offsetof(RoomObject022524a0Joint, translation) == 0x4c, "translation");

/* What func_02034270 tells of the ground at a point (func_0203423c releases it); 0x44 bytes. */
typedef struct RoomObject022524a0Ground {
    u8 unk_00[0x38];
    s32 unk_38; /* what func_020341c8 gives when asked with 0 */
    u8 unk_3c[8];
} RoomObject022524a0Ground;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257054;
extern MemberPointer data_ov004_02257214[ROOM_OBJECT_022524A0_STATE_COUNT];
extern const MemberPointer data_ov004_02250478, data_ov004_02250480;
extern u32 data_ov004_02257040;
extern MemberPointer data_ov004_02257204[ROOM_OBJECT_022524A0_STATE_COUNT];
extern const MemberPointer data_ov004_02250410, data_ov004_02250438;

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022524a0[];
extern const u8 data_ov004_0225254c[];

/* The main program's scratch matrix. */
extern Mtx43 data_021fbe48;

/* Advances the model's joint animation (the main program's model object at 0x538), and whether
 * that animation is at its end. */
extern void func_02054cdc(void *model);
extern int func_02056f94(void *anim);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1), straight
 * to func_020526b8. */
extern int func_02052738(unsigned int object, int state, int a2, int a3);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
/* The ground at a point, its value (unk_38 when asked with 0), and its release. */
extern int func_02034270(RoomObject022524a0Ground *out, Vec3 *at, int a, int b);
extern int func_020341c8(RoomObject022524a0Ground *ground, int a);
extern void func_0203423c(RoomObject022524a0Ground *ground);

static unsigned int RoomObject022524a0_address(RoomObject022524a0 *object)
{
    return (unsigned int) (uintptr_t) object;
}

static void RoomObject022524a0_set_vtables(RoomObject022524a0 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022524a0;
    object->base.receiver_vtable = data_ov004_0225254c;
}

/* func_ov004_0221412c (update of PLAYING): advances the joint animation; once it has ended,
 * requests IDLE and gives the answer, else 0. */
int RoomObject022524a0_UpdatePlaying(RoomObject022524a0 *object)
{
    func_02054cdc(object->base.unk_538);
    if (func_02056f94(object->base.joint_anim) == 0) {
        return 0;
    }
    return func_02052738(RoomObject022524a0_address(object), ROOM_OBJECT_022524A0_IDLE, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_0221412c, RoomObject022524a0_UpdatePlaying)

/* func_ov004_02214160 (entry of PLAYING): the node set's value 1, the animations of variant 0
 * once from the start, and the sound at 2. */
int RoomObject022524a0_EnterPlaying(RoomObject022524a0 *object)
{
    ByteSet_SetValue(&object->base.node_set, 1);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02214160, RoomObject022524a0_EnterPlaying)

/* func_ov004_02214198 (update of IDLE): when the switch was asked to change, requests
 * PLAYING. */
void RoomObject022524a0_UpdateIdle(RoomObject022524a0 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_02052738(RoomObject022524a0_address(object), ROOM_OBJECT_022524A0_PLAYING, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02214198, RoomObject022524a0_UpdateIdle)

/* func_ov004_022141c0 (entry of IDLE): the node set's value 0 and the animations of variant 0
 * once from the start. */
int RoomObject022524a0_EnterIdle(RoomObject022524a0 *object)
{
    ByteSet_SetValue(&object->base.node_set, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022141c0, RoomObject022524a0_EnterIdle)

/* _ZN18Obj_ov004_022524a019func_ov004_022141f0Ev: the state's update, through its table. */
void RoomObject022524a0_UpdateState(RoomObject022524a0 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_022524A0_STATE_COUNT] = {
        &data_ov004_02250478, /* RoomObject022524a0_UpdateIdle */
        &data_ov004_02250480, /* RoomObject022524a0_UpdatePlaying */
    };
    MemberTable_InitOnce(&data_ov004_02257054, data_ov004_02257214, updates, ROOM_OBJECT_022524A0_STATE_COUNT);
    if (object->state < ROOM_OBJECT_022524A0_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257214[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022524a019func_ov004_022141f0Ev, RoomObject022524a0_UpdateState)

/* func_ov004_0221425c (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given
 * `state` and `value`), then enters `state` if its entry (through a table) agrees; whether it
 * did. States 2 and above do not exist. */
int RoomObject022524a0_EnterState(RoomObject022524a0 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_022524A0_STATE_COUNT] = {
        &data_ov004_02250410, /* RoomObject022524a0_EnterIdle */
        &data_ov004_02250438, /* RoomObject022524a0_EnterPlaying */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257040, data_ov004_02257204, entries, ROOM_OBJECT_022524A0_STATE_COUNT);
    if (state < ROOM_OBJECT_022524A0_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257204[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221425c, RoomObject022524a0_EnterState)

/* func_ov004_022142e0 (vtable slot 0x6c, the model's hook after a node's description): for a
 * node of the node set while PLAYING, the joint's translation taken into the world by the
 * object's matrix (through the scratch matrix data_021fbe48, which keeps that copy); where the
 * ground there answers above 0, requests IDLE. */
void RoomObject022524a0_NodeGroundHook(RoomObject022524a0 *object, int node, NodeHookState *state)
{
    if (ByteSet_Contains(&object->base.node_set, node) == 0 || object->state != ROOM_OBJECT_022524A0_PLAYING) {
        return;
    }
    const RoomObject022524a0Joint *joint = state->unk_B4;
    Vec3 local = joint->translation;
    Vec3 world;
    RoomObject022524a0Ground ground;
    data_021fbe48 = object->base.matrix;
    MTX_MultVec43(&local, &data_021fbe48, &world);
    func_02034270(&ground, &world, 0, 0);
    if (func_020341c8(&ground, 0) > 0) {
        func_02052738(RoomObject022524a0_address(object), ROOM_OBJECT_022524A0_IDLE, SLOT_70_VALUE, 1);
    }
    func_0203423c(&ground);
}
CLEAN_AS(func_ov004_022142e0, RoomObject022524a0_NodeGroundHook)

/* func_ov004_02214370 (vtable slot 0x90, when it starts to vanish): the animations of variant
 * 0 once from the start. */
void RoomObject022524a0_OnVanish(RoomObject022524a0 *object)
{
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
}
CLEAN_AS(func_ov004_02214370, RoomObject022524a0_OnVanish)

/* func_ov004_0221438c (vtable slot 0x0c): the switch off, at once. */
int RoomObject022524a0_Vfunc0C(RoomObject022524a0 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221438c, RoomObject022524a0_Vfunc0C)

/* _ZN18Obj_ov004_022524a019func_ov004_022143a8Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject022524a0_Update(RoomObject022524a0 *object)
{
    RoomObject022524a0_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022524a019func_ov004_022143a8Ev, RoomObject022524a0_Update)

/* func_ov004_022143b8 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0, to play once from the start, and enters IDLE; done at once. */
int RoomObject022524a0_Start(RoomObject022524a0 *object)
{
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    object->base.vtable->vfunc_70(&object->base, ROOM_OBJECT_022524A0_IDLE, SLOT_70_VALUE);
    return 1;
}
CLEAN_AS(func_ov004_022143b8, RoomObject022524a0_Start)

/* func_ov004_022143e4 (the deleting destructor, vtable slot 0x44). */
RoomObject022524a0 *RoomObject022524a0_Delete(RoomObject022524a0 *object)
{
    RoomObject022524a0_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022143e4, RoomObject022524a0_Delete)

/* func_ov004_02214410 (the destructor, vtable slot 0x40). */
RoomObject022524a0 *RoomObject022524a0_Destroy(RoomObject022524a0 *object)
{
    RoomObject022524a0_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02214410, RoomObject022524a0_Destroy)

/* func_ov004_02214434 (the constructor): the base, then this class's vtables. Its state is
 * left as the allocation zeroed it (IDLE). */
RoomObject022524a0 *RoomObject022524a0_Construct(RoomObject022524a0 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject022524a0_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02214434, RoomObject022524a0_Construct)

/* func_ov004_02214458: a new one from the room's heap; nothing when it has no room. */
void RoomObject022524a0_Create(void)
{
    RoomObject022524a0 *object = RoomObject_Alloc(ROOM_OBJECT_022524A0_SIZE);
    if (object != NULL) {
        RoomObject022524a0_Construct(object);
    }
}
CLEAN_AS(func_ov004_02214458, RoomObject022524a0_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject022524a0's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject022524a0 *RoomObject022524a0_from_receiver(void *receiver)
{
    return (RoomObject022524a0 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a954: the deleting destructor, entered from the receiver part. */
RoomObject022524a0 *RoomObject022524a0Receiver_Delete(void *receiver)
{
    return RoomObject022524a0_Delete(RoomObject022524a0_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022524a0D0Ev, RoomObject022524a0Receiver_Delete)

/* func_ov004_0221a970: the destructor, entered from the receiver part. */
RoomObject022524a0 *RoomObject022524a0Receiver_Destroy(void *receiver)
{
    return RoomObject022524a0_Destroy(RoomObject022524a0_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022524a0D1Ev, RoomObject022524a0Receiver_Destroy)
