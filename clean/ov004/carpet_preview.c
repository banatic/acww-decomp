/* A carpet shown in the room as a preview (carpet_preview.h). */
#include "carpet_preview.h"

#include "clean.h"
#include "room_object_life.h"
#include "main/item_texture.h"
#include "main/vram_copy_task.h"
#include "room_preview.h"

static_assert(offsetof(CarpetPreview, shown_frames) == 0x846, "shown_frames");
static_assert(offsetof(CarpetPreview, material_texture) == 0x848, "material texture");
static_assert(sizeof(CarpetPreview) == 0x870, "the size CarpetPreview_Create allocates");

#define CARPET_PREVIEW_SIZE 0x870
#define FLOOR_DRAWN_FRAMES 2
#define CARPET_FIRST 0x1144 /* the item code of carpet 0 */
#define CARPET_COUNT 0x44

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02250e5c[];
extern const u8 data_ov004_02250f08[];

/* "m_dummy_floor", the material the carpet goes on. */
extern const char data_ov004_02253190[];

/* func_ov004_02212764 (vtable slot 0x88): drawn once shown_frames is 2 or more. */
int CarpetPreview_CanDraw(CarpetPreview *object)
{
    return object->shown_frames >= FLOOR_DRAWN_FRAMES;
}
CLEAN_AS(func_ov004_02212764, CarpetPreview_CanDraw)

/* func_ov004_02212778 (vtable slot 0x0c) */
int CarpetPreview_Vfunc0c(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02212778, CarpetPreview_Vfunc0c)

/* func_ov004_0221277c (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * counts the frames since the carpet was put on, up to 2. */
int CarpetPreview_Update(CarpetPreview *object)
{
    if (object->shown_frames < FLOOR_DRAWN_FRAMES) {
        object->shown_frames++;
    }
    return 1;
}
CLEAN_AS(func_ov004_0221277c, CarpetPreview_Update)

/* func_ov004_02212794 (vtable slot 0x7c, once the model is bound): keeps the room's carpet
 * number, loads that carpet into the room's floor texture file and puts its texture on
 * "m_dummy_floor"; done when the material took it. */
int CarpetPreview_Start(CarpetPreview *object)
{
    object->carpet = (u16) RoomPreview_Number(RoomPreview_Get());
    object->shown_frames = 0;
    u16 item = object->carpet < CARPET_COUNT ? (u16) (object->carpet + CARPET_FIRST) : CARPET_FIRST;
    CarpetTexture_Load(RoomPreview_CarpetFile(RoomPreview_Get()), &item);
    G3dModel *model = object->base.model_resource;
    void *texture = CarpetTexture_Textures(RoomPreview_CarpetFile(RoomPreview_Get()));
    return VramCopyMaterial_Queue(&object->material_texture, (const u8 *) model, data_ov004_02253190, texture, 0, 0) != 0;
}
CLEAN_AS(func_ov004_02212794, CarpetPreview_Start)

static void carpet_preview_set_vtables(CarpetPreview *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02250e5c;
    object->base.receiver_vtable = data_ov004_02250f08;
}

/* func_ov004_02212820 (the deleting destructor, vtable slot 0x44).
 * QUIRK: the material texture binding at 0x848 the constructor built is not taken down. */
CarpetPreview *CarpetPreview_Delete(CarpetPreview *object)
{
    carpet_preview_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212820, CarpetPreview_Delete)

/* func_ov004_0221284c (the destructor, vtable slot 0x40); the same QUIRK. */
CarpetPreview *CarpetPreview_Destroy(CarpetPreview *object)
{
    carpet_preview_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221284c, CarpetPreview_Destroy)

/* func_ov004_02212870 (the constructor). Its other fields are left as the allocation zeroed
 * them. */
CarpetPreview *CarpetPreview_Construct(CarpetPreview *object)
{
    RoomObject_ConstructBase(&object->base);
    carpet_preview_set_vtables(object);
    VramCopyMaterial_Construct(&object->material_texture);
    return object;
}
CLEAN_AS(func_ov004_02212870, CarpetPreview_Construct)

/* func_ov004_022128a0: a new floor from the room's heap; nothing when it has no room. */
void CarpetPreview_Create(void)
{
    CarpetPreview *object = RoomObject_Alloc(CARPET_PREVIEW_SIZE);
    if (object != NULL) {
        CarpetPreview_Construct(object);
    }
}
CLEAN_AS(func_ov004_022128a0, CarpetPreview_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters CarpetPreview's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static CarpetPreview *carpet_preview_from_receiver(void *receiver)
{
    return (CarpetPreview *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ab84: the deleting destructor, entered from the receiver part. */
CarpetPreview *CarpetPreviewReceiver_Delete(void *receiver)
{
    return CarpetPreview_Delete(carpet_preview_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250e5cD0Ev, CarpetPreviewReceiver_Delete)

/* func_ov004_0221aba0: the destructor, entered from the receiver part. */
CarpetPreview *CarpetPreviewReceiver_Destroy(void *receiver)
{
    return CarpetPreview_Destroy(carpet_preview_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250e5cD1Ev, CarpetPreviewReceiver_Destroy)
