/* The room's wall: a class of overlay 4's room objects (vtable 0x022511e0, receiver part
 * 0x0225128c, 0x870 bytes) whose model has a material named "m_dummy_wall", the twin of the
 * floor (room_object_02250e5c.h). Once its model is bound it keeps the word at 0x10 of
 * data_ov004_022596b0 (RoomPreview_Get, RoomPreview_Number), loads the wallpaper it names
 * (item 0x1100 plus it, 0x1100 when it is 0x44 or more) into the room's wall texture file
 * (RoomPreview_WallpaperFile, WallpaperFile_Load) and puts that texture on the material. It is drawn from
 * the second frame after that on. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022511E0_H
#define CLEAN_OV004_ROOM_OBJECT_022511E0_H

#include "types.h"

#include "main/vram_copy_task.h"
#include "room_object.h"

typedef struct RoomObject022511e0 {
    RoomObject base;
    u16 unk_844; /* func_ov004_0223d2ac of data_ov004_022596b0: the wallpaper's number */
    u8 unk_846;  /* frames since the wallpaper was put on, up to 2; drawn from 2 on */
    u8 unk_847;
    /* Puts a texture on a material of the model (built by VramCopyMaterial_Construct, filled by
     * VramCopyMaterial_Queue). */
    VramCopyMaterial material_texture;
} RoomObject022511e0;

int RoomObject022511e0_CanDraw(RoomObject022511e0 *object);
int RoomObject022511e0_Vfunc0C(void);
int RoomObject022511e0_Update(RoomObject022511e0 *object);
int RoomObject022511e0_Start(RoomObject022511e0 *object);
RoomObject022511e0 *RoomObject022511e0_Delete(RoomObject022511e0 *object);
RoomObject022511e0 *RoomObject022511e0_Destroy(RoomObject022511e0 *object);
RoomObject022511e0 *RoomObject022511e0_Construct(RoomObject022511e0 *object);
void RoomObject022511e0_Create(void);
RoomObject022511e0 *RoomObject022511e0Receiver_Delete(void *receiver);
RoomObject022511e0 *RoomObject022511e0Receiver_Destroy(void *receiver);

#endif
