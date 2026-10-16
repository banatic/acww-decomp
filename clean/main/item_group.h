/* Groups of kind 1 item codes numbered from a first code: the code of a number in the group
 * (the first code for a number past the group) and whether a code is in the group.
 *
 *   0x1100-0x1143  wallpaper (68)              ItemGroup_Wallpaper, ItemGroup_IsWallpaper
 *   0x1144-0x1187  carpets (68)                ItemGroup_IsCarpet
 *   0x11a8-0x12a7  clothes (256, "/cloth/")    ItemGroup_Cloth, ItemGroup_IsCloth
 *   0x1380-0x139f  (32)                        ItemGroup_Item1380, ItemGroup_Is1380
 *   0x13a8-0x13c7  worn on the head, the first model (32; head_look.h)
 *                                              ItemGroup_HeadA, ItemGroup_IsHeadA
 *   0x13c8-0x1407  worn on the head, the second model (64)
 *                                              ItemGroup_IsHeadB
 *   0x1431-0x1470  worn as part C (64; glasses_look.h)
 *                                              ItemGroup_PartC, ItemGroup_IsPartC
 *
 * Each test also has a form that answers nothing (ItemGroup_Test...). */
#ifndef CLEAN_MAIN_ITEM_GROUP_H
#define CLEAN_MAIN_ITEM_GROUP_H

#include "types.h"

u16 ItemGroup_HeadA(u32 index);
u16 ItemGroup_Wallpaper(u16 index);
u16 ItemGroup_Item1380(u32 index);
u16 ItemGroup_PartC(u32 index);
u16 ItemGroup_Cloth(u16 index);
int ItemGroup_IsHeadA(const u16 *code);
void ItemGroup_TestIsHeadA(const u16 *code);
int ItemGroup_IsWallpaper(const u16 *code);
void ItemGroup_TestIsWallpaper(const u16 *code);
int ItemGroup_Is1380(const u16 *code);
void ItemGroup_TestIs1380(const u16 *code);
u16 ItemGroup_IsPartC(const u16 *code);
void ItemGroup_TestIsPartC(const u16 *code);
int ItemGroup_IsCloth(const u16 *code);
void ItemGroup_TestIsCloth(const u16 *code);
int ItemGroup_IsCarpet(const u16 *code);
void ItemGroup_TestIsCarpet(const u16 *code);
int ItemGroup_IsHeadB(const u16 *code);
void ItemGroup_TestIsHeadB(const u16 *code);

/* More groups, with the index of a code in its group (-1 for a code outside it):
 *
 *   0x1144-0x1187  carpets (68)                ItemGroup_Carpet
 *   0x1188-0x11a7  the players' designs (32: four players of eight, design.c)
 *                                              ItemGroup_Design, ItemGroup_IsDesign,
 *                                              ItemGroup_DesignIndex, ItemGroup_DesignOf
 *   0x12b0-0x12e7  insects (56, insect_tables.h)
 *                                              ItemGroup_Insect, ItemGroup_IsInsect,
 *                                              ItemGroup_InsectIndex
 *   0x12e8-0x131f  fish (56, creature_table.h) ItemGroup_IsFish, ItemGroup_FishIndex
 *   0x13c8-0x1407  worn on the head, the second model (64)
 *                                              ItemGroup_HeadB
 *   0x1408-0x1428  worn on the head, the first of a pair (33; item_form.h)
 *                                              ItemGroup_HeadC, ItemGroup_IsHeadC,
 *                                              ItemGroup_HeadCIndex
 *   0x1471-0x1491  worn as part C, the second of a pair (33; glasses_look.h)
 *                                              ItemGroup_PartC2, ItemGroup_IsPartC2,
 *                                              ItemGroup_PartC2Index
 *   0x1492-0x14fd  bags of bells (108, smallest first; player_pockets.h)
 *                                              ItemGroup_BellBag
 *
 * and three groups of room codes (four codes per item): 0x3894-0x38e3 (museum_record.h),
 * 0x450c-0x45db (item_attributes.h) and 0x45dc-0x47d7 (room_sync.h). */
u16 ItemGroup_Carpet(u16 index);
u16 ItemGroup_HeadB(u32 index);
u16 ItemGroup_Insect(u32 index);
u16 ItemGroup_HeadC(u32 index);
u16 ItemGroup_PartC2(u32 index);
u16 ItemGroup_Design(u32 index);
u16 ItemGroup_BellBag(u32 index);
int ItemGroup_IsHeadC(const u16 *code);
int ItemGroup_HeadCIndex(const u16 *code);
int ItemGroup_IsPartC2(const u16 *code);
int ItemGroup_PartC2Index(const u16 *code);
int ItemGroup_IsDesign(const u16 *code);
int ItemGroup_DesignIndex(const u16 *code);
int ItemGroup_DesignSlot(const u16 *code);
int ItemGroup_DesignPlayer(const u16 *code);
int ItemGroup_DesignOf(int player, int slot);
void ItemGroup_ConstructDesign(u16 *code, int player, int slot);
int ItemGroup_IsInsect(const u16 *code);
int ItemGroup_InsectIndex(const u16 *code);
int ItemGroup_IsFish(const u16 *code);
int ItemGroup_FishIndex(const u16 *code);
int ItemGroup_IsRoom3894(const u16 *code);
int ItemGroup_IsRoom45dc(const u16 *code);
int ItemGroup_IsRoom450c(const u16 *code);

#endif
