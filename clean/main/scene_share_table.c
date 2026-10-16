/* The persons' entries behind the shared records of a session (scene_share_table.h). */
#include "scene_share_table.h"

#include "acre_tile.h"
#include "clean.h"
#include "npc_id.h"
#include "packed_bytes.h"
#include "scene_query.h"
#include "session.h"
#include "session_record.h"
#include "spawner.h"
#include "town_villager.h"
#include "villager_home.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_town.h"

static_assert(sizeof(SceneShareEntry) == 0x1e, "SceneShareEntry size");

extern NetSession *data_020ccf94;  /* the session */
extern VillagerTown data_021e5a2c; /* the town's villagers */

/* The entries of the villagers and of the other persons, and the flag set when a villager's
 * record is written. */
extern SceneShareEntry data_021d213c[SCENE_SHARE_TABLE_E_COUNT];
extern SceneShareEntry data_021d232c[SCENE_SHARE_TABLE_D_COUNT];
extern u8 data_021d2128;

/* The spawner's request (spawner.h). */
extern SpawnerRequest data_020e1ca8;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The first shared record of each kind of person. */
#define SCENE_SHARE_TABLE_RECORDS_E 12
#define SCENE_SHARE_TABLE_RECORDS_D 32

#define SCENE_SHARE_TABLE_ANGLE_SIZE 2
#define SCENE_SHARE_TABLE_NOTE_SIZE 15 /* note_kind, note_priority and note */

/* A villager's house: its tile plus (1, 2) is the tile before its door. */
#define SCENE_SHARE_TABLE_DOOR_X 1
#define SCENE_SHARE_TABLE_DOOR_Z 2

static int scene_share_table_kind(const u16 *person)
{
    return (*person & 0xf000) >> 12;
}

static u32 scene_share_table_index(const u16 *person)
{
    return *person & SCENE_SHARE_TABLE_INDEX_MASK;
}

/* The persons of one kind (`count` of them, codes `kind_code` | index) that the session's
 * records place in `scene`: one held by no system gets no owner and no holder, one held by
 * this system and run by another is taken over (this system runs it, none holds it); either
 * is sent with value 1. */
static void scene_share_table_claim(const NetSession *session, u16 kind_code, u32 count, int scene)
{
    for (u32 i = 0; i < count; i++) {
        u16 person = (u16) ((i & SCENE_SHARE_TABLE_INDEX_MASK) | kind_code);
        SceneShareEntry *record = SceneShareTable_SharedRecord(&person);
        if (record == NULL) {
            continue;
        }
        u8 record_scene;
        PackedBytes_SplitScene(&record->scene, &record_scene, NULL);
        if (record_scene != scene) {
            continue;
        }
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShareTable_ReadSlots(&owner, &holder, &person) == 0) {
            continue;
        }
        if (holder >= SCENE_SHARE_NO_SLOT) {
            SceneShareTable_SetSlotsAndSend(1, SCENE_SHARE_NO_SLOT, SCENE_SHARE_NO_SLOT, &person);
        } else {
            int local_slot = session->local_slot;
            if (holder == local_slot && holder != owner) {
                SceneShareTable_SetSlotsAndSend(1, local_slot, SCENE_SHARE_NO_SLOT, &person);
            }
        }
    }
}

/* func_02084f8c: the villagers, then the other persons, that the session's records place in
 * the scene shown, claimed (scene_share_table_claim). The session is the one on entry. */
void SceneShareTable_ClaimScenePersons(void)
{
    int scene = SceneQuery_Current();
    const NetSession *session = data_020ccf94;
    scene_share_table_claim(session, SCENE_SHARE_TABLE_CODE_E, SCENE_SHARE_TABLE_E_COUNT, scene);
    scene_share_table_claim(session, SCENE_SHARE_TABLE_CODE_D, SCENE_SHARE_TABLE_D_COUNT, scene);
}
CLEAN_AS(func_02084f8c, SceneShareTable_ClaimScenePersons)

/* func_020850b8: the owner and holder of the person's shared record, when it has one in use;
 * else 0 and nothing written. */
int SceneShareTable_ReadSlots(int *owner, int *holder, u16 *person)
{
    SceneShareEntry *record = SceneShareTable_SharedRecord(person);
    if (record == NULL || record->in_use == 0) {
        return 0;
    }
    *owner = record->owner;
    *holder = record->holder;
    return 1;
}
CLEAN_AS(func_020850b8, SceneShareTable_ReadSlots)

/* func_020850e8: the owner and holder into the person's entry; while this system's slot is
 * taken, the person's shared record is updated with `value`'s address. */
void SceneShareTable_SetSlotsAndSend(int value, int owner, int holder, u16 *person)
{
    SceneShareTable_SetSlots(person, owner, holder);
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) == 0) {
        return;
    }
    int kind = scene_share_table_kind(person);
    int index = (int) scene_share_table_index(person);
    if (kind == SCENE_SHARE_KIND_E) {
        SessionRecord_Update(index + SCENE_SHARE_TABLE_RECORDS_E, &value, 0, 0);
    } else if (kind == SCENE_SHARE_KIND_D) {
        SessionRecord_Update(index + SCENE_SHARE_TABLE_RECORDS_D, &value, 0, 0);
    }
}
CLEAN_AS(func_020850e8, SceneShareTable_SetSlotsAndSend)

