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
 * The entry's byte 0x18 stays set while the counter at 0x1a runs: func_0208541c counts the
 * counter down each time and clears the byte when it reaches 0. */
#ifndef CLEAN_MAIN_VILLAGER_STATE_H
#define CLEAN_MAIN_VILLAGER_STATE_H

#include "types.h"

#define VILLAGER_STATE_ENTRIES 8
#define VILLAGER_STATE_NONE (-1) /* the town bytes that hold no index */

/* The flags at 0x1d of an entry. */
#define VILLAGER_STATE_FLAG_0 0x01
#define VILLAGER_STATE_FLAG_1 0x02 /* set by VillagerState_SetFlag1UnlessScene */
#define VILLAGER_STATE_FLAG_2 0x04

#define VILLAGER_TALLY_DELAY 40
#define VILLAGER_TALLY_TIMER 1200

typedef struct VillagerTally {
    u16 timer; /* 0x00: the count is dropped when it is out */
    u8 delay;  /* 0x02: runs out before the timer starts; counts are taken while it runs */
    u8 count;  /* 0x03 */
} VillagerTally;

typedef struct VillagerState {
    u8 state;            /* 0x00: 0-7 */
    u8 byte_01;          /* 0x01: 3 when set up */
    u8 unused_02[2];     /* 0x02 */
    u8 object[12];       /* 0x04: set up by func_0209bd5c (no item, 0xfff1, at its 0x08) */
    u8 bytes_10[8];      /* 0x10: cleared by func_0209c52c */
    u8 byte_18;          /* 0x18: 5 when set up; cleared when the counter runs out */
    u8 unused_19;        /* 0x19 */
    u16 counter;         /* 0x1a */
    u8 byte_1c;          /* 0x1c: 12 when set up */
    u8 flags;            /* 0x1d: VILLAGER_STATE_FLAG_* */
    u8 byte_1e;          /* 0x1e: doubled up to 32 by VillagerState_DoubleByte1E */
    u8 unused_1f;        /* 0x1f */
    u32 word_20;         /* 0x20 */
    u16 half_24;         /* 0x24 */
    u16 item;            /* 0x26: an item code; 0xfff1 is none */
    VillagerTally tally; /* 0x28 */
} VillagerState;

typedef struct VillagerStates {
    VillagerState entries[VILLAGER_STATE_ENTRIES]; /* 0x000 */
    s8 index_160;                                  /* 0x160 */
    u8 byte_161;                                   /* 0x161 */
    s8 index_162;                                  /* 0x162: a villager index (func_0207a8ac gives its entry state 0), or -1 */
    s8 index_163;                                  /* 0x163: a villager index (func_0207a8ac gives its entry state 3), or -1 */
    s8 index_164;                                  /* 0x164 */
    u8 unused_165[3];
    u32 word_168; /* 0x168 */
    s8 index_16c; /* 0x16c */
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
void VillagerState_ClearAllFlag2(void);
void VillagerState_ClearAllFlag0(void);
void VillagerState_ClearWord168(void);
int VillagerState_GetIndex164(void);
void VillagerState_SetIndex164(unsigned char index);
int VillagerState_GetIndex16C(void);
void VillagerState_SetIndex16C(char index);
signed char VillagerState_GetIndex163(void);
void VillagerState_SetIndex163(unsigned char index);
int VillagerState_GetIndex162(void);
void VillagerState_SetIndex162(unsigned char index);
void VillagerState_ClearIndex160(void);

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
void VillagerState_ClearItem(VillagerState *entry);
void VillagerState_SetItem(VillagerState *entry, const u16 *item);
u16 *VillagerState_Item(VillagerState *entry);
void VillagerState_DoubleByte1E(VillagerState *entry);
void VillagerState_SetFlag1UnlessScene(VillagerState *entry);
void VillagerState_CountDown(VillagerState *entry);
int VillagerState_GetCounter(const VillagerState *entry);
void VillagerState_SetCounter(VillagerState *entry, int counter);
void VillagerState_AddCounter(VillagerState *entry, int amount);
void VillagerState_SetByte18(VillagerState *entry, int value);
int VillagerState_GetByte18(const VillagerState *entry);
void VillagerState_SetByte1C(VillagerState *entry, int value);
int VillagerState_GetByte1C(const VillagerState *entry);
u8 *VillagerState_Object(VillagerState *entry);
void VillagerState_SetByte01(VillagerState *entry, int value);
int VillagerState_LinkedByte01(const VillagerState *entry);
void VillagerState_SettleState(VillagerState *entry);
void VillagerState_SetState(VillagerState *entry, int state);
int VillagerState_LinkedState(const VillagerState *entry);
VillagerState *VillagerState_Destruct(VillagerState *entry);
VillagerState *VillagerState_Construct(VillagerState *entry);

#endif
