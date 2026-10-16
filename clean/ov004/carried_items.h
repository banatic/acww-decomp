/* The items a room object carries while it moves or turns (its member at 0x18c): when a move
 * or turn starts, the pile items (kind 1) lying on the cells it covers are taken off the town's
 * map with their position in the object's space; while it moves they are drawn with it; when it
 * stops they are put back on the map on the cells under their new positions. Up to four. */
#ifndef CLEAN_OV004_CARRIED_ITEMS_H
#define CLEAN_OV004_CARRIED_ITEMS_H

#include "types.h"

#include "autoload_2/approach.h" /* Vec3 */
#include "main/lookups.h"        /* ItemCode */

struct RoomObject;

/* An item and its position in the carrying object's space; 0xfff1 when the slot is free. */
typedef struct CarriedItem {
    u8 unk_00[2];
    ItemCode item;
    Vec3 position;
} CarriedItem;

typedef struct CarriedItems {
    u8 unk_00[4];
    CarriedItem slots[4];
} CarriedItems;

void CarriedItems_PutDown(CarriedItems *items, struct RoomObject *object);
int CarriedItems_PickUp(CarriedItems *items, struct RoomObject *object);
int CarriedItems_CellsAreClear(CarriedItems *items, struct RoomObject *object);
int CarriedItems_Add(CarriedItems *items, const ItemCode *item, const Vec3 *position);
void CarriedItems_Draw(CarriedItems *items, struct RoomObject *object);
CarriedItem *CarriedItems_Slot(CarriedItems *items, unsigned int index);
void CarriedItems_Clear(CarriedItems *items);
CarriedItems *CarriedItems_Destruct(CarriedItems *items);
CarriedItems *CarriedItems_Construct(CarriedItems *items);
void CarriedItem_Draw(CarriedItem *slot, struct RoomObject *object);
int CarriedItem_Set(CarriedItem *slot, const ItemCode *item, const Vec3 *position);
ItemCode *CarriedItem_Item(CarriedItem *slot);
Vec3 *CarriedItem_Position(CarriedItem *slot);
CarriedItem *CarriedItem_Clear(CarriedItem *slot);
int CarriedItem_IsUsed(const CarriedItem *slot);
void CarriedItem_Destruct(CarriedItem *slot);
CarriedItem *CarriedItem_Construct(CarriedItem *slot);

#endif
