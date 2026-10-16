/* A walker on the field's paths (path_walker.h).
 *
 * REQUIRES: the walker and the tiles handed out at word-aligned addresses, as every object of the
 * game and the callers' locals are (the ARM9 reads and writes the aligned word at a misaligned
 * address). */
#include "path_walker.h"

#include "actor.h"
#include "actor_table.h"
#include "autoload_2/fx_math.h"
#include "clean.h"

static_assert(sizeof(PathWalkerJunction) == 3, "PathWalkerJunction layout");
static_assert(offsetof(PathWalkerTable, steps) == 0x10, "PathWalkerTable layout");
static_assert(offsetof(PathWalker, goal_x) == 0x0c, "PathWalker layout");
static_assert(offsetof(PathWalker, goal_acre_x) == 0x14, "PathWalker layout");
static_assert(offsetof(PathWalker, stop_x) == 0x1c, "PathWalker layout");
static_assert(offsetof(PathWalker, table) == 0x28, "PathWalker layout");
static_assert(offsetof(PathWalker, trail) == 0x2c, "PathWalker layout");
static_assert(offsetof(PathWalker, heading) == 0x88, "PathWalker layout");
static_assert(offsetof(PathWalker, mode) == 0x8c, "PathWalker layout");
static_assert(offsetof(PathWalker, return_dir) == 0x90, "PathWalker layout");
static_assert(offsetof(PathWalker, last_x) == 0x94, "PathWalker layout");
static_assert(offsetof(PathWalkerMap, tiles_wide) == 0x0c, "PathWalkerMap layout");

/* One tile's step in each of the four directions (index 0 to 3 for the bits 1, 2, 4, 8). */
typedef struct PathWalkerStep {
    s32 x;
    s32 z;
} PathWalkerStep;

#define PATH_WALKER_NO_STEP 4
#define PATH_WALKER_ACRE_SIZE 0x28
#define PATH_WALKER_ACRE_TILES 16
#define PATH_WALKER_ARRIVED 2

/* The acres' flags (func_02037d80, func_02037d64) the pickers look for. */
#define PATH_WALKER_ACRE_FLAG_8 8
#define PATH_WALKER_ACRE_FLAG_200 0x200

/* The vtable slot of the owner (an object of class 0x020d8c64) that gives its villager record
 * (data_021e5a2c holds the eight, 0x7ec bytes each), or 0. */
#define PATH_WALKER_OWNER_VILLAGER 0x64

extern PathWalkerMap *data_021c80bc;
extern const PathWalkerStep data_021c172c[];
extern u8 data_021e5a2c[];
extern Random data_021cb5a0;
extern const fx16 FX_SinCosTable_[];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

extern unsigned int func_020644cc(int bound);
extern int func_02037d64(int acre, int flags);
extern int func_0207cc54(unsigned int candidates, int count, int columns);
extern int func_02037e8c(int acre);
extern int func_020800d0(int villager);
extern char *func_02137550(char *dst, int n);
extern unsigned int func_0208150c(unsigned int villager);
extern void *func_0207cc94(void *villagers, void **except, int count);
extern void *func_0204f61c(PathWalkerMap *map, unsigned int x, unsigned int z, unsigned int flags);
extern void *func_0204f704(PathWalkerMap *map, void *flags);
extern void func_0204f794(Vec3 *point, u32 x, u32 z);
extern void func_0204f7e0(Vec3 *point, Vec3 *from);
extern int func_02078e98(int point, int map);
extern int func_02078ec0(int x, int z, void *map);
extern int func_0204ed58(int map, int x, int z);
extern int func_0204ed30(int map, int position);
extern void func_0204f800(int *x, int *z, int acre_x, int acre_z, int offset_x, int offset_z);
extern void func_020138a8(void *walker, void *position);
extern void func_02013910(void *walker);
extern void func_02013934(char *walker, int position);
extern int func_02013738(int walker, int position, int map);
extern int func_0201354c(void *walker, u32 *stop, const Vec3 *position);

