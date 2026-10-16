/* The saved and the marked place (scene_place.h). */
#include "scene_place.h"

#include "clean.h"
#include "main/actor_table.h"
#include "main/scene_tables.h"

static_assert(offsetof(ScenePlace, player_param) == 0x0c, "player_param");
static_assert(offsetof(ScenePlace, angle) == 0x10, "angle");
static_assert(offsetof(ScenePlace, scene) == 0x12, "scene");
static_assert(offsetof(ScenePlace, tile_z) == 0x14, "tile_z");
static_assert(sizeof(ScenePlace) == 0x18, "place");

/* The scene where ScenePlace_SavePlayer keeps the point from coming too near (on z). */
#define SCENE_PLACE_Z_LIMIT_SCENE 0x0b
/* What a reset place holds. */
#define SCENE_PLACE_START_XZ 0x30000 /* 48.0 */
#define SCENE_PLACE_START_PARAM 0x00800000u
/* The player's state as func_02095fc0 gives it goes to bits 22-29 of the parameter. */
#define SCENE_PLACE_STATE_SHIFT 22
#define SCENE_PLACE_STATE_MASK 0x3fc00000u

extern ScenePlace data_021f69a0; /* the saved place */
extern ScenePlace data_021f69b8; /* the marked place */

/* ScenePlace_SavePlayer's function-local static: its guard and the lowest z in scene 0x0b. */
extern u32 data_021f6934;
extern fx32 data_021f6940;
extern const fx32 data_020ca0f0;

/* ScenePlace_Reset's function-local static point: its guard, the point and its destruction
 * record. */
extern u32 data_021f6938;
extern Vec3 data_021f6994;
extern u8 data_021f6988[];

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020012dc(void *object); /* the static objects' destructor: nothing */

/* The current scene. */
extern u8 func_020b65c4(void);
/* The player's actor's point and angle, and its state (0x93 without an actor; then nothing is
 * written). */
extern int func_02095fc0(Vec3 *position, s16 *angle);

/* func_020b5e90: the marked place back to its start. */
void ScenePlace_ResetMarked(void)
{
    ScenePlace_Reset(&data_021f69b8);
}
CLEAN_AS(func_020b5e90, ScenePlace_ResetMarked)

