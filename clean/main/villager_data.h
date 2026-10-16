/* The game's data of each of its 150 villagers (data_020cd884, 0x4e bytes each, func_02082500
 * by the villager number of an NpcId), and what one of the town's villagers reads of its own:
 *
 *   0x06  ten item codes, the items its house starts with (TownVillager_Setup)
 *   0x1a  six pairs of an attribute and a value of it (ItemAttributes_Match), one for each of
 *         the villager's numbers at 0x7d7 (VillagerMode_Counter7D7): the items it likes
 *   0x26  its birthday (month, then day)
 *   0x28  a byte whose bits 2-4 pick its house's room (VillagerHouseItems_RoomModel)
 *   0x29  a byte Design compares
 *   0x2c  its first clothes, an index of the items 0x11a8-0x12a7
 *   0x2e  an index of the items 0x1380-0x139f (the villager's byte 0x7da)
 *   0x2f  the villager's byte 0x7d8 at first
 *   0x30  its wallpaper and 0x31 its carpet (villager_furniture.h)
 *   0x32  eight scores its mode record starts from (villager_mode.h)
 *   0x3a  eight weights of its mode record (4.12 fixed point)
 *   0x4a  its personality, 0x4b whether it can come to a town (villager_residents.h)
 *   0x4c  its species (0-32), 0x4d its song */
#ifndef CLEAN_MAIN_VILLAGER_DATA_H
#define CLEAN_MAIN_VILLAGER_DATA_H

#include "clean.h"
#include "lookups.h"
#include "types.h"

#define VILLAGER_DATA_ITEMS 10
#define VILLAGER_DATA_LIKES 6
#define VILLAGER_DATA_MODE_KINDS 8
/* VillagerData_Species without data; also the number of species. */
#define VILLAGER_DATA_NO_SPECIES 0x21
/* VillagerData_StarSign without data: past the twelve signs. */
#define VILLAGER_DATA_NO_STAR_SIGN 12
/* The items the villager's indexes at 0x2c and 0x2e count from, and how many each has. */
#define VILLAGER_DATA_CLOTHES_FIRST 0x11a8
#define VILLAGER_DATA_CLOTHES_COUNT 0x100
#define VILLAGER_DATA_ITEM_1380_FIRST 0x1380
#define VILLAGER_DATA_ITEM_1380_COUNT 0x20

/* An attribute of items and a value of it. */
typedef struct VillagerDataLike {
    u8 attribute;
    u8 value;
} VillagerDataLike;

typedef struct VillagerData {
    u8 unknown_00[6];
    u16 items[VILLAGER_DATA_ITEMS];              /* 0x06 */
    VillagerDataLike likes[VILLAGER_DATA_LIKES]; /* 0x1a */
    MonthDay birthday;                           /* 0x26 */
    u8 room;                                     /* 0x28 */
    u8 byte_29;                                  /* 0x29 */
    u8 unknown_2a[2];
    u16 clothes;                                /* 0x2c */
    u8 item_1380;                               /* 0x2e */
    u8 byte_2f;                                 /* 0x2f */
    u8 wallpaper;                               /* 0x30 */
    u8 carpet;                                  /* 0x31 */
    u8 mode_scores[VILLAGER_DATA_MODE_KINDS];   /* 0x32 */
    s16 mode_weights[VILLAGER_DATA_MODE_KINDS]; /* 0x3a */
    u8 personality;                             /* 0x4a */
    u8 comes;                                   /* 0x4b */
    u8 species;                                 /* 0x4c */
    u8 song;                                    /* 0x4d */
} VillagerData;

static_assert(offsetof(VillagerData, likes) == 0x1a, "the items a villager likes");
static_assert(offsetof(VillagerData, birthday) == 0x26, "a villager's birthday");
static_assert(offsetof(VillagerData, clothes) == 0x2c, "a villager's clothes");
static_assert(offsetof(VillagerData, mode_weights) == 0x3a, "a villager's mode weights");
static_assert(offsetof(VillagerData, species) == 0x4c, "a villager's species");
static_assert(sizeof(VillagerData) == 0x4e, "a villager's data is 0x4e bytes");

const s16 *VillagerData_ModeWeights(u8 *villager);
int VillagerData_ItemLiking(u8 *villager, u16 *item);
const VillagerDataLike *VillagerData_Like(u8 *villager, u32 index);
const VillagerData *VillagerData_Of(u8 *villager);
const u8 *VillagerData_Byte29(u8 *villager);
u8 VillagerData_SpeciesByte(u8 *villager);
int VillagerData_Species(u8 *villager);
int VillagerData_StarSign(u8 *villager);
const MonthDay *VillagerData_Birthday(u8 *villager);
const u8 *VillagerData_Room(u8 *villager);
void VillagerData_DefaultItem1380(u16 *out, u8 *villager);
void VillagerData_DefaultClothes(u16 *out, u8 *villager);

#endif
