/* One of the town's villagers as a whole (town_villager.h). */
#include "town_villager.h"

#include "clean.h"
#include "design_info.h"
#include "player_record.h"
#include "player_records.h"
#include "text_string.h"
#include "villager_catchphrase.h"
#include "villager_data.h"
#include "villager_entry.h"
#include "villager_furniture.h"
#include "villager_items.h"
#include "villager_memories.h"
#include "villager_move.h"
#include "villager_object.h"
#include "villager_part_handover.h"
#include "villager_status.h"
#include "villager_town.h"
#include "date_time.h"
#include "event_calendar.h"
#include "item_traits.h"
#include "letter.h"
#include "npc_lookup.h"
#include "small_texts.h"
#include "town_name.h"
#include "villager_memory_entry.h"
#include "villager_mode_record.h"
#include "villager_plot_tile.h"

#define TOWN_VILLAGER_HOUSE_ITEM_COUNT 10
#define TOWN_VILLAGER_ITEM_COUNT 4
#define TOWN_VILLAGER_NO_ITEM 0xfff1
/* The villager's byte 0x7d6 (how it came to the town) of an emptied place. */
#define TOWN_VILLAGER_CAME 0x7d6
#define TOWN_VILLAGER_CAME_RESET 3
/* The mode (villager_mode.h) in which the villager's number at 0x7d8 stays below 10. */
#define TOWN_VILLAGER_MODE_2 2
#define TOWN_VILLAGER_MODE_2_NUMBERS 10
/* The offset of the town's villagers (data_021e5a2c) from data_021dc7a8. */
#define TOWN_VILLAGER_TOWN_OFFSET 0x9284
/* Where a player record's part keeps the villager that handed it an object. */
#define TOWN_VILLAGER_PART_HANDOVER 0xa4

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The game's own constructors and destructors, handed to __cxa_vec_ctor and
 * __cxa_vec_cleanup: of a memory of a player and of an item code. */
extern void func_02081f30(void *memory);
extern void func_02081f18(void *memory);
extern void func_02034ce0(void *item);
extern void func_020051b0(void *item);

static u8 *town_villager_at(u8 *villager, int offset)
{
    return villager + offset;
}

static u16 *town_villager_house_items(u8 *villager)
{
    return (u16 *) (void *) town_villager_at(villager, TOWN_VILLAGER_HOUSE_ITEMS);
}

static VillagerRecord *town_villager_record(u8 *villager)
{
    return (VillagerRecord *) (void *) VillagerStatus_ModeRecord(villager);
}

/* func_02080808: whether `index` names one of the eight memories. */
int TownVillager_IsMemoryIndex(u8 *villager, u32 index)
{
    (void) villager;
    return index < VILLAGER_MEMORIES;
}
CLEAN_AS(func_02080808, TownVillager_IsMemoryIndex)

/* func_02080928: whether the villager can be picked as a companion: its NpcId valid, not the
 * villager planning to move away (VillagerMove_VillagerIndex), its stay VILLAGER_STAY_RESIDENT,
 * and with a current player whose record's part does not hold an object handed over by it. */
int TownVillager_IsFreeCompanion(u8 *villager)
{
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return 0;
    }
    int moving =
        VillagerMove_VillagerIndex((VillagerTown *) (void *) (ItemTraits_StateBlockAddress() + TOWN_VILLAGER_TOWN_OFFSET));
    u8 *record = PlayerRecords_Current();
    if (moving == VillagerStatus_Index(villager)) {
        return 0;
    }
    if (VillagerStatus_Stay(villager) != VILLAGER_STAY_RESIDENT) {
        return 0;
    }
    if (record == NULL) {
        return 0;
    }
    VillagerPartHandover *handover =
        (VillagerPartHandover *) (void *) (PlayerRecord_VillagerPart(record) + TOWN_VILLAGER_PART_HANDOVER);
    return !VillagerPartHandover_IsFrom(handover, TownVillager_NpcId(villager));
}
CLEAN_AS(func_02080928, TownVillager_IsFreeCompanion)

