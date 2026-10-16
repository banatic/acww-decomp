/* Villagers moving into and out of the town (villager_residents.h). */
#include "villager_residents.h"

#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "villager_bonds.h"
#include "villager_copy.h"
#include "villager_entry.h"
#include "villager_move.h"
#include "villager_outdoors.h"
#include "villager_roster.h"

/* The bytes of a villager's data (data_020cd884) read here. */
#define VILLAGER_RESIDENTS_DATA_PERSONALITY 0x4a
#define VILLAGER_RESIDENTS_DATA_COMES 0x4b
#define VILLAGER_RESIDENTS_COMES_ALWAYS 0
#define VILLAGER_RESIDENTS_COMES_NEVER 2 /* and above */
/* The days from the last change after which a leaver is always picked, and a newcomer always
 * comes after a villager has left; before, a draw decides. */
#define VILLAGER_RESIDENTS_LEAVE_DAYS 4
#define VILLAGER_RESIDENTS_ARRIVE_DAYS 8
/* The days a leaver stays in mode 9 before it goes. */
#define VILLAGER_RESIDENTS_LEAVER_DAYS 2
/* What the counts of the personalities start below: more than a town's villagers. */
#define VILLAGER_RESIDENTS_COUNT_START 9
#define VILLAGER_RESIDENTS_ALL_FIELDS                                                                                         \
    (DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR | DATE_TIME_MINUTE | DATE_TIME_SECOND)
#define VILLAGER_RESIDENTS_NONE (-1)

extern u8 data_021ee418[];            /* the record exchanged with other consoles */
extern const NpcIdHead data_021dc7aa; /* this town (number and name) */
/* A villager (0x7ec bytes) in which a newcomer is put together before it moves in. */
extern u8 data_021d1554[VILLAGER_TOWN_VILLAGER_SIZE];
/* The candidates of VillagerResidents_PickOfPersonality, a set of villager numbers. */
extern u32 data_021d12c8[VILLAGER_RESIDENTS_NUMBER_WORDS];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern NpcId *func_0208150c(const void *villager);     /* the villager's NpcId, at 0x7a0 */
extern NpcIdHead *func_020800fc(const void *villager); /* the town it last lived in, at 0x7b8 */
extern int func_02064294(const NpcIdHead *head);       /* whether the head is set */
extern void func_020642d0(NpcIdHead *dst, const NpcIdHead *src);
extern u8 *func_020900d8(u8 *record);                                       /* the record's villager, at 0x14c */
extern int func_0207cf74(u32 index);                                        /* whether the index is 0-7 */
extern unsigned int func_020644cc(int bound);                               /* a random number below `bound` */
extern void func_0209e474(DateTime *now);                                   /* the clock's date and time */
extern void func_0209df64(Date *today);                                     /* the clock's date */
extern int func_0209e3ac(const DateTime *a, const DateTime *b, int fields); /* DateTime_Compare */
extern int func_0209e380(const DateTime *from, const DateTime *to);         /* DateTime_DaysBetween */
extern int func_0209dffc(const DateTime *when);                             /* 1 when it is not a valid date and time */
/* The villager's record (at 0x734) and its object: the object's first 8 bytes are a date and
 * time, its byte 0x10 its mode. */
extern u8 *func_0207f1c8(const void *villager);
extern u8 *func_0209b5ec(u8 *object);
extern const DateTime *func_0209bfec(u8 *object);
extern int func_0207f0c0(const void *villager); /* a villager whose object is in mode 11 */
extern int func_0207f120(const void *villager); /* a villager whose object is in mode 9 */
/* 1 unless one of the four players' records holds the villager (func_0207ef54). */
extern int func_0207dca8(const void *villager);
/* Mode 10, with `now`, given to the villager's object, and the object at 0x24 of its record
 * cleared. */
extern void func_0207dbe8(u8 *villager, const DateTime *now);
extern void func_0207ef3c(u8 *villager, u8 came); /* its byte 0x7d6 */
extern void func_02080078(u8 *villager);          /* a free plot (0x500a) put on its house's tile */
extern void func_020800ec(u8 *villager);          /* its house's tile (0x7ce) set to none */
/* For each player of the town, func_02080dc0 with the villager. */
extern void func_02080d70(u8 *villager);
/* 1 when the villager held for the exchange stays rather than `villager` going there in its
 * place. */
