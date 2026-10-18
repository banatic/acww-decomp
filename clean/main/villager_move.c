/* One villager's plan to move away (villager_move.h). */
#include "villager_move.h"

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
#include "villager_move_record.h"
#include "villager_roster.h"
#include "villager_status.h"

static_assert(offsetof(VillagerMove, npc) == 0x0c, "npc");
static_assert(offsetof(VillagerMove, players) == 0x1c, "players");
static_assert(offsetof(VillagerMove, started) == 0xb2, "started");
static_assert(offsetof(VillagerMove, last_step) == 0xb6, "last step");
static_assert(offsetof(VillagerMove, stage) == 0xba, "stage");

/* The days after the start from which the plan's first steps are taken at once. */
#define VILLAGER_MOVE_FIRST_DAYS 10
/* Steps left over from this many on the days forward clear the plan. */
#define VILLAGER_MOVE_LEFT_OVER 3

/* The chance of a plan in each month: a plan is made when a random number below it is below
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
static void set_last_step(VillagerMove *move, const DateTime *when)
{
    move->last_step.year = when->year;
    move->last_step.month = when->month;
    move->last_step.day = when->day;
}

/* func_0207b05c: the plan brought up to today.
 *
 * With no villager named, a town of seven or more villagers may start one: a villager picked
 * with this month's chance (VillagerMove_PickVillager) gets a plan from today; it is kept at
 * 0x4076 and the ones out walking are drawn again.
 *
 * With one named: a plan whose start is after today is cleared. A plan at stage 5 is kept for
 * the three days from its last step, then cleared. Otherwise one step is taken for each day
 * since the last step (either way): once ten days from the start have passed (and only the
 * first time, which sets the start's last byte) the steps up to the ninth day from the start are
 * taken whatever, then the rest stop at stage 5. When the steps did not reach stage 5 the last
 * step is today. When they did: going forward with three or more steps left over, the plan is
 * cleared; else the day of the last step moves by the steps taken (back, unless a step was left
 * over, which clears the plan).
 *
 * QUIRK: the steps owed for the first days are cut to the signed days since the last step, so
 * when the clock went back past it they are not taken at all. */
void VillagerMove_Update(VillagerTown *town)
{
    VillagerMove *move = &town->move;
    int villager = VillagerMove_VillagerIndex(town);
    Date today;
    Calendar_Today(&today);

    if (villager == VILLAGER_TOWN_NONE) {
        if (!VillagerMove_TownIsFull(town)) {
            return;
        }
        villager = VillagerMove_PickVillager(town, (u8) (today.month - 1));
        if (villager == VILLAGER_TOWN_NONE) {
            return;
        }
        u8 *picked = VillagerRoster_At(town, villager);
        if (picked != NULL && has_villager(picked)) {
            VillagerMoveRecord_Start(move, TownVillager_NpcId(picked), &today);
            town->move_index = (s8) villager;
            VillagerOutdoors_ClearTime(&town->outdoors);
        }
        return;
    }

    if (!Calendar_IsOnOrAfter(&today, &move->started)) {
        VillagerMoveRecord_Clear(move);
        return;
    }
    if (VillagerMoveRecord_IsIdle(move)) {
        if (!VillagerMoveRecord_IsRecentlyDone(move, &today)) {
            VillagerMoveRecord_Clear(move);
        }
        return;
    }
    int days = Calendar_DaysFrom(&today, &move->last_step);
    if (days == 0) {
        return;
    }

    int owed = 0;
    int first_days = 0;
    if (move->started.unused == 0 && Calendar_DaysFrom(&today, &move->started) >= VILLAGER_MOVE_FIRST_DAYS) {
        int done = Calendar_DaysFrom(&move->last_step, &move->started);
        if (done >= 0 && done < VILLAGER_MOVE_FIRST_DAYS) {
            owed = VILLAGER_MOVE_FIRST_DAYS - 1 - done;
        }
        first_days = 1;
    }
    int left = magnitude(days);
    int taken = 0;
    if (owed > left) {
        owed = days;
    }
    for (; owed > 0; owed--) {
        VillagerMove_Step(town);
        left--;
        taken++;
    }
    if (first_days) {
        move->started.unused = 1;
    }
    while (left > 0) {
        VillagerMove_Step(town);
        left--;
        taken++;
        if (VillagerMoveRecord_IsIdle(move)) {
            break;
        }
    }

    if (!VillagerMoveRecord_IsIdle(move)) {
        MI_CpuCopy8(&today, &move->last_step, sizeof(Date));
        return;
    }
    if (left >= VILLAGER_MOVE_LEFT_OVER && days > 0) {
        VillagerMoveRecord_Clear(move);
        return;
    }
    if (taken <= 0) {
        return;
    }
    DateTime when;
    DateTime_Set(&when, &move->last_step, 0, 0, 0);
    if (days > 0) {
        DateTime_AddDays(&when, taken);
        set_last_step(move, &when);
        return;
    }
    if (left > 0) {
        VillagerMoveRecord_Clear(move);
        return;
    }
    DateTime_SubtractDays(&when, taken);
    set_last_step(move, &when);
}
CLEAN_AS(func_0207b05c, VillagerMove_Update)

