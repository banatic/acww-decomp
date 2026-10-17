/* Overlay 15: the data of scenes 0x0b, 0x0c, 0x0d and 0x0e (data_020e5688 names each scene's
 * overlay), rooms, so loaded with overlay 4 (data_020e5538). Its one function is its static
 * initialiser, run when the overlay is loaded, which fills in the count of the step of the
 * scene's setup (scene_setup.h) that makes overlay 4's shared objects, copied from overlay 4's
 * constant (the compiler cannot fold another overlay's constant); the scene's exits
 * (scene_exit.h), each made by SceneExit_Init and registered for destruction. */
#include "clean.h"
#include "autoload_2/vector.h"
#include "main/scene_exit.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). */
extern const u8 data_ov004_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov015_02260150;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov015InitRecord {
    struct Ov015InitRecord *next;
    void *destruct;
    void *object;
} Ov015InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern SceneExit data_ov015_022601e4, data_ov015_02260200, data_ov015_0226021c;
extern Ov015InitRecord data_ov015_022601d8, data_ov015_022601c0, data_ov015_022601cc;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov015_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov015InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov015_02260020: the scene's tables filled in, in this order. */
void Ov015Init_SceneTables(void)
{
    data_ov015_02260150.count = data_ov004_02256914;
    ov015_init_exit(&data_ov015_022601e4, SCENE_EXIT_TO_BUILDING_500B, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 4,
                    &data_ov015_022601d8);
    ov015_init_exit(&data_ov015_02260200, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov015_022601c0);
    ov015_init_exit(&data_ov015_0226021c, 0x2f, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0, &data_ov015_022601cc);
}
CLEAN_AS(__sinit_ov015_02260020, Ov015Init_SceneTables)
