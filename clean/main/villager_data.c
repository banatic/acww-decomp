/* What one of the town's villagers reads of the game's data of its villager number
 * (villager_data.h). */
#include "villager_data.h"

#include "clean.h"
#include "item_attributes.h"
#include "npc_id.h"
#include "town_villager.h"
#include "villager_mode.h"
#include "npc_lookup.h"

/* A byte for each species (0-32). */
extern const u8 data_020cd4dc[VILLAGER_DATA_NO_SPECIES];

/* The data of the villager's number, as each function here looks it up itself. */
static const VillagerData *villager_data_of(u8 *villager)
{
    return NpcLookup_Data(NpcId_Number(TownVillager_NpcId(villager)));
}

/* func_02080814: the eight weights of the villager's mode record, NULL without data. */
const s16 *VillagerData_ModeWeights(u8 *villager)
{
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? data->mode_weights : NULL;
}
CLEAN_AS(func_02080814, VillagerData_ModeWeights)

/* func_02080834: how well the item matches what the villager likes now (the pair its number at
 * 0x7d7 picks, ItemAttributes_Match); 0 when the number is past 5 or there is no data. */
int VillagerData_ItemLiking(u8 *villager, u16 *item)
{
    const VillagerDataLike *like = VillagerData_Like(villager, VillagerMode_Counter7D7(villager));
    if (like == NULL) {
        return 0;
    }
    return ItemAttributes_Match(item, like->attribute, like->value);
}
CLEAN_AS(func_02080834, VillagerData_ItemLiking)

/* func_02080864: the villager's liking `index` (0-5), NULL past 5 or without data. */
const VillagerDataLike *VillagerData_Like(u8 *villager, u32 index)
{
    if (index >= VILLAGER_DATA_LIKES) {
        return NULL;
    }
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? &data->likes[index] : NULL;
}
CLEAN_AS(func_02080864, VillagerData_Like)

/* func_02080890: the villager's data, NULL when its number has none. */
const VillagerData *VillagerData_Of(u8 *villager)
{
    return villager_data_of(villager);
}
CLEAN_AS(func_02080890, VillagerData_Of)

/* func_020808b0: the byte 0x29 of the villager's data, NULL without data. */
const u8 *VillagerData_Byte29(u8 *villager)
{
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? &data->byte_29 : NULL;
}
CLEAN_AS(func_020808b0, VillagerData_Byte29)

/* func_020808d0: data_020cd4dc's byte for the villager's species; species 0's without data. */
u8 VillagerData_SpeciesByte(u8 *villager)
{
    u32 species = (u32) VillagerData_Species(villager);
    if (species >= VILLAGER_DATA_NO_SPECIES) {
        species = 0;
    }
    return data_020cd4dc[species];
}
CLEAN_AS(func_020808d0, VillagerData_SpeciesByte)

/* func_020808ec: the villager's species, VILLAGER_DATA_NO_SPECIES without data. */
int VillagerData_Species(u8 *villager)
{
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? data->species : VILLAGER_DATA_NO_SPECIES;
}
CLEAN_AS(func_020808ec, VillagerData_Species)

/* func_0208090c: the star sign of the villager's birthday (enum StarSign),
 * VILLAGER_DATA_NO_STAR_SIGN without data. */
int VillagerData_StarSign(u8 *villager)
{
    const MonthDay *birthday = VillagerData_Birthday(villager);
    if (birthday == NULL) {
        return VILLAGER_DATA_NO_STAR_SIGN;
    }
    return (int) Lookups_StarSignOf(birthday);
}
CLEAN_AS(func_0208090c, VillagerData_StarSign)

/* func_02080a2c: the villager's birthday, NULL without data. */
const MonthDay *VillagerData_Birthday(u8 *villager)
{
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? &data->birthday : NULL;
}
CLEAN_AS(func_02080a2c, VillagerData_Birthday)

/* func_02080b64: the byte 0x28 of the villager's data (its room); NULL when its NpcId is not
 * valid or it has no data. */
const u8 *VillagerData_Room(u8 *villager)
{
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return NULL;
    }
    const VillagerData *data = villager_data_of(villager);
    return data != NULL ? &data->room : NULL;
}
CLEAN_AS(func_02080b64, VillagerData_Room)

/* func_02080bd4: the item 0x1380-0x139f the villager's data names (the first of them for an
 * index past the range, and without a valid NpcId or data). */
void VillagerData_DefaultItem1380(u16 *out, u8 *villager)
{
    *out = VILLAGER_DATA_ITEM_1380_FIRST;
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return;
    }
    const VillagerData *data = villager_data_of(villager);
    if (data != NULL) {
        u8 index = data->item_1380;
        *out = index < VILLAGER_DATA_ITEM_1380_COUNT ? (u16) (VILLAGER_DATA_ITEM_1380_FIRST + index)
                                                     : VILLAGER_DATA_ITEM_1380_FIRST;
    }
}
CLEAN_AS(func_02080bd4, VillagerData_DefaultItem1380)

/* func_02080c84: the clothes the villager's data names (the first clothes for an index past
 * the range, and without a valid NpcId or data). */
void VillagerData_DefaultClothes(u16 *out, u8 *villager)
{
    *out = VILLAGER_DATA_CLOTHES_FIRST;
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return;
    }
    const VillagerData *data = villager_data_of(villager);
    if (data != NULL) {
        u16 index = data->clothes;
        *out = index < VILLAGER_DATA_CLOTHES_COUNT ? (u16) (VILLAGER_DATA_CLOTHES_FIRST + index) : VILLAGER_DATA_CLOTHES_FIRST;
    }
}
CLEAN_AS(func_02080c84, VillagerData_DefaultClothes)
