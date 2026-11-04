/* One villager sick in bed (villager_sickness.h). */
#include "villager_sickness.h"

#include "clean.h"
#include "villager_town.h"
#include "calendar.h"
#include "date_time.h"
#include "item_object.h"
#include "main_random.h"
#include "player_id.h"
#include "town_villager.h"
#include "villager_checks.h"
#include "villager_data.h"
#include "villager_sickness_record.h"
#include "villager_roster.h"
#include "villager_status.h"

static_assert(offsetof(VillagerSickness, npc) == 0x0c, "npc");
static_assert(offsetof(VillagerSickness, players) == 0x1c, "players");
static_assert(offsetof(VillagerSickness, started) == 0xb2, "started");
static_assert(offsetof(VillagerSickness, last_step) == 0xb6, "last step");
static_assert(offsetof(VillagerSickness, stage) == 0xba, "stage");

/* The days after falling sick from which the first steps are taken at once. */
#define VILLAGER_SICKNESS_FIRST_DAYS 10
/* Steps left over from this many on the days forward clear the record. */
#define VILLAGER_SICKNESS_LEFT_OVER 3

/* The chance of a sickness in each month: a villager falls sick when a random number below it is below
 * the villager's byte 3 + 0x80. */
extern const u16 data_020cd4c4[12];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

static int magnitude(int value)
{
    return value < 0 ? -value : value;
}

/* The day of the last step set from `when`. */
static void set_last_step(VillagerSickness *sickness, const DateTime *when)
{
    sickness->last_step.year = when->year;
    sickness->last_step.month = when->month;
    sickness->last_step.day = when->day;
}

/* func_0207b05c: the sickness brought up to today.
 *
 * With no villager named, a town of seven or more villagers may start one: a villager picked
 * with this month's chance (VillagerSickness_PickVillager) falls sick today; it is kept at
 * 0x4076 and the ones out walking are drawn again.
 *
 * With one named: a sickness whose start is after today is cleared. One at stage 5 (well) is kept for
 * the three days from its last step, then cleared. Otherwise one step is taken for each day
 * since the last step (either way): once ten days from the start have passed (and only the
 * first time, which sets the start's last byte) the steps up to the ninth day from the start are
 * taken whatever, then the rest stop at stage 5. When the steps did not reach stage 5 the last
 * step is today. When they did: going forward with three or more steps left over, the record is
 * cleared; else the day of the last step moves by the steps taken (back, unless a step was left
 * over, which clears the record).
 *
 * QUIRK: the steps owed for the first days are cut to the signed days since the last step, so
 * when the clock went back past it they are not taken at all. */
void VillagerSickness_Update(VillagerTown *town)
{
    VillagerSickness *sickness = &town->sickness;
    int villager = VillagerSickness_VillagerIndex(town);
    Date today;
    Calendar_Today(&today);

    if (villager == VILLAGER_TOWN_NONE) {
        if (!VillagerSickness_HasEnoughVillagers(town)) {
            return;
        }
        villager = VillagerSickness_PickVillager(town, (u8) (today.month - 1));
        if (villager == VILLAGER_TOWN_NONE) {
            return;
        }
        u8 *picked = VillagerRoster_At(town, villager);
        if (picked != NULL && has_villager(picked)) {
            VillagerSicknessRecord_Start(sickness, TownVillager_NpcId(picked), &today);
            town->last_sick = (s8) villager;
            VillagerOutdoors_ClearTime(&town->outdoors);
        }
        return;
    }

    if (!Calendar_IsOnOrAfter(&today, &sickness->started)) {
        VillagerSicknessRecord_Clear(sickness);
        return;
    }
    if (VillagerSicknessRecord_IsWell(sickness)) {
        if (!VillagerSicknessRecord_IsRecentlyCured(sickness, &today)) {
            VillagerSicknessRecord_Clear(sickness);
        }
        return;
    }
    int days = Calendar_DaysFrom(&today, &sickness->last_step);
    if (days == 0) {
        return;
    }

    int owed = 0;
    int first_days = 0;
    if (sickness->started.unused == 0 && Calendar_DaysFrom(&today, &sickness->started) >= VILLAGER_SICKNESS_FIRST_DAYS) {
        int done = Calendar_DaysFrom(&sickness->last_step, &sickness->started);
        if (done >= 0 && done < VILLAGER_SICKNESS_FIRST_DAYS) {
            owed = VILLAGER_SICKNESS_FIRST_DAYS - 1 - done;
        }
        first_days = 1;
    }
    int left = magnitude(days);
    int taken = 0;
    if (owed > left) {
        owed = days;
    }
    for (; owed > 0; owed--) {
        VillagerSickness_Step(town);
        left--;
        taken++;
    }
    if (first_days) {
        sickness->started.unused = 1;
    }
    while (left > 0) {
        VillagerSickness_Step(town);
        left--;
        taken++;
        if (VillagerSicknessRecord_IsWell(sickness)) {
            break;
        }
    }

    if (!VillagerSicknessRecord_IsWell(sickness)) {
        MI_CpuCopy8(&today, &sickness->last_step, sizeof(Date));
        return;
    }
    if (left >= VILLAGER_SICKNESS_LEFT_OVER && days > 0) {
        VillagerSicknessRecord_Clear(sickness);
        return;
    }
    if (taken <= 0) {
        return;
    }
    DateTime when;
    DateTime_Set(&when, &sickness->last_step, 0, 0, 0);
    if (days > 0) {
        DateTime_AddDays(&when, taken);
        set_last_step(sickness, &when);
        return;
    }
    if (left > 0) {
        VillagerSicknessRecord_Clear(sickness);
        return;
    }
    DateTime_SubtractDays(&when, taken);
    set_last_step(sickness, &when);
}
CLEAN_AS(func_0207b05c, VillagerSickness_Update)

