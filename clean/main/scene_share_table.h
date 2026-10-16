/* The persons' entries behind the shared records of a session (scene_share.h,
 * session_record.h): this system's own copy of each person's record, from which the record
 * writers copy into the session's table.
 *
 * A person is named by a code: its kind in the top four bits, an index in the rest.
 *   kind 0xe  the town's eight villagers (index 0-7): entries at data_021d213c, shared records
 *             12-19;
 *   kind 0xd  38 other persons (index 0-37): entries at data_021d232c, shared records 32-69.
 * Other kinds have no entry and no record. An entry is a SceneShareEntry (30 bytes): whether it
 * is in use, the slots of the system running the person and of the one holding it, its scene,
 * its place, angle, the 15 bytes of its motion's note and four extra bytes.
 *
 * Writing a villager's record (SceneShareTable_WriteRecordE) sets data_021d2128. */
#ifndef CLEAN_MAIN_SCENE_SHARE_TABLE_H
#define CLEAN_MAIN_SCENE_SHARE_TABLE_H

#include "autoload_2/vector.h"
#include "scene_share.h"
#include "types.h"

#define SCENE_SHARE_TABLE_E_COUNT 8
#define SCENE_SHARE_TABLE_D_COUNT 38

#define SCENE_SHARE_TABLE_CODE_E 0xe000 /* kind 0xe in the top four bits */
#define SCENE_SHARE_TABLE_CODE_D 0xd000
#define SCENE_SHARE_TABLE_INDEX_MASK 0x0fff

void SceneShareTable_ClaimScenePersons(void);
int SceneShareTable_ReadSlots(int *owner, int *holder, u16 *person);
void SceneShareTable_SetSlotsAndSend(int value, int owner, int holder, u16 *person);
SceneShareEntry *SceneShareTable_SharedRecord(u16 *person);
int SceneShareTable_SetSlots(u16 *person, int owner, int holder);
int SceneShareTable_SetPlace(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra);
SceneShareEntry *SceneShareTable_SharedRecordD(const u16 *person);
void SceneShareTable_WriteRecordD(u8 *record, int id);
int SceneShareTable_SetSlotsD(u16 *person, u8 owner, u8 holder);
int SceneShareTable_SetPlaceD(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra);
SceneShareEntry *SceneShareTable_SharedRecordE(const u16 *person);
void SceneShareTable_WriteRecordE(u8 *record, int id);
void SceneShareTable_FillRecordE(u8 *record, int id);
int SceneShareTable_SetSlotsE(u16 *person, u8 owner, u8 holder);
int SceneShareTable_SetPlaceE(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra);
void SceneShareTable_PlaceVillagersAtHome(void);
void SceneShareTable_Reset(void);

#endif
