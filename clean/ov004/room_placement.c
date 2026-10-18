/* Putting a piece of furniture down in the room (room_placement.h). */
#include "room_placement.h"

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/furniture_info.h"
#include "main/item_code.h"
#include "main/item_footprint.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_kinds.h"
#include "main/session_players.h"
#include "main/unit_type_info.h"
#include "room_object.h"
#include "room_object_body.h"
#include "room_object_map.h"
#include "room_objects.h"

/* The player's actor (SessionPlayers_ActorOf). */
#define ROOM_PLACEMENT_PLAYER 4

/* The placement's mode for a piece found a place by the search. */
#define PLACEMENT_MODE_SEARCHED 1

/* The shapes of FurnitureInfo_Shape: two cells in a row, two by two. */
#define SHAPE_TWO_CELLS 1
#define SHAPE_TWO_BY_TWO 2

/* FurnitureInfo_DmaUnk1A of a piece that may stand on top of another. */
#define CAN_STAND_ON_TOP 2

/* The four players' records, and each player's eight items of a series. */
extern u8 data_021dc7bc[];
#define SERIES_ITEMS_PER_PLAYER 8
#define SERIES_ITEMS 0x20

/* The town's map, the room being its only acre. */
extern AcreMap *data_021c80bc;

/* The order the sides are tried in, from the side facing the actor. */
extern const u8 data_ov004_02247cdc[4];

/* The cells a two-by-two piece is tried at around the cell found, built on the first call of
 * RoomPlacement_Find (bit 0 of the guard). */
extern u32 data_ov004_022595d4;
extern FootprintCell data_ov004_02259688[4];

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* An item of the series from `first`, for this console's player and `item` (0 to 7); the first
 * of the series past the last. ROOM_PLACEMENT_NO_SPACE without the player's record. */
static int place_series(u32 *out, unsigned int item, int mode, u16 first)
{
    unsigned int player = (unsigned int) RoomPlacement_PlayerIndex();
    if (player == (unsigned int) -1) {
        return ROOM_PLACEMENT_NO_SPACE;
    }
    unsigned int index = item + player * SERIES_ITEMS_PER_PLAYER;
    ItemCode code = (ItemCode) (index < SERIES_ITEMS ? first + index * 4 : first);
    return RoomPlacement_FindNearPlayer(out, &code, mode);
}

/* func_ov004_0223b3f8: RoomPlacement_FindNearPlayer for an item of the series 0x3f24. */
int RoomPlacement_PlaceSeries3F24(u32 *out, unsigned int item, int mode)
{
    return place_series(out, item, mode, 0x3f24);
}
CLEAN_AS(func_ov004_0223b3f8, RoomPlacement_PlaceSeries3F24)

/* func_ov004_0223b440: the same for the series 0x4224. */
int RoomPlacement_PlaceSeries4224(u32 *out, unsigned int item, int mode)
{
    return place_series(out, item, mode, 0x4224);
}
CLEAN_AS(func_ov004_0223b440, RoomPlacement_PlaceSeries4224)

/* func_ov004_0223b488: the same for the series 0x3ea4. */
int RoomPlacement_PlaceSeries3EA4(u32 *out, unsigned int item, int mode)
{
    return place_series(out, item, mode, 0x3ea4);
}
CLEAN_AS(func_ov004_0223b488, RoomPlacement_PlaceSeries3EA4)

/* func_ov004_0223b4d0: the same for the series 0x3d84. */
int RoomPlacement_PlaceSeries3D84(u32 *out, unsigned int item, int mode)
{
    return place_series(out, item, mode, 0x3d84);
}
CLEAN_AS(func_ov004_0223b4d0, RoomPlacement_PlaceSeries3D84)

/* func_ov004_0223b518: the index among the four players' records (data_021dc7bc) of this
 * console's player, -1 without a current record. */
int RoomPlacement_PlayerIndex(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return -1;
    }
    return PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (void *) PlayerRecord_Player(record));
}
CLEAN_AS(func_ov004_0223b518, RoomPlacement_PlayerIndex)

/* func_ov004_0223b540: RoomPlacement_Find near the player's actor (actor 4), facing as it
 * faces; ROOM_PLACEMENT_NOT_FURNITURE without it. */