/* An arithmetic shift right, as the ARM's ASR does it, for negative values too. */
static s32 path_walker_asr(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

static s32 path_walker_add(s32 a, s32 b)
{
    return (s32) ((u32) a + (u32) b);
}

/* The acre a position is in. */
static s32 path_walker_acre_of(fx32 coordinate)
{
    return path_walker_asr(coordinate, 17);
}

/* The record of acre (x, z), or null outside the map or without one. */
static u8 *path_walker_acre(const PathWalkerMap *map, u32 x, u32 z)
{
    if (x < map->acres_wide && z < map->acres_high && map->acres != NULL) {
        return (u8 *) (uintptr_t) ((u32) (uintptr_t) map->acres + (x + z * map->acres_wide) * PATH_WALKER_ACRE_SIZE);
    }
    return NULL;
}

/* The acre's x and z (at 4 in its record). */
static const s32 *path_walker_acre_place(u8 *acre)
{
    return (const s32 *) (uintptr_t) (u32) func_02037e8c((int) (uintptr_t) acre);
}

/* The owner's villager record (vtable slot 0x64), or 0. */
static int path_walker_owner_villager(void *owner)
{
    u32 vtable = *(const u32 *) owner;
    u32 code = *(const u32 *) (uintptr_t) (vtable + PATH_WALKER_OWNER_VILLAGER);
    return ((int (*)(void *))(uintptr_t) code)(owner);
}

/* The place in a villager record (func_020800d0: at 0x7ce): a tile's x and z. */
static const u8 *path_walker_villager_place(int villager)
{
    return (const u8 *) (uintptr_t) (u32) func_020800d0(villager);
}

/* Another villager than the owner's (func_0207cc94 picks one at random), or null. */
static void *path_walker_other_villager(void *owner)
{
    unsigned int except;
    func_02137550((char *) &except, sizeof(except));
    except = func_0208150c((unsigned int) path_walker_owner_villager(owner));
    return func_0207cc94(data_021e5a2c, (void **) &except, 1);
}

/* The walker's state after it lost its way: no junctions, no heading. */
static void path_walker_forget(PathWalker *self)
{
    PathWalker_ClearTrail(self);
    self->heading = 0;
    self->mode = PATH_WALKER_NONE;
}

/* The phase 2 and 1 once the walker has arrived, else 0. */
static int path_walker_finish(PathWalker *self, Vec3 *position)
{
    if (PathWalker_Arrived(self, position)) {
        self->phase = PATH_WALKER_ARRIVED;
        return 1;
    }
    return 0;
}

static int path_walker_in_goal_acre(const PathWalker *self, const Vec3 *position)
{
    return path_walker_acre_of(position->x) == self->goal_acre_x && path_walker_acre_of(position->z) == self->goal_acre_z;
}

static int path_walker_on_goal_tile(const PathWalker *self, const Vec3 *position)
{
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    return x == self->goal_x && z == self->goal_z;
}

/* ---- Picking a goal: a tile on the paths in an acre */

/* func_020125bc: a tile in one of the acres 1 to wide-2 of row 4 that have the flag 8 (picked
 * at random, func_0207cc54), not the one the position is in; only on maps more than 4 acres
 * high and at most 8 wide. 0, 0 when there is none. `self` is only passed on. */
void PathWalker_PickInRow4(PathWalkerTile *out, u32 self, const Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    u8 candidates = 0;
    int count = 0;
    int columns = 0;

    out->x = 0;
    out->z = 0;
    if (map == NULL) {
        return;
    }
    s32 wide = (s32) map->acres_wide;
    if ((s32) map->acres_high > 4 && wide <= 8) {
        s32 own_x = path_walker_acre_of(position->x);
        s32 own_z = path_walker_acre_of(position->z);
        for (s32 x = 1; x < path_walker_add(wide, -1); x++) {
            if (!(x == own_x && own_z == 4)) {
                u8 *acre = path_walker_acre(map, (u32) x, 4);
                if (acre != NULL && func_02037d64((int) (uintptr_t) acre, PATH_WALKER_ACRE_FLAG_8) != 0) {
                    candidates = (u8) (candidates | (1u << (x - 1)));
                    count++;
                }
            }
            columns++;
        }
    }

    int pick = func_0207cc54(candidates, count, columns);
    if ((u32) pick >= (u32) columns) {
        return;
    }
    u8 *acre = path_walker_acre(map, (u32) pick + 1, 4);
    if (acre != NULL) {
        PathWalkerTile tile;
        PathWalker_PickInAcre(&tile, (PathWalker *) (uintptr_t) self, path_walker_acre_place(acre), map);
        *out = tile;
    }
}
CLEAN_AS(func_020125bc, PathWalker_PickInRow4)

/* func_020126b4: whether the position is in the goal acre. */
int PathWalker_InGoalAcreA(PathWalker *self, const Vec3 *position)
{
    return path_walker_in_goal_acre(self, position);
}
CLEAN_AS(func_020126b4, PathWalker_InGoalAcreA)

/* func_020126d0: a tile in an acre picked at random away from the map's edges: x from 1 to
 * wide-2 (0 on maps less than 3 acres wide), z from 1 to high-2. Maps less than 3 acres high
 * give 0, 0 (after x is drawn). */
void PathWalker_PickInAnyAcre(PathWalkerTile *out, PathWalker *self)
{
    PathWalkerMap *map = data_021c80bc;

    out->x = 0;
    out->z = 0;
    if (map == NULL) {
        return;
    }
    s32 wide = (s32) map->acres_wide;
    s32 high = (s32) map->acres_high;
    s32 acre[2] = {0, 0};
    if (wide >= 3) {
        acre[0] = (s32) func_020644cc(wide - 2) + 1;
    }
    if (high >= 3) {
        acre[1] = (s32) func_020644cc(high - 2) + 1;
        PathWalkerTile tile;
        PathWalker_PickInAcre(&tile, self, acre, map);
        *out = tile;
    }
}
CLEAN_AS(func_020126d0, PathWalker_PickInAnyAcre)

/* func_0201272c: as PathWalker_InGoalAcreA. */
int PathWalker_InGoalAcreB(PathWalker *self, const Vec3 *position)
{
    return path_walker_in_goal_acre(self, position);
}
CLEAN_AS(func_0201272c, PathWalker_InGoalAcreB)

/* func_02012748: a tile in the acre of the owner's villager's place (the place's tile over 16);
 * 0, 0 without a map or a villager. The record is asked for twice. */
void PathWalker_PickInOwnAcre(PathWalkerTile *out, PathWalker *self, void *position, void *owner)
{
    PathWalkerMap *map = data_021c80bc;
    (void) position;

    out->x = 0;
    out->z = 0;
    if (map == NULL || path_walker_owner_villager(owner) == 0) {
        return;
    }
    const u8 *place = path_walker_villager_place(path_walker_owner_villager(owner));
    s32 acre[2] = {place[0] >> 4, place[1] >> 4};
    PathWalkerTile tile;
    PathWalker_PickInAcre(&tile, self, acre, map);
    *out = tile;
}
CLEAN_AS(func_02012748, PathWalker_PickInOwnAcre)

/* func_020127ac: an arrival by placing: on the goal tile's column and at most a tile past it,
 * the position is put on the goal tile; within 3 tiles left and 4 right of it and at most 5
 * past it, on the goal's column 0 or 1 tile past it (at random); else
 * PathWalker_PlaceAtRandom. Then as PathWalker_PlaceAtRandom ends.
 * QUIRK: after PathWalker_PlaceAtRandom, which ends with func_02013910 and the check of arrival
 * itself, both run a second time. */
int PathWalker_PlaceNearGoal(PathWalker *self, Vec3 *position)
{
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);

    s32 goal_x = self->goal_x;
    if (x == goal_x && z >= self->goal_z && z <= path_walker_add(self->goal_z, 1)) {
        func_0204f794(position, (u32) self->goal_x, (u32) self->goal_z);
    } else if (x >= path_walker_add(goal_x, -3) && x <= path_walker_add(goal_x, 4) && z >= self->goal_z &&
               z <= path_walker_add(self->goal_z, 5)) {
        s32 tile_z = path_walker_add(self->goal_z, (s32) func_020644cc(2));
        func_0204f794(position, (u32) goal_x, (u32) tile_z);
    } else {
        PathWalker_PlaceAtRandom(self, position);
    }
    PathWalker_MarkTileUnknown(self);
    return path_walker_finish(self, position);
}
CLEAN_AS(func_020127ac, PathWalker_PlaceNearGoal)

/* func_02012844: whether the position is on the goal tile. */
int PathWalker_OnGoalTileA(PathWalker *self, const Vec3 *position)
{
    return path_walker_on_goal_tile(self, position);
}
CLEAN_AS(func_02012844, PathWalker_OnGoalTileA)

/* func_02012878: the tile in front of (one past in z) the owner's villager's place; 0, 0
 * without a villager. */
