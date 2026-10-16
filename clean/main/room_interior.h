/* The wallpaper and carpet of rooms (scenes).
 *
 * Each scene (func_020b65c4, below 51) has a wallpaper and a carpet item code here, 0xfff1
 * (nothing) when unset; the player's house rooms (scenes 1 to 5, func_020b67e8) also keep them
 * in their records at data_021ebcd4 (0x448: wallpaper, 0x44a: carpet). The room being shown
 * belongs to overlay 4 (indoors, data_020e54a8 is 1), which changes it and answers the code it
 * replaces.
 *
 * A change made on one console is sent to the others in the session as message 0x14 (four
 * bytes, RoomInteriorChange), which RoomInterior_ReceiveChange applies. */
#ifndef CLEAN_MAIN_ROOM_INTERIOR_H
#define CLEAN_MAIN_ROOM_INTERIOR_H

#include "types.h"

#define ROOM_INTERIOR_SCENES 51

/* The message: the item code, then a halfword of bits. */
#define ROOM_CHANGE_SCENE_MASK 0x3f    /* bits 0-5: the scene the change is for */
#define ROOM_CHANGE_WALLPAPER (1 << 6) /* the wallpaper, else the carpet */
#define ROOM_CHANGE_OPTION (1 << 7)    /* overlay 4's third argument (`option` below) */
#define ROOM_CHANGE_SOUND (1 << 8)     /* with the change's sound */
typedef struct RoomInteriorChange {
    u16 item;
    u16 bits;
} RoomInteriorChange;

void RoomInterior_ReceiveChange(const RoomInteriorChange *change);
u16 *RoomInterior_SceneCarpet(u32 scene);
int RoomInterior_SetSceneCarpet(u32 scene, const u16 *item);
u16 *RoomInterior_SceneWallpaper(u32 scene);
int RoomInterior_SetSceneWallpaper(u32 scene, const u16 *item);
void RoomInterior_ClearScenes(void);
int RoomInterior_Set(u16 *item, int option, int wallpaper, int with_sound, u8 send);
int RoomInterior_ResendCarpet(int send);
int RoomInterior_ResendWallpaper(int send);
void RoomInterior_SetCarpetDesign(int design, int option, int with_sound, int send);
u16 *RoomInterior_SetCarpet(const u16 *item, int option, int with_sound, u32 send);
void RoomInterior_SetWallpaperDesign(int design, int option, int with_sound, int send);
int RoomInterior_SetWallpaper(const u16 *item, int option, int with_sound, int send);
void RoomInterior_SendChange(const u16 *item, int option, u16 wallpaper, u16 with_sound);
void RoomInterior_DesignCode(u16 *code, int design);
void RoomInterior_DestroySceneCarpets(void);
void RoomInterior_DestroySceneWallpapers(void);
void RoomInterior_ConstructCode(u16 *code);

#endif
