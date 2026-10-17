/* The town map's picture and its markers (town_map_image.h), built for the menu's map tab. */
#include "town_map_image.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"
#include "main/building_shapes.h"
#include "main/collision_map.h"
#include "main/collision_query.h"
#include "main/house_record.h"
#include "main/map_code.h"
#include "main/unit_type_info.h"
#include "main/villager_home.h"
#include "main/villager_plot_tile.h"
#include "main/villager_roster.h"

static_assert(sizeof(TownMapMarker) == 6, "marker");
static_assert(offsetof(TownMapImage, markers) == TOWN_MAP_IMAGE_PIXELS_SIZE, "markers");
static_assert(sizeof(TownMapImage) == 0x2066, "size (func_ov117_02299a18)");

/* The picture while it is built, or NULL. */
extern TownMapImage *data_ov117_0229a320;

/* The villagers (0x7ec bytes each, main/villager_roster.h). */
extern u8 data_021e5a2c[];

/* The player's house record (main/house_record.h). */
extern u8 data_021ebcd4[];

/* The block's constructor and destructor, as the game hands them to __cxa_vec_ctor
 * (TownMapImage_ClearBlock, TownMapImage_DestructBlock). */
extern void func_ov117_02299c50(void *block);
extern void func_ov117_02299c4c(void *block);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The collision map the acres' units are read from (main/collision_map.h): the town's while
 * the picture is drawn and the spots looked for. */
#define TOWN_MAP_IMAGE_COLLISION_TOWN 1
#define TOWN_MAP_IMAGE_COLLISION_DEFAULT 0

/* The acres' flag whose acres have a spot (main/acre_kind.h). */
#define TOWN_MAP_IMAGE_SPOT_ACRE_FLAG 4
#define TOWN_MAP_IMAGE_NO_SPOT 4 /* CollisionQuery_FindSpotInBlock found none */

/* The codes of the buildings marked. */
#define TOWN_MAP_IMAGE_CODE_PLAYER_HOUSE_FIRST 0x5014
#define TOWN_MAP_IMAGE_CODE_PLAYER_HOUSE_LAST 0x501a
#define TOWN_MAP_IMAGE_CODE_STORE_FIRST 0x500d
#define TOWN_MAP_IMAGE_CODE_STORE_LAST 0x5010

static AcreMap *town_map(void)
{
    return (AcreMap *) (uintptr_t) AcreMap_Town();
}

/* func_ov117_022999a0: the picture copied to `pixels_out` and, when `markers_out` is not 0,
 * its markers to `markers_out`; the picture freed. Nothing without a picture. */
void TownMapImage_Finish(int pixels_out, int markers_out)
{
    TownMapImage *image = data_ov117_0229a320;
    if (image == NULL) {
        return;
    }
    TownMapImage_CopyPixels((int) (uintptr_t) image, pixels_out);
    if (markers_out != 0) {
        TownMapMarkers_Copy((TownMapMarker *) (uintptr_t) TownMapImage_Markers((int) (uintptr_t) image),
                            (TownMapMarker *) (uintptr_t) markers_out);
    }
    Heap_FreeCurrent(image);
    data_ov117_0229a320 = NULL;
}
CLEAN_AS(func_ov117_022999a0, TownMapImage_Finish)

/* func_ov117_022999e0: a set of the markers put (TownMapMarkSet), when there is a picture. */
void TownMapImage_Mark(int set)
{
    if (data_ov117_0229a320 != NULL) {
        TownMapImage_MarkSet((unsigned int) (uintptr_t) data_ov117_0229a320, set);
    }
}
CLEAN_AS(func_ov117_022999e0, TownMapImage_Mark)

/* func_ov117_022999fc: a row of acres drawn, when there is a picture. */
void TownMapImage_DrawRow(int row)
{
    if (data_ov117_0229a320 != NULL) {
        TownMapImage_DrawRowOf((int) (uintptr_t) data_ov117_0229a320, row);
    }
}
CLEAN_AS(func_ov117_022999fc, TownMapImage_DrawRow)

/* func_ov117_02299a18: a picture from the current heap, unless there is one: blank, with no
 * markers. */
void TownMapImage_Create(void)
{
    if (data_ov117_0229a320 != NULL) {
        return;
    }
    data_ov117_0229a320 = Heap_AllocCurrent(sizeof(TownMapImage));
    if (data_ov117_0229a320 != NULL) {
        TownMapImage_Construct(data_ov117_0229a320);
    }
}
CLEAN_AS(func_ov117_02299a18, TownMapImage_Create)