void PathWalker_PickOwnFront(PathWalkerTile *out, int self, int position, void *owner)
{
    (void) self;
    (void) position;

    out->x = 0;
    out->z = 0;
    if (path_walker_owner_villager(owner) != 0) {
        const u8 *place = path_walker_villager_place(path_walker_owner_villager(owner));
        out->x = place[0];
        out->z = (u32) place[1] + 1;
    }
}
CLEAN_AS(func_02012878, PathWalker_PickOwnFront)

/* func_020128b0: as PathWalker_InGoalAcreA. */
int PathWalker_InGoalAcreC(PathWalker *self, const Vec3 *position)
{
    return path_walker_in_goal_acre(self, position);
}
CLEAN_AS(func_020128b0, PathWalker_InGoalAcreC)

/* func_020128cc: a tile in the acre of another villager's place (picked at random among the
 * villagers but the owner's); 0, 0 without a map, an owner's villager or another one. */
void PathWalker_PickInOtherAcre(PathWalkerTile *out, PathWalker *self, void *position, void *owner)
{
    PathWalkerMap *map = data_021c80bc;
    (void) position;

    out->x = 0;
    out->z = 0;
    if (map == NULL || path_walker_owner_villager(owner) == 0) {
        return;
    }
    void *other = path_walker_other_villager(owner);
    if (other == NULL) {
        return;
    }
    const u8 *place = path_walker_villager_place((int) (uintptr_t) other);
    s32 acre[2] = {place[0] >> 4, place[1] >> 4};
    PathWalkerTile tile;
    PathWalker_PickInAcre(&tile, self, acre, map);
    *out = tile;
}
CLEAN_AS(func_020128cc, PathWalker_PickInOtherAcre)

/* func_02012950: when not arrived, the walker forgets its way and chooses a route again (0);
 * 1 once arrived (the phase is kept). */
int PathWalker_StepUntilArrived(PathWalker *self, const Vec3 *position)
{
    if (!PathWalker_Arrived(self, position)) {
        path_walker_forget(self);
        PathWalker_ChooseRoute(self, position);
        return 0;
    }
    return 1;
}
CLEAN_AS(func_02012950, PathWalker_StepUntilArrived)

/* func_0201298c: as PathWalker_OnGoalTileA. */
int PathWalker_OnGoalTileB(PathWalker *self, const Vec3 *position)
{
    return path_walker_on_goal_tile(self, position);
}
CLEAN_AS(func_0201298c, PathWalker_OnGoalTileB)

/* func_020129c0: the tile in front of another villager's place (as PathWalker_PickOwnFront and
 * PathWalker_PickInOtherAcre); 0, 0 without one. No map is needed. */
void PathWalker_PickOtherFront(PathWalkerTile *out, int self, int position, void *owner)
{
    (void) self;
    (void) position;

    out->x = 0;
    out->z = 0;
    if (path_walker_owner_villager(owner) != 0) {
        void *other = path_walker_other_villager(owner);
        if (other != NULL) {
            const u8 *place = path_walker_villager_place((int) (uintptr_t) other);
            out->x = place[0];
            out->z = (u32) place[1] + 1;
        }
    }
}
CLEAN_AS(func_020129c0, PathWalker_PickOtherFront)

/* func_02012a18: whether the acre the position is in has the flag 0x200 (func_0204f61c). */
int PathWalker_InFlaggedAcre(void *self, const Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    (void) self;

    if (map == NULL) {
        return 0;
    }
    u32 x = (u32) path_walker_acre_of(position->x);
    u32 z = (u32) path_walker_acre_of(position->z);
    return func_0204f61c(map, x, z, PATH_WALKER_ACRE_FLAG_200) != NULL;
}
CLEAN_AS(func_02012a18, PathWalker_InFlaggedAcre)

/* func_02012a4c: a tile in the first acre with the flag 0x200 (func_0204f704); 0, 0 without
 * one. */
void PathWalker_PickInFlaggedAcre(PathWalkerTile *out, PathWalker *self)
{
    PathWalkerMap *map = data_021c80bc;

    out->x = 0;
    out->z = 0;
    if (map == NULL) {
        return;
    }
    u8 *acre = func_0204f704(map, (void *) (uintptr_t) PATH_WALKER_ACRE_FLAG_200);
    if (acre != NULL) {
        PathWalkerTile tile;
        PathWalker_PickInAcre(&tile, self, path_walker_acre_place(acre), map);
        *out = tile;
    }
}
CLEAN_AS(func_02012a4c, PathWalker_PickInFlaggedAcre)

/* func_02012a98: the position is put on a tile 3 to 7 tiles away in a direction drawn about a
 * base heading, the first of ten tries that func_02078e98 accepts (on the field's map: 0
 * stands for data_021c80bc). One draw in four takes the heading to the goal tile and a spread
 * of 0x1000, else the base is drawn from the game's generator with a spread of 0x7fff (one in
 * four) or 0x3fff; the draw within the spread goes either way, and after every second try the
 * spread grows by 0x1000 (unless it is 0xffff). Then func_02013910, and the arrival check
 * (phase 2 and 1 once arrived, else 0). */
int PathWalker_PlaceAtRandom(PathWalker *self, Vec3 *position)
{
    u16 spread = 0x7fff;
    s32 base;
    Vec3 point;

    int kind = (int) func_020644cc(4);
    func_0204f794(&point, (u32) self->goal_x, (u32) self->goal_z);
    if (kind == 0) {
        base = Vec_YawTo(position, &point);
        spread = 0x1000;
    } else if (kind == 1) {
        base = (s16) Random_Next(&data_021cb5a0);
    } else {
        base = (s16) Random_Next(&data_021cb5a0);
        spread = 0x7fff >> 1;
    }

    for (int i = 0; i < 10; i++) {
        fx32 distance = (fx32) ((func_020644cc(5) + 3) << 13);
        s16 turn = (s16) func_020644cc(spread);
        if (func_020644cc(2) != 0) {
            turn = (s16) -turn;
        }
        u16 angle = (u16) (s16) (turn + base);
        int index = (angle >> 4) * 2;
        point.x = path_walker_add(position->x, FX_MulFunc(distance, FX_SinCosTable_[index]));
        point.z = path_walker_add(position->z, FX_MulFunc(distance, FX_SinCosTable_[index + 1]));
        func_0204f7e0(&point, &point);
        if (func_02078e98((int) (uintptr_t) &point, 0) != 0) {
            position->x = point.x;
            position->z = point.z;
            break;
        }
        if ((i & 1) != 0 && spread != 0xffff) {
            spread = (u16) (spread + 0x1000);
        }
    }

    PathWalker_MarkTileUnknown(self);
    return path_walker_finish(self, position);
}
CLEAN_AS(func_02012a98, PathWalker_PlaceAtRandom)

