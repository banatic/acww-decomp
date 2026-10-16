/* The players' records (player_records.h). */
#include "player_records.h"

#include "clean.h"
#include "session.h"

#define NO_ITEM 0xfff1

extern NetSession *data_020ccf94; /* the session */
extern u8 data_021dc7bc[];        /* the town's four records */
extern u8 data_021d5738[];        /* the three guest records */

/* The item each town record number gets at 0x240e when a new player is made there (items
 * 0x3884, 0x3888, 0x388c and 0x3890), built once, with the guard bit 0 of data_021d56f0, and
 * registered for destruction with the blocks below. */
extern int data_021d56f0;
extern u16 data_021d56f4[PLAYER_RECORDS_TOWN];
extern u8 data_021d572c[], data_021d5720[], data_021d5714[], data_021d5708[];
#define STARTING_ITEM_FIRST 0x3884
#define STARTING_ITEM_STEP 4

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *block);
/* An item code's destructor (nothing to do); registered, so the game's symbol. */
extern void func_020051b0(void *item);
/* A record's constructor and destructor; handed to the array helpers, so the game's symbols. */
extern void *func_02099bc8(void *record);
extern void *func_02099ad0(void *record);

extern u8 func_02096284(int player);                    /* a session player's record number */
extern int func_020988d8(u32 number);                   /* 1 for 0-3 */
extern int func_020988a4(u8 *players, int number);      /* whether that town player exists */
extern u8 *func_02098844(u8 *players, int number);      /* that town record; NULL past 3 */
extern int func_02099a28(u8 *record);                   /* whether its player exists */
extern void func_02099a38(u8 *record);                  /* clear it */
extern void *func_02099870(u8 *record);                 /* its player's name and ids (0x247e) */
extern int func_020951bc(void *name);                   /* whether that is set */
extern int func_020950d0(void *name);                   /* its player id */
extern int func_020950f8(u16 *taken, int count);        /* a new player id, none of `taken` */
extern void func_020996bc(u8 *record, const u16 *item); /* set its item at 0x240e */
/* Make a new player in the record: its name, player id and `arg`, the item at 0x2406 *item. */
extern void func_0209987c(u8 *record, const void *name, int id, int arg, int a4, u8 a5, u8 a6, u8 a7, u8 a8, u8 a9, int a10,
                          const u16 *item);

static u8 *player_records_at(u8 *records, int index)
{
    return records + index * PLAYER_RECORD_SIZE;
}

/* func_02098420: whether record `number` holds a player (0 outside 0-6). */
int PlayerRecords_Exists(int number)
{
    if (func_020988d8((u32) number) == 1) {
        return func_020988a4(data_021dc7bc, number);
    }
    if (PlayerRecords_IsGuest(number) == 1 && PlayerRecords_Guests() != NULL) {
        int index = PlayerRecords_GuestIndex(number);
        return func_02099a28(player_records_at(PlayerRecords_Guests(), index));
    }
    return 0;
}
CLEAN_AS(func_02098420, PlayerRecords_Exists)

/* func_0209847c: record `number`; NULL outside 0-6. */
u8 *PlayerRecords_Get(int number)
{
    if (func_020988d8((u32) number) == 1) {
        return func_02098844(data_021dc7bc, number);
    }
    if (PlayerRecords_IsGuest(number) == 1 && PlayerRecords_Guests() != NULL) {
        u8 *guests = PlayerRecords_Guests();
        return player_records_at(guests, PlayerRecords_GuestIndex(number));
    }
    return NULL;
}
CLEAN_AS(func_0209847c, PlayerRecords_Get)

/* func_020984d4: the record number of this system's player. */
int PlayerRecords_CurrentNumber(void)
{
    return func_02096284(data_020ccf94->local_player);
}
CLEAN_AS(func_020984d4, PlayerRecords_CurrentNumber)

/* func_020984e8: the record of this system's player. */
u8 *PlayerRecords_Current(void)
{
    return PlayerRecords_OfPlayer(data_020ccf94->local_player);
}
CLEAN_AS(func_020984e8, PlayerRecords_Current)

/* func_020984fc: the record of session player `player`. */
u8 *PlayerRecords_OfPlayer(int player)
{
    return PlayerRecords_Get(func_02096284(player));
}
CLEAN_AS(func_020984fc, PlayerRecords_OfPlayer)

