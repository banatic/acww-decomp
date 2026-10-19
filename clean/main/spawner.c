/* The spawner process, its request and its checks (spawner.h). */
#include "spawner.h"

#include "acre_map.h"
#include "acre_record.h"
#include "acre_tile.h"
#include "actor.h"
#include "autoload_2/heap.h"
#include "block_020b220c.h"
#include "clean.h"
#include "date_time.h"
#include "item_object.h"
#include "overlay_slots.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "villager_part.h"
#include "villager_part_block.h"
#include "beside_spot.h"
#include "block_021d27ac.h"
#include "block_021d27ac_parts.h"
#include "daily_bits.h"
#include "event_announce.h"
#include "event_calendar.h"
#include "link_global.h"
#include "main_random.h"
#include "middle_spot.h"
#include "near_spot.h"
#include "paired_town.h"
#include "tile_requests.h"
#include "town_spot.h"
#include "town_start_day.h"
#include "unit_type_info.h"
#include "wfc_stats.h"
#include "scene_kinds.h"
#include "scene_query.h"

static_assert(sizeof(SpawnerRequest) == 0x10, "request size");
static_assert(offsetof(SpawnerRequest, profile) == 0x0c && offsetof(SpawnerRequest, priority) == 0x0f, "request");
static_assert(sizeof(SpawnerEntry) == 0x14, "spawn table entry size");
static_assert(offsetof(SpawnerEntry, place) == 0x08 && offsetof(SpawnerEntry, flags) == 0x10, "spawn table entry");
static_assert(sizeof(SpawnerCheck) == 0x0c, "check size");
static_assert(sizeof(SpawnerEvent) == 0x08, "event entry size");
static_assert(offsetof(Spawner, part_50) == 0x50 && offsetof(Spawner, overlay_loaded) == 0x70, "spawner");
static_assert(offsetof(Spawner, overlay) == 0x74 && sizeof(Spawner) == 0x78, "spawner");

/* Scenes some checks look for (func_020b65c4). */
#define SCENE_0 0x00 /* where the checks of codes 0xd011 and 0xd019 answer */
#define SCENE_9 0x09
#define SCENE_B 0x0b
#define SCENE_C 0x0c
#define SCENE_2C 0x2c /* where no check run with a check mode answers */

/* The events (func_02085d2c) Spawner_CheckD020In needs all off. */
#define EVENT_D020_FIRST 0x3b
#define EVENT_D020_LAST 0x44
#define EVENT_3B 0x3b
#define EVENT_3C 0x3c
#define EVENT_3D 0x3d
#define EVENT_ANY 0x13 /* in data_020d0664: whatever event is going on */

/* The bit of the player's word at 0x23ec (func_020887c0) Spawner_PlayerLacksFlag18 tests, the
 * player record's flags the checks test (PlayerRecord_TestFlag) and the flag of the object at
 * data_021d27ac (func_02086108) Spawner_Profile56Allowed tests. */
#define PLAYER_BIT_18 0x18
#define PLAYER_FLAG_1 1
#define PLAYER_FLAG_23 0x23
#define OBJECT_FLAG_8 8

/* What the placers look for on the map (AcreTile_FindItemAllFlags): a building of the codes
 * 0x5014-0x501a in a tile with flag 1, or building 0x5000 in a tile with flag 0x200. */
#define BUILDING_5014 0x5014
#define BUILDING_501A 0x501a
#define BUILDING_5000 0x5000
#define TILE_FLAG_1 1
#define TILE_FLAG_200 0x200

/* The acres Spawner_PlaceOnRandomTile searches, and how many tiles it keeps. */
#define RANDOM_TILE_ACRE_ANY_FLAGS 0x7f000
#define RANDOM_TILE_ACRE_ALL_FLAGS 8
#define RANDOM_TILES 32
#define ACRE_TILES 16

#define ANGLE_QUARTER 0x4000
#define ANGLE_THREE_QUARTERS 0xc000
#define RANDOM_ANGLE_BOUND 0xffff /* func_020644cc(0xffff): any angle but 0xffff */

/* The vtables: the spawner's and the base process's. */
extern const u32 data_020e1cc0[];
extern const u32 data_020da13c[];

/* The request, the checks and the spawn table (filled by __sinit_020c5f70). */
extern SpawnerRequest data_020e1ca8;
extern SpawnerCheck data_020e1d08[SPAWNER_CHECKS];
extern SpawnerEntry data_020e1d8c[SPAWNER_ENTRIES];
extern int data_020d0644; /* the spawn table's number of entries */
/* The profile the cleared request names (0), and the profile 0x56 two checks ask for. */
extern const u16 data_020e1b8c;
extern const u16 data_020e1b84;
extern const u16 data_020e1b88;
/* Where a request without a position stands. */
extern const Vec3 data_021fbee8;

/* The tables of the event checks: Spawner_CheckEvents3e's four events with the conditions
 * data_020d0654 (only the third, func_02083f40, is set), Spawner_CheckEvent45's one event. */
extern const SpawnerEvent data_020d0684[];
extern SpawnerCondition *const data_020d0654[];
extern const SpawnerEvent data_020d064c[];
/* Spawner_CheckProfile56OrD025In's eight events and the event each needs going on. */
extern const SpawnerEvent data_020d06a4[];
extern const int data_020d0664[];

extern u8 data_020e54a8;          /* 0 outdoors, 1 in a room */
extern NetSession *data_020ccf94; /* the session */
extern AcreMap *data_021c80bc;    /* the map of the scene */
extern u8 data_021f3b85[];        /* four bytes; func_0209fa30 tests the last */
extern u8 data_021f3278[];        /* what func_020881c4 tests */

/* Spawner_PlaceOnRandomTile's tiles, cleared on its first call (bit 0 of data_021d212c). */
typedef struct SpawnerTile {
    int x;
    int z;
} SpawnerTile;
extern u32 data_021d212c;
extern SpawnerTile data_021d222c[RANDOM_TILES];

/* ---- Helpers */

static int outdoors(void)
{
    return data_020e54a8 == 0;
}

/* Whether this console is in the session. */
static int in_session(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

/* What a check run with `check_mode` needs: nothing without it, else being outdoors outside
 * scene 0x2c. */
static int mode_allows(int check_mode)
{
    return check_mode == 0 || (outdoors() && SceneQuery_Current() != SCENE_2C);
}

static int entry_result(const SpawnerEntry *entry)
{
    return (int) (intptr_t) entry;
}

/* The entry of the spawn table for `code`, as a check answers it. */
static int code_result(u16 code)
{
    return entry_result(Spawner_FindCode(&code, data_020e1d8c, data_020d0644));
}

static int profile_result(const u16 *profile)
{
    return entry_result(Spawner_FindProfile(profile, data_020e1d8c, data_020d0644));
}

/* The function `fn` (MemberFn, autoload_2/process.h) calls on `object`, and in `self` the
 * object it is called with. */
static uintptr_t member_target(const MemberFn *fn, void *object, void **self)
{
    u8 *adjusted = (u8 *) object + (fn->adj - (fn->adj & 1)) / 2;
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        target = *(const u32 *) (uintptr_t) (*(const u32 *) adjusted + fn->ptr);
    }
    *self = adjusted;
    return target;
}

/* ---- The process */

