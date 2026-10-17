/* Overlay 32: the data of scene 0x01 (data_020e5688 names each scene's overlay), a room, so
 * loaded with overlay 4 (data_020e5538). Its one function is its static initialiser, run when
 * the overlay is loaded, which fills in the count of the step of the scene's setup
 * (scene_setup.h) that makes overlay 4's shared objects, copied from overlay 4's constant (the
 * compiler cannot fold another overlay's constant); a point, registered for destruction like a
 * static C++ object; the scene's exits (scene_exit.h), each made by SceneExit_Init and
 * registered for destruction. */
#include "clean.h"
#include "autoload_2/vector.h"
#include "main/scene_exit.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). */
extern const u8 data_ov004_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov032_0226028c;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov032InitRecord {
    struct Ov032InitRecord *next;
    void *destruct;
    void *object;
} Ov032InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a point: nothing (the game's function is handed on). */
extern void func_020012dc(void *object);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern Vec3 data_ov032_022602e4;
extern SceneExit data_ov032_0226032c, data_ov032_02260348, data_ov032_02260364, data_ov032_02260380, data_ov032_0226039c,
    data_ov032_022603b8, data_ov032_022603d4;
extern Ov032InitRecord data_ov032_022602cc, data_ov032_022602f0, data_ov032_02260308, data_ov032_02260320, data_ov032_022602c0,
    data_ov032_022602d8, data_ov032_022602fc, data_ov032_02260314;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov032_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov032InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov032_02260020: the scene's tables filled in, in this order. */
void Ov032Init_SceneTables(void)
{
    data_ov032_0226028c.count = data_ov004_02256914;
    data_ov032_022602e4.x = 0x10000;
    data_ov032_022602e4.y = 0;
    data_ov032_022602e4.z = 0x1d000;
    __register_global_object(&data_ov032_022602e4, (void *) (uintptr_t) func_020012dc, &data_ov032_022602cc);
    ov032_init_exit(&data_ov032_0226032c, SCENE_EXIT_TO_BUILDINGS_5014, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 4,
                    &data_ov032_022602f0);
    ov032_init_exit(&data_ov032_02260348, 0x07, &(Vec3){0xf000, 0, 0x1d000}, 0x10c00000, 0x4000, 2, 2, -0x4000, 1,
                    &data_ov032_02260308);
    ov032_init_exit(&data_ov032_02260364, 0x05, &(Vec3){0xf000, 0, 0x1d000}, 0x10c00000, 0x4000, 2, 2, -0x4000, 1,
                    &data_ov032_02260320);
    ov032_init_exit(&data_ov032_02260380, 0x04, &(Vec3){0x17000, 0, 0x1a000}, 0x23800000, -0x4000, 2, 2, -0x4000, 3,
                    &data_ov032_022602c0);
    ov032_init_exit(&data_ov032_0226039c, 0x03, &(Vec3){0x9000, 0, 0x1a000}, 0x23800000, 0x4000, 2, 2, 0x4000, 3,
                    &data_ov032_022602d8);
    ov032_init_exit(&data_ov032_022603b8, 0x02, &data_ov032_022602e4, 0x23800000, -0x8000, 2, 2, -0x8000, 3,
                    &data_ov032_022602fc);
    ov032_init_exit(&data_ov032_022603d4, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov032_02260314);
}
CLEAN_AS(__sinit_ov032_02260020, Ov032Init_SceneTables)