/* func_02085148: the person's record in the session's table, or NULL (another kind, no table,
 * or an index out of range). */
SceneShareEntry *SceneShareTable_SharedRecord(u16 *person)
{
    int kind = scene_share_table_kind(person);
    if (kind == SCENE_SHARE_KIND_E) {
        return SceneShareTable_SharedRecordE(person);
    }
    if (kind == SCENE_SHARE_KIND_D) {
        return SceneShareTable_SharedRecordD(person);
    }
    return NULL;
}
CLEAN_AS(func_02085148, SceneShareTable_SharedRecord)

/* func_02085174: the owner and holder into the person's entry, and the entry put in use.
 * Whether the person has an entry. */
int SceneShareTable_SetSlots(u16 *person, int owner, int holder)
{
    int kind = scene_share_table_kind(person);
    if (kind == SCENE_SHARE_KIND_E) {
        return SceneShareTable_SetSlotsE(person, (u8) owner, (u8) holder);
    }
    if (kind == SCENE_SHARE_KIND_D) {
        return SceneShareTable_SetSlotsD(person, (u8) owner, (u8) holder);
    }
    return 0;
}
CLEAN_AS(func_02085174, SceneShareTable_SetSlots)

/* func_020851a0: the scene, place, angle, note and extra bytes into the person's entry, and the
 * entry put in use. Whether the person has an entry. */
int SceneShareTable_SetPlace(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra)
{
    int kind = scene_share_table_kind(person);
    if (kind == SCENE_SHARE_KIND_E) {
        return SceneShareTable_SetPlaceE(person, scene, position, angle, note, extra);
    }
    if (kind == SCENE_SHARE_KIND_D) {
        return SceneShareTable_SetPlaceD(person, scene, position, angle, note, extra);
    }
    return 0;
}
CLEAN_AS(func_020851a0, SceneShareTable_SetPlace)

/* func_020851e0: the shared record of person 0xd<index> (record 32 + index), or NULL for an
 * index of 38 or more. The kind is not checked. */
SceneShareEntry *SceneShareTable_SharedRecordD(const u16 *person)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_D_COUNT) {
        return NULL;
    }
    return (SceneShareEntry *) Session_GetRecord(data_020ccf94, (int) index + SCENE_SHARE_TABLE_RECORDS_D);
}
CLEAN_AS(func_020851e0, SceneShareTable_SharedRecordD)

/* func_0208520c (the writer of records 32-69): the entry of record `id` put in use and copied
 * into the record (as many bytes as the record has). Nothing for another id. */
void SceneShareTable_WriteRecordD(u8 *record, int id)
{
    u32 index = (u32) id - SCENE_SHARE_TABLE_RECORDS_D;
    if (index >= SCENE_SHARE_TABLE_D_COUNT) {
        return;
    }
    SceneShareEntry *entry = &data_021d232c[index];
    entry->in_use = 1;
    MI_CpuCopy8(entry, record, SessionRecord_GetSize((u32) id));
}
CLEAN_AS(func_0208520c, SceneShareTable_WriteRecordD)

/* An entry put in use with the owner and holder given. */
static void scene_share_table_set_slots(SceneShareEntry *entry, u8 owner, u8 holder)
{
    entry->in_use = 1;
    entry->owner = owner;
    entry->holder = holder;
}

/* func_02085244: the owner and holder into the entry of person 0xd<index>; 0 for an index of
 * 38 or more. The kind is not checked. */
int SceneShareTable_SetSlotsD(u16 *person, u8 owner, u8 holder)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_D_COUNT) {
        return 0;
    }
    scene_share_table_set_slots(&data_021d232c[index], owner, holder);
    return 1;
}
CLEAN_AS(func_02085244, SceneShareTable_SetSlotsD)

/* An entry put in use with a scene (number 0), the x and z of `position`, the low two bytes
 * of `angle`, the note's 15 bytes and the four extra bytes. */
static void scene_share_table_set_place(SceneShareEntry *entry, int scene, const Vec3 *position, int angle, const void *note,
                                        const void *extra)
{
    entry->in_use = 1;
    PackedBytes_JoinScene(&entry->scene, (u8) scene, 0);
    PackedBytes_PackPoint(entry->place, position->x, position->z);
    /* QUIRK: the angle is handed over as an int and its first two bytes in memory copied (the
     * low half on the little-endian DS). */
    MI_CpuCopy8(&angle, entry->angle, SCENE_SHARE_TABLE_ANGLE_SIZE);
    MI_CpuCopy8(note, &entry->note_kind, SCENE_SHARE_TABLE_NOTE_SIZE);
    MI_CpuCopy8(extra, entry->extra, SCENE_SHARE_EXTRA_SIZE);
}

