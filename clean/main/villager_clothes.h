/* The clothes a villager scene object (villager_scene_object.h) shows, its member at 0x64c: a
 * VramCopyMaterial (vram_copy_task.h) that copies the clothes' texture over its model's
 * material, the item shown (0x28; 0xfff1 when constructed, 0xffff while starting) and a link
 * (0x2c) to an entry of the pool at data_021d1e20 (pool_link.h), which holds a slot byte of
 * the clothes' texture files (cloth_slots.h).
 *
 * The texture is the item's (for the items 0x11a8-0x12a7) or else the villager's own design
 * (TownVillager_Design) when the object has a town record. Clothes of the item shown already
 * are not loaded again, except the eight items 0x12a8-0x12af, whose look can change under the
 * same item. */
#ifndef CLEAN_MAIN_VILLAGER_CLOTHES_H
#define CLEAN_MAIN_VILLAGER_CLOTHES_H

#include "pool_link.h"
#include "types.h"
#include "vram_copy_task.h"

typedef struct VillagerClothes {
    VramCopyMaterial copy; /* 0x00 */
    u16 item;              /* 0x28 */
    u8 unk_2a[2];          /* 0x2a */
    PoolLink slot;         /* 0x2c */
} VillagerClothes;

int VillagerClothes_ItemOf(int clothes);
void VillagerClothes_End(VillagerClothes *clothes);
int VillagerClothes_Change(VillagerClothes *clothes, u8 *villager, u16 *item);
int VillagerClothes_LoadTexture(VillagerClothes *clothes, u8 *villager, u16 *item);
int VillagerClothes_Start(VillagerClothes *clothes, u8 *villager, u16 *item);
VillagerClothes *VillagerClothes_Destruct(VillagerClothes *clothes);
VillagerClothes *VillagerClothes_Construct(VillagerClothes *clothes);

#endif
