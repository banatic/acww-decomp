/* The room objects of vtable 0x02252824 (room_object_02252824.h). */
#include "room_object_02252824.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject02252824, state) == 0x844, "state");
static_assert(sizeof(RoomObject02252824) == 0x848, "the size RoomObject02252824_Create allocates");

#define ROOM_OBJECT_02252824_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* start again at the end */
#define ANIM_MODE_ONCE 1   /* stop at the end */
#define ANIM_MODE_3 3      /* the animations' mode 3 */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257018;
extern MemberPointer data_ov004_022574ac[ROOM_OBJECT_02252824_STATE_COUNT];
extern const MemberPointer data_ov004_02250078, data_ov004_022502f8, data_ov004_02250038, data_ov004_02250378;
extern u32 data_ov004_0225706c;
extern MemberPointer data_ov004_0225748c[ROOM_OBJECT_02252824_STATE_COUNT];
extern const MemberPointer data_ov004_022502a8, data_ov004_02250250, data_ov004_022502d8, data_ov004_02250158;

/* Whether each state shows the object on (for vtable slot 0x74): TURNING_ON and ON do. */
extern const u8 data_ov004_02247690[ROOM_OBJECT_02252824_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252824[];
extern const u8 data_ov004_022528d0[];

/* The model object at 0x538: whether it has a joint animation, its advance, and its render
 * object. */
extern u32 func_02054ec4(void *model);
extern void func_02054cdc(void *model);
extern void *func_02055e00(void *model);
/* An animation of RoomObject.anims: its advance, whether it is at its end, and playing `file`
 * on `model` by `mode` and `speed` from `frame`. */
extern void func_02056ffc(FurnitureAnim *anim);
extern int func_02056f94(FurnitureAnim *anim);
extern void func_02056440(FurnitureAnim *anim, void *model, const AnimFile *file, int mode, int speed, int frame);
/* Binding the animations to the model (each given the heap of the object's pool entry), as
 * RoomObject_LoadAnims does. */
extern int func_0209d324(void *entry);
extern int func_020564d0(FurnitureAnim *anim, G3dModel *resource, int a2);
extern int func_0205650c(FurnitureAnim *anim, G3dModel *resource, int a2);
extern int func_02055140(void *model, int a1);
extern void func_02056478(FurnitureAnim *anim, const AnimFile *file, u8 mode, int speed, u16 frame);
extern void func_02056424(FurnitureAnim *anim, const AnimFile *file, u8 *texture, u8 mode, int speed, u16 frame);
extern void func_02055060(void *model, const AnimFile *file, int mode, int speed, int frame, int a5);
extern void func_02055050(void *model);
extern void func_020563dc(FurnitureAnim *anim, void *model);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);

static unsigned int RoomObject02252824_address(RoomObject02252824 *object)
{
    return (unsigned int) (uintptr_t) object;
}

