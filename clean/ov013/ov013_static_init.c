/* Overlay 13: the data of scene 0x1f (data_020e5688 names each scene's overlay), a room, so
 * loaded with overlay 4 (data_020e5538). Its one function is its static initialiser, run when
 * the overlay is loaded, which fills in the count of the step of the scene's setup
 * (scene_setup.h) that makes overlay 4's shared objects, copied from overlay 4's constant (the
 * compiler cannot fold another overlay's constant); the scene's exits (scene_exit.h), each made
 * by SceneExit_Init and registered for destruction. */
#include "clean.h"
#include "autoload_2/vector.h"
#include "main/scene_exit.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). */
extern const u8 data_ov004_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov013_022600d0;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov013InitRecord {
    struct Ov013InitRecord *next;
    void *destruct;
    void *object;
} Ov013InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern SceneExit data_ov013_0226014c;
extern Ov013InitRecord data_ov013_02260140;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov013_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov013InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov013_02260020: the scene's tables filled in, in this order. */
void Ov013Init_SceneTables(void)
{
    data_ov013_022600d0.count = data_ov004_02256914;
    ov013_init_exit(&data_ov013_0226014c, 0x1d, &(Vec3){0xa000, 0x200, 0x9000}, 0x23800000, 0, 2, 2, 0, 3,
                    &data_ov013_02260140);
}
CLEAN_AS(__sinit_ov013_02260020, Ov013Init_SceneTables)
