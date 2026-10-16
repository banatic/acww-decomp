/* A player record's object at 0x2416 (PlayerRecord_Field2416, 0x11 bytes; func_02088c10
 * constructs it): a date, a few counts and the flags of the fishing tourney and the insect
 * contest (event_winner.h).
 *
 *   0x00  a date: day, month, year (PlayerField2416_SetToday)
 *   0x08  a byte DayEvents_PlayerHas asks to be 15 for its events of kind 2 (func_02088bdc)
 *   0x0b, 0x0c  two bytes cleared together
 *   0x0e  a count up to 100 that overlay 70 adds to
 *   0x0f  a count up to 255 that overlay 71 raises; the insurance letter pays for it
 *         (NpcLetters_SendInsurance) and clears it
 *   0x10  bit 0: entered the fishing tourney; bit 1: entered the insect contest; bits 2-5: a
 *         count up to 10 that overlay 84 raises; bit 6: owed a gardening letter */
#ifndef CLEAN_MAIN_PLAYER_FIELD_2416_H
#define CLEAN_MAIN_PLAYER_FIELD_2416_H

#include "main/calendar.h"
#include "types.h"

#define PLAYER_FIELD_2416_SIZE 0x11

typedef struct PlayerField2416 {
    u8 day; /* 0x00 */
    u8 month;
    u8 year;
    u8 unk_03;
    Date date_04; /* 0x04: a second date (PlayerField2416_SetDate04Today) */
    u8 byte_08;   /* 0x08 */
    u8 count_09;  /* 0x09: up to PLAYER_FIELD_2416_COUNT_09_MAX */
    u8 count_0a;  /* 0x0a: up to PLAYER_FIELD_2416_COUNT_0A_MAX */
    u8 byte_0b;   /* 0x0b: points up to 255 that overlay 87 compares with a table */
    u8 byte_0c;   /* 0x0c: overlay 87's level in that table, up to PLAYER_FIELD_2416_LEVEL_MAX */
    u8 count_0d;  /* 0x0d: up to PLAYER_FIELD_2416_COUNT_0D_MAX */
    u8 count_0e;  /* 0x0e: up to PLAYER_FIELD_2416_COUNT_0E_MAX */
    u8 claims;    /* 0x0f */
    u8 flags;     /* 0x10 */
} PlayerField2416;

#define PLAYER_FIELD_2416_COUNT_0E_MAX 100
#define PLAYER_FIELD_2416_CLAIMS_MAX 0xff
#define PLAYER_FIELD_2416_TALLY_MAX 10

/* PlayerField2416.flags */
#define PLAYER_FIELD_2416_FISHING 0x01
#define PLAYER_FIELD_2416_INSECTS 0x02
#define PLAYER_FIELD_2416_TALLY_SHIFT 2
#define PLAYER_FIELD_2416_TALLY_MASK 0x3c
#define PLAYER_FIELD_2416_GARDENING 0x40

void PlayerField2416_RaiseClaims(PlayerField2416 *field);
int PlayerField2416_Claims(PlayerField2416 *field);
void PlayerField2416_SetToday(PlayerField2416 *field);
PlayerField2416 *PlayerField2416_Date(PlayerField2416 *field);
void PlayerField2416_ClearGardening(PlayerField2416 *field);
void PlayerField2416_SetGardening(PlayerField2416 *field);
int PlayerField2416_Gardening(PlayerField2416 *field);
void PlayerField2416_ClearBytes0B(PlayerField2416 *field);
void PlayerField2416_ClearTally(PlayerField2416 *field);
void PlayerField2416_RaiseTally(PlayerField2416 *field);
int PlayerField2416_Tally(PlayerField2416 *field);
void PlayerField2416_SetInsects(PlayerField2416 *field, u32 entered);
int PlayerField2416_Insects(PlayerField2416 *field);
void PlayerField2416_SetFishing(PlayerField2416 *field, int entered);
int PlayerField2416_Fishing(PlayerField2416 *field);
void PlayerField2416_AddCount0E(PlayerField2416 *field, u8 amount);

/* The bytes at 0x09 to 0x0d. Overlay 4 raises the count at 0x09 now and then, overlay 53 adds
 * to the one at 0x0a, and overlay 87 adds points to 0x0b and raises the level at 0x0c; the
 * count at 0x0d is raised once a day in scene 6 (StateBlock_StartMode2). */
#define PLAYER_FIELD_2416_COUNT_09_MAX 15
#define PLAYER_FIELD_2416_COUNT_0A_MAX 16
#define PLAYER_FIELD_2416_POINTS_MAX 0xff
#define PLAYER_FIELD_2416_LEVEL_MAX 12
#define PLAYER_FIELD_2416_COUNT_0D_MAX 6

int PlayerField2416_Count0E(PlayerField2416 *field);
void PlayerField2416_RaiseCount0D(PlayerField2416 *field);
int PlayerField2416_Count0D(PlayerField2416 *field);
void PlayerField2416_RaiseLevel(PlayerField2416 *field);
int PlayerField2416_Level(PlayerField2416 *field);
void PlayerField2416_AddPoints(PlayerField2416 *field, int amount);
int PlayerField2416_Points(PlayerField2416 *field);
void PlayerField2416_AddCount0A(PlayerField2416 *field, int amount);
int PlayerField2416_Count0A(PlayerField2416 *field);
void PlayerField2416_SetCount09(PlayerField2416 *field, u8 count);
int PlayerField2416_Count09(PlayerField2416 *field);
void PlayerField2416_SetByte08(PlayerField2416 *field, int value);
int PlayerField2416_Byte08(PlayerField2416 *field);
void PlayerField2416_SetDate04Today(PlayerField2416 *field);
int PlayerField2416_Date04(PlayerField2416 *field);
void PlayerField2416_Reset(PlayerField2416 *field);
void PlayerField2416_Destruct(PlayerField2416 *field);
void PlayerField2416_Construct(PlayerField2416 *field);

#endif
