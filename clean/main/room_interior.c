/* The wallpaper and carpet of rooms (room_interior.h). */
#include "room_interior.h"

#include "clean.h"
#include "item_group.h"
#include "session.h"
#include "house_record.h"
#include "ov004/room_shell.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_kinds.h"
#include "scene_query.h"

static_assert(sizeof(RoomInteriorChange) == 4, "message size");

/* The session message a change is sent as. */
#define ROOM_CHANGE_HANDLER 0x14

/* The code of nothing. */
#define ROOM_ITEM_NONE 0xfff1

/* 1 indoors, when overlay 4 has the room being shown. */
extern u8 data_020e54a8;
/* Each scene's carpet and wallpaper. */
extern u16 data_021c5204[ROOM_INTERIOR_SCENES];
extern u16 data_021c519c[ROOM_INTERIOR_SCENES];
/* An item code of nothing: what the lookups answer outside the scenes or the room. */
extern u16 data_021c5174;
/* The rooms' records. */
extern u8 data_021ebcd4[];
/* The session. */
extern NetSession *data_020ccf94;
/* The four players' records. */
extern u8 data_021dc7bc[];

/* The item code's destructor (nothing to do), handed to __cxa_vec_cleanup. */
extern void func_020051b0(void *code);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_020348fc: a change received from another console: applied to the room shown when it is
 * for the current scene (without sending it on); else kept in the scene's table, and in the
 * room's record too for a room of the house that has one.
 * QUIRK: a house room whose record is missing keeps nothing. */
void RoomInterior_ReceiveChange(const RoomInteriorChange *change)
{
    u16 item = change->item;
    u8 scene = (u8) (change->bits & ROOM_CHANGE_SCENE_MASK);
    int option = (change->bits & ROOM_CHANGE_OPTION) != 0;
    int wallpaper = (change->bits & ROOM_CHANGE_WALLPAPER) != 0;
    int with_sound = (change->bits & ROOM_CHANGE_SOUND) != 0;

    if (scene == SceneQuery_Current()) {
        RoomInterior_Set(&item, option, wallpaper, with_sound, 0);
        return;
    }
    if (SceneKinds_IsHouseRoom(scene) != 0) {
        void *record = HouseRecord_RoomOfScene((HouseRecord *) (void *) data_021ebcd4, scene);
        if (record == NULL) {
            return;
        }
        if (wallpaper) {
            HouseRecord_RoomSetWallpaper(record, &item, option);
            RoomInterior_SetSceneWallpaper(scene, &item);
        } else {
            HouseRecord_RoomSetCarpet(record, &item, option);
            RoomInterior_SetSceneCarpet(scene, &item);
        }
    } else if (wallpaper) {
        RoomInterior_SetSceneWallpaper(scene, &item);
    } else {
        RoomInterior_SetSceneCarpet(scene, &item);
    }
}
CLEAN_AS(func_020348fc, RoomInterior_ReceiveChange)

/* func_020349b8: the scene's carpet, the code of nothing past the scenes. */
u16 *RoomInterior_SceneCarpet(u32 scene)
{
    return scene < ROOM_INTERIOR_SCENES ? &data_021c5204[scene] : &data_021c5174;
}
CLEAN_AS(func_020349b8, RoomInterior_SceneCarpet)

