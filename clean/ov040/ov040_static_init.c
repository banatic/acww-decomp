/* Overlay 40: the data of scene 0x1c (data_020e5688 names each scene's overlay), a room, so
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
extern SceneSetupStep data_ov040_022600b0;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov040InitRecord {
    struct Ov040InitRecord *next;
    void *destruct;
    void *object;
} Ov040InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern SceneExit data_ov040_0226012c;
extern Ov040InitRecord data_ov040_02260120;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov040_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov040InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov040_02260020: the scene's tables filled in, in this order. */
void Ov040Init_SceneTables(void)
{
    data_ov040_022600b0.count = data_ov004_02256914;
    ov040_init_exit(&data_ov040_0226012c, SCENE_EXIT_TO_MARKED_PLACE, &(Vec3){0, 0, 0}, 0, 0, 2, 2, 0, 4,
                    &data_ov040_02260120);
}
CLEAN_AS(__sinit_ov040_02260020, Ov040Init_SceneTables)
