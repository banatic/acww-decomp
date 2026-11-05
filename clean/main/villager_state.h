/* The running state of the town's eight villagers (data_021d13e4, VillagerState_Table): one
 * entry of 0x2c bytes for each villager index (the one func_0207f29c gives a villager of
 * data_021e5a2c; func_0207f270 finds its entry), then a few bytes for the town as a whole.
 * Nothing of it is kept in the save: VillagerState_ResetTable sets it all up.
 *
 * Each entry holds a tally (VillagerTally) that counts events within a time limit: Start gives
 * it 40 ticks of delay and 1200 of timer, Count adds one while the delay runs, Tick runs the
 * delay down and then the timer, and the count is dropped when the timer is out. Its level is 1
 * from a count of 7 and 2 from 10, while data_020e54a8 is 0.
 *
 * The entry's mood (byte 0x18, villager_mood.h) stays set while its frames at 0x1a run:
 * func_0208541c counts them down each time and clears the mood when they reach 0. The byte at
 * 0x1c is the villager's activity of the moment (one of its hobbies' kinds, read by overlay 68
 * to pick the tool it carries, held at 0x26), and 0x20 and 0x24 its room's score and flags
 * (VillagerTown_ScoreRoom, RoomScore_ScoreVillager).
 *
 * The town bytes after the entries name villagers of the day: the one with fleas (0x160), the
 * one that tells the fox's password (0x161), the birthday villager and its companion (0x162,
 * 0x163), the visitor of the player's flea market (0x164), and the villager that greets the
 * player first on the player's birthday (0x16c); 0x168 counts the frames since the last
 * villager event (villager_events.h). */
#ifndef CLEAN_MAIN_VILLAGER_STATE_H
#define CLEAN_MAIN_VILLAGER_STATE_H

#include "types.h"

#define VILLAGER_STATE_ENTRIES 8
#define VILLAGER_STATE_NONE (-1) /* the town bytes that hold no index */

/* The flags at 0x1d of an entry. */
#define VILLAGER_STATE_FLAG_STING_SAID 0x01
#define VILLAGER_STATE_FLAG_1 0x02 /* set by VillagerState_SetFlag1UnlessScene */
#define VILLAGER_STATE_FLAG_GREETED 0x04

#define VILLAGER_TALLY_DELAY 40
#define VILLAGER_TALLY_TIMER 1200

typedef struct VillagerTally {
    u16 timer; /* 0x00: the count is dropped when it is out */
    u8 delay;  /* 0x02: runs out before the timer starts; counts are taken while it runs */
    u8 count;  /* 0x03 */
} VillagerTally;

typedef struct VillagerState {
    u8 state;             /* 0x00: 0-7 */
    u8 place;             /* 0x01: where it is (enum VillagerPlace of villager_outdoors.h); none (3) when set up */
    u8 unused_02[2];      /* 0x02 */
    u8 object[12];        /* 0x04: the villager's dealt errand (villager_errands.h), set up by VillagerErrand_Clear */
    u8 bytes_10[8];       /* 0x10: cleared by func_0209c52c */
    u8 mood;              /* 0x18: villager_mood.h; 5 when set up; cleared when its frames run out */
    u8 unused_19;         /* 0x19 */
    u16 mood_frames;      /* 0x1a */
    u8 activity;          /* 0x1c: 12 when set up */
    u8 flags;             /* 0x1d: VILLAGER_STATE_FLAG_* */
    u8 byte_1e;           /* 0x1e: doubled up to 32 by VillagerState_DoubleByte1E */
    u8 unused_1f;         /* 0x1f */
    u32 room_score;       /* 0x20: VillagerTown_ScoreRoom */
    u16 room_score_flags; /* 0x24 */
    u16 held_item;        /* 0x26: an item code; 0xfff1 is none */
    VillagerTally tally;  /* 0x28 */
} VillagerState;

