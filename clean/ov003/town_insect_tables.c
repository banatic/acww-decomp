/* The global tables of the town's insects as objects (town_insect_tables.h). */
#include "town_insect_tables.h"

#include "clean.h"
#include "main/link_global.h"
#include "main/packed_bytes.h"
#include "main/session.h"
#include "main/session_record.h"

static_assert(sizeof(TownInsect) == 0x25c, "an insect");
static_assert(sizeof(TownInsectTablesEntry) == 0x10, "an entry of the shared table");
static_assert(offsetof(TownInsectTablesEntry, kind) == 0x0c, "TownInsectTablesEntry.kind");

/* The session (session.h). */
extern NetSession *data_020ccf94;
/* The three tables of insects (town_insect.h). */
extern TownInsect data_ov003_02260994[TOWN_INSECT_EVENT_COUNT];
extern TownInsect data_ov003_02260e4c[TOWN_INSECT_HELD_COUNT];
extern TownInsect data_ov003_022617bc[TOWN_INSECT_TOWN_COUNT];
/* What the town insects share with the session, one entry per town insect. */
extern TownInsectTablesEntry data_ov003_02262aa8[TOWN_INSECT_TOWN_COUNT];

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The destructors handed to __cxa_vec_cleanup: an insect's (TownInsect_Destruct) and an
 * entry's (TownInsectTables_DestroyEntry). */
extern void func_ov003_0222d520(void *insect);
extern void func_ov003_02235d80(void *entry);

/* func_ov003_02235bc8: the global destructor of the held insects' table. */
void TownInsectTables_DestroyHeld(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_02260e4c, TOWN_INSECT_HELD_COUNT, sizeof(TownInsect), func_ov003_0222d520);
}
CLEAN_AS(func_ov003_02235bc8, TownInsectTables_DestroyHeld)

/* func_ov003_02235bec: the global destructor of the event insects' table. */
void TownInsectTables_DestroyEvent(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_02260994, TOWN_INSECT_EVENT_COUNT, sizeof(TownInsect), func_ov003_0222d520);
}
CLEAN_AS(func_ov003_02235bec, TownInsectTables_DestroyEvent)

/* func_ov003_02235c10: the global destructor of the town insects' table. */
void TownInsectTables_DestroyTown(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_022617bc, TOWN_INSECT_TOWN_COUNT, sizeof(TownInsect), func_ov003_0222d520);
}
CLEAN_AS(func_ov003_02235c10, TownInsectTables_DestroyTown)

/* func_ov003_02235c34: what the session says of town insect `index`, when this system does not
 * hold the scene and the session is linked: the x and z of its point from its record, and,
 * when z is above 0, its kind and byte 0x254, and 1 is returned; else 0. */
int TownInsectTables_ReadRecord(TownInsectProcess *process, int index, s8 *kind, int *x, int *z, u8 *byte254)
{
    (void) process;
    if (LinkGlobal_HoldsScene() == 0) {
        NetSession *session = data_020ccf94;
        if (Session_IsLinked(session) != 0) {
            u8 *record = Session_GetRecord(session, index + TOWN_INSECT_TABLES_FIRST_RECORD);
            if (record != NULL) {
                PackedBytes_UnpackPoint(record, (u32 *) x, (u32 *) z);
                if (*z > 0) {
                    *kind = (s8) record[5];
                    *byte254 = record[6];
                    return 1;
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_02235c34, TownInsectTables_ReadRecord)

/* func_ov003_02235c94: the writer of session records 0x18-0x1f: the x and z of the entry's
 * point packed (PackedBytes_PackPoint), then its kind and byte 0x254, copied to `record` for the
 * record's size. */
void TownInsectTables_WriteRecord(u8 *record, int id, void *unused)
{
    (void) unused;
    u8 bytes[8] = {0};
    const TownInsectTablesEntry *entry = &data_ov003_02262aa8[id - TOWN_INSECT_TABLES_FIRST_RECORD];
    PackedBytes_PackPoint(bytes, entry->point.x, entry->point.z);
    bytes[5] = (u8) entry->kind;
    bytes[6] = entry->byte254;
    MI_CpuCopy8(bytes, record, SessionRecord_GetSize((u32) id));
}
CLEAN_AS(func_ov003_02235c94, TownInsectTables_WriteRecord)

/* func_ov003_02235ce8: town insect `index` shared with the session, when this system holds the
 * scene and the session is linked: its record sent (SessionRecord_Update), then its entry set to
 * `kind`, `point` and `byte254`, and 1 is returned; else 0.
 * QUIRK: the record is written from the entry before the entry takes the new values, so the
 * session hears of them on the next call. The object handed to SessionRecord_Update is the
 * address of the unused last parameter; the writer does not read it. */
int TownInsectTables_PublishRecord(TownInsectProcess *process, int index, int kind, const Vec3 *point, u8 byte254, int unused)
{
    (void) process;
    if (LinkGlobal_HoldsScene() != 0 && Session_IsLinked(data_020ccf94) != 0) {
        SessionRecord_Update(index + TOWN_INSECT_TABLES_FIRST_RECORD, &unused, 0, 0);
        TownInsectTablesEntry *entry = &data_ov003_02262aa8[index];
        entry->kind = (s8) kind;
        entry->point.x = point->x;
        entry->point.y = point->y;
        entry->point.z = point->z;
        entry->byte254 = byte254;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02235ce8, TownInsectTables_PublishRecord)

/* func_ov003_02235d58: the destructor of a member of the process (town_insect.h): nothing to
 * do. */
void TownInsectTables_DestroyProcessPart(TownInsectProcess *process)
{
    (void) process;
}
CLEAN_AS(func_ov003_02235d58, TownInsectTables_DestroyProcessPart)

/* func_ov003_02235d5c: the constructor of that member: nothing to do. */
void TownInsectTables_ConstructProcessPart(TownInsectProcess *process)
{
    (void) process;
}
CLEAN_AS(func_ov003_02235d5c, TownInsectTables_ConstructProcessPart)

/* func_ov003_02235d60: the global destructor of the shared table. */
void TownInsectTables_DestroyEntries(void)
{
    __cxa_vec_cleanup(data_ov003_02262aa8, TOWN_INSECT_TOWN_COUNT, sizeof(TownInsectTablesEntry), func_ov003_02235d80);
}
CLEAN_AS(func_ov003_02235d60, TownInsectTables_DestroyEntries)

/* func_ov003_02235d80: the destructor of an entry: nothing to do. */
void TownInsectTables_DestroyEntry(void) {}
CLEAN_AS(func_ov003_02235d80, TownInsectTables_DestroyEntry)

/* func_ov003_02235d84: the constructor of an entry: nothing to do. */
void TownInsectTables_ConstructEntry(void) {}
CLEAN_AS(func_ov003_02235d84, TownInsectTables_ConstructEntry)