extern int func_02080330(const u8 *held, const u8 *villager, const DateTime *now);
extern void func_02081660(u8 *villager);                                 /* a place emptied (a villager reset) */
extern void func_0208164c(u8 *dst, const u8 *src);                       /* a villager copied */
extern void func_02081518(u8 *villager, u32 number, int a, int b, u8 c); /* a villager of that number */
extern const u8 *func_02082500(u8 number); /* the villager's data (data_020cd884), NULL past 149 */

static int is_set(const DateTime *when)
{
    const u8 *bytes = (const u8 *) when;
    for (size_t i = 0; i < sizeof(DateTime); i++) {
        if (bytes[i] != 0) {
            return 1;
        }
    }
    return 0;
}

/* The numbers of the villagers that have lived in the town, at 0x4060. */
static u32 *met_numbers(VillagerTown *town)
{
    return (u32 *) (void *) town->unknown_4060;
}

/* The number of the villager that last left, at 0x4074. */
static s8 *gone_number(VillagerTown *town)
{
    return (s8 *) &town->unknown_4060[0x14];
}

static int same_town(const NpcIdHead *a, const NpcIdHead *b)
{
    return a->id == b->id && memcmp(a->data, b->data, sizeof(a->data)) == 0;
}

static int bit_set(unsigned int mask, int bit)
{
    return (mask >> bit) & 1;
}

/* ---- Sets of villager numbers */

/* func_0207ca48: `number` taken out of the set, when it is a villager's number. */
void VillagerResidents_RemoveNumber(VillagerTown *town, u32 *set, int number)
{
    (void) town;
    if (Npc_IsValidNumber((u32) number)) {
        set[number >> 5] &= ~(1u << (number & 31));
    }
}
CLEAN_AS(func_0207ca48, VillagerResidents_RemoveNumber)

/* func_0207ca74: `number` put in the set, when it is a villager's number. */
void VillagerResidents_AddNumber(u32 *set, int number)
{
    if (Npc_IsValidNumber((u32) number)) {
        set[number >> 5] |= 1u << (number & 31);
    }
}
CLEAN_AS(func_0207ca74, VillagerResidents_AddNumber)

/* func_0207caa0: whether `number` is a villager's number in the set. */
int VillagerResidents_HasNumber(int number, const u32 *set)
{
    if (!Npc_IsValidNumber((u32) number)) {
        return 0;
    }
    return (set[number >> 5] >> (number & 31)) & 1;
}
CLEAN_AS(func_0207caa0, VillagerResidents_HasNumber)

/* func_0207ca08: whether every villager that can come (byte 0x4b of its data below 2) is in
 * `met`. */
int VillagerResidents_AllMet(const u32 *met)
{
    for (int i = 0; i < NPC_COUNT; i++) {
        const u8 *data = func_02082500((u8) i);
        if (data != NULL && data[VILLAGER_RESIDENTS_DATA_COMES] < VILLAGER_RESIDENTS_COMES_NEVER &&
            VillagerResidents_HasNumber((u8) i, met) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0207ca08, VillagerResidents_AllMet)

/* func_0207c9b8: once every villager that can come has been met, `met` starts again from the
 * villagers living in the town. */
void VillagerResidents_RefreshMet(u32 *met, VillagerTown *town)
{
    if (!VillagerResidents_AllMet(met)) {
        return;
    }
    MI_CpuFill8(met, 0, VILLAGER_RESIDENTS_NUMBER_WORDS * sizeof(u32));
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const NpcId *npc = func_0208150c(town->villagers[i]);
        if (NpcId_IsValid(npc)) {
            VillagerResidents_AddNumber(met, NpcId_Number(npc));
        }
    }
}
CLEAN_AS(func_0207c9b8, VillagerResidents_RefreshMet)

/* ---- Choosing who comes */

/* func_0207c818: the personality (0-5) fewest of the town's villagers have, leaving out the
 * personalities whose bits are set in `excluded`; a draw among those that tie.
 * QUIRK: with all six left out it gives 0. */
int VillagerResidents_PickPersonality(VillagerTown *town, int excluded)
{
    u8 counts[PERSONALITY_COUNT];
    MI_CpuFill8(counts, 0, sizeof(counts));
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const NpcId *npc = func_0208150c(town->villagers[i]);
        if (NpcId_IsValid(npc) && (unsigned int) NpcId_Personality(npc) < PERSONALITY_COUNT) {
            counts[NpcId_Personality(npc)]++;
        }
    }

    u8 fewest = 0;
    int tied = 0;
    int lowest = VILLAGER_RESIDENTS_COUNT_START;
    for (int p = 0; p < PERSONALITY_COUNT; p++) {
        if (bit_set((unsigned int) excluded, p)) {
            continue;
        }
        if (counts[p] < lowest) {
            fewest = (u8) (1u << p);
            tied = 1;
            lowest = counts[p];
        } else if (counts[p] == lowest) {
            fewest |= (u8) (1u << p);
            tied++;
        }
    }
    int picked = VillagerRoster_PickBit(fewest, tied, PERSONALITY_COUNT);
    if ((unsigned int) picked < PERSONALITY_COUNT) {
        return (u8) picked;
    }
    return 0;
}
CLEAN_AS(func_0207c818, VillagerResidents_PickPersonality)

