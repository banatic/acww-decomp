/* A walker on the field's paths: what moves an actor of overlay 68 (a villager; the object is at
 * 0x3c in it) from one junction of the paths to the next towards a goal tile.
 *
 * Each tile of the field has four bits (func_0204ed58 reads them): the directions 1, 2, 4 and 8
 * in which a path leaves it; 1 and 4 are opposite, as are 2 and 8. A tile without bits is off
 * the paths. The steps along each direction are the table at data_021c172c (four pairs x, z).
 * Tiles are 0x2000 units of position wide (Position_Tile), acres 16 tiles.
 *
 * The walker's behaviour is a table of C++ pointers to member functions (`table` at 0x28):
 * whether it has arrived, and the step run each frame for each state (0 or 1) and phase (0 to
 * 2; 2 once arrived). The functions here are the ones the tables name: the steps, the checks of
 * arrival, and the choice of a goal (a tile picked at random in an acre).
 *
 * While it walks, the walker remembers the junctions it passed (`trail`, newest first): each
 * with the tile's x and z and a byte of the directions tried there (bits 4-7) and the direction
 * it came from (bits 0-3). */
#ifndef CLEAN_MAIN_PATH_WALKER_H
#define CLEAN_MAIN_PATH_WALKER_H

#include "autoload_2/vector.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The field's acres and their size (data_021c80bc): `acres` holds `acres_wide` by `acres_high`
 * records of 0x28 bytes, the acre's x and z at 4 in each (func_02037e8c). */
typedef struct PathWalkerMap {
    u8 *acres;
    u32 acres_wide;
    u32 acres_high;
    u32 tiles_wide; /* 0x0c */
    u32 tiles_high; /* 0x10 */
} PathWalkerMap;

typedef struct PathWalkerTile {
    u32 x;
    u32 z;
} PathWalkerTile;

/* A junction remembered: the tile and the directions (see above). */
typedef struct PathWalkerJunction {
    u8 x;
    u8 z;
    u8 directions;
} PathWalkerJunction;

#define PATH_WALKER_TRAIL 30

typedef struct PathWalkerTable {
    MemberPointer arrived; /* (walker, position): nonzero once at the goal */
    MemberPointer unk_08;
    MemberPointer steps[2][3]; /* by state and phase: (walker, position) */
} PathWalkerTable;

typedef struct PathWalker {
    u32 state;                                   /* 0x00: 0 or 1, the row of steps */
    u32 phase;                                   /* 0x04: 0 to 2 */
    u32 status;                                  /* 0x08 */
    s32 goal_x;                                  /* 0x0c: the goal tile */
    s32 goal_z;                                  /* 0x10 */
    s32 goal_acre_x;                             /* 0x14: the goal acre */
    s32 goal_acre_z;                             /* 0x18 */
    s32 stop_x;                                  /* 0x1c: the junction it walks to */
    s32 stop_z;                                  /* 0x20 */
    u32 unk_24;                                  /* 0x24 */
    const PathWalkerTable *table;                /* 0x28 */
    PathWalkerJunction trail[PATH_WALKER_TRAIL]; /* 0x2c */
    u8 unk_86[2];                                /* 0x86 */
    s32 heading;                                 /* 0x88: the direction it walks in, 0 for none */
    s32 mode;                                    /* 0x8c: PATH_WALKER_* */
    u32 return_dir;                              /* 0x90: the step index back to a path, 4 for none */
    s32 last_x;                                  /* 0x94: a tile it was on (func_02013934) */
    s32 last_z;                                  /* 0x98 */
} PathWalker;

/* What `mode` holds: walking on from junction to junction (the junctions are remembered),
 * walking back to one remembered, and neither (off the paths, or starting). */
#define PATH_WALKER_ONWARD 0
#define PATH_WALKER_BACK 1
#define PATH_WALKER_NONE 2

