/* An item shown in the room as a room object (data_ov004_022596b0, RoomPreview_Get): a
 * scene of overlay 142 hands it the item picked (RoomPreview_Show) and clears it
 * (RoomPreview_Clear). A wallpaper (0x1100-0x1143) is shown as room object 0x4a64 and a carpet
 * (0x1144-0x1187) as 0x4a60, which read the number noted here (RoomPreview_Number) and load
 * it into the texture files kept here (RoomPreview_WallpaperFile, RoomPreview_CarpetFile;
 * room_object_022511e0.h, room_object_02250e5c.h); an item of a pile (0x1000-0x10ff) as the
 * object 0x4a68 + 4 * its item, and anything else as its placed form.
 *
 * Two objects take turns: a new item starts in the other slot, near the player
 * (RoomPlacement_FindNearPlayer), while the one shown is deleted. The texture files, two of
 * each, are allocated by the room's start and freed by its end (room_manager.h). */
#ifndef CLEAN_OV004_ROOM_PREVIEW_H
#define CLEAN_OV004_ROOM_PREVIEW_H

#include "autoload_2/process.h"
#include "main/lookups.h" /* ItemCode */
#include "types.h"

#define ROOM_PREVIEW_SLOTS 2

typedef struct RoomPreview {
    Process *objects[ROOM_PREVIEW_SLOTS];    /* 0x00: the room objects, NULL for none */
    ItemCode items[ROOM_PREVIEW_SLOTS];      /* 0x08: the item each shows */
    u8 current;                              /* 0x0c: bit 0, the slot shown last */
    u8 pad_0d[3];                            /* 0x0d */
    int number;                              /* 0x10: the wallpaper's or carpet's number, -1 */
    u8 *wallpaper_files[ROOM_PREVIEW_SLOTS]; /* 0x14: WallpaperFile (0x10c4 bytes) */
    u8 *carpet_files[ROOM_PREVIEW_SLOTS];    /* 0x1c: CarpetTexture (0x20c4 bytes) */
} RoomPreview;

RoomPreview *RoomPreview_Get(void);
u8 *RoomPreview_CarpetFile(RoomPreview *preview);
u8 *RoomPreview_WallpaperFile(RoomPreview *preview);
void RoomPreview_Clear(RoomPreview *preview);
int RoomPreview_Show(RoomPreview *preview, ItemCode *item);
void RoomPreview_FreeFiles(RoomPreview *preview);
void RoomPreview_AllocFiles(RoomPreview *preview);
unsigned long RoomPreview_Number(RoomPreview *preview);
void RoomPreview_Reset(RoomPreview *preview);
RoomPreview *RoomPreview_Destruct(RoomPreview *preview);
RoomPreview *RoomPreview_Construct(RoomPreview *preview);

#endif
