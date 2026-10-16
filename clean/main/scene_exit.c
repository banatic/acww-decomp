/* The ways out of a scene and main's entry record (scene_exit.h). */
#include "scene_exit.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/global_021dc5b0.h"
#include "main/scene_place.h"
#include "main/scene_tables.h"
#include "main/session.h"

static_assert(offsetof(SceneExit, angle) == 0x02, "angle");
static_assert(offsetof(SceneExit, position) == 0x04, "position");
static_assert(offsetof(SceneExit, player_param) == 0x10, "player_param");
static_assert(offsetof(SceneExit, change_arg) == 0x14, "change_arg");
static_assert(offsetof(SceneExit, door_angle) == 0x16, "door_angle");
static_assert(offsetof(SceneExit, door_kind) == 0x18, "door_kind");
static_assert(sizeof(SceneExit) == 0x1c, "exit");
static_assert(offsetof(SceneExitScene, exits) == 0x0c, "exits");

/* The process class that changes scenes (scene_change.h) and what it is asked for with. */
#define SCENE_EXIT_CHANGE_CLASS 5
#define SCENE_EXIT_CHANGE_ARG 3
#define SCENE_EXIT_CHANGE_FLAGS 1
/* No exit index. */
#define SCENE_EXIT_NO_INDEX (-1)
/* An exit in the table with no height is given this one when taken. */
#define SCENE_EXIT_DEFAULT_HEIGHT 0x200
/* A door of this kind is taken as the next kind in a session. */
#define SCENE_EXIT_SESSION_KIND 7
/* What the exits to a building of the town map lead to: scene 0 (where the town map is), 1.0
 * further on z than the building's front, with this parameter and angle 0. */
#define SCENE_EXIT_BUILDING_SCENE 0
#define SCENE_EXIT_BUILDING_STEP 0x1000u
#define SCENE_EXIT_BUILDING_PARAM 0x0f000000u
/* The door facings along z and along x. */
#define SCENE_EXIT_FACING_Z_A 0
#define SCENE_EXIT_FACING_Z_B (-0x8000)
#define SCENE_EXIT_FACING_X_A 0x4000
#define SCENE_EXIT_FACING_X_B (-0x4000)

extern SceneExitScene *data_021f6948; /* the running scene's setup, or NULL */
extern NetSession *data_020ccf94;
extern ScenePlace data_021f69a0; /* the saved place */
extern ScenePlace data_021f69b8; /* the marked place */
/* The process class asked for next (func_020a53ec sets it). */
extern u16 data_020e3c80;

/* Asks for process class `class_id` as the next scene, with `param` and `arg` for its spawn
 * (`flags` is not used). */
extern void func_020a53ec(int class_id, int param, int arg, int flags);

/* A point copied a coordinate at a time, x first, as the ROM does (which matters when the two
 * overlap). */
static void scene_exit_copy_point(Vec3 *to, const Vec3 *from)
{
    to->x = from->x;
    to->y = from->y;
    to->z = from->z;
}

/* The exit `index` of the running scene's table, or NULL when there is none. */
static SceneExit *scene_exit_find(int index)
{
    if (index == SCENE_EXIT_NO_INDEX || data_021f6948 == NULL) {
        return NULL;
    }
    SceneExitList *list = data_021f6948->exits;
    if (list == NULL || list->exits == NULL) {
        return NULL;
    }
    if (index < 0 || index >= list->count) {
        return NULL;
    }
    return &list->exits[index];
}

/* SBServerGetFlags (0x020b5e18, named after a GameSpy function by mistake): the byte kept for
 * process class 6. */
int SceneExit_NextArg(const SceneExit *exit)
{
    return exit->next_arg;
}
CLEAN_AS(SBServerGetFlags, SceneExit_NextArg)

/* func_020b5e1c */
void SceneExit_SetChangeArg(SceneExit *exit, int value)
{
    exit->change_arg = (u8) value;
}
CLEAN_AS(func_020b5e1c, SceneExit_SetChangeArg)

