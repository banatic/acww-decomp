/* The spawner: a resident process (class 0xcc, vtable data_020e1cc0, built by func_02085ed0)
 * that makes one special actor at a time, on request.
 *
 * A request (data_020e1ca8) names an actor profile, the scene it is for, a priority (0: none,
 * 1-4) and a position. Each frame (func_02085558) the spawner runs the checks of its table
 * (data_020e1d08, highest priority first): the first check above the pending request's priority
 * that answers with an entry of the spawn table replaces the request (Spawner_RunChecks). Then
 * a pending request for the current scene is carried out: its entry's placer sets the actor's
 * position and angle, its overlay is loaded when the entry asks for it, and the actor is made
 * under the spawner (Spawner_Serve). Other code asks for an actor with priority 1
 * (Spawner_RequestAt, the warp object of overlay 3).
 *
 * The spawn table (data_020e1d8c, data_020d0644 entries) gives each profile the argument it is
 * made with (`code`), an overlay and its placer, a member function of the spawner. */
#ifndef CLEAN_MAIN_SPAWNER_H
#define CLEAN_MAIN_SPAWNER_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "calendar.h"
#include "types.h"

#define SPAWNER_PRIORITY_NONE 0
#define SPAWNER_PRIORITY_MAX 4
#define SPAWNER_CHECKS 11
/* The spawn table's entries (data_020d0644 holds the number too). */
#define SPAWNER_ENTRIES 23
#define SPAWNER_NO_SCENE 0x33 /* the scene of a cleared request */

/* The request (data_020e1ca8). */
typedef struct SpawnerRequest {
    Vec3 position; /* 0x00: where the caller wants the actor; the placers may use it */
    u16 profile;   /* 0x0c: the actor's profile */
    u8 scene;      /* 0x0e: the scene the actor is for */
    u8 priority;   /* 0x0f: SPAWNER_PRIORITY_NONE or 1-4 */
} SpawnerRequest;

/* An entry of the spawn table (data_020e1d8c). */
typedef struct SpawnerEntry {
    u16 profile;    /* 0x00 */
    u16 code;       /* 0x02: the argument the actor is made with (Actor_Spawn's `group`) */
    u32 overlay;    /* 0x04: loaded with the actor when bit 0 of `flags` is set */
    MemberFn place; /* 0x08: the placer, (self, position, angle, request) */
    u8 flags;       /* 0x10 */
    u8 unused_11[3];
} SpawnerEntry;

#define SPAWNER_ENTRY_LOADS_OVERLAY 1

/* An entry of the table of checks (data_020e1d08): a member function that answers an entry
 * of the spawn table or 0, and the priority its answer is requested with. */
typedef struct SpawnerCheck {
    MemberFn check; /* 0x00 */
    u8 priority;    /* 0x08 */
    u8 unused_09[3];
} SpawnerCheck;

/* An event and the profile asked for while it is on (the tables of Spawner_CheckEvents). */
typedef struct SpawnerEvent {
    u32 event;   /* 0x00: for func_02085d2c */
    u16 profile; /* 0x04 */
    u16 unused_06;
} SpawnerEvent;

/* The process (0x78 bytes). */
typedef struct Spawner {
    Process base;      /* 0x00 */
    u8 part_50[0x20];  /* 0x50: a part with an empty constructor and destructor */
    u8 overlay_loaded; /* 0x70: whether `overlay` was loaded for the last actor */
    u8 unused_71[3];
    u32 overlay; /* 0x74 */
} Spawner;

/* A condition of the tables of Spawner_CheckEvents. */
typedef int SpawnerCondition(void);

