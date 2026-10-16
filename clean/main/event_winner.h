/* A record of who won one of the town's events and with what (0x48 bytes; data_021f3aa4 is
 * one, read by the villagers' talk, villager_talk_lines.c): the winner, a player or a villager,
 * a second villager, an item and its size, and the day of the record.
 *
 * Its functions here judge one event by the items 0-30 planted near homes
 * (EventWinner_JudgeGardens), give the size of a creature caught (EventWinner_RandomSize) and
 * start the record afresh when its day is past (EventWinner_ExpireForEvent,
 * EventWinner_ResetIfNotToday); the functions after 0x0208675c set its parts. */
#ifndef CLEAN_MAIN_EVENT_WINNER_H
#define CLEAN_MAIN_EVENT_WINNER_H

#include "acre_map.h"
#include "calendar.h"
#include "design.h"
#include "npc_id.h"
#include "types.h"

typedef struct EventWinner {
    DesignCreator player; /* 0x00: the winning player (cleared when a villager won) */
    NpcId villager;       /* 0x1e: the winning villager (cleared when a player won) */
    NpcId npc_2e;         /* 0x2e */
    u16 item;             /* 0x3e */
    int size;             /* 0x40 */
    Date date;            /* 0x44: when the record was started; its last byte is cleared then */
} EventWinner;

/* A tile's world coordinates, as EventWinner_IsNearAttr4 takes them. */
typedef struct EventWinnerTile {
    int x;
    int z;
} EventWinnerTile;

/* An item's kind for the judging (EventWinner_ItemKind): items 0-26 are kinds 0-26 and items
 * 28-30 kinds 27-29; item 27 and the rest count for nothing. */
#define EVENT_WINNER_ITEM_KINDS 30

void EventWinner_JudgeGardens(EventWinner *record);
int EventWinner_ScoreAroundBuilding(EventWinner *record, AcreMap *map);
int EventWinner_IsNearAttr4(const EventWinnerTile *tile);
int EventWinner_ScoreAroundHome(u8 *villager, AcreMap *map);
int EventWinner_CountBits(u32 bits);
int EventWinner_ItemKind(u32 *kind, const u16 *item);
fx32 EventWinner_RandomSize(u16 *item);
void EventWinner_ExpireForEvent(EventWinner *record, int event);
void EventWinner_ResetIfNotToday(EventWinner *record, int mode);
int EventWinner_Size(const EventWinner *record);
void EventWinner_SetSize(EventWinner *record, int size);
void EventWinner_GetItem(u16 *item, const EventWinner *record);
void EventWinner_SetItem(EventWinner *record, const u16 *item);
NpcId *EventWinner_Npc2E(EventWinner *record);

#endif