/* SBServerGetState (0x020b5e20, named after a GameSpy function by mistake): what process
 * class 5 is asked for with. */
int SceneExit_ChangeArg(const SceneExit *exit)
{
    return exit->change_arg;
}
CLEAN_AS(SBServerGetState, SceneExit_ChangeArg)

/* func_020b5e24 */
int SceneExit_UsesOwnPoint(const SceneExit *exit)
{
    return exit->own_point != 0;
}
CLEAN_AS(func_020b5e24, SceneExit_UsesOwnPoint)

/* func_020b5e34 */
int SceneExit_PlayerParam(const SceneExit *exit)
{
    return (int) exit->player_param;
}
CLEAN_AS(func_020b5e34, SceneExit_PlayerParam)

/* func_020b5e38 */
int SceneExit_Angle(const SceneExit *exit)
{
    return exit->angle;
}
CLEAN_AS(func_020b5e38, SceneExit_Angle)

/* func_020b5e40: the exit's point, as an address. */
int SceneExit_Position(SceneExit *exit)
{
    return (int) (uintptr_t) &exit->position;
}
CLEAN_AS(func_020b5e40, SceneExit_Position)

/* func_020b5e44: unless the process that changes scenes is already asked for, asks for it with
 * `change_arg` and keeps `next_arg` for the scene after it. */
void SceneExit_RequestChange(int change_arg, int next_arg)
{
    if (data_020e3c80 != SCENE_EXIT_CHANGE_CLASS) {
        func_020a53ec(SCENE_EXIT_CHANGE_CLASS, change_arg, SCENE_EXIT_CHANGE_ARG, SCENE_EXIT_CHANGE_FLAGS);
        Global021dc5b0_Set((u8) next_arg);
    }
}
CLEAN_AS(func_020b5e44, SceneExit_RequestChange)

/* func_020b5e70: the scene the entry record leads to (SCENE_EXIT_NONE for none). */
int SceneExit_NextScene(void)
{
    return SceneExit_Scene((const SceneExit *) (uintptr_t) SceneTables_EntryRecord());
}
CLEAN_AS(func_020b5e70, SceneExit_NextScene)

/* func_020b5e84 */
int SceneExit_Scene(const SceneExit *exit)
{
    return exit->scene;
}
CLEAN_AS(func_020b5e84, SceneExit_Scene)

/* func_020b5e88: the exit free again. */
void SceneExit_Clear(SceneExit *exit)
{
    exit->scene = SCENE_EXIT_NONE;
}
CLEAN_AS(func_020b5e88, SceneExit_Clear)

/* func_020b5fc8: where to stand at the door of exit `index`: the centre of the tile `from` is
 * on, at the height of `from`, but along the way the door faces (z for facings 0 and 0x8000, x
 * for 0x4000 and 0xc000) `from`'s own coordinate. Without such an exit, `from` itself and 0.
 * QUIRK: with `point` the same vector as `from`, the coordinate kept is the tile centre's. */
int SceneExit_DoorPoint(const SceneExit *entry, int index, Vec3 *point, const Vec3 *from)
{
    int kind;
    s16 facing;
    Vec3 centre;

    if (SceneExit_DoorInfo(entry, index, &kind, &facing) == 0) {
        point->x = from->x;
        point->y = from->y;
        point->z = from->z;
        return 0;
    }
    AcreTile_SnapToTileCentre(&centre, from);
    fx32 z = centre.z;
    fx32 y = from->y;
    fx32 x = centre.x;
    point->x = x;
    point->y = y;
    point->z = z;
    if (facing == SCENE_EXIT_FACING_Z_A || facing == SCENE_EXIT_FACING_Z_B) {
        point->x = from->x;
    } else if (facing == SCENE_EXIT_FACING_X_A || facing == SCENE_EXIT_FACING_X_B) {
        point->z = from->z;
    }
    return 1;
}
CLEAN_AS(func_020b5fc8, SceneExit_DoorPoint)