static void destruct(Spawner *self)
{
    self->base.vtable = data_020e1cc0;
    Spawner_PartDestruct(self->part_50);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_02083cc0: the destructor. */
Spawner *Spawner_Destruct(Spawner *self)
{
    destruct(self);
    return self;
}
CLEAN_AS(func_02083cc0, Spawner_Destruct)

/* func_02083cec: the destructor, then the memory freed. */
Spawner *Spawner_DestructFree(Spawner *self)
{
    destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02083cec, Spawner_DestructFree)

/* ---- The placers (the spawn table's member functions): each sets the actor's position and
 * angle (only the angle about Y, angle[1], is ever set) and answers 1, or 0 when it found no
 * place and set nothing. */

/* func_02083d1c: the tile centre nearest to the request's position moved 0x4000 to -x and 0x6000
 * to +z, facing angle 0. */
int Spawner_PlaceOffRequest(Spawner *self, Vec3 *position, u16 *angle, const SpawnerRequest *request)
{
    (void) self;
    Vec3 near = {request->position.x - 0x4000, 0, request->position.z + 0x6000};
    AcreTile_SnapToTileCentre(position, &near);
    angle[1] = 0;
    return 1;
}
CLEAN_AS(func_02083d1c, Spawner_PlaceOffRequest)

/* func_02083d54: what func_02087a78 makes of part 0x31 of the object at data_021d27ac. */
int Spawner_PlaceFromPart31(Spawner *self, Vec3 *position, u16 *angle, const SpawnerRequest *request)
{
    (void) self;
    BesideSpot_Place(Block021d27ac_Part31(Block021d27ac_Get()), position, &angle[1], request);
    return 1;
}
CLEAN_AS(func_02083d54, Spawner_PlaceFromPart31)

/* func_02083d78: where part 0x04 says, facing a random angle. */
int Spawner_PlaceFromPart4(Spawner *self, Vec3 *position, u16 *angle)
{
    (void) self;
    TownSpot_ToPosition((const TownSpot *) (void *) Block021d27ac_Part04(Block021d27ac_Get()), position);
    angle[1] = (u16) MainRandom_Below(RANDOM_ANGLE_BOUND);
    return 1;
}
CLEAN_AS(func_02083d78, Spawner_PlaceFromPart4)

/* func_02083da4: where part 0x24 says, facing the angle it says. */
int Spawner_PlaceFromPart24(Spawner *self, Vec3 *position, u16 *angle)
{
    (void) self;
    void *part = Block021d27ac_Part24(Block021d27ac_Get());
    NearSpot_ToPosition(part, position);
    angle[1] = (u16) NearSpot_Facing(part);
    return 1;
}
CLEAN_AS(func_02083da4, Spawner_PlaceFromPart24)

/* func_02083dcc: the centre of a random tile func_02031a48 accepts, from the first 32 found in
 * the acres with any of the flags 0x7f000 and flag 8, row by row; 0 outdoors when there is no
 * map or no such tile, and always 0 in a room (nothing set). */
int Spawner_PlaceOnRandomTile(Spawner *self, Vec3 *position)
{
    (void) self;
    if ((data_021d212c & 1) == 0) {
        for (int i = 0; i < RANDOM_TILES; i++) {
            data_021d222c[i].x = 0;
            data_021d222c[i].z = 0;
        }
        data_021d212c |= 1;
    }
    if (!outdoors()) {
        return 0;
    }
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int found = 0;
    int wide = map->acres_wide;
    int high = map->acres_high;
    for (int acre_z = 0; acre_z < high && found < RANDOM_TILES; acre_z++) {
        for (int acre_x = 0; acre_x < wide && found < RANDOM_TILES; acre_x++) {
            AcreRecord *acre = NULL;
            if ((u32) acre_x < (u32) map->acres_wide && (u32) acre_z < (u32) map->acres_high && map->acres != NULL) {
                acre = (AcreRecord *) (map->acres + (acre_x + acre_z * map->acres_wide) * ACRE_MAP_ACRE_SIZE);
            }
            if (acre == NULL || !AcreRecord_HasAnyFlag(acre, RANDOM_TILE_ACRE_ANY_FLAGS) ||
                !AcreRecord_HasAllFlags(acre, RANDOM_TILE_ACRE_ALL_FLAGS)) {
                continue;
            }
            int first_x = 0;
            int first_z = 0;
            AcreTile_TileOfAcre(&first_x, &first_z, acre_x, acre_z, 0, 0);
            for (int z = first_z; z < first_z + ACRE_TILES && found < RANDOM_TILES; z++) {
                for (int x = first_x; x < first_x + ACRE_TILES && found < RANDOM_TILES; x++) {
                    if (UnitTypeInfo_IsType1eOver08(x, z) != 0) {
                        data_021d222c[found].x = x;
                        data_021d222c[found].z = z;
                        found++;
                    }
                }
            }
        }
    }
    if (found <= 0) {
        return 0;
    }
    const SpawnerTile *tile = &data_021d222c[MainRandom_Below(found)];
    AcreTile_TileCentre(position, (u32) tile->x, (u32) tile->z);
    return 1;
}
CLEAN_AS(func_02083dcc, Spawner_PlaceOnRandomTile)

/* ---- The event checks */

/* func_02083f40 (a condition of data_020d0654): whether there is a player and bit 0x18 after
 * its word at 0x23ec is clear. */
int Spawner_PlayerLacksFlag18(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 0;
    }
    return DailyBits_Test((DailyBits *) ((u32 *) PlayerRecord_Field23EC(record)), PLAYER_BIT_18) == 0;
}
CLEAN_AS(func_02083f40, Spawner_PlayerLacksFlag18)

/* func_02083f68 (check 10, priority 2): event 0x45, profile 0x54.
 * QUIRK: declared without a result; in the ROM the answer of Spawner_CheckEvents is still in r0
 * when it returns, so Spawner_RunChecks gets it. */
void Spawner_CheckEvent45(void)
{
    (void) Spawner_CheckEvents(data_020d064c, NULL, 1, 1);
}
CLEAN_AS(func_02083f68, Spawner_CheckEvent45)

/* func_02083f84 (check 8, priority 2): the events 0x3e, 0x41, 0x42 and 0x43, for the profiles
 * 0x6a, 0x6b, 0x68 and 0x62; 0x42 only while Spawner_PlayerLacksFlag18.
 * QUIRK: declared without a result, as Spawner_CheckEvent45. */
void Spawner_CheckEvents3e(void)
{
    (void) Spawner_CheckEvents(data_020d0684, data_020d0654, 4, 1);
}
CLEAN_AS(func_02083f84, Spawner_CheckEvents3e)

/* func_02083fa4: the entry of the profile of the first of `count` events that is on now, when
 * its condition (if `conditions` and the event's one are set) holds; 0 while the last of the
 * bytes at data_021f3b85 is set, the player has flag 1, either sound flag is set, this console
 * is in the session, or the check mode forbids it. */
int Spawner_CheckEvents(const SpawnerEvent *events, SpawnerCondition *const *conditions, int count, int check_mode)
{
    int held = TownStartDay_IsSet((TownStartDay *) (void *) data_021f3b85);
    if (!mode_allows(check_mode) || held != 0 || Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet() || in_session()) {
        return 0;
    }
    int index = Spawner_FirstEventOn(events, count);
    if (index == -1) {
        return 0;
    }
    if (conditions != NULL && conditions[index] != NULL && conditions[index]() == 0) {
        return 0;
    }
    return profile_result(&events[index].profile);
}
CLEAN_AS(func_02083fa4, Spawner_CheckEvents)

/* ---- The checks of codes */

/* func_0208404c (check 9, priority 2) */
int Spawner_CheckD020(void)
{
    return Spawner_CheckD020In(1);
}
CLEAN_AS(func_0208404c, Spawner_CheckD020)

/* func_02084058: the entry of code 0xd020 when none of the events 0x3b-0x44 is on now and
 * func_020881c4 accepts data_021f3278; 0 while the player has flag 1, either sound flag is
 * set, the check mode forbids it or this console is in the session. */
int Spawner_CheckD020In(int check_mode)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet() || !mode_allows(check_mode) || in_session()) {
        return 0;
    }
    for (u32 event = EVENT_D020_FIRST; event <= EVENT_D020_LAST; event++) {
        if (Spawner_EventOn(event, &now) != 0) {
            return 0;
        }
    }
    if (WfcStats_IsInUse((const WfcStats *) (void *) data_021f3278) == 0) {
        return 0;
    }
    return code_result(0xd020);
}
CLEAN_AS(func_02084058, Spawner_CheckD020In)

/* func_02084160 (placer): where part 0x0c of the object at data_021d27ac says. */
int Spawner_PlaceFromPartC(Spawner *self, Vec3 *position)
{
    (void) self;
    MiddleSpot_ToPosition((const MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get()), position);
    return 1;
}
CLEAN_AS(func_02084160, Spawner_PlaceFromPartC)

/* func_0208417c (check 7, priority 3).
 * QUIRK: declared without a result; in the ROM the answer is still in r0 when it returns, so
 * Spawner_RunChecks gets it. */
void Spawner_CheckD023(void)
{
    (void) Spawner_CheckD023In(1);
}
CLEAN_AS(func_0208417c, Spawner_CheckD023)

/* func_02084188: the entry of code 0xd023 while func_02088394 holds and event 0x3d is off;
 * 0 while the player has flag 1, either sound flag is set, the check mode forbids it or this
 * console is in the session. */
int Spawner_CheckD023In(int check_mode)
{
    if (PairedTown_CurrentFlaggedInLastWeek() == 0 || Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet() ||
        !mode_allows(check_mode) || in_session() || Spawner_EventOn(EVENT_3D, NULL) != 0) {
        return 0;
    }
    return code_result(0xd023);
}
CLEAN_AS(func_02084188, Spawner_CheckD023In)