/* func_0207b268: one step of the plan, and the player id of the stage it moves to emptied.
 * When the player id of the current stage is set, or the first days are past, the stage goes
 * down (from 0 to 5, the end; 5 and above stay); otherwise it goes up, up to 4, staying there.
 * QUIRK: the stage is kept in a byte, so going up from 0xff gives stage 0. */
void VillagerMove_Step(VillagerTown *town)
{
    VillagerMove *move = &town->move;
    int stage = move->stage;
    u8 *id = NULL;

    if (VillagerMoveRecord_HasStagePlayer(move) || move->started.unused != 0) {
        if (stage == 0) {
            stage = VILLAGER_MOVE_STAGE_NONE;
        } else if (stage < VILLAGER_MOVE_STAGES) {
            stage--;
        }
        move->stage = (u8) stage;
        id = (u8 *) VillagerMoveRecord_Player(move, move->stage);
    } else if ((u8) (stage + 1) < VILLAGER_MOVE_STAGES) {
        move->stage = (u8) (stage + 1);
        id = (u8 *) VillagerMoveRecord_Player(move, move->stage);
    } else if (stage < VILLAGER_MOVE_STAGES) {
        id = (u8 *) VillagerMoveRecord_Player(move, (u32) stage);
    }
    if (id != NULL) {
        PlayerId_Clear((DesignCreator *) (void *) id);
    }
}
CLEAN_AS(func_0207b268, VillagerMove_Step)

/* func_0207b2f8: whether the town has seven villagers or more. */
int VillagerMove_TownIsFull(VillagerTown *town)
{
    return VillagerRoster_Count(town) >= VILLAGER_MOVE_MIN_VILLAGERS;
}
CLEAN_AS(func_0207b2f8, VillagerMove_TownIsFull)

/* func_0207b310: a villager to plan a move in month `month` (0-11), or -1: a random one of the
 * resident villagers no player has in its record (func_0207dca8) for which func_02080998 gives
 * -1, other than the last one picked; it plans when a random number below the month's chance
 * is below its byte 3 + 0x80.
 * REQUIRES: func_02080890 finds the data of the villager picked, as it does for a valid NpcId. */
int VillagerMove_PickVillager(VillagerTown *town, unsigned int month)
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
        if (i != town->move_index && has_villager(villager) && VillagerStatus_Stay((u8 *) villager) == 3 &&
            VillagerCheck_NoPlayerHolds((u8 *) villager) && TownVillager_EventYearWithin((u8 *) villager, 15, &now) == -1) {
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
CLEAN_AS(func_0207b310, VillagerMove_PickVillager)

/* func_0207b3dc: the index of the villager the plan names, or -1 when there is no plan. */
int VillagerMove_VillagerIndex(VillagerTown *town)
{
    if (ItemObject_IsInUse((ItemObject *) (void *) VillagerMoveRecord_Object(VillagerMove_Record(town)))) {
        return VillagerRoster_IndexOf(town, VillagerMoveRecord_Npc(VillagerMove_Record(town)));
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207b3dc, VillagerMove_VillagerIndex)

/* func_0207b410 */
VillagerMove *VillagerMove_Record(VillagerTown *town)
{
    return &town->move;
}
CLEAN_AS(func_0207b410, VillagerMove_Record)