/* func_020b5ea0: the marked place set, when `scene` is one; whether it was. */
int ScenePlace_SetMarked(int unused, int scene, const Vec3 *position, int player_param, short angle, int tile_x, int tile_z)
{
    (void) unused;
    if (ScenePlace_IsScene((unsigned int) scene)) {
        ScenePlace_Set(&data_021f69b8, (u8) scene, position, (unsigned int) player_param, angle, (unsigned int) tile_x,
                       (unsigned int) tile_z);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020b5ea0, ScenePlace_SetMarked)

/* func_020b5ee4: the saved place set to where the player's actor is in the current scene,
 * moved `z_offset` along z, with its angle, its tile and its state in bits 22-29 of the
 * parameter. In scene 0x0b the point is first kept at least 1.0 past data_020ca0f0 on z (a
 * limit computed on the first call). Whether the place was set (the scene is one).
 * BUG: without the player's actor func_02095fc0 writes neither point nor angle and the ROM saves
 * what was on the stack; here that is (0, 0, 0) and angle 0, with state 0x93. */
int ScenePlace_SavePlayer(int unused, int z_offset)
{
    Vec3 position = {0, 0, 0};
    s16 angle = 0;
    int tile_x;
    int tile_z;
    int state;

    (void) unused;
    if ((data_021f6934 & 1) == 0) {
        data_021f6940 = (fx32) ((u32) data_020ca0f0 + 0x1000u);
        data_021f6934 |= 1;
    }

    state = func_02095fc0(&position, &angle);
    tile_x = 0;
    tile_z = 0;
    Position_Tile(&tile_x, &tile_z, (const Position *) &position);

    if (func_020b65c4() == SCENE_PLACE_Z_LIMIT_SCENE && position.z < data_021f6940) {
        position.z = data_021f6940;
    }
    position.z = (fx32) ((u32) position.z + (u32) z_offset);

    int entry = SceneTables_EntryRecord();
    int scene = func_020b65c4();
    return ScenePlace_SetSaved(entry, scene, &position,
                               (int) (((u32) state << SCENE_PLACE_STATE_SHIFT) & SCENE_PLACE_STATE_MASK), angle, tile_x,
                               tile_z);
}
CLEAN_AS(func_020b5ee4, ScenePlace_SavePlayer)

/* func_020b5f84: the saved place set, when `scene` is one; whether it was. */
int ScenePlace_SetSaved(int unused, int scene, const Vec3 *position, int player_param, short angle, int tile_x, int tile_z)
{
    (void) unused;
    if (ScenePlace_IsScene((unsigned int) scene)) {
        ScenePlace_Set(&data_021f69a0, (u8) scene, position, (unsigned int) player_param, angle, (unsigned int) tile_x,
                       (unsigned int) tile_z);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020b5f84, ScenePlace_SetSaved)

/* func_020b64c0: whether `scene` is one of the scenes. */
int ScenePlace_IsScene(unsigned int scene)
{
    return scene < SCENE_PLACE_SCENES;
}
CLEAN_AS(func_020b64c0, ScenePlace_IsScene)

/* func_020b64cc */
signed char ScenePlace_TileZ(const ScenePlace *place)
{
    return place->tile_z;
}
CLEAN_AS(func_020b64cc, ScenePlace_TileZ)

/* func_020b64d4 */
signed char ScenePlace_TileX(const ScenePlace *place)
{
    return place->tile_x;
}
CLEAN_AS(func_020b64d4, ScenePlace_TileX)

/* func_020b64dc */
int ScenePlace_Scene(const ScenePlace *place)
{
    return place->scene;
}
CLEAN_AS(func_020b64dc, ScenePlace_Scene)

/* func_020b64e0 */
int ScenePlace_Angle(const ScenePlace *place)
{
    return place->angle;
}
CLEAN_AS(func_020b64e0, ScenePlace_Angle)

/* func_020b64e8 */
int ScenePlace_PlayerParam(const ScenePlace *place)
{
    return (int) place->player_param;
}
CLEAN_AS(func_020b64e8, ScenePlace_PlayerParam)

/* func_020b64ec: the place's point (the place itself, which starts with it). */
void *ScenePlace_Position(ScenePlace *place)
{
    return &place->position;
}
CLEAN_AS(func_020b64ec, ScenePlace_Position)

/* func_020b64f0: every field of the place; the tiles are kept as signed bytes. */
void ScenePlace_Set(ScenePlace *place, unsigned char scene, const Vec3 *position, unsigned int player_param, short angle,
                    unsigned int tile_x, unsigned int tile_z)
{
    place->scene = scene;
    place->position.x = position->x;
    place->position.y = position->y;
    place->position.z = position->z;
    place->player_param = player_param;
    place->angle = angle;
    place->tile_x = (s8) (u8) tile_x;
    place->tile_z = (s8) (u8) tile_z;
}
CLEAN_AS(func_020b64f0, ScenePlace_Set)

/* func_020b6518: the place back to its start: scene 0 at (48.0, 0, 48.0), angle 0, parameter
 * 0x00800000 and no tile.
 * QUIRK: the point is a function-local static, built on the first call and registered for
 * destruction (func_020012dc, which does nothing). */
void ScenePlace_Reset(ScenePlace *place)
{
    if ((data_021f6938 & 1) == 0) {
        data_021f6994.x = SCENE_PLACE_START_XZ;
        data_021f6994.y = 0;
        data_021f6994.z = SCENE_PLACE_START_XZ;
        __register_global_object(&data_021f6994, (void *) func_020012dc, data_021f6988);
        data_021f6938 |= 1;
    }
    ScenePlace_Set(place, 0, &data_021f6994, SCENE_PLACE_START_PARAM, 0, (unsigned int) -1, (unsigned int) -1);
}
CLEAN_AS(func_020b6518, ScenePlace_Reset)

/* func_020b657c: a place's destructor: nothing. */
void ScenePlace_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_020b657c, ScenePlace_Destruct)

/* func_020b6580: a place's constructor: reset (ScenePlace_Reset); the place. */
int ScenePlace_Construct(ScenePlace *place)
{
    ScenePlace_Reset(place);
    return (int) (uintptr_t) place;
}
CLEAN_AS(func_020b6580, ScenePlace_Construct)
