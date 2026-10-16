/* Overlay 098: the pockets scene's (ov096/pockets_screen.h) code for when data_020e54a8 is 0,
 * the case in which main's player messages 1, 2 and 5 are taken (main/player_messages.h) and
 * the town map (data_021c80bc, func_0204f5e0) is read. ov097 (ov097/pockets_room.h) stands in
 * for it otherwise.
 *
 * It adds choice rows for a grid item (PocketsTown_AddItemRows) and a letter of kind 4
 * (PocketsTown_AddLetterRows), and runs their actions and the sub states they lead to:
 *   action 21 -> sub state 0x2c  an insect (items 0x12b0-0x12e7) let go with a random turn
 *   action 22, 23 -> 0x2d, 0x2e  a request at the tile ahead of the player (or a drop request)
 *   action 24 -> sub state 0x30  a fish (items 0x12e8-0x131f) placed at the point ahead
 *   action 25 -> 0x33, 0x34      the letter placed at the point ahead and passed on
 *   action 33 -> 0x35-0x39       an insect or a fish held up for show, then put away
 * In a linked session each of these is told to the other consoles by a player message. */
#ifndef CLEAN_OV098_POCKETS_TOWN_H
#define CLEAN_OV098_POCKETS_TOWN_H

#include "ov096/pockets_screen.h"
#include "types.h"

/* One step on the town's tile grid: the neighbouring tile in one of 16 directions. */
typedef struct PocketsTownStep {
    s32 dx;
    s32 dz;
} PocketsTownStep;

void PocketsTown_WaitShowEnd(PocketsScreen *self);
void PocketsTown_WaitPutAway(PocketsScreen *self);
void PocketsTown_WaitDismissShow(PocketsScreen *self);
void PocketsTown_WaitShowing(PocketsScreen *self);
void PocketsTown_ShowItem(PocketsScreen *self);
void PocketsTown_ActionShowItem(PocketsScreen *self);
void PocketsTown_PassLetter(PocketsScreen *self);
void PocketsTown_WaitLetterPlaced(PocketsScreen *self);
void PocketsTown_WaitLetterPlacing(PocketsScreen *self);
void PocketsTown_ActionPlaceLetter(PocketsScreen *self);
void PocketsTown_ActionTileOrDrop(PocketsScreen *self);
void PocketsTown_StartTileState61(PocketsScreen *self);
void PocketsTown_WaitTileRequest(PocketsScreen *self);
void PocketsTown_ActionTile(PocketsScreen *self);
int PocketsTown_FindTileAhead(PocketsScreen *self);
PocketsTownStep *PocketsTown_DirectionStep(int unused, int angle);
void PocketsTown_SendTurn(PocketsScreen *self, int kind, int turn);
int PocketsTown_LetInsectGo(PocketsScreen *self);
int PocketsTown_ActionInsect(PocketsScreen *self);
void PocketsTown_SendPlaceId(PocketsScreen *self, int id);
void PocketsTown_SendPoint(PocketsScreen *self, char id, char type);
void PocketsTown_PlaceFish(PocketsScreen *self);
void PocketsTown_ActionFish(PocketsScreen *self);
int PocketsTown_FindPointAhead(PocketsScreen *self, int for_letter);
void PocketsTown_AddLetterRows(PocketsScreen *self);
void PocketsTown_AddItemRows(PocketsScreen *self, u16 item);
int PocketsTown_CanUseItem(PocketsScreen *self, unsigned int item);

#endif
