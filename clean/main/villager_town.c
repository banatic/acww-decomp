/* The town's villagers as one block (villager_town.h). */
#include "villager_town.h"

#include "clean.h"
#include "date_time.h"
#include "design.h"
#include "session.h"
#include "villager_bonds.h"

static_assert(offsetof(VillagerTown, bonds) == 0x3f60, "bonds");
static_assert(offsetof(VillagerTown, outdoors) == 0x3f7c, "outdoors");
static_assert(offsetof(VillagerTown, move) == 0x3f90, "move");
static_assert(offsetof(VillagerTown, date_404c) == 0x404c, "date 0x404c");
static_assert(offsetof(VillagerTown, latest) == 0x4050, "latest");
static_assert(offsetof(VillagerTown, time_4058) == 0x4058, "time 0x4058");
static_assert(offsetof(VillagerTown, index_4075) == 0x4075, "index 0x4075");
static_assert(offsetof(VillagerTown, move_index) == 0x4076, "move index");
static_assert(offsetof(VillagerTown, mark) == 0x4078, "mark");
static_assert(offsetof(VillagerTown, last_day) == 0x407a, "last day");
static_assert(sizeof(VillagerTownEvent) == 12, "event");

/* The hour from which the day's events count. */
#define VILLAGER_TOWN_EVENT_HOUR 6
/* The pockets' list of a player's record, and its first free place (-1: full). */
#define VILLAGER_TOWN_POCKETS_FULL (-1)
/* The state func_0207f150 gives a villager that lives in the town as usual. */
#define VILLAGER_TOWN_RESIDENT 3
/* The days within which VillagerTown_IsFarFromDate404C gives 0. */
#define VILLAGER_TOWN_DATE_404C_DAYS 14
/* The item a villager takes when it takes a design from the shop. */
#define VILLAGER_TOWN_DESIGN_ITEM 0x12a8
/* What func_0209c020 and func_0207d788 give for nothing to do. */
#define VILLAGER_TOWN_OBJECT_NONE 12
/* The type of object VillagerTown_ExpirePlayerObjects looks at, and the type it sets. */
#define VILLAGER_TOWN_PLAYER_OBJECT 0x15
#define VILLAGER_TOWN_PLAYER_OBJECT_DONE 4
/* The lowest score VillagerTown_ClosestCompanion starts from. */
#define VILLAGER_TOWN_NO_SCORE (-100000)