/* func_ov117_02299a48: the whole picture at once: its four rows of acres, the villagers'
 * houses and the other markers, copied out and freed. */
void TownMapImage_Build(int pixels_out, int markers_out)
{
    TownMapImage_Create();
    for (int row = 0; row < TOWN_MAP_IMAGE_ACRES; row++) {
        TownMapImage_DrawRow(row);
    }
    TownMapImage_Mark(TOWN_MAP_MARK_VILLAGERS);
    TownMapImage_Mark(TOWN_MAP_MARK_OTHERS);
    TownMapImage_Finish(pixels_out, markers_out);
}
CLEAN_AS(func_ov117_02299a48, TownMapImage_Build)

/* func_ov117_02299a88: the picture's markers. */
int TownMapImage_Markers(int image)
{
    return (int) ((u32) image + TOWN_MAP_IMAGE_PIXELS_SIZE);
}
CLEAN_AS(func_ov117_02299a88, TownMapImage_Markers)

/* func_ov117_02299a94: the picture's pixels copied to `pixels_out`. */
void TownMapImage_CopyPixels(int image, int pixels_out)
{
    MI_CpuCopy8((const void *) (uintptr_t) image, (void *) (uintptr_t) pixels_out, TOWN_MAP_IMAGE_PIXELS_SIZE);
}
CLEAN_AS(func_ov117_02299a94, TownMapImage_CopyPixels)

/* func_ov117_02299aa4: the block of the acre at (column, row); the first block for one outside
 * the 4 x 4. */
TownMapBlock *TownMapImage_Block(TownMapBlock *blocks, unsigned int column, unsigned int row)
{
    if (column >= TOWN_MAP_IMAGE_ACRES || row >= TOWN_MAP_IMAGE_ACRES) {
        return blocks;
    }
    return &blocks[column + row * TOWN_MAP_IMAGE_ACRES];
}
CLEAN_AS(func_ov117_02299aa4, TownMapImage_Block)

/* func_ov117_02299ab8: the villagers' houses marked for set 0, the other markers for any other
 * set. */
void TownMapImage_MarkSet(unsigned int image, int set)
{
    TownMapMarker *markers = (TownMapMarker *) (uintptr_t) (image + TOWN_MAP_IMAGE_PIXELS_SIZE);
    if (set == TOWN_MAP_MARK_VILLAGERS) {
        TownMapImage_MarkVillagers(markers);
    } else {
        TownMapImage_MarkOthers(markers);
    }
}
CLEAN_AS(func_ov117_02299ab8, TownMapImage_MarkSet)

/* func_ov117_02299adc: the four acres of a row (`row` & 3) drawn into their blocks. */
void TownMapImage_DrawRowOf(int image, int row)
{
    unsigned int acre_row = (unsigned int) row & 3;
    for (unsigned int column = 0; column < TOWN_MAP_IMAGE_ACRES; column++) {
        TownMapBlock *block = TownMapImage_Block((TownMapBlock *) (uintptr_t) image, column, acre_row);
        TownMapImage_DrawBlock(block->pixels, (int) column, (int) acre_row);
    }
}
CLEAN_AS(func_ov117_02299adc, TownMapImage_DrawRowOf)

/* func_ov117_02299b08: the sixteen blocks cleared (__cxa_vec_ctor), the markers constructed. */
TownMapImage *TownMapImage_Construct(TownMapImage *image)
{
    __cxa_vec_ctor(image->blocks, TOWN_MAP_IMAGE_BLOCKS, sizeof(TownMapBlock), func_ov117_02299c50, func_ov117_02299c4c);
    TownMapMarkers_Construct(image->markers);
    return image;
}
CLEAN_AS(func_ov117_02299b08, TownMapImage_Construct)

/* func_ov117_02299b40: the acre (column, row) inside the town's border drawn into a cleared
 * block: its 16 x 16 units of the town's collision map, each 2 x 2 pixels of the four colours
 * of the unit's type (left top, right top, left bottom, right bottom), in 16-colour characters
 * of 8 x 8 pixels, two pixels to a byte (the left one in the low half). A unit with no colours
 * leaves its pixels as they were: the colours are ORed into the block. */