/* func_02084210 (from the spawner's update): while this console is in the session, the player
 * lacks flag 1 and func_020883cc holds, part 0x0c of the object at data_021d27ac goes to
 * func_02087f58 outdoors. */
void Spawner_UpdatePartCInSession(Spawner *self)
{
    (void) self;
    if (!in_session() || Spawner_PlayerHasFlag1() || PairedTown_CurrentUnflaggedInLastWeek() == 0) {
        return;
    }
    if (outdoors()) {
        MiddleSpot_Pick((MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get()));
    }
}
CLEAN_AS(func_02084210, Spawner_UpdatePartCInSession)

/* func_02084260 (placer): outdoors where part 0x0c says; in a room 0x1000 to +x of the centre
 * of tile (6, 17). */
int Spawner_PlaceFromPartCOrRoom(Spawner *self, Vec3 *position)
{
    (void) self;
    if (outdoors()) {
        MiddleSpot_ToPosition((const MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get()), position);
        return 1;
    }
    AcreTile_TileCentre(position, 6, 0x11);
    position->x += 0x1000;
    return 1;
}
CLEAN_AS(func_02084260, Spawner_PlaceFromPartCOrRoom)

/* func_020842ac (check 6, priority 3).
 * QUIRK: declared without a result, as Spawner_CheckD023. */
void Spawner_CheckD022(void)
{
    (void) Spawner_CheckD022In(1);
}
CLEAN_AS(func_020842ac, Spawner_CheckD022)

/* func_020842b8: the entry of code 0xd022 when either
 *   func_020883cc holds, the check mode allows it, this console is not in the session and
 *   event 0x3d is off, or
 *   func_02087f30 accepts part 0x0c of the object at data_021d27ac and the scene is 0x0b with
 *   the session not linked, or the scene is 0x0c;
 * 0 while the player has flag 1 or either sound flag is set. */
int Spawner_CheckD022In(int check_mode)
{
    if (Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet()) {
        return 0;
    }
    if (PairedTown_CurrentUnflaggedInLastWeek() != 0 && mode_allows(check_mode) && !in_session() &&
        Spawner_EventOn(EVENT_3D, NULL) == 0) {
        return code_result(0xd022);
    }
    if (MiddleSpot_HasMark((const MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get())) != 0 &&
        SceneQuery_Current() == SCENE_B && Session_IsLinked(data_020ccf94) == 0) {
        return code_result(0xd022);
    }
    if (MiddleSpot_HasMark((const MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get())) != 0 &&
        SceneQuery_Current() == SCENE_C) {
        return code_result(0xd022);
    }
    return 0;
}
CLEAN_AS(func_020842b8, Spawner_CheckD022In)

/* func_0208437c (check 5, priority 4) */
int Spawner_CheckD002(void)
{
    return Spawner_CheckD002In(1);
}
CLEAN_AS(func_0208437c, Spawner_CheckD002)

/* func_02084388: the entry of code 0xd002 while event 0x3b is on; 0 while this console is in
 * the session, the check mode forbids it, the last of the bytes at data_021f3b85 is set, the
 * player has flag 1 or either sound flag is set. */
int Spawner_CheckD002In(int check_mode)
{
    int held = TownStartDay_IsSet((TownStartDay *) (void *) data_021f3b85);
    if (in_session() || !mode_allows(check_mode) || held != 0 || Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet() ||
        Spawner_EventOn(EVENT_3B, NULL) == 0) {
        return 0;
    }
    return code_result(0xd002);
}
CLEAN_AS(func_02084388, Spawner_CheckD002In)

/* func_02084418 (placer): outdoors, 0x4000 to +x and +z of the centre of the first tile with
 * flag 1 holding a building 0x5014-0x501a, facing angle 0xc000; 0 without a map or such a
 * tile, and in a room. */
int Spawner_PlaceBeforeBuilding(Spawner *self, Vec3 *position, s16 *angle)
{
    (void) self;
    if (!outdoors()) {
        return 0;
    }
    AcreMap *map = data_021c80bc;
    int acre_x = 0, acre_z = 0, x = 0, z = 0;
    if (map == NULL) {
        return 0;
    }
    u16 first = BUILDING_5014;
    u16 last = BUILDING_501A;
    if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, TILE_FLAG_1, 0) == 0) {
        return 0;
    }
    AcreTile_TileCentreInAcre(position, acre_x, acre_z, x, z);
    position->x += 0x4000;
    position->z += 0x4000;
    angle[1] = (s16) ANGLE_THREE_QUARTERS;
    return 1;
}
CLEAN_AS(func_02084418, Spawner_PlaceBeforeBuilding)

/* func_020844b8 (check 4, priority 4).
 * QUIRK: declared without a result, as Spawner_CheckD023. */
void Spawner_CheckD00D(void)
{
    (void) Spawner_CheckD00DIn(1);
}
CLEAN_AS(func_020844b8, Spawner_CheckD00D)

/* func_020844c4: Spawner_CheckD002In's conditions with event 0x3c, for code 0xd00d. */
int Spawner_CheckD00DIn(int check_mode)
{
    int held = TownStartDay_IsSet((TownStartDay *) (void *) data_021f3b85);
    if (in_session() || !mode_allows(check_mode) || held != 0 || Spawner_PlayerHasFlag1() || Spawner_SoundFlagSet() ||
        Spawner_EventOn(EVENT_3C, NULL) == 0) {
        return 0;
    }
    return code_result(0xd00d);
}
CLEAN_AS(func_020844c4, Spawner_CheckD00DIn)

/* func_02084554 (placer): the origin. */
int Spawner_PlaceAtOrigin(Spawner *self, Vec3 *position)
{
    (void) self;
    position->x = 0;
    position->y = 0;
    position->z = 0;
    return 1;
}
CLEAN_AS(func_02084554, Spawner_PlaceAtOrigin)

/* func_02084560 (placer): beside building 0x5000 when the player has flag 1, else beside a
 * building 0x5014-0x501a.
 * QUIRK: asks for the current player first and drops the answer. */
int Spawner_PlaceForPlayer(Spawner *self, Vec3 *position, s16 *angle)
{
    (void) PlayerRecords_Current();
    if (Spawner_PlayerHasFlag1()) {
        return Spawner_PlaceBesideBuilding5000(self, position, angle);
    }
    return Spawner_PlaceBesideBuilding(self, position, angle);
}
CLEAN_AS(func_02084560, Spawner_PlaceForPlayer)

/* func_02084590 (placer): Spawner_PlaceBesideBuilding5000.
 * QUIRK: declared without a result; in the ROM its answer is still in r0 when it returns. */
void Spawner_PlaceBesideBuilding5000Void(Spawner *self, Vec3 *position, s16 *angle)
{
    (void) Spawner_PlaceBesideBuilding5000(self, position, angle);
}
CLEAN_AS(func_02084590, Spawner_PlaceBesideBuilding5000Void)

/* The first tile with `flags` holding a building of the codes `first`-`last`, as a tile of the
 * whole map; 0 when there is none. */
static int find_building(AcreMap *map, u16 *first, u16 *last, int flags, int *tile_x, int *tile_z)
{
    int acre_x = 0, acre_z = 0, x = 0, z = 0;
    if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, first, last, flags, 0) == 0) {
        return 0;
    }
    *tile_x = 0;
    *tile_z = 0;
    AcreTile_TileOfAcre(tile_x, tile_z, acre_x, acre_z, x, z);
    return 1;
}

/* func_02084598 (placer): the centre of the tile two to +x and two to +z of a building
 * 0x5014-0x501a (in a tile with flag 1), facing a random angle; 0 without a map or such a
 * tile. */
int Spawner_PlaceBesideBuilding(Spawner *self, Vec3 *position, s16 *angle)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    u16 first = BUILDING_5014;
    u16 last = BUILDING_501A;
    int x, z;
    if (map == NULL || !find_building(map, &first, &last, TILE_FLAG_1, &x, &z)) {
        return 0;
    }
    AcreTile_TileCentre(position, (u32) (x + 2), (u32) (z + 2));
    angle[1] = (s16) MainRandom_Below(RANDOM_ANGLE_BOUND);
    return 1;
}
CLEAN_AS(func_02084598, Spawner_PlaceBesideBuilding)

/* func_02084630 (placer): the centre of the tile two to -x and three to +z of building 0x5000
 * (in a tile with flag 0x200), facing a random angle; 0 without a map or such a tile. */
