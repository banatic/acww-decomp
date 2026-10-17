/* Overlay 24: the data of scene 0x25 (data_020e5688 names each scene's overlay), a room, so
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
/* The scene's setup steps; its second step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov024_0226014c[2];

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct Ov024InitRecord {
    struct Ov024InitRecord *next;
    void *destruct;
    void *object;
} Ov024InitRecord;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a point: nothing (the game's function is handed on). */
extern void func_020012dc(void *object);
/* SceneExit_Destruct, handed on as the game's function. */
extern void func_020b649c(void *object);

extern Vec3 data_ov024_022601a4;
extern SceneExit data_ov024_022601b0, data_ov024_022601cc;
extern Ov024InitRecord data_ov024_02260180, data_ov024_0226018c, data_ov024_02260198;

/* An exit to `scene`: the player put at `at` (a copy is handed on) with `player_param` and
 * `angle`, the two bytes of the change of scene, and the door's facing and kind; then registered
 * with its destructor. */
static void ov024_init_exit(SceneExit *exit, u8 scene, const Vec3 *at, int player_param, s16 angle, u8 change_arg, u8 next_arg,
                            s16 door_angle, u8 door_kind, Ov024InitRecord *record)
{
    Vec3 copy = *at;
    SceneExit_Init(exit, scene, &copy, player_param, angle, change_arg, next_arg, door_angle, door_kind);
    __register_global_object(exit, (void *) (uintptr_t) func_020b649c, record);
}

/* __sinit_ov024_02260020: the scene's tables filled in, in this order. */
void Ov024Init_SceneTables(void)
{
    data_ov024_0226014c[1].count = data_ov004_02256914;
    data_ov024_022601a4.x = 0x10000;
    data_ov024_022601a4.y = 0x200;
    data_ov024_022601a4.z = 0x1d000;
    __register_global_object(&data_ov024_022601a4, (void *) (uintptr_t) func_020012dc, &data_ov024_02260180);
    ov024_init_exit(&data_ov024_022601b0, 0x20, &(Vec3){0x17000, 0, 0x14000}, 0x23800000, -0x4000, 2, 2, -0x4000, 3,
                    &data_ov024_0226018c);
    ov024_init_exit(&data_ov024_022601cc, 0x26, &data_ov024_022601a4, 0x23800000, -0x8000, 2, 2, -0x8000, 3,
                    &data_ov024_02260198);
}
CLEAN_AS(__sinit_ov024_02260020, Ov024Init_SceneTables)