/* func_02080998: the first of the `days` + 1 days from `from` (from the clock when NULL) on
 * which the calendar has an event whose id is the villager's index; the year (byte 5) of that
 * day, or -1 when none has, or the villager's NpcId is not valid or it has no index. */
int TownVillager_EventYearWithin(u8 *villager, int days, const DateTime *from)
{
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return -1;
    }
    if (VillagerStatus_Index(villager) == TOWN_VILLAGER_NONE) {
        return -1;
    }
    int index = VillagerStatus_Index(villager);
    DateTime day = {0};
    if (from == NULL) {
        DateTime_Now(&day);
    } else {
        MI_CpuCopy8(from, &day, sizeof(day));
    }
    for (int i = 0; i <= days; i++) {
        VillagerTownEvent events[VILLAGER_TOWN_DAY_EVENTS];
        DateTime when;
        MI_CpuCopy8(&day, &when, sizeof(when));
        int count = EventCalendar_ListAll((EventCalendarEvent *) events, &when);
        for (int k = 0; k < count; k++) {
            if (events[k].id == index) {
                return day.year;
            }
        }
        DateTime_AddDays(&day, 1);
    }
    return -1;
}
CLEAN_AS(func_02080998, TownVillager_EventYearWithin)

/* func_02080b98: the first of `count` villagers whose NpcId is not valid (an empty place), or
 * -1. */
int TownVillager_FirstEmpty(u8 *villagers, int count)
{
    for (int i = 0; i < count; i++) {
        u8 *villager = villagers + i * TOWN_VILLAGER_SIZE;
        if (!NpcId_IsValid((NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC))) {
            return i;
        }
    }
    return TOWN_VILLAGER_NONE;
}
CLEAN_AS(func_02080b98, TownVillager_FirstEmpty)

/* func_02080c24: the villager's byte 0x7da set to the index of an item 0x1380-0x139f; other
 * items leave it. */
void TownVillager_SetItem1380(u8 *villager, const u16 *item)
{
    u32 code = *item;
    if (code >= VILLAGER_DATA_ITEM_1380_FIRST && code < VILLAGER_DATA_ITEM_1380_FIRST + VILLAGER_DATA_ITEM_1380_COUNT) {
        villager[TOWN_VILLAGER_ITEM_1380] = (u8) (code - VILLAGER_DATA_ITEM_1380_FIRST);
    }
}
CLEAN_AS(func_02080c24, TownVillager_SetItem1380)

/* func_02080c60: the item 0x1380-0x139f the villager's byte 0x7da names (the first for an index
 * past the range). */
void TownVillager_Item1380(u16 *out, u8 *villager)
{
    *out = VILLAGER_DATA_ITEM_1380_FIRST;
    u8 index = villager[TOWN_VILLAGER_ITEM_1380];
    if (index < VILLAGER_DATA_ITEM_1380_COUNT) {
        *out = (u16) (VILLAGER_DATA_ITEM_1380_FIRST + index);
    }
}
CLEAN_AS(func_02080c60, TownVillager_Item1380)

/* func_02080cd8 */
void TownVillager_SetClothes(u8 *villager, const u16 *clothes)
{
    *TownVillager_Clothes(villager) = *clothes;
}
CLEAN_AS(func_02080cd8, TownVillager_SetClothes)

/* func_02080ce4 */
u16 *TownVillager_Clothes(u8 *villager)
{
    return (u16 *) (void *) town_villager_at(villager, TOWN_VILLAGER_CLOTHES);
}
CLEAN_AS(func_02080ce4, TownVillager_Clothes)

/* func_020814f4 */
Letter *TownVillager_Letter(u8 *villager)
{
    return (Letter *) (void *) town_villager_at(villager, TOWN_VILLAGER_LETTER);
}
CLEAN_AS(func_020814f4, TownVillager_Letter)

/* func_02081500 */
u8 *TownVillager_Design(u8 *villager)
{
    return town_villager_at(villager, TOWN_VILLAGER_DESIGN);
}
CLEAN_AS(func_02081500, TownVillager_Design)

/* func_0208150c */
NpcId *TownVillager_NpcId(u8 *villager)
{
    return (NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC);
}
CLEAN_AS(func_0208150c, TownVillager_NpcId)

