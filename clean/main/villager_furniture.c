/* The house of one of the town's villagers (villager_furniture.h). */
#include "villager_furniture.h"

#include "clean.h"
#include "npc_id.h"
#include "session.h"
#include "villager_entry.h"
#include "villager_items.h"
#include "villager_status.h"
#include "item_code.h"
#include "main_random.h"
#include "room_cells.h"
#include "town_villager.h"
#include "villager_house_items.h"
#include "villager_object.h"

#define VILLAGER_FURNITURE_OFFSET 0x78c
#define VILLAGER_FURNITURE_WALLPAPER 0x7d4
#define VILLAGER_FURNITURE_CARPET 0x7d5
#define VILLAGER_FURNITURE_DRAW 0x7d8
/* VillagerFurniture_ResetForMode: the bound of the draw for mode 2, and for the others. */
#define VILLAGER_FURNITURE_DRAW_MODE_2 10
#define VILLAGER_FURNITURE_DRAW_OTHER 40

extern NetSession *data_020ccf94; /* the session */

static u16 *VillagerFurniture_Items(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_FURNITURE_OFFSET);
}

static int VillagerFurniture_IsSlotCode(u16 code)
{
    return code >= VILLAGER_FURNITURE_SLOT_FIRST && code <= VILLAGER_FURNITURE_SLOT_LAST;
}

/* func_0207f2e8 */
void VillagerFurniture_SetCarpet(u8 *villager, u8 index)
{
    villager[VILLAGER_FURNITURE_CARPET] = index;
}
CLEAN_AS(func_0207f2e8, VillagerFurniture_SetCarpet)

/* func_0207f2f4 */
void VillagerFurniture_SetWallpaper(u8 *villager, u8 index)
{
    villager[VILLAGER_FURNITURE_WALLPAPER] = index;
}
CLEAN_AS(func_0207f2f4, VillagerFurniture_SetWallpaper)

/* func_0207f300 */
u8 VillagerFurniture_Carpet(u8 *villager)
{
    return villager[VILLAGER_FURNITURE_CARPET];
}
CLEAN_AS(func_0207f300, VillagerFurniture_Carpet)

/* func_0207f30c */
u8 VillagerFurniture_Wallpaper(u8 *villager)
{
    return villager[VILLAGER_FURNITURE_WALLPAPER];
}
CLEAN_AS(func_0207f30c, VillagerFurniture_Wallpaper)

/* func_0207f318: whether the item the spot at `tile` stands for is there and marked. */
int VillagerFurniture_IsMarkedAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots,
                                 int count)
{
    int slot = VillagerFurniture_SlotAt(villager, tile, spots, count);
    return VillagerHouseItems_IsSlot(villager, (u32) slot) &&
           VillagerFurniture_Items(villager)[slot] != VILLAGER_FURNITURE_NONE && VillagerEntry_IsItemMarked(villager, slot);
}
CLEAN_AS(func_0207f318, VillagerFurniture_IsMarkedAt)

/* func_0207f360: the item the spot at `tile` stands for taken out of the house (emptied and
 * unmarked); 0 when there is no such spot. */
int VillagerFurniture_TakeAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots, int count)
{
    int slot = VillagerFurniture_SlotAt(villager, tile, spots, count);
    if (!VillagerHouseItems_IsSlot(villager, (u32) slot)) {
        return 0;
    }
    VillagerFurniture_Items(villager)[slot] = VILLAGER_FURNITURE_NONE;
    VillagerEntry_UnmarkItem(villager, slot);
    return 1;
}
CLEAN_AS(func_0207f360, VillagerFurniture_TakeAt)

/* func_0207f3a0: which of the villager's items the first of the `count` spots on `tile` that
 * holds a code 0xf000-0xf02f stands for; -1 when there is none, for no spots or a tile outside
 * the acre. */