Spawner *Spawner_Destruct(Spawner *self);
Spawner *Spawner_DestructFree(Spawner *self);
int Spawner_PlaceOffRequest(Spawner *self, Vec3 *position, u16 *angle, const SpawnerRequest *request);
int Spawner_PlaceFromPart31(Spawner *self, Vec3 *position, u16 *angle, const SpawnerRequest *request);
int Spawner_PlaceFromPart4(Spawner *self, Vec3 *position, u16 *angle);
int Spawner_PlaceFromPart24(Spawner *self, Vec3 *position, u16 *angle);
int Spawner_PlaceOnRandomTile(Spawner *self, Vec3 *position);
int Spawner_PlayerLacksFlag18(void);
void Spawner_CheckEvent45(void);
void Spawner_CheckEvents3e(void);
int Spawner_CheckEvents(const SpawnerEvent *events, SpawnerCondition *const *conditions, int count, int check_mode);
int Spawner_CheckD020(void);
int Spawner_CheckD020In(int check_mode);
int Spawner_PlaceFromPartC(Spawner *self, Vec3 *position);
void Spawner_CheckD023(void);
int Spawner_CheckD023In(int check_mode);
void Spawner_UpdatePartCInSession(Spawner *self);
int Spawner_PlaceFromPartCOrRoom(Spawner *self, Vec3 *position);
void Spawner_CheckD022(void);
int Spawner_CheckD022In(int check_mode);
int Spawner_CheckD002(void);
int Spawner_CheckD002In(int check_mode);
int Spawner_PlaceBeforeBuilding(Spawner *self, Vec3 *position, s16 *angle);
void Spawner_CheckD00D(void);
int Spawner_CheckD00DIn(int check_mode);
int Spawner_PlaceAtOrigin(Spawner *self, Vec3 *position);
int Spawner_PlaceForPlayer(Spawner *self, Vec3 *position, s16 *angle);
void Spawner_PlaceBesideBuilding5000Void(Spawner *self, Vec3 *position, s16 *angle);
int Spawner_PlaceBesideBuilding(Spawner *self, Vec3 *position, s16 *angle);
int Spawner_PlaceBesideBuilding5000(Spawner *self, Vec3 *position, s16 *angle);
int Spawner_CheckEvents06a4(void);
int Spawner_CheckEvents06a4In(int check_mode);
int Spawner_PlayerBlock0Ready(void);
void Spawner_CheckProfile56(void);
int Spawner_CheckProfile56In(int check_mode);
int Spawner_Profile56Allowed(void);
int Spawner_PlaceBelowBuilding(Spawner *self, Vec3 *position, u16 *angle);
int Spawner_CheckD019(void);
int Spawner_PlaceInFrontOfBuilding(Spawner *self, Vec3 *position);
int Spawner_CheckD011(void);
int Spawner_SoundFlagSet(void);
int Spawner_PlayerHasFlag1(void);
int Spawner_FirstEventOn(const SpawnerEvent *events, int count);
void Spawner_ReleaseOverlay(Spawner *self);
const SpawnerEntry *Spawner_Serve(Spawner *self, const SpawnerEntry *table, int count);
int Spawner_RunChecks(Spawner *self);
int Spawner_RequestAt(const u16 *profile, int scene, const Vec3 *position);
int Spawner_Request(const u16 *profile, u32 priority, int scene, const Vec3 *position);
const SpawnerEntry *Spawner_FindProfile(const u16 *profile, const SpawnerEntry *table, int count);
const SpawnerEntry *Spawner_FindCode(const u16 *code, const SpawnerEntry *table, int count);
void Spawner_ForgetOverlay(Spawner *self);
void Spawner_NoteOverlay(Spawner *self, const u32 *overlay);
int Spawner_IsPending(int self, const SpawnerRequest *request);
void Spawner_ClearRequest(SpawnerRequest *request);
void Spawner_SetRequest(SpawnerRequest *request, const u16 *profile, u8 scene, u8 priority, const Vec3 *position);
void Spawner_PartDestruct(void *part);
void Spawner_PartConstruct(void *part);

/* The process's phases and the villagers it makes (the vtable's slots 0, 3 and 6). */
int Spawner_Execute(void);
int Spawner_Delete(Spawner *self);
int Spawner_Create(Spawner *self);
void Spawner_SpawnHouseGuest(Spawner *self);
void Spawner_SpawnHouseOwner(Spawner *self);
void Spawner_PlaceTownVillagers(Spawner *self);
void Spawner_KeepOffRaisedGround(u8 *villager, Vec3 *position);
void Spawner_PeekCode(u16 *code);
int Spawner_EventOn(u32 event, const DateTime *when);
int Spawner_PlaceOnFreeTile(Spawner *self, Vec3 *position);
Spawner *Spawner_New(void);
void Spawner_RequestDestruct(void *request);

#endif
