/* A sound of overlay 4's scenes and five bytes of main (block_020b220c.h). */
#include "block_020b220c.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "town_tune.h"

/* Where the sound plays: (1.0, 0, 30.0). */
#define BLOCK_020B220C_SOUND_X 0x10000
#define BLOCK_020B220C_SOUND_Z 0x1e000

/* The function-local static point: its guard, the point and its destruction record. */
extern u32 data_021f4b54;
extern Vec3 data_021f4b7c;
extern u8 data_021f4b64[];
extern int data_021f4b48;
extern u8 data_021f4b18;
extern u8 data_021f4b1c;

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020012dc(void *object); /* TrivialObject_Destruct */

/* func_020b220c: in scenes 1-5 and 17-24 entry 0 of the scenes' sound
 * set plays at (1.0, 0, 30.0); in scene 0x1a entry 1, in 9 entry 2, in 10 entry 3; in other
 * scenes nothing.
 * QUIRK: the first call that plays builds the point as a function-local static and registers
 * it for destruction (func_020012dc, which does nothing). */
void Block020b220c_PlaySceneSound(void)
{
    int scene = SceneQuery_Current();
    int entry;
    if (SceneKinds_IsHouseRoom((unsigned int) scene) != 0 || SceneQuery_In11(scene) != 0) {
        entry = 0;
    } else if (scene == 0x1a) {
        entry = 1;
    } else if (scene == 9) {
        entry = 2;
    } else if (scene == 10) {
        entry = 3;
    } else {
        return;
    }

    if ((data_021f4b54 & 1) == 0) {
        data_021f4b7c.x = BLOCK_020B220C_SOUND_X;
        data_021f4b7c.y = 0;
        data_021f4b7c.z = BLOCK_020B220C_SOUND_Z;
        __register_global_object(&data_021f4b7c, (void *) func_020012dc, data_021f4b64);
        data_021f4b54 |= 1;
    }
    TownTune_PlayAt(&data_021f4b7c, entry);
}
CLEAN_AS(func_020b220c, Block020b220c_PlaySceneSound)

/* func_020b22a0 */
int Block020b220c_GoneKind(void)
{
    return data_021f4b48;
}
CLEAN_AS(func_020b22a0, Block020b220c_GoneKind)

/* func_020b22ac: overlay 9's scene actor going away (SceneActor_UpdateGone) gives its kind. */
void Block020b220c_SetGoneKind(unsigned int kind)
{
    data_021f4b48 = (int) kind;
}
CLEAN_AS(func_020b22ac, Block020b220c_SetGoneKind)

/* func_020b22b8 */
u8 Block020b220c_Flag4b18(void)
{
    return data_021f4b18;
}
CLEAN_AS(func_020b22b8, Block020b220c_Flag4b18)

/* func_020b22c4 */
void Block020b220c_ClearFlag4b18(void)
{
    data_021f4b18 = 0;
}
CLEAN_AS(func_020b22c4, Block020b220c_ClearFlag4b18)

/* func_020b22d0 */
void Block020b220c_SetFlag4b18(void)
{
    data_021f4b18 = 1;
}
CLEAN_AS(func_020b22d0, Block020b220c_SetFlag4b18)

/* func_020b22dc */
u8 Block020b220c_Flag4b1c(void)
{
    return data_021f4b1c;
}
CLEAN_AS(func_020b22dc, Block020b220c_Flag4b1c)

/* func_020b22e8 */
void Block020b220c_ClearFlag4b1c(void)
{
    data_021f4b1c = 0;
}
CLEAN_AS(func_020b22e8, Block020b220c_ClearFlag4b1c)

/* func_020b22f4 */
void Block020b220c_SetFlag4b1c(void)
{
    data_021f4b1c = 1;
}
CLEAN_AS(func_020b22f4, Block020b220c_SetFlag4b1c)