int RoomPlacement_FindNearPlayer(u32 *out, ItemCode *item, int mode)
{
    MapActor *player = SessionPlayers_ActorOf(ROOM_PLACEMENT_PLAYER);
    if (player == NULL) {
        return ROOM_PLACEMENT_NOT_FURNITURE;
    }
    return RoomPlacement_Find(out, item, &player->position, (s16) player->angle, mode);
}
CLEAN_AS(func_ov004_0223b540, RoomPlacement_FindNearPlayer)

/* For a piece two cells long placed at (x, z) facing `side`: whether the actor at `position`
 * is behind it, more than a quarter turn from the side's angle as seen from the middle of its
 * cells. When so the same piece is tried from its second cell facing the other way. */
static void try_turned(u32 *out, int x, int z, int side, int number, u8 layer, const Vec3 *position, int player_x,
                       int player_z)
{
    u16 code = ItemCode_MakeVariant(number, side);
    s16 side_angle = (s16) (side << 14);
    ItemFootprint footprint;
    ItemFootprint_Construct(&footprint, &code);
    Vec3 middle = {0, 0, 0};
    u32 count = ItemFootprint_Count(&footprint);
    for (u32 i = 0; i < count; i++) {
        int cell_x = x + ItemFootprint_Cell(&footprint, i)->x;
        int cell_z = z + ItemFootprint_Cell(&footprint, i)->y;
        Vec3 centre;
        AcreTile_TileCentre(&centre, (u32) cell_x, (u32) cell_z);
        VEC_Add(&middle, &centre, &middle);
    }
    Vec_Divide(&middle, (fx32) (count << 12));
    Vec3 delta;
    Vec_Subtract(&delta, position, &middle);
    if (Math_AbsDiff16(side_angle, Math_Atan2(delta.x, delta.z)) > 0x4000) {
        FootprintCell *first = ItemFootprint_Cell(&footprint, 1);
        FootprintCell *second = ItemFootprint_Cell(&footprint, 1);
        RoomPlacement_TryAt(out, x + first->x, z + second->y, (side + 2) & 3, number, layer, player_x, player_z);
    }
    ItemFootprint_Destruct(&footprint);
}

/* func_ov004_0223b574: a place for the furniture of `item` near an actor at `position` facing
 * `angle`. In mode ROOM_PLACEMENT_MODE_UNPLACED the placement is made at once (cell (0, 0),
 * side 0, in that mode). Otherwise, in a house's room, on top of other furniture first and
 * then on the floor, the cells of RoomObjects_CellAhead (the actor's own, ahead, to either
 * side) are tried with the four sides in data_ov004_02247cdc's order from the side facing the
 * actor (a two-by-two piece also with the cell found as any of its four corners), never
 * covering the actor's cell; the first that fits (RoomPlacement_TryAt) is taken. A piece two
 * cells long that would turn its back on the actor is tried once turned about (try_turned),
 * which replaces the placement when it fits.
 * QUIRK: the cell centre of each cell tried is worked out and not used; the first call fills in
 * the four corners. */
