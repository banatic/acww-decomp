/* The room's floor (room_object_02250e5c.h). */
#include "room_object_02250e5c.h"

#include "clean.h"
#include "room_object_life.h"
#include "main/item_texture.h"
#include "main/vram_copy_task.h"
#include "room_preview.h"

static_assert(offsetof(RoomObject02250e5c, unk_846) == 0x846, "unk_846");
static_assert(offsetof(RoomObject02250e5c, material_texture) == 0x848, "material texture");
static_assert(sizeof(RoomObject02250e5c) == 0x870, "the size RoomObject02250e5c_Create allocates");

#define ROOM_OBJECT_02250E5C_SIZE 0x870
#define FLOOR_DRAWN_FRAMES 2
#define CARPET_FIRST 0x1144 /* the item code of carpet 0 */
#define CARPET_COUNT 0x44

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02250e5c[];
extern const u8 data_ov004_02250f08[];

/* "m_dummy_floor", the material the carpet goes on. */
extern const char data_ov004_02253190[];

/* func_ov004_02212764 (vtable slot 0x88): drawn once unk_846 is 2 or more. */
int RoomObject02250e5c_CanDraw(RoomObject02250e5c *object)
{
    return object->unk_846 >= FLOOR_DRAWN_FRAMES;
}
CLEAN_AS(func_ov004_02212764, RoomObject02250e5c_CanDraw)

/* func_ov004_02212778 (vtable slot 0x0c) */
int RoomObject02250e5c_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02212778, RoomObject02250e5c_Vfunc0C)

/* func_ov004_0221277c (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * counts the frames since the carpet was put on, up to 2. */
int RoomObject02250e5c_Update(RoomObject02250e5c *object)
{
    if (object->unk_846 < FLOOR_DRAWN_FRAMES) {
        object->unk_846++;
    }
    return 1;
}
CLEAN_AS(func_ov004_0221277c, RoomObject02250e5c_Update)

/* func_ov004_02212794 (vtable slot 0x7c, once the model is bound): keeps the room's carpet
 * number, loads that carpet into the room's floor texture file and puts its texture on
 * "m_dummy_floor"; done when the material took it. */
int RoomObject02250e5c_Start(RoomObject02250e5c *object)
{
    object->unk_844 = (u16) RoomPreview_Number(RoomPreview_Get());
    object->unk_846 = 0;
    u16 item = object->unk_844 < CARPET_COUNT ? (u16) (object->unk_844 + CARPET_FIRST) : CARPET_FIRST;
    CarpetTexture_Load(RoomPreview_CarpetFile(RoomPreview_Get()), &item);
    G3dModel *model = object->base.model_resource;
    void *texture = CarpetTexture_Textures(RoomPreview_CarpetFile(RoomPreview_Get()));
    return VramCopyMaterial_Queue(&object->material_texture, (const u8 *) model, data_ov004_02253190, texture, 0, 0) != 0;
}
CLEAN_AS(func_ov004_02212794, RoomObject02250e5c_Start)

static void RoomObject02250e5c_set_vtables(RoomObject02250e5c *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02250e5c;
    object->base.receiver_vtable = data_ov004_02250f08;
}

/* func_ov004_02212820 (the deleting destructor, vtable slot 0x44).
 * QUIRK: the material texture binding at 0x848 the constructor built is not taken down. */
RoomObject02250e5c *RoomObject02250e5c_Delete(RoomObject02250e5c *object)
{
    RoomObject02250e5c_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212820, RoomObject02250e5c_Delete)

/* func_ov004_0221284c (the destructor, vtable slot 0x40); the same QUIRK. */
RoomObject02250e5c *RoomObject02250e5c_Destroy(RoomObject02250e5c *object)
{
    RoomObject02250e5c_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221284c, RoomObject02250e5c_Destroy)

/* func_ov004_02212870 (the constructor). Its other fields are left as the allocation zeroed
 * them. */
RoomObject02250e5c *RoomObject02250e5c_Construct(RoomObject02250e5c *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02250e5c_set_vtables(object);
    VramCopyMaterial_Construct(&object->material_texture);
    return object;
}
CLEAN_AS(func_ov004_02212870, RoomObject02250e5c_Construct)

/* func_ov004_022128a0: a new floor from the room's heap; nothing when it has no room. */
void RoomObject02250e5c_Create(void)
{
    RoomObject02250e5c *object = RoomObject_Alloc(ROOM_OBJECT_02250E5C_SIZE);
    if (object != NULL) {
        RoomObject02250e5c_Construct(object);
    }
}
CLEAN_AS(func_ov004_022128a0, RoomObject02250e5c_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02250e5c's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02250e5c *RoomObject02250e5c_from_receiver(void *receiver)
{
    return (RoomObject02250e5c *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ab84: the deleting destructor, entered from the receiver part. */
RoomObject02250e5c *RoomObject02250e5cReceiver_Delete(void *receiver)
{
    return RoomObject02250e5c_Delete(RoomObject02250e5c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250e5cD0Ev, RoomObject02250e5cReceiver_Delete)

/* func_ov004_0221aba0: the destructor, entered from the receiver part. */
RoomObject02250e5c *RoomObject02250e5cReceiver_Destroy(void *receiver)
{
    return RoomObject02250e5c_Destroy(RoomObject02250e5c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250e5cD1Ev, RoomObject02250e5cReceiver_Destroy)
