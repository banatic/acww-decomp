/* The room objects of vtable 0x02250d30 (room_object_02250d30.h). */
#include "room_object_02250d30.h"

#include "clean.h"
#include "room_object_life.h"
#include "room_preview.h"

static_assert(offsetof(RoomObject02250d30, unk_844) == 0x844, "unk_844");
static_assert(sizeof(RoomObject02250d30) == 0x848, "the size RoomObject02250d30_Create allocates");

#define ROOM_OBJECT_02250D30_SIZE 0x848

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02250d30[];
extern const u8 data_ov004_02250ddc[];

/* func_ov004_022126b0 (vtable slot 0x0c) */
int RoomObject02250d30_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022126b0, RoomObject02250d30_Vfunc0C)

/* func_ov004_022126b4 (vtable slot 0x80, each frame while neither appearing nor vanishing) */
int RoomObject02250d30_Vfunc80(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022126b4, RoomObject02250d30_Vfunc80)

/* func_ov004_022126b8 (vtable slot 0x7c, once the model is bound): keeps the word at 0x10 of
 * data_ov004_022596b0, cut to 16 bits; done at once. */
int RoomObject02250d30_Start(RoomObject02250d30 *object)
{
    object->unk_844 = (u16) RoomPreview_Number(RoomPreview_Get());
    return 1;
}
CLEAN_AS(func_ov004_022126b8, RoomObject02250d30_Start)

static void set_vtables(RoomObject02250d30 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02250d30;
    object->base.receiver_vtable = data_ov004_02250ddc;
}

/* func_ov004_022126d4 (the deleting destructor, vtable slot 0x44) */
RoomObject02250d30 *RoomObject02250d30_Delete(RoomObject02250d30 *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022126d4, RoomObject02250d30_Delete)

/* func_ov004_02212700 (the destructor, vtable slot 0x40) */
RoomObject02250d30 *RoomObject02250d30_Destroy(RoomObject02250d30 *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02212700, RoomObject02250d30_Destroy)

/* func_ov004_02212724 (the constructor). unk_844 is left as the allocation zeroed it. */
RoomObject02250d30 *RoomObject02250d30_Construct(RoomObject02250d30 *object)
{
    RoomObject_ConstructBase(&object->base);
    set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02212724, RoomObject02250d30_Construct)

/* func_ov004_02212748: a new one from the room's heap; nothing when it has no room. */
void RoomObject02250d30_Create(void)
{
    RoomObject02250d30 *object = RoomObject_Alloc(ROOM_OBJECT_02250D30_SIZE);
    if (object != NULL) {
        RoomObject02250d30_Construct(object);
    }
}
CLEAN_AS(func_ov004_02212748, RoomObject02250d30_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02250d30's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02250d30 *RoomObject02250d30_from_receiver(void *receiver)
{
    return (RoomObject02250d30 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221abbc: the deleting destructor, entered from the receiver part. */
RoomObject02250d30 *RoomObject02250d30Receiver_Delete(void *receiver)
{
    return RoomObject02250d30_Delete(RoomObject02250d30_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250d30D0Ev, RoomObject02250d30Receiver_Delete)

/* func_ov004_0221abd8: the destructor, entered from the receiver part. */
RoomObject02250d30 *RoomObject02250d30Receiver_Destroy(void *receiver)
{
    return RoomObject02250d30_Destroy(RoomObject02250d30_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250d30D1Ev, RoomObject02250d30Receiver_Destroy)