/* func_020b6044: the door's kind and facing of exit `index` (each skipped when NULL); whether
 * there is such an exit (both 0 when not).
 * QUIRK: both are cleared before the NULL checks, so passing NULL crashes. */
int SceneExit_DoorInfo(const SceneExit *entry, int index, int *kind, s16 *door_angle)
{
    (void) entry;
    *kind = 0;
    *door_angle = 0;
    SceneExit *exit = scene_exit_find(index);
    if (exit == NULL) {
        return 0;
    }
    if (kind != NULL) {
        *kind = exit->door_kind;
    }
    if (door_angle != NULL) {
        *door_angle = exit->door_angle;
    }
    return 1;
}
CLEAN_AS(func_020b6044, SceneExit_DoorInfo)

/* func_020b6098: takes exit `index` of the running scene: what it leads to is worked out
 * (SceneExit_Resolve); an exit to the saved or the marked place writes that place back with it
 * (a building's front becomes the marked place). Then the entry record, if free, is set to it.
 * Whether it was.
 * BUG: when the building of an exit 0x3d or 0x3e is not on the town map nothing is worked out,
 * and the ROM writes what was on the stack to the marked place and the entry record; here
 * zeros. */
int SceneExit_Take(SceneExit *entry, int index)
{
    u8 scene = 0;
    u8 change_arg = 0;
    u8 next_arg = 0;
    s16 angle = 0;
    Vec3 position = {0, 0, 0};
    int player_param = 0;
    int tile_x = 0;
    int tile_z = 0;

    int source =
        SceneExit_Resolve(entry, index, &scene, &position, &player_param, &angle, &change_arg, &next_arg, &tile_x, &tile_z);
    if (source == 0) {
        return 0;
    }
    if (source == SCENE_EXIT_FROM_SAVED) {
        ScenePlace_Set(&data_021f69a0, scene, &position, (unsigned int) player_param, angle, (unsigned int) tile_x,
                       (unsigned int) tile_z);
    } else if (source == SCENE_EXIT_FROM_MARKED) {
        ScenePlace_Set(&data_021f69b8, scene, &position, (unsigned int) player_param, angle, (unsigned int) tile_x,
                       (unsigned int) tile_z);
    }
    return SceneExit_SetTo(entry, scene, &position, (unsigned int) player_param, angle, change_arg, next_arg) != 0;
}
CLEAN_AS(func_020b6098, SceneExit_Take)

/* func_020b6140: what exit `index` of the running scene leads to (SceneExit_ResolveSpecial for
 * the exits to places, else the table's record), and which (enum SceneExitSource); 0 without
 * such an exit. The tile is only given for the places.
 * QUIRK: an exit of the table with height 0 is given SCENE_EXIT_DEFAULT_HEIGHT in the table
 * itself; in a session a door of kind 7 leads as kind 8.
 * BUG: for an exit of the table the ROM writes what was on the stack to `tile_x` and `tile_z`
 * (when not NULL); here 0 (no caller reads them then). */
int SceneExit_Resolve(const SceneExit *entry, int index, u8 *scene, Vec3 *position, int *player_param, s16 *angle,
                      u8 *change_arg, u8 *next_arg, int *tile_x, int *tile_z)
{
    int found_tile_x = 0;
    int found_tile_z = 0;

    int source = SceneExit_ResolveSpecial(entry, index, scene, position, player_param, angle, &found_tile_x, &found_tile_z,
                                          change_arg, next_arg);
    if (tile_x != NULL) {
        *tile_x = found_tile_x;
    }
    if (tile_z != NULL) {
        *tile_z = found_tile_z;
    }
    if (source != SCENE_EXIT_FROM_TABLE) {
        return source;
    }

    SceneExit *exit = scene_exit_find(index);
    if (exit == NULL) {
        return 0;
    }
    u8 to = exit->scene;
    if (exit->position.y == 0) {
        exit->position.y = SCENE_EXIT_DEFAULT_HEIGHT;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) != 0 && to == SCENE_EXIT_SESSION_KIND) {
        to = SCENE_EXIT_SESSION_KIND + 1;
    }
    *scene = to;
    scene_exit_copy_point(position, &exit->position);
    *player_param = (int) exit->player_param;
    *angle = exit->angle;
    *change_arg = exit->change_arg;
    *next_arg = exit->next_arg;
    return source;
}
CLEAN_AS(func_020b6140, SceneExit_Resolve)