/* func_02085278: the place and the rest (scene_share_table_set_place) into the entry of person
 * 0xd<index>; 0 for an index of 38 or more. The kind is not checked. */
int SceneShareTable_SetPlaceD(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_D_COUNT) {
        return 0;
    }
    scene_share_table_set_place(&data_021d232c[index], scene, position, angle, note, extra);
    return 1;
}
CLEAN_AS(func_02085278, SceneShareTable_SetPlaceD)

/* func_020852e4: the shared record of villager 0xe<index> (record 12 + index), or NULL for an
 * index of 8 or more. The kind is not checked. */
SceneShareEntry *SceneShareTable_SharedRecordE(const u16 *person)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_E_COUNT) {
        return NULL;
    }
    return (SceneShareEntry *) Session_GetRecord(data_020ccf94, (int) index + SCENE_SHARE_TABLE_RECORDS_E);
}
CLEAN_AS(func_020852e4, SceneShareTable_SharedRecordE)

/* func_02085310 (the writer of records 12-19): the entry of record `id` put in use and copied
 * into the record, and data_021d2128 set. Nothing for another id. */
void SceneShareTable_WriteRecordE(u8 *record, int id)
{
    u32 index = (u32) id - SCENE_SHARE_TABLE_RECORDS_E;
    if (index >= SCENE_SHARE_TABLE_E_COUNT) {
        return;
    }
    SceneShareEntry *entry = &data_021d213c[index];
    entry->in_use = 1;
    MI_CpuCopy8(entry, record, SessionRecord_GetSize((u32) id));
    data_021d2128 = 1;
}
CLEAN_AS(func_02085310, SceneShareTable_WriteRecordE)

/* func_02085350 (the filler of records 12-19): the record written, then the villager's entry
 * of the state table, when it has one, gets byte 0x18 and its counter cleared. */
void SceneShareTable_FillRecordE(u8 *record, int id)
{
    SceneShareTable_WriteRecordE(record, id);
    VillagerState *state = VillagerTown_StateAt(id - SCENE_SHARE_TABLE_RECORDS_E);
    if (state != NULL) {
        VillagerState_SetByte18(state, 0);
        VillagerState_SetCounter(state, 0);
    }
}
CLEAN_AS(func_02085350, SceneShareTable_FillRecordE)

/* func_0208537c: the owner and holder into the entry of villager 0xe<index>; 0 for an index of
 * 8 or more. The kind is not checked. */
int SceneShareTable_SetSlotsE(u16 *person, u8 owner, u8 holder)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_E_COUNT) {
        return 0;
    }
    scene_share_table_set_slots(&data_021d213c[index], owner, holder);
    return 1;
}
CLEAN_AS(func_0208537c, SceneShareTable_SetSlotsE)

/* func_020853b0: the place and the rest (scene_share_table_set_place) into the entry of
 * villager 0xe<index>; 0 for an index of 8 or more. The kind is not checked. */
int SceneShareTable_SetPlaceE(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra)
{
    u32 index = scene_share_table_index(person);
    if (index >= SCENE_SHARE_TABLE_E_COUNT) {
        return 0;
    }
    scene_share_table_set_place(&data_021d213c[index], scene, position, angle, note, extra);
    return 1;
}
CLEAN_AS(func_020853b0, SceneShareTable_SetPlaceE)

/* func_02085e18: the villagers' entries cleared, then each of the town's villagers put in use
 * at the tile before its house's door, in scene 0. */
void SceneShareTable_PlaceVillagersAtHome(void)
{
    MI_CpuFill8(data_021d213c, 0, sizeof(data_021d213c));
    for (int i = 0; i < SCENE_SHARE_TABLE_E_COUNT; i++) {
        SceneShareEntry *entry = &data_021d213c[i];
        u8 *villager = VillagerRoster_At(&data_021e5a2c, i);
        if (villager == NULL || NpcId_IsValid(TownVillager_NpcId(villager)) == 0) {
            continue;
        }
        Vec3 position = {0, 0, 0};
        const VillagerPlot *home = VillagerHome_Tile(villager);
        AcreTile_TileCentre(&position, (u32) (home->x + SCENE_SHARE_TABLE_DOOR_X), (u32) (home->z + SCENE_SHARE_TABLE_DOOR_Z));
        PackedBytes_PackPoint(entry->place, position.x, position.z);
        PackedBytes_JoinScene(&entry->scene, 0, 0);
        entry->in_use = 1;
    }
}
CLEAN_AS(func_02085e18, SceneShareTable_PlaceVillagersAtHome)

/* func_02085e94: data_021d2128 and every entry cleared, and the spawner's request cleared. */
void SceneShareTable_Reset(void)
{
    data_021d2128 = 0;
    MI_CpuFill8(data_021d213c, 0, sizeof(data_021d213c));
    MI_CpuFill8(data_021d232c, 0, sizeof(data_021d232c));
    Spawner_ClearRequest(&data_020e1ca8);
}
CLEAN_AS(func_02085e94, SceneShareTable_Reset)