/* func_0207b268: one day's step of the sickness, and the player id of the stage it moves to
 * emptied. When a player handed the medicine at the current stage (its player id is set), or
 * the first days are past, the villager gets better: the stage goes down (from 0 to 5, well;
 * 5 and above stay); otherwise it gets worse: up, up to 4, staying there.
 * QUIRK: the stage is kept in a byte, so going up from 0xff gives stage 0. */
void VillagerSickness_Step(VillagerTown *town)
{
    VillagerSickness *sickness = &town->sickness;
    int stage = sickness->stage;
    u8 *id = NULL;

    if (VillagerSicknessRecord_HasStagePlayer(sickness) || sickness->started.unused != 0) {
        if (stage == 0) {
            stage = VILLAGER_SICKNESS_WELL;
        } else if (stage < VILLAGER_SICKNESS_STAGES) {
            stage--;
        }
        sickness->stage = (u8) stage;
        id = (u8 *) VillagerSicknessRecord_Player(sickness, sickness->stage);
    } else if ((u8) (stage + 1) < VILLAGER_SICKNESS_STAGES) {
        sickness->stage = (u8) (stage + 1);
        id = (u8 *) VillagerSicknessRecord_Player(sickness, sickness->stage);
    } else if (stage < VILLAGER_SICKNESS_STAGES) {
        id = (u8 *) VillagerSicknessRecord_Player(sickness, (u32) stage);
    }
    if (id != NULL) {
        PlayerId_Clear((DesignCreator *) (void *) id);
    }
}
CLEAN_AS(func_0207b268, VillagerSickness_Step)

/* func_0207b2f8: whether the town has seven villagers or more. */
int VillagerSickness_HasEnoughVillagers(VillagerTown *town)
{
    return VillagerRoster_Count(town) >= VILLAGER_SICKNESS_MIN_VILLAGERS;
}
CLEAN_AS(func_0207b2f8, VillagerSickness_HasEnoughVillagers)

/* func_0207b310: a villager to fall sick in month `month` (0-11), or -1: a random one of the
 * resident villagers no player has in its record (func_0207dca8) for which func_02080998 gives
 * -1, other than the last one picked; it falls sick when a random number below the month's chance
 * is below its byte 3 + 0x80.
 * REQUIRES: func_02080890 finds the data of the villager picked, as it does for a valid NpcId. */
int VillagerSickness_PickVillager(VillagerTown *town, unsigned int month)
{
    if (month >= 12) {
        return VILLAGER_TOWN_NONE;
    }
    u8 candidates = 0;
    int count = 0;
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (i != town->last_sick && has_villager(villager) && VillagerStatus_Stay((u8 *) villager) == 3 &&
            VillagerCheck_NoPlayerHolds((u8 *) villager) && TownVillager_BirthdayYearWithin((u8 *) villager, 15, &now) == -1) {
            candidates |= (u8) (1u << i);
            count++;
        }
    }
    int chosen = VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
    u8 *villager = VillagerRoster_At(town, chosen);
    if (villager != NULL) {
        const u8 *data = (const u8 *) VillagerData_Of(villager);
        if ((int) MainRandom_Below(data_020cd4c4[month]) < data[3] + 0x80) {
            return chosen;
        }
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207b310, VillagerSickness_PickVillager)

/* func_0207b3dc: the index of the villager the record names, or -1 when no one is sick. */
int VillagerSickness_VillagerIndex(VillagerTown *town)
{
    if (ItemObject_IsInUse((ItemObject *) (void *) VillagerSicknessRecord_Object(VillagerSickness_Record(town)))) {
        return VillagerRoster_IndexOf(town, VillagerSicknessRecord_Npc(VillagerSickness_Record(town)));
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207b3dc, VillagerSickness_VillagerIndex)

/* func_0207b410 */
VillagerSickness *VillagerSickness_Record(VillagerTown *town)
{
    return &town->sickness;
}
CLEAN_AS(func_0207b410, VillagerSickness_Record)
