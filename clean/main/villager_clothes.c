/* The clothes a villager scene object shows (villager_clothes.h). */
#include "villager_clothes.h"

#include "clean.h"
#include "cloth_slots.h"
#include "item_code.h"
#include "item_texture.h"
#include "town_villager.h"

static_assert(sizeof(VramCopyMaterial) == 0x28, "VramCopyMaterial size");
static_assert(offsetof(VillagerClothes, item) == 0x28, "VillagerClothes layout");
static_assert(offsetof(VillagerClothes, slot) == 0x2c, "VillagerClothes layout");

#define VILLAGER_CLOTHES_NO_ITEM 0xfff1
#define VILLAGER_CLOTHES_STARTING 0xffff
/* The items whose clothes texture is their own, and those always loaded again. */
#define VILLAGER_CLOTHES_ITEM_FIRST 0x11a8
#define VILLAGER_CLOTHES_ITEM_LAST 0x12a7
#define VILLAGER_CLOTHES_RELOAD_FIRST 0x12a8
#define VILLAGER_CLOTHES_RELOAD_LAST 0x12af
/* The villager scene object's model resource (in its model at 0xec), and its town record. */
#define VILLAGER_CLOTHES_MODEL 0x148
#define VILLAGER_CLOTHES_RECORD 0x830

/* The name of the model's material the clothes are copied over. */
extern const char *const data_020d8d2c;

static int clothes_reloads(u16 item)
{
    return item >= VILLAGER_CLOTHES_RELOAD_FIRST && item <= VILLAGER_CLOTHES_RELOAD_LAST;
}

/* Whether `*item` is the item shown: by variant item when `*item` has variants, else by code. */
static int clothes_same(VillagerClothes *clothes, u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(&clothes->item);
    }
    return *item == clothes->item;
}

/* func_0202defc: the address of the item shown. */
int VillagerClothes_ItemOf(int clothes)
{
    return (int) (uintptr_t) &((VillagerClothes *) (uintptr_t) clothes)->item;
}
CLEAN_AS(func_0202defc, VillagerClothes_ItemOf)

/* func_0202df00: the copy taken off the VBlank queue, and the pool entry given back. */
void VillagerClothes_End(VillagerClothes *clothes)
{
    VramCopyMaterial_End(&clothes->copy);
    PoolLink_Release(&clothes->slot);
}
CLEAN_AS(func_0202df00, VillagerClothes_End)

/* func_0202df18: the clothes of `*item` put on: unless it is the item shown (and not one of
 * 0x12a8-0x12af while both are), its texture loaded (VillagerClothes_LoadTexture) and queued to
 * be copied over the model's material, the item then shown. Whether the copy was queued. */
int VillagerClothes_Change(VillagerClothes *clothes, u8 *villager, u16 *item)
{
    if (clothes_same(clothes, item) && (!clothes_reloads(*item) || !clothes_reloads(clothes->item))) {
        return 0;
    }
    int texture = VillagerClothes_LoadTexture(clothes, villager, item);
    if (texture == 0) {
        return 0;
    }
    const u8 *model = *(const u8 *const *) (const void *) (villager + VILLAGER_CLOTHES_MODEL);
    int queued = VramCopyMaterial_Queue(&clothes->copy, model, data_020d8d2c, (G3dResTex *) (uintptr_t) texture, 0, 0);
    clothes->item = *item;
    return queued;
}
CLEAN_AS(func_0202df18, VillagerClothes_Change)

/* func_0202dfd0: the clothes' texture loaded into the slot of the pool entry: the item's own for
 * the items 0x11a8-0x12a7, else the villager's design when the object has a town record, else
 * the item's. Its textures (ClothTexture_GetTextures), 0 without a slot or a file. */
int VillagerClothes_LoadTexture(VillagerClothes *clothes, u8 *villager, u16 *item)
{
    unsigned char *slot = (unsigned char *) (uintptr_t) PoolLink_Pool1E20Entry(&clothes->slot);
    if (slot == NULL) {
        return 0;
    }
    if (*item >= VILLAGER_CLOTHES_ITEM_FIRST && *item <= VILLAGER_CLOTHES_ITEM_LAST) {
        ClothSlots_Load(slot, item, NULL, 1, 1);
    } else if (*(u8 **) (void *) (villager + VILLAGER_CLOTHES_RECORD) != NULL) {
        u8 *record = *(u8 **) (void *) (villager + VILLAGER_CLOTHES_RECORD);
        ClothSlots_PutDesign(slot, (Design *) (void *) TownVillager_Design(record));
    } else {
        ClothSlots_Load(slot, item, NULL, 1, 1);
    }
    int file = ClothSlots_SlotFile(slot);
    if (file == 0) {
        return 0;
    }
    return (int) (uintptr_t) ClothTexture_GetTextures((DesignModel *) (uintptr_t) file);
}
CLEAN_AS(func_0202dfd0, VillagerClothes_LoadTexture)

/* func_0202e058: the clothes started: no item shown (0xffff), a pool entry taken, then the
 * clothes of `*item` put on. Whether both worked. */
int VillagerClothes_Start(VillagerClothes *clothes, u8 *villager, u16 *item)
{
    clothes->item = VILLAGER_CLOTHES_STARTING;
    if (PoolLink_Take(&clothes->slot) == 0) {
        return 0;
    }
    if (VillagerClothes_Change(clothes, villager, item) == 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_0202e058, VillagerClothes_Start)

/* func_0202e094: the destructor: the pool link's. */
VillagerClothes *VillagerClothes_Destruct(VillagerClothes *clothes)
{
    PoolLink_Pool1E20Destruct(&clothes->slot);
    return clothes;
}
CLEAN_AS(func_0202e094, VillagerClothes_Destruct)

/* func_0202e0a8: the constructor: the copy's, no item, the pool link's. */
VillagerClothes *VillagerClothes_Construct(VillagerClothes *clothes)
{
    VramCopyMaterial_Construct(&clothes->copy);
    clothes->item = VILLAGER_CLOTHES_NO_ITEM;
    PoolLink_Pool1E20Construct(&clothes->slot);
    return clothes;
}
CLEAN_AS(func_0202e0a8, VillagerClothes_Construct)