extern NetSession *data_020ccf94; /* the game's session */
extern u8 data_021dc7bc[];        /* the four players' records (0x249c bytes each) */
extern const u32 data_020cd524[VILLAGER_TOWN_EVENTS];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern NpcId *func_0208150c(const void *villager);                    /* the villager's NpcId, at 0x7a0 */
extern int func_0207f150(const void *villager);                       /* 0-3, from three tests of the villager */
extern VillagerState *func_0207f270(const void *villager);            /* its entry of the state table */
extern u8 *func_0207f1c8(const void *villager);                       /* the villager's record, at 0x734 */
extern u8 *func_0207cec0(VillagerTown *town, int villager);           /* villager `villager`, or NULL past 7 */
extern int func_0207cf14(const VillagerTown *town, const NpcId *npc); /* the villager it names, or -1 */
extern u8 *func_0207ce98(VillagerTown *town, const NpcId *npc);       /* the villager it names, or NULL */
extern int func_0207cf74(u32 index);                                  /* whether the index is 0-7 */
/* A random one of the `count` bits set in `candidates` (of `bits`), or -1 for none. */
extern int func_0207cc54(u32 candidates, int count, int bits);
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */
/* The villager's memory of the player (0x80 bytes), or NULL when it does not know the player. */
extern u8 *func_020807a8(const void *villager, const void *player);
extern int func_02081d20(const u8 *memory); /* how fond the villager is (signed byte 0x6c) */
extern int func_02081898(const u8 *memory); /* bit 14 of its halfword 0x7c */
extern void func_02081888(u8 *memory);      /* sets bit 5 of its halfword 0x7c */
/* Whether the villager is one a companion can be picked from (func_02080928). */
extern int func_02080928(const void *villager);
extern void *func_020984e8(void);                    /* the current player's record, or NULL */
extern void *func_02098844(u8 *players, int player); /* a player's record; NULL past 3 */
extern void *func_02098868(u8 *players, void *id);   /* the town's player of that id, or NULL */
extern u8 *func_02099870(void *record);              /* the player's id (name and town), at 0x247e */
extern u8 *func_02099640(void *record);              /* the record's part at 0x1e40 */
extern u8 *func_02099734(void *record);              /* the record's pockets, at 0x11a8 */
extern u8 *func_020992e4(void *record);              /* a date of the record (day, month), at 0x2414 */
extern u8 func_020992ac(void *record);               /* the year it was last celebrated, at 0x2453 */
extern u8 func_02099174(void *record, u32 villager); /* its byte 0x2454 + villager; 0xff past 7 */
extern void func_02099164(void *record, u32 villager, u8 value);
extern int func_02099020(void *record, u32 bit);    /* a bit of the record's flags */
extern int func_02098eb8(u8 *pockets);              /* the first free place of the pockets, or -1 */
extern int func_020951bc(const void *player);       /* whether the player id is set */
extern void *func_02065f7c(MailLetter *letter);     /* the letter's sender, a player id at 0x24 */
extern void *func_02065f64(MailLetter *letter);     /* the villager it is addressed to, or NULL */
extern void *func_0209527c(void *id, void *player); /* a player id constructed from another */
extern int func_0209526c(void *id);                 /* a player id's destructor */
extern int func_0209a9a8(u8 *part, MailLetter *letter);
extern void func_02081144(u8 *villager, void *player, MailLetter *letter);
extern int func_02081418(u8 *villager, MailLetter *letter);
extern int func_020b65c4(void);                                             /* the current scene */
extern void func_0209e474(DateTime *now);                                   /* the clock's date and time */
extern void func_0209e29c(DateTime *when, int days);                        /* DateTime_AddDays */
extern int func_0209e3ac(const DateTime *a, const DateTime *b, int fields); /* DateTime_Compare */
extern int func_0209e380(const void *from, const DateTime *to);             /* DateTime_DaysBetween */
extern void func_0209df64(Date *today);                                     /* Calendar_Today */
extern void func_0209dfd8(DateTime *dst, const Date *date, u8 hour, u8 minute, u8 second);
extern int func_0209dd9c(const Date *date, const Date *other);       /* Calendar_IsOnOrAfter */
extern int func_0209dcdc(const Date *date, const Date *origin);      /* Calendar_DaysFrom */
extern int func_0203fea0(VillagerTownEvent *events, DateTime *when); /* the date's events */
extern int func_0203fc78(u32 event, DateTime *when, int arg);        /* whether the event is on */
extern u32 func_02041608(void);                                      /* the event going on (data_020db6e0) */
extern void func_0205ba64(void *search);
extern void func_0205ba60(void *search);
extern u32 func_0205b868(void *search, int villager, u16 *found, int *a, int *b, int *c);
extern int func_0205a1dc(void *player, const NpcId *npc);
extern int func_02080998(const void *villager, int n, const DateTime *now);
extern void func_02080cd8(u8 *villager, const u16 *item); /* the villager's halfword 0x7d2 */
extern void func_0207d5bc(u8 *villager);                  /* clears bit 6 of halfword 0x7c of its eight memories */
extern void func_0207d148(u8 *villager);                  /* halves byte 0x1e of its state entry */
extern void func_0207d128(u8 *villager);                  /* doubles it (VillagerState_DoubleByte1E) */
extern void func_0207d2b4(u8 *villager, void *record);    /* sets it from the villager's fondness */
extern void func_0207d71c(u8 *villager);
extern void func_0207f454(u8 *villager);
extern void func_0207f5e4(u8 *villager);
extern int func_0207d840(u8 *villager, const DateTime *now);
extern void func_0207d978(u8 *villager, const DateTime *now);
extern void func_0207d91c(u8 *villager, const DateTime *now);
extern int func_0207d788(u8 *villager, DateTime *latest, DateTime *second, const DateTime *now);
extern void func_0207dc30(u8 *villager, const DateTime *now);
extern int func_0207c048(VillagerTown *town, const DateTime *now);
extern int func_0207bfdc(VillagerTown *town);
extern void func_0207c190(VillagerTown *town, const DateTime *now);
extern void func_0207c4e8(VillagerTown *town, const DateTime *now);
extern void func_0207f414(u8 *villager, int result, int flag);
extern u8 *func_0209b5e8(u8 *record);             /* record + 0x24: the villager's object */
extern u8 *func_0209b5ec(u8 *object);             /* the object itself */
extern u8 *func_0209b91c(u8 *object);             /* the object itself */
extern u8 *func_0209b908(u8 *object);             /* object + 12 */
extern u8 *func_0209bc20(u8 *object);             /* the object itself */
extern int func_0209bd44(const u8 *object);       /* whether it holds something (its type, byte 0x0a) */
extern int func_0209bc40(const u8 *object);       /* its type, byte 0x0a */
extern int func_0209bba0(const u8 *object);       /* the low five bits of its byte 0x0b */
extern void func_0209bb90(u8 *object, int value); /* sets them */
extern int func_0209c2c0(const u8 *object);       /* bit 0 of its byte 0x21 */
extern int func_0209c020(u8 *object, const DateTime *when);
extern void func_0209baf4(u8 *object);
extern void func_02095238(u8 *id); /* a player id emptied */
extern void func_0209af04(u8 *part);
extern int func_02059e1c(int kind, u8 *player, u8 *part);
extern void func_0209a77c(VillagerMove *move); /* the record cleared: no plan */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(func_0208150c(villager));
}

static int is_resident(const u8 *villager)
{
    return func_0207f150(villager) == VILLAGER_TOWN_RESIDENT;
}

