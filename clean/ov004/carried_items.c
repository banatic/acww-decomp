/* The items a room object carries (carried_items.h). */
#include "carried_items.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/matrix.h" /* Mtx43_Translate */
#include "clean.h"
#include "main/item_code.h"
#include "room_object.h"
#include "cells.h"
#include "icon_models.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/room_sync.h"
#include "main/scene_query.h"
#include "room_object_body.h"
#include "room_object_map.h"

static_assert(offsetof(CarriedItem, item) == 2, "carried item code");
static_assert(sizeof(CarriedItem) == 0x10, "carried item");
static_assert(offsetof(CarriedItems, slots) == 4, "carried slots");
static_assert(sizeof(CarriedItems) == 0x44, "carried items");

#define SLOTS 4
#define BLOCK_CELLS 16 /* cells along a block of the town's map */
#define ONE 0x1000     /* 1 in 20.12 fixed point */

/* The town's map (AcreTile_ItemInAcre finds the item on a cell of it). */
extern void *data_021c80bc;

/* The scratch matrix RoomObject_BuildMatrix builds an object's matrix into. */
extern Mtx43 data_021fbe48;

extern int MTX_Inverse43(const Mtx43 *mtx, Mtx43 *inverse);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void func_ov004_0220d9a0(void *slot);
extern void *func_ov004_0220d9a4(char *slot);
extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *object);

/* The unused static of CarriedItems_PickUp: its guard, the object and its record of the C++
 * runtime's list of objects to destroy. */
extern u32 data_ov004_02256c84;
extern ItemCode data_ov004_02256c44;
extern u8 data_ov004_02256dd4[];

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The item on cell (x, y) of the town's map, layer 1. */
static ItemCode *item_on_cell(void *map, s32 x, s32 y)
{
    return AcreTile_ItemInAcre(map, shift_right(x, 4), shift_right(y, 4), x & (BLOCK_CELLS - 1), y & (BLOCK_CELLS - 1), 1);
}

/* Whether `item` is "nothing": an item with variants is compared without its variant. */
static int is_none(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        ItemCode none = ITEM_CODE_NONE;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

/* func_ov004_0220d4ec: each item onto the map at the cell under its position in the object's
 * matrix, in the current town (SceneQuery_Current); then no items. */
void CarriedItems_PutDown(CarriedItems *items, RoomObject *object)
{
    for (unsigned int i = 0; i < SLOTS; i++) {
        CarriedItem *slot = CarriedItems_Slot(items, i);
        if (CarriedItem_IsUsed(slot)) {
            Vec3 origin = {0, 0, 0};
            data_021fbe48 = object->matrix;
            Mtx43_Translate(&data_021fbe48, slot->position.x, slot->position.y, slot->position.z);
            Vec3 position;
            MTX_MultVec43(&origin, &data_021fbe48, &position);
            int x;
            int y;
            Position_Tile(&x, &y, (const Position *) (const void *) &position);
            int town = SceneQuery_Current();
            RoomSync_PutItem(town, x, y, CarriedItem_Item(slot), 1);
        }
    }
    CarriedItems_Clear(items);
}
CLEAN_AS(func_ov004_0220d4ec, CarriedItems_PutDown)

/* func_ov004_0220d594: when nothing but pile items lies loose on the object's cells, takes the
 * pile items with their positions on its top (in its space), and carries none if they do not
 * all fit. Whether they did.
 * QUIRK: when the cells hold other loose items, nothing changes and the result is still 1.
 * QUIRK: the first call builds a function-local static item code (0xfff1) that nothing reads,
 * and registers it for destruction (TrivialObject_DestructItemCode, which does nothing). */
int CarriedItems_PickUp(CarriedItems *items, RoomObject *object)
{
    if ((data_ov004_02256c84 & 1) == 0) {
        data_ov004_02256c44 = ITEM_CODE_NONE;
        __register_global_object(&data_ov004_02256c44, (void *) func_020051b0, data_ov004_02256dd4);
        data_ov004_02256c84 |= 1;
    }

    int all = 1;
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    void *map = data_021c80bc;
    if (CarriedItems_CellsAreClear(items, object)) {
        CarriedItems_Clear(items);
        RoomObject_BuildMatrix(object, NULL, 0);
        MTX_Inverse43(&data_021fbe48, &data_021fbe48);
        for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
            s32 x = CellList_At(&cells, (int) i)->x;
            s32 y = CellList_At(&cells, (int) i)->y;
            ItemCode *item = item_on_cell(map, x, y);
            if (item != NULL && ItemCode_IsKind1(item)) {
                Vec3 point;
                AcreTile_TileCentre(&point, (unsigned int) x, (unsigned int) y);
                point.y = object->top_height;
                Vec3 local;
                MTX_MultVec43(&point, &data_021fbe48, &local);
                /* the next items are still tried after one did not fit */
                all = (all & CarriedItems_Add(items, item, &local)) != 0;
            }
        }
        if (!all) {
            CarriedItems_Clear(items);
        }
    }
    CellList_Destruct(&cells);
    return all;
}
CLEAN_AS(func_ov004_0220d594, CarriedItems_PickUp)

/* func_ov004_0220d6b8: whether the object's cells hold no loose items other than pile items
 * (kind 1) and the ones ItemCode_IsF031OrVariant names. `items` is not read. */