/* func_02012bcc: a step to a neighbouring tile (PathWalker_StepToNeighbourOn); 1 once arrived
 * (the phase is kept), else the walker forgets its way and chooses a route again (0). 0
 * without a map. */
int PathWalker_StepToNeighbour(PathWalker *self, Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    PathWalker_StepToNeighbourOn(self, position, map);
    if (PathWalker_Arrived(self, position)) {
        return 1;
    }
    path_walker_forget(self);
    PathWalker_ChooseRoute(self, position);
    return 0;
}
CLEAN_AS(func_02012bcc, PathWalker_StepToNeighbour)

/* func_02012c20: func_02013738 moves the position to a neighbouring tile; the answer is 0. */
int PathWalker_StepToNeighbourOn(PathWalker *self, Vec3 *position, PathWalkerMap *map)
{
    PathWalker_StepToClearNeighbour(self, position, map);
    return 0;
}
CLEAN_AS(func_02012c20, PathWalker_StepToNeighbourOn)

/* func_02012c30: a step along the path (PathWalker_StepAlongOn); phase 2 and 1 once arrived,
 * else 0 (also without a map). */
int PathWalker_StepAlong(PathWalker *self, Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    if (map != NULL) {
        PathWalker_StepAlongOn(self, position, map);
        return path_walker_finish(self, position);
    }
    return 0;
}
CLEAN_AS(func_02012c30, PathWalker_StepAlong)

/* func_02012c68: after func_020138a8, the position moves one tile in the heading. A tile off
 * the paths makes the walker forget its way and choose a route there (no step back); reaching
 * the junction it walked to makes it choose the next. Without a heading it forgets its way and
 * chooses a route. The answer is 0.
 * QUIRK: a heading with none of the bits 1, 2, 4, 8 steps by the words after the table of
 * steps (index 4). */
int PathWalker_StepAlongOn(PathWalker *self, Vec3 *position, PathWalkerMap *map)
{
    PathWalker_ReplanIfMoved(self, position);

    if (self->heading == 0) {
        path_walker_forget(self);
        PathWalker_ChooseRoute(self, position);
        return 0;
    }

    const PathWalkerStep *step = &data_021c172c[PathWalker_StepIndex((int) (uintptr_t) self, self->heading)];
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    u32 tile_x = (u32) x + (u32) step->x;
    u32 tile_z = (u32) z + (u32) step->z;

    if (func_0204ed58((int) (uintptr_t) map, (int) tile_x, (int) tile_z) == 0) {
        func_0204f794(position, tile_x, tile_z);
        path_walker_forget(self);
        PathWalker_ChooseRoute(self, position);
        self->return_dir = PATH_WALKER_NO_STEP;
        return 0;
    }
    func_0204f794(position, tile_x, tile_z);
    if (tile_x == (u32) self->stop_x && tile_z == (u32) self->stop_z) {
        PathWalker_ChooseRoute(self, position);
    }
    return 0;
}
CLEAN_AS(func_02012c68, PathWalker_StepAlongOn)

/* func_02012d40: a step back towards the paths (PathWalker_StepToPathOn, within the map's
 * tiles); phase 2 and 1 once arrived, else 0 (also without a map). */
int PathWalker_StepToPath(PathWalker *self, Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    PathWalkerTile limit = {map->tiles_wide, map->tiles_high};
    PathWalker_StepToPathOn(self, position, &limit, map);
    return path_walker_finish(self, position);
}
CLEAN_AS(func_02012d40, PathWalker_StepToPath)

/* func_02012d84: after func_020138a8, with a way back (`return_dir` below 4) the tiles are
 * looked at one after the other in that direction, while within `limit`: the first on the
 * paths, or the junction the walker walked to, gets the position and a new route; else the
 * first that func_02078ec0 accepts gets the position. Without a way back the walker forgets
 * its way and chooses a route. The answer is 0. */
int PathWalker_StepToPathOn(PathWalker *self, Vec3 *position, PathWalkerTile *limit, PathWalkerMap *map)
{
    PathWalker_ReplanIfMoved(self, position);

    if (self->return_dir >= PATH_WALKER_NO_STEP) {
        path_walker_forget(self);
        PathWalker_ChooseRoute(self, position);
        return 0;
    }

    const PathWalkerStep *step = &data_021c172c[self->return_dir];
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    u32 tile_x = (u32) x;
    u32 tile_z = (u32) z;
    while (tile_x < limit->x && tile_z < limit->z) {
        tile_x += (u32) step->x;
        tile_z += (u32) step->z;
        int at_stop = tile_x == (u32) self->stop_x && tile_z == (u32) self->stop_z;
        if (at_stop || func_0204ed58((int) (uintptr_t) map, (int) tile_x, (int) tile_z) != 0) {
            func_0204f794(position, tile_x, tile_z);
            PathWalker_ChooseRoute(self, position);
            break;
        }
        if (func_02078ec0((int) tile_x, (int) tile_z, map) != 0) {
            func_0204f794(position, tile_x, tile_z);
            break;
        }
    }
    return 0;
}
CLEAN_AS(func_02012d84, PathWalker_StepToPathOn)

/* The junction nearest the goal over the directions open at `here` (`open`) and not in
 * `skip`, each walked by PathWalker_FindJunctionAlong; its direction (0 for none), and in
 * `stop` its tile. The first found is taken, then any nearer (Vec_DistanceXZ from the goal
 * tile's centre). */
static int path_walker_nearest(PathWalker *self, int open, int skip, const PathWalkerTile *here, const PathWalkerTile *limit,
                               PathWalkerMap *map, PathWalkerTile *stop)
{
    Vec3 goal;
    Vec3 junction;
    PathWalkerTile found;
    fx32 best = -0x1000;
    int direction = 0;

    func_0204f794(&goal, (u32) self->goal_x, (u32) self->goal_z);
    for (int i = 0; i < 4; i++) {
        if (((skip >> i) & 1) != 0) {
            continue;
        }
        int bit = open & (1 << i);
        if (bit == 0) {
            continue;
        }
        PathWalkerTile from = *here;
        found.x = 0;
        found.z = 0;
        if (PathWalker_FindJunctionAlong(self, &found, &from, bit, limit, map) == 0) {
            continue;
        }
        func_0204f794(&junction, found.x, found.z);
        fx32 distance = Vec_DistanceXZ(&goal, &junction);
        if (best < 0 || distance < best) {
            *stop = found;
            best = distance;
            direction = bit;
        }
    }
    return direction;
}

