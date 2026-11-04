/* A player record's object at 0x2416 (PlayerRecord_Field2416, 0x11 bytes; func_02088c10
 * constructs it): a date, the player's counts with special characters and the flags of the
 * fishing tourney and the insect contest (event_winner.h). Each count has one writer:
 *
 *   0x00  a date: day, month, year (PlayerField2416_SetToday)
 *   0x04  the day the player's part-time job at Nook's ended (overlay 50, NookClerkTalk_JobEnd)
 *   0x08  the days the tailor's sister talked with the player, up to 15 (overlay 4,
 *         tailor_sister.c); DayEvents_PlayerHas asks for 15 for its events of kind 2
 *   0x09  the coffees drunk at the cafe, up to 15 (overlay 4, cafe_master.c)
 *   0x0a  the haircuts, up to 16 (overlay 53, barber_talk.c)
 *   0x0b, 0x0c  the acorn festival's points and level (overlay 87, acorn_npc_talk.c), cleared
 *         together
 *   0x0d  the visits after a reset, up to 6 (StateBlock_StartMode2), whose count picks the
 *         line overlay 77's mole starts with
 *   0x0e  the fashion score, up to 100, that overlay 70's giraffe adds to
 *   0x0f  a count up to 255 that overlay 71 raises; the insurance letter pays for it
 *         (NpcLetters_SendInsurance) and clears it
 *   0x10  bit 0: entered the fishing tourney; bit 1: entered the insect contest; bits 2-5: the
 *         gifts of the fireworks show, up to 10 (overlay 84); bit 6: owed a gardening letter */
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
    Date job_end;        /* 0x04: the day Nook's part-time job ended (PlayerField2416_SetJobEndToday) */
    u8 tailor_talk_days; /* 0x08 */
    u8 coffees;          /* 0x09: up to PLAYER_FIELD_2416_COFFEES_MAX */
    u8 haircuts;         /* 0x0a: up to PLAYER_FIELD_2416_HAIRCUTS_MAX */
    u8 acorn_points;     /* 0x0b: points up to 255 that overlay 87 compares with a table */
    u8 acorn_level;      /* 0x0c: overlay 87's level in that table, up to PLAYER_FIELD_2416_ACORN_LEVEL_MAX */
    u8 resets;           /* 0x0d: up to PLAYER_FIELD_2416_RESETS_MAX */
    u8 fashion_score;    /* 0x0e: up to PLAYER_FIELD_2416_FASHION_SCORE_MAX */
    u8 claims;           /* 0x0f */
    u8 flags;            /* 0x10 */
} PlayerField2416;

#define PLAYER_FIELD_2416_FASHION_SCORE_MAX 100
#define PLAYER_FIELD_2416_CLAIMS_MAX 0xff
#define PLAYER_FIELD_2416_FIREWORKS_GIFTS_MAX 10

/* PlayerField2416.flags */
#define PLAYER_FIELD_2416_FISHING 0x01
#define PLAYER_FIELD_2416_INSECTS 0x02
#define PLAYER_FIELD_2416_FIREWORKS_GIFTS_SHIFT 2
#define PLAYER_FIELD_2416_FIREWORKS_GIFTS_MASK 0x3c
#define PLAYER_FIELD_2416_GARDENING 0x40

void PlayerField2416_RaiseClaims(PlayerField2416 *field);
int PlayerField2416_Claims(PlayerField2416 *field);
void PlayerField2416_SetToday(PlayerField2416 *field);
PlayerField2416 *PlayerField2416_Date(PlayerField2416 *field);
void PlayerField2416_ClearGardening(PlayerField2416 *field);
void PlayerField2416_SetGardening(PlayerField2416 *field);
int PlayerField2416_Gardening(PlayerField2416 *field);
void PlayerField2416_ClearAcorns(PlayerField2416 *field);
void PlayerField2416_ClearFireworksGifts(PlayerField2416 *field);
void PlayerField2416_RaiseFireworksGifts(PlayerField2416 *field);
int PlayerField2416_FireworksGifts(PlayerField2416 *field);
void PlayerField2416_SetInsects(PlayerField2416 *field, u32 entered);
int PlayerField2416_Insects(PlayerField2416 *field);
void PlayerField2416_SetFishing(PlayerField2416 *field, int entered);
int PlayerField2416_Fishing(PlayerField2416 *field);
void PlayerField2416_AddFashionScore(PlayerField2416 *field, u8 amount);

/* The counts at 0x09 to 0x0d: the coffees, the haircuts, the acorn festival's points and level,
 * and the visits after a reset (raised in scene 6, StateBlock_StartMode2). */
#define PLAYER_FIELD_2416_COFFEES_MAX 15
#define PLAYER_FIELD_2416_HAIRCUTS_MAX 16
#define PLAYER_FIELD_2416_ACORN_POINTS_MAX 0xff
#define PLAYER_FIELD_2416_ACORN_LEVEL_MAX 12
#define PLAYER_FIELD_2416_RESETS_MAX 6

int PlayerField2416_FashionScore(PlayerField2416 *field);
void PlayerField2416_RaiseResets(PlayerField2416 *field);
int PlayerField2416_Resets(PlayerField2416 *field);
void PlayerField2416_RaiseAcornLevel(PlayerField2416 *field);
int PlayerField2416_AcornLevel(PlayerField2416 *field);
void PlayerField2416_AddAcornPoints(PlayerField2416 *field, int amount);
int PlayerField2416_AcornPoints(PlayerField2416 *field);
void PlayerField2416_AddHaircuts(PlayerField2416 *field, int amount);
int PlayerField2416_Haircuts(PlayerField2416 *field);
void PlayerField2416_SetCoffees(PlayerField2416 *field, u8 count);
int PlayerField2416_Coffees(PlayerField2416 *field);
void PlayerField2416_SetTailorTalkDays(PlayerField2416 *field, int value);
int PlayerField2416_TailorTalkDays(PlayerField2416 *field);
void PlayerField2416_SetJobEndToday(PlayerField2416 *field);
int PlayerField2416_JobEndDate(PlayerField2416 *field);
void PlayerField2416_Reset(PlayerField2416 *field);
void PlayerField2416_Destruct(PlayerField2416 *field);
void PlayerField2416_Construct(PlayerField2416 *field);

#endif