/* An exit to a building of the town map: scene 0 at the building's front (1.0 further on z) and
 * its tile, when the building is there. */
static void scene_exit_to_building(const SceneExit *exit, int found, Vec3 *front, int front_tile_x, int front_tile_z,
                                   u8 *scene, Vec3 *position, int *player_param, s16 *angle, int *tile_x, int *tile_z,
                                   u8 *change_arg, u8 *next_arg)
{
    if (!found) {
        return;
    }
    front->z = (fx32) ((u32) front->z + SCENE_EXIT_BUILDING_STEP);
    *scene = SCENE_EXIT_BUILDING_SCENE;
    scene_exit_copy_point(position, front);
    *player_param = (int) SCENE_EXIT_BUILDING_PARAM;
    *angle = 0;
    *tile_x = front_tile_x;
    *tile_z = front_tile_z;
    *change_arg = exit->change_arg;
    *next_arg = exit->next_arg;
}

/* A place's fields with the exit's two bytes. */
static void scene_exit_to_place(const SceneExit *exit, ScenePlace *place, u8 *scene, Vec3 *position, int *player_param,
                                s16 *angle, int *tile_x, int *tile_z, u8 *change_arg, u8 *next_arg)
{
    *scene = (u8) ScenePlace_Scene(place);
    scene_exit_copy_point(position, (const Vec3 *) ScenePlace_Position(place));
    *player_param = ScenePlace_PlayerParam(place);
    *angle = (s16) ScenePlace_Angle(place);
    *tile_x = ScenePlace_TileX(place);
    *tile_z = ScenePlace_TileZ(place);
    *change_arg = exit->change_arg;
    *next_arg = exit->next_arg;
}

/* func_020b6214: for an exit `index` of the running scene to 0x3c-0x3f, what it leads to, from
 * the saved place (SCENE_EXIT_FROM_SAVED), the marked place or a building of the town map
 * (SCENE_EXIT_FROM_MARKED); SCENE_EXIT_FROM_TABLE for any other exit, and for no exit. The town
 * map is looked up for any exit found. Nothing is written for a building not on the map. */
int SceneExit_ResolveSpecial(const SceneExit *entry, int index, u8 *scene, Vec3 *position, int *player_param, s16 *angle,
                             int *tile_x, int *tile_z, u8 *change_arg, u8 *next_arg)
{
    (void) entry;
    SceneExit *exit = scene_exit_find(index);
    if (exit == NULL) {
        return SCENE_EXIT_FROM_TABLE;
    }
    int town = (int) AcreMap_Town();
    Vec3 front = {0, 0, 0};
    int front_tile_x = 0;
    int front_tile_z = 0;

    switch (exit->scene) {
        case SCENE_EXIT_TO_BUILDINGS_5014: {
            int found = AcreMap_HasBuilding5014(town, (int) (uintptr_t) &front, (int) (uintptr_t) &front_tile_x,
                                                (int) (uintptr_t) &front_tile_z);
            scene_exit_to_building(exit, found, &front, front_tile_x, front_tile_z, scene, position, player_param, angle,
                                   tile_x, tile_z, change_arg, next_arg);
            return SCENE_EXIT_FROM_MARKED;
        }
        case SCENE_EXIT_TO_BUILDING_500B: {
            int found = AcreMap_HasBuilding500b(town, (int) (uintptr_t) &front, (int) (uintptr_t) &front_tile_x,
                                                (int) (uintptr_t) &front_tile_z);
            scene_exit_to_building(exit, found, &front, front_tile_x, front_tile_z, scene, position, player_param, angle,
                                   tile_x, tile_z, change_arg, next_arg);
            return SCENE_EXIT_FROM_MARKED;
        }
        case SCENE_EXIT_TO_SAVED_PLACE:
            scene_exit_to_place(exit, &data_021f69a0, scene, position, player_param, angle, tile_x, tile_z, change_arg,
                                next_arg);
            return SCENE_EXIT_FROM_SAVED;
        case SCENE_EXIT_TO_MARKED_PLACE:
            scene_exit_to_place(exit, &data_021f69b8, scene, position, player_param, angle, tile_x, tile_z, change_arg,
                                next_arg);
            return SCENE_EXIT_FROM_MARKED;
        default:
            return SCENE_EXIT_FROM_TABLE;
    }
}
CLEAN_AS(func_020b6214, SceneExit_ResolveSpecial)

