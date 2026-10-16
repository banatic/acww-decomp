/* The dated events of a player's year: four kinds of five events each, every one starting on
 * the n-th weekday of a month (data_020d0704) and running through up to seven parts of a few
 * days each (data_020d07a4). An event's part is named by one byte (DayEvent): its kind in
 * bits 0-1, the event in bits 2-4 and the part in bits 5-7.
 *
 * A player's record keeps at 0x2427 (PlayerRecord_Field2427) the part it reached last and the
 * day it did (DayEventMark). A part counts for the player (DayEvents_PlayerHas) when it is the
 * marked one on its marked day (or with no day marked), when it follows the marked one, or,
 * for an event's first part, when the player qualifies for the kind: kind 0 by its record's
 * flag 6, kind 1 by flag 8 or a complete museum record, kind 2 by byte 8 of its object at
 * 0x2416 being 15, kind 3 by Nook's store being at its last level. */
#ifndef CLEAN_MAIN_DAY_EVENTS_H
#define CLEAN_MAIN_DAY_EVENTS_H

#include "types.h"

#define DAY_EVENTS_KINDS 4
#define DAY_EVENTS_PER_KIND 5
#define DAY_EVENTS_PARTS 7

#define DAY_EVENT_KIND(event) ((event) & 3)
#define DAY_EVENT_INDEX(event) (((event) >> 2) & 7)
#define DAY_EVENT_PART(event) (((event) >> 5) & 7)
#define DAY_EVENT_MAKE(kind, index, part) ((u8) (((kind) & 3) | (((index) & 7) << 2) | (((part) & 7) << 5)))

/* What DayEvents_ClearMark leaves in the mark's event byte. */
#define DAY_EVENT_NONE 0xff

/* The player record's mark (5 bytes at 0x2427). */
typedef struct DayEventMark {
    u8 event; /* a DayEvent byte */
    u8 day;   /* the date it was reached; all 0 for none */
    u8 month;
    u8 year;
    u8 unused;
} DayEventMark;

int DayEvents_PlayerHas(int year, int month, int day, u8 *event);
int DayEvents_Find(int year, u8 month, u8 day, u8 *event);
u8 *DayEvents_MarkDate(DayEventMark *mark);
void DayEvents_SetMark(DayEventMark *mark, const u8 *event);
void DayEvents_MarkEvent(const DayEventMark *mark, u8 *event);
void DayEvents_ClearMark(DayEventMark *mark);
void DayEvents_MarkDestruct(DayEventMark *mark);
void DayEvents_MarkConstruct(DayEventMark *mark);

#endif