/* func_0207c8c8: a random villager number of personality `personality` that has not been met
 * and does not live in the town, among those that can come (with `first_villagers`, only those
 * whose byte 0x4b is 0); -1 for none. The candidates are kept in data_021d12c8. */
int VillagerResidents_PickOfPersonality(VillagerTown *town, int personality, int first_villagers)
{
    u32 *candidates = data_021d12c8;
    u32 *met = met_numbers(town);
    int count = 0;
    MI_CpuFill8(candidates, 0, VILLAGER_RESIDENTS_NUMBER_WORDS * sizeof(u32));

    for (int i = 0; i < NPC_COUNT; i++) {
        if (VillagerResidents_HasNumber((u8) i, met)) {
            continue;
        }
        const u8 *data = func_02082500((u8) i);
        u8 comes = data[VILLAGER_RESIDENTS_DATA_COMES];
        if (comes >= VILLAGER_RESIDENTS_COMES_NEVER) {
            continue;
        }
        if (first_villagers != 0 && comes != VILLAGER_RESIDENTS_COMES_ALWAYS) {
            continue;
        }
        if (data[VILLAGER_RESIDENTS_DATA_PERSONALITY] == personality) {
            VillagerResidents_AddNumber(candidates, (u8) i);
            count++;
        }
    }

    /* The villagers living in the town are taken out. */
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS && count > 0; i++) {
        const NpcId *npc = func_0208150c(town->villagers[i]);
        if (!NpcId_IsValid(npc)) {
            continue;
        }
        u8 number = (u8) NpcId_Number(npc);
        if (VillagerResidents_HasNumber(number, candidates)) {
            VillagerResidents_RemoveNumber(town, candidates, number);
            count--;
        }
    }

    if (count > 0) {
        int nth = (int) func_020644cc(count);
        for (int i = 0; i < NPC_COUNT; i++) {
            if (VillagerResidents_HasNumber((u8) i, candidates)) {
                if (nth == 0) {
                    return i;
                }
                nth--;
            }
        }
    }
    return VILLAGER_RESIDENTS_NONE;
}
CLEAN_AS(func_0207c8c8, VillagerResidents_PickOfPersonality)

/* func_0207c598: the number of a new villager: of the personality fewest have, else of the
 * next fewest, up to all six; -1 for none. */
int VillagerResidents_PickNumber(VillagerTown *town)
{
    u8 excluded = 0;
    for (int i = 0; i < PERSONALITY_COUNT; i++) {
        unsigned int personality = (unsigned int) VillagerResidents_PickPersonality(town, excluded);
        if (personality >= PERSONALITY_COUNT) {
            break;
        }
        int number = VillagerResidents_PickOfPersonality(town, (int) personality, 0);
        if (number != VILLAGER_RESIDENTS_NONE) {
            return number;
        }
        excluded = (u8) (excluded | (1u << personality));
    }
    return VILLAGER_RESIDENTS_NONE;
}
CLEAN_AS(func_0207c598, VillagerResidents_PickNumber)

/* ---- Leaving */

/* func_0207c0c0: the place of the first villager whose object is in mode 11, or -1. */
int VillagerResidents_FindMode11(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (func_0207f0c0(town->villagers[i])) {
            return i;
        }
    }
    return VILLAGER_RESIDENTS_NONE;
}
CLEAN_AS(func_0207c0c0, VillagerResidents_FindMode11)

/* func_0207c160: the place of the first villager about to leave (mode 9), or -1. */
int VillagerResidents_FindLeaving(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (func_0207f120(town->villagers[i])) {
            return i;
        }
    }
    return VILLAGER_RESIDENTS_NONE;
}
CLEAN_AS(func_0207c160, VillagerResidents_FindLeaving)