int Spawner_PlaceBesideBuilding5000(Spawner *self, Vec3 *position, s16 *angle)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    u16 building = BUILDING_5000; /* the first and last code are the same halfword */
    int x, z;
    if (map == NULL || !find_building(map, &building, &building, TILE_FLAG_200, &x, &z)) {
        return 0;
    }
    AcreTile_TileCentre(position, (u32) (x - 2), (u32) (z + 3));
    angle[1] = (s16) MainRandom_Below(RANDOM_ANGLE_BOUND);
    return 1;
}
CLEAN_AS(func_02084630, Spawner_PlaceBesideBuilding5000)

/* ---- The checks of profile 0x56 and the eight events */

/* func_020846c0 (check 3, priority 4) */
int Spawner_CheckEvents06a4(void)
{
    return Spawner_CheckEvents06a4In(1);
}
CLEAN_AS(func_020846c0, Spawner_CheckEvents06a4)

/* func_020846cc: when this console is not in the session,
 *   profile 0x56 while Spawner_PlayerBlock0Ready, else
 *   the profile of the first of the eight events of data_020d06a4 that is on now (looked for
 *   unless either sound flag is set) while the event of data_020d0664 it needs is going on
 *   (0x13 needs none),
 * each only when the check mode allows it; else, or when Spawner_Profile56Allowed fails, the
 * entry of code 0xd025 in scene 9. In the session only the last one: code 0xd025 in scene 9. */
int Spawner_CheckEvents06a4In(int check_mode)
{
    if (in_session()) {
        return SceneQuery_Current() == SCENE_9 ? code_result(0xd025) : 0;
    }
    int allowed = mode_allows(check_mode);
    if (Spawner_PlayerBlock0Ready()) {
        return allowed ? profile_result(&data_020e1b88) : 0;
    }
    int index = -1;
    if (!Spawner_SoundFlagSet()) {
        index = Spawner_FirstEventOn(data_020d06a4, 8);
    }
    if (index != -1) {
        int needs = data_020d0664[index];
        if ((u32) needs != EventAnnounce_CurrentEvent() && needs != EVENT_ANY) {
            index = -1;
        }
    }
    if (index != -1) {
        return allowed ? profile_result(&data_020d06a4[index].profile) : 0;
    }
    if (Spawner_Profile56Allowed() || SceneQuery_Current() != SCENE_9) {
        return 0;
    }
    return code_result(0xd025);
}
CLEAN_AS(func_020846cc, Spawner_CheckEvents06a4In)

/* func_020847e4: whether the current player's villager part has a block 0 whose object is in
 * use at step band 1, and neither sound flag is set. */
int Spawner_PlayerBlock0Ready(void)
{
    u8 *record = PlayerRecords_Current();
    VillagerPartBlock *block = NULL;
    if (record != NULL) {
        block = VillagerPart_Block((VillagerPart *) PlayerRecord_VillagerPart(record), 0);
    }
    if (block == NULL || ItemObject_IsInUse((ItemObject *) VillagerPartBlock_Object(block)) == 0 ||
        ItemObject_StepBand((ItemObject *) VillagerPartBlock_Object(block)) != 1 || Spawner_SoundFlagSet()) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020847e4, Spawner_PlayerBlock0Ready)

/* func_02084834 (check 0, priority 4).
 * QUIRK: declared without a result, as Spawner_CheckD023. */
void Spawner_CheckProfile56(void)
{
    (void) Spawner_CheckProfile56In(1);
}
CLEAN_AS(func_02084834, Spawner_CheckProfile56)

/* func_02084840: the entry of profile 0x56 while Spawner_Profile56Allowed and the check mode
 * allows it. */
int Spawner_CheckProfile56In(int check_mode)
{
    if (!Spawner_Profile56Allowed() || !mode_allows(check_mode)) {
        return 0;
    }
    return profile_result(&data_020e1b84);
}
CLEAN_AS(func_02084840, Spawner_CheckProfile56In)

/* func_02084890: whether this console is not in the session, flag 8 of the object at
 * data_021d27ac is set, neither sound flag is set and the player lacks flag 1. */
int Spawner_Profile56Allowed(void)
{
    return !in_session() && Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), OBJECT_FLAG_8) != 0 &&
           !Spawner_SoundFlagSet() && !Spawner_PlayerHasFlag1();
}
CLEAN_AS(func_02084890, Spawner_Profile56Allowed)

/* func_020848d0 (placer): 0x8000 to -x and 0x6000 to +z of the corner of the first tile with
 * flag 1 holding a building 0x5014-0x501a, at height 0, facing angle 0x4000; 0 without a map
 * or such a tile. */
int Spawner_PlaceBelowBuilding(Spawner *self, Vec3 *position, u16 *angle)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    int acre_x = 0, acre_z = 0, x = 0, z = 0;
    if (map == NULL) {
        return 0;
    }
    u16 first = BUILDING_5014;
    u16 last = BUILDING_501A;
    if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, TILE_FLAG_1, 0) == 0) {
        return 0;
    }
    angle[0] = 0;
    angle[1] = ANGLE_QUARTER;
    angle[2] = 0;
    AcreTile_PositionInAcre(position, (u32) acre_x, (u32) acre_z, (u32) x, (u32) z);
    position->x -= 0x8000;
    position->z += 0x6000;
    position->y = 0;
    return 1;
}
CLEAN_AS(func_020848d0, Spawner_PlaceBelowBuilding)

/* func_0208496c (check 2, priority 4): the entry of code 0xd019 in scene 0 while the player
 * has flag 0x23 and the scene byte at data_020e54b0 is 1-5 or 6; 0 while either sound flag
 * is set or this console is in the session. */
int Spawner_CheckD019(void)
{
    u8 *record = PlayerRecords_Current();
    if (SceneQuery_Current() != SCENE_0 || Spawner_SoundFlagSet() || in_session() || record == NULL ||
        PlayerRecord_TestFlag(record, PLAYER_FLAG_23) == 0) {
        return 0;
    }
    if (SceneKinds_IsHouseRoom(SceneQuery_Previous()) != 0 || SceneQuery_Previous() == 6) {
        return code_result(0xd019);
    }
    return 0;
}
CLEAN_AS(func_0208496c, Spawner_CheckD019)

/* func_020849e8 (placer): outdoors, 0x4000 to +z of the centre of the first tile with flag 1
 * holding a building 0x5014-0x501a; 0 without a map or such a tile, and in a room. */
int Spawner_PlaceInFrontOfBuilding(Spawner *self, Vec3 *position)
{
    (void) self;
    if (!outdoors()) {
        return 0;
    }
    AcreMap *map = data_021c80bc;
    int acre_x = 0, acre_z = 0, x = 0, z = 0;
    if (map == NULL) {
        return 0;
    }
    u16 first = BUILDING_5014;
    u16 last = BUILDING_501A;
    if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, TILE_FLAG_1, 0) == 0) {
        return 0;
    }
    AcreTile_TileCentreInAcre(position, acre_x, acre_z, x, z);
    position->z += 0x4000;
    return 1;
}
CLEAN_AS(func_020849e8, Spawner_PlaceInFrontOfBuilding)

/* func_02084a78 (check 1, priority 4): the entry of code 0xd011 in scene 0 while func_02087ea0
 * accepts part 0x30 of the object at data_021d27ac and this console is not in the session. */
int Spawner_CheckD011(void)
{
    if (SceneQuery_Current() != SCENE_0 || Block021d27acPart30_IsSet(Block021d27ac_Part30(Block021d27ac_Get())) == 0 ||
        in_session()) {
        return 0;
    }
    return code_result(0xd011);
}
CLEAN_AS(func_02084a78, Spawner_CheckD011)

/* func_02084ad0: whether either of the flags at data_021f4b18 and data_021f4b1c (the ones the
 * scenes' sound classes test) is set. */
int Spawner_SoundFlagSet(void)
{
    return Block020b220c_Flag4b18() != 0 || Block020b220c_Flag4b1c() != 0;
}
CLEAN_AS(func_02084ad0, Spawner_SoundFlagSet)

/* func_02084af0: whether there is a current player and its record has flag 1. */
int Spawner_PlayerHasFlag1(void)
{
    u8 *record = PlayerRecords_Current();
    return record != NULL && PlayerRecord_TestFlag(record, PLAYER_FLAG_1) != 0;
}
CLEAN_AS(func_02084af0, Spawner_PlayerHasFlag1)