/* Walking back the way of `direction` to the junction there, if there is one. */
static void path_walker_turn_back(PathWalker *self, int direction, const PathWalkerTile *here, const PathWalkerTile *limit,
                                  PathWalkerMap *map)
{
    PathWalkerTile from = *here;
    PathWalkerTile found = {0, 0};
    if (PathWalker_FindJunctionAlong(self, &found, &from, direction, limit, map) != 0) {
        self->stop_x = (s32) found.x;
        self->stop_z = (s32) found.z;
        self->mode = PATH_WALKER_BACK;
        self->heading = direction;
    }
}

/* func_02012e58: the walker at the position chooses where to walk next, by the directions open
 * at its tile:
 * - off the paths: the way back to them (func_0201354c sets the junction to walk to and gives
 *   the step index), phase 0, and it forgets its way;
 * - only the way it came open: it walks back to the junction that way;
 * - walking on (or neither): a junction remembered at this tile adds the directions tried
 *   there; of the directions open, not tried and not the way back, the one whose next junction
 *   is nearest the goal is taken (and, walking on, the junction remembered with it); without
 *   one it walks back. Phase 1;
 * - walking back: the junction remembered here (with what came after it) is dropped; of the
 *   directions open, not tried there and not the way back or the way it first came, the one
 *   nearest the goal is taken and the junction remembered again; without one it walks back
 *   the way it first came. Phase 1.
 * The step index back to the paths is then none (4), but in the first case. */
void PathWalker_ChooseRoute(PathWalker *self, const Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    if (map == NULL) {
        return;
    }
    int open = func_0204ed30((int) (uintptr_t) map, (int) (uintptr_t) position);
    if (open == 0) {
        self->return_dir = (u32) PathWalker_FindWayToPath(self, (u32 *) &self->stop_x, position);
        self->phase = 0;
        path_walker_forget(self);
        return;
    }

    int back = PathWalker_Opposite((int) (uintptr_t) self, self->heading);
    PathWalkerTile limit = {map->tiles_wide, map->tiles_high};
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    PathWalkerTile here = {(u32) x, (u32) z};
    PathWalkerTile stop = {0, 0};

    if ((open & ~back) == 0) {
        path_walker_turn_back(self, back, &here, &limit, map);
    } else if (self->mode != PATH_WALKER_BACK) {
        int tried = 0;
        int from = self->heading;
        if (PathWalker_FindJunction(self, &here) != -1) {
            PathWalkerJunction junction = PathWalker_PopTo(self, &here);
            tried = junction.directions >> 4;
            from = junction.directions & 0xf;
        }
        int direction = path_walker_nearest(self, open, back | tried, &here, &limit, map, &stop);
        if (direction != 0) {
            if (self->mode == PATH_WALKER_ONWARD) {
                PathWalker_PushJunction(self, tried | direction, from, &here);
            }
            self->stop_x = (s32) stop.x;
            self->stop_z = (s32) stop.z;
            self->mode = PATH_WALKER_ONWARD;
            self->heading = direction;
        } else {
            path_walker_turn_back(self, back, &here, &limit, map);
        }
        self->phase = 1;
    } else {
        PathWalkerJunction junction = PathWalker_PopTo(self, &here);
        int from = junction.directions & 0xf;
        int first_back = PathWalker_Opposite((int) (uintptr_t) self, from);
        int direction = path_walker_nearest(self, open, back | first_back, &here, &limit, map, &stop);
        if (direction != 0) {
            if (from == 0) {
                from = self->heading;
            }
            self->stop_x = (s32) stop.x;
            self->stop_z = (s32) stop.z;
            PathWalker_PushJunction(self, (junction.directions >> 4) | direction, from, &here);
            self->mode = PATH_WALKER_ONWARD;
            self->heading = direction;
        } else {
            path_walker_turn_back(self, first_back, &here, &limit, map);
        }
        self->phase = 1;
    }
    self->return_dir = PATH_WALKER_NO_STEP;
}
CLEAN_AS(func_02012e58, PathWalker_ChooseRoute)

/* func_020131c0: the direction opposite `direction` (1 and 4, 2 and 8), 0 for none.
 * QUIRK: for several bits the result is the bits shifted left by 2 unless none of them stays
 * in the low four. */
int PathWalker_Opposite(int self, int direction)
{
    (void) self;
    if (direction == 0) {
        return 0;
    }
    u32 bits = (u32) direction << 2;
    if ((bits & 0xf) == 0) {
        bits = (bits >> 4) & 0xf;
    }
    return (int) bits;
}
CLEAN_AS(func_020131c0, PathWalker_Opposite)

/* func_020131dc: a tile on the paths in acre (acre[0], acre[1]) picked at random among all of
 * them (func_020644cc); 0, 0 when it has none. `self` is not used. */
void PathWalker_PickInAcre(PathWalkerTile *out, PathWalker *self, const s32 *acre, PathWalkerMap *map)
{
    u16 rows[PATH_WALKER_ACRE_TILES];
    int count = 0;
    int corner_x = 0;
    int corner_z = 0;
    (void) self;

    MI_CpuFill8(rows, 0, sizeof(rows));
    func_0204f800(&corner_x, &corner_z, acre[0], acre[1], 0, 0);
    for (int z = 0; z < PATH_WALKER_ACRE_TILES; z++) {
        for (int x = 0; x < PATH_WALKER_ACRE_TILES; x++) {
            if (func_0204ed58((int) (uintptr_t) map, path_walker_add(corner_x, x), path_walker_add(corner_z, z)) != 0) {
                rows[z] = (u16) (rows[z] | (1u << x));
                count++;
            }
        }
    }
    if (count > 0) {
        int pick = (int) func_020644cc(count);
        for (int z = 0; z < PATH_WALKER_ACRE_TILES; z++) {
            for (int x = 0; x < PATH_WALKER_ACRE_TILES; x++) {
                if (((rows[z] >> x) & 1) != 0) {
                    if (pick == 0) {
                        out->x = (u32) path_walker_add(corner_x, x);
                        out->z = (u32) path_walker_add(corner_z, z);
                        return;
                    }
                    pick--;
                }
            }
        }
    }
    out->x = 0;
    out->z = 0;
}
CLEAN_AS(func_020131dc, PathWalker_PickInAcre)

/* func_020132a0: the step of the walker's state and phase (from its table), when there is one;
 * in state 1 the tile the position is on is then kept (func_02013934). Its answer, else 0. */
