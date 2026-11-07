/* Small table lookups the game keeps together: star signs by birthday, a window of the night
 * for each of six personalities, and records for the 38 special characters (person codes of
 * kind 0xd, NPC_CODE_KIND_SPECIAL). */
#ifndef CLEAN_MAIN_LOOKUPS_H
#define CLEAN_MAIN_LOOKUPS_H

#include "types.h"

/* A time window, both ends excluded (NpcLookup_IsInNightWindow, func_020821d4, tests the clock against it). */
typedef struct NightWindow {
    u8 start_hour;
    u8 start_minute;
    u8 end_hour;
    u8 end_minute;
} NightWindow;

/* A birthday as the game stores it: month first. */
typedef struct MonthDay {
    u8 month;
    u8 day;
} MonthDay;

/* The star signs in the order of the game's table, each ending on its last day. */
enum StarSign {
    STAR_SIGN_CAPRICORN, /* to 19 January, and from 22 December */
    STAR_SIGN_AQUARIUS,
    STAR_SIGN_PISCES,
    STAR_SIGN_ARIES,
    STAR_SIGN_TAURUS,
    STAR_SIGN_GEMINI,
    STAR_SIGN_CANCER,
    STAR_SIGN_LEO,
    STAR_SIGN_VIRGO,
    STAR_SIGN_LIBRA,
    STAR_SIGN_SCORPIO,
    STAR_SIGN_SAGITTARIUS,
};

/* An item code: the kind in the top four bits, an index in the rest. */
typedef u16 ItemCode;

const NightWindow *Lookups_NightWindow(u32 personality);
u32 Lookups_StarSignOf(const MonthDay *birthday);
u32 Lookups_StarSign(u32 month, u32 day);
u8 Lookups_SlotIndex(const u8 *pair);
const u8 *Lookups_SpecialNpcRecord(const ItemCode *item);
int Lookups_SpecialNpcSortKey(const ItemCode *item);

#endif
