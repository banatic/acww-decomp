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

#endif
