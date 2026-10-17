/* Three processes of overlay 4 (0x50 bytes, the base process and nothing more) that set up the
 * scenes 0x23-0x29 (the ones with obj_etc_museum spots, etc_museum.h) when they are entered:
 *
 *   class 81  vtable data_ov004_0225672c, profile data_ov004_022566c0 (MuseumSetup_New), on the
 *             scene class of autoload_2 (data_020da13c);
 *   class 83  vtable data_ov004_022566d8, profile data_ov004_022566c8 (MuseumSetupPlain_New),
 *             derived from class 81;
 *   class 82  vtable data_ov004_02256780, profile data_ov004_022566b8 (MuseumSetupGroupA_New),
 *             derived from class 81.
 *
 * Their creation (slot 0, MuseumSetup_Create) makes the scene's obj_etc_museum spots from the
 * table data_ov004_0224b868 (one row of spots for each of the seven scenes; the spots are built
 * by the overlay's static initialiser), then calls the class's slot 18: nothing in classes 81
 * and 83; in class 82 (MuseumSetupGroupA_ClearMissing) each item of the museum record's group A
 * lying on the scene's acre (0, 0) that nobody has given is taken away: replaced by item 0x4a54
 * when its furniture shape is 0, else by the empty tile. Their execution (slot 6) is done at
 * once. */
#ifndef CLEAN_OV004_MUSEUM_ROOM_SETUP_H
#define CLEAN_OV004_MUSEUM_ROOM_SETUP_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "types.h"

/* The process's vtable slot each class sets up its scene with. */
#define MUSEUM_SETUP_SLOT_SCENE 18

/* The rows of data_ov004_0224b868. */
#define MUSEUM_SETUP_ROWS 7

typedef struct MuseumSetup {
    Process base;
} MuseumSetup;

/* An obj_etc_museum spot: what EtcMuseum_Spawn is given (0x1c bytes). */
typedef struct MuseumSetupSpot {
    Vec3 position;        /* 0x00 */
    u32 face_angle;       /* 0x0c */
    s16 yaw;              /* 0x10 */
    s16 complete_message; /* 0x12 */
    const u8 *exhibits;   /* 0x14 */
    u8 count;             /* 0x18 */
    u8 kind;              /* 0x19: enum EtcMuseumKind */
    u8 pad_1a[2];
} MuseumSetupSpot;

/* A row of data_ov004_0224b868: a scene's spots. */
typedef struct MuseumSetupRow {
    u8 scene;
    u8 pad_01[3];
    MuseumSetupSpot *spots; /* 0x04 */
    u32 count;              /* 0x08 */
} MuseumSetupRow;

int MuseumSetupPlain_SetUpScene(void);
MuseumSetup *MuseumSetupPlain_DestructFree(MuseumSetup *self);
MuseumSetup *MuseumSetupPlain_Destruct(MuseumSetup *self);
MuseumSetup *MuseumSetupPlain_Construct(MuseumSetup *self);
void MuseumSetupPlain_New(void);
int MuseumSetupGroupA_ClearMissing(void);
MuseumSetup *MuseumSetupGroupA_DestructFree(MuseumSetup *self);
MuseumSetup *MuseumSetupGroupA_Destruct(MuseumSetup *self);
MuseumSetup *MuseumSetupGroupA_Construct(MuseumSetup *self);
void MuseumSetupGroupA_New(void);
void MuseumSetup_SpawnSpots(void);
int MuseumSetup_Execute(void);
int MuseumSetup_SetUpScene(void);
int MuseumSetup_Create(MuseumSetup *self);
MuseumSetup *MuseumSetup_DestructBase(MuseumSetup *self);
MuseumSetup *MuseumSetup_DestructFree(MuseumSetup *self);
MuseumSetup *MuseumSetup_Destruct(MuseumSetup *self);
MuseumSetup *MuseumSetup_Construct(MuseumSetup *self);
MuseumSetup *MuseumSetup_ConstructBase(MuseumSetup *self);
void MuseumSetup_New(void);
unsigned char MuseumSetupSpot_Count(const MuseumSetupSpot *spot);
u32 MuseumSetupSpot_Exhibits(const MuseumSetupSpot *spot);
short MuseumSetupSpot_CompleteMessage(const MuseumSetupSpot *spot);
unsigned char MuseumSetupSpot_Kind(const MuseumSetupSpot *spot);
u32 MuseumSetupSpot_FaceAngle(const MuseumSetupSpot *spot);
int MuseumSetupSpot_Yaw(const MuseumSetupSpot *spot);

/* A spot as the overlay's data describes it (0x18 bytes): the static initialiser builds each
 * spot from one (MuseumSetupSpot_Construct). `directions` has a bit for each quarter turn
 * (bit i for the yaw i * 0x4000) from which the spot is faced. */
typedef struct MuseumSetupSpotSource {
    Vec3 position;        /* 0x00 */
    u8 directions;        /* 0x0c */
    u8 kind;              /* 0x0d: enum EtcMuseumKind */
    s16 complete_message; /* 0x0e */
    const u8 *exhibits;   /* 0x10 */
    u8 count;             /* 0x14 */
    u8 pad_15[3];
} MuseumSetupSpotSource;

Vec3 *MuseumSetupSpot_Position(const MuseumSetupSpot *spot);
MuseumSetupSpot *MuseumSetupSpot_Construct(MuseumSetupSpot *spot, const MuseumSetupSpotSource *source);
void MuseumSetupSpot_Init(MuseumSetupSpot *spot, const Vec3 *position, int directions, int kind, short complete_message,
                          const u8 *exhibits, unsigned char count);
void MuseumSetupSpot_Destruct(MuseumSetupSpot *spot);

#endif
