/* The room's wallpaper and carpet parts (room_surface.h). */
#include "room_surface.h"

#include <stdint.h>

#include "clean.h"
#include "main/design_assets.h"
#include "main/g3d_resource.h"
#include "main/house_record.h"
#include "main/item_code.h"
#include "main/item_group.h"
#include "main/item_texture.h"
#include "main/room_interior.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "main/wallpaper_file.h"

static_assert(offsetof(RoomWallpaper, copy) == 0x4, "wallpaper copy");
static_assert(offsetof(RoomWallpaper, file) == 0x2c, "wallpaper file");
static_assert(offsetof(RoomWallpaper, mode) == 0x10f0, "wallpaper mode");
static_assert(offsetof(RoomWallpaper, bind) == 0x10f4, "wallpaper bind");
static_assert(offsetof(RoomWallpaper, texture) == 0x10fc, "wallpaper texture");
static_assert(sizeof(RoomWallpaper) == 0x1100, "wallpaper size");
static_assert(offsetof(RoomCarpet, file) == 0x2c, "carpet file");
static_assert(offsetof(RoomCarpet, mode) == 0x20f0, "carpet mode");
static_assert(offsetof(RoomCarpet, bind) == 0x20f4, "carpet bind");
static_assert(offsetof(RoomCarpet, texture) == 0x20fc, "carpet texture");
static_assert(sizeof(RoomCarpet) == 0x2100, "carpet size");

/* The item ranges the parts take. */
#define ROOM_SURFACE_WALLPAPER_FIRST 0x1100
#define ROOM_SURFACE_WALLPAPER_LAST 0x1143
#define ROOM_SURFACE_CARPET_FIRST 0x1144
#define ROOM_SURFACE_CARPET_LAST 0x1187
#define ROOM_SURFACE_DESIGN_FIRST 0x1188
#define ROOM_SURFACE_DESIGN_LAST 0x11a7

/* The rooms' records (house_record.h). */
extern HouseRecord data_021ebcd4;

/* The names of the model's materials the parts copy their item's texture over: words of the
 * overlay that point to "m_dummy_floor" and "m_dummy_wall", read each time. */
extern const char *data_ov004_02255a80;
extern const char *data_ov004_02255a84;
/* The same names, as the bindings pick them. */
extern const char data_ov004_02255aa0[]; /* "m_dummy_floor" */
extern const char data_ov004_02255a90[]; /* "m_dummy_wall" */
/* The texture and palette of the room's texture resource bound while no design is shown. */
extern const char data_ov004_02255b18[]; /* "dummy_floor" */
extern const char data_ov004_02255b24[]; /* "dummy_floor_pl" */
extern const char data_ov004_02255b34[]; /* "dummy_wall" */
extern const char data_ov004_02255b40[]; /* "dummy_wall_pl" */

static int RoomSurface_in(ItemCode code, ItemCode first, ItemCode last)
{
    return code >= first && code <= last;
}

/* Whether `item` is the part's item: by the item of its variant for a code with a variant. */
static int RoomSurface_same_item(const ItemCode *shown, const ItemCode *item)
{
    if (ItemCode_HasVariant(shown)) {
        int mine = ItemCode_VariantItem(shown);
        return mine == ItemCode_VariantItem(item);
    }
    return *shown == *item;
}

/* A player's design's texture (the item says whose and which), from the design manager. */
static G3dResTex *RoomSurface_design_texture(const ItemCode *item)
{
    int player = ItemGroup_DesignPlayer(item);
    int slot = ItemGroup_DesignSlot(item);
    DesignManager *designs = (DesignManager *) (uintptr_t) DesignManager_Get();
    return (G3dResTex *) (uintptr_t) DesignManager_PlayerTexture(designs, (u8) player, (u8) slot);
}

