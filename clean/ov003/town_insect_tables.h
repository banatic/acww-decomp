/* The global tables of the town's insects (town_insect.h) as objects: their destructors, and the
 * table that shares the town insects with the session.
 *
 * While this system holds the scene, each town insect's kind, target point and byte 0x254 are
 * kept in an entry of data_ov003_02262aa8 (TownInsectTables_PublishRecord) and sent as session
 * record 0x18 + its index (main/session_record.h; written by TownInsectTables_WriteRecord); the
 * other systems read them back from the session (TownInsectTables_ReadRecord). */
#ifndef CLEAN_OV003_TOWN_INSECT_TABLES_H
#define CLEAN_OV003_TOWN_INSECT_TABLES_H

#include "autoload_2/vector.h"
#include "ov003/town_insect.h"
#include "types.h"

/* The first session record of the town insects. */
#define TOWN_INSECT_TABLES_FIRST_RECORD 0x18

/* An entry of data_ov003_02262aa8, one per town insect. */
typedef struct TownInsectTablesEntry {
    Vec3 point; /* the insect's target; x and z are sent */
    s8 kind;
    u8 byte254; /* TownInsect.unk_254 */
    u8 unk_0e[2];
} TownInsectTablesEntry;

void TownInsectTables_DestroyHeld(void *object);
void TownInsectTables_DestroyEvent(void *object);
void TownInsectTables_DestroyTown(void *object);
int TownInsectTables_ReadRecord(TownInsectProcess *process, int index, s8 *kind, int *x, int *z, u8 *byte254);
void TownInsectTables_WriteRecord(u8 *record, int id, void *unused);
int TownInsectTables_PublishRecord(TownInsectProcess *process, int index, int kind, const Vec3 *point, u8 byte254, int unused);
void TownInsectTables_DestroyProcessPart(TownInsectProcess *process);
void TownInsectTables_ConstructProcessPart(TownInsectProcess *process);
void TownInsectTables_DestroyEntries(void);
void TownInsectTables_DestroyEntry(void);
void TownInsectTables_ConstructEntry(void);

#endif
