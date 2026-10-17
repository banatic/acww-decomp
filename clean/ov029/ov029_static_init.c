/* Overlay 29: the data of scenes 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 and 0x19
 * (data_020e5688 names each scene's overlay), rooms, so loaded with overlay 4 (data_020e5538).
 * Its one function is its static initialiser, run when the overlay is loaded, which fills in the
 * count of the step of the scene's setup (scene_setup.h) that makes overlay 4's shared objects,
 * copied from overlay 4's constant (the compiler cannot fold another overlay's constant); the
 * scene's exits (scene_exit.h), each made by SceneExit_Init and registered for destruction. */
#include "clean.h"
#include "autoload_2/vector.h"
#include "main/scene_exit.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). */
extern const u8 data_ov004_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov029_022601f8;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov029InitRecord {
    struct Ov029InitRecord *next;
    void *destruct;
    void *object;
} Ov029InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern SceneExit data_ov029_02260294, data_ov029_022602b0, data_ov029_022602cc, data_ov029_022602e8, data_ov029_02260304,
    data_ov029_02260320, data_ov029_0226033c;
extern Ov029InitRecord data_ov029_02260258, data_ov029_02260270, data_ov029_0226027c, data_ov029_02260240, data_ov029_0226024c,
    data_ov029_02260264, data_ov029_02260288;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov029_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov029InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov029_02260020: the scene's tables filled in, in this order. */
void Ov029Init_SceneTables(void)
{
    data_ov029_022601f8.count = data_ov004_02256914;
    ov029_init_exit(&data_ov029_02260294, SCENE_EXIT_TO_MARKED_PLACE, &(Vec3){0, 0, 0}, 0, 0, 2, 2, 0, 4,
                    &data_ov029_02260258);
    ov029_init_exit(&data_ov029_022602b0, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0, 0, 2, 2, 0, 0, &data_ov029_02260270);
    ov029_init_exit(&data_ov029_022602cc, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov029_0226027c);
    ov029_init_exit(&data_ov029_022602e8, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov029_02260240);
    ov029_init_exit(&data_ov029_02260304, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov029_0226024c);
    ov029_init_exit(&data_ov029_02260320, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov029_02260264);
    ov029_init_exit(&data_ov029_0226033c, SCENE_EXIT_TO_SAVED_PLACE, &(Vec3){0, 0, 0}, 0x800000, 0, 2, 2, 0, 0,
                    &data_ov029_02260288);
}
CLEAN_AS(__sinit_ov029_02260020, Ov029Init_SceneTables)
