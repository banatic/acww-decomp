/* The town's objects of codes 0x5000-0x5021: the buildings and special characters that
 * overlay 9's scene actors stand for (ov009/scene_actor.h), each with a record of ten bytes in
 * main's table data_020d1f24 (SceneActorRecord) and an index 0-0x21 (func_020b3f58: the code's
 * low bits, the four variants 0x500d-0x5010 and the seven 0x5014-0x501a each counted as their
 * first).
 *
 * Main keeps a visit record per object (data_021f4bac, a byte each): in the low four bits the
 * session slots of the players visiting it, in the high four the answer to the last request
 * to visit (TOWN_OBJECTS_ANSWER_*, 0 while there is none). Slot 0's system, or a system
 * playing alone, decides: a request of its own is answered at once (TownObjects_RequestVisit),
 * another system's comes as message 0x23 and is answered with the same message
 * (TownObjects_OnVisitMessage); a player leaving clears its bit, through message 0x24 from the
 * others (TownObjects_Leave). Message 0x22 carries a scene actor's new mode to the other
 * systems (TownObjects_SetActorMode, TownObjects_OnModeMessage).
 *
 * The scenes inside the objects are numbered too: the table data_020d1ebc gives each scene's
 * object code. */
#ifndef CLEAN_MAIN_TOWN_OBJECTS_H
#define CLEAN_MAIN_TOWN_OBJECTS_H

#include "ov009/scene_actor.h"
#include "types.h"

#define TOWN_OBJECTS_FIRST 0x5000
#define TOWN_OBJECTS_LAST 0x5021
#define TOWN_OBJECTS_COUNT 0x22

/* The answers to a request to visit. */
#define TOWN_OBJECTS_ANSWER_LET_IN 1 /* the visitor's bit is set */
#define TOWN_OBJECTS_ANSWER_FULL 2   /* more visitors than byte 9 of the object's record */
#define TOWN_OBJECTS_ANSWER_HOUSE 3  /* a villager's house (TownObjects_HouseState2) with nobody in */

void TownObjects_MarkFootprints(void);
int TownObjects_VisitorsHere(void);
int TownObjects_VisitorsInScene(int scene);
int TownObjects_VisitorMask(int scene);
void TownObjects_ClearExtraVisitors(void);
void TownObjects_SetExtraVisitors(void);
u8 TownObjects_ExtraVisitors(void);
void TownObjects_Leave(int code, int slot);
int TownObjects_VisitAnswer(u16 code);
void TownObjects_RequestVisit(u32 code);
void TownObjects_ResetVisits(void);
void TownObjects_OnLeftMessage(const u8 *index, u32 slot);
void TownObjects_OnVisitMessage(u8 *payload, int slot);
void TownObjects_OnModeMessage(const u16 *payload);
int TownObjects_HouseState2(int code);
int TownObjects_VillagerState2(int villager);
int TownObjects_SetActorMode(SceneActor *actor, unsigned int mode);
int TownObjects_AtKeptTile(void);
void TownObjects_KeepAtKeptTile(void);

#endif