int PathWalker_Step(PathWalker *self, Vec3 *position)
{
    const PathWalkerTable *table = self->table;
    if (table == NULL || self->state >= 2 || self->phase >= 3) {
        return 0;
    }
    const MemberPointer *step = &table->steps[self->state][self->phase];
    if (step->function == 0) {
        return 0;
    }
    void *object = MemberPointer_Object(step, self);
    int result = ((int (*)(void *, Vec3 *))(uintptr_t) MemberPointer_Code(step, object))(object, position);
    if (self->state == 1) {
        PathWalker_KeepTile(self, position);
    }
    return result;
}
CLEAN_AS(func_020132a0, PathWalker_Step)

/* func_02013300 */
int PathWalker_Status(const PathWalker *self)
{
    return (int) self->status;
}
CLEAN_AS(func_02013300, PathWalker_Status)

/* func_02013304: the junction remembered at `tile`, dropped from the trail with the newer ones
 * (the older move up to the front); all zero when there is none. */
PathWalkerJunction PathWalker_PopTo(PathWalker *self, const PathWalkerTile *tile)
{
    PathWalkerJunction found;
    int index = PathWalker_FindJunction(self, tile);
    MI_CpuFill8(&found, 0, sizeof(found));
    if (index != -1) {
        u8 *trail = (u8 *) self->trail;
        MI_CpuCopy8(trail + index * 3, &found, 3);
        for (int i = index; i < PATH_WALKER_TRAIL - 1; i++) {
            MI_CpuCopy8(trail + (i + 1) * 3, trail + (i - index) * 3, 3);
        }
        MI_CpuFill8(trail + (PATH_WALKER_TRAIL - 1 - index) * 3, 0, (u32) (index + 1) * 3);
    }
    return found;
}
CLEAN_AS(func_02013304, PathWalker_PopTo)

