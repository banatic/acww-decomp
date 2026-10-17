/* Overlay 18: the data of scene 0x32 (data_020e5688 names each scene's overlay), a room, so
 * loaded with overlay 4 (data_020e5538). Its one function is its static initialiser, run when
 * the overlay is loaded, which fills in the scene's exits (scene_exit.h), each made by
 * SceneExit_Init and registered for destruction. */
#include "clean.h"
#include "autoload_2/vector.h"
#include "main/scene_exit.h"
#include "main/scene_setup.h"
#include "types.h"

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov018InitRecord {
    struct Ov018InitRecord *next;
    void *destruct;
    void *object;
} Ov018InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern SceneExit data_ov018_02260164, data_ov018_02260180, data_ov018_0226019c;
extern Ov018InitRecord data_ov018_02260140, data_ov018_0226014c, data_ov018_02260158;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov018_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov018InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov018_02260020: the scene's tables filled in, in this order. */
void Ov018Init_SceneTables(void)
{
    ov018_init_exit(&data_ov018_02260164, SCENE_EXIT_TO_BUILDINGS_5014, &(Vec3){0, 0, 0}, 0x800000, 0, 3, 2, 0, 0,
                    &data_ov018_02260140);
    ov018_init_exit(&data_ov018_02260180, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 3, 2, 0, 0,
                    &data_ov018_0226014c);
    ov018_init_exit(&data_ov018_0226019c, SCENE_EXIT_TO_BUILDING_500B, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov018_02260158);
}
CLEAN_AS(__sinit_ov018_02260020, Ov018Init_SceneTables)