/* func_02081518: the villager set up as villager `number` of `town` (this town when NULL): its
 * NpcId (with the personality of its data, else 0) and its catchphrase from "st_npc_habit"; with
 * data, also its clothes, the ten items of its house, wallpaper and carpet, a mode drawn from the
 * data's scores (`mode_draw` handed on), its house items reset for that mode, its byte 0x7d8
 * (below 10 in mode 2), the marks of its items and its byte 0x7da. Last how it came to the
 * town (`came`). */
void TownVillager_Setup(u8 *villager, u32 number, int came, const NpcIdHead *town, u8 mode_draw)
{
    const VillagerData *data = NpcLookup_Data((int) number);
    VillagerCatchphraseText text;
    CatchphraseWide_Construct((CatchphraseWide *) &text);
    u8 personality = data != NULL ? data->personality : 0;
    NpcId_Set((NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC), (u8) number, personality, town);
    TextString_ClearWide((TextObject *) (void *) &text);
    if (NpcLookup_CatchphraseToWide(&text, number)) {
        CatchphraseWide_CopyOut((CatchphraseWide *) &text, (u16 *) (void *) town_villager_at(villager, VILLAGER_CATCHPHRASE),
                                VILLAGER_CATCHPHRASE_LENGTH);
    }
    if (data != NULL) {
        u16 clothes = data->clothes;
        *TownVillager_Clothes(villager) = clothes < VILLAGER_DATA_CLOTHES_COUNT ? (u16) (VILLAGER_DATA_CLOTHES_FIRST + clothes)
                                                                                : VILLAGER_DATA_CLOTHES_FIRST;
        u16 *items = town_villager_house_items(villager);
        for (int i = 0; i < TOWN_VILLAGER_HOUSE_ITEM_COUNT; i++) {
            items[i] = data->items[i];
        }
        VillagerFurniture_SetWallpaper(villager, data->wallpaper);
        VillagerFurniture_SetCarpet(villager, data->carpet);
        VillagerObject_DrawRecordMode(town_villager_record(villager), (int) (uintptr_t) data->mode_scores, mode_draw);
        int mode = VillagerModeRecord_Mode(VillagerObject_RecordMode(town_villager_record(villager)));
        VillagerFurniture_ResetForMode(villager, mode, 0);
        villager[TOWN_VILLAGER_NUMBER_7D8] = data->byte_2f;
        if (VillagerModeRecord_Mode(VillagerObject_RecordMode(town_villager_record(villager))) == TOWN_VILLAGER_MODE_2) {
            villager[TOWN_VILLAGER_NUMBER_7D8] = (u8) (villager[TOWN_VILLAGER_NUMBER_7D8] % TOWN_VILLAGER_MODE_2_NUMBERS);
        }
        VillagerEntry_MarkItems(villager);
        villager[TOWN_VILLAGER_ITEM_1380] = data->item_1380;
    }
    VillagerStatus_SetCame(villager, (u8) came);
    CatchphraseWide_Destruct((CatchphraseWide *) &text);
}
CLEAN_AS(func_02081518, TownVillager_Setup)

/* func_0208164c: the whole villager copied. */
void TownVillager_Copy(u8 *dst, const u8 *src)
{
    MI_CpuCopy8(src, dst, TOWN_VILLAGER_SIZE);
}
CLEAN_AS(func_0208164c, TownVillager_Copy)

/* func_02081660: the villager emptied (an empty place): all zero, then its NpcId cleared, the
 * first clothes, no catchphrase, its eight memories, last town, house items and house tile
 * emptied, its mode record and object cleared, came TOWN_VILLAGER_CAME_RESET, its letter, items and
 * letter town emptied. */
