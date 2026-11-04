/* A carpet shown in the room (room object 0x4a60, room_preview.h: a scene of overlay 142 hands
 * the room the item picked) on a floor of its own: a class of overlay 4's room objects (vtable 0x02250e5c, receiver part
 * 0x02250f08, 0x870 bytes) whose model has a material named "m_dummy_floor". Once its model is
 * bound it keeps the word at 0x10 of data_ov004_022596b0 (RoomPreview_Get,
 * RoomPreview_Number), loads the carpet it names (item 0x1144 plus it, 0x1144 when it is 0x44
 * or more) into the room's floor texture file (RoomPreview_CarpetFile, CarpetTexture_Load) and puts that
 * texture on the material. It is drawn from the second frame after that on. The twin class for
 * a wallpaper is wallpaper_preview.h. */
#ifndef CLEAN_OV004_CARPET_PREVIEW_H
#define CLEAN_OV004_CARPET_PREVIEW_H

#include "types.h"

#include "main/vram_copy_task.h"
#include "room_object.h"

typedef struct CarpetPreview {
    RoomObject base;
    u16 carpet;      /* func_ov004_0223d2ac of data_ov004_022596b0: the carpet's number */
    u8 shown_frames; /* frames since the carpet was put on, up to 2; drawn from 2 on */
    u8 unk_847;
    /* Puts a texture on a material of the model (built by VramCopyMaterial_Construct, filled by
     * VramCopyMaterial_Queue). */
    VramCopyMaterial material_texture;
} CarpetPreview;

int CarpetPreview_CanDraw(CarpetPreview *object);
int CarpetPreview_Vfunc0C(void);
int CarpetPreview_Update(CarpetPreview *object);
int CarpetPreview_Start(CarpetPreview *object);
CarpetPreview *CarpetPreview_Delete(CarpetPreview *object);
CarpetPreview *CarpetPreview_Destroy(CarpetPreview *object);
CarpetPreview *CarpetPreview_Construct(CarpetPreview *object);
void CarpetPreview_Create(void);

CarpetPreview *CarpetPreviewReceiver_Delete(void *receiver);
CarpetPreview *CarpetPreviewReceiver_Destroy(void *receiver);

#endif