/* Bit `index` of a villager mask (index 0-7). */
static u8 bit_of(int index)
{
    return (u8) (1u << index);
}

/* ---- The marked villager */

/* func_0207a44c: bit 6 of the flags of every memory of every villager cleared. */
void VillagerTown_ClearMemoryFlags(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            func_0207d5bc(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207a44c, VillagerTown_ClearMemoryFlags)

/* func_0207a47c: whether a villager is marked and it is the one `npc` names. */
int VillagerTown_IsMarked(VillagerTown *town, const NpcId *npc)
{
    if ((town->mark & VILLAGER_TOWN_MARKED) == 0) {
        return 0;
    }
    int villager = func_0207cf14(town, npc);
    if (!func_0207cf74((u32) villager)) {
        return 0;
    }
    return ((town->mark & VILLAGER_TOWN_MARK_INDEX) >> VILLAGER_TOWN_MARK_SHIFT) == villager;
}
CLEAN_AS(func_0207a47c, VillagerTown_IsMarked)

/* func_0207a4c0: the villager `npc` names marked, when it is one of the town's. */
void VillagerTown_Mark(VillagerTown *town, const NpcId *npc)
{
    int villager = func_0207cf14(town, npc);
    if (func_0207cf74((u32) villager)) {
        town->mark = (u16) (((town->mark | VILLAGER_TOWN_MARKED) & ~VILLAGER_TOWN_MARK_INDEX) |
                            ((villager & 7) << VILLAGER_TOWN_MARK_SHIFT));
    }
}
CLEAN_AS(func_0207a4c0, VillagerTown_Mark)

/* func_0207a500: no villager marked. */
void VillagerTown_ClearMark(VillagerTown *town)
{
    town->mark &= (u16) ~(VILLAGER_TOWN_MARKED | VILLAGER_TOWN_MARK_INDEX);
}
CLEAN_AS(func_0207a500, VillagerTown_ClearMark)

/* ---- Letters and players */

/* A player id as func_0209527c constructs it (0x20 bytes). */
typedef struct VillagerTownPlayerId {
    u8 bytes[0x20];
} VillagerTownPlayerId;

/* func_0207a51c: a letter handed to the villager it is addressed to. When its sender is a
 * player of the town, that player's record takes note of it first (func_0209a9a8). Then the
 * villager reads it (func_02081144) and keeps it (func_02081418, whose result is given back);
 * 0 when the letter has no sender set or no villager of the town to go to. */
int VillagerTown_GiveLetter(VillagerTown *town, MailLetter *letter)
{
    if (letter == NULL) {
        return 0;
    }
    void *sender = func_02065f7c(letter);
    if (sender == NULL) {
        return 0;
    }
    VillagerTownPlayerId id;
    int result = 0;
    func_0209527c(&id, sender);
    if (func_020951bc(&id)) {
        void *player = func_02098868(data_021dc7bc, &id);
        void *addressee = func_02065f64(letter);
        if (player != NULL) {
            func_0209a9a8(func_02099640(player), letter);
        }
        if (addressee != NULL) {
            NpcId npc;
            NpcId_ConstructCopy(&npc, addressee);
            if (NpcId_IsValid(&npc)) {
                u8 *villager = func_0207ce98(town, &npc);
                if (villager != NULL) {
                    func_02081144(villager, player, letter);
                    result = func_02081418(villager, letter);
                }
            }
            NpcId_Destruct(&npc);
        }
    }
    func_0209526c(&id);
    return result;
}
CLEAN_AS(func_0207a51c, VillagerTown_GiveLetter)

/* func_0207a5d0: whether every villager of the town knows the player; 0 when the player id is
 * not set. */
int VillagerTown_AllRemember(VillagerTown *town, const void *player)
{
    if (!func_020951bc(player)) {
        return 0;
    }
    u8 *villager = func_0207cec0(town, 0);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(villager) && func_020807a8(villager, player) == NULL) {
            return 0;
        }
        villager += VILLAGER_TOWN_VILLAGER_SIZE;
    }
    return 1;
}
CLEAN_AS(func_0207a5d0, VillagerTown_AllRemember)

/* func_0207a62c: the date at 0x404c set to `date`. */
void VillagerTown_SetDate404C(VillagerTown *town, const Date *date)
{
    MI_CpuCopy8(date, &town->date_404c, sizeof(Date));
    town->date_404c.unused = 1;
}
CLEAN_AS(func_0207a62c, VillagerTown_SetDate404C)

/* func_0207a650: 0 when the date at 0x404c is set and `date` is within 13 days of it, either
 * way; otherwise 1. */
int VillagerTown_IsFarFromDate404C(VillagerTown *town, const Date *date)
{
    int far = 1;
    if (town->date_404c.unused != 0) {
        int days;
        if (func_0209dd9c(date, &town->date_404c)) {
            days = func_0209dcdc(date, &town->date_404c);
        } else {
            days = func_0209dcdc(&town->date_404c, date);
        }
        if (days < VILLAGER_TOWN_DATE_404C_DAYS) {
            far = 0;
        }
    }
    return far;
}
CLEAN_AS(func_0207a650, VillagerTown_IsFarFromDate404C)

