/* A pair of halfwords of a scene object (scene_value_3aa.h). */
#include "scene_value_3aa.h"

#include "clean.h"

static_assert(sizeof(SceneValue3aa) == 4, "SceneValue3aa layout");

/* The bounds of the grades. */
#define SCENE_VALUE_3AA_LOW 100
#define SCENE_VALUE_3AA_HIGH 800

/* func_0201b350 */
void SceneValue3aa_SetSecond(SceneValue3aa *self, int second)
{
    self->second = (u16) second;
}
CLEAN_AS(func_0201b350, SceneValue3aa_SetSecond)

/* func_0201b354: 0 below 100, 1 below 800, else 2. */
int SceneValue3aa_Grade(SceneValue3aa *self)
{
    if (self->value < SCENE_VALUE_3AA_LOW) {
        return 0;
    }
    if (self->value < SCENE_VALUE_3AA_HIGH) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_0201b354, SceneValue3aa_Grade)

/* func_0201b370 */
void SceneValue3aa_Clear(SceneValue3aa *self)
{
    self->value = 0;
    self->second = 0;
}
CLEAN_AS(func_0201b370, SceneValue3aa_Clear)