/* func_02098510: a guest record number's index among the guests, -1 for another number. */
int PlayerRecords_GuestIndex(int number)
{
    if (PlayerRecords_IsGuest(number) == 1) {
        return number - PLAYER_RECORD_FIRST_GUEST;
    }
    return -1;
}
CLEAN_AS(func_02098510, PlayerRecords_GuestIndex)

/* func_02098530: whether record `number` is a guest's (4-6). */
int PlayerRecords_IsGuest(int number)
{
    return number >= PLAYER_RECORD_FIRST_GUEST && number < PLAYER_RECORD_FIRST_GUEST + PLAYER_RECORDS_GUESTS;
}
CLEAN_AS(func_02098530, PlayerRecords_IsGuest)

/* func_02098540: clear the guest records. */
void PlayerRecords_ClearGuests(void)
{
    PlayerRecords_ClearThree(PlayerRecords_Guests());
}
CLEAN_AS(func_02098540, PlayerRecords_ClearGuests)

/* func_02098554: clear three records in a row. */
void PlayerRecords_ClearThree(u8 *records)
{
    for (int i = 0; i < PLAYER_RECORDS_GUESTS; i++) {
        func_02099a38(player_records_at(records, i));
    }
}
CLEAN_AS(func_02098554, PlayerRecords_ClearThree)

/* func_02098578 */
u8 *PlayerRecords_Guests(void)
{
    return data_021d5738;
}
CLEAN_AS(func_02098578, PlayerRecords_Guests)

/* func_02098580: the guest records' destructor (registered by __sinit_020c6394). */
u8 *PlayerRecords_DestructGuests(u8 *guests)
{
    __cxa_vec_cleanup(guests, PLAYER_RECORDS_GUESTS, PLAYER_RECORD_SIZE, (void (*)(void *))(uintptr_t) func_02099ad0);
    return guests;
}
CLEAN_AS(func_02098580, PlayerRecords_DestructGuests)

/* func_020985a0: the guest records' constructor. */
u8 *PlayerRecords_ConstructGuests(u8 *guests)
{
    __cxa_vec_ctor(guests, PLAYER_RECORDS_GUESTS, PLAYER_RECORD_SIZE, (void (*)(void *))(uintptr_t) func_02099bc8,
                   (void (*)(void *))(uintptr_t) func_02099ad0);
    return guests;
}
CLEAN_AS(func_020985a0, PlayerRecords_ConstructGuests)

/* func_020985cc: make a new player in town record `number` (0-3) of `players`: clear the
 * record, then give it `name`, `arg`, a player id that none of the other town players has, no
 * item at 0x2406 and the record number's starting item. The record, or NULL for another
 * number. */
u8 *PlayerRecords_NewPlayer(u8 *players, const void *name, int arg, int number)
{
    if (func_020988d8((u32) number) != 1) {
        return NULL;
    }
    if ((data_021d56f0 & 1) == 0) {
        u8 *blocks[PLAYER_RECORDS_TOWN] = {data_021d572c, data_021d5720, data_021d5714, data_021d5708};
        for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
            data_021d56f4[i] = (u16) (STARTING_ITEM_FIRST + i * STARTING_ITEM_STEP);
            __register_global_object(&data_021d56f4[i], (void *) (uintptr_t) func_020051b0, blocks[i]);
        }
        data_021d56f0 |= 1;
    }
    u8 *self = player_records_at(players, number);

    /* The ids of the other players there are. */
    u16 taken[PLAYER_RECORDS_TOWN - 1];
    int count = 0;
    MI_CpuFill8(taken, 0, sizeof(taken));
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        if (i == number) {
            continue;
        }
        u8 *other = player_records_at(players, i);
        if (func_020951bc(func_02099870(other)) == 1) {
            taken[count] = (u16) func_020950d0(func_02099870(other));
            count++;
        }
    }

    func_02099a38(self);
    u16 no_item = NO_ITEM;
    func_0209987c(self, name, func_020950f8(taken, count), arg, 0, 0, 0, 0, 0, 0, 0, &no_item);
    func_020996bc(self, &data_021d56f4[number & 3]);
    return self;
}
CLEAN_AS(func_020985cc, PlayerRecords_NewPlayer)

/* The town's four records. */

#include <string.h>

extern int func_02099314(u8 *records, int count); /* the first of `count` records without a player, or -1 */
extern int func_0209518c(const PlayerRecordsId *a, const PlayerRecordsId *b); /* the same player number and name */
extern u32 func_020644cc(int bound);                                          /* a random number below `bound` */

