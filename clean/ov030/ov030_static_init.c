/* Overlay 30: the data of scene 0x30 (data_020e5688 names each scene's overlay), a room, so
 * loaded with overlay 4 (data_020e5538). Its one function is its static initialiser, run when
 * the overlay is loaded, which fills in the count of the step of the scene's setup
 * (scene_setup.h) that makes overlay 4's shared objects, copied from overlay 4's constant (the
 * compiler cannot fold another overlay's constant). */
#include "clean.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). */
extern const u8 data_ov004_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov030_0226006c;

/* __sinit_ov030_02260020: the count filled in. */
void Ov030Init_SceneTables(void)
{
    data_ov030_0226006c.count = data_ov004_02256914;
}
CLEAN_AS(__sinit_ov030_02260020, Ov030Init_SceneTables)