/* func_0207a6a0: the villager that goes out first (the state table's index 0x16c) cleared;
 * then, in scene 6, on the date at 0x2414 of the player's record (read as the player's
 * birthday) from 6:00, when the record has not marked this year (its byte 0x2453), its flag 1
 * is clear and its pockets have room: the villager fondest of the player (VillagerTown_FondestOf)
 * goes out first, and the ones out are drawn again. `record` is the current player's when
 * NULL. */
void VillagerTown_PickBirthdayVisitor(VillagerTown *town, void *record)
{
    VillagerState_SetIndex16C((char) VILLAGER_TOWN_NONE);
    if (func_020b65c4() != 6) {
        return;
    }
    if (record == NULL) {
        record = func_020984e8();
    }
    if (record == NULL) {
        return;
    }
    if (func_02099020(record, 1) != 0) {
        return;
    }
    if (func_02098eb8(func_02099734(record)) == VILLAGER_TOWN_POCKETS_FULL) {
        return;
    }
    u8 *player = func_02099870(record);
    const u8 *date = func_020992e4(record);
    if ((date[0] | date[1]) == 0) {
        return;
    }
    if (!func_020951bc(player)) {
        return;
    }
    DateTime now = {0};
    func_0209e474(&now);
    if (func_020992ac(record) == now.year) {
        return;
    }
    if (date[1] != now.month || date[0] != now.day || now.hour < VILLAGER_TOWN_EVENT_HOUR) {
        return;
    }
    int villager = VillagerTown_FondestOf(town, player);
    if (func_0207cf74((u32) villager)) {
        VillagerOutdoors_ClearTime(&town->outdoors);
    }
    VillagerState_SetIndex16C((char) villager);
}
CLEAN_AS(func_0207a6a0, VillagerTown_PickBirthdayVisitor)

/* func_0207a764: a random one of the resident villagers fondest of the player, or -1 (also
 * when the player id is not set). */
int VillagerTown_FondestOf(VillagerTown *town, const void *player)
{
    if (!func_020951bc(player)) {
        return VILLAGER_TOWN_NONE;
    }
    int best = -128;
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (!has_villager(villager) || !is_resident(villager)) {
            continue;
        }
        const u8 *memory = func_020807a8(villager, player);
        if (memory == NULL) {
            continue;
        }
        int fondness = func_02081d20(memory);
        if (fondness == best) {
            candidates |= bit_of(i);
            count++;
        } else if (fondness > best) {
            best = fondness;
            candidates = bit_of(i);
            count = 1;
        }
    }
    return func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207a764, VillagerTown_FondestOf)

/* func_0207a7f8: the state table's index 0x164 set to VillagerTown_PickOutsideAcquaintance. */
void VillagerTown_PickIndex164(VillagerTown *town)
{
    VillagerState_SetIndex164((unsigned char) VillagerTown_PickOutsideAcquaintance(town));
}
CLEAN_AS(func_0207a7f8, VillagerTown_PickIndex164)

/* func_0207a810: a random one of the villagers out walking that know the current player and
 * whose memory of the player has bit 14 of its flags clear; -1 for none, or when there is no
 * current player or its id is not set. */
int VillagerTown_PickOutsideAcquaintance(VillagerTown *town)
{
    void *record = func_020984e8();
    u8 *player = record != NULL ? func_02099870(record) : NULL;
    if (player == NULL || !func_020951bc(player)) {
        return VILLAGER_TOWN_NONE;
    }
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && func_020807a8(villager, player) != NULL &&
            func_02081898(func_020807a8(villager, player)) == 0 &&
            VillagerState_LinkedByte01(func_0207f270(villager)) == VILLAGER_PLACE_OUTSIDE) {
            candidates |= bit_of(i);
            count++;
        }
    }
    return func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207a810, VillagerTown_PickOutsideAcquaintance)

/* ---- The villager of the day's event and its companion */

/* func_0207a8ac: every villager whose state is 3 settles; then, when the state table names a
 * villager of the day's event (index 0x162), that one gets state 0 and its companion (index
 * 0x163), when it is a villager, state 3. When the one at 0x162 is no villager, both indexes
 * are cleared. */
void VillagerTown_ApplyEventStates(VillagerTown *town)
{
    int event_villager = VillagerState_GetIndex162();
    int companion = VillagerState_GetIndex163();
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && VillagerState_LinkedState(func_0207f270(villager)) == 3) {
            VillagerState_SettleState(func_0207f270(villager));
        }
    }
    if (event_villager == VILLAGER_TOWN_NONE) {
        return;
    }
    u8 *villager = func_0207cec0(town, event_villager);
    if (villager != NULL && has_villager(villager)) {
        VillagerState_SetState(func_0207f270(villager), 0);
        villager = func_0207cec0(town, companion);
        if (villager != NULL && has_villager(villager)) {
            VillagerState_SetState(func_0207f270(villager), 3);
        }
    } else {
        VillagerState_SetIndex162((unsigned char) VILLAGER_TOWN_NONE);
        VillagerState_SetIndex163((unsigned char) VILLAGER_TOWN_NONE);
    }
}
CLEAN_AS(func_0207a8ac, VillagerTown_ApplyEventStates)