/* func_020349d0: whether `scene` is one. */
int RoomInterior_SetSceneCarpet(u32 scene, const u16 *item)
{
    if (scene < ROOM_INTERIOR_SCENES) {
        data_021c5204[scene] = *item;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020349d0, RoomInterior_SetSceneCarpet)

/* func_020349e8 */
u16 *RoomInterior_SceneWallpaper(u32 scene)
{
    return scene < ROOM_INTERIOR_SCENES ? &data_021c519c[scene] : &data_021c5174;
}
CLEAN_AS(func_020349e8, RoomInterior_SceneWallpaper)

/* func_02034a00 */
int RoomInterior_SetSceneWallpaper(u32 scene, const u16 *item)
{
    if (scene < ROOM_INTERIOR_SCENES) {
        data_021c519c[scene] = *item;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02034a00, RoomInterior_SetSceneWallpaper)

/* func_02034a18: every scene's wallpaper and carpet set to nothing. */
void RoomInterior_ClearScenes(void)
{
    u32 scene;

    for (scene = 0; scene < ROOM_INTERIOR_SCENES; scene++) {
        data_021c5204[scene] = ROOM_ITEM_NONE;
        data_021c519c[scene] = ROOM_ITEM_NONE;
    }
}
CLEAN_AS(func_02034a18, RoomInterior_ClearScenes)

/* func_02034a48: the room's wallpaper or carpet changed to `*item`. */
int RoomInterior_Set(u16 *item, int option, int wallpaper, int with_sound, u8 send)
{
    if (wallpaper) {
        return RoomInterior_SetWallpaper(item, option, with_sound, send);
    }
    return (int) (uintptr_t) RoomInterior_SetCarpet(item, option, with_sound, send);
}
CLEAN_AS(func_02034a48, RoomInterior_Set)

/* func_02034a74: indoors, the room's carpet set to itself (sent to the others when `send`);
 * whether it was indoors. */
int RoomInterior_ResendCarpet(int send)
{
    if (data_020e54a8 == 1) {
        RoomInterior_SetCarpet(RoomShell_CarpetCode(), 0, 0, (u32) send);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02034a74, RoomInterior_ResendCarpet)

/* func_02034aa8 */
int RoomInterior_ResendWallpaper(int send)
{
    if (data_020e54a8 == 1) {
        RoomInterior_SetWallpaper(RoomShell_WallpaperCode(), 0, 0, send);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02034aa8, RoomInterior_ResendWallpaper)

/* func_02034adc: the carpet changed to one of the current player's designs. */
void RoomInterior_SetCarpetDesign(int design, int option, int with_sound, int send)
{
    u16 code;

    RoomInterior_DesignCode(&code, design);
    RoomInterior_SetCarpet(&code, option, with_sound, (u32) send);
}
CLEAN_AS(func_02034adc, RoomInterior_SetCarpetDesign)

/* func_02034b04: indoors, the room's carpet changed to `*item` (sent to the others when
 * `send`); the code it replaced. Outdoors nothing changes and the code of nothing comes back. */
u16 *RoomInterior_SetCarpet(const u16 *item, int option, int with_sound, u32 send)
{
    u16 code = *item;

    if (data_020e54a8 != 1) {
        return &data_021c5174;
    }
    u16 *replaced = RoomShell_SetCarpet(&code, option, with_sound);
    if (send != 0) {
        RoomInterior_SendChange(&code, option, 0, (u16) with_sound);
    }
    return replaced;
}
CLEAN_AS(func_02034b04, RoomInterior_SetCarpet)

/* func_02034b58 */
void RoomInterior_SetWallpaperDesign(int design, int option, int with_sound, int send)
{
    u16 code;

    RoomInterior_DesignCode(&code, design);
    RoomInterior_SetWallpaper(&code, option, with_sound, send);
}
CLEAN_AS(func_02034b58, RoomInterior_SetWallpaperDesign)

/* func_02034b80 */
int RoomInterior_SetWallpaper(const u16 *item, int option, int with_sound, int send)
{
    u16 code = *item;

    if (data_020e54a8 != 1) {
        return (int) (uintptr_t) &data_021c5174;
    }
    int replaced = (int) (uintptr_t) RoomShell_SetWallpaper(&code, option, with_sound);
    if (send != 0) {
        RoomInterior_SendChange(&code, option, 1, (u16) with_sound);
    }
    return replaced;
}
CLEAN_AS(func_02034b80, RoomInterior_SetWallpaper)

/* func_02034bd4: while linked, the change sent to the others for the current scene.
 * BUG: bits 9-15 of the message's second halfword are what was left on the stack in the
 * original; here they are 0. The receiver reads only bits 0-8. */
void RoomInterior_SendChange(const u16 *item, int option, u16 wallpaper, u16 with_sound)
{
    RoomInteriorChange change;

    if (Session_IsLinked(data_020ccf94) == 0) {
        return;
    }
    change.item = *item;
    change.bits = (u16) (SceneQuery_Current() & ROOM_CHANGE_SCENE_MASK);
    if ((wallpaper & 1) != 0) {
        change.bits |= ROOM_CHANGE_WALLPAPER;
    }
    if ((option & 1) != 0) {
        change.bits |= ROOM_CHANGE_OPTION;
    }
    if ((with_sound & 1) != 0) {
        change.bits |= ROOM_CHANGE_SOUND;
    }
    Session_BeginMessage(data_020ccf94);
    Session_AppendMessage(data_020ccf94, &change, sizeof(change));
    Session_EndMessage(data_020ccf94, ROOM_CHANGE_HANDLER, sizeof(change));
}
CLEAN_AS(func_02034bd4, RoomInterior_SendChange)

/* func_02034c64: the code of design `design` (0 to 7) of the current player (player 0 when
 * there is none). */
void RoomInterior_DesignCode(u16 *code, int design)
{
    int player = 0;
    void *record = PlayerRecords_Current();

    if (record != NULL) {
        player = PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) PlayerRecord_Player(record)) & 3;
    }
    ItemGroup_ConstructDesign(code, player, design & 7);
}
CLEAN_AS(func_02034c64, RoomInterior_DesignCode)

/* func_02034ca0: the destructor of the scenes' carpets, registered by __sinit_020c4c5c. */
void RoomInterior_DestroySceneCarpets(void)
{
    __cxa_vec_cleanup(data_021c5204, ROOM_INTERIOR_SCENES, sizeof(u16), func_020051b0);
}
CLEAN_AS(func_02034ca0, RoomInterior_DestroySceneCarpets)

/* func_02034cc0 */
void RoomInterior_DestroySceneWallpapers(void)
{
    __cxa_vec_cleanup(data_021c519c, ROOM_INTERIOR_SCENES, sizeof(u16), func_020051b0);
}
CLEAN_AS(func_02034cc0, RoomInterior_DestroySceneWallpapers)

/* func_02034ce0: an item code's constructor: nothing. */
void RoomInterior_ConstructCode(u16 *code)
{
    *code = ROOM_ITEM_NONE;
}
CLEAN_AS(func_02034ce0, RoomInterior_ConstructCode)