int RoomPlacement_Find(u32 *out, ItemCode *item, const Vec3 *position, int angle, int mode)
{
    static const FootprintCell corners[4] = {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
    if (!ItemCode_HasVariant(item)) {
        return ROOM_PLACEMENT_NOT_FURNITURE;
    }
    if (RoomObjects_FreeCount(RoomObjects_Table()) == 0) {
        return ROOM_PLACEMENT_ROOM_FULL;
    }
    if (mode == ROOM_PLACEMENT_MODE_UNPLACED) {
        *out = (u32) Placement_Make(0, 0, ItemCode_VariantItem(item), 0, 0, ROOM_PLACEMENT_MODE_UNPLACED);
        return ROOM_PLACEMENT_PLACED;
    }
    if (!SceneKinds_CurrentIsHouseRoom()) {
        return ROOM_PLACEMENT_NOT_FURNITURE;
    }
    int number = ItemCode_VariantItem(item);
    int shape = FurnitureInfo_Shape(number);
    int facing_actor = Angle_Side((s16) (angle + 0x8000));
    int player_x;
    int player_z;
    Position_Tile(&player_x, &player_z, (const Position *) (const void *) position);
    if ((data_ov004_022595d4 & 1) == 0) {
        for (int i = 0; i < 4; i++) {
            data_ov004_02259688[i] = corners[i];
        }
        data_ov004_022595d4 |= 1;
    }
    for (int layer = 1; layer >= 0; layer--) {
        for (u32 pass = 0; pass < 4; pass++) {
            int near_x;
            int near_z;
            if (!RoomObjects_CellAhead(&near_x, &near_z, position, angle, (int) pass)) {
                continue;
            }
            Vec3 near_centre;
            AcreTile_TileCentre(&near_centre, (u32) near_x, (u32) near_z);
            for (int turn = 0; turn < 4; turn++) {
                int side = (facing_actor + data_ov004_02247cdc[turn]) & 3;
                u32 tries = shape == SHAPE_TWO_BY_TWO ? 4 : 1;
                for (u32 corner = 0; corner < tries; corner++) {
                    int x = near_x + data_ov004_02259688[corner].x;
                    int z = near_z + data_ov004_02259688[corner].y;
                    if (RoomPlacement_TryAt(out, x, z, side, number, (u8) layer, player_x, player_z) ==
                        ROOM_PLACEMENT_PLACED) {
                        if (shape == SHAPE_TWO_CELLS) {
                            try_turned(out, x, z, side, number, (u8) layer, position, player_x, player_z);
                        }
                        return ROOM_PLACEMENT_PLACED;
                    }
                }
            }
        }
    }
    return ROOM_PLACEMENT_NO_SPACE;
}
CLEAN_AS(func_ov004_0223b574, RoomPlacement_Find)

/* func_ov004_0223b7f8: whether furniture `number` fits at cell (x, z) facing `side` on `layer`
 * (ROOM_PLACEMENT_PLACED, the placement in `*out`, in the search's mode) or not
 * (ROOM_PLACEMENT_NO_SPACE). Each cell of its footprint must be on the map, empty
 * (ITEM_CODE_NONE), of a kind of ground that takes furniture (UnitTypeInfo_Byte04At) and,
 * unless FurnitureInfo_IndoorBit2 allows it, not the actor's cell (player_x, player_z). On top
 * only a one-cell piece that may stand there fits, on objects whose unk_788 is 1 and that are
 * not busy. */
int RoomPlacement_TryAt(u32 *out, int x, int z, int side, int number, u8 layer, int player_x, int player_z)
{
    int on_actor_cell = FurnitureInfo_IndoorBit2(number);
    int shape = FurnitureInfo_Shape(number);
    int stands = FurnitureInfo_DmaUnk1A(number);
    u16 code = ItemCode_MakeVariant(number, side);
    ItemFootprint footprint;
    ItemFootprint_Construct(&footprint, &code);
    AcreMap *map = data_021c80bc;
    int fits = 1;
    for (u32 i = 0; i < ItemFootprint_Count(&footprint); i++) {
        int cell_x = x + ItemFootprint_Cell(&footprint, i)->x;
        int cell_z = z + ItemFootprint_Cell(&footprint, i)->y;
        int acre_x = cell_x >> 4;
        int acre_z = cell_z >> 4;
        u16 *tile = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, cell_x - acre_x * 16, cell_z - acre_z * 16, layer);
        if (!on_actor_cell && cell_x == player_x && cell_z == player_z) {
            fits = 0;
            break;
        }
        if (tile == NULL || *tile != ITEM_CODE_NONE) {
            fits = 0;
            break;
        }
        if (!UnitTypeInfo_Byte04At(cell_x, cell_z)) {
            fits = 0;
            break;
        }
        if (layer == ROOM_OBJECTS_LAYER_ON_TOP) {
            if (shape != 0 || stands != CAN_STAND_ON_TOP) {
                fits = 0;
                break;
            }
            RoomObject *below = RoomObjects_GridObjectAt(RoomObjects_Grid(), cell_x, cell_z, ROOM_OBJECTS_LAYER_FLOOR);
            if (below == NULL || below->unk_788 != 1 || RoomObject_IsBusy(below)) {
                fits = 0;
                break;
            }
        }
    }
    if (fits) {
        *out = (u32) Placement_Make(x, z, number, side, layer, PLACEMENT_MODE_SEARCHED);
        ItemFootprint_Destruct(&footprint);
        return ROOM_PLACEMENT_PLACED;
    }
    ItemFootprint_Destruct(&footprint);
    return ROOM_PLACEMENT_NO_SPACE;
}
CLEAN_AS(func_ov004_0223b7f8, RoomPlacement_TryAt)
