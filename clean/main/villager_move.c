/* One villager's plan to move away (villager_move.h). */
#include "villager_move.h"

#include "clean.h"
#include "villager_town.h"

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
extern NpcId *func_0208150c(const void *villager);                    /* the villager's NpcId, at 0x7a0 */
extern int func_0207f150(const void *villager);                       /* 0-3, from three tests of the villager */
extern u8 *func_0207cec0(VillagerTown *town, int villager);           /* villager `villager`, or NULL past 7 */
extern int func_0207cf14(const VillagerTown *town, const NpcId *npc); /* the villager it names, or -1 */
extern int func_0207cad4(const VillagerTown *town);                   /* how many villagers it has (func_0207cadc) */
/* A random one of the `count` bits set in `candidates` (of `bits`), or -1 for none. */
extern int func_0207cc54(u32 candidates, int count, int bits);
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */
/* Whether no player of the town has the villager in its record's part at 0x1e40. */
extern int func_0207dca8(const void *villager);
extern int func_02080998(const void *villager, int n, const DateTime *now);
extern const u8 *func_02080890(const void *villager);           /* the villager's data, or NULL */
extern void func_0209e474(DateTime *now);                       /* the clock's date and time */
extern void func_0209df64(Date *today);                         /* Calendar_Today */
extern int func_0209dd9c(const Date *date, const Date *other);  /* Calendar_IsOnOrAfter */
extern int func_0209dcdc(const Date *date, const Date *origin); /* Calendar_DaysFrom */
extern void func_0209dfd8(DateTime *dst, const Date *date, u8 hour, u8 minute, u8 second);
extern void func_0209e29c(DateTime *when, int days); /* DateTime_AddDays */
extern void func_0209e140(DateTime *when, int days); /* DateTime_SubtractDays */
extern void func_0209a77c(VillagerMove *move);       /* the record cleared: no plan */
extern int func_0209a654(const VillagerMove *move);  /* whether its stage is 5 */
/* Whether its stage is 5 and `today` (the date when NULL) is 0-2 days after its last step. */
extern int func_0209a610(const VillagerMove *move, const Date *today);
/* Whether the player id of the current stage is set. */
extern int func_0209a67c(const VillagerMove *move);
extern u8 *func_0209a6fc(VillagerMove *move, u32 stage); /* that stage's player id; NULL past 4 */
/* A plan for the villager of `npc` from `today`: stage 1 or 2. */
extern void func_0209a710(VillagerMove *move, const NpcId *npc, const Date *today);
extern u8 *func_0209a778(VillagerMove *move);    /* its object */
extern NpcId *func_0209a774(VillagerMove *move); /* its NpcId */
extern int func_0209bd44(const u8 *object);      /* whether it holds something */
extern void func_02095238(u8 *id);               /* a player id emptied */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(func_0208150c(villager));
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
    func_0209df64(&today);

    if (villager == VILLAGER_TOWN_NONE) {
        if (!VillagerMove_TownIsFull(town)) {
            return;
        }
        villager = VillagerMove_PickVillager(town, (u8) (today.month - 1));
        if (villager == VILLAGER_TOWN_NONE) {
            return;
        }
        u8 *picked = func_0207cec0(town, villager);
        if (picked != NULL && has_villager(picked)) {
            func_0209a710(move, func_0208150c(picked), &today);
            town->move_index = (s8) villager;
            VillagerOutdoors_ClearTime(&town->outdoors);
        }
        return;
    }

    if (!func_0209dd9c(&today, &move->started)) {
        func_0209a77c(move);
        return;
    }
    if (func_0209a654(move)) {
        if (!func_0209a610(move, &today)) {
            func_0209a77c(move);
        }
        return;
    }
    int days = func_0209dcdc(&today, &move->last_step);
    if (days == 0) {
        return;
    }

    int owed = 0;
    int first_days = 0;
    if (move->started.unused == 0 && func_0209dcdc(&today, &move->started) >= VILLAGER_MOVE_FIRST_DAYS) {
        int done = func_0209dcdc(&move->last_step, &move->started);
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
        if (func_0209a654(move)) {
            break;
        }
    }

    if (!func_0209a654(move)) {
        MI_CpuCopy8(&today, &move->last_step, sizeof(Date));
        return;
    }
    if (left >= VILLAGER_MOVE_LEFT_OVER && days > 0) {
        func_0209a77c(move);
        return;
    }
    if (taken <= 0) {
        return;
    }
    DateTime when;
    func_0209dfd8(&when, &move->last_step, 0, 0, 0);
    if (days > 0) {
        func_0209e29c(&when, taken);
        set_last_step(move, &when);
        return;
    }
    if (left > 0) {
        func_0209a77c(move);
        return;
    }
    func_0209e140(&when, taken);
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

    if (func_0209a67c(move) || move->started.unused != 0) {
        if (stage == 0) {
            stage = VILLAGER_MOVE_STAGE_NONE;
        } else if (stage < VILLAGER_MOVE_STAGES) {
            stage--;
        }
        move->stage = (u8) stage;
        id = func_0209a6fc(move, move->stage);
    } else if ((u8) (stage + 1) < VILLAGER_MOVE_STAGES) {
        move->stage = (u8) (stage + 1);
        id = func_0209a6fc(move, move->stage);
    } else if (stage < VILLAGER_MOVE_STAGES) {
        id = func_0209a6fc(move, (u32) stage);
    }
    if (id != NULL) {
        func_02095238(id);
    }
}
CLEAN_AS(func_0207b268, VillagerMove_Step)

/* func_0207b2f8: whether the town has seven villagers or more. */
int VillagerMove_TownIsFull(VillagerTown *town)
{
    return func_0207cad4(town) >= VILLAGER_MOVE_MIN_VILLAGERS;
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
    func_0209e474(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (i != town->move_index && has_villager(villager) && func_0207f150(villager) == 3 && func_0207dca8(villager) &&
            func_02080998(villager, 15, &now) == -1) {
            candidates |= (u8) (1u << i);
            count++;
        }
    }
    int chosen = func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
    u8 *villager = func_0207cec0(town, chosen);
    if (villager != NULL) {
        const u8 *data = func_02080890(villager);
        if ((int) func_020644cc(data_020cd4c4[month]) < data[3] + 0x80) {
            return chosen;
        }
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207b310, VillagerMove_PickVillager)

/* func_0207b3dc: the index of the villager the plan names, or -1 when there is no plan. */
int VillagerMove_VillagerIndex(VillagerTown *town)
{
    if (func_0209bd44(func_0209a778(VillagerMove_Record(town)))) {
        return func_0207cf14(town, func_0209a774(VillagerMove_Record(town)));
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
