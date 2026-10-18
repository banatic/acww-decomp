/* Items the town villagers' talk scenes draw: clothes by style, insects and fish of the date
 * (villager_talk_picks.h). */
#include "villager_talk_picks.h"

#include "clean.h"
#include "date_time.h"
#include "player_records.h"
#include "villager_roster.h"
#include "creature_draw.h"
#include "insect_draw.h"
#include "item_lists.h"

#define VILLAGER_TALK_PICKS_NO_ITEM 0xfff1
#define VILLAGER_TALK_PICKS_CLOTHES_FIRST 0x11a8
#define VILLAGER_TALK_PICKS_CLOTHES_COUNT 0x100
#define VILLAGER_TALK_PICKS_STYLES 10

/* The game's pickers by index (a slot without one holds 0). */
extern const u32 data_020c8efc[VILLAGER_TALK_PICKS_TABLE];
extern const u32 data_020c8f10[VILLAGER_TALK_PICKS_TABLE];

/* func_020264b4: clothes of any of the ten styles but the second style byte (`styles[1]`),
 * drawn for the current player (which 1), or when that gave none for no player (which 0). */
void VillagerTalkPick_ClothesNotStyle1(u16 *out, const u8 *styles, int clothes)
{
    u16 drawn[2];
    u16 mask = 0;
    int count = 0;
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    for (int style = 0; style < VILLAGER_TALK_PICKS_STYLES; style++) {
        if (style != styles[1]) {
            mask = (u16) (mask | (1 << style));
            count++;
        }
    }
    VillagerTalkPick_ClothesOfStyleMask(&drawn[0], mask, count, PlayerRecords_Current(), 1, clothes);
    *out = drawn[0];
    if (*out == VILLAGER_TALK_PICKS_NO_ITEM) {
        VillagerTalkPick_ClothesOfStyleMask(&drawn[1], mask, count, NULL, 0, clothes);
        *out = drawn[1];
    }
}
CLEAN_AS(func_020264b4, VillagerTalkPick_ClothesNotStyle1)

/* func_02026528: clothes of a style drawn from the `count` styles set in `mask`
 * (VillagerRoster_PickBit), for `player` with `which`; 0xfff1 when no style was drawn. */
void VillagerTalkPick_ClothesOfStyleMask(u16 *out, int mask, int count, u8 *player, u8 which, int clothes)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    int style = VillagerRoster_PickBit((unsigned int) mask, count, VILLAGER_TALK_PICKS_STYLES);
    if (style != -1) {
        u16 drawn;
        ItemLists_DrawRange(&drawn, VILLAGER_TALK_PICKS_CLOTHES_FIRST, VILLAGER_TALK_PICKS_CLOTHES_COUNT,
                            (u16 *) (uintptr_t) clothes, 1, player, which, style, 0, 1);
        *out = drawn;
    }
}
CLEAN_AS(func_02026528, VillagerTalkPick_ClothesOfStyleMask)

/* The picker of `table` for `index` called with the date of now; 0xfff1 when there is none. */
static void pick_by_index(u16 *out, const u32 *table, unsigned int index)
{
    if (index < VILLAGER_TALK_PICKS_TABLE && table[index] != 0) {
        u32 function = table[index];
        DateTime now = {0};
        DateTime_Now(&now);
        ((void (*)(u16 *, DateTime *))(uintptr_t) function)(out, &now);
        return;
    }
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
}

/* A fish of the classes first-last for the date. */
static int pick_fish(u16 *out, const DateTime *now, int first, int last)
{
    return CreatureDraw_FishOfBands(out, first, last, now->month, now->day);
}

/* An insect of the classes first-last for the month. */
static int pick_insect(u16 *out, const DateTime *now, int first, int last)
{
    return InsectDraw_OfBands(out, first, last, now->month);
}

/* func_02026584: a fish by the picker for `index` (data_020c8f10). */
void VillagerTalkPick_Fish(u16 *out, int unused, unsigned int index)
{
    (void) unused;
    pick_by_index(out, data_020c8f10, index);
}
CLEAN_AS(func_02026584, VillagerTalkPick_Fish)

/* func_020265c0: a fish of the classes 3-4, else 0-2. */
void VillagerTalkPick_Fish4(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_fish(out, now, 3, 4) != 0) {
        return;
    }
    pick_fish(out, now, 0, 2);
}
CLEAN_AS(func_020265c0, VillagerTalkPick_Fish4)

/* func_020265fc: a fish of the classes 2-3, else 0-1, else 4. */
void VillagerTalkPick_Fish3(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_fish(out, now, 2, 3) != 0) {
        return;
    }
    if (pick_fish(out, now, 0, 1) != 0) {
        return;
    }
    pick_fish(out, now, 4, 4);
}
CLEAN_AS(func_020265fc, VillagerTalkPick_Fish3)

/* func_0202664c: a fish of the classes 1-2, else 0, else 3-4. */
void VillagerTalkPick_Fish1(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_fish(out, now, 1, 2) != 0) {
        return;
    }
    if (pick_fish(out, now, 0, 0) != 0) {
        return;
    }
    pick_fish(out, now, 3, 4);
}
CLEAN_AS(func_0202664c, VillagerTalkPick_Fish1)

/* func_0202669c: a fish of the classes 0-1, else 2-4. */
void VillagerTalkPick_Fish0(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_fish(out, now, 0, 1) != 0) {
        return;
    }
    pick_fish(out, now, 2, 4);
}
CLEAN_AS(func_0202669c, VillagerTalkPick_Fish0)

/* func_020266d8: an insect by the picker for `index` (data_020c8efc). */
void VillagerTalkPick_Insect(u16 *out, int unused, unsigned int index)
{
    (void) unused;
    pick_by_index(out, data_020c8efc, index);
}
CLEAN_AS(func_020266d8, VillagerTalkPick_Insect)

/* func_02026714: an insect of the classes 3-4, else 0-2. */
void VillagerTalkPick_Insect4(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_insect(out, now, 3, 4) == 0) {
        pick_insect(out, now, 0, 2);
    }
}
CLEAN_AS(func_02026714, VillagerTalkPick_Insect4)

/* func_02026748: an insect of the classes 2-3, else 0-1, else 4. */
void VillagerTalkPick_Insect3(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_insect(out, now, 2, 3) != 0) {
        return;
    }
    if (pick_insect(out, now, 0, 1) != 0) {
        return;
    }
    pick_insect(out, now, 4, 4);
}
CLEAN_AS(func_02026748, VillagerTalkPick_Insect3)

/* func_0202678c: an insect of the classes 1-2, else 0, else 3-4. */
void VillagerTalkPick_Insect1(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_insect(out, now, 1, 2) != 0) {
        return;
    }
    if (pick_insect(out, now, 0, 0) != 0) {
        return;
    }
    pick_insect(out, now, 3, 4);
}
CLEAN_AS(func_0202678c, VillagerTalkPick_Insect1)

/* func_020267d0: an insect of the classes 0-1, else 2-4. */
void VillagerTalkPick_Insect0(u16 *out, const DateTime *now)
{
    *out = VILLAGER_TALK_PICKS_NO_ITEM;
    if (pick_insect(out, now, 0, 1) == 0) {
        pick_insect(out, now, 2, 4);
    }
}
CLEAN_AS(func_020267d0, VillagerTalkPick_Insect0)