/* func_0207a964: the state table's indexes 0x162 and 0x163 brought up to date: the villager of
 * today's event (VillagerTown_FindEventVillager) and the one closest to it. A villager of the
 * event that is new takes a new companion, and when it is the one planning to move away, the
 * plan is dropped. For the same one, its companion is kept while func_02080928 accepts it. */
void VillagerTown_UpdateEventVillager(VillagerTown *town)
{
    DateTime now = {0};
    int previous = VillagerState_GetIndex162();
    func_0209e474(&now);
    int event_villager = VillagerTown_FindEventVillager(town, &now);
    if (event_villager == VILLAGER_TOWN_NONE) {
        VillagerState_SetIndex162((unsigned char) VILLAGER_TOWN_NONE);
        VillagerState_SetIndex163((unsigned char) VILLAGER_TOWN_NONE);
    } else if (event_villager == previous) {
        u8 *companion = func_0207cec0(town, VillagerState_GetIndex163());
        if (companion != NULL && func_02080928(companion)) {
            return;
        }
        VillagerState_SetIndex163((unsigned char) VillagerTown_ClosestCompanion(town, previous));
    } else {
        int companion = VillagerTown_ClosestCompanion(town, event_villager);
        VillagerState_SetIndex162((unsigned char) event_villager);
        VillagerState_SetIndex163((unsigned char) companion);
        if (event_villager == VillagerMove_VillagerIndex(town)) {
            func_0209a77c(&town->move);
        }
    }
}
CLEAN_AS(func_0207a964, VillagerTown_UpdateEventVillager)

/* func_0207aa08: the first resident villager whose index is the id of one of the events of
 * `when`'s date; -1 for none, before 6:00, or when there is no current player or its flag 1 is
 * set. */
int VillagerTown_FindEventVillager(const VillagerTown *town, const DateTime *when)
{
    void *record = func_020984e8();
    if (record == NULL || func_02099020(record, 1) != 0 || when->hour < VILLAGER_TOWN_EVENT_HOUR) {
        return VILLAGER_TOWN_NONE;
    }
    DateTime copy;
    VillagerTownEvent events[VILLAGER_TOWN_DAY_EVENTS];
    MI_CpuCopy8(when, &copy, sizeof(DateTime));
    int count = func_0203fea0(events, &copy);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (!has_villager(villager) || !is_resident(villager)) {
            continue;
        }
        for (int k = 0; k < count; k++) {
            if (events[k].id == i) {
                return i;
            }
        }
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207aa08, VillagerTown_FindEventVillager)

/* func_0207aa8c: a random one of the villagers func_02080928 accepts, other than `villager`,
 * that get on best with it (VillagerBond_Compatibility); -1 for none. */
int VillagerTown_ClosestCompanion(VillagerTown *town, int villager)
{
    int best = VILLAGER_TOWN_NO_SCORE;
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (i == villager || !func_02080928(town->villagers[i])) {
            continue;
        }
        int score = VillagerBond_Compatibility(town->bonds, villager, i);
        if (score > best) {
            best = score;
            candidates = bit_of(i);
            count = 1;
        } else if (score == best) {
            candidates |= bit_of(i);
            count++;
        }
    }
    return func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207aa8c, VillagerTown_ClosestCompanion)

/* func_0207ab0c: for each resident villager and each player of the town (id set, flag 1
 * clear), the player's byte for the villager (0x2454 + index): func_02080998's value for the
 * villager, written when it changed and func_0205a1dc agrees, or 0xff when it gives -1. */
void VillagerTown_UpdatePlayersVillagerBytes(VillagerTown *town)
{
    DateTime now = {0};
    func_0209e474(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        const NpcId *npc = func_0208150c(villager);
        if (!NpcId_IsValid(npc) || !is_resident(villager)) {
            continue;
        }
        for (int j = 0; j < 4; j++) {
            void *record = func_02098844(data_021dc7bc, j);
            if (record == NULL) {
                continue;
            }
            u8 *player = func_02099870(record);
            if (!func_020951bc(player) || func_02099020(record, 1) != 0) {
                continue;
            }
            int value = func_02080998(villager, 7, &now);
            if (value == -1) {
                func_02099164(record, (u32) i, 0xff);
            } else if (func_02099174(record, (u32) i) != value && func_0205a1dc(player, npc)) {
                func_02099164(record, (u32) i, (u8) value);
            }
        }
    }
}
CLEAN_AS(func_0207ab0c, VillagerTown_UpdatePlayersVillagerBytes)

/* ---- Each villager's state entry */