/* func_020b63f4: a free exit set to `scene` at `position`; whether it was free. */
int SceneExit_SetTo(SceneExit *exit, unsigned char scene, const Vec3 *position, unsigned int player_param, short angle,
                    unsigned char change_arg, unsigned char next_arg)
{
    if (exit->scene != SCENE_EXIT_NONE) {
        return 0;
    }
    exit->scene = scene;
    scene_exit_copy_point(&exit->position, position);
    exit->player_param = player_param;
    exit->angle = angle;
    exit->own_point = 0;
    exit->change_arg = change_arg;
    exit->next_arg = next_arg;
    return 1;
}
CLEAN_AS(func_020b63f4, SceneExit_SetTo)

/* func_020b6434: a free exit set to `scene` at the scene's own point; whether it was free. */
int SceneExit_SetToScene(SceneExit *exit, unsigned char scene, unsigned char change_arg, unsigned char next_arg)
{
    if (exit->scene != SCENE_EXIT_NONE) {
        return 0;
    }
    exit->scene = scene;
    exit->change_arg = change_arg;
    exit->next_arg = next_arg;
    exit->own_point = 1;
    return 1;
}
CLEAN_AS(func_020b6434, SceneExit_SetToScene)

/* func_020b6454: a free exit set to `scene` at the scene's own point, its bytes kept; whether
 * it was free. */
unsigned char SceneExit_SetToSceneOnly(SceneExit *exit, unsigned char scene)
{
    if (exit->scene != SCENE_EXIT_NONE) {
        return 0;
    }
    exit->scene = scene;
    exit->own_point = 1;
    return 1;
}
CLEAN_AS(func_020b6454, SceneExit_SetToSceneOnly)

/* func_020b6468: an exit of a table, every field but own_point. */
void SceneExit_Init(SceneExit *exit, unsigned char scene, const Vec3 *position, int player_param, short angle,
                    unsigned char change_arg, unsigned char next_arg, short door_angle, unsigned char door_kind)
{
    exit->scene = scene;
    scene_exit_copy_point(&exit->position, position);
    exit->player_param = (u32) player_param;
    exit->angle = angle;
    exit->change_arg = change_arg;
    exit->next_arg = next_arg;
    exit->door_angle = door_angle;
    exit->door_kind = door_kind;
}
CLEAN_AS(func_020b6468, SceneExit_Init)

/* func_020b649c: an exit's destructor: nothing. */
void SceneExit_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_020b649c, SceneExit_Destruct)

/* func_020b64a0: an exit's constructor: free, at the scene's own point, (0, 0, 0) and angle 0,
 * with both bytes 2. */
void SceneExit_Construct(SceneExit *exit)
{
    exit->scene = SCENE_EXIT_NONE;
    exit->position.x = 0;
    exit->position.y = 0;
    exit->position.z = 0;
    exit->player_param = 0;
    exit->angle = 0;
    exit->own_point = 1;
    exit->change_arg = 2;
    exit->next_arg = 2;
    exit->door_angle = 0;
    exit->door_kind = 0;
}
CLEAN_AS(func_020b64a0, SceneExit_Construct)