int CarriedItems_CellsAreClear(CarriedItems *items, RoomObject *object)
{
    (void) items;
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    void *map = data_021c80bc;
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        s32 y = CellList_At(&cells, (int) i)->y;
        s32 x = CellList_At(&cells, (int) i)->x;
        ItemCode *item = item_on_cell(map, x, y);
        if (item != NULL && !ItemCode_IsF031OrVariant(item) && !ItemCode_IsKind1(item) && !is_none(item)) {
            CellList_Destruct(&cells);
            return 0;
        }
    }
    CellList_Destruct(&cells);
    return 1;
}
CLEAN_AS(func_ov004_0220d6b8, CarriedItems_CellsAreClear)

/* func_ov004_0220d788: the item into the first free slot; whether there was one. */
int CarriedItems_Add(CarriedItems *items, const ItemCode *item, const Vec3 *position)
{
    for (unsigned int i = 0; i < SLOTS; i++) {
        if (!CarriedItem_IsUsed(CarriedItems_Slot(items, i))) {
            CarriedItem_Set(CarriedItems_Slot(items, i), item, position);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0220d788, CarriedItems_Add)

/* func_ov004_0220d7cc */
void CarriedItems_Draw(CarriedItems *items, RoomObject *object)
{
    for (unsigned int i = 0; i < SLOTS; i++) {
        CarriedItem_Draw(CarriedItems_Slot(items, i), object);
    }
}
CLEAN_AS(func_ov004_0220d7cc, CarriedItems_Draw)

/* func_ov004_0220d7f0: the slot, or the first one when `index` is past the last. */
CarriedItem *CarriedItems_Slot(CarriedItems *items, unsigned int index)
{
    if (index < SLOTS) {
        return &items->slots[index];
    }
    return &items->slots[0];
}
CLEAN_AS(func_ov004_0220d7f0, CarriedItems_Slot)

/* func_ov004_0220d800 */
void CarriedItems_Clear(CarriedItems *items)
{
    for (unsigned int i = 0; i < SLOTS; i++) {
        CarriedItem_Clear(CarriedItems_Slot(items, i));
    }
}
CLEAN_AS(func_ov004_0220d800, CarriedItems_Clear)

/* func_ov004_0220d824: the slots destroyed by the C++ runtime. */
CarriedItems *CarriedItems_Destruct(CarriedItems *items)
{
    __cxa_vec_cleanup(items->slots, SLOTS, sizeof(CarriedItem), func_ov004_0220d9a0);
    return items;
}
CLEAN_AS(func_ov004_0220d824, CarriedItems_Destruct)

/* func_ov004_0220d840: the slots built by the C++ runtime, then cleared. */
CarriedItems *CarriedItems_Construct(CarriedItems *items)
{
    __cxa_vec_ctor(items->slots, SLOTS, sizeof(CarriedItem), (void (*)(void *)) func_ov004_0220d9a4, func_ov004_0220d9a0);
    CarriedItems_Clear(items);
    return items;
}
CLEAN_AS(func_ov004_0220d840, CarriedItems_Construct)

/* func_ov004_0220d870: the item's model at its place on the object (IconModels_DrawItemAt), at
 * scale 1. */
void CarriedItem_Draw(CarriedItem *slot, RoomObject *object)
{
    if (CarriedItem_IsUsed(slot)) {
        data_021fbe48 = object->matrix;
        Mtx43_Translate(&data_021fbe48, slot->position.x, slot->position.y, slot->position.z);
        Vec3 origin = {0, 0, 0};
        Vec3 position;
        MTX_MultVec43(&origin, &data_021fbe48, &position);
        Vec3 scale = {ONE, ONE, ONE};
        IconModels_DrawItemAt(*CarriedItem_Item(slot), &position, &scale, 0, 0, 0);
    }
}
CLEAN_AS(func_ov004_0220d870, CarriedItem_Draw)

/* func_ov004_0220d904: the item and its position into a free slot; whether it was free. */
int CarriedItem_Set(CarriedItem *slot, const ItemCode *item, const Vec3 *position)
{
    if (CarriedItem_IsUsed(slot)) {
        return 0;
    }
    slot->item = *item;
    slot->position = *position;
    return 1;
}
CLEAN_AS(func_ov004_0220d904, CarriedItem_Set)

/* func_ov004_0220d930 */
ItemCode *CarriedItem_Item(CarriedItem *slot)
{
    return &slot->item;
}
CLEAN_AS(func_ov004_0220d930, CarriedItem_Item)

/* func_ov004_0220d934 */
Vec3 *CarriedItem_Position(CarriedItem *slot)
{
    return &slot->position;
}
CLEAN_AS(func_ov004_0220d934, CarriedItem_Position)

/* func_ov004_0220d938: free. */
CarriedItem *CarriedItem_Clear(CarriedItem *slot)
{
    slot->item = ITEM_CODE_NONE;
    slot->position.x = 0;
    slot->position.y = 0;
    slot->position.z = 0;
    return slot;
}
CLEAN_AS(func_ov004_0220d938, CarriedItem_Clear)

/* func_ov004_0220d94c: whether the slot holds an item. */
int CarriedItem_IsUsed(const CarriedItem *slot)
{
    return !is_none(&slot->item);
}
CLEAN_AS(func_ov004_0220d94c, CarriedItem_IsUsed)

/* func_ov004_0220d9a0 */
void CarriedItem_Destruct(CarriedItem *slot)
{
    (void) slot;
}
CLEAN_AS(func_ov004_0220d9a0, CarriedItem_Destruct)

/* func_ov004_0220d9a4: free. */
CarriedItem *CarriedItem_Construct(CarriedItem *slot)
{
    slot->item = ITEM_CODE_NONE;
    CarriedItem_Clear(slot);
    return slot;
}
CLEAN_AS(func_ov004_0220d9a4, CarriedItem_Construct)