/* Vtable slot 0x70: RoomObject02252824_EnterState for this class. */
static void RoomObject02252824_switch_to(RoomObject02252824 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

static AnimSet *RoomObject02252824_anims(RoomObject02252824 *object)
{
    return FurnitureModel_Anims(&object->base.model_files);
}

static const AnimFile *RoomObject02252824_file(int address)
{
    return (const AnimFile *) (uintptr_t) (u32) address;
}

static FurnitureAnim *RoomObject02252824_material(RoomObject02252824 *object)
{
    return &object->base.anims[ROOM_ANIM_MATERIAL];
}

/* Advances a bound animation, giving its frame to its target; whether it is at its end. */
static int RoomObject02252824_advance(FurnitureAnim *anim)
{
    func_02056ffc(anim);
    *anim->target = anim->frame;
    return func_02056f94(anim);
}

/* The common update of TURNING_ON and TURNING_OFF: the material animation advanced while it is
 * bound; then `next` once it has ended, or at once when it is not bound. */
static void RoomObject02252824_run_material(RoomObject02252824 *object, int next)
{
    FurnitureAnim *anim = RoomObject02252824_material(object);
    if (FurnitureAnim_Target(anim) != NULL) {
        if (RoomObject02252824_advance(anim) != 0) {
            RoomObject02252824_switch_to(object, next);
        }
    } else {
        RoomObject02252824_switch_to(object, next);
    }
}

/* func_ov004_02214474 (update of TURNING_OFF): the switch off, at once; then OFF once the
 * material animation has ended. */
void RoomObject02252824_UpdateTurningOff(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject02252824_run_material(object, ROOM_OBJECT_02252824_OFF);
}
CLEAN_AS(func_ov004_02214474, RoomObject02252824_UpdateTurningOff)

/* func_ov004_022144e0 (entry of TURNING_OFF): the switch off, at once; the material animation,
 * when the archive has one and it is bound, in mode 3 from its last frame; the sound at 4.
 * QUIRK: a file without frames starts from 0xffff. */
int RoomObject02252824_EnterTurningOff(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    if (AnimSet_Anim08(RoomObject02252824_anims(object), 0)) {
        const AnimFile *file = RoomObject02252824_file(AnimSet_Anim08(RoomObject02252824_anims(object), 0));
        FurnitureAnim *anim = RoomObject02252824_material(object);
        if (FurnitureAnim_Target(anim) != NULL) {
            func_02056440(anim, func_02055e00(object->base.unk_538), file, ANIM_MODE_3, ONE, (u16) (file->frames - 1));
        }
    }
    RoomObject_PlaySound2(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_022144e0, RoomObject02252824_EnterTurningOff)

/* func_ov004_02214568 (update of ON): func_020537a8 of its number and the sound at 0; when the
 * switch was asked to change, requests TURNING_OFF and gives the answer, else 0. */
int RoomObject02252824_UpdateOn(RoomObject02252824 *object)
{
    RoomObject_Lookup020537a8(&object->base);
    RoomObject_PlaySound0(&object->base);
    if (Switch_IsPending(&object->base.light_switch) == 0) {
        return 0;
    }
    return func_0205265c(RoomObject02252824_address(object), ROOM_OBJECT_02252824_TURNING_OFF, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_02214568, RoomObject02252824_UpdateOn)

/* func_ov004_02214598 (entry of ON): the switch on, at once; the material animation, when the
 * archive has one, once from its last frame, which holds it there (bound or not).
 * QUIRK: a file without frames starts from 0xffff. */
int RoomObject02252824_EnterOn(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    if (AnimSet_Anim08(RoomObject02252824_anims(object), 0)) {
        const AnimFile *file = RoomObject02252824_file(AnimSet_Anim08(RoomObject02252824_anims(object), 0));
        func_02056440(RoomObject02252824_material(object), func_02055e00(object->base.unk_538), file, ANIM_MODE_ONCE, ONE,
                      (u16) (file->frames - 1));
    }
    return 1;
}
CLEAN_AS(func_ov004_02214598, RoomObject02252824_EnterOn)

/* func_ov004_02214610 (update of TURNING_ON): the switch on, at once, and the sound at 0; then
 * ON once the material animation has ended. */
void RoomObject02252824_UpdateTurningOn(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound0(&object->base);
    RoomObject02252824_run_material(object, ROOM_OBJECT_02252824_ON);
}
CLEAN_AS(func_ov004_02214610, RoomObject02252824_UpdateTurningOn)

/* func_ov004_02214680 (entry of TURNING_ON): the switch on, at once; the material animation,
 * when the archive has one and it is bound, once from the start; the sound at 2. */
int RoomObject02252824_EnterTurningOn(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    if (AnimSet_Anim08(RoomObject02252824_anims(object), 0)) {
        const AnimFile *file = RoomObject02252824_file(AnimSet_Anim08(RoomObject02252824_anims(object), 0));
        FurnitureAnim *anim = RoomObject02252824_material(object);
        if (FurnitureAnim_Target(anim) != NULL) {
            func_02056440(anim, func_02055e00(object->base.unk_538), file, ANIM_MODE_ONCE, ONE, 0);
        }
    }
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02214680, RoomObject02252824_EnterTurningOn)

/* func_ov004_02214704 (update of OFF): when the switch was asked to change, requests
 * TURNING_ON. */
void RoomObject02252824_UpdateOff(RoomObject02252824 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_0205265c(RoomObject02252824_address(object), ROOM_OBJECT_02252824_TURNING_ON, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02214704, RoomObject02252824_UpdateOff)

/* func_ov004_0221472c (entry of OFF): the switch off, at once; the material animation, when
 * the archive has one, in mode 3 from its first frame (bound or not). */
int RoomObject02252824_EnterOff(RoomObject02252824 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    if (AnimSet_Anim08(RoomObject02252824_anims(object), 0)) {
        const AnimFile *file = RoomObject02252824_file(AnimSet_Anim08(RoomObject02252824_anims(object), 0));
        func_02056440(RoomObject02252824_material(object), func_02055e00(object->base.unk_538), file, ANIM_MODE_3, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221472c, RoomObject02252824_EnterOff)

/* _ZN18Obj_ov004_0225282419func_ov004_0221479cEv: the state's update, through its table. */
void RoomObject02252824_UpdateState(RoomObject02252824 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252824_STATE_COUNT] = {
        &data_ov004_02250078, /* RoomObject02252824_UpdateOff */
        &data_ov004_022502f8, /* RoomObject02252824_UpdateTurningOn */
        &data_ov004_02250038, /* RoomObject02252824_UpdateOn */
        &data_ov004_02250378, /* RoomObject02252824_UpdateTurningOff */
    };
    MemberTable_InitOnce(&data_ov004_02257018, data_ov004_022574ac, updates, ROOM_OBJECT_02252824_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252824_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022574ac[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225282419func_ov004_0221479cEv, RoomObject02252824_UpdateState)

/* func_ov004_02214828 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given
 * `state` and `value`), then enters `state` if its entry (through a table) agrees; whether it
 * did. States 4 and above do not exist. */
int RoomObject02252824_EnterState(RoomObject02252824 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252824_STATE_COUNT] = {
        &data_ov004_022502a8, /* RoomObject02252824_EnterOff */
        &data_ov004_02250250, /* RoomObject02252824_EnterTurningOn */
        &data_ov004_022502d8, /* RoomObject02252824_EnterOn */
        &data_ov004_02250158, /* RoomObject02252824_EnterTurningOff */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225706c, data_ov004_0225748c, entries, ROOM_OBJECT_02252824_STATE_COUNT);
    if (state < ROOM_OBJECT_02252824_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225748c[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02214828, RoomObject02252824_EnterState)

/* func_ov004_022148c8 (vtable slot 0x74): whether `state` shows the object on (TURNING_ON and
 * ON do); 0 for a state that does not exist. */
u8 RoomObject02252824_StateIsOn(RoomObject02252824 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02252824_STATE_COUNT) {
        return data_ov004_02247690[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_022148c8, RoomObject02252824_StateIsOn)

/* func_ov004_022148dc (vtable slot 0x0c) */
int RoomObject02252824_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022148dc, RoomObject02252824_Vfunc0C)

/* _ZN18Obj_ov004_0225282419func_ov004_022148e0Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update, then the joint animation (when the model has
 * one) and the bound texture coordinate, pattern and visibility animations advanced, each
 * giving its frame to its target. */
int RoomObject02252824_Update(RoomObject02252824 *object)
{
    RoomObject02252824_UpdateState(object);
    if (func_02054ec4(object->base.unk_538) != 0) {
        func_02054cdc(object->base.unk_538);
    }
    static const int others[3] = {ROOM_ANIM_TEXCOORD, ROOM_ANIM_PATTERN, ROOM_ANIM_VISIBILITY};
    for (int i = 0; i < 3; i++) {
        FurnitureAnim *anim = &object->base.anims[others[i]];
        if (FurnitureAnim_Target(anim) != NULL) {
            func_02056ffc(anim);
            *anim->target = anim->frame;
        }
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225282419func_ov004_022148e0Ev, RoomObject02252824_Update)

/* func_ov004_02214988 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 the archive has (each only when its binding, given the heap of the object's pool
 * entry, succeeds), in the order visibility, texture coordinates, joints, patterns and
 * material; all loop from frame 0 at normal speed but the material one, in mode 3. Then ON
 * when the switch is on and func_ov004_0223c10c says no, else OFF; done at once. */
int RoomObject02252824_Start(RoomObject02252824 *object)
{
    RoomObject *base = &object->base;
    void *entry = (void *) (uintptr_t) (u32) RoomObject_PoolEntry(base);
    if (AnimSet_Anim10(RoomObject02252824_anims(object), 0)) {
        FurnitureAnim *anim = &base->anims[ROOM_ANIM_VISIBILITY];
        G3dModel *resource = base->model_resource;
        if (func_020564d0(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, RoomObject02252824_file(AnimSet_Anim10(RoomObject02252824_anims(object), 0)), ANIM_MODE_LOOP,
                          ONE, 0);
            func_020563dc(anim, func_02055e00(base->unk_538));
        }
    }
    if (AnimSet_Anim18(RoomObject02252824_anims(object), 0)) {
        FurnitureAnim *anim = &base->anims[ROOM_ANIM_TEXCOORD];
        G3dModel *resource = base->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, RoomObject02252824_file(AnimSet_Anim18(RoomObject02252824_anims(object), 0)), ANIM_MODE_LOOP,
                          ONE, 0);
            func_020563dc(anim, func_02055e00(base->unk_538));
        }
    }
    if (AnimSet_Anim00(RoomObject02252824_anims(object), 0)) {
        if (func_02055140(base->unk_538, func_0209d324(entry))) {
            func_02055060(base->unk_538, RoomObject02252824_file(AnimSet_Anim00(RoomObject02252824_anims(object), 0)),
                          ANIM_MODE_LOOP, ONE, 0, 0);
            func_02055050(base->unk_538);
        }
    }
    if (AnimSet_Anim20(RoomObject02252824_anims(object), 0)) {
        FurnitureAnim *anim = &base->anims[ROOM_ANIM_PATTERN];
        G3dModel *resource = base->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            const AnimFile *file = RoomObject02252824_file(AnimSet_Anim20(RoomObject02252824_anims(object), 0));
            func_02056424(anim, file, FurnitureModel_Texture(&base->model_files), ANIM_MODE_LOOP, ONE, 0);
            func_020563dc(anim, func_02055e00(base->unk_538));
        }
    }
    if (AnimSet_Anim08(RoomObject02252824_anims(object), 0)) {
        FurnitureAnim *anim = &base->anims[ROOM_ANIM_MATERIAL];
        G3dModel *resource = base->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, RoomObject02252824_file(AnimSet_Anim08(RoomObject02252824_anims(object), 0)), ANIM_MODE_3, ONE,
                          0);
            func_020563dc(anim, func_02055e00(base->unk_538));
        }
    }
    if (Switch_Value(&base->light_switch) != 0 && func_ov004_0223c10c() == 0) {
        RoomObject02252824_switch_to(object, ROOM_OBJECT_02252824_ON);
    } else {
        RoomObject02252824_switch_to(object, ROOM_OBJECT_02252824_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02214988, RoomObject02252824_Start)

static void RoomObject02252824_set_vtables(RoomObject02252824 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252824;
    object->base.receiver_vtable = data_ov004_022528d0;
}

/* func_ov004_02214bc0 (the deleting destructor, vtable slot 0x44). */
RoomObject02252824 *RoomObject02252824_Delete(RoomObject02252824 *object)
{
    RoomObject02252824_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02214bc0, RoomObject02252824_Delete)

/* func_ov004_02214bec (the destructor, vtable slot 0x40). */
RoomObject02252824 *RoomObject02252824_Destroy(RoomObject02252824 *object)
{
    RoomObject02252824_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02214bec, RoomObject02252824_Destroy)

/* func_ov004_02214c10 (the constructor): the base, then this class's vtables. Its state is
 * left as the allocation zeroed it (OFF). */
RoomObject02252824 *RoomObject02252824_Construct(RoomObject02252824 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252824_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02214c10, RoomObject02252824_Construct)

/* func_ov004_02214c34: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252824_Create(void)
{
    RoomObject02252824 *object = RoomObject_Alloc(ROOM_OBJECT_02252824_SIZE);
    if (object != NULL) {
        RoomObject02252824_Construct(object);
    }
}
CLEAN_AS(func_ov004_02214c34, RoomObject02252824_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252824's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252824 *RoomObject02252824_from_receiver(void *receiver)
{
    return (RoomObject02252824 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a91c: the deleting destructor, entered from the receiver part. */
RoomObject02252824 *RoomObject02252824Receiver_Delete(void *receiver)
{
    return RoomObject02252824_Delete(RoomObject02252824_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252824D0Ev, RoomObject02252824Receiver_Delete)

/* func_ov004_0221a938: the destructor, entered from the receiver part. */
RoomObject02252824 *RoomObject02252824Receiver_Destroy(void *receiver)
{
    return RoomObject02252824_Destroy(RoomObject02252824_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252824D1Ev, RoomObject02252824Receiver_Destroy)
