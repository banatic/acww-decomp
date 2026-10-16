/* The room objects of vtable 0x02252374 (room_object_02252374.h). */
#include "room_object_02252374.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/item_code.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject02252374, item_model) == 0x844, "item model");
static_assert(offsetof(RoomObject02252374, material_texture) == 0x848, "material texture");
static_assert(offsetof(RoomObject02252374, unk_870) == 0x870, "unk_870");
static_assert(offsetof(RoomObject02252374, starting) == 0x873, "starting");
static_assert(offsetof(RoomObject02252374, state) == 0x874, "state");
static_assert(sizeof(RoomObject02252374) == 0x878, "the size RoomObject02252374_Create allocates");
static_assert(sizeof(DesignModel) == 0x2c4, "the item model's size");

#define ROOM_OBJECT_02252374_SIZE 0x878
#define ROOM_OBJECT_02252374_ITEM_FIRST 0x3984
#define ROOM_OBJECT_02252374_ITEM_LAST 0x3d83
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257074;
extern MemberPointer data_ov004_02257254[ROOM_OBJECT_02252374_STATE_COUNT];
extern const MemberPointer data_ov004_022505e8, data_ov004_022505f8;
extern u32 data_ov004_022570a8;
extern MemberPointer data_ov004_02257234[ROOM_OBJECT_02252374_STATE_COUNT];
extern const MemberPointer data_ov004_02250520, data_ov004_02250528;

/* Whether each state shows the object on (for vtable slot 0x74): ON does, OFF not. */
extern const u8 data_ov004_02247664[ROOM_OBJECT_02252374_STATE_COUNT];

/* "w", the material the texture goes on, and "myD", the texture of its own file OFF puts on. */
extern const char data_ov004_022531c8[];
extern const char data_ov004_022531d4[];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252374[];
extern const u8 data_ov004_02252420[];

/* The item code of furniture `item` in `variant`. */
extern u16 func_0204bc50(int item, int variant);
/* The item a room item stands for (0x3984-0x3d83: 0x11a8 plus the code's distance in fours). */
extern void func_02061e2c(ItemCode *out, const ItemCode *item);
/* The heap of an entry of the pool data_ov004_02259698. */
extern Heap *func_0209d324(void *entry);
/* Loads the model of `*item` into `model`; and that model's resource. */
extern int func_0203d064(DesignModel *model, const u16 *item, void *unused);
extern unsigned int func_0203cfc8(DesignModel *model);
/* The index of the texture and of the palette named `name` in a texture file. */
extern int func_02057a40(void *file, const char *name);
extern int func_020579b8(void *file, const char *name);
/* Puts texture `tex_index` and palette `plt_index` of `texture` on the material named
 * `material` of `model`; whether it could. */
extern int func_020b9d3c(void *bind, G3dModel *model, const char *material, void *texture, int tex_index, int plt_index);
extern void *func_020b9e58(void *bind);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);

