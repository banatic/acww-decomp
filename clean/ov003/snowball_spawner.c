/* The process that puts the town's balls of snow in place (snowball_spawner.h). */
#include "snowball_spawner.h"

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/date_time.h"
#include "main/map_code.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/snowmen.h"
#include "snowball_spot.h"

static_assert(sizeof(SnowballSpawner) == 0x50, "the process");

/* The snowball actor (ov003/snowman.h) and its groups: the two loose balls, then two per
 * snowman. */
#define SNOWBALL_SPAWNER_ACTOR 0xbd
#define SNOWBALL_SPAWNER_FIRST_SNOWMAN_GROUP 2
/* The inner acres of the town map, 1 to 4 across and down. */
#define SNOWBALL_SPAWNER_FIRST_ACRE 1
#define SNOWBALL_SPAWNER_LAST_ACRE 4
/* The day turns at 6:00 for the snowmen (snowmen.h). */
#define SNOWBALL_SPAWNER_DAY_START_HOUR 6

/* The scene's map (acre_map.h), main's three snowmen, and the session. */
extern AcreMap *data_021c80bc;
extern SnowmenRecord data_021f3b56[SNOWMEN_COUNT];
extern NetSession *data_020ccf94;
/* The vtables: this class's and its base class's. */
extern const u32 data_ov003_0223c550[];
extern const u32 data_020da13c[];

/* func_ov003_02236274: the balls of each snowman standing in the inner acres made at the centre
 * of its tile, the head first; a snowman object main no longer records is replaced by the empty
 * tile. */
void SnowballSpawner_SpawnSnowmen(SnowballSpawner *self)
{
    AcreMap *map = data_021c80bc;

    for (u32 acre_z = SNOWBALL_SPAWNER_FIRST_ACRE; acre_z <= SNOWBALL_SPAWNER_LAST_ACRE; acre_z++) {
        for (u32 acre_x = SNOWBALL_SPAWNER_FIRST_ACRE; acre_x <= SNOWBALL_SPAWNER_LAST_ACRE; acre_x++) {
            AcreRecord *acre = NULL;
            if (acre_x < (u32) map->acres_wide && acre_z < (u32) map->acres_high && map->acres != NULL) {
                acre = (AcreRecord *) (void *) (map->acres + (acre_x + acre_z * (u32) map->acres_wide) * ACRE_MAP_ACRE_SIZE);
            }
            if (acre == NULL) {
                continue;
            }
            for (int z = 0; z < ACRE_RECORD_SIDE; z++) {
                for (int x = 0; x < ACRE_RECORD_SIDE; x++) {
                    u16 *code = AcreRecord_Tile(acre, (u32) x, (u32) z, 0);
                    if (code == NULL || !MapCode_IsSnowman(code)) {
                        continue;
                    }
                    int number = MapCode_SnowmanIndex(code);
                    if (!Snowmen_Get(data_021f3b56, (u32) number, NULL, NULL, NULL, NULL, NULL, NULL)) {
                        u16 empty = ACRE_MAP_ITEM_NONE;
                        AcreRecord_SetTile(acre, &empty, x, z, 0);
                        continue;
                    }
                    int head = number * 2 + SNOWBALL_SPAWNER_FIRST_SNOWMAN_GROUP;
                    Vec3 centre;
                    AcreTile_TileCentreInAcre(&centre, (int) acre_x, (int) acre_z, x, z);
                    Actor_Spawn(SNOWBALL_SPAWNER_ACTOR, head, &centre, NULL, self);
                    Actor_Spawn(SNOWBALL_SPAWNER_ACTOR, head + 1, &centre, NULL, self);
                }
            }
        }
    }
}
CLEAN_AS(func_ov003_02236274, SnowballSpawner_SpawnSnowmen)

/* func_ov003_02236374: the two loose balls made (groups 0 and 1) where main kept them, or at a
 * new spot each when it kept none (a point whose x is 0), the second away from the first; each
 * one made has its point kept. None while this system has a slot taken in the session, out of
 * the snow season or when a snowman was built today (by the snowmen's day, from 6:00): then
 * main's loose balls are reset. None either outside scene 0 or while all three snowmen are
 * recorded. */