void PathWalker_PickInRow4(PathWalkerTile *out, u32 self, const Vec3 *position);
int PathWalker_InGoalAcreA(PathWalker *self, const Vec3 *position);
void PathWalker_PickInAnyAcre(PathWalkerTile *out, PathWalker *self);
int PathWalker_InGoalAcreB(PathWalker *self, const Vec3 *position);
void PathWalker_PickInOwnAcre(PathWalkerTile *out, PathWalker *self, void *position, void *owner);
int PathWalker_PlaceNearGoal(PathWalker *self, Vec3 *position);
int PathWalker_OnGoalTileA(PathWalker *self, const Vec3 *position);
void PathWalker_PickOwnFront(PathWalkerTile *out, int self, int position, void *owner);
int PathWalker_InGoalAcreC(PathWalker *self, const Vec3 *position);
void PathWalker_PickInOtherAcre(PathWalkerTile *out, PathWalker *self, void *position, void *owner);
int PathWalker_StepUntilArrived(PathWalker *self, const Vec3 *position);
int PathWalker_OnGoalTileB(PathWalker *self, const Vec3 *position);
void PathWalker_PickOtherFront(PathWalkerTile *out, int self, int position, void *owner);
int PathWalker_InFlaggedAcre(void *self, const Vec3 *position);
void PathWalker_PickInFlaggedAcre(PathWalkerTile *out, PathWalker *self);
int PathWalker_PlaceAtRandom(PathWalker *self, Vec3 *position);
int PathWalker_StepToNeighbour(PathWalker *self, Vec3 *position);
int PathWalker_StepToNeighbourOn(PathWalker *self, Vec3 *position, PathWalkerMap *map);
int PathWalker_StepAlong(PathWalker *self, Vec3 *position);
int PathWalker_StepAlongOn(PathWalker *self, Vec3 *position, PathWalkerMap *map);
int PathWalker_StepToPath(PathWalker *self, Vec3 *position);
int PathWalker_StepToPathOn(PathWalker *self, Vec3 *position, PathWalkerTile *limit, PathWalkerMap *map);
void PathWalker_ChooseRoute(PathWalker *self, const Vec3 *position);
int PathWalker_Opposite(int self, int direction);
void PathWalker_PickInAcre(PathWalkerTile *out, PathWalker *self, const s32 *acre, PathWalkerMap *map);
int PathWalker_Step(PathWalker *self, Vec3 *position);
int PathWalker_Status(const PathWalker *self);
PathWalkerJunction PathWalker_PopTo(PathWalker *self, const PathWalkerTile *tile);
int PathWalker_FindJunction(PathWalker *self, const PathWalkerTile *tile);
void PathWalker_PushJunction(PathWalker *self, int tried, int from, const PathWalkerTile *tile);
int PathWalker_TrailLength(PathWalker *self);
void PathWalker_ClearTrail(PathWalker *self);
int PathWalker_FindJunctionAlong(PathWalker *self, PathWalkerTile *out, PathWalkerTile *from, int direction,
                                 const PathWalkerTile *limit, PathWalkerMap *map);
int PathWalker_StepIndex(int self, int direction);
int PathWalker_Arrived(PathWalker *self, const Vec3 *position);

/* The kinds of walk (`status`: the row of data_021c1914, a table of seven PathWalkerTable
 * filled at start-up, whose `unk_08` picks the goal tile); 7 for none. */
#define PATH_WALKER_KINDS 7

int PathWalker_FindWayToPath(PathWalker *self, u32 *stop, const Vec3 *position);
int PathWalker_StepToClearNeighbour(PathWalker *self, Vec3 *position, PathWalkerMap *map);
int PathWalker_SearchLine(PathWalker *self, Vec3 *point, const PathWalkerTile *from, const PathWalkerTile *step, int count,
                          const PathWalkerTile *limit, int check_ground, PathWalkerMap *map);
int PathWalker_IsWalking(const PathWalker *self);
void PathWalker_SetState(PathWalker *self, int state);
void PathWalker_ReplanIfMoved(PathWalker *self, Vec3 *position);
void PathWalker_MarkTileUnknown(PathWalker *self);
void PathWalker_KeepTile(PathWalker *self, const Vec3 *position);
void PathWalker_Start(PathWalker *self, Vec3 *position, u32 kind, int state, void *owner);
void PathWalker_Init(PathWalker *self);
void PathWalker_Destruct(PathWalker *self);
int PathWalker_Construct(PathWalker *self);

#endif
