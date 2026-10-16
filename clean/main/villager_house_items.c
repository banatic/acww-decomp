/* What one of the town's villagers keeps in its house (villager_house_items.h). */
#include "villager_house_items.h"

#include "clean.h"
#include "museum_record.h"
#include "npc_id.h"
#include "villager_furniture.h"
#include "villager_mode.h"
#include "villager_roster.h"

#define VILLAGER_HOUSE_ITEMS_OFFSET 0x78c
#define VILLAGER_HOUSE_DRAW 0x7d8
/* VillagerHouseItems_GiveAwayOne: only for a villager with at least this many items. */
#define VILLAGER_HOUSE_CROWDED 7
/* The modes that have a filter (func_0209c2d4 gives a mode's place within its group). */
#define VILLAGER_HOUSE_FILTERS 5
/* The wallpapers and carpets, kept by index (villager_furniture.h). */
#define VILLAGER_HOUSE_WALLPAPER_FIRST 0x1100
#define VILLAGER_HOUSE_WALLPAPER_LAST 0x1143
#define VILLAGER_HOUSE_CARPET_FIRST 0x1144
#define VILLAGER_HOUSE_CARPET_LAST 0x1187
/* The items mode 3 keeps. */
#define VILLAGER_HOUSE_MODE_3_FIRST 0x11a8
#define VILLAGER_HOUSE_MODE_3_LAST 0x12a7
/* The kinds of group A items (func_020535f0) are below this. */
#define VILLAGER_HOUSE_GROUP_A_KINDS 24
/* VillagerHouseItems_StoreGroupA: an object of this type (byte 0x0a) names a group A kind. */
#define VILLAGER_HOUSE_OBJECT_TYPE_2 2
/* VillagerHouseItems_PickCheapest starts from a worth above any item's. */
#define VILLAGER_HOUSE_WORTH_MAX 99999
/* The template sets of a villager's room (acre_map.h), and the draws of its variant. */
#define VILLAGER_HOUSE_TEMPLATE_MODE_2 3
#define VILLAGER_HOUSE_TEMPLATE_OTHER 2
#define VILLAGER_HOUSE_TEMPLATE_VARIANTS_MODE_2 10
/* The template codes that stand for one of the ten items (villager_furniture.h). */
#define VILLAGER_HOUSE_SLOT_CODE_FIRST 0xf000
#define VILLAGER_HOUSE_SLOT_CODE_LAST 0xf02f
/* The room models past 0x1010 a villager's data names (bits 2-4 of its byte 0x28). */
#define VILLAGER_HOUSE_ROOMS 5

/* The item that stands in for an item of kind 3 or 4 of each size class: 0x4a48, 0x4a4c, 0x4a50. */
extern const u16 data_020cd42c[VILLAGER_HOUSE_CLASSES];
extern const int data_020e18c0[VILLAGER_HOUSE_CLASSES]; /* -1, -1, -1 */
/* The filter of each mode 0-4: the methods func_0207fd94, func_0207fd6c, func_0207fd44,
 * func_0207fd1c and func_0207fcc8, filled in by the static constructor __sinit_020c5d3c. */
extern const MemberPointer data_021d1330[VILLAGER_HOUSE_FILTERS];
extern const MemberPointer __ptmf_null;