/* Whether two ids name the same player: the same town, then func_0209518c. */
static int player_records_same(const PlayerRecordsId *a, const PlayerRecordsId *b)
{
    return a->town_id == b->town_id && memcmp(a->town_name, b->town_name, sizeof(a->town_name)) == 0 &&
           func_0209518c(a, b) != 0;
}

/* func_0209871c: the number of the town record whose player has id `player`; -1 when there is
 * none, or when that id is not set. */
int PlayerRecords_FindIndex(u8 *players, const PlayerRecordsId *player)
{
    if (func_020951bc((void *) (uintptr_t) player) != 1) {
        return -1;
    }
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        const PlayerRecordsId *id = func_02099870(player_records_at(players, i));
        if (player_records_same(player, id)) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_0209871c, PlayerRecords_FindIndex)

/* func_0209877c: the first town record without a player, or -1. */
int PlayerRecords_FirstFree(u8 *players)
{
    return func_02099314(players, PLAYER_RECORDS_TOWN);
}
CLEAN_AS(func_0209877c, PlayerRecords_FirstFree)

/* func_02098788: clear the four town records. */
void PlayerRecords_ClearTown(u8 *players)
{
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        func_02099a38(player_records_at(players, i));
    }
}
CLEAN_AS(func_02098788, PlayerRecords_ClearTown)

/* func_020987ac: the record of a town player drawn at random, other than the player of id
 * `player` (when given); NULL when there is no other. */
u8 *PlayerRecords_RandomOther(u8 *players, const PlayerRecordsId *player)
{
    int count;
    if (player == NULL || PlayerRecords_Find(players, player) == NULL) {
        count = PlayerRecords_CountTown(players);
    } else {
        count = PlayerRecords_CountTown(players) - 1;
    }
    if (count <= 0) {
        return NULL;
    }
    u32 left = func_020644cc(count);
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        u8 *record = player_records_at(players, i);
        if (func_02099a28(record) != 1) {
            continue;
        }
        if (player != NULL && player_records_same(player, func_02099870(record))) {
            continue;
        }
        if (left == 0) {
            return record;
        }
        left--;
    }
    return NULL;
}
CLEAN_AS(func_020987ac, PlayerRecords_RandomOther)

/* func_02098844: town record `number`; NULL outside 0-3. */
u8 *PlayerRecords_TownRecord(u8 *players, int number)
{
    if (PlayerRecords_IsTownNumber((u32) number) != 0) {
        return player_records_at(players, number);
    }
    return NULL;
}
CLEAN_AS(func_02098844, PlayerRecords_TownRecord)

/* func_02098868: the town record of the player of id `player`, or NULL. */
u8 *PlayerRecords_Find(u8 *players, const PlayerRecordsId *player)
{
    return PlayerRecords_TownRecord(players, PlayerRecords_FindIndex(players, player));
}
CLEAN_AS(func_02098868, PlayerRecords_Find)

/* func_02098880: how many town records hold a player. */
int PlayerRecords_CountTown(u8 *players)
{
    int count = 0;
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        if (PlayerRecords_TownExists(players, i) != 0) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_02098880, PlayerRecords_CountTown)

/* func_020988a4: whether town record `number` holds a player (0 outside 0-3). */
int PlayerRecords_TownExists(u8 *players, int number)
{
    if (PlayerRecords_IsTownNumber((u32) number) != 0 && func_02099a28(player_records_at(players, number)) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020988a4, PlayerRecords_TownExists)

/* func_020988d8: whether `number` is a town record's (0-3). */
int PlayerRecords_IsTownNumber(u32 number)
{
    return number < PLAYER_RECORDS_TOWN;
}
CLEAN_AS(func_020988d8, PlayerRecords_IsTownNumber)

/* func_020988e4: the town records' destructor. */
u8 *PlayerRecords_DestructTown(u8 *players)
{
    __cxa_vec_cleanup(players, PLAYER_RECORDS_TOWN, PLAYER_RECORD_SIZE, (void (*)(void *))(uintptr_t) func_02099ad0);
    return players;
}
CLEAN_AS(func_020988e4, PlayerRecords_DestructTown)

/* func_02098904: the town records' constructor. */
u8 *PlayerRecords_ConstructTown(u8 *players)
{
    __cxa_vec_ctor(players, PLAYER_RECORDS_TOWN, PLAYER_RECORD_SIZE, (void (*)(void *))(uintptr_t) func_02099bc8,
                   (void (*)(void *))(uintptr_t) func_02099ad0);
    return players;
}
CLEAN_AS(func_02098904, PlayerRecords_ConstructTown)
