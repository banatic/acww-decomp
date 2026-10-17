/* The room's wallpaper and carpet as the model of the room (room_shell.h) keeps them: one part
 * each, at 0x128 (the wallpaper's, 0x1100 bytes) and 0x1228 (the carpet's, 0x2100 bytes) of the
 * room's object. A part holds the item shown and the one it replaced, the texture file of the
 * item (WallpaperFile, "/wall/wall_%d.nsbtx"; CarpetTexture, "/carpet/floor_<n>.nsbtx"), a copy
 * of its image and palette over the model's material "m_dummy_wall" or "m_dummy_floor"
 * (VramCopyMaterial), and a binding of that material (MaterialBind) to the room's own texture
 * resource, where a player's design is bound instead.
 *
 * Putting an item up (RoomWallpaper_Set, RoomCarpet_Set) takes a wallpaper (0x1100-0x1143) or
 * carpet (0x1144-0x1187) by loading its file and queueing the copy, a player's design
 * (0x1188-0x11a7) by binding the design's texture, and the item already shown (with the same
 * mode) as it is. The item it replaced is kept, the room's record (house_record.h) and the
 * scene's (room_interior.h) are given the new one. The mode is the record's flag that flips
 * the texture (ROOM_SHELL_MODE_FLIP). */
#ifndef CLEAN_OV004_ROOM_SURFACE_H
#define CLEAN_OV004_ROOM_SURFACE_H

#include "main/g3d_resource.h"
#include "main/lookups.h" /* ItemCode */
#include "main/material_bind.h"
#include "main/vram_copy_task.h"
#include "types.h"

/* The sizes of the texture files the parts hold. */
#define ROOM_WALLPAPER_FILE_SIZE 0x10c4
#define ROOM_CARPET_FILE_SIZE 0x20c4

typedef struct RoomWallpaper {
    ItemCode replaced;                 /* 0x0000: the item the last change replaced */
    ItemCode code;                     /* 0x0002: the item shown */
    VramCopyMaterial copy;             /* 0x0004 */
    u8 file[ROOM_WALLPAPER_FILE_SIZE]; /* 0x002c: a WallpaperFile */
    int mode;                          /* 0x10f0 */
    MaterialBind bind;                 /* 0x10f4: material "m_dummy_wall" */
    G3dResTex *texture;                /* 0x10fc: the room's texture resource */
} RoomWallpaper;

typedef struct RoomCarpet {
    ItemCode replaced;              /* 0x0000 */
    ItemCode code;                  /* 0x0002 */
    VramCopyMaterial copy;          /* 0x0004 */
    u8 file[ROOM_CARPET_FILE_SIZE]; /* 0x002c: a CarpetTexture file */
    int mode;                       /* 0x20f0 */
    MaterialBind bind;              /* 0x20f4: material "m_dummy_floor" */
    G3dResTex *texture;             /* 0x20fc */
} RoomCarpet;

void RoomCarpet_End(RoomCarpet *self);
int RoomCarpet_Set(RoomCarpet *self, ItemCode *item, u8 *model, int mode);
void RoomCarpet_Record(RoomCarpet *self, const ItemCode *code, int mode);
int RoomCarpet_SetCode(RoomCarpet *self, int code, u8 *model, int mode);
int RoomCarpet_PickMaterial(RoomCarpet *self, u8 *model, G3dResTex *texture);
int RoomCarpet_Mode(RoomCarpet *self);
ItemCode *RoomCarpet_Replaced(RoomCarpet *self);
ItemCode *RoomCarpet_Code(RoomCarpet *self);
RoomCarpet *RoomCarpet_Destruct(RoomCarpet *self);
RoomCarpet *RoomCarpet_Construct(RoomCarpet *self);

void RoomWallpaper_End(RoomWallpaper *self);
int RoomWallpaper_Set(RoomWallpaper *self, ItemCode *item, u8 *model, int mode);
void RoomWallpaper_Record(RoomWallpaper *self, const ItemCode *code, int mode);
int RoomWallpaper_SetCode(RoomWallpaper *self, int code, u8 *model, int mode);
int RoomWallpaper_PickMaterial(RoomWallpaper *self, u8 *model, G3dResTex *texture);
int RoomWallpaper_Mode(RoomWallpaper *self);
ItemCode *RoomWallpaper_Replaced(RoomWallpaper *self);
ItemCode *RoomWallpaper_Code(RoomWallpaper *self);
RoomWallpaper *RoomWallpaper_Destruct(RoomWallpaper *self);
RoomWallpaper *RoomWallpaper_Construct(RoomWallpaper *self);

#endif