extern NpcId *func_0208150c(const void *villager);                    /* the villager's NpcId, at 0x7a0 */
extern VillagerModeRecord *func_0207f1c8(const void *villager);       /* its mode record, at 0x734 */
extern VillagerModeRecord *func_0209b5ec(VillagerModeRecord *record); /* the record itself */
extern int func_0209c330(const VillagerModeRecord *record);           /* its mode */
extern int func_0209c2c0(const VillagerModeRecord *record);           /* bit 0 of its flags (VILLAGER_MODE_FROM_2) */
extern u8 *func_0209b5e8(VillagerModeRecord *record);                 /* its object, at 0x24 */
extern u8 *func_0209b91c(u8 *object);                                 /* the object itself */
extern int func_0209bd44(const u8 *object);                           /* whether it holds something */
extern int func_0209bc40(const u8 *object);                           /* its type, byte 0x0a */
extern u8 func_0209b914(const u8 *object);                            /* its byte 0x2a */
extern u8 func_0209b8bc(const u8 *object);                            /* its byte 0x2f */
/* A mode's group (func_0209c310) in `group` and its place within the group. */
extern int func_0209c2d4(u8 *group, u32 mode);
extern int func_020644cc(int bound);                              /* a random number below `bound` */
extern int func_0204bcdc(const u16 *item);                        /* whether the item is of kind 3 or 4 */
extern int func_0204bc64(const u16 *item);                        /* its index among the items of kind 3 or 4 */
extern int func_02053bc0(const u16 *item);                        /* its size class (0 for other kinds) */
extern u32 func_020535f0(const u16 *item);                        /* the kind of a group A item; 0 for others */
extern int func_0204c878(const u16 *item);                        /* what the item is worth */
extern int func_0203a6ec(u16 item);                               /* the item put in the town's list of 15; 0 when full */
extern void func_02061b1c(u16 *out, const u16 *code, int always); /* the item a code stands for */
extern int func_02080834(u8 *villager, u16 *item);                /* how much the villager likes the item */
extern const u8 *func_02080b64(const u8 *villager);               /* its villager data + 0x28, or NULL */
extern const u8 *func_02082500(int number);                       /* a villager's data, NULL past 149 */

static int is_group_a(u16 code)
{
    return code >= MUSEUM_A_FIRST && code <= MUSEUM_A_LAST;
}

/* The group A item code's index among the 52 (its variant left out). */
static int group_a_index(u16 code)
{
    return (code - MUSEUM_A_FIRST) >> 2;
}

/* The mode and its bit FROM_2, from the villager's mode record. */
static VillagerModeRecord *mode_record(const u8 *villager)
{
    return func_0209b5ec(func_0207f1c8(villager));
}

/* func_0207f590: the item of kind 3 or 4 that stands in for `item` (one of three, by its size
 * class) in `out`; 0xfff1 when `item` is not of kind 3 or 4. */
void VillagerHouseItems_ReplacementFor(u16 *out, const u8 *villager, const u16 *item)
{
    (void) villager;
    *out = VILLAGER_HOUSE_ITEM_NONE;
    if (func_0204bcdc(item)) {
        int size_class = func_02053bc0(item);
        if (size_class < VILLAGER_HOUSE_CLASSES) {
            *out = data_020cd42c[size_class];
        }
    }
}
CLEAN_AS(func_0207f590, VillagerHouseItems_ReplacementFor)

/* func_0207f5c8: the house's items 1 and 2 emptied. */
void VillagerHouseItems_ClearSlots1And2(u8 *villager)
{
    u16 *items = VillagerHouseItems_Items(villager);
    items[1] = VILLAGER_HOUSE_ITEM_NONE;
    items[2] = VILLAGER_HOUSE_ITEM_NONE;
}
CLEAN_AS(func_0207f5c8, VillagerHouseItems_ClearSlots1And2)

/* func_0207f5e4: once a day, a villager with seven items or more gives one of them away half
 * of the time: for each size class, a random place of its range holding an item that does not
 * fit the villager's mode; one of those places at random is emptied, its item going to the
 * town's list of 15. */
void VillagerHouseItems_GiveAwayOne(u8 *villager)
{
    if (!NpcId_IsValid(func_0208150c(villager))) {
        return;
    }
    if (VillagerHouseItems_Count(villager) < VILLAGER_HOUSE_CROWDED) {
        return;
    }
    if (func_020644cc(2) != 0) {
        return;
    }
    VillagerModeRecord *record = mode_record(villager);
    int mode = func_0209c330(record);
    int from_2 = func_0209c2c0(record);

    int picks[VILLAGER_HOUSE_CLASSES];
    for (int i = 0; i < VILLAGER_HOUSE_CLASSES; i++) {
        picks[i] = data_020e18c0[i];
    }
    int count = 0;
    int first = 0;
    int end = 0;
    for (int i = 0; i < VILLAGER_HOUSE_CLASSES; i++) {
        if (VillagerHouseItems_SlotRange(villager, &first, &end, i, mode, (u8) from_2)) {
            picks[i] = VillagerHouseItems_PickUnfitting(villager, mode, first, end);
            if (VillagerHouseItems_IsSlot(villager, (u32) picks[i])) {
                count++;
            }
        }
    }
    if (count <= 0) {
        return;
    }
    int chosen = func_020644cc(count);
    if (chosen >= VILLAGER_HOUSE_CLASSES) {
        return;
    }
    u16 *items = VillagerHouseItems_Items(villager);
    for (int i = 0; i < VILLAGER_HOUSE_CLASSES; i++) {
        int slot = picks[i];
        if (!VillagerHouseItems_IsSlot(villager, (u32) slot)) {
            continue;
        }
        if (chosen == 0) {
            if (items[slot] != VILLAGER_HOUSE_ITEM_NONE) {
                VillagerHouseItems_GiveUp(&items[slot]);
            }
            items[slot] = VILLAGER_HOUSE_ITEM_NONE;
            return;
        }
        chosen--;
    }
}
CLEAN_AS(func_0207f5e4, VillagerHouseItems_GiveAwayOne)

