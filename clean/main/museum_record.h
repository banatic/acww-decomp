/* A record of who gave each of 184 items, in four groups, and the date the record was
 * completed.
 *
 * Each item has four bits: 0 when nobody gave it, 1-4 for the player (0-3) who did, and 5 once
 * that player is gone (MuseumRecord_ForgetPlayer). Completing the record stores the date, and
 * on a later day each player of the town is sent a letter from "sp_npc_owl" with item 0x3870
 * (MuseumRecord_SendLetters). The callers are overlay 47 and the players' code; the group
 * sizes (52, 56, 56 and 20) and the owl's letter suggest the museum, which is why it is named
 * so here; which of the museum's collections each group is has not been checked. */
#ifndef CLEAN_MAIN_MUSEUM_RECORD_H
#define CLEAN_MAIN_MUSEUM_RECORD_H

#include "types.h"

/* The four groups' item codes. Group A's items come in four variants (the low two bits), which
 * share one entry; the others have one entry each. */
#define MUSEUM_A_FIRST 0x450c /* 52 items, 4 codes apart */
#define MUSEUM_A_LAST 0x45db
#define MUSEUM_A_ITEMS 52
#define MUSEUM_B_FIRST 0x12e8 /* 56 items */
#define MUSEUM_B_LAST 0x131f
#define MUSEUM_B_ITEMS 56
#define MUSEUM_C_FIRST 0x12b0 /* 56 items */
#define MUSEUM_C_LAST 0x12e7
#define MUSEUM_C_ITEMS 56
#define MUSEUM_D_FIRST 0x3894 /* 20 items, 4 codes apart */
#define MUSEUM_D_LAST 0x38e3
#define MUSEUM_D_ITEMS 20
#define MUSEUM_ITEMS (MUSEUM_A_ITEMS + MUSEUM_B_ITEMS + MUSEUM_C_ITEMS + MUSEUM_D_ITEMS)

/* An item's four bits. */
enum MuseumGiver {
    MUSEUM_NOT_GIVEN = 0,
    MUSEUM_GIVEN_BY_PLAYER_0 = 1, /* 1-4: by player 0-3 */
    MUSEUM_GIVEN_BY_FORMER = 5    /* by a player who has left */
};

/* What MuseumRecord_Giver tells of an item. */
enum MuseumGiverKind {
    MUSEUM_BY_CURRENT_PLAYER = 0,
    MUSEUM_BY_OTHER_PLAYER = 1,
    MUSEUM_BY_FORMER_PLAYER = 2,
    MUSEUM_NOBODY = 3
};

/* Four bits per item, two items to a byte (the first in the low bits); each group's array has
 * one byte more than it needs. */
typedef struct MuseumRecord {
    u8 group_a[0x1b];
    u8 group_b[0x1d];
    u8 group_c[0x1d];
    u8 group_d[0xb];
    u8 day; /* 0x60: when the record was completed */
    u8 month;
    u8 year;
    u8 unk_63; /* set to 0 with the date */
} MuseumRecord;

int MuseumRecord_CountGroupAKind(MuseumRecord *record, int kind);
int MuseumRecord_PercentGiven(MuseumRecord *record);
int MuseumRecord_GroupBComplete(MuseumRecord *record);
unsigned int MuseumRecord_GroupDComplete(MuseumRecord *record);
int MuseumRecord_GroupAComplete(MuseumRecord *record);
int MuseumRecord_GroupCComplete(MuseumRecord *record);
int MuseumRecord_Complete(MuseumRecord *record);
int MuseumRecord_GiverName(MuseumRecord *record, void *name, const u16 *item);
void MuseumRecord_ForgetPlayer(MuseumRecord *record, int player);
void MuseumRecord_Give(MuseumRecord *record, const u16 *item);
int MuseumRecord_SendLetters(void *record);
void MuseumRecord_CheckLetters(MuseumRecord *record);
int MuseumRecord_IsGiven(MuseumRecord *record, const u16 *item);
int MuseumRecord_Giver(MuseumRecord *record, const u16 *item);
int MuseumRecord_GiverBits(MuseumRecord *record, const u16 *item);
int MuseumRecord_Locate(MuseumRecord *record, const u16 *item, int *index);
void MuseumRecord_SetFormer(MuseumRecord *record, const u16 *item);
void MuseumRecord_Clear(MuseumRecord *record, const u16 *item);
void MuseumRecord_ClearAll(MuseumRecord *record);
void MuseumRecord_Destruct(MuseumRecord *record);
MuseumRecord *MuseumRecord_Construct(MuseumRecord *record);

#endif