/* func_02013384: the place in the trail of the junction at `tile`, -1 when there is none. */
int PathWalker_FindJunction(PathWalker *self, const PathWalkerTile *tile)
{
    for (int i = 0; i < PATH_WALKER_TRAIL; i++) {
        if (tile->x == self->trail[i].x && tile->z == self->trail[i].z) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02013384, PathWalker_FindJunction)

/* func_020133b4: the junction at `tile` is remembered at the front, with the directions tried
 * and the one it came from (the low four bits of each); the others move back by one (the last
 * of the thirty is lost when it is full). */
void PathWalker_PushJunction(PathWalker *self, int tried, int from, const PathWalkerTile *tile)
{
    int count = PathWalker_TrailLength(self);
    u8 *entry = (u8 *) self->trail + 3 * count;
    while (count > 0) {
        MI_CpuCopy8(entry - 3, entry, 3);
        entry -= 3;
        count--;
    }
    entry[2] = (u8) (((tried & 0xf) << 4) | (from & 0xf));
    entry[0] = (u8) tile->x;
    entry[1] = (u8) tile->z;
}
CLEAN_AS(func_020133b4, PathWalker_PushJunction)

/* func_02013420: the junctions remembered: the first of the 29 entries without directions
 * tried, else 29. */
int PathWalker_TrailLength(PathWalker *self)
{
    for (int i = 0; i < PATH_WALKER_TRAIL - 1; i++) {
        if ((self->trail[i].directions >> 4) == 0) {
            return i;
        }
    }
    return PATH_WALKER_TRAIL - 1;
}
CLEAN_AS(func_02013420, PathWalker_TrailLength)

/* func_02013440 */
void PathWalker_ClearTrail(PathWalker *self)
{
    MI_CpuFill8(self->trail, 0, sizeof(self->trail));
}
CLEAN_AS(func_02013440, PathWalker_ClearTrail)

/* func_02013450: the next junction from `from` in `direction`, walking while within `limit`
 * (`from` moves along): a tile with a path leaving it sideways is the junction (its tile in
 * `out`, the answer the tiles walked); before a tile off the paths, the last tile on them is
 * (the answer minus the tiles walked to it). 0 when there is none, or for a direction with none
 * of the four bits.
 * QUIRK: a path that ends one tile away gives 0, as none. */
int PathWalker_FindJunctionAlong(PathWalker *self, PathWalkerTile *out, PathWalkerTile *from, int direction,
                                 const PathWalkerTile *limit, PathWalkerMap *map)
{
    int index = PathWalker_StepIndex((int) (uintptr_t) self, direction);
    if (index < 4) {
        u32 dx = (u32) data_021c172c[index].x;
        u32 dz = (u32) data_021c172c[index].z;
        int sideways = ~(direction | PathWalker_Opposite((int) (uintptr_t) self, direction));
        int walked = 0;
        while (from->x < limit->x && from->z < limit->z) {
            from->x += dx;
            from->z += dz;
            walked++;
            int open = func_0204ed58((int) (uintptr_t) map, (int) from->x, (int) from->z);
            if (open == 0) {
                out->x = from->x - dx;
                out->z = from->z - dz;
                return 1 - walked;
            }
            if ((open & sideways) != 0) {
                out->x = from->x;
                out->z = from->z;
                return walked;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_02013450, PathWalker_FindJunctionAlong)

/* func_020134f8: the step index (0 to 3) of the lowest of the four direction bits set, 4 for
 * none. */
int PathWalker_StepIndex(int self, int direction)
{
    (void) self;
    if (direction != 0) {
        for (int i = 0; i < 4; i++) {
            if (((direction >> i) & 1) != 0) {
                return i;
            }
        }
    }
    return PATH_WALKER_NO_STEP;
}
CLEAN_AS(func_020134f8, PathWalker_StepIndex)

/* func_02013518: the walker table's check of arrival, 0 without one. */
int PathWalker_Arrived(PathWalker *self, const Vec3 *position)
{
    const PathWalkerTable *table = self->table;
    if (table == NULL || table->arrived.function == 0) {
        return 0;
    }
    void *object = MemberPointer_Object(&table->arrived, self);
    return ((int (*)(void *, const Vec3 *))(uintptr_t) MemberPointer_Code(&table->arrived, object))(object, position);
}
CLEAN_AS(func_02013518, PathWalker_Arrived)

/* ---- Finding the paths again, and the walker's life */

static_assert(sizeof(PathWalker) == 0x9c, "PathWalker layout");

/* The walker's table by kind of walk (filled at start-up). */
extern const PathWalkerTable data_021c1914[];

/* The ground at a tile (func_02034240 asks about the tile's centre, func_0203423c releases the
 * answer): PathWalker_SearchLine counts the tiles whose word at 0x30 is set. */
typedef struct PathWalkerGround {
    u8 unk_00[0x30];
    s32 unk_30;
    u8 unk_34[0x10];
} PathWalkerGround;

/* The bits of an acre's flags (func_0204f658) that make PathWalker_SearchLine look at the
 * ground. */
#define PATH_WALKER_ACRE_GROUND_FLAGS 0x7f000
/* Tiles in a row with the ground's word at 0x30 set that end a search. */
#define PATH_WALKER_GROUND_RUN 4
/* `state` before a walk starts: neither row of steps. */
#define PATH_WALKER_STATE_NONE 2
/* `last_x` and `last_z` once PathWalker_MarkTileUnknown marked them. */
#define PATH_WALKER_TILE_UNKNOWN 0xff

extern void *func_02034240(PathWalkerGround *ground, u32 x, u32 z, int a, int b);
extern void func_0203423c(PathWalkerGround *ground);
extern u32 func_0204f658(PathWalkerMap *map, u32 acre_x, u32 acre_z);
extern void func_0204f828(int *acre, int *tile, const Vec3 *position);
extern void func_0204f7ac(Vec3 *position, int acre_x, int acre_z, int tile_x, int tile_z);
extern int TownTile_IsClear(int x, int z, void *map);

/* The step of index `index` as a tile (the words are added as they are, without sign). */
static const PathWalkerTile *path_walker_step_tile(int index)
{
    return (const PathWalkerTile *) &data_021c172c[index];
}

/* func_0201354c: the way from a position off the paths back to them. Within the position's acre,
 * each of the four directions is searched (PathWalker_SearchLine, in the order 0, 2, 1, 3) up to
 * the acre's edge for a tile on the paths; of those found, the nearest the position
 * (Vec_DistanceXZ, the first on equal distances) is taken. Without any, the position moves to a
 * clear neighbouring tile (PathWalker_StepToClearNeighbour) instead. The tile reached goes to
 * `stop` (x and z); the answer is the step index taken, 4 for none (also without a map, or
 * when the position is on the paths already: then `stop` is not written).
 * The ground is looked at in the search when the acre has one of the flags 0x7f000. */
int PathWalker_FindWayToPath(PathWalker *self, u32 *stop, const Vec3 *position)
{
    PathWalkerMap *map = data_021c80bc;
    Vec3 reached = *position;
    int result = PATH_WALKER_NO_STEP;

    if (map == NULL) {
        return PATH_WALKER_NO_STEP;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    PathWalkerTile limit = {map->tiles_wide, map->tiles_high};
    if (func_0204ed30((int) (uintptr_t) map, (int) (uintptr_t) position) != 0) {
        return PATH_WALKER_NO_STEP;
    }

    Vec3 found[4];
    for (int i = 0; i < 4; i++) {
        found[i] = *position;
    }
    Position_Tile(&x, &z, (const Position *) position);
    PathWalkerTile here = {(u32) x, (u32) z};
    u32 flags = func_0204f658(map, (u32) path_walker_acre_of(position->x), (u32) path_walker_acre_of(position->z));
    int check_ground = (flags & PATH_WALKER_ACRE_GROUND_FLAGS) != 0;

    /* The acre's first tile on each axis, and the first past it. */
    u32 first_x = here.x & 0xfff0;
    u32 first_z = here.z & 0xfff0;
    u32 past_x = first_x + PATH_WALKER_ACRE_TILES;
    u32 past_z = first_z + PATH_WALKER_ACRE_TILES;

    u8 open = 0;
    if (PathWalker_SearchLine(self, &found[0], &here, path_walker_step_tile(0), (int) (here.z - first_z), &limit, check_ground,
                              map) != 0) {
        open |= 1;
    }
    if (PathWalker_SearchLine(self, &found[2], &here, path_walker_step_tile(2), (int) (past_z - here.z), &limit, check_ground,
                              map) != 0) {
        open |= 4;
    }
    if (PathWalker_SearchLine(self, &found[1], &here, path_walker_step_tile(1), (int) (here.x - first_x), &limit, check_ground,
                              map) != 0) {
        open |= 2;
    }
    if (PathWalker_SearchLine(self, &found[3], &here, path_walker_step_tile(3), (int) (past_x - here.x), &limit, check_ground,
                              map) != 0) {
        open |= 8;
    }

    if (open != 0) {
        fx32 best = -0x1000;
        for (int i = 0; i < 4; i++) {
            fx32 distance = Vec_DistanceXZ(position, &found[i]);
            if (((open >> i) & 1) != 0 && (best < 0 || distance < best)) {
                reached = found[i];
                best = distance;
                result = i;
            }
        }
    } else {
        int step = PathWalker_StepToClearNeighbour(self, &reached, map);
        if ((u32) step < 4) {
            result = step;
        }
    }

    int stop_x;
    int stop_z;
    Position_Tile(&stop_x, &stop_z, (const Position *) &reached);
    stop[0] = (u32) stop_x;
    stop[1] = (u32) stop_z;
    return result;
}
CLEAN_AS(func_0201354c, PathWalker_FindWayToPath)

/* func_02013738: the position moves to the centre of a neighbouring tile in its acre (one of the
 * four steps, picked at random among those TownTile_IsClear accepts, func_0207cc54); the
 * answer is the step index, 4 when none is clear (the position is kept). `self` is not used. */
int PathWalker_StepToClearNeighbour(PathWalker *self, Vec3 *position, PathWalkerMap *map)
{
    int acre[2] = {0, 0};
    int tile[2] = {0, 0};
    u8 candidates = 0;
    int count = 0;
    (void) self;

    func_0204f828(acre, tile, position);
    for (int i = 0; i < 4; i++) {
        u32 x = (u32) tile[0] + (u32) data_021c172c[i].x;
        u32 z = (u32) tile[1] + (u32) data_021c172c[i].z;
        if (x < PATH_WALKER_ACRE_TILES && z < PATH_WALKER_ACRE_TILES) {
            int map_x = 0;
            int map_z = 0;
            func_0204f800(&map_x, &map_z, acre[0], acre[1], (int) x, (int) z);
            if (TownTile_IsClear(map_x, map_z, map) != 0) {
                candidates = (u8) (candidates | (1u << i));
                count++;
            }
        }
    }

    int pick = func_0207cc54(candidates, count, 4);
    if ((u32) pick < 4) {
        func_0204f7ac(position, acre[0], acre[1], path_walker_add(tile[0], data_021c172c[pick].x),
                      path_walker_add(tile[1], data_021c172c[pick].z));
        return pick;
    }
    return PATH_WALKER_NO_STEP;
}
CLEAN_AS(func_02013738, PathWalker_StepToClearNeighbour)

/* func_020137ec: from `from`, up to `count` tiles along `step` are looked at; the first on the
 * paths gives `point` its centre (func_0204f794) and the answer 1. Tiles outside `limit` are
 * skipped. With `check_ground`, the ground of each tile within `limit` is asked about first, and
 * four in a row with its word at 0x30 set end the search. 0 when nothing is found. `self` is
 * not used. */
int PathWalker_SearchLine(PathWalker *self, Vec3 *point, const PathWalkerTile *from, const PathWalkerTile *step, int count,
                          const PathWalkerTile *limit, int check_ground, PathWalkerMap *map)
{
    u32 x = from->x;
    u32 z = from->z;
    int covered = 0;
    (void) self;

    for (int i = 0; i < count; i++) {
        x += step->x;
        z += step->z;
        if (x >= limit->x || z >= limit->z) {
            continue;
        }
        if (check_ground != 0) {
            PathWalkerGround ground;
            func_02034240(&ground, x, z, 0, 0);
            covered = ground.unk_30 != 0 ? covered + 1 : 0;
            func_0203423c(&ground);
            if (covered >= PATH_WALKER_GROUND_RUN) {
                return 0;
            }
        }
        if (func_0204ed58((int) (uintptr_t) map, (int) x, (int) z) != 0) {
            func_0204f794(point, x, z);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020137ec, PathWalker_SearchLine)

/* func_02013894: whether a walk is under way (its kind is one of the seven). */
int PathWalker_IsWalking(const PathWalker *self)
{
    return self->status < PATH_WALKER_KINDS;
}
CLEAN_AS(func_02013894, PathWalker_IsWalking)

/* func_020138a4 */
void PathWalker_SetState(PathWalker *self, int state)
{
    self->state = (u32) state;
}
CLEAN_AS(func_020138a4, PathWalker_SetState)

/* func_020138a8: when the walker keeps a tile (`last_x` and `last_z` both nonzero) and the
 * position is on another one (it was moved), it forgets its way and chooses a route from there;
 * the phase is 3 before that and the way back to the paths none (4) after.
 * QUIRK: a route that keeps the phase (no map, or only the way back open) leaves phase 3, where
 * PathWalker_Step does nothing; and the way back to the paths that PathWalker_ChooseRoute finds
 * off them is dropped (4), to be found again by the next step. */
void PathWalker_ReplanIfMoved(PathWalker *self, Vec3 *position)
{
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) position);
    if (self->last_x != 0 && self->last_z != 0 && (self->last_x != x || self->last_z != z)) {
        self->phase = 3;
        path_walker_forget(self);
        PathWalker_ChooseRoute(self, position);
        self->return_dir = PATH_WALKER_NO_STEP;
    }
}
CLEAN_AS(func_020138a8, PathWalker_ReplanIfMoved)

/* func_02013910: a tile not kept yet (0, 0) becomes 0xff, 0xff, which no position is on, so
 * that the next PathWalker_ReplanIfMoved chooses a route. */
void PathWalker_MarkTileUnknown(PathWalker *self)
{
    if (self->last_x == 0 && self->last_z == 0) {
        self->last_x = PATH_WALKER_TILE_UNKNOWN;
        self->last_z = PATH_WALKER_TILE_UNKNOWN;
    }
}
CLEAN_AS(func_02013910, PathWalker_MarkTileUnknown)

/* func_02013934: the tile the position is on is kept. */
void PathWalker_KeepTile(PathWalker *self, const Vec3 *position)
{
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) position);
    self->last_x = x;
    self->last_z = z;
}
CLEAN_AS(func_02013934, PathWalker_KeepTile)

/* func_02013948: starts a walk of kind `kind` (none from 7 on) in state `state`: the walker is
 * set up afresh with the kind's table, whose goal picker (when it has one) gives the goal tile
 * for the position and `owner`; the goal acre follows (the tile over 16, rounded down), and a
 * route is chosen. Without a picker the walker keeps no goal. */
void PathWalker_Start(PathWalker *self, Vec3 *position, u32 kind, int state, void *owner)
{
    typedef void (*PathWalkerPicker)(PathWalkerTile *out, void *walker, Vec3 *position, void *owner);

    if (kind >= PATH_WALKER_KINDS) {
        return;
    }
    PathWalker_Init(self);
    self->status = kind;
    self->state = (u32) state;
    self->table = &data_021c1914[kind];
    const MemberPointer *pick = &self->table->unk_08;
    if (pick->function == 0) {
        return;
    }
    PathWalkerTile goal;
    void *object = MemberPointer_Object(pick, self);
    ((PathWalkerPicker) (uintptr_t) MemberPointer_Code(pick, object))(&goal, object, position, owner);
    self->goal_x = (s32) goal.x;
    self->goal_z = (s32) goal.z;
    self->goal_acre_x = path_walker_asr(self->goal_x, 4);
    self->goal_acre_z = path_walker_asr(self->goal_z, 4);
    PathWalker_ChooseRoute(self, position);
}
CLEAN_AS(func_02013948, PathWalker_Start)

/* func_020139bc: all zero, then no walk (state 2, kind 7), the halves of `unk_24` 0xffff,
 * neither walking on nor back, and no way back to the paths. */
void PathWalker_Init(PathWalker *self)
{
    MI_CpuFill8(self, 0, sizeof(*self));
    self->state = PATH_WALKER_STATE_NONE;
    self->status = PATH_WALKER_KINDS;
    self->unk_24 = 0xffffffffu;
    self->mode = PATH_WALKER_NONE;
    self->return_dir = PATH_WALKER_NO_STEP;
}
CLEAN_AS(func_020139bc, PathWalker_Init)

/* func_020139ec: the destructor; nothing to release. */
void PathWalker_Destruct(PathWalker *self)
{
    (void) self;
}
CLEAN_AS(func_020139ec, PathWalker_Destruct)

/* func_020139f0: the constructor: the goal, the goal acre, the junction walked to and the tile
 * kept are zero. Returns the walker. */
int PathWalker_Construct(PathWalker *self)
{
    self->goal_x = 0;
    self->goal_z = 0;
    self->goal_acre_x = 0;
    self->goal_acre_z = 0;
    self->stop_x = 0;
    self->stop_z = 0;
    self->last_x = 0;
    self->last_z = 0;
    return (int) (uintptr_t) self;
}
CLEAN_AS(func_020139f0, PathWalker_Construct)