/* func_02084b14: the index of the first of `count` events that is on now, -1 when none is. */
int Spawner_FirstEventOn(const SpawnerEvent *events, int count)
{
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < count; i++) {
        if (Spawner_EventOn(events[i].event, &now) != 0) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02084b14, Spawner_FirstEventOn)

/* ---- Requests */

/* func_02084b54: the overlay loaded for the last actor released, if there is one. */
void Spawner_ReleaseOverlay(Spawner *self)
{
    if (self->overlay_loaded) {
        OverlaySlots_Release((u8) self->overlay);
        Spawner_ForgetOverlay(self);
    }
}
CLEAN_AS(func_02084b54, Spawner_ReleaseOverlay)

/* func_02084b74: a pending request carried out and cleared. When its profile is in `table` and
 * it is for the current scene, the entry's placer sets the position and angle (the angle
 * starts at 0), the entry's overlay is loaded (or the spawner notes it has none) and the actor
 * is made under the spawner; when that worked, outdoors and with this console outside the
 * session, the position also goes to func_02042fd4. The entry, when the actor was made, else 0.
 * BUG: the position starts as whatever is on the stack, and is used as such when the placer
 * finds no place; here it starts at the origin. */
const SpawnerEntry *Spawner_Serve(Spawner *self, const SpawnerEntry *table, int count)
{
    SpawnerRequest *request = &data_020e1ca8;
    const SpawnerEntry *made = NULL;
    if (!Spawner_IsPending((int) (intptr_t) self, request)) {
        return NULL;
    }
    const SpawnerEntry *entry = Spawner_FindProfile(&request->profile, table, count);
    if (entry != NULL && request->scene == SceneQuery_Current()) {
        Vec3 position = {0, 0, 0};
        s16 angle[3] = {0, 0, 0};
        if (entry->place.ptr != 0) {
            void *object;
            uintptr_t place = member_target(&entry->place, self, &object);
            ((int (*)(void *, Vec3 *, s16 *, SpawnerRequest *)) place)(object, &position, angle, request);
        }
        if (entry->flags & SPAWNER_ENTRY_LOADS_OVERLAY) {
            OverlaySlots_Load((u8) entry->overlay);
            Spawner_NoteOverlay(self, &entry->overlay);
        } else {
            Spawner_ForgetOverlay(self);
        }
        if (Actor_Spawn(entry->profile, entry->code, &position, angle, self) != 0) {
            if (outdoors() && !in_session()) {
                Vec3 copy = position;
                TileRequests_ClearSpawnTile(&copy);
            }
            made = entry;
        }
    }
    Spawner_ClearRequest(request);
    return made;
}
CLEAN_AS(func_02084b74, Spawner_Serve)

/* func_02084c60: the checks run in order while their priority is above the pending request's;
 * the first one that answers an entry the request is replaced with stops them (1). 0 when
 * none did. */