/* The house room shown, NULL outside the house or without a record. */
static HouseRoom *RoomSurface_house_room(void)
{
    if (!SceneKinds_CurrentIsHouseRoom()) {
        return NULL;
    }
    return HouseRecord_Room(&data_021ebcd4, SceneKinds_CurrentHouseRoomIndex());
}

/* func_ov004_02232508 (at the room's release): the carpet's copy taken off the queue. */
void RoomCarpet_End(RoomCarpet *self)
{
    VramCopyMaterial_End(&self->copy);
}
CLEAN_AS(func_ov004_02232508, RoomCarpet_End)

/* The item taken: the shown one kept as replaced, `*item` shown (read again), the house room's
 * record and the scene's carpet given it. */
static void RoomCarpet_take(RoomCarpet *self, const ItemCode *item, int mode)
{
    self->replaced = self->code;
    self->code = *item;
    RoomCarpet_Record(self, &self->code, mode);
    RoomInterior_SetSceneCarpet(SceneQuery_Current(), &self->code);
}

/* func_ov004_02232514: puts carpet `*item` down on `model`, with `mode`; whether it did. Nothing
 * happens when the model has no material "m_dummy_floor". The item shown with the same mode is
 * taken as it is. A carpet is taken once its file is loaded and its copy queued (outside Nook's
 * shop the material is first bound back to the room's "dummy_floor" texture); a player's
 * design by binding its texture to the material. Anything else is refused.
 * QUIRK: a carpet taken from its file leaves the part's mode as it was (the record and the
 * scene still get `mode`); the other two ways keep `mode`. */
