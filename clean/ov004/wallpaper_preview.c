/* A wallpaper shown in the room as a preview (wallpaper_preview.h). */
#include "wallpaper_preview.h"

#include "clean.h"
#include "room_object_life.h"
#include "main/vram_copy_task.h"
#include "main/wallpaper_file.h"
#include "room_preview.h"

static_assert(offsetof(WallpaperPreview, shown_frames) == 0x846, "shown_frames");
static_assert(offsetof(WallpaperPreview, material_texture) == 0x848, "material texture");
static_assert(sizeof(WallpaperPreview) == 0x870, "the size WallpaperPreview_Create allocates");

#define WALLPAPER_PREVIEW_SIZE 0x870
#define WALL_DRAWN_FRAMES 2
#define WALLPAPER_FIRST 0x1100 /* the item code of wallpaper 0 */
#define WALLPAPER_COUNT 0x44

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022511e0[];
extern const u8 data_ov004_0225128c[];

/* "m_dummy_wall", the material the wallpaper goes on. */
extern const char data_ov004_022531a0[];

/* func_ov004_022128bc (vtable slot 0x88): drawn once shown_frames is 2 or more. */
int WallpaperPreview_CanDraw(WallpaperPreview *object)
{
    return object->shown_frames >= WALL_DRAWN_FRAMES;
}
CLEAN_AS(func_ov004_022128bc, WallpaperPreview_CanDraw)

/* func_ov004_022128d0 (vtable slot 0x0c) */
int WallpaperPreview_Vfunc0c(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022128d0, WallpaperPreview_Vfunc0c)

/* func_ov004_022128d4 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * counts the frames since the wallpaper was put on, up to 2. */
int WallpaperPreview_Update(WallpaperPreview *object)
{
    if (object->shown_frames < WALL_DRAWN_FRAMES) {
        object->shown_frames++;
    }
    return 1;
}
CLEAN_AS(func_ov004_022128d4, WallpaperPreview_Update)

/* func_ov004_022128ec (vtable slot 0x7c, once the model is bound): keeps the room's wallpaper
 * number, loads that wallpaper into the room's wall texture file and puts its texture on
 * "m_dummy_wall"; done when the material took it. */
int WallpaperPreview_Start(WallpaperPreview *object)
{
    object->wallpaper = (u16) RoomPreview_Number(RoomPreview_Get());
    object->shown_frames = 0;
    u16 item = object->wallpaper < WALLPAPER_COUNT ? (u16) (object->wallpaper + WALLPAPER_FIRST) : WALLPAPER_FIRST;
    WallpaperFile_Load(RoomPreview_WallpaperFile(RoomPreview_Get()), &item);
    G3dModel *model = object->base.model_resource;
    void *texture = (void *) (uintptr_t) WallpaperFile_Texture(RoomPreview_WallpaperFile(RoomPreview_Get()));
    return VramCopyMaterial_Queue(&object->material_texture, (const u8 *) model, data_ov004_022531a0, texture, 0, 0) != 0;
}
CLEAN_AS(func_ov004_022128ec, WallpaperPreview_Start)

static void wallpaper_preview_set_vtables(WallpaperPreview *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022511e0;
    object->base.receiver_vtable = data_ov004_0225128c;
}

/* func_ov004_02212978 (the deleting destructor, vtable slot 0x44).
 * QUIRK: the material texture binding at 0x848 the constructor built is not taken down. */
WallpaperPreview *WallpaperPreview_Delete(WallpaperPreview *object)
{
    wallpaper_preview_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212978, WallpaperPreview_Delete)

/* func_ov004_022129a4 (the destructor, vtable slot 0x40); the same QUIRK. */
WallpaperPreview *WallpaperPreview_Destroy(WallpaperPreview *object)
{
    wallpaper_preview_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022129a4, WallpaperPreview_Destroy)

/* func_ov004_022129c8 (the constructor). Its other fields are left as the allocation zeroed
 * them. */
WallpaperPreview *WallpaperPreview_Construct(WallpaperPreview *object)
{
    RoomObject_ConstructBase(&object->base);
    wallpaper_preview_set_vtables(object);
    VramCopyMaterial_Construct(&object->material_texture);
    return object;
}
CLEAN_AS(func_ov004_022129c8, WallpaperPreview_Construct)

/* func_ov004_022129f8: a new wall from the room's heap; nothing when it has no room. */
void WallpaperPreview_Create(void)
{
    WallpaperPreview *object = RoomObject_Alloc(WALLPAPER_PREVIEW_SIZE);
    if (object != NULL) {
        WallpaperPreview_Construct(object);
    }
}
CLEAN_AS(func_ov004_022129f8, WallpaperPreview_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters WallpaperPreview's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static WallpaperPreview *wallpaper_preview_from_receiver(void *receiver)
{
    return (WallpaperPreview *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ab4c: the deleting destructor, entered from the receiver part. */
WallpaperPreview *WallpaperPreviewReceiver_Delete(void *receiver)
{
    return WallpaperPreview_Delete(wallpaper_preview_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022511e0D0Ev, WallpaperPreviewReceiver_Delete)

/* func_ov004_0221ab68: the destructor, entered from the receiver part. */
WallpaperPreview *WallpaperPreviewReceiver_Destroy(void *receiver)
{
    return WallpaperPreview_Destroy(wallpaper_preview_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022511e0D1Ev, WallpaperPreviewReceiver_Destroy)
