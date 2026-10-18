/* The four items of a villager (villager_items.h). */
#include "villager_items.h"

#include "clean.h"
#include "session_villager.h"
#include "item_code.h"
#include "item_traits.h"
#include "main_random.h"

#define VILLAGER_ITEMS_OFFSET 0x7b0

static u16 *items_of(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_ITEMS_OFFSET);
}

/* func_0207ddd0: the villager's item worth the most (func_0204c878; of equal ones the last), in
 * `out`; 0xfff1 when it has none, or only items worth less than 0. */
void VillagerItems_MostValuable(u16 *out, u8 *villager)
{
    *out = VILLAGER_ITEMS_NONE;
    u16 *items = VillagerItems_At(villager, 0);
    int best = 0;
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        if (items[i] == VILLAGER_ITEMS_NONE) {
            continue;
        }
        int worth = ItemTraits_Price(&items[i]);
        if (worth >= best) {
            *out = items[i];
            best = worth;
        }
    }
}
CLEAN_AS(func_0207ddd0, VillagerItems_MostValuable)

/* func_0207de14: one of the villager's items at random, in `out`; 0xfff1 when it has none. */
void VillagerItems_Random(u16 *out, u8 *villager)
{
    *out = VILLAGER_ITEMS_NONE;
    u16 *items = VillagerItems_At(villager, 0);
    int count = 0;
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        if (items[i] != VILLAGER_ITEMS_NONE) {
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    int pick = (int) MainRandom_Below(count);
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        if (items[i] == VILLAGER_ITEMS_NONE) {
            continue;
        }
        if (pick == 0) {
            *out = items[i];
            return;
        }
        pick--;
    }
}
CLEAN_AS(func_0207de14, VillagerItems_Random)

/* func_0207de70: the item taken from the villager's items, which are packed again and sent.
 * Gives 1, or 0 when the villager does not have it. */
int VillagerItems_Remove(u8 *villager, u16 *item)
{
    int index = VillagerItems_Find(villager, item);
    if (index == VILLAGER_ITEMS_NOT_FOUND) {
        return 0;
    }
    items_of(villager)[index] = VILLAGER_ITEMS_NONE;
    VillagerItems_Pack(villager);
    SessionVillager_SendItems(villager, VillagerItems_At(villager, 0));
    return 1;
}
CLEAN_AS(func_0207de70, VillagerItems_Remove)

/* func_0207deb4: the place of the item among the villager's items, or -1. */
int VillagerItems_Find(u8 *villager, u16 *item)
{
    u16 *items = VillagerItems_At(villager, 0);
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        int same;
        if (ItemCode_HasVariant(item) != 0) {
            int wanted = ItemCode_VariantItem(item);
            same = wanted == ItemCode_VariantItem(&items[i]);
        } else {
            same = *item == items[i];
        }
        if (same) {
            return i;
        }
    }
    return VILLAGER_ITEMS_NOT_FOUND;
}
CLEAN_AS(func_0207deb4, VillagerItems_Find)

/* func_0207df18: the item added to the villager's items (packed first) in the first empty
 * place; with none empty the first is pushed out and the item goes last. Then they are sent. */
void VillagerItems_Add(u8 *villager, u16 *item)
{
    u16 *items = items_of(villager);
    VillagerItems_Pack(villager);
    u16 none = VILLAGER_ITEMS_NONE;
    int index = VillagerItems_Find(villager, &none);
    if (index != VILLAGER_ITEMS_NOT_FOUND) {
        items[index] = *item;
    } else {
        for (int i = 0; i < VILLAGER_ITEMS_COUNT - 1; i++) {
            items[i] = items[i + 1];
        }
        items[VILLAGER_ITEMS_COUNT - 1] = *item;
    }
    SessionVillager_SendItems(villager, VillagerItems_At(villager, 0));
}
CLEAN_AS(func_0207df18, VillagerItems_Add)

/* func_0207df88: the villager's items moved to the front, keeping their order. */
void VillagerItems_Pack(u8 *villager)
{
    u16 *items = items_of(villager);
    for (int i = 0; i < VILLAGER_ITEMS_COUNT - 1; i++) {
        if (items[i] != VILLAGER_ITEMS_NONE) {
            continue;
        }
        int next = i + 1;
        while (next < VILLAGER_ITEMS_COUNT && items[next] == VILLAGER_ITEMS_NONE) {
            next++;
        }
        if (next == VILLAGER_ITEMS_COUNT) {
            return;
        }
        items[i] = items[next];
        items[next] = VILLAGER_ITEMS_NONE;
    }
}
CLEAN_AS(func_0207df88, VillagerItems_Pack)

/* func_0207dfd4: the villager's item at `index`, or NULL from 4. */
u16 *VillagerItems_At(u8 *villager, unsigned int index)
{
    if (index < VILLAGER_ITEMS_COUNT) {
        return &items_of(villager)[index];
    }
    return NULL;
}
CLEAN_AS(func_0207dfd4, VillagerItems_At)

/* func_0207dfec: all four places emptied. */
void VillagerItems_Clear(u8 *villager)
{
    u16 *items = items_of(villager);
    for (int i = 0; i < VILLAGER_ITEMS_COUNT; i++) {
        items[i] = VILLAGER_ITEMS_NONE;
    }
}
CLEAN_AS(func_0207dfec, VillagerItems_Clear)