int RoomCarpet_Set(RoomCarpet *self, ItemCode *item, u8 *model, int mode)
{
    if (G3dRes_MaterialIndex(model, data_ov004_02255a80) == -1) {
        return 0;
    }
    if (RoomSurface_same_item(&self->code, item) && self->mode == mode) {
        self->mode = mode;
        RoomCarpet_take(self, item, mode);
        return 1;
    }

    ItemCode code = *item;
    if (RoomSurface_in(code, ROOM_SURFACE_CARPET_FIRST, ROOM_SURFACE_CARPET_LAST)) {
        if (!CarpetTexture_Load(self->file, item)) {
            return 0;
        }
        if (!SceneQuery_CurrentInNook()) {
            MaterialBind_SetByName(&self->bind, self->texture, data_ov004_02255b18, data_ov004_02255b24);
        }
        if (!VramCopyMaterial_Queue(&self->copy, model, data_ov004_02255a80, CarpetTexture_Textures(self->file), 0, 0)) {
            return 0;
        }
        RoomCarpet_take(self, item, mode);
        return 1;
    }
    if (RoomSurface_in(code, ROOM_SURFACE_DESIGN_FIRST, ROOM_SURFACE_DESIGN_LAST)) {
        MaterialBind_Set(&self->bind, RoomSurface_design_texture(item), 0, 0);
        self->replaced = self->code;
        self->code = *item;
        self->mode = mode;
        RoomCarpet_Record(self, &self->code, mode);
        RoomInterior_SetSceneCarpet(SceneQuery_Current(), &self->code);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02232514, RoomCarpet_Set)

/* func_ov004_022326a8: in a room of the player's house, the room's record given the carpet
 * and its mode. */
void RoomCarpet_Record(RoomCarpet *self, const ItemCode *code, int mode)
{
    (void) self;
    HouseRoom *room = RoomSurface_house_room();
    if (room != NULL) {
        HouseRecord_RoomSetCarpet(room, code, mode);
    }
}
CLEAN_AS(func_ov004_022326a8, RoomCarpet_Record)

/* func_ov004_022326dc: RoomCarpet_Set with the item `code`. */
int RoomCarpet_SetCode(RoomCarpet *self, int code, u8 *model, int mode)
{
    ItemCode item = (ItemCode) code;
    return RoomCarpet_Set(self, &item, model, mode);
}
CLEAN_AS(func_ov004_022326dc, RoomCarpet_SetCode)

/* func_ov004_022326f4: with a texture resource, the binding picks the model's material
 * "m_dummy_floor" and the resource is kept; whether there was one. */
int RoomCarpet_PickMaterial(RoomCarpet *self, u8 *model, G3dResTex *texture)
{
    if (texture == NULL) {
        return 0;
    }
    MaterialBind_PickByName(&self->bind, model, data_ov004_02255aa0);
    self->texture = texture;
    return 1;
}
CLEAN_AS(func_ov004_022326f4, RoomCarpet_PickMaterial)

/* func_ov004_02232728 */
int RoomCarpet_Mode(RoomCarpet *self)
{
    return self->mode;
}
CLEAN_AS(func_ov004_02232728, RoomCarpet_Mode)

/* func_ov004_02232734 */
ItemCode *RoomCarpet_Replaced(RoomCarpet *self)
{
    return &self->replaced;
}
CLEAN_AS(func_ov004_02232734, RoomCarpet_Replaced)

/* func_ov004_02232738 */
ItemCode *RoomCarpet_Code(RoomCarpet *self)
{
    return &self->code;
}
CLEAN_AS(func_ov004_02232738, RoomCarpet_Code)

/* func_ov004_0223273c: only the binding is taken down. */
RoomCarpet *RoomCarpet_Destruct(RoomCarpet *self)
{
    MaterialBind_Destruct(&self->bind);
    return self;
}
CLEAN_AS(func_ov004_0223273c, RoomCarpet_Destruct)

/* func_ov004_02232754: no item (both codes 0xfff1, set before and after the members are
 * built), mode 0. */
RoomCarpet *RoomCarpet_Construct(RoomCarpet *self)
{
    self->replaced = ITEM_CODE_NONE;
    self->code = ITEM_CODE_NONE;
    VramCopyMaterial_Construct(&self->copy);
    CarpetTexture_Construct(self->file);
    MaterialBind_Construct(&self->bind);
    self->replaced = ITEM_CODE_NONE;
    self->code = ITEM_CODE_NONE;
    self->mode = 0;
    return self;
}
CLEAN_AS(func_ov004_02232754, RoomCarpet_Construct)

/* func_ov004_02232794 (at the room's release): the wallpaper's copy taken off the queue. */
void RoomWallpaper_End(RoomWallpaper *self)
{
    VramCopyMaterial_End(&self->copy);
}
CLEAN_AS(func_ov004_02232794, RoomWallpaper_End)

static void RoomWallpaper_take(RoomWallpaper *self, const ItemCode *item, int mode)
{
    self->replaced = self->code;
    self->code = *item;
    RoomWallpaper_Record(self, &self->code, mode);
    RoomInterior_SetSceneWallpaper(SceneQuery_Current(), &self->code);
}

/* func_ov004_022327a0: RoomCarpet_Set for the wallpaper: a wallpaper item (0x1100-0x1143) or a
 * player's design, on the model's material "m_dummy_wall" ("dummy_wall" of the room's texture).
 * QUIRK: a wallpaper taken from its file leaves the part's mode as it was. */
int RoomWallpaper_Set(RoomWallpaper *self, ItemCode *item, u8 *model, int mode)
{
    if (G3dRes_MaterialIndex(model, data_ov004_02255a84) == -1) {
        return 0;
    }
    if (RoomSurface_same_item(&self->code, item) && self->mode == mode) {
        self->mode = mode;
        RoomWallpaper_take(self, item, mode);
        return 1;
    }

    ItemCode code = *item;
    if (RoomSurface_in(code, ROOM_SURFACE_WALLPAPER_FIRST, ROOM_SURFACE_WALLPAPER_LAST)) {
        if (!WallpaperFile_Load(self->file, item)) {
            return 0;
        }
        if (!SceneQuery_CurrentInNook()) {
            MaterialBind_SetByName(&self->bind, self->texture, data_ov004_02255b34, data_ov004_02255b40);
        }
        G3dResTex *textures = (G3dResTex *) (uintptr_t) WallpaperFile_Texture(self->file);
        if (!VramCopyMaterial_Queue(&self->copy, model, data_ov004_02255a84, textures, 0, 0)) {
            return 0;
        }
        RoomWallpaper_take(self, item, mode);
        return 1;
    }
    if (RoomSurface_in(code, ROOM_SURFACE_DESIGN_FIRST, ROOM_SURFACE_DESIGN_LAST)) {
        MaterialBind_Set(&self->bind, RoomSurface_design_texture(item), 0, 0);
        self->replaced = self->code;
        self->code = *item;
        self->mode = mode;
        RoomWallpaper_Record(self, &self->code, mode);
        RoomInterior_SetSceneWallpaper(SceneQuery_Current(), &self->code);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022327a0, RoomWallpaper_Set)

/* func_ov004_02232934: in a room of the player's house, the room's record given the
 * wallpaper and its mode. */
void RoomWallpaper_Record(RoomWallpaper *self, const ItemCode *code, int mode)
{
    (void) self;
    HouseRoom *room = RoomSurface_house_room();
    if (room != NULL) {
        HouseRecord_RoomSetWallpaper(room, code, mode);
    }
}
CLEAN_AS(func_ov004_02232934, RoomWallpaper_Record)

/* func_ov004_02232968: RoomWallpaper_Set with the item `code`. */
int RoomWallpaper_SetCode(RoomWallpaper *self, int code, u8 *model, int mode)
{
    ItemCode item = (ItemCode) code;
    return RoomWallpaper_Set(self, &item, model, mode);
}
CLEAN_AS(func_ov004_02232968, RoomWallpaper_SetCode)

/* func_ov004_02232980: with a texture resource, the binding picks "m_dummy_wall" and the
 * resource is kept; whether there was one. */
int RoomWallpaper_PickMaterial(RoomWallpaper *self, u8 *model, G3dResTex *texture)
{
    if (texture == NULL) {
        return 0;
    }
    MaterialBind_PickByName(&self->bind, model, data_ov004_02255a90);
    self->texture = texture;
    return 1;
}
CLEAN_AS(func_ov004_02232980, RoomWallpaper_PickMaterial)

/* func_ov004_022329b4 */
int RoomWallpaper_Mode(RoomWallpaper *self)
{
    return self->mode;
}
CLEAN_AS(func_ov004_022329b4, RoomWallpaper_Mode)

/* func_ov004_022329c0 */
ItemCode *RoomWallpaper_Replaced(RoomWallpaper *self)
{
    return &self->replaced;
}
CLEAN_AS(func_ov004_022329c0, RoomWallpaper_Replaced)

/* func_ov004_022329c4 */
ItemCode *RoomWallpaper_Code(RoomWallpaper *self)
{
    return &self->code;
}
CLEAN_AS(func_ov004_022329c4, RoomWallpaper_Code)

/* func_ov004_022329c8: only the binding is taken down. */
RoomWallpaper *RoomWallpaper_Destruct(RoomWallpaper *self)
{
    MaterialBind_Destruct(&self->bind);
    return self;
}
CLEAN_AS(func_ov004_022329c8, RoomWallpaper_Destruct)

/* func_ov004_022329e0: no item, mode 0. */
RoomWallpaper *RoomWallpaper_Construct(RoomWallpaper *self)
{
    self->replaced = ITEM_CODE_NONE;
    self->code = ITEM_CODE_NONE;
    VramCopyMaterial_Construct(&self->copy);
    WallpaperFile_Construct(self->file);
    MaterialBind_Construct(&self->bind);
    self->replaced = ITEM_CODE_NONE;
    self->code = ITEM_CODE_NONE;
    self->mode = 0;
    return self;
}
CLEAN_AS(func_ov004_022329e0, RoomWallpaper_Construct)