void SnowballSpawner_SpawnLooseBalls(SnowballSpawner *self)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0 || !SceneQuery_IsSnowSeason()) {
        Snowmen_ResetLooseBalls(Snowmen_LooseBalls());
        return;
    }

    for (u32 number = 0; number < SNOWMEN_COUNT; number++) {
        DateTime today = {0};
        DateTime_Now(&today);
        if (today.hour < SNOWBALL_SPAWNER_DAY_START_HOUR) {
            DateTime_SubtractDays(&today, 1);
        }
        int head_size;
        int body_size;
        int face;
        u8 year;
        u8 month;
        u8 day;
        if (!Snowmen_Get(data_021f3b56, number, &head_size, &body_size, &face, &year, &month, &day)) {
            continue;
        }
        if (year == today.year && month == today.month && day == today.day) {
            Snowmen_ResetLooseBalls(Snowmen_LooseBalls());
            return;
        }
    }

    if (!SceneQuery_CurrentIs0()) {
        return;
    }
    if (Snowmen_AllRecorded(data_021f3b56)) {
        return;
    }

    /* Each ball's kept point is looked at, and read, with a call of its own. */
    Vec3 first;
    Vec3 second;
    if (Snowmen_LooseBalls()[0].position.x != 0) {
        first = Snowmen_LooseBalls()[0].position;
    } else {
        SnowballSpot_Pick(self, &first, NULL, 1);
    }
    if (Snowmen_LooseBalls()[1].position.x != 0) {
        second = Snowmen_LooseBalls()[1].position;
    } else {
        SnowballSpot_Pick(self, &second, &first, 1);
    }

    if (Actor_Spawn(SNOWBALL_SPAWNER_ACTOR, 0, &first, NULL, self) != 0) {
        Snowmen_LooseBalls()[0].position = first;
    }
    if (Actor_Spawn(SNOWBALL_SPAWNER_ACTOR, 1, &second, NULL, self) != 0) {
        Snowmen_LooseBalls()[1].position = second;
    }
}
CLEAN_AS(func_ov003_02236374, SnowballSpawner_SpawnLooseBalls)

/* func_ov003_022364c0 (vtable slot 3): the deletion is done at once. */
int SnowballSpawner_Delete(void)
{
    return 1;
}
CLEAN_AS(func_ov003_022364c0, SnowballSpawner_Delete)

/* func_ov003_022364c4 (vtable slot 9): the drawing is done at once. */
int SnowballSpawner_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov003_022364c4, SnowballSpawner_Draw)

/* func_ov003_022364c8 (vtable slot 6): the execution is done at once. */
int SnowballSpawner_Execute(void)
{
    return 1;
}
CLEAN_AS(func_ov003_022364c8, SnowballSpawner_Execute)

/* func_ov003_022364cc (vtable slot 0): the creation: the snowmen's balls, then the loose ones;
 * done at once. */
int SnowballSpawner_Create(SnowballSpawner *self)
{
    SnowballSpawner_SpawnSnowmen(self);
    SnowballSpawner_SpawnLooseBalls(self);
    return 1;
}
CLEAN_AS(func_ov003_022364cc, SnowballSpawner_Create)

/* func_ov003_022364e4 (vtable slot 17): the destructor, and the process freed. */
SnowballSpawner *SnowballSpawner_DestructFree(SnowballSpawner *self)
{
    self->base.vtable = data_ov003_0223c550;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov003_022364e4, SnowballSpawner_DestructFree)

/* func_ov003_0223650c (vtable slot 16): the destructor. */
SnowballSpawner *SnowballSpawner_Destruct(SnowballSpawner *self)
{
    self->base.vtable = data_ov003_0223c550;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov003_0223650c, SnowballSpawner_Destruct)

/* func_ov003_0223652c: the constructor: a process with this class's vtable. */
SnowballSpawner *SnowballSpawner_Construct(SnowballSpawner *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov003_0223c550;
    return self;
}
CLEAN_AS(func_ov003_0223652c, SnowballSpawner_Construct)

/* func_ov003_0223654c: the process made (zeroed, from the auxiliary heap) and constructed; NULL
 * when there is no room. */
SnowballSpawner *SnowballSpawner_New(void)
{
    SnowballSpawner *self = Heap_AllocAuxZeroed(sizeof(SnowballSpawner));
    if (self != NULL) {
        self = SnowballSpawner_Construct(self);
    }
    return self;
}
CLEAN_AS(func_ov003_0223654c, SnowballSpawner_New)