void TownVillager_Reset(u8 *villager)
{
    MI_CpuFill8(villager, 0, TOWN_VILLAGER_SIZE);
    NpcId_Clear((NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC));
    *TownVillager_Clothes(villager) = VILLAGER_DATA_CLOTHES_FIRST;
    VillagerCatchphrase_Clear(villager);
    for (int i = 0; i < VILLAGER_MEMORIES; i++) {
        VillagerMemoryEntry_Clear((VillagerMemory *) (void *) town_villager_at(villager, i * (int) sizeof(VillagerMemory)));
    }
    TownName_Clear((TownName *) ((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LAST_TOWN)));
    u16 *items = town_villager_house_items(villager);
    for (int i = 0; i < TOWN_VILLAGER_HOUSE_ITEM_COUNT; i++) {
        items[i] = TOWN_VILLAGER_NO_ITEM;
    }
    VillagerPlotTile_Clear((VillagerPlot *) (void *) town_villager_at(villager, TOWN_VILLAGER_HOUSE_TILE));
    VillagerObject_ClearRecord((VillagerRecord *) (void *) town_villager_at(villager, TOWN_VILLAGER_RECORD));
    villager[TOWN_VILLAGER_CAME] = TOWN_VILLAGER_CAME_RESET;
    Letter_Clear(TownVillager_Letter(villager));
    VillagerItems_Clear(villager);
    TownName_Clear((TownName *) ((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LETTER_TOWN)));
}
CLEAN_AS(func_02081660, TownVillager_Reset)

/* func_02081710: the villager's destructor, its parts from the last to the first. */
u8 *TownVillager_Destruct(u8 *villager)
{
    TownName_Destruct((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LETTER_TOWN));
    VillagerPlotTile_Destruct((VillagerPlot *) (void *) town_villager_at(villager, TOWN_VILLAGER_HOUSE_TILE));
    TownName_Destruct((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LAST_TOWN));
    __cxa_vec_cleanup(town_villager_at(villager, TOWN_VILLAGER_ITEMS), TOWN_VILLAGER_ITEM_COUNT, sizeof(u16), func_020051b0);
    NpcId_Destruct((NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC));
    __cxa_vec_cleanup(town_villager_house_items(villager), TOWN_VILLAGER_HOUSE_ITEM_COUNT, sizeof(u16), func_020051b0);
    VillagerObject_DestructRecord((VillagerRecord *) (void *) town_villager_at(villager, TOWN_VILLAGER_RECORD));
    Letter_Destruct(TownVillager_Letter(villager));
    Design_Destruct((Design *) (void *) town_villager_at(villager, TOWN_VILLAGER_DESIGN));
    __cxa_vec_cleanup(villager, VILLAGER_MEMORIES, sizeof(VillagerMemory), func_02081f18);
    return villager;
}
CLEAN_AS(func_02081710, TownVillager_Destruct)

/* func_020817a8: the villager's constructor; its clothes start as no item. */
u8 *TownVillager_Construct(u8 *villager)
{
    __cxa_vec_ctor(villager, VILLAGER_MEMORIES, sizeof(VillagerMemory), func_02081f30, func_02081f18);
    Design_Construct((char *) town_villager_at(villager, TOWN_VILLAGER_DESIGN));
    Letter_Construct(TownVillager_Letter(villager));
    VillagerObject_ConstructRecord((VillagerRecord *) (void *) town_villager_at(villager, TOWN_VILLAGER_RECORD));
    __cxa_vec_ctor(town_villager_house_items(villager), TOWN_VILLAGER_HOUSE_ITEM_COUNT, sizeof(u16), func_02034ce0,
                   func_020051b0);
    NpcId_Construct((NpcId *) (void *) town_villager_at(villager, TOWN_VILLAGER_NPC));
    __cxa_vec_ctor(town_villager_at(villager, TOWN_VILLAGER_ITEMS), TOWN_VILLAGER_ITEM_COUNT, sizeof(u16), func_02034ce0,
                   func_020051b0);
    TownName_Construct((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LAST_TOWN));
    VillagerPlotTile_Construct((VillagerPlot *) (void *) town_villager_at(villager, TOWN_VILLAGER_HOUSE_TILE));
    *TownVillager_Clothes(villager) = TOWN_VILLAGER_NO_ITEM;
    TownName_Construct((NpcIdHead *) (void *) town_villager_at(villager, TOWN_VILLAGER_LETTER_TOWN));
    return villager;
}
CLEAN_AS(func_020817a8, TownVillager_Construct)
