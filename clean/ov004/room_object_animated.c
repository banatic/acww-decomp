/* The room objects that play their animations from the start (room_object_animated.h). */
#include "room_object_animated.h"

#include "clean.h"
#include "room_object_anims.h"
#include "room_object_life.h"

static_assert(offsetof(AnimatedRoomObject, start_frame) == 0x844, "start frame");
static_assert(sizeof(AnimatedRoomObject) == 0x848, "the size AnimatedRoomObject_Create allocates");

#define ANIMATED_ROOM_OBJECT_SIZE 0x848

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022526f8[];
extern const u8 data_ov004_022527a4[];

extern int func_02062b14(void);

/* func_ov004_022115ac (vtable slot 0x0c) */
int AnimatedRoomObject_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022115ac, AnimatedRoomObject_Vfunc0C)

/* func_ov004_022115b0 (vtable slot 0x80, each frame while neither appearing nor vanishing) */
int AnimatedRoomObject_Vfunc80(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022115b0, AnimatedRoomObject_Vfunc80)

/* func_ov004_022115b4 (vtable slot 0x7c, once the model is bound): its animations of variant 0
 * from the frame func_02062b14 gives (kept in start_frame, cut to 16 bits), advanced once;
 * done at once. */
int AnimatedRoomObject_StartAnims(AnimatedRoomObject *object)
{
    object->start_frame = func_02062b14();
    RoomObject_LoadAnims(&object->base, 0, 0, 0, (u16) object->start_frame);
    RoomObject_AdvanceAnims(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_022115b4, AnimatedRoomObject_StartAnims)

static void set_vtables(AnimatedRoomObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022526f8;
    object->base.receiver_vtable = data_ov004_022527a4;
}

/* func_ov004_022115ec (the deleting destructor, vtable slot 0x44) */
AnimatedRoomObject *AnimatedRoomObject_Delete(AnimatedRoomObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022115ec, AnimatedRoomObject_Delete)

/* func_ov004_02211618 (the destructor, vtable slot 0x40) */
AnimatedRoomObject *AnimatedRoomObject_Destroy(AnimatedRoomObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02211618, AnimatedRoomObject_Destroy)

/* func_ov004_0221163c (the constructor). start_frame is left as the allocation zeroed it. */
AnimatedRoomObject *AnimatedRoomObject_Construct(AnimatedRoomObject *object)
{
    RoomObject_ConstructBase(&object->base);
    set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_0221163c, AnimatedRoomObject_Construct)

/* func_ov004_02211660: a new one from the room's heap; nothing when it has no room. */
void AnimatedRoomObject_Create(void)
{
    AnimatedRoomObject *object = RoomObject_Alloc(ANIMATED_ROOM_OBJECT_SIZE);
    if (object != NULL) {
        AnimatedRoomObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_02211660, AnimatedRoomObject_Create)
