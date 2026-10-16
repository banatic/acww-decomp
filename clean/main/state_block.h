/* The large block of the game's state that func_0209f0f0 clears (0x173fc bytes). What it holds
 * is not known yet; its last words are 32 flags and a value func_0209f180 checks. */
#ifndef CLEAN_MAIN_STATE_BLOCK_H
#define CLEAN_MAIN_STATE_BLOCK_H

#include "clock.h"
#include "types.h"

void StateBlock_ClearFlag(u32 *block, u32 flag);
void StateBlock_SetFlag(u32 *block, u32 flag);
int StateBlock_TestFlag(u32 *block, u32 flag);

/* The state block's layout (data_021dc7a8): the town and everything kept with it. Each part
 * is named after the code that owns it where that code has a Clean name, else by its offset;
 * StateBlock_Init sets each one up and StateBlock_Destruct destructs them. */

#define STATE_BLOCK_PLAYERS 4
#define STATE_BLOCK_SET_UP 0x32 /* StateBlock.marker once a town was set up */

/* The town's number and name, as a design's creator keeps them. */
typedef struct StateBlockTown {
    u16 number;
    u8 name[12];
} StateBlockTown;

typedef struct StateBlock {
    u8 marker; /* 0x00000: STATE_BLOCK_SET_UP once StateBlock_SetUpTown ran */
    u8 unk_00001;
    StateBlockTown town;                      /* 0x00002 */
    u8 unk_00010[4];                          /* 0x00010 */
    u8 players[0x9284 - 0x14];                /* 0x00014: player_records.h */
    u8 villagers[0xd304 - 0x9284];            /* 0x09284: VillagerTown */
    u8 layout[0xf52a - 0xd304];               /* 0x0d304: town_layout.h */
    u8 part_0f52a;                            /* 0x0f52a */
    u8 part_0f52b;                            /* 0x0f52b */
    u8 part_0f52c[0x10ad0 - 0xf52c];          /* 0x0f52c */
    u8 shop_designs[0x11c70 - 0x10ad0];       /* 0x10ad0: ShopDesigns */
    u8 part_11c70[0x125c0 - 0x11c70];         /* 0x11c70 */
    u8 bbs[0x13144 - 0x125c0];                /* 0x125c0: Bbs */
    u8 mailboxes[STATE_BLOCK_PLAYERS][0xa04]; /* 0x13144: a MailBox for each player */
    u8 post_office[0x1635c - 0x15954];        /* 0x15954: MailPostOffice */
    u8 constellations[0x16800 - 0x1635c];     /* 0x1635c: ConstellationStore */
    u8 part_16800[STATE_BLOCK_PLAYERS][0xb4]; /* 0x16800: one for each player */
    u8 part_16ad0[0x16d08 - 0x16ad0];         /* 0x16ad0 */
    u8 house_looks[0x16f44 - 0x16d08];        /* 0x16d08: HouseLooksRecord */
    u8 bottle[0x1704c - 0x16f44];             /* 0x16f44: BottleState */
    u8 part_1704c[0x17150 - 0x1704c];         /* 0x1704c */
    u8 museum[0x171b4 - 0x17150];             /* 0x17150: MuseumRecord */
    u8 nook_store[0x17218 - 0x171b4];         /* 0x171b4: NookStore */
    u8 part_17218[0x17254 - 0x17218];         /* 0x17218 */
    u8 part_17254[0x172c0 - 0x17254];         /* 0x17254 */
    u8 part_172c0[0x172de - 0x172c0];         /* 0x172c0 */
    u8 part_172de[0x172fc - 0x172de];         /* 0x172de */
    u8 part_172fc[0x17344 - 0x172fc];         /* 0x172fc */
    u8 part_17344[0x17364 - 0x17344];         /* 0x17344 */
    u8 part_17364[0x1737e - 0x17364];         /* 0x17364 */
    u8 part_1737e[0x17388 - 0x1737e];         /* 0x1737e */
    u8 fox_shop[0x1739c - 0x17388];           /* 0x17388: FoxShop */
    u8 shop_list_a[0x173ae - 0x1739c];        /* 0x1739c: ShopListA */
    u8 snowmen[0x173c0 - 0x173ae];            /* 0x173ae: SnowmenRecord */
    u8 part_173c0[0x173c8 - 0x173c0];         /* 0x173c0 */
    u8 part_173c8[0x173cc - 0x173c8];         /* 0x173c8 */
    ClockOffset clock_offset;                 /* 0x173cc */
    u8 part_173d4[0x173dd - 0x173d4];         /* 0x173d4 */
    u8 part_173dd[0x173e2 - 0x173dd];         /* 0x173dd */
    u8 part_173e2[0x173f4 - 0x173e2];         /* 0x173e2 */
    u32 flags;                                /* 0x173f4: StateBlock_SetFlag and the others */
    u8 part_173f8[4];                         /* 0x173f8 */
} StateBlock;

void StateBlock_FinishStart(StateBlock *block);
void StateBlock_Start(StateBlock *block, int mode);
void StateBlock_SetClockOffset(StateBlock *block);
void StateBlock_LoadTownMap(StateBlock *block);
void StateBlock_SetUpTown(StateBlock *block);
void StateBlock_MovePlayerHere(StateBlock *block);
void StateBlock_StartMode6(StateBlock *block);
void StateBlock_StartMode5(StateBlock *block);
void StateBlock_StartMode4(StateBlock *block);
void StateBlock_StartMode3(StateBlock *block);
void StateBlock_StartMode2(StateBlock *block);
void StateBlock_StartMode1(StateBlock *block);
void StateBlock_StartMode0(StateBlock *block);
void StateBlock_ForgetPlayer(StateBlock *block, int player);
void StateBlock_Init(StateBlock *block);
void StateBlock_Clear(StateBlock *block);
int StateBlock_IsSetUp(StateBlock *block);
StateBlock *StateBlock_Destruct(StateBlock *block);

#endif