void TownMapImage_DrawBlock(u8 *pixels, int column, int row)
{
    CollisionMap_Select(TOWN_MAP_IMAGE_COLLISION_TOWN);
    unsigned int unit_x0 = (unsigned int) column * 16 + 16;
    unsigned int unit_z0 = (unsigned int) row * 16 + 16;
    unsigned int n = 0;
    for (unsigned int char_row = 0; char_row < 4; char_row++) {
        for (unsigned int char_column = 0; char_column < 4; char_column++) {
            for (unsigned int py = 0; py < 8; py++) {
                unsigned int y = char_row * 8 + py;
                for (unsigned int px = 0; px < 8; px++) {
                    unsigned int x = char_column * 8 + px;
                    u8 colours[4];
                    u8 value = 0;
                    if (UnitTypeInfo_Bytes18At(colours, (int) (unit_x0 + (x >> 1)), (int) (unit_z0 + (y >> 1)))) {
                        int top = (y & 1) == 0;
                        if ((x & 1) == 0) {
                            value = (u8) ((top ? colours[0] : colours[2]) & 0xf);
                        } else {
                            value = (u8) (((top ? colours[1] : colours[3]) & 0xf) << 4);
                        }
                    }
                    pixels[n >> 1] |= value;
                    n++;
                }
            }
        }
    }
    CollisionMap_Select(TOWN_MAP_IMAGE_COLLISION_DEFAULT);
}
CLEAN_AS(func_ov117_02299b40, TownMapImage_DrawBlock)

/* func_ov117_02299c4c: a block's destructor: nothing. */
void TownMapImage_DestructBlock(void *block)
{
    (void) block;
}
CLEAN_AS(func_ov117_02299c4c, TownMapImage_DestructBlock)

/* func_ov117_02299c50: a block's constructor: all its pixels 0. */
void TownMapImage_ClearBlock(unsigned char *block)
{
    memset(block, 0, TOWN_MAP_IMAGE_BLOCK_SIZE);
}
CLEAN_AS(func_ov117_02299c50, TownMapImage_ClearBlock)

/* func_ov117_02299c68: all the markers but the villagers' houses.
 * QUIRK: the spots take places 0, 1, 2 and on, one for each found; a fourth spot would take the
 * first villager's place (3), and so on. */
void TownMapImage_MarkOthers(TownMapMarker *markers)
{
    TownMapImage_MarkSpots(markers);
    TownMapImage_Mark5000(markers);
    TownMapImage_Mark500B(markers);
    TownMapImage_MarkPlayerHouse(markers);
    TownMapImage_Mark5011(markers);
    TownMapImage_Mark500C(markers);
    TownMapImage_MarkStore(markers);
}
CLEAN_AS(func_ov117_02299c68, TownMapImage_MarkOthers)

/* func_ov117_02299c9c */
void TownMapImage_MarkVillagers(TownMapMarker *markers)
{
    TownMapImage_MarkVillagerHouses(markers);
}
CLEAN_AS(func_ov117_02299c9c, TownMapImage_MarkVillagers)

/* func_ov117_02299ca4: the 17 markers copied, field by field. */
void TownMapMarkers_Copy(TownMapMarker *from, TownMapMarker *to)
{
    for (unsigned int i = 0; i < TOWN_MAP_MARKERS; i++) {
        to[i].x = from[i].x;
        to[i].y = from[i].y;
        to[i].kind = from[i].kind;
    }
}
CLEAN_AS(func_ov117_02299ca4, TownMapMarkers_Copy)

/* A tile (x, z) of the town map as a place on the picture: the middle of its 2 x 2 pixels,
 * moved by the centre of the shape of the building `code` when it has one (in 1/2048 tile). */
static void tile_to_picture(int *x, int *z, u16 *code)
{
    *x = *x * 2 + 1;
    *z = *z * 2 + 1;
    BuildingShapeEntry *shape = BuildingShapes_Of(code);
    if (shape != NULL) {
        int centre_x, centre_z, width, depth;
        BuildingShapes_Bounds(shape, &centre_x, &centre_z, &width, &depth);
        *x += centre_x >> 11;
        *z += centre_z >> 11;
    }
}

/* The marker `index` put on the first item of codes first-last of the town map with any of
 * `flags`, moved by the centre of its building's shape: the shape of the code found on its tile
 * when `code_on_tile`, else of `first`. Nothing when there is no such item. */
static void mark_building(TownMapMarker *markers, AcreMap *map, int index, u16 *first, u16 *last, int flags, int code_on_tile)
{
    int acre_x, acre_z, offset_x, offset_z;
    if (AcreTile_FindItemAnyFlag(map, &acre_x, &acre_z, &offset_x, &offset_z, first, last, flags, 0) == 0) {
        return;
    }
    int x, z;
    AcreTile_TileOfAcre(&x, &z, acre_x, acre_z, offset_x, offset_z);
    u16 *code = first;
    if (code_on_tile) {
        int tile_acre_x = x >> 4;
        int tile_acre_z = z >> 4;
        code = AcreTile_ItemInAcre(map, (u32) tile_acre_x, (u32) tile_acre_z, x - tile_acre_x * 16, z - tile_acre_z * 16, 0);
    }
    tile_to_picture(&x, &z, code);
    TownMapMarkers_Set(markers, index, (u16) x, (u16) z, 0);
}