int VillagerFurniture_SlotAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots, int count)
{
    if (spots == NULL || (u32) tile->x >= VILLAGER_FURNITURE_ACRE_TILES || (u32) tile->z >= VILLAGER_FURNITURE_ACRE_TILES) {
        return VILLAGER_FURNITURE_NOT_FOUND;
    }
    for (int i = 0; i < count; i++) {
        if (tile->x != spots[i].x || tile->z != spots[i].z) {
            continue;
        }
        u16 code = spots[i].code;
        if (VillagerFurniture_IsSlotCode(code)) {
            return VillagerHouseItems_SlotOfCode(villager, &code);
        }
    }
    return VILLAGER_FURNITURE_NOT_FOUND;
}
CLEAN_AS(func_0207f3a0, VillagerFurniture_SlotAt)

/* func_0207f414: for a new mode, byte 0x7d8 drawn again (below 10 for mode 2, else below 40)
 * and the house's items 1 and 2 emptied, for mode 2 or when `from_2` is set. */
void VillagerFurniture_ResetForMode(u8 *villager, int mode, int from_2)
{
    if (mode == 2) {
        villager[VILLAGER_FURNITURE_DRAW] = (u8) MainRandom_Below(VILLAGER_FURNITURE_DRAW_MODE_2);
        VillagerHouseItems_ClearSlots1And2(villager);
    } else {
        villager[VILLAGER_FURNITURE_DRAW] = (u8) MainRandom_Below(VILLAGER_FURNITURE_DRAW_OTHER);
        if (from_2 != 0) {
            VillagerHouseItems_ClearSlots1And2(villager);
        }
    }
}
CLEAN_AS(func_0207f414, VillagerFurniture_ResetForMode)

/* func_0207f454: the villager's four items (villager_items.h) put away into its house, and the
 * four emptied; when one of them went into the ten, func_02052fdc with the villager's place in
 * the town. Then func_0209b998 on the object of its mode record. Nothing while this system
 * holds a session slot, or for a villager whose NpcId is not valid.
 * QUIRK: the place is passed on as a byte (-1 becomes 255). */
void VillagerFurniture_StoreItems(u8 *villager)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return;
    }
    u16 *items = VillagerItems_At(villager, 0);
    int stored = 0;
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        if (VillagerHouseItems_Store(villager, &items[i])) {
            stored = 1;
        }
    }
    VillagerItems_Clear(villager);
    if (stored) {
        RoomCells_ResetByIndex((unsigned char) VillagerStatus_Index(villager));
    }
    VillagerObject_SetLow5From1To2(VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
}
CLEAN_AS(func_0207f454, VillagerFurniture_StoreItems)

/* func_0207f4c8: the 256 codes of an item template filled for the villager: each code
 * 0xf000-0xf02f becomes the item it stands for with the code's variant, or 0xfff1 when that is
 * not an item of kind 3 or 4. For a villager not staying as a resident (VillagerStatus_Stay),
 * a marked item of kind 3 or 4 is replaced by the one func_0207f590 gives, and an unmarked
 * one dropped. */
void VillagerFurniture_FillTemplate(u8 *villager, u16 *codes)
{
    int moving = VillagerStatus_Stay(villager) != VILLAGER_STAY_RESIDENT;
    for (int i = 0; i < VILLAGER_FURNITURE_TEMPLATE_CODES; i++) {
        u16 *code = &codes[i];
        if (!VillagerFurniture_IsSlotCode(*code)) {
            continue;
        }
        int slot = VillagerHouseItems_SlotOfCode(villager, code);
        u16 fetched;
        VillagerHouseItems_Get(&fetched, villager, slot);
        u16 item = fetched;
        if (moving && ItemCode_HasVariant(&item)) {
            if (VillagerEntry_IsItemMarked(villager, slot)) {
                u16 replacement;
                VillagerHouseItems_ReplacementFor(&replacement, villager, &item);
                item = replacement;
            } else {
                item = VILLAGER_FURNITURE_NONE;
            }
        }
        if (ItemCode_HasVariant(&item)) {
            ItemCode_SetVariant(&item, *code & VILLAGER_FURNITURE_VARIANT_MASK);
            *code = item;
        } else {
            *code = VILLAGER_FURNITURE_NONE;
        }
    }
}
CLEAN_AS(func_0207f4c8, VillagerFurniture_FillTemplate)
