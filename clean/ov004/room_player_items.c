/* The process that puts the players' items on the scene's map (room_player_items.h). */
#include "room_player_items.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/furniture_info.h"
#include "main/item_code.h"
#include "main/player_record.h"
#include "main/player_records.h"

static_assert(sizeof(Process) == 0x50, "the size RoomPlayerItems_New allocates");

/* The players whose items are placed, and the variant they are turned to. */
#define ROOM_PLAYER_ITEMS_PLAYERS 4
#define ROOM_PLAYER_ITEMS_VARIANT 3
/* Items of this shape (FurnitureInfo_ItemShape) are two tiles wide, and the half of the room
 * (x below this) where they move one tile left. */
#define ROOM_PLAYER_ITEMS_WIDE_SHAPE 2
#define ROOM_PLAYER_ITEMS_LEFT_HALF 8
/* The map's layer the items go on (AcreTile_SetItem). */
#define ROOM_PLAYER_ITEMS_LAYER 0

typedef struct RoomPlayerItemsTile {
    int x;
    int z;
} RoomPlayerItemsTile;

/* The tile of each player's item: a function-local static the compiler fills the first time,
 * recording that in bit 0 of the guard word before it. */
extern u32 data_ov004_022589c8;
extern RoomPlayerItemsTile data_ov004_022589cc[ROOM_PLAYER_ITEMS_PLAYERS];

extern AcreMap *data_021c80bc; /* the map of the scene shown, or NULL */

/* The class's vtable and the Process base's. */
extern const u32 data_ov004_02255a38[];
extern const u32 data_020da13c[];

static void RoomPlayerItems_init_tiles(void)
{
    static const RoomPlayerItemsTile tiles[ROOM_PLAYER_ITEMS_PLAYERS] = {{6, 9}, {9, 9}, {6, 12}, {9, 12}};
    if ((data_ov004_022589c8 & 1) == 0) {
        for (int i = 0; i < ROOM_PLAYER_ITEMS_PLAYERS; i++) {
            data_ov004_022589cc[i] = tiles[i];
        }
        data_ov004_022589c8 |= 1;
    }
}

/* Whether `item` is empty: for a code with a variant, whether its item is that of 0xfff1. */
static int RoomPlayerItems_is_empty(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        ItemCode none = ITEM_CODE_NONE;
        int item_number = ItemCode_VariantItem(item);
        return item_number == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

/* func_ov004_022319ac: with a map shown, each of players 0 to 3 that has a record and a
 * non-empty item 0x240e has it put on the map, turned to variant 3, at the player's tile (one
 * tile left for a wide item on the left half). */
void RoomPlayerItems_Place(void)
{
    RoomPlayerItems_init_tiles();
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return;
    }
    for (int player = 0; player < ROOM_PLAYER_ITEMS_PLAYERS; player++) {
        u8 *record = PlayerRecords_Get(player);
        if (record == NULL) {
            continue;
        }
        int x = data_ov004_022589cc[player].x;
        int z = data_ov004_022589cc[player].z;
        ItemCode item = *PlayerRecord_Item240E(record);
        if (RoomPlayerItems_is_empty(&item)) {
            continue;
        }
        ItemCode_SetVariant(&item, ROOM_PLAYER_ITEMS_VARIANT);
        if (x < ROOM_PLAYER_ITEMS_LEFT_HALF && FurnitureInfo_ItemShape(&item) == ROOM_PLAYER_ITEMS_WIDE_SHAPE) {
            x--;
        }
        AcreTile_SetItem(map, &item, x, z, ROOM_PLAYER_ITEMS_LAYER);
    }
}
CLEAN_AS(func_ov004_022319ac, RoomPlayerItems_Place)

/* func_ov004_02231aa8 (vtable slot 0, the creation): the items placed; done. */
int RoomPlayerItems_Create(void)
{
    RoomPlayerItems_Place();
    return 1;
}
CLEAN_AS(func_ov004_02231aa8, RoomPlayerItems_Create)

/* func_ov004_02231ab8 (the deleting destructor, vtable slot 0x44) */
Process *RoomPlayerItems_Delete(Process *self)
{
    self->vtable = data_ov004_02255a38;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02231ab8, RoomPlayerItems_Delete)

/* func_ov004_02231ae0 (the destructor, vtable slot 0x40) */
Process *RoomPlayerItems_Destruct(Process *self)
{
    self->vtable = data_ov004_02255a38;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_ov004_02231ae0, RoomPlayerItems_Destruct)

/* func_ov004_02231b00 (the constructor): the base's vtable set before the class's. */
Process *RoomPlayerItems_Construct(Process *self)
{
    Process_Construct(self);
    self->vtable = data_020da13c;
    self->vtable = data_ov004_02255a38;
    return self;
}
CLEAN_AS(func_ov004_02231b00, RoomPlayerItems_Construct)

/* func_ov004_02231b20 (the profile's maker): a new one from the room's heap; nothing when it
 * has no room. */
void RoomPlayerItems_New(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));
    if (self != NULL) {
        RoomPlayerItems_Construct(self);
    }
}
CLEAN_AS(func_ov004_02231b20, RoomPlayerItems_New)
