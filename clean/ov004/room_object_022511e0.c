/* The room's wall (room_object_022511e0.h). */
#include "room_object_022511e0.h"

#include "clean.h"
#include "room_object_life.h"

static_assert(offsetof(RoomObject022511e0, unk_846) == 0x846, "unk_846");
static_assert(offsetof(RoomObject022511e0, material_texture) == 0x848, "material texture");
static_assert(sizeof(RoomObject022511e0) == 0x870, "the size RoomObject022511e0_Create allocates");

#define ROOM_OBJECT_022511E0_SIZE 0x870
#define WALL_DRAWN_FRAMES 2
#define WALLPAPER_FIRST 0x1100 /* the item code of wallpaper 0 */
#define WALLPAPER_COUNT 0x44

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022511e0[];
extern const u8 data_ov004_0225128c[];

/* "m_dummy_wall", the material the wallpaper goes on. */
extern const char data_ov004_022531a0[];

/* The room (data_ov004_022596b0), its word at 0x10, and its wall texture file in use. */
extern void *func_ov004_0223d03c(void);
extern unsigned long func_ov004_0223d2ac(void *p);
extern void *func_ov004_0223d054(void *room);
/* Loads the wallpaper `*item` (0x1100 to 0x1143) into a texture file. */
extern int func_020ba1f4(void *file, u16 *item);
/* The texture block of a texture file. */
extern void *func_020ba1ec(void *file);
/* Puts texture 0 and palette 0 of `texture` on the material named `material` of `model`;
 * whether it could. */
extern int func_020b9d3c(void *bind, G3dModel *model, const char *material, void *texture, int tex_index, int plt_index);
extern void *func_020b9e58(void *bind);

/* func_ov004_022128bc (vtable slot 0x88): drawn once unk_846 is 2 or more. */
int RoomObject022511e0_CanDraw(RoomObject022511e0 *object)
{
    return object->unk_846 >= WALL_DRAWN_FRAMES;
}
CLEAN_AS(func_ov004_022128bc, RoomObject022511e0_CanDraw)

/* func_ov004_022128d0 (vtable slot 0x0c) */
int RoomObject022511e0_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022128d0, RoomObject022511e0_Vfunc0C)

/* func_ov004_022128d4 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * counts the frames since the wallpaper was put on, up to 2. */
int RoomObject022511e0_Update(RoomObject022511e0 *object)
{
    if (object->unk_846 < WALL_DRAWN_FRAMES) {
        object->unk_846++;
    }
    return 1;
}
CLEAN_AS(func_ov004_022128d4, RoomObject022511e0_Update)

/* func_ov004_022128ec (vtable slot 0x7c, once the model is bound): keeps the room's wallpaper
 * number, loads that wallpaper into the room's wall texture file and puts its texture on
 * "m_dummy_wall"; done when the material took it. */
int RoomObject022511e0_Start(RoomObject022511e0 *object)
{
    object->unk_844 = (u16) func_ov004_0223d2ac(func_ov004_0223d03c());
    object->unk_846 = 0;
    u16 item = object->unk_844 < WALLPAPER_COUNT ? (u16) (object->unk_844 + WALLPAPER_FIRST) : WALLPAPER_FIRST;
    func_020ba1f4(func_ov004_0223d054(func_ov004_0223d03c()), &item);
    G3dModel *model = object->base.model_resource;
    void *texture = func_020ba1ec(func_ov004_0223d054(func_ov004_0223d03c()));
    return func_020b9d3c(object->material_texture, model, data_ov004_022531a0, texture, 0, 0) != 0;
}
CLEAN_AS(func_ov004_022128ec, RoomObject022511e0_Start)

static void RoomObject022511e0_set_vtables(RoomObject022511e0 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022511e0;
    object->base.receiver_vtable = data_ov004_0225128c;
}

/* func_ov004_02212978 (the deleting destructor, vtable slot 0x44).
 * QUIRK: the material texture binding at 0x848 the constructor built is not taken down. */
RoomObject022511e0 *RoomObject022511e0_Delete(RoomObject022511e0 *object)
{
    RoomObject022511e0_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212978, RoomObject022511e0_Delete)

/* func_ov004_022129a4 (the destructor, vtable slot 0x40); the same QUIRK. */
RoomObject022511e0 *RoomObject022511e0_Destroy(RoomObject022511e0 *object)
{
    RoomObject022511e0_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022129a4, RoomObject022511e0_Destroy)

/* func_ov004_022129c8 (the constructor). Its other fields are left as the allocation zeroed
 * them. */
RoomObject022511e0 *RoomObject022511e0_Construct(RoomObject022511e0 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject022511e0_set_vtables(object);
    func_020b9e58(object->material_texture);
    return object;
}
CLEAN_AS(func_ov004_022129c8, RoomObject022511e0_Construct)

/* func_ov004_022129f8: a new wall from the room's heap; nothing when it has no room. */
void RoomObject022511e0_Create(void)
{
    RoomObject022511e0 *object = RoomObject_Alloc(ROOM_OBJECT_022511E0_SIZE);
    if (object != NULL) {
        RoomObject022511e0_Construct(object);
    }
}
CLEAN_AS(func_ov004_022129f8, RoomObject022511e0_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject022511e0's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject022511e0 *RoomObject022511e0_from_receiver(void *receiver)
{
    return (RoomObject022511e0 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ab4c: the deleting destructor, entered from the receiver part. */
RoomObject022511e0 *RoomObject022511e0Receiver_Delete(void *receiver)
{
    return RoomObject022511e0_Delete(RoomObject022511e0_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022511e0D0Ev, RoomObject022511e0Receiver_Delete)

/* func_ov004_0221ab68: the destructor, entered from the receiver part. */
RoomObject022511e0 *RoomObject022511e0Receiver_Destroy(void *receiver)
{
    return RoomObject022511e0_Destroy(RoomObject022511e0_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022511e0D1Ev, RoomObject022511e0Receiver_Destroy)