/* func_0207c048: whether a villager is to be picked to leave: the town has all eight, none is
 * leaving or in mode 11, and `now` is a day or more after the latest time seen; always from
 * the fourth day, else by a draw of one in (4 - days). */
int VillagerResidents_IsLeaveDue(VillagerTown *town, const DateTime *now)
{
    if (VillagerRoster_Count(town) != VILLAGER_TOWN_VILLAGERS) {
        return 0;
    }
    int leaving = VillagerResidents_FindLeaving(town);
    int mode11 = VillagerResidents_FindMode11(town);
    if (leaving != VILLAGER_RESIDENTS_NONE || mode11 != VILLAGER_RESIDENTS_NONE) {
        return 0;
    }
    if (func_0209e3ac(now, &town->latest, VILLAGER_RESIDENTS_ALL_FIELDS) != 1) {
        return 0;
    }
    int days = func_0209e380(&town->latest, now);
    if (days <= 0) {
        return 0;
    }
    if (days >= VILLAGER_RESIDENTS_LEAVE_DAYS) {
        return 1;
    }
    return func_020644cc(VILLAGER_RESIDENTS_LEAVE_DAYS - days) == 0;
}
CLEAN_AS(func_0207c048, VillagerResidents_IsLeaveDue)

/* func_0207bfdc: a random villager to leave, or -1: one that is not the last to move in nor
 * the one planning to move away (villager_move.h), and that no player's record holds
 * (func_0207dca8). */
int VillagerResidents_PickLeaver(VillagerTown *town)
{
    int moving = VillagerMove_VillagerIndex(town);
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (i == town->index_4075 || i == moving) {
            continue;
        }
        if (!NpcId_IsValid(func_0208150c(villager)) || func_0207dca8(villager) == 0) {
            continue;
        }
        candidates |= (u8) (1u << i);
        count++;
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207bfdc, VillagerResidents_PickLeaver)

/* func_0207c0f0: the place of the villager about to leave once its date (that of its object)
 * is two days or more from `now`, else -1.
 * QUIRK: the days are counted either way, so a date two days or more after `now` (the clock set
 * back) counts too. */
int VillagerResidents_ReadyLeaver(VillagerTown *town, const DateTime *now)
{
    int index = VillagerResidents_FindLeaving(town);
    u8 *villager = VillagerRoster_At(town, index);
    if (villager == NULL) {
        return VILLAGER_RESIDENTS_NONE;
    }
    u8 *object = func_0209b5ec(func_0207f1c8(villager));
    int order = func_0209e3ac(now, func_0209bfec(object), VILLAGER_RESIDENTS_ALL_FIELDS);
    int days = 0;
    if (order == 1) {
        days = func_0209e380(func_0209bfec(object), now);
    } else if (order == -1) {
        days = func_0209e380(now, func_0209bfec(object));
    }
    if (days < VILLAGER_RESIDENTS_LEAVER_DAYS) {
        return VILLAGER_RESIDENTS_NONE;
    }
    return index;
}
CLEAN_AS(func_0207c0f0, VillagerResidents_ReadyLeaver)

/* func_0207c330: villager `index` leaves the town: a free plot where its house stood, this town
 * as the one it last lived in, its number kept as the one gone; it leaves the walkers and the
 * bonds, is copied into `hold` when there is one, and its place is emptied. The time it left
 * is `now`. */
void VillagerResidents_MoveOut(VillagerTown *town, u8 *hold, u8 *villager, int index, const DateTime *now)
{
    func_02080078(villager);
    func_020800ec(villager);
    func_020642d0(func_020800fc(villager), &data_021dc7aa);
    *gone_number(town) = (s8) NpcId_Number(func_0208150c(villager));
    VillagerOutdoors_Remove(&town->outdoors, index);
    VillagerBond_ForgetVillager(town->bonds, index);
    if (hold != NULL) {
        func_0208164c(hold, villager);
    }
    func_02081660(villager);
    MI_CpuCopy8(now, &town->time_4058, sizeof(DateTime));
}
CLEAN_AS(func_0207c330, VillagerResidents_MoveOut)

/* func_0207c3b0: `newcomer` moves into place `index` (`place`): the villagers' objects checked
 * first (VillagerTown_CheckObjects); it is copied there, its object put in mode 10 with `now`,
 * no house tile yet, `came` kept at its 0x7d6 and its items marked; it joins the walkers'
 * order with no bonds, and its number is met. `now` becomes the latest time seen (and the time
 * a villager left, when one has), and the place the newcomer's. */
