/* Overlay 6: the data of scene 0x2c (data_020e5688 names each scene's overlay), a scene
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
extern SceneSetupStep data_ov006_02262df4;

/* __sinit_ov006_02262da0: the count filled in. */
void Ov006Init_SceneTables(void)
{
    data_ov006_02262df4.count = data_ov003_02239ad8;
}
CLEAN_AS(__sinit_ov006_02262da0, Ov006Init_SceneTables)
