/* The town map's picture, built by overlay 117 for the map tab of the menu (overlay 118, tab 5
 * of the menu's bar, ov090/menu_tabs.h, overlay group 7 with overlay 117).
 *
 * The picture (TownMapImage, 0x2066 bytes from the current heap, kept at data_ov117_0229a320
 * while it is built) is the 4 x 4 acres inside the town's border, each a block of 4 x 4
 * 16-colour characters (512 bytes, 32 x 32 pixels): each tile of an acre is 2 x 2 pixels, the
 * four colours its unit's type gives (UnitTypeInfo_Bytes18At). Then 17 markers, each a place
 * on the picture and a kind:
 *
 * - 0-2: the spots found in acres of flag 4 (CollisionQuery_FindSpotInBlock), whose kind is the
 *   spot's (0-3);
 * - 3-10: the houses of the eight villagers;
 * - 11-16: the buildings found on the town map: the players' house (0x5014-0x501a), building
 *   0x5000, building 0x5011, the store (0x500d-0x5010), building 0x500c and building 0x500b.
 *
 * Overlay 118 asks for the picture one acre row at a time (TownMapImage_DrawRow), then for the
 * markers (TownMapImage_Mark), and finally takes the picture and the markers into its own
 * memory (TownMapImage_Finish). */
#ifndef CLEAN_OV117_TOWN_MAP_IMAGE_H
#define CLEAN_OV117_TOWN_MAP_IMAGE_H

#include "types.h"

#define TOWN_MAP_IMAGE_ACRES 4 /* acres to a side */
#define TOWN_MAP_IMAGE_BLOCKS (TOWN_MAP_IMAGE_ACRES * TOWN_MAP_IMAGE_ACRES)
#define TOWN_MAP_IMAGE_BLOCK_SIZE 0x200
#define TOWN_MAP_IMAGE_PIXELS_SIZE (TOWN_MAP_IMAGE_BLOCKS * TOWN_MAP_IMAGE_BLOCK_SIZE)
#define TOWN_MAP_MARKERS 17

/* The markers' places in the list. */
enum TownMapMarkerIndex {
    TOWN_MAP_MARKER_SPOTS = 0,     /* 0-2 */
    TOWN_MAP_MARKER_VILLAGERS = 3, /* 3-10, by villager */
    TOWN_MAP_MARKER_PLAYER_HOUSE = 0x0b,
    TOWN_MAP_MARKER_5000 = 0x0c,
    TOWN_MAP_MARKER_5011 = 0x0d,
    TOWN_MAP_MARKER_STORE = 0x0e,
    TOWN_MAP_MARKER_500C = 0x0f,
    TOWN_MAP_MARKER_500B = 0x10
};

/* Which markers TownMapImage_Mark puts. */
enum TownMapMarkSet {
    TOWN_MAP_MARK_VILLAGERS = 0, /* the villagers' houses; any other value: all the others */
    TOWN_MAP_MARK_OTHERS = 1
};

/* A marker: (-1, -1) when there is none. */
typedef struct TownMapMarker {
    s16 x;
    s16 y;
    u8 kind;
    u8 pad_05;
} TownMapMarker;

typedef struct TownMapBlock {
    u8 pixels[TOWN_MAP_IMAGE_BLOCK_SIZE]; /* 16 characters, row by row */
} TownMapBlock;

typedef struct TownMapImage {
    TownMapBlock blocks[TOWN_MAP_IMAGE_BLOCKS]; /* 0x0000: acre (column, row) at column + row * 4 */
    TownMapMarker markers[TOWN_MAP_MARKERS];    /* 0x2000 */
} TownMapImage;

void TownMapImage_Finish(int pixels_out, int markers_out);
void TownMapImage_Mark(int set);
void TownMapImage_DrawRow(int row);
void TownMapImage_Create(void);
void TownMapImage_Build(int pixels_out, int markers_out);
int TownMapImage_Markers(int image);
void TownMapImage_CopyPixels(int image, int pixels_out);
TownMapBlock *TownMapImage_Block(TownMapBlock *blocks, unsigned int column, unsigned int row);
void TownMapImage_MarkSet(unsigned int image, int set);
void TownMapImage_DrawRowOf(int image, int row);
TownMapImage *TownMapImage_Construct(TownMapImage *image);
void TownMapImage_DrawBlock(u8 *pixels, int column, int row);
void TownMapImage_DestructBlock(void *block);
void TownMapImage_ClearBlock(unsigned char *block);
void TownMapImage_MarkOthers(TownMapMarker *markers);
void TownMapImage_MarkVillagers(TownMapMarker *markers);
void TownMapMarkers_Copy(TownMapMarker *from, TownMapMarker *to);
void TownMapImage_MarkStore(TownMapMarker *markers);
void TownMapImage_Mark5000(TownMapMarker *markers);
void TownMapImage_Mark500C(TownMapMarker *markers);
void TownMapImage_Mark500B(TownMapMarker *markers);
void TownMapImage_Mark5011(TownMapMarker *markers);
void TownMapImage_MarkPlayerHouse(TownMapMarker *markers);
void TownMapImage_MarkVillagerHouses(TownMapMarker *markers);
void TownMapImage_MarkSpots(TownMapMarker *markers);
unsigned char TownMapMarkers_Kind(TownMapMarker *markers, unsigned int index);
TownMapMarker *TownMapMarkers_Get(TownMapMarker *markers, unsigned int index);
void TownMapMarkers_Set(TownMapMarker *markers, int index, u16 x, u16 y, u8 kind);
void TownMapMarkers_Clear(TownMapMarker *markers);
void TownMapMarkers_Destruct(void *markers);
TownMapMarker *TownMapMarkers_Construct(TownMapMarker *markers);

#endif