void VillagerResidents_MoveIn(VillagerTown *town, u8 *place, int index, const u8 *newcomer, unsigned char came,
                              const DateTime *now)
{
    VillagerTown_CheckObjects(town);
    func_0208164c(place, newcomer);
    func_0207dbe8(place, now);
    func_020800ec(place);
    func_0207ef3c(place, came);
    VillagerEntry_MarkItems(place);
    VillagerOutdoors_AddToOrder(&town->outdoors, index);
    VillagerBond_ForgetVillager(town->bonds, index);
    VillagerResidents_AddNumber(met_numbers(town), NpcId_Number(func_0208150c(place)));
    MI_CpuCopy8(now, &town->latest, sizeof(DateTime));
    if (is_set(&town->time_4058)) {
        MI_CpuCopy8(now, &town->time_4058, sizeof(DateTime));
    }
    VillagerResidents_SetNewcomer(town, (u8) index);
}
CLEAN_AS(func_0207c3b0, VillagerResidents_MoveIn)

/* The leaver, if any, goes into the hold unless the held villager stays (func_02080330); when
 * it stays, the leaver just goes. */
static void leave_by_hold(VillagerTown *town, u8 *held, u8 *leaver, int index, const DateTime *now)
{
    if (leaver == NULL) {
        return;
    }
    func_02080d70(leaver);
    if (func_02080330(held, leaver, now) == 0) {
        VillagerResidents_MoveOut(town, held, leaver, index, now);
    } else {
        VillagerResidents_MoveOut(town, NULL, leaver, index, now);
    }
}

/* func_0207c190: the exchange of villagers with other towns through the villager held at
 * 0x14c of data_021ee418.
 *   - Nothing held (or held without a town): the leaver, if ready, goes into the hold.
 *   - Held from this town, or a villager the town has or last saw leave: the leaver, if ready,
 *     goes into the hold or just goes (leave_by_hold).
 *   - Held from another town: it moves into the leaver's place (the leaver going into the hold)
 *     or, without a leaver, into the first free place, and the hold is emptied. */
void VillagerResidents_Exchange(VillagerTown *town, const DateTime *now)
{
    u8 *held = VillagerCopy_Villager(func_020900d8(data_021ee418));
    int index = VillagerResidents_ReadyLeaver(town, now);
    u8 *leaver = VillagerRoster_At(town, index);

    if (!NpcId_IsValid(func_0208150c(held)) || func_02064294(func_020800fc(held)) == 0) {
        if (leaver != NULL) {
            func_02080d70(leaver);
            VillagerResidents_MoveOut(town, held, leaver, index, now);
        }
        return;
    }
    if (same_town(func_020800fc(held), &data_021dc7aa) ||
        VillagerRoster_FindNumber(town, NpcId_Number(func_0208150c(held))) != NULL ||
        *gone_number(town) == NpcId_Number(func_0208150c(held))) {
        leave_by_hold(town, held, leaver, index, now);
        return;
    }
    if (leaver != NULL) {
        func_02081660(data_021d1554);
        func_0208164c(data_021d1554, held);
        func_02080d70(leaver);
        VillagerResidents_MoveOut(town, held, leaver, index, now);
        VillagerResidents_MoveIn(town, leaver, index, data_021d1554, VILLAGER_RESIDENTS_CAME_EXCHANGED, now);
        return;
    }
    int free = VillagerRoster_FirstFree(town);
    if (!func_0207cf74((u32) free)) {
        return;
    }
    VillagerResidents_MoveIn(town, VillagerRoster_At(town, free), free, held, VILLAGER_RESIDENTS_CAME_EXCHANGED, now);
    func_02081660(held);
}
CLEAN_AS(func_0207c190, VillagerResidents_Exchange)

/* ---- Arriving */

/* func_0207c5e4: whether a new villager is to come: the town has a free place, and either no
 * villager has left yet and the latest time seen is unset, not valid, or a day or more before
 * `now`; or one has, and `now` is a day or more after: always from the eighth day, else by a
 * draw of one in (8 - days). */