/* func_0207abd4: byte 0x18 and the counter of every villager's state entry cleared. */
void VillagerTown_ClearByte18AndCounters(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager)) {
            VillagerState_SetByte18(func_0207f270(villager), 0);
            VillagerState_SetCounter(func_0207f270(villager), 0);
        }
    }
}
CLEAN_AS(func_0207abd4, VillagerTown_ClearByte18AndCounters)

/* func_0207ac20: VillagerTown_Search for each villager index. */
void VillagerTown_SearchAll(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        VillagerTown_Search(town, i);
    }
}
CLEAN_AS(func_0207ac20, VillagerTown_SearchAll)

/* What func_0205ba64 sets up for func_0205b868 (0x14 bytes, no item in its two halfwords). */
typedef struct VillagerTownSearch {
    u8 bytes[0x10];
    u16 item_10;
    u16 item_12;
} VillagerTownSearch;

/* func_0207ac40: for villager `villager`, the word 0x20 and halfword 0x24 of its state entry
 * set from func_0205b868. */
void VillagerTown_Search(VillagerTown *town, int villager)
{
    u8 *found = func_0207cec0(town, villager);
    if (found == NULL || !has_villager(found)) {
        return;
    }
    int a = 5;
    int b = 0;
    int c = 0;
    u16 result = 0;
    if (!has_villager(found)) {
        return;
    }
    VillagerState *entry = func_0207f270(found);
    if (entry == NULL) {
        return;
    }
    VillagerTownSearch search;
    func_0205ba64(&search);
    entry->word_20 = func_0205b868(&search, villager, &result, &a, &b, &c);
    entry->half_24 = result;
    func_0205ba60(&search);
}
CLEAN_AS(func_0207ac40, VillagerTown_Search)

/* func_0207acbc: unless this system is linked with others, VillagerTown_FlagAcquaintance; and
 * unless it holds its slot of the session, VillagerTown_DoubleByte1E. */
void VillagerTown_UpdateAlone(VillagerTown *town, const void *player)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerTown_FlagAcquaintance(town, player);
    }
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        VillagerTown_DoubleByte1E(town);
    }
}
CLEAN_AS(func_0207acbc, VillagerTown_UpdateAlone)

/* func_0207acf8: bit 5 of the flags of one villager's memory of the player set: a random one
 * of the villagers out walking that know the player, else of the resident villagers that know
 * it, other than the one planning to move away. Nothing when the player id is not set. */
void VillagerTown_FlagAcquaintance(VillagerTown *town, const void *player)
{
    if (!func_020951bc(player)) {
        return;
    }
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && VillagerState_LinkedByte01(func_0207f270(villager)) == VILLAGER_PLACE_OUTSIDE &&
            func_020807a8(villager, player) != NULL) {
            candidates |= bit_of(i);
            count++;
        }
    }
    int chosen = func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
    if (!func_0207cf74((u32) chosen)) {
        candidates = 0;
        count = 0;
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            const u8 *villager = town->villagers[i];
            if (has_villager(villager) && is_resident(villager) && i != VillagerMove_VillagerIndex(town) &&
                func_020807a8(villager, player) != NULL) {
                candidates |= bit_of(i);
                count++;
            }
        }
        chosen = func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
    }
    u8 *villager = func_0207cec0(town, chosen);
    if (villager != NULL && has_villager(villager)) {
        u8 *memory = func_020807a8(villager, player);
        if (memory != NULL) {
            func_02081888(memory);
        }
    }
}
CLEAN_AS(func_0207acf8, VillagerTown_FlagAcquaintance)

/* func_0207adf4: unless this system holds its slot of the session, byte 0x1e of every
 * villager's state entry halved. */
void VillagerTown_HalveByte1E(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            func_0207d148(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207adf4, VillagerTown_HalveByte1E)

/* func_0207ae34: unless this system holds its slot of the session, byte 0x1e of every
 * villager's state entry doubled (up to 32). */
void VillagerTown_DoubleByte1E(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            func_0207d128(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207ae34, VillagerTown_DoubleByte1E)

/* func_0207ae74: byte 0x1e of every villager's state entry set from its fondness of the player
 * of `record` (func_0207d2b4). */
void VillagerTown_SetByte1E(VillagerTown *town, void *record)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            func_0207d2b4(town->villagers[i], record);
        }
    }
}
CLEAN_AS(func_0207ae74, VillagerTown_SetByte1E)

/* ---- The calendar's events */

/* func_0207aeac: the place in data_020cd524 of the first of its events found on the days from
 * `from` (the clock's date and time when NULL) to `days` days after it, looking day by day and
 * within a day at the events in their order; 11 for none. */