typedef struct VillagerStates {
    VillagerState entries[VILLAGER_STATE_ENTRIES]; /* 0x000 */
    s8 flea_villager;                              /* 0x160 */
    u8 fox_password_villager;                      /* 0x161 */
    s8 birthday_villager;                          /* 0x162: a villager index (func_0207a8ac gives its entry state 0), or -1 */
    s8 birthday_companion;                         /* 0x163: a villager index (func_0207a8ac gives its entry state 3), or -1 */
    s8 flea_market_visitor;                        /* 0x164 */
    u8 unused_165[3];
    u32 idle_frames;     /* 0x168 */
    s8 birthday_greeter; /* 0x16c */
    u8 unused_16d[3];
} VillagerStates;

/* The table */
VillagerStates *VillagerState_Table(void);
void VillagerState_ResetTable(VillagerStates *table);
void VillagerState_Reset(void);
void VillagerState_ClearTable(VillagerStates *table);
void VillagerState_Clear(void);
void VillagerState_NoOp(void);
void VillagerState_CallNoOp(void);
VillagerState *VillagerState_At(VillagerStates *table, int index);
int VillagerState_IsIndex(int index);
void VillagerState_ClearAllTallies(void);
void VillagerState_ClearAllGreeted(void);
void VillagerState_ClearAllStingSaid(void);
void VillagerState_ClearIdleFrames(void);
int VillagerState_GetFleaMarketVisitor(void);
void VillagerState_SetFleaMarketVisitor(unsigned char index);
int VillagerState_GetBirthdayGreeter(void);
void VillagerState_SetBirthdayGreeter(char index);
signed char VillagerState_GetBirthdayCompanion(void);
void VillagerState_SetBirthdayCompanion(unsigned char index);
int VillagerState_GetBirthdayVillager(void);
void VillagerState_SetBirthdayVillager(unsigned char index);
void VillagerState_ClearFleaVillager(void);

/* The tally */
int VillagerTally_Level(const VillagerTally *tally);
void VillagerTally_Start(VillagerTally *tally);
void VillagerTally_Count(VillagerTally *tally);
void VillagerTally_Tick(VillagerTally *tally, int skip);
void VillagerTally_Clear(VillagerTally *tally);
void VillagerTally_Destruct(VillagerTally *tally);
void VillagerTally_Construct(VillagerTally *tally);

/* An entry */
void VillagerState_Init(VillagerState *entry);
VillagerTally *VillagerState_Tally(VillagerState *entry);
void VillagerState_ClearHeldItem(VillagerState *entry);
void VillagerState_SetHeldItem(VillagerState *entry, const u16 *item);
u16 *VillagerState_HeldItem(VillagerState *entry);
void VillagerState_DoubleByte1E(VillagerState *entry);
void VillagerState_SetFlag1UnlessScene(VillagerState *entry);
void VillagerState_CountDownMood(VillagerState *entry);
int VillagerState_GetMoodFrames(const VillagerState *entry);
void VillagerState_SetMoodFrames(VillagerState *entry, int counter);
void VillagerState_AddMoodFrames(VillagerState *entry, int amount);
void VillagerState_SetMood(VillagerState *entry, int value);
int VillagerState_GetMood(const VillagerState *entry);
void VillagerState_SetActivity(VillagerState *entry, int value);
int VillagerState_GetActivity(const VillagerState *entry);
u8 *VillagerState_Errand(VillagerState *entry);
void VillagerState_SetPlace(VillagerState *entry, int value);
int VillagerState_LinkedPlace(const VillagerState *entry);
void VillagerState_SettleState(VillagerState *entry);
void VillagerState_SetState(VillagerState *entry, int state);
int VillagerState_LinkedState(const VillagerState *entry);
VillagerState *VillagerState_Destruct(VillagerState *entry);
VillagerState *VillagerState_Construct(VillagerState *entry);
VillagerStates *VillagerState_DestructTable(VillagerStates *table);

#endif