int VillagerResidents_IsArrivalDue(VillagerTown *town, const DateTime *now)
{
    if (VillagerRoster_Count(town) >= VILLAGER_TOWN_VILLAGERS) {
        return 0;
    }
    if (!is_set(&town->time_4058)) {
        if (!is_set(&town->latest) || func_0209dffc(&town->latest) != 0) {
            return 1;
        }
        return func_0209e3ac(now, &town->latest, VILLAGER_RESIDENTS_ALL_FIELDS) == 1 && func_0209e380(&town->latest, now) >= 1;
    }
    if (func_0209e3ac(now, &town->time_4058, VILLAGER_RESIDENTS_ALL_FIELDS) != 1) {
        return 0;
    }
    int days = func_0209e380(&town->time_4058, now);
    if (days <= 0) {
        return 0;
    }
    if (days >= VILLAGER_RESIDENTS_ARRIVE_DAYS) {
        return 1;
    }
    return func_020644cc(VILLAGER_RESIDENTS_ARRIVE_DAYS - days) == 0;
}
CLEAN_AS(func_0207c5e4, VillagerResidents_IsArrivalDue)

/* func_0207c4e8: when a new villager is due, the first free place is emptied and a villager
 * drawn for it (VillagerResidents_PickNumber, after the villagers met start again if all have
 * been) moves in; `now` then becomes the latest time seen, and the time a villager left when one
 * has. */
void VillagerResidents_MoveInNew(VillagerTown *town, const DateTime *now)
{
    if (!VillagerResidents_IsArrivalDue(town, now)) {
        return;
    }
    int index = VillagerRoster_FirstFree(town);
    u8 *place = VillagerRoster_At(town, index);
    if (place != NULL) {
        func_02081660(place);
        VillagerResidents_RefreshMet(met_numbers(town), town);
        int number = VillagerResidents_PickNumber(town);
        if (number != VILLAGER_RESIDENTS_NONE) {
            func_02081660(data_021d1554);
            func_02081518(data_021d1554, (u8) number, 1, 0, 0);
            VillagerResidents_MoveIn(town, place, index, data_021d1554, VILLAGER_RESIDENTS_CAME_NEW, now);
        }
    }
    MI_CpuCopy8(now, &town->latest, sizeof(DateTime));
    if (is_set(&town->time_4058)) {
        MI_CpuCopy8(now, &town->time_4058, sizeof(DateTime));
    }
}
CLEAN_AS(func_0207c4e8, VillagerResidents_MoveInNew)

/* func_0207c460: the villager `npc` names, when it lives in the town, made the last to move in. */
void VillagerResidents_SetNewcomerNpc(VillagerTown *town, const NpcId *npc)
{
    if (!NpcId_IsValid(npc)) {
        return;
    }
    int index = VillagerRoster_IndexOf(town, npc);
    if (func_0207cf74((u32) index)) {
        VillagerResidents_SetNewcomer(town, (u8) index);
    }
}
CLEAN_AS(func_0207c460, VillagerResidents_SetNewcomerNpc)

/* func_0207c498: the place of the last villager to move in set. */
VillagerTown *VillagerResidents_SetNewcomer(VillagerTown *town, unsigned char index)
{
    town->index_4075 = (s8) index;
    return town;
}
CLEAN_AS(func_0207c498, VillagerResidents_SetNewcomer)

/* func_0207c76c: a new town: the block reset, then three villagers drawn for places 0-2, each
 * of the personality fewest have among those not given yet, and among the villagers whose
 * byte 0x4b is 0; a place whose draw finds none stays empty. The clock's time becomes the latest seen, the walkers' order is made, today is the
 * day the per-day update last ran, and no villager is picked to move away. */
void VillagerResidents_StartTown(VillagerTown *town)
{
    u8 excluded = 0;
    VillagerRoster_Init(town);
    for (int i = 0; i < VILLAGER_RESIDENTS_FIRST_VILLAGERS; i++) {
        unsigned int personality = (unsigned int) VillagerResidents_PickPersonality(town, excluded);
        if (personality >= PERSONALITY_COUNT) {
            continue;
        }
        int number = VillagerResidents_PickOfPersonality(town, (int) personality, 1);
        if (number == VILLAGER_RESIDENTS_NONE) {
            continue;
        }
        func_02081518(town->villagers[i], (u8) number, 0, 0, 1);
        VillagerResidents_AddNumber(met_numbers(town), (u8) number);
        excluded = (u8) (excluded | (1u << personality));
    }
    func_0209e474(&town->latest);
    VillagerOutdoors_ListResidents(&town->outdoors, town->villagers[0]);
    func_0209df64(&town->last_day);
    town->move_index = VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207c76c, VillagerResidents_StartTown)