int VillagerTown_NextEvent(unsigned int days, const DateTime *from)
{
    DateTime day = {0};
    if (from == NULL) {
        func_0209e474(&day);
    } else {
        MI_CpuCopy8(from, &day, sizeof(DateTime));
    }
    for (unsigned int n = 0; n <= days; n++) {
        DateTime copy;
        VillagerTownEvent events[VILLAGER_TOWN_DAY_EVENTS];
        MI_CpuCopy8(&day, &copy, sizeof(DateTime));
        int count = func_0203fea0(events, &copy);
        for (int i = 0; i < count; i++) {
            for (int k = 0; k < VILLAGER_TOWN_EVENTS; k++) {
                if (events[i].id == data_020cd524[k]) {
                    return k;
                }
            }
        }
        func_0209e29c(&day, 1);
    }
    return VILLAGER_TOWN_EVENTS;
}
CLEAN_AS(func_0207aeac, VillagerTown_NextEvent)

/* func_0207af30: the place in data_020cd524 of the first of its events that is on now and is
 * the event going on (func_02041608); 11 for none. */
int VillagerTown_CurrentEvent(void)
{
    DateTime now = {0};
    func_0209e474(&now);
    for (int i = 0; i < VILLAGER_TOWN_EVENTS; i++) {
        u32 event = data_020cd524[i];
        DateTime copy;
        MI_CpuCopy8(&now, &copy, sizeof(DateTime));
        if (func_0203fc78(event, &copy, 0) != 0 && event == func_02041608()) {
            return i;
        }
    }
    return VILLAGER_TOWN_EVENTS;
}
CLEAN_AS(func_0207af30, VillagerTown_CurrentEvent)

/* func_0207af90: the state table's byte 0x161 set to a random one of the villagers out
 * walking, else of the resident villagers other than the one planning to move away; 0 for
 * none. */
void VillagerTown_PickIndex161(VillagerTown *town)
{
    u8 candidates = 0;
    int count = 0;
    u8 chosen = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && VillagerState_LinkedByte01(func_0207f270(villager)) == VILLAGER_PLACE_OUTSIDE) {
            candidates |= bit_of(i);
            count++;
        }
    }
    int pick = func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
    if (pick != VILLAGER_TOWN_NONE) {
        chosen = (u8) pick;
    } else {
        candidates = 0;
        count = 0;
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            const u8 *villager = town->villagers[i];
            if (has_villager(villager) && is_resident(villager) && i != VillagerMove_VillagerIndex(town)) {
                candidates |= bit_of(i);
                count++;
            }
        }
        pick = func_0207cc54(candidates, count, VILLAGER_TOWN_VILLAGERS);
        if (pick != VILLAGER_TOWN_NONE) {
            chosen = (u8) pick;
        }
    }
    VillagerState_Table()->byte_161 = chosen;
}
CLEAN_AS(func_0207af90, VillagerTown_PickIndex161)

/* ---- The updates */

/* func_0207b41c: each villager's own update. Unless `skip_designs`, a villager that takes a
 * design from the shop (Design_VillagerTakeShopDesign) gets item 0x12a8 in its halfword 0x7d2.
 * Then func_0207d71c; when the object of the villager's record holds something with the low
 * bits of its byte 0x0b clear, the player id after it (at 12) is emptied; then func_0207f454. */
void VillagerTown_UpdateVillagers(VillagerTown *town, int skip_designs)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        if (skip_designs == 0 && Design_VillagerTakeShopDesign(i, 0) != 0) {
            u16 item = VILLAGER_TOWN_DESIGN_ITEM;
            func_02080cd8(villager, &item);
        }
        func_0207d71c(villager);
        u8 *object = func_0209b5e8(func_0207f1c8(villager));
        u8 *held = func_0209b91c(object);
        if (func_0209bd44(held) && func_0209bba0(held) == 0) {
            func_02095238(func_0209b908(object));
        }
        func_0207f454(villager);
    }
}
CLEAN_AS(func_0207b41c, VillagerTown_UpdateVillagers)

/* func_0207b4a8: for each player of the town whose id is set, the object at 0xb4 of its
 * record's part at 0x1e40 (with the NpcId at 0xa4 before it), when it holds type 0x15 for a
 * valid NpcId:
 *   - with the low bits of its byte 0x0b clear: emptied (func_0209af04) when `now` is a day
 *     before its date (its bytes 3-5);
 *   - else, with no kind in the low three bits of byte 0xc8: emptied;
 *   - else: the low bits of byte 0x0b set to 4, and when the date at 0xc0 is not `now`'s day,
 *     emptied when func_02059e1c agrees.
 * `town` is not used. */
void VillagerTown_ExpirePlayerObjects(VillagerTown *town, const DateTime *now)
{
    (void) town;
    for (int i = 0; i < 4; i++) {
        void *record = func_02098844(data_021dc7bc, i);
        if (!func_020951bc(func_02099870(record))) {
            continue;
        }
        u8 *part = func_02099640(record) + 0xa4;
        u8 *object = part + 0x10;
        if (!func_0209bd44(object) || func_0209bc40(object) != VILLAGER_TOWN_PLAYER_OBJECT ||
            !NpcId_IsValid((const NpcId *) part)) {
            continue;
        }
        if (func_0209bba0(object) == 0) {
            if (func_0209e380(func_0209bc20(object), now) < 0) {
                func_0209af04(part);
            }
        } else if ((part[0x24] & 7) != 0) {
            int days = func_0209e380(part + 0x1c, now);
            func_0209bb90(object, VILLAGER_TOWN_PLAYER_OBJECT_DONE);
            if (days != 0 && func_02059e1c(part[0x24] & 7, func_02099870(record), part) != 0) {
                func_0209af04(part);
            }
        } else {
            func_0209af04(part);
        }
    }
}
CLEAN_AS(func_0207b4a8, VillagerTown_ExpirePlayerObjects)

