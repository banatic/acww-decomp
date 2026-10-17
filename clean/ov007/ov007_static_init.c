/* Overlay 7: the data of scene 0x2a (data_020e5688 names each scene's overlay), a scene
 * outdoors, so loaded with overlay 3 (data_020e5538). Its one function is its static
 * initialiser, run when the overlay is loaded, which fills in the count of the step of the
 * scene's setup (scene_setup.h) that makes overlay 4's shared objects, copied from overlay 4's
 * constant (the compiler cannot fold another overlay's constant; see the QUIRK below). */
#include "clean.h"
#include "main/scene_setup.h"
#include "types.h"

/* The count of overlay 4's shared objects (their table at 0x02256918). QUIRK: this scene is
 * outdoors, so overlay 3 is loaded at these addresses when the initialiser runs, and
 * 0x02256914 and 0x02256918 are in overlay 3's bss, which no code of overlay 3 names. */
extern const u8 data_ov003_02256914;
/* The scene's setup steps; a step makes the objects at 0x02256918 (its count 0 in the ROM). */
extern SceneSetupStep data_ov007_02262dc8;

/* __sinit_ov007_02262da0: the count filled in. */
void Ov007Init_SceneTables(void)
{
    data_ov007_02262dc8.count = data_ov003_02256914;
}
CLEAN_AS(__sinit_ov007_02262da0, Ov007Init_SceneTables)
