/* A wallpaper shown in the room (room object 0x4a64, room_preview.h: a scene of overlay 142
 * hands the room the item picked) on a wall of its own: a class of overlay 4's room objects (vtable 0x022511e0, receiver part
 * 0x0225128c, 0x870 bytes) whose model has a material named "m_dummy_wall", the twin of the
 * carpet's (carpet_preview.h). Once its model is bound it keeps the word at 0x10 of
 * data_ov004_022596b0 (RoomPreview_Get, RoomPreview_Number), loads the wallpaper it names
 * (item 0x1100 plus it, 0x1100 when it is 0x44 or more) into the room's wall texture file
 * (RoomPreview_WallpaperFile, WallpaperFile_Load) and puts that texture on the material. It is drawn from
 * the second frame after that on. */
#ifndef CLEAN_OV004_WALLPAPER_PREVIEW_H
#define CLEAN_OV004_WALLPAPER_PREVIEW_H

#include "types.h"

#include "main/vram_copy_task.h"
#include "room_object.h"

typedef struct WallpaperPreview {
    RoomObject base;
    u16 wallpaper;   /* func_ov004_0223d2ac of data_ov004_022596b0: the wallpaper's number */
    u8 shown_frames; /* frames since the wallpaper was put on, up to 2; drawn from 2 on */
    u8 unk_847;
    /* Puts a texture on a material of the model (built by VramCopyMaterial_Construct, filled by
     * VramCopyMaterial_Queue). */
    VramCopyMaterial material_texture;
} WallpaperPreview;

int WallpaperPreview_CanDraw(WallpaperPreview *object);
int WallpaperPreview_Vfunc0c(void);
int WallpaperPreview_Update(WallpaperPreview *object);
int WallpaperPreview_Start(WallpaperPreview *object);
WallpaperPreview *WallpaperPreview_Delete(WallpaperPreview *object);
WallpaperPreview *WallpaperPreview_Destruct(WallpaperPreview *object);
WallpaperPreview *WallpaperPreview_Construct(WallpaperPreview *object);
void WallpaperPreview_Create(void);
WallpaperPreview *WallpaperPreviewReceiver_Delete(void *receiver);
WallpaperPreview *WallpaperPreviewReceiver_Destruct(void *receiver);

#endif
