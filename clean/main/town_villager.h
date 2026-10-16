/* One of the town's villagers as a whole (0x7ec bytes, eight at data_021e5a2c, villager_town.h):
 * its parts, how it is constructed, emptied, copied and set up from a villager number.
 *
 *   0x000  eight memories of players (villager_memories.h)
 *   0x400  a design (design_info.h)
 *   0x634  the last letter a player sent it (villager_mail.h)
 *   0x734  its mode record and object (villager_object.h)
 *   0x78c  the ten items of its house (villager_furniture.h)
 *   0x7a0  its NpcId; a villager whose NpcId is not valid is an empty place
 *   0x7b0  four items (villager_items.h)
 *   0x7b8  the town it last lived in (villager_home.h)
 *   0x7c6  its catchphrase (villager_catchphrase.h)
 *   0x7ce  the tile of its house (villager_home.h)
 *   0x7d0  marks of its house's items (villager_entry.h)
 *   0x7d2  its clothes, an item 0x11a8-0x12a7
 *   0x7d4  its wallpaper, 0x7d5 its carpet (villager_furniture.h)
 *   0x7d6  how it came to the town (villager_status.h)
 *   0x7d7  a number 0-5 (villager_mode.h)
 *   0x7d8  a number drawn with its mode (villager_furniture.h)
 *   0x7da  an index of the items 0x1380-0x139f
 *   0x7dc  the town it got the last letter in (villager_mail.h) */
#ifndef CLEAN_MAIN_TOWN_VILLAGER_H
#define CLEAN_MAIN_TOWN_VILLAGER_H

#include "calendar.h"
#include "mail.h"
#include "npc_id.h"
#include "types.h"

#define TOWN_VILLAGER_SIZE 0x7ec
#define TOWN_VILLAGER_DESIGN 0x400
#define TOWN_VILLAGER_LETTER 0x634
#define TOWN_VILLAGER_RECORD 0x734
#define TOWN_VILLAGER_HOUSE_ITEMS 0x78c
#define TOWN_VILLAGER_NPC 0x7a0
#define TOWN_VILLAGER_ITEMS 0x7b0
#define TOWN_VILLAGER_LAST_TOWN 0x7b8
#define TOWN_VILLAGER_HOUSE_TILE 0x7ce
#define TOWN_VILLAGER_CLOTHES 0x7d2
#define TOWN_VILLAGER_NUMBER_7D8 0x7d8
#define TOWN_VILLAGER_ITEM_1380 0x7da
#define TOWN_VILLAGER_LETTER_TOWN 0x7dc
#define TOWN_VILLAGER_NONE (-1)

int TownVillager_IsMemoryIndex(u8 *villager, u32 index);
int TownVillager_IsFreeCompanion(u8 *villager);
int TownVillager_EventYearWithin(u8 *villager, int days, const DateTime *from);
int TownVillager_FirstEmpty(u8 *villagers, int count);
void TownVillager_SetItem1380(u8 *villager, const u16 *item);
void TownVillager_Item1380(u16 *out, u8 *villager);
void TownVillager_SetClothes(u8 *villager, const u16 *clothes);
u16 *TownVillager_Clothes(u8 *villager);
MailLetter *TownVillager_Letter(u8 *villager);
u8 *TownVillager_Design(u8 *villager);
NpcId *TownVillager_NpcId(u8 *villager);
void TownVillager_Setup(u8 *villager, u32 number, int came, const NpcIdHead *town, u8 mode_draw);
void TownVillager_Copy(u8 *dst, const u8 *src);
void TownVillager_Reset(u8 *villager);
u8 *TownVillager_Destruct(u8 *villager);
u8 *TownVillager_Construct(u8 *villager);

#endif
