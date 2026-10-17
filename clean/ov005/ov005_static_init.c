/* Overlay 5: the data of scenes 0x00 and 0x31 (data_020e5688 names each scene's overlay), scenes
 * outdoors, so loaded with overlay 3 (data_020e5538). Its one function is its static
 * initialiser, run when the overlay is loaded, which fills in the count of the step of the
 * scene's setup (scene_setup.h) that makes overlay 3's shared objects, copied from overlay 3's
 * constant (the compiler cannot fold another overlay's constant). */
#include "clean.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 3's shared objects (their table at 0x02239ae4). */
extern const u8 data_ov003_02239ad8;
/* The scene's setup steps; a step makes the objects at 0x02239ae4 (its count 0 in the ROM). */
extern SceneSetupStep data_ov005_02262e0c;

/* __sinit_ov005_02262da0: the count filled in. */
void Ov005Init_SceneTables(void)
{
    data_ov005_02262e0c.count = data_ov003_02239ad8;
}
CLEAN_AS(__sinit_ov005_02262da0, Ov005Init_SceneTables)