/* Vtable slot 0x70: RoomObject02252374_EnterState for this class. */
static void RoomObject02252374_switch_to(RoomObject02252374 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* The texture file of the furniture's archive. */
static void *RoomObject02252374_texture_file(RoomObject02252374 *object)
{
    return (void *) (uintptr_t) AnimSet_File28(FurnitureModel_Anims(&object->base.model_files));
}

/* func_ov004_02213d70 (update of OFF): the switch off, shown at once. */
void RoomObject02252374_UpdateOff(RoomObject02252374 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
}
CLEAN_AS(func_ov004_02213d70, RoomObject02252374_UpdateOff)

/* func_ov004_02213d84 (entry of OFF): the switch off, shown at once, and the texture "myD" of
 * its own texture file on "w"; unk_870 cleared when that went on. */
int RoomObject02252374_EnterOff(RoomObject02252374 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    int tex_index = func_02057a40(RoomObject02252374_texture_file(object), data_ov004_022531d4);
    int plt_index = func_020579b8(RoomObject02252374_texture_file(object), data_ov004_022531d4);
    G3dModel *model = object->base.model_resource;
    if (func_020b9d3c(object->material_texture, model, data_ov004_022531c8, RoomObject02252374_texture_file(object), tex_index,
                      plt_index) != 0) {
        object->unk_870 = 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_02213d84, RoomObject02252374_EnterOff)

/* func_ov004_02213e10 (update of ON): the switch on, shown at once. */
void RoomObject02252374_UpdateOn(RoomObject02252374 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
}
CLEAN_AS(func_ov004_02213e10, RoomObject02252374_UpdateOn)

/* func_ov004_02213e24 (entry of ON): the switch on, shown at once, and the loaded model's
 * texture on "w".
 * REQUIRES: the item model was loaded (without it func_0203cfc8 is handed NULL). */
int RoomObject02252374_EnterOn(RoomObject02252374 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    G3dModel *model = object->base.model_resource;
    void *texture = (void *) (uintptr_t) func_0203cfc8(object->item_model);
    func_020b9d3c(object->material_texture, model, data_ov004_022531c8, texture, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_02213e24, RoomObject02252374_EnterOn)

/* _ZN18Obj_ov004_0225237419func_ov004_02213e74Ev: the state's update, through its table. */
void RoomObject02252374_UpdateState(RoomObject02252374 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252374_STATE_COUNT] = {
        &data_ov004_022505e8, /* RoomObject02252374_UpdateOn */
        &data_ov004_022505f8, /* RoomObject02252374_UpdateOff */
    };
    MemberTable_InitOnce(&data_ov004_02257074, data_ov004_02257254, updates, ROOM_OBJECT_02252374_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252374_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257254[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225237419func_ov004_02213e74Ev, RoomObject02252374_UpdateState)

/* func_ov004_02213ee0 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given
 * `state` and `value`), then enters `state` if its entry (through a table) agrees; whether it
 * did. States 2 and above do not exist. */
int RoomObject02252374_EnterState(RoomObject02252374 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252374_STATE_COUNT] = {
        &data_ov004_02250520, /* RoomObject02252374_EnterOn */
        &data_ov004_02250528, /* RoomObject02252374_EnterOff */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_022570a8, data_ov004_02257234, entries, ROOM_OBJECT_02252374_STATE_COUNT);
    if (state < ROOM_OBJECT_02252374_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257234[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02213ee0, RoomObject02252374_EnterState)

/* func_ov004_02213f64 (vtable slot 0x74): whether `state` shows the object on (ON does); 0 for
 * a state that does not exist. */
u8 RoomObject02252374_StateIsOn(RoomObject02252374 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02252374_STATE_COUNT) {
        return data_ov004_02247664[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02213f64, RoomObject02252374_StateIsOn)

/* func_ov004_02213f78: requests ON for the object at its cell; the answer. */
int RoomObject02252374_RequestOn(RoomObject02252374 *object)
{
    return func_0205265c((unsigned int) (uintptr_t) object, ROOM_OBJECT_02252374_ON, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_02213f78, RoomObject02252374_RequestOn)

/* func_ov004_02213f8c: requests OFF for the object at its cell; the answer. */
int RoomObject02252374_RequestOff(RoomObject02252374 *object)
{
    return func_0205265c((unsigned int) (uintptr_t) object, ROOM_OBJECT_02252374_OFF, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_02213f8c, RoomObject02252374_RequestOff)

/* func_ov004_02213fa0 (vtable slot 0x8c): its model keeps a copy of its texture. */
int RoomObject02252374_KeepsTextureCopy(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213fa0, RoomObject02252374_KeepsTextureCopy)

/* func_ov004_02213fa4 (vtable slot 0x0c) */
int RoomObject02252374_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213fa4, RoomObject02252374_Vfunc0C)

/* _ZN18Obj_ov004_0225237419func_ov004_02213fa8Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject02252374_Update(RoomObject02252374 *object)
{
    RoomObject02252374_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225237419func_ov004_02213fa8Ev, RoomObject02252374_Update)

/* func_ov004_02213fb8 (vtable slot 0x7c, once the model is bound): for an item code in the
 * range, loads the model of the item it stands for (0x2c4 bytes from the heap of its pool
 * entry) and enters the state its switch says (ON when on, OFF when off); done at once.
 * QUIRK: ON is then entered in any case, so with the switch off OFF's entry runs and is undone
 * at once; and for a code outside the range ON is entered without a loaded model (see
 * RoomObject02252374_EnterOn). */
int RoomObject02252374_Start(RoomObject02252374 *object)
{
    object->starting = 1;
    ItemCode item = func_0204bc50(RoomObject_Number(&object->base), 0);
    if (item >= ROOM_OBJECT_02252374_ITEM_FIRST && item <= ROOM_OBJECT_02252374_ITEM_LAST) {
        ItemCode shown;
        func_02061e2c(&shown, &item);
        Heap *heap = func_0209d324((void *) (uintptr_t) RoomObject_PoolEntry(&object->base));
        object->item_model = Heap_Alloc(heap, sizeof(DesignModel));
        func_0203d064(object->item_model, &shown, NULL);
        if (Switch_Value(&object->base.light_switch) != 0) {
            RoomObject02252374_switch_to(object, ROOM_OBJECT_02252374_ON);
        } else {
            RoomObject02252374_switch_to(object, ROOM_OBJECT_02252374_OFF);
        }
    }
    RoomObject02252374_switch_to(object, ROOM_OBJECT_02252374_ON);
    object->starting = 0;
    return 1;
}
CLEAN_AS(func_ov004_02213fb8, RoomObject02252374_Start)

static void RoomObject02252374_set_vtables(RoomObject02252374 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252374;
    object->base.receiver_vtable = data_ov004_02252420;
}

/* func_ov004_02214070 (the deleting destructor, vtable slot 0x44).
 * QUIRK: neither the item model nor the material texture binding is taken down. */
RoomObject02252374 *RoomObject02252374_Delete(RoomObject02252374 *object)
{
    RoomObject02252374_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02214070, RoomObject02252374_Delete)

/* func_ov004_0221409c (the destructor, vtable slot 0x40); the same QUIRK. */
RoomObject02252374 *RoomObject02252374_Destroy(RoomObject02252374 *object)
{
    RoomObject02252374_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221409c, RoomObject02252374_Destroy)

/* func_ov004_022140c0 (the constructor): builds the material texture binding; no item model;
 * unk_870 and unk_871 cleared. Its other fields are left as the allocation zeroed them. */
RoomObject02252374 *RoomObject02252374_Construct(RoomObject02252374 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252374_set_vtables(object);
    func_020b9e58(object->material_texture);
    object->item_model = NULL;
    object->unk_871 = 0;
    object->unk_870 = object->unk_871;
    return object;
}
CLEAN_AS(func_ov004_022140c0, RoomObject02252374_Construct)

/* func_ov004_02214110: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252374_Create(void)
{
    RoomObject02252374 *object = RoomObject_Alloc(ROOM_OBJECT_02252374_SIZE);
    if (object != NULL) {
        RoomObject02252374_Construct(object);
    }
}
CLEAN_AS(func_ov004_02214110, RoomObject02252374_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252374's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252374 *RoomObject02252374_from_receiver(void *receiver)
{
    return (RoomObject02252374 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a98c: the deleting destructor, entered from the receiver part. */
RoomObject02252374 *RoomObject02252374Receiver_Delete(void *receiver)
{
    return RoomObject02252374_Delete(RoomObject02252374_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252374D0Ev, RoomObject02252374Receiver_Delete)

/* func_ov004_0221a9a8: the destructor, entered from the receiver part. */
RoomObject02252374 *RoomObject02252374Receiver_Destroy(void *receiver)
{
    return RoomObject02252374_Destroy(RoomObject02252374_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252374D1Ev, RoomObject02252374Receiver_Destroy)