/* func_ov117_02299cd0: the store (codes 0x500d-0x5010, flag 2), by the shape of the one found. */
void TownMapImage_MarkStore(TownMapMarker *markers)
{
    AcreMap *map = town_map();
    if (map == NULL) {
        return;
    }
    u16 codes[2] = {TOWN_MAP_IMAGE_CODE_STORE_FIRST, TOWN_MAP_IMAGE_CODE_STORE_LAST};
    mark_building(markers, map, TOWN_MAP_MARKER_STORE, &codes[0], &codes[1], 2, 1);
}
CLEAN_AS(func_ov117_02299cd0, TownMapImage_MarkStore)

/* The marker `index` on building `code` (alone in its range) with any of `flags`. */
static void mark_single_building(TownMapMarker *markers, int index, u16 code, int flags)
{
    AcreMap *map = town_map();
    if (map == NULL) {
        return;
    }
    mark_building(markers, map, index, &code, &code, flags, 0);
}

/* func_ov117_02299d9c: building 0x5000 (flag 0x200). */
void TownMapImage_Mark5000(TownMapMarker *markers)
{
    mark_single_building(markers, TOWN_MAP_MARKER_5000, 0x5000, 0x200);
}
CLEAN_AS(func_ov117_02299d9c, TownMapImage_Mark5000)

/* func_ov117_02299e44: building 0x500c (flag 2). */
void TownMapImage_Mark500C(TownMapMarker *markers)
{
    mark_single_building(markers, TOWN_MAP_MARKER_500C, 0x500c, 2);
}
CLEAN_AS(func_ov117_02299e44, TownMapImage_Mark500C)

/* func_ov117_02299ee8: building 0x500b (no flags). */
void TownMapImage_Mark500B(TownMapMarker *markers)
{
    mark_single_building(markers, TOWN_MAP_MARKER_500B, 0x500b, 0);
}
CLEAN_AS(func_ov117_02299ee8, TownMapImage_Mark500B)

/* func_ov117_02299f8c: building 0x5011 (flag 0x800). */
void TownMapImage_Mark5011(TownMapMarker *markers)
{
    mark_single_building(markers, TOWN_MAP_MARKER_5011, 0x5011, 0x800);
}
CLEAN_AS(func_ov117_02299f8c, TownMapImage_Mark5011)

/* func_ov117_0229a034: the players' house (codes 0x5014-0x501a, flag 1), by the shape of the
 * one found.
 * QUIRK: the house's size is asked for (HouseRecord_Size) and not used. */
void TownMapImage_MarkPlayerHouse(TownMapMarker *markers)
{
    AcreMap *map = town_map();
    if (map == NULL) {
        return;
    }
    HouseRecord_Size((const HouseRecord *) (void *) data_021ebcd4);
    u16 codes[2] = {TOWN_MAP_IMAGE_CODE_PLAYER_HOUSE_FIRST, TOWN_MAP_IMAGE_CODE_PLAYER_HOUSE_LAST};
    mark_building(markers, map, TOWN_MAP_MARKER_PLAYER_HOUSE, &codes[0], &codes[1], 1, 1);
}
CLEAN_AS(func_ov117_0229a034, TownMapImage_MarkPlayerHouse)

/* func_ov117_0229a10c: the houses of the eight villagers that have one, at their house's tile
 * moved by the house's shape. */
void TownMapImage_MarkVillagerHouses(TownMapMarker *markers)
{
    for (int i = 0; i < 8; i++) {
        u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, i);
        if (VillagerPlotTile_IsSet(VillagerHome_Tile(villager)) == 0) {
            continue;
        }
        u16 code = MapCode_VillagerHouse((u32) i);
        int x = VillagerHome_Tile(villager)->x;
        int z = VillagerHome_Tile(villager)->z;
        tile_to_picture(&x, &z, &code);
        TownMapMarkers_Set(markers, TOWN_MAP_MARKER_VILLAGERS + i, (u16) x, (u16) z, 0);
    }
}
CLEAN_AS(func_ov117_0229a10c, TownMapImage_MarkVillagerHouses)

/* func_ov117_0229a194: the spots of the acres inside the border that have flag 4, on the town's
 * collision map: each found one marked from place 0 on with its kind (0-3), moved from the
 * middle of its unit's pixels by the kind: 0 by (1, 3), 1 by (3, 1), 2 by (0, 4), 3 by (2, 4).
 * REQUIRES: there is a town map (the game reads it without a test). */
