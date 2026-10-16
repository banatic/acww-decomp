/* Where a scene object steps next on the field's paths (scene_path_step.h). */
#include "scene_path_step.h"

#include "acre_tile.h"
#include "clean.h"
#include "itcm/vector.h"
#include "session.h"
#include "town_tile.h"

/* The steps to the tiles around a tile, and the path direction bit of each (1 << step). */
extern const Vec3 data_020c81fc[SCENE_PATH_STEPS];
extern const u32 data_020c81b4[SCENE_PATH_STEPS];

extern AcreMap *data_021c80bc; /* the field's map */
extern NetSession *data_020ccf94;

/* The point at 0x6f4 of the field actor of session slot `slot`, or null. */
extern Vec3 *func_02095794(u32 slot);
/* Clears `size` bytes. */
extern void *func_02137550(void *dst, u32 size);

/* The object's parts used here. */
#define SCENE_PATH_STEP_OBJECT_POSITION 0x5c /* Vec3 */
#define SCENE_PATH_STEP_OBJECT_ANGLE 0x8e    /* u16: where it faces */

/* The steps by the direction they go. */
#define SCENE_PATH_STEP_MINUS_Z 0
#define SCENE_PATH_STEP_MINUS_X 1
#define SCENE_PATH_STEP_PLUS_Z 2
#define SCENE_PATH_STEP_PLUS_X 3

/* What the step the object faces is nearer by, and the step behind it farther. */
#define SCENE_PATH_STEP_FACING_BONUS 0x2000

static void scene_path_step_copy(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* The tile `step` leads to from `tile`. */
static void scene_path_step_next(Vec3 *next, const Vec3 *tile, int step)
{
    Vec3 sum;
    Vec_Add(&sum, tile, &data_020c81fc[step]);
    scene_path_step_copy(next, &sum);
}

/* func_0201b458: `out` is where the object at `object` steps next on its way to `target`:
 * - when the object's tile has no paths, the nearest to the object of the tiles around its
 *   own that are on a path and clear (TownTile_IsClearAt); without one, `target` itself;
 * - else the tile around its own along one of its paths that is clear and nearest to `target`,
 *   counting the step the object faces 0x2000 nearer and the one behind it 0x2000 farther;
 *   when `target`'s tile has no paths and that tile is farther from it than the object's own
 *   tile, the object's position.
 * QUIRK: a distance of 0 counts as no tile found yet, so a tile at distance 0 is never chosen.
 * QUIRK: on a path without any tile found, the step to -z is taken.
 * BUG: in a linked session the tiles of the four players are read (func_02095794) and each
 * candidate is compared with them (Vec_Equal), but the answers are not used: a tile a player
 * stands on can be chosen. BUGFIX: such a tile is passed over. */
void ScenePathStep_Choose(Vec3 *out, u8 *object, const Vec3 *target)
{
    const Vec3 *position = (const Vec3 *) (const void *) (object + SCENE_PATH_STEP_OBJECT_POSITION);
    AcreMap *map = data_021c80bc;
    Vec3 tile;
    Vec3 target_tile;
    Vec3 next;
    int best_step = 0;
    fx32 best_distance = 0;

    scene_path_step_copy(out, target);
    int paths_here = AcreTile_PathDirectionsAt(map, position);
    int paths_there = AcreTile_PathDirectionsAt(map, target);
    AcreTile_SnapToTileCentre(&tile, position);
    AcreTile_SnapToTileCentre(&target_tile, target); /* not used further */
    tile.y = 0;
    target_tile.y = 0;

    if (paths_here == 0) {
        for (int step = 0; step < SCENE_PATH_STEPS; step++) {
            scene_path_step_next(&next, &tile, step);
            fx32 distance = Vec_DistanceXZ(position, &next);
            if (AcreTile_PathDirectionsAt(map, &next) == 0 || TownTile_IsClearAt(&next, NULL) == 0) {
                continue;
            }
            if (best_distance != 0 && best_distance <= distance) {
                continue;
            }
            best_distance = distance;
            best_step = step;
        }
        if (best_distance != 0) {
            scene_path_step_next(out, &tile, best_step);
        } else {
            scene_path_step_copy(out, target);
        }
        return;
    }

    fx32 own_tile_distance = Vec_DistanceXZ(target, &tile);
    Vec3 players[SESSION_SLOTS];
    func_02137550(players, sizeof(players));

    u16 angle = *(const u16 *) (const void *) (object + SCENE_PATH_STEP_OBJECT_ANGLE);
    int ahead;
    int behind;
    if (angle >= 0xe000 || angle < 0x2000) {
        ahead = SCENE_PATH_STEP_PLUS_Z;
        behind = SCENE_PATH_STEP_MINUS_Z;
    } else if (angle < 0x6000) {
        ahead = SCENE_PATH_STEP_PLUS_X;
        behind = SCENE_PATH_STEP_MINUS_X;
    } else if (angle < 0xa000) {
        ahead = SCENE_PATH_STEP_MINUS_Z;
        behind = SCENE_PATH_STEP_PLUS_Z;
    } else {
        ahead = SCENE_PATH_STEP_MINUS_X;
        behind = SCENE_PATH_STEP_PLUS_X;
    }

    if (Session_IsLinked(data_020ccf94) != 0) {
        for (u32 slot = 0; slot < SESSION_SLOTS; slot++) {
            const Vec3 *player = func_02095794(slot);
            if (player == NULL) {
                continue;
            }
            Vec3 player_tile;
            AcreTile_SnapToTileCentre(&player_tile, player);
            player_tile.y = 0;
            scene_path_step_copy(&players[slot], &player_tile);
        }
    }

    for (int step = 0; step < SCENE_PATH_STEPS; step++) {
        scene_path_step_next(&next, &tile, step);
        fx32 distance = Vec_DistanceXZ(target, &next);
        if (step == ahead) {
            distance = (fx32) ((u32) distance - SCENE_PATH_STEP_FACING_BONUS);
        } else if (step == behind) {
            distance = (fx32) ((u32) distance + SCENE_PATH_STEP_FACING_BONUS);
        }
        int occupied = 0;
        for (int slot = 0; slot < SESSION_SLOTS; slot++) {
            if (Vec_Equal(&next, &players[slot]) != 0) {
                occupied = 1;
            }
        }
#ifdef BUGFIX
        if (occupied) {
            continue;
        }
#else
        (void) occupied;
#endif
        if (TownTile_IsClearAt(&next, NULL) == 0) {
            continue;
        }
        if ((data_020c81b4[step] & (u32) paths_here) == 0) {
            continue;
        }
        if (best_distance != 0 && best_distance <= distance) {
            continue;
        }
        best_distance = distance;
        best_step = step;
    }

    if (paths_there == 0 && best_distance > own_tile_distance) {
        scene_path_step_copy(out, position);
    } else {
        scene_path_step_next(out, &tile, best_step);
    }
}
CLEAN_AS(func_0201b458, ScenePathStep_Choose)