/* func_0207f6dc: how many of the ten places hold an item. */
int VillagerHouseItems_Count(const u8 *villager)
{
    const u16 *items = (const u16 *) (const void *) (villager + VILLAGER_HOUSE_ITEMS_OFFSET);
    int count = 0;
    for (int i = 0; i < VILLAGER_HOUSE_ITEMS; i++) {
        if (items[i] != VILLAGER_HOUSE_ITEM_NONE) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0207f6dc, VillagerHouseItems_Count)

/* func_0207f708: how many of the ten places hold `item`: for a place holding an item of kind 3
 * or 4, the same item of any variant (func_0204bc64), else the same code. */
int VillagerHouseItems_CountSame(const u8 *villager, const u16 *item)
{
    const u16 *items = (const u16 *) (const void *) (villager + VILLAGER_HOUSE_ITEMS_OFFSET);
    int count = 0;
    for (int i = 0; i < VILLAGER_HOUSE_ITEMS; i++) {
        int same;
        if (func_0204bcdc(&items[i])) {
            int index = func_0204bc64(&items[i]);
            same = index == func_0204bc64(item);
        } else {
            same = items[i] == *item;
        }
        if (same) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0207f708, VillagerHouseItems_CountSame)

/* func_0207f76c: `item` put away into the villager's house. An item of kind 3 or 4 (by the item
 * its code stands for) takes a place of its size class (VillagerHouseItems_MakeRoom; a group A
 * item of class 2 VillagerHouseItems_StoreGroupA) or, with no place for it, may go to the
 * town's list; a wallpaper or a carpet becomes the house's. Non-zero when the item went into
 * one of the ten places. */
int VillagerHouseItems_Store(u8 *villager, u16 *item)
{
    if (*item == VILLAGER_HOUSE_ITEM_NONE) {
        return 0;
    }
    u16 stands_for;
    func_02061b1c(&stands_for, item, 1);
    VillagerModeRecord *record = mode_record(villager);
    int mode = func_0209c330(record);
    int from_2 = func_0209c2c0(record);

    if (func_0204bcdc(&stands_for)) {
        int fits = VillagerHouseItems_FitsMode(villager, item, (u32) mode);
        int size_class = func_02053bc0(&stands_for);
        if (is_group_a(*item) && size_class == 2) {
            return VillagerHouseItems_StoreGroupA(villager, item, size_class, mode, (u8) from_2, (u8) fits);
        }
        int slot = VillagerHouseItems_MakeRoom(villager, size_class, mode, from_2, (u8) fits);
        if (VillagerHouseItems_IsSlot(villager, (u32) slot)) {
            VillagerHouseItems_Items(villager)[slot] = *item;
            return 1;
        }
        VillagerHouseItems_MaybeGiveUp(item);
        return 0;
    }

    u16 code = *item;
    if (code >= VILLAGER_HOUSE_WALLPAPER_FIRST && code <= VILLAGER_HOUSE_WALLPAPER_LAST) {
        VillagerFurniture_SetWallpaper(villager, (u8) (code - VILLAGER_HOUSE_WALLPAPER_FIRST));
    } else if (code >= VILLAGER_HOUSE_CARPET_FIRST && code <= VILLAGER_HOUSE_CARPET_LAST) {
        VillagerFurniture_SetCarpet(villager, (u8) (code - VILLAGER_HOUSE_CARPET_FIRST));
    }
    return 0;
}
CLEAN_AS(func_0207f76c, VillagerHouseItems_Store)

/* func_0207f8a0: a group A item of size class 2 put into the place its kind gives within the
 * class's range (its place among the items of its kind, VillagerHouseItems_GroupAPlace, wrapped
 * around the range). An empty place just takes it. Else the item there gives way (half of the
 * time to the town's list) and the new one takes its place, except when the new item does not
 * fit the mode while the old one does, or, in mode 2, when the villager's object (of type 2,
 * byte 0x2a at least 2) names a group A kind (byte 0x2f) that the old item has and the new one
 * has not: then the new item gives way instead. Non-zero when it was put in.
 * QUIRK: what both items are worth (func_0204c878) is asked for and not used. */
int VillagerHouseItems_StoreGroupA(u8 *villager, u16 *item, int size_class, int mode, u8 from_2, u8 fits)
{
    if (!is_group_a(*item) || size_class != 2) {
        return 0;
    }
    int first = 0;
    int end = 0;
    if (!VillagerHouseItems_SlotRange(villager, &first, &end, size_class, mode, from_2)) {
        return 0;
    }
    int width = end - first;
    int place = VillagerHouseItems_GroupAPlace(villager, item);
    int slot = 0;
    if (place >= 0) {
        slot = first + place % width;
    }
    if (!VillagerHouseItems_IsSlot(villager, (u32) slot)) {
        return 0;
    }
    u16 *there = &VillagerHouseItems_Items(villager)[slot];
    if (*there == VILLAGER_HOUSE_ITEM_NONE) {
        *there = *item;
        return 1;
    }
    int old_fits = VillagerHouseItems_FitsMode(villager, there, (u32) mode);
    if (fits) {
        u8 *object = func_0209b5e8(func_0207f1c8(villager));
        u8 *same = func_0209b91c(object);
        func_0204c878(item);
        func_0204c878(there);
        if (mode == 2) {
            u32 wanted = VILLAGER_HOUSE_GROUP_A_KINDS;
            if (func_0209bd44(same) && func_0209bc40(same) == VILLAGER_HOUSE_OBJECT_TYPE_2 && func_0209b914(object) >= 2 &&
                func_0209b8bc(object) < VILLAGER_HOUSE_GROUP_A_KINDS) {
                wanted = func_0209b8bc(object);
            }
            if (wanted < VILLAGER_HOUSE_GROUP_A_KINDS && wanted != func_020535f0(item) && old_fits &&
                wanted == func_020535f0(there)) {
                VillagerHouseItems_MaybeGiveUp(item);
                return 0;
            }
        }
    } else if (old_fits) {
        VillagerHouseItems_MaybeGiveUp(item);
        return 0;
    }
    VillagerHouseItems_MaybeGiveUp(there);
    *there = *item;
    return 1;
}
CLEAN_AS(func_0207f8a0, VillagerHouseItems_StoreGroupA)

/* func_0207fa3c: for a group A item of a kind below 24, its index less that of the first group
 * A item of the same kind; -1 for any other item. */
int VillagerHouseItems_GroupAPlace(const u8 *villager, const u16 *item)
{
    (void) villager;
    if (!is_group_a(*item)) {
        return -1;
    }
    u32 kind = func_020535f0(item);
    if (kind >= VILLAGER_HOUSE_GROUP_A_KINDS) {
        return -1;
    }
    for (int i = 0; i < MUSEUM_A_ITEMS; i++) {
        u16 other = (u16) (MUSEUM_A_FIRST + i * 4);
        if (func_020535f0(&other) == kind) {
            return group_a_index(*item) - i;
        }
    }
    return -1;
}
CLEAN_AS(func_0207fa3c, VillagerHouseItems_GroupAPlace)

/* func_0207fad0: a place of the size class's range made ready for a new item: a random empty
 * one; else a random one whose item does not fit the mode, or when the new item fits, the one
 * with the cheapest item; that item gives way (half of the time to the town's list). The place
 * is left empty; -1 when there is none (or no range). */
int VillagerHouseItems_MakeRoom(u8 *villager, int size_class, int mode, int from_2, u8 fits)
{
    int first = 0;
    int end = 0;
    if (!VillagerHouseItems_SlotRange(villager, &first, &end, size_class, mode, (u8) from_2)) {
        return VILLAGER_HOUSE_NO_SLOT;
    }
    int slot = VillagerHouseItems_PickEmpty(villager, first, end);
    if (slot == VILLAGER_HOUSE_NO_SLOT) {
        slot = VillagerHouseItems_PickUnfitting(villager, mode, first, end);
        if (slot == VILLAGER_HOUSE_NO_SLOT && fits) {
            slot = VillagerHouseItems_PickCheapest(villager, first, end);
        }
        if (slot != VILLAGER_HOUSE_NO_SLOT) {
            VillagerHouseItems_MaybeGiveUp(&VillagerHouseItems_Items(villager)[slot]);
        }
    }
    if (slot != VILLAGER_HOUSE_NO_SLOT) {
        VillagerHouseItems_Items(villager)[slot] = VILLAGER_HOUSE_ITEM_NONE;
    }
    return slot;
}
CLEAN_AS(func_0207fad0, VillagerHouseItems_MakeRoom)

/* func_0207fb70: half of the time the item goes to the town's list (non-zero when it found
 * room); the other half it is just dropped (1). */
int VillagerHouseItems_MaybeGiveUp(const u16 *item)
{
    if (func_020644cc(2) != 0) {
        return 1;
    }
    return func_0203a6ec(*item) != 0;
}
CLEAN_AS(func_0207fb70, VillagerHouseItems_MaybeGiveUp)

/* func_0207fb98: the item goes to the town's list; non-zero when it found room. */
int VillagerHouseItems_GiveUp(const u16 *item)
{
    return func_0203a6ec(*item) != 0;
}
CLEAN_AS(func_0207fb98, VillagerHouseItems_GiveUp)

/* func_0207fbb4: a random one of the places `first` to `end` - 1 whose item does not fit the
 * mode; -1 for none, or when `first` is not a place. */
int VillagerHouseItems_PickUnfitting(u8 *villager, int mode, int first, int end)
{
    if (!VillagerHouseItems_IsSlot(villager, (u32) first)) {
        return VILLAGER_HOUSE_NO_SLOT;
    }
    u16 *items = VillagerHouseItems_Items(villager);
    u32 candidates = 0;
    int count = 0;
    for (int i = first; i < end; i++) {
        if (VillagerHouseItems_IsSlot(villager, (u32) i) && items[i] != VILLAGER_HOUSE_ITEM_NONE &&
            !VillagerHouseItems_FitsMode(villager, &items[i], (u32) mode)) {
            candidates |= 1u << i;
            count++;
        }
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_HOUSE_ITEMS);
}
CLEAN_AS(func_0207fbb4, VillagerHouseItems_PickUnfitting)

/* func_0207fc34: whether the item fits the villager's mode: what the mode's filter says, and
 * 1 for a mode without one. The filter is a member function of the villager, called through
 * the game's member pointer. */
int VillagerHouseItems_FitsMode(u8 *villager, u16 *item, u32 mode)
{
    MemberPointer filter = VillagerHouseItems_ModeFilter((u32) (uintptr_t) villager, mode);
    if (filter.function == 0) {
        return 1;
    }
    void *self = MemberPointer_Object(&filter, villager);
    u32 code = MemberPointer_Code(&filter, self);
    return ((int (*)(void *, u16 *))(uintptr_t) code)(self, item) != 0;
}
CLEAN_AS(func_0207fc34, VillagerHouseItems_FitsMode)

/* func_0207fc7c: the filter of a mode 0-4 (data_021d1330), the null member pointer for the
 * others. */
MemberPointer VillagerHouseItems_ModeFilter(u32 villager, u32 mode)
{
    (void) villager;
    u8 group = 3;
    int place = func_0209c2d4(&group, mode);
    if (group == 0 && (u32) place < VILLAGER_HOUSE_FILTERS) {
        return data_021d1330[place];
    }
    return __ptmf_null;
}
CLEAN_AS(func_0207fc7c, VillagerHouseItems_ModeFilter)

/* func_0207fcc8: the filter of mode 4: an item of kind 3 or 4 outside group A that the villager
 * likes (func_02080834 above 0). */
int VillagerHouseItems_FitsMode4(u8 *villager, u16 *item)
{
    if (!func_0204bcdc(item) || is_group_a(*item)) {
        return 0;
    }
    return func_02080834(villager, item) > 0;
}
CLEAN_AS(func_0207fcc8, VillagerHouseItems_FitsMode4)

/* func_0207fd1c: the filter of mode 3: items 0x11a8-0x12a7. */
int VillagerHouseItems_FitsMode3(const u8 *villager, const u16 *item)
{
    (void) villager;
    return *item >= VILLAGER_HOUSE_MODE_3_FIRST && *item <= VILLAGER_HOUSE_MODE_3_LAST;
}
CLEAN_AS(func_0207fd1c, VillagerHouseItems_FitsMode3)

/* func_0207fd44: the filter of mode 2: group A items. */
int VillagerHouseItems_FitsMode2(const u8 *villager, const u16 *item)
{
    (void) villager;
    return is_group_a(*item);
}
CLEAN_AS(func_0207fd44, VillagerHouseItems_FitsMode2)

/* func_0207fd6c: the filter of mode 1: group B items. */
int VillagerHouseItems_FitsMode1(const u8 *villager, const u16 *item)
{
    (void) villager;
    return *item >= MUSEUM_B_FIRST && *item <= MUSEUM_B_LAST;
}
CLEAN_AS(func_0207fd6c, VillagerHouseItems_FitsMode1)

/* func_0207fd94: the filter of mode 0: group C items. */
int VillagerHouseItems_FitsMode0(const u8 *villager, const u16 *item)
{
    (void) villager;
    return *item >= MUSEUM_C_FIRST && *item <= MUSEUM_C_LAST;
}
CLEAN_AS(func_0207fd94, VillagerHouseItems_FitsMode0)

/* func_0207fdbc: the place from `first` to `end` - 1 holding the cheapest item (the last of
 * equals); -1 for none, or when `first` is not a place. */
int VillagerHouseItems_PickCheapest(u8 *villager, int first, int end)
{
    if (!VillagerHouseItems_IsSlot(villager, (u32) first)) {
        return VILLAGER_HOUSE_NO_SLOT;
    }
    u16 *items = VillagerHouseItems_Items(villager);
    int best = VILLAGER_HOUSE_WORTH_MAX;
    int slot = VILLAGER_HOUSE_NO_SLOT;
    for (int i = first; i < end; i++) {
        if (VillagerHouseItems_IsSlot(villager, (u32) i) && items[i] != VILLAGER_HOUSE_ITEM_NONE) {
            int worth = func_0204c878(&items[i]);
            if (worth <= best) {
                slot = i;
                best = worth;
            }
        }
    }
    return slot;
}
CLEAN_AS(func_0207fdbc, VillagerHouseItems_PickCheapest)

/* func_0207fe28: a random empty place from `first` to `end` - 1; -1 for none, or when `first`
 * is not a place. */
int VillagerHouseItems_PickEmpty(u8 *villager, int first, int end)
{
    if (!VillagerHouseItems_IsSlot(villager, (u32) first)) {
        return VILLAGER_HOUSE_NO_SLOT;
    }
    u16 *items = VillagerHouseItems_Items(villager);
    u32 candidates = 0;
    int count = 0;
    for (int i = first; i < end; i++) {
        if (VillagerHouseItems_IsSlot(villager, (u32) i) && items[i] == VILLAGER_HOUSE_ITEM_NONE) {
            candidates |= 1u << i;
            count++;
        }
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_HOUSE_ITEMS);
}
CLEAN_AS(func_0207fe28, VillagerHouseItems_PickEmpty)

/* func_0207fe94: the places for an item of the size class (villager_house_items.h): from
 * `first` up to `end` - 1. 0, with both left as they are, for another class. */
int VillagerHouseItems_SlotRange(const u8 *villager, int *first, int *end, int size_class, int mode, u8 from_2)
{
    (void) villager;
    int wider = mode == 2 || (mode == VILLAGER_MODE_NONE_YET && from_2 != 0);
    switch (size_class) {
        case 0:
            *first = 5;
            *end = 10;
            return 1;
        case 1:
            *first = 1;
            *end = 5;
            if (wider) {
                *first = 3;
            }
            return 1;
        case 2:
            *first = 0;
            *end = wider ? 3 : 1;
            return 1;
    }
    return 0;
}
CLEAN_AS(func_0207fe94, VillagerHouseItems_SlotRange)

/* func_0207ff00: the ten places. */
u16 *VillagerHouseItems_Items(u8 *villager)
{
    return (u16 *) (void *) (villager + VILLAGER_HOUSE_ITEMS_OFFSET);
}
CLEAN_AS(func_0207ff00, VillagerHouseItems_Items)

/* func_0207ff0c: the item a place holds, as the item its code stands for (func_02061b1c), in
 * `out`; 0xfff1 for an empty place or one past 9. */
void VillagerHouseItems_Get(u16 *out, const u8 *villager, int slot)
{
    *out = VILLAGER_HOUSE_ITEM_NONE;
    if (!VillagerHouseItems_IsSlot(villager, (u32) slot)) {
        return;
    }
    const u16 *items = (const u16 *) (const void *) (villager + VILLAGER_HOUSE_ITEMS_OFFSET);
    *out = items[slot];
    if (*out != VILLAGER_HOUSE_ITEM_NONE) {
        u16 stands_for;
        func_02061b1c(&stands_for, out, 1);
        *out = stands_for;
    }
}
CLEAN_AS(func_0207ff0c, VillagerHouseItems_Get)

/* func_0207ff58: which place a template code 0xf000-0xf02f stands for: (code - 0xf000) / 4,
 * less 2 from 3 on (so 0, 1, 2, 1, 2, 3, ... 9); -1 for any other code.
 * QUIRK: codes 3 and 4 name the same places as 1 and 2. */
int VillagerHouseItems_SlotOfCode(const u8 *villager, const u16 *code)
{
    (void) villager;
    u16 value = *code;
    if (value < VILLAGER_HOUSE_SLOT_CODE_FIRST || value > VILLAGER_HOUSE_SLOT_CODE_LAST) {
        return VILLAGER_HOUSE_NO_SLOT;
    }
    int slot = (value - VILLAGER_HOUSE_SLOT_CODE_FIRST) >> 2;
    if (slot >= 3) {
        slot -= 2;
    }
    return slot;
}
CLEAN_AS(func_0207ff58, VillagerHouseItems_SlotOfCode)

/* func_0207ffa0: whether `slot` is one of the ten places. */
int VillagerHouseItems_IsSlot(const u8 *villager, u32 slot)
{
    (void) villager;
    return slot < VILLAGER_HOUSE_ITEMS;
}
CLEAN_AS(func_0207ffa0, VillagerHouseItems_IsSlot)

/* func_0207ffac: the model of the villager's room: 0x1010 plus what bits 2-4 of its data's byte
 * 0x28 give (0 past 4, or with no data). */
int VillagerHouseItems_RoomModel(const u8 *villager)
{
    const u8 *data = func_02080b64(villager);
    int room = 0;
    if (data != NULL) {
        room = (data[0] & 0x1f) >> 2;
        if (room >= VILLAGER_HOUSE_ROOMS) {
            room = 0;
        }
    }
    return VILLAGER_HOUSE_ROOM_FIRST + room;
}
CLEAN_AS(func_0207ffac, VillagerHouseItems_RoomModel)

/* func_0207ffdc: the item template set of the villager's room and its variant: set 3 with byte
 * 0x7d8 % 10 in mode 2, or in modes 8-11 reached from mode 2; else set 2 with byte 0x7d8. 0,
 * with both left as they are, for a villager without a valid NpcId or data. */
int VillagerHouseItems_Template(u8 *villager, int *template_set, int *variant)
{
    if (!NpcId_IsValid(func_0208150c(villager))) {
        return 0;
    }
    if (func_02082500(NpcId_Number(func_0208150c(villager))) == NULL) {
        return 0;
    }
    VillagerModeRecord *record = mode_record(villager);
    /* the mode is read again for each test */
    int mode_2 = func_0209c330(record) == 2;
    if (!mode_2) {
        int later = func_0209c330(record) == VILLAGER_MODE_NONE_YET || func_0209c330(record) == VILLAGER_MODE_LEAVING ||
                    func_0209c330(record) == VILLAGER_MODE_ARRIVED || func_0209c330(record) == VILLAGER_MODE_11;
        mode_2 = later && func_0209c2c0(record) != 0;
    }
    if (mode_2) {
        *template_set = VILLAGER_HOUSE_TEMPLATE_MODE_2;
        *variant = villager[VILLAGER_HOUSE_DRAW] % VILLAGER_HOUSE_TEMPLATE_VARIANTS_MODE_2;
    } else {
        *template_set = VILLAGER_HOUSE_TEMPLATE_OTHER;
        *variant = villager[VILLAGER_HOUSE_DRAW];
    }
    return 1;
}
CLEAN_AS(func_0207ffdc, VillagerHouseItems_Template)