void TownMapImage_MarkSpots(TownMapMarker *markers)
{
    CollisionMap_Select(TOWN_MAP_IMAGE_COLLISION_TOWN);
    int count = 0;
    AcreMap *map = town_map();
    for (int row = 1; row < 5; row++) {
        for (int column = 1; column < 5; column++) {
            AcreRecord *acre = NULL;
            if ((u32) column < (u32) map->acres_wide && (u32) row < (u32) map->acres_high && map->acres != NULL) {
                acre = (AcreRecord *) (void *) (map->acres + ACRE_MAP_ACRE_SIZE * (column + row * map->acres_wide));
            }
            if ((AcreRecord_Flags(acre) & TOWN_MAP_IMAGE_SPOT_ACRE_FLAG) == 0) {
                continue;
            }
            int x, z;
            int kind = CollisionQuery_FindSpotInBlock(&x, &z, column, row);
            if (kind == TOWN_MAP_IMAGE_NO_SPOT) {
                continue;
            }
            x = x * 2 + 1;
            z = z * 2 + 1;
            switch (kind) {
                case 0:
                    x += 1;
                    z += 3;
                    break;
                case 1:
                    x += 3;
                    z += 1;
                    break;
                case 2:
                    z += 4;
                    break;
                case 3:
                    x += 2;
                    z += 4;
                    break;
            }
            TownMapMarkers_Set(markers, count, (u16) x, (u16) z, (u8) kind);
            count++;
        }
    }
    CollisionMap_Select(TOWN_MAP_IMAGE_COLLISION_DEFAULT);
}
CLEAN_AS(func_ov117_0229a194, TownMapImage_MarkSpots)

/* func_ov117_0229a26c: a marker's kind; the first marker's for an index past the list. */
unsigned char TownMapMarkers_Kind(TownMapMarker *markers, unsigned int index)
{
    if (index < TOWN_MAP_MARKERS) {
        return markers[index].kind;
    }
    return markers[0].kind;
}
CLEAN_AS(func_ov117_0229a26c, TownMapMarkers_Kind)

/* func_ov117_0229a280: a marker that is set (neither x nor y -1), or NULL. */
TownMapMarker *TownMapMarkers_Get(TownMapMarker *markers, unsigned int index)
{
    if (index >= TOWN_MAP_MARKERS) {
        return NULL;
    }
    TownMapMarker *marker = &markers[index];
    if (marker->x == -1 || marker->y == -1) {
        return NULL;
    }
    return marker;
}
CLEAN_AS(func_ov117_0229a280, TownMapMarkers_Get)

/* func_ov117_0229a2a4: a marker set, for an index below 17.
 * QUIRK: the index is compared signed: a negative one writes before the list (the game passes
 * none). */
void TownMapMarkers_Set(TownMapMarker *markers, int index, u16 x, u16 y, u8 kind)
{
    if (index >= TOWN_MAP_MARKERS) {
        return;
    }
    TownMapMarker *marker = (TownMapMarker *) (uintptr_t) ((uintptr_t) markers + (uintptr_t) (index * 6));
    marker->x = (s16) x;
    marker->y = (s16) y;
    marker->kind = kind;
}
CLEAN_AS(func_ov117_0229a2a4, TownMapMarkers_Set)

/* func_ov117_0229a2c8: no markers: each at (-1, -1), kind 0. */
void TownMapMarkers_Clear(TownMapMarker *markers)
{
    for (unsigned int i = 0; i < TOWN_MAP_MARKERS; i++) {
        markers[i].x = -1;
        markers[i].y = -1;
        markers[i].kind = 0;
    }
}
CLEAN_AS(func_ov117_0229a2c8, TownMapMarkers_Clear)

/* func_ov117_0229a2ec: the markers' destructor: nothing. */
void TownMapMarkers_Destruct(void *markers)
{
    (void) markers;
}
CLEAN_AS(func_ov117_0229a2ec, TownMapMarkers_Destruct)

/* func_ov117_0229a2f0: the markers constructed at (0, 0), then cleared. */
TownMapMarker *TownMapMarkers_Construct(TownMapMarker *markers)
{
    for (unsigned int i = 0; i < TOWN_MAP_MARKERS; i++) {
        markers[i].x = 0;
        markers[i].y = 0;
    }
    TownMapMarkers_Clear(markers);
    return markers;
}
CLEAN_AS(func_ov117_0229a2f0, TownMapMarkers_Construct)