int Spawner_RunChecks(Spawner *self)
{
    const SpawnerCheck *check = data_020e1d08;
    int scene = SceneQuery_Current();
    for (int i = 0; i < SPAWNER_CHECKS; i++, check++) {
        if (check->priority <= data_020e1ca8.priority) {
            break;
        }
        if (check->check.ptr == 0) {
            continue;
        }
        void *object;
        uintptr_t target = member_target(&check->check, self, &object);
        int entry = ((int (*)(void *)) target)(object);
        if (entry != 0 && Spawner_Request((const u16 *) (intptr_t) entry, check->priority, scene, NULL)) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02084c60, Spawner_RunChecks)

/* func_02084cd0: profile `*profile` asked for in `scene` at `position` with priority 1, unless
 * the player has flag 1 or this console is in the session. Whether the request was taken. */
int Spawner_RequestAt(const u16 *profile, int scene, const Vec3 *position)
{
    if (Spawner_PlayerHasFlag1() || in_session()) {
        return 0;
    }
    return Spawner_Request(profile, 1, scene, position);
}
CLEAN_AS(func_02084cd0, Spawner_RequestAt)

/* func_02084d08: the request replaced when `priority` is above the pending one's; whether it
 * was. */
int Spawner_Request(const u16 *profile, u32 priority, int scene, const Vec3 *position)
{
    if (data_020e1ca8.priority < priority) {
        Spawner_SetRequest(&data_020e1ca8, profile, (u8) scene, (u8) priority, position);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02084d08, Spawner_Request)

/* func_02084d34: the first of `count` entries for profile `*profile`, NULL when none is. */
const SpawnerEntry *Spawner_FindProfile(const u16 *profile, const SpawnerEntry *table, int count)
{
    for (int i = 0; i < count; i++) {
        if (*profile == table[i].profile) {
            return &table[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_02084d34, Spawner_FindProfile)

/* func_02084d5c: the first of `count` entries made with `*code`, NULL when none is. */
const SpawnerEntry *Spawner_FindCode(const u16 *code, const SpawnerEntry *table, int count)
{
    for (int i = 0; i < count; i++) {
        if (table[i].code == *code) {
            return &table[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_02084d5c, Spawner_FindCode)

/* func_02084d84 */
void Spawner_ForgetOverlay(Spawner *self)
{
    self->overlay_loaded = 0;
}
CLEAN_AS(func_02084d84, Spawner_ForgetOverlay)

/* func_02084d8c */
void Spawner_NoteOverlay(Spawner *self, const u32 *overlay)
{
    self->overlay_loaded = 1;
    self->overlay = *overlay;
}
CLEAN_AS(func_02084d8c, Spawner_NoteOverlay)

/* func_02084d9c: whether the request has a priority (1-4). */
int Spawner_IsPending(int self, const SpawnerRequest *request)
{
    (void) self;
    return request->priority > SPAWNER_PRIORITY_NONE && request->priority <= SPAWNER_PRIORITY_MAX;
}
CLEAN_AS(func_02084d9c, Spawner_IsPending)

/* func_02084dac: no profile (0), scene 0x33, no priority, at the default position. */
void Spawner_ClearRequest(SpawnerRequest *request)
{
    Spawner_SetRequest(request, &data_020e1b8c, SPAWNER_NO_SCENE, SPAWNER_PRIORITY_NONE, NULL);
}
CLEAN_AS(func_02084dac, Spawner_ClearRequest)

/* func_02084dc8: the request set; without a position it stands at data_021fbee8. */
void Spawner_SetRequest(SpawnerRequest *request, const u16 *profile, u8 scene, u8 priority, const Vec3 *position)
{
    request->profile = *profile;
    request->scene = scene;
    request->priority = priority;
    const Vec3 *from = position != NULL ? position : &data_021fbee8;
    /* One field after the other, as the game copies them. */
    request->position.x = from->x;
    request->position.y = from->y;
    request->position.z = from->z;
}
CLEAN_AS(func_02084dc8, Spawner_SetRequest)

/* func_02084f84: the destructor of the spawner's part at 0x50; nothing to do. */
void Spawner_PartDestruct(void *part)
{
    (void) part;
}
CLEAN_AS(func_02084f84, Spawner_PartDestruct)

/* func_02084f88: the constructor of the spawner's part at 0x50; nothing to do. */
void Spawner_PartConstruct(void *part)
{
    (void) part;
}
CLEAN_AS(func_02084f88, Spawner_PartConstruct)

/* ---- The process's phases and the villagers it makes
 *
 * The vtable data_020e1cc0 has Spawner_Create in slot 0 (the create phase's work, done at
 * once), Spawner_Delete in slot 3 (the delete phase's) and Spawner_Execute in slot 6 (the
 * execute phase's). Creating the spawner makes the villagers of the scene: those out in the
 * town (Spawner_PlaceTownVillagers), the owner of the villager's house shown
 * (Spawner_SpawnHouseOwner) or the villager visiting the player's house
 * (Spawner_SpawnHouseGuest). */

#include "actor_table.h"
#include "field_collision.h"
#include "npc_id.h"
#include "npc_lookup.h"
#include "packed_bytes.h"
#include "scene_exit.h"
#include "scene_share_table.h"
#include "tile_grid.h"
#include "town_objects.h"
#include "town_villager.h"
#include "villager_events.h"
#include "villager_furniture.h"
#include "villager_home.h"
#include "villager_move.h"
#include "villager_move_record.h"
#include "villager_outdoors.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_status.h"
#include "villager_town.h"

extern VillagerTown data_021e5a2c; /* the town's villagers */
/* The villagers' entries behind the session's records (scene_share_table.h). */
extern SceneShareEntry data_021d213c[SCENE_SHARE_TABLE_E_COUNT];
extern const int data_020d0648; /* the number of events of data_020d0684 */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The profiles of the villager actors made here. */
#define SPAWNER_PROFILE_EVENT_VILLAGER 0x80 /* the villager VillagerState_GetIndex162 names */
#define SPAWNER_PROFILE_COMPANION 0x81      /* the one VillagerState_GetIndex163 names, with it */
#define SPAWNER_PROFILE_GUEST 0x82          /* a villager who said it would come */
#define SPAWNER_PROFILE_MOVING 0x83         /* the villager planning to move, while it does */
#define SPAWNER_PROFILE_OUTDOORS 0x84       /* a villager out in the town */
#define SPAWNER_PROFILE_VILLAGER 0x85       /* a villager at home */
#define SPAWNER_PROFILE_STAYING 0x86        /* a villager at home in event 10, status 3 */
#define SPAWNER_PROFILE_EVENT_GUEST 0x87    /* the visitor of event 10 */
#define SPAWNER_PROFILE_NONE 0xd8           /* no companion */

#define SPAWNER_PERSON_E 0xe000 /* a villager's person code (scene_share_table.h) */
#define SPAWNER_PERSON_INDEX 0x0fff
#define SPAWNER_NO_PERSON 0xfff1

#define SPAWNER_VILLAGERS 8
#define SPAWNER_NO_VILLAGER (-1)
#define SPAWNER_EVENT_10 10                   /* VillagerTown_CurrentEvent's event 10 */
#define SPAWNER_NO_EVENT VILLAGER_TOWN_EVENTS /* VillagerTown_CurrentEvent: none on */
#define SPAWNER_CODE_D008 0xd008              /* the entry Spawner_Create treats apart */
#define SPAWNER_SCENE_2C 0x2c
#define SPAWNER_STATUS_STAYING 3 /* VillagerStatus_Stay */
#define SPAWNER_DOOR_X 1         /* the tile before a house's door, from its tile */
#define SPAWNER_DOOR_Z 2

/* The player's appointment with a villager: an NpcId at 0xa4 of the player's villager part, an
 * object of type 0x15 at 0xb4 and the time at 0xc0. The object's low five bits say how far it
 * went: with 0 the villager comes within 30 minutes of the time, with 1-3 within 60. */
#define SPAWNER_APPOINTMENT 0xa4
#define SPAWNER_APPOINTMENT_OBJECT 0x10
#define SPAWNER_APPOINTMENT_TIME 0x1c
#define SPAWNER_APPOINTMENT_TYPE 0x15
#define SPAWNER_APPOINTMENT_STEPS 4
#define SPAWNER_APPOINTMENT_MINUTES 30
#define SPAWNER_APPOINTMENT_LATE_MINUTES 60

/* The tile grid kept in the spawner's part at 0x50 (tile_grid.h). */
static TileGrid *spawner_grid(Spawner *self)
{
    return (TileGrid *) (void *) self->part_50;
}

static u16 spawner_villager_person(int index)
{
    return (u16) (((u32) index & SPAWNER_PERSON_INDEX) | SPAWNER_PERSON_E);
}

/* A random angle about Y, a whole number of quarter turns. */
static s16 spawner_random_quarter(void)
{
    return (s16) (u16) (MainRandom_Below(4) << 14);
}

/* The centre of the tile before the villager's house's door. */
static void spawner_at_door(u8 *villager, Vec3 *position)
{
    const VillagerPlot *home = VillagerHome_Tile(villager);
    AcreTile_TileCentre(position, (u32) (home->x + SPAWNER_DOOR_X), (u32) (home->z + SPAWNER_DOOR_Z));
}

/* The x and z of an entry's place. */
static void spawner_entry_place(const SceneShareEntry *entry, Vec3 *position)
{
    PackedBytes_UnpackPoint(entry->place, (u32 *) (void *) &position->x, (u32 *) (void *) &position->z);
}

/* func_0208541c (vtable slot 6, the execute phase): in scene 0 the villagers' idle frames are
 * counted and, outside the session, the roster woken up. Outside the session, each villager
 * with a state entry and no actor counts its entry down while byte 0x18 is set: byte 0x18 is
 * cleared when the counter reaches 0, and the entry's tally ticks. Always 1. */
int Spawner_Execute(void)
{
    VillagerTown *town = &data_021e5a2c;
    if (SceneQuery_CurrentIs0() != 0) {
        VillagerEvent_CountIdleFrame();
        if (!in_session()) {
            VillagerRoster_WakeUp(town);
        }
    }
    if (in_session()) {
        return 1;
    }
    for (int i = 0; i < SPAWNER_VILLAGERS; i++) {
        u8 *villager = VillagerRoster_At(town, i);
        if (villager == NULL || NpcId_IsValid(TownVillager_NpcId(villager)) == 0) {
            continue;
        }
        VillagerState *state = VillagerStatus_StateEntry(villager);
        if (state == NULL) {
            continue;
        }
        ItemCode person = spawner_villager_person(i);
        if (Actors_GetE(&person) != NULL || VillagerState_GetByte18(state) == 0) {
            continue;
        }
        VillagerState_CountDown(state);
        if (VillagerState_GetCounter(state) == 0) {
            VillagerState_SetByte18(state, 0);
        }
        VillagerTally_Tick(VillagerState_Tally(state), 0);
    }
    return 1;
}
CLEAN_AS(func_0208541c, Spawner_Execute)

/* func_020854f4 (vtable slot 3, the delete phase): the overlay released, the request cleared
 * and the villagers' index 0x160 cleared. Leaving scene 0, the villagers are updated with the
 * clock and, when the next scene is the house of a villager (scenes 0x11-0x18), that
 * villager's furniture stored. Always 1. */
int Spawner_Delete(Spawner *self)
{
    VillagerTown *town = &data_021e5a2c;
    Spawner_ReleaseOverlay(self);
    Spawner_ClearRequest(&data_020e1ca8);
    VillagerState_ClearIndex160();
    if (SceneQuery_CurrentIs0() == 0) {
        return 1;
    }
    VillagerTown_UpdateWithClock(town);
    int next = SceneExit_NextScene();
    if (SceneQuery_In11(next) == 0) {
        return 1;
    }
    u8 *villager = VillagerRoster_ForCode(town, (s8) next);
    if (villager != NULL && NpcId_IsValid(TownVillager_NpcId(villager)) != 0) {
        VillagerFurniture_StoreItems(villager);
    }
    return 1;
}
CLEAN_AS(func_020854f4, Spawner_Delete)

/* func_02085558 (vtable slot 0, the create phase): parts 0x24 and 0x31 of the object at
 * data_021d27ac prepared; in scene 0 the event villager updated, the states applied and index
 * 0x164 cleared; coming from scene 0, indices 0x162 and 0x163 cleared (and the states applied)
 * when the event villager changed. Then the scene's villagers made: outdoors (unless the sound
 * flag is set) those out in the town, after drawing index 0x160 outside the session; in a
 * villager's house its owner; in the player's house, outside event 10, index 0x164 and the
 * extra visitors cleared, and in its first room the guest. Then the checks run and the request
 * served; an entry served gets part 0x31 told, and part 0x24 too unless it is code 0xd008 and
 * func_02087e38 refuses. Last part 0x0c updated in the session and, in scene 0, the villagers
 * updated with the clock. Always 1. */
int Spawner_Create(Spawner *self)
{
    int entries = data_020d0644;
    VillagerTown *town = &data_021e5a2c;

    NearSpot_ClearServed((NearSpot *) (void *) Block021d27ac_Part24(Block021d27ac_Get()));
    BesideSpot_ClearServed(Block021d27ac_Part31(Block021d27ac_Get()));
    if (SceneQuery_CurrentIs0() != 0) {
        VillagerTown_UpdateEventVillager(town);
        VillagerTown_ApplyEventStates(town);
        VillagerState_SetIndex164((unsigned char) SPAWNER_NO_VILLAGER);
    } else if (SceneQuery_Is0(SceneQuery_Previous()) != 0) {
        DateTime now = {0};
        int index = VillagerState_GetIndex162();
        DateTime_Now(&now);
        if (index != SPAWNER_NO_VILLAGER && index != VillagerTown_FindEventVillager(town, &now)) {
            VillagerState_SetIndex162((unsigned char) SPAWNER_NO_VILLAGER);
            VillagerState_SetIndex163((unsigned char) SPAWNER_NO_VILLAGER);
            VillagerTown_ApplyEventStates(town);
        }
    }

    if (outdoors()) {
        if (Spawner_SoundFlagSet() == 0) {
            if (!in_session()) {
                const void *player = NULL;
                if (PlayerRecords_Current() != NULL) {
                    player = PlayerRecord_Player(PlayerRecords_Current());
                }
                VillagerOutdoors_DrawIndex160((const u8 *) town, player);
            }
            Spawner_PlaceTownVillagers(self);
        }
    } else if (SceneQuery_CurrentIn11() != 0) {
        Spawner_SpawnHouseOwner(self);
    } else if (SceneKinds_CurrentIsHouseRoom() != 0) {
        if (VillagerTown_CurrentEvent() != SPAWNER_EVENT_10 && VillagerState_GetIndex164() != SPAWNER_NO_VILLAGER) {
            VillagerState_SetIndex164((unsigned char) SPAWNER_NO_VILLAGER);
            TownObjects_ClearExtraVisitors();
        }
        if (SceneKinds_CurrentHouseRoomIndex() == 0) {
            Spawner_SpawnHouseGuest(self);
        }
    }

    Spawner_RunChecks(self);
    const SpawnerEntry *served = Spawner_Serve(self, data_020e1d8c, entries);
    if (served != NULL) {
        BesideSpot_SetServed(Block021d27ac_Part31(Block021d27ac_Get()));
        if (served->code != SPAWNER_CODE_D008 ||
            NearSpot_Found((const NearSpot *) (void *) Block021d27ac_Part24(Block021d27ac_Get())) != 0) {
            NearSpot_SetServed((NearSpot *) (void *) Block021d27ac_Part24(Block021d27ac_Get()));
        }
    }
    Spawner_UpdatePartCInSession(self);
    if (SceneQuery_CurrentIs0() != 0) {
        VillagerTown_UpdateWithClock(town);
    }
    return 1;
}
CLEAN_AS(func_02085558, Spawner_Create)

/* func_020856fc: outside the session, in the player's house: with no event on, the villager of
 * the player's appointment (SPAWNER_APPOINTMENT) when its time is near enough, as profile 0x82;
 * an appointment with steps done that is more than 60 minutes past instead clears the extra
 * visitors and settles that villager's state. In event 10 the visitor (index 0x164, picked
 * when coming from scene 0), as profile 0x87. A villager of steps 1-3 or of event 10 (not
 * coming from scene 0) whose entry is in use stands at the entry's place; else at the origin.
 * QUIRK: the entry's angle is copied out, but the actor is made with no angle. */
void Spawner_SpawnHouseGuest(Spawner *self)
{
    VillagerTown *town = &data_021e5a2c;
    if (in_session()) {
        return;
    }
    int profile = SPAWNER_PROFILE_VILLAGER;
    int spawn = 0;
    Vec3 position = {0, 0, 0};
    u16 person = SPAWNER_NO_PERSON;
    u8 angle_unused[2];

    int event = VillagerTown_CurrentEvent();
    if (event == SPAWNER_NO_EVENT) {
        u8 *appointment = PlayerRecord_VillagerPart(PlayerRecords_Current()) + SPAWNER_APPOINTMENT;
        ItemObject *object = (ItemObject *) (void *) (appointment + SPAWNER_APPOINTMENT_OBJECT);
        const NpcId *npc = (const NpcId *) (const void *) appointment;
        int index = SPAWNER_NO_VILLAGER;
        if (ItemObject_IsInUse(object) != 0 && ItemObject_Type(object) == SPAWNER_APPOINTMENT_TYPE) {
            DateTime now = {0};
            DateTime_Now(&now);
            const DateTime *when = (const DateTime *) (const void *) (appointment + SPAWNER_APPOINTMENT_TIME);
            int minutes = DateTime_MinutesBetween(when, &now);
            if (ItemObject_Low5(object) == 0) {
                if (minutes <= SPAWNER_APPOINTMENT_MINUTES) {
                    index = VillagerRoster_IndexOf(town, npc);
                }
            } else if ((u32) ItemObject_Low5(object) < SPAWNER_APPOINTMENT_STEPS) {
                if (minutes <= SPAWNER_APPOINTMENT_LATE_MINUTES) {
                    index = VillagerRoster_IndexOf(town, npc);
                    if (ActorTable_IsKindESlot((u32) index) && data_021d213c[index].in_use != 0) {
                        spawner_entry_place(&data_021d213c[index], &position);
                        MI_CpuCopy8(data_021d213c[index].angle, angle_unused, sizeof(angle_unused));
                    }
                } else {
                    TownObjects_ClearExtraVisitors();
                    u8 *villager = VillagerRoster_Find(town, npc);
                    if (villager != NULL) {
                        VillagerState_SettleState(VillagerStatus_StateEntry(villager));
                    }
                }
            }
        }
        if (index != SPAWNER_NO_VILLAGER) {
            person = spawner_villager_person(index);
            profile = SPAWNER_PROFILE_GUEST;
            spawn = 1;
        }
    } else if (event == SPAWNER_EVENT_10) {
        if (SceneQuery_Is0(SceneQuery_Previous()) != 0) {
            VillagerTown_PickIndex164(town);
        }
        int index = VillagerState_GetIndex164();
        if (ActorTable_IsKindESlot((u32) index)) {
            person = spawner_villager_person(index);
            profile = SPAWNER_PROFILE_EVENT_GUEST;
            if (SceneQuery_Is0(SceneQuery_Previous()) == 0 && data_021d213c[index].in_use != 0) {
                spawner_entry_place(&data_021d213c[index], &position);
                MI_CpuCopy8(data_021d213c[index].angle, angle_unused, sizeof(angle_unused));
            }
            spawn = 1;
        }
    }
    if (spawn) {
        Actor_Spawn(profile, person, &position, NULL, self);
    }
}
CLEAN_AS(func_020856fc, Spawner_SpawnHouseGuest)

/* func_020858ac: in the house of villager n (scenes 0x11-0x18), that villager, when valid: at
 * its shared record's place and angle when the record is in use and func_020a7278 answers 0,
 * else on a free tile (Spawner_PlaceOnFreeTile) facing a random quarter turn; nothing when
 * there is none. Outside the session it is the event villager (index 0x162, profile 0x80) with
 * its companion (index 0x163, profile 0x81, made after it on another free tile), the villager
 * planning to move while it does (0x83), or in event 10 a villager with status 3 (0x86); else
 * profile 0x85. */
void Spawner_SpawnHouseOwner(Spawner *self)
{
    VillagerTown *town = &data_021e5a2c;
    int index = SceneQuery_CurrentIndexIn11();
    u8 *villager = VillagerRoster_At(town, index);
    if (villager == NULL || NpcId_IsValid(TownVillager_NpcId(villager)) == 0) {
        return;
    }

    u16 person = spawner_villager_person(index);
    u16 companion = SPAWNER_NO_PERSON;
    Vec3 position = {0, 0, 0};
    s16 angle[3] = {0, 0, 0};

    SceneShareEntry *record = SceneShareTable_SharedRecordE(&person);
    int placed;
    if (LinkGlobal_HoldsScene() == 0 && record != NULL && record->in_use != 0) {
        spawner_entry_place(record, &position);
        MI_CpuCopy8(record->angle, &angle[1], sizeof(angle[1]));
        placed = 1;
    } else {
        placed = Spawner_PlaceOnFreeTile(self, &position);
        angle[1] = spawner_random_quarter();
    }
    if (placed == 0) {
        return;
    }

    int profile = SPAWNER_PROFILE_VILLAGER;
    int companion_profile = SPAWNER_PROFILE_NONE;
    if (!in_session()) {
        if (index == VillagerState_GetIndex162()) {
            profile = SPAWNER_PROFILE_EVENT_VILLAGER;
            if (ActorTable_IsKindESlot((u32) VillagerState_GetIndex163())) {
                companion = spawner_villager_person(VillagerState_GetIndex163());
                companion_profile = SPAWNER_PROFILE_COMPANION;
            }
        } else if (index == VillagerMove_VillagerIndex(town)) {
            if (VillagerMoveRecord_IsIdle(VillagerMove_Record(town)) == 0) {
                profile = SPAWNER_PROFILE_MOVING;
            }
        } else if (VillagerTown_CurrentEvent() == SPAWNER_EVENT_10 &&
                   VillagerStatus_Stay(villager) == SPAWNER_STATUS_STAYING) {
            profile = SPAWNER_PROFILE_STAYING;
        }
    }

    Actor_Spawn(profile, person, &position, angle, self);
    if (companion_profile == SPAWNER_PROFILE_NONE) {
        return;
    }
    if (((companion & 0xf000) >> 12) == SCENE_SHARE_KIND_E) {
        Spawner_PlaceOnFreeTile(self, &position);
        angle[1] = spawner_random_quarter();
        Actor_Spawn(companion_profile, companion, &position, angle, self);
    }
}
CLEAN_AS(func_020858ac, Spawner_SpawnHouseOwner)

/* func_02085a30: as many of the villagers out in the town as NpcLookup_FourUnlessSlotTaken
 * allows (counting those made), in order, as profile 0x84. By its shared record in use, each
 * stands at the record's place and angle when the record is for the scene shown, else before
 * its door. Without one, when func_020a7278 answers nonzero and its own entry is in use, it
 * stands at the entry's place (kept off raised ground, Spawner_KeepOffRaisedGround) when the
 * entry is for the scene shown, scene 0, scene 31 or scene 0x2c, else before its door. Else
 * before its door. */
void Spawner_PlaceTownVillagers(Spawner *self)
{
    VillagerTown *town = &data_021e5a2c;
    int limit = NpcLookup_FourUnlessSlotTaken();
    if (limit <= 0) {
        return;
    }
    int made = 0;
    for (int i = 0; i < SPAWNER_VILLAGERS && made < limit; i++) {
        u8 *villager = VillagerRoster_At(town, i);
        if (villager == NULL || NpcId_IsValid(TownVillager_NpcId(villager)) == 0 ||
            VillagerRoster_IsOutside(town, TownVillager_NpcId(villager)) == 0) {
            continue;
        }
        u8 scene = 0;
        u16 person = spawner_villager_person(i);
        Vec3 position = {0, 0, 0};
        s16 angle[3] = {0, 0, 0};

        SceneShareEntry *record = SceneShareTable_SharedRecordE(&person);
        if (record != NULL && record->in_use != 0) {
            PackedBytes_SplitScene(&record->scene, &scene, NULL);
            if (scene == SceneQuery_Current()) {
                spawner_entry_place(record, &position);
                MI_CpuCopy8(record->angle, &angle[1], sizeof(angle[1]));
            } else {
                spawner_at_door(villager, &position);
            }
        } else if (LinkGlobal_HoldsScene() != 0 && data_021d213c[i].in_use != 0) {
            SceneShareEntry *entry = &data_021d213c[i];
            PackedBytes_SplitScene(&entry->scene, &scene, NULL);
            if (scene != SceneQuery_Current() && SceneQuery_Is0(scene) == 0 && SceneQuery_Is31(scene) == 0 &&
                scene != SPAWNER_SCENE_2C) {
                spawner_at_door(villager, &position);
            } else {
                spawner_entry_place(entry, &position);
                Spawner_KeepOffRaisedGround(villager, &position);
            }
        } else {
            spawner_at_door(villager, &position);
        }
        if (Actor_Spawn(SPAWNER_PROFILE_OUTDOORS, person, &position, angle, self) != 0) {
            made++;
        }
    }
}
CLEAN_AS(func_02085a30, Spawner_PlaceTownVillagers)

/* func_02085be0: a villager of status 0 whose ground at `position` is not at height 0 is moved
 * before its door. */
void Spawner_KeepOffRaisedGround(u8 *villager, Vec3 *position)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 0);
    if (VillagerStatus_Get(villager) == 0 && CollisionGround_GetHeight(&ground, 0) != 0) {
        spawner_at_door(villager, position);
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_02085be0, Spawner_KeepOffRaisedGround)

/* The entry a check answered, or NULL. */
static const SpawnerEntry *spawner_answer(int result)
{
    return (const SpawnerEntry *) (intptr_t) result;
}

/* func_02085c2c: the code of the entry the checks would answer now (run without a check mode),
 * 0xfff1 for none or when the check of profile 0x56 or of the events at data_020d06a4 answers.
 * The events 0x3d, 0x3f and 0x40 count only while func_0209fa30 answers 0 for
 * data_021f3b85. */
void Spawner_PeekCode(u16 *code)
{
    int started = TownStartDay_IsSet((TownStartDay *) (void *) data_021f3b85);
    int blocked = Spawner_CheckProfile56In(0);
    if (blocked == 0) {
        blocked = Spawner_CheckEvents06a4In(0);
    }
    const SpawnerEntry *entry;
    if (blocked != 0) {
        *code = SPAWNER_NO_PERSON;
    } else if ((entry = spawner_answer(Spawner_CheckD00DIn(0))) != NULL) {
        *code = entry->code;
    } else if ((entry = spawner_answer(Spawner_CheckD002In(0))) != NULL) {
        *code = entry->code;
    } else if (started == 0 && Spawner_EventOn(EVENT_3D, NULL) != 0) {
        *code = 0xd00e;
    } else if ((entry = spawner_answer(Spawner_CheckD022In(0))) != NULL) {
        *code = entry->code;
    } else if ((entry = spawner_answer(Spawner_CheckD023In(0))) != NULL) {
        *code = entry->code;
    } else if ((entry = spawner_answer(Spawner_CheckEvents(data_020d0684, data_020d0654, data_020d0648, 0))) != NULL) {
        *code = entry->code;
    } else if (started == 0 && Spawner_EventOn(0x3f, NULL) != 0) {
        *code = 0xd00a;
    } else if (started == 0 && Spawner_EventOn(0x40, NULL) != 0) {
        *code = 0xd00b;
    } else if ((entry = spawner_answer(Spawner_CheckD020In(0))) != NULL) {
        *code = entry->code;
    } else {
        *code = SPAWNER_NO_PERSON;
    }
}
CLEAN_AS(func_02085c2c, Spawner_PeekCode)

/* func_02085d2c: whether `event` is on at `when` (now when it is NULL), asked with a copy. */
int Spawner_EventOn(u32 event, const DateTime *when)
{
    DateTime now = {0};
    if (when == NULL) {
        DateTime_Now(&now);
        when = &now;
    }
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof(copy));
    return EventCalendar_State((int) event, &copy, 0) != 0;
}
CLEAN_AS(func_02085d2c, Spawner_EventOn)

/* func_02085d6c: a random free tile of the grid in the spawner's part 0x50 (TileGrid_Build),
 * of rows 0-13 (rows 14 and 15 are unmarked first), its centre into `position`. 0 when the
 * grid cannot be built or has no free tile. */
int Spawner_PlaceOnFreeTile(Spawner *self, Vec3 *position)
{
    TileGrid *grid = spawner_grid(self);
    if (TileGrid_Build(grid) == 0) {
        return 0;
    }
    for (u32 x = 0; x < TILE_GRID_SIZE; x++) {
        TileGrid_Unmark(grid, x, TILE_GRID_SEARCH_ROWS);
        TileGrid_Unmark(grid, x, TILE_GRID_SEARCH_ROWS + 1);
    }
    int count = 0;
    for (u32 z = 0; z < TILE_GRID_SEARCH_ROWS; z++) {
        for (u32 x = 0; x < TILE_GRID_SIZE; x++) {
            if (TileGrid_IsMarked(grid, x, z)) {
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    u32 pick = MainRandom_Below(count);
    for (u32 z = 0; z < TILE_GRID_SEARCH_ROWS; z++) {
        for (u32 x = 0; x < TILE_GRID_SIZE; x++) {
            if (!TileGrid_IsMarked(grid, x, z)) {
                continue;
            }
            if (pick == 0) {
                AcreTile_TileCentre(position, x, z);
                return 1;
            }
            pick--;
        }
    }
    return 0;
}
CLEAN_AS(func_02085d6c, Spawner_PlaceOnFreeTile)

/* func_02085ed0: a new spawner (0x78 bytes, zeroed, from the auxiliary heap), or NULL.
 * QUIRK: the base process's vtable is stored, then the spawner's, as a C++ constructor does. */
Spawner *Spawner_New(void)
{
    Spawner *self = Heap_AllocAuxZeroed(sizeof(Spawner));
    if (self != NULL) {
        Process_Construct(&self->base);
        self->base.vtable = data_020da13c;
        self->base.vtable = data_020e1cc0;
        Spawner_PartConstruct(self->part_50);
    }
    return self;
}
CLEAN_AS(func_02085ed0, Spawner_New)

/* func_02085f04: the request's destructor (registered by __sinit_020c5f70); nothing to do. */
void Spawner_RequestDestruct(void *request)
{
    (void) request;
}
CLEAN_AS(func_02085f04, Spawner_RequestDestruct)