/* func_0207b9d0: the state table's entry for villager index `index`, or NULL outside 0-7. */
VillagerState *VillagerTown_StateAt(int index)
{
    return VillagerState_At(VillagerState_Table(), index);
}
CLEAN_AS(func_0207b9d0, VillagerTown_StateAt)

/* func_0207bd80: on a new day (the date differs from the one at 0x407a), func_0207f5e4 for each
 * of the eight villager places, and the date kept. */
void VillagerTown_StartDay(VillagerTown *town)
{
    DateTime last;
    func_0209dfd8(&last, &town->last_day, 0, 0, 0);
    DateTime now = {0};
    func_0209e474(&now);
    if (func_0209e3ac(&now, &last, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) != 0) {
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            func_0207f5e4(town->villagers[i]);
        }
        func_0209df64(&town->last_day);
    }
}
CLEAN_AS(func_0207bd80, VillagerTown_StartDay)

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

/* func_0207bddc: the town's villagers brought up to date. When the clock is earlier than the
 * latest time seen, that time is moved back to it, and the time at 0x4058 too when it is set.
 * Then each part in turn; the players' bytes for the villagers only without `skip_designs`. */
void VillagerTown_Update(VillagerTown *town, int skip_designs)
{
    DateTime now = {0};
    func_0209e474(&now);
    if (func_0209e3ac(&now, &town->latest,
                      DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR | DATE_TIME_MINUTE |
                          DATE_TIME_SECOND) == -1) {
        MI_CpuCopy8(&now, &town->latest, sizeof(DateTime));
        if (is_set(&town->time_4058)) {
            MI_CpuCopy8(&now, &town->time_4058, sizeof(DateTime));
        }
    }
    VillagerTown_ExpirePlayerObjects(town, &now);
    VillagerTown_UpdateObjects(town, &now);
    func_0207c190(town, &now);
    VillagerTown_GiveObject9(town, &now);
    func_0207c4e8(town, &now);
    VillagerTown_StartDay(town);
    VillagerTown_UpdateVillagers(town, skip_designs);
    VillagerMove_Update(town);
    if (skip_designs == 0) {
        VillagerTown_UpdatePlayersVillagerBytes(town);
    }
    VillagerTown_UpdateEventVillager(town);
}
CLEAN_AS(func_0207bddc, VillagerTown_Update)

/* func_0207be8c: unless this system holds its slot of the session, func_0207d840 for every
 * villager with the clock's date and time. */
void VillagerTown_UpdateWithClock(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    DateTime now = {0};
    func_0209e474(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            func_0207d840(town->villagers[i], &now);
        }
    }
}
CLEAN_AS(func_0207be8c, VillagerTown_UpdateWithClock)

/* func_0207bee0: for every villager, the object of its record checked with no date
 * (func_0209c020); for a result other than 12, func_0207f414 with it and bit 0 of the object's
 * byte 0x21 (read before the check). */
void VillagerTown_CheckObjects(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        u8 *object = func_0209b5ec(func_0207f1c8(villager));
        int flag = func_0209c2c0(object);
        int result = func_0209c020(object, NULL);
        if (result != VILLAGER_TOWN_OBJECT_NONE) {
            func_0207f414(villager, result, flag);
        }
    }
}
CLEAN_AS(func_0207bee0, VillagerTown_CheckObjects)

/* func_0207bf38: for every villager, func_0207d978 and func_0207d91c with the time; then when
 * func_0207d788 gives other than 12, the object of its record is cleared (func_0209baf4). */
void VillagerTown_UpdateObjects(VillagerTown *town, const DateTime *now)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        func_0207d978(villager, now);
        func_0207d91c(villager, now);
        if (func_0207d788(villager, &town->latest, &town->time_4058, now) != VILLAGER_TOWN_OBJECT_NONE) {
            func_0209baf4(func_0209b5e8(func_0207f1c8(villager)));
        }
    }
}
CLEAN_AS(func_0207bf38, VillagerTown_UpdateObjects)

/* func_0207bfa4: when func_0207c048 agrees, a villager picked by func_0207bfdc, if any, gets
 * func_0207dc30 (which gives its record's object type 9). */
void VillagerTown_GiveObject9(VillagerTown *town, const DateTime *now)
{
    if (func_0207c048(town, now) == 0) {
        return;
    }
    int villager = func_0207bfdc(town);
    if (villager != VILLAGER_TOWN_NONE) {
        func_0207dc30(town->villagers[villager], now);
    }
}
CLEAN_AS(func_0207bfa4, VillagerTown_GiveObject9)
