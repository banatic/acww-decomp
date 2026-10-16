/* A scene object's three standard animation numbers (scene_standard_anims.h). */
#include "scene_standard_anims.h"

#include "clean.h"

static_assert(sizeof(SceneStandardAnims) == 12, "SceneStandardAnims layout");

/* func_0201b378 */
int SceneStandardAnims_Third(SceneStandardAnims *self)
{
    return self->number[2];
}
CLEAN_AS(func_0201b378, SceneStandardAnims_Third)

/* func_0201b37c */
int SceneStandardAnims_Second(SceneStandardAnims *self)
{
    return self->number[1];
}
CLEAN_AS(func_0201b37c, SceneStandardAnims_Second)

/* func_0201b380 */
int SceneStandardAnims_First(SceneStandardAnims *self)
{
    return self->number[0];
}
CLEAN_AS(func_0201b380, SceneStandardAnims_First)

/* func_0201b384 */
void SceneStandardAnims_SetThird(SceneStandardAnims *self, int number)
{
    self->number[2] = number;
}
CLEAN_AS(func_0201b384, SceneStandardAnims_SetThird)

/* func_0201b388 */
void SceneStandardAnims_SetSecond(SceneStandardAnims *self, int number)
{
    self->number[1] = number;
}
CLEAN_AS(func_0201b388, SceneStandardAnims_SetSecond)

/* func_0201b38c */
void SceneStandardAnims_SetFirst(SceneStandardAnims *self, int number)
{
    self->number[0] = number;
}
CLEAN_AS(func_0201b38c, SceneStandardAnims_SetFirst)

/* func_0201b390: the destructor; nothing to do. */
void SceneStandardAnims_Destruct(SceneStandardAnims *self)
{
    (void) self;
}
CLEAN_AS(func_0201b390, SceneStandardAnims_Destruct)

/* func_0201b394: the animations 0, 1 and 2 stand for themselves. */
void SceneStandardAnims_Init(SceneStandardAnims *self)
{
    self->number[0] = 0;
    self->number[1] = 1;
    self->number[2] = 2;
}
CLEAN_AS(func_0201b394, SceneStandardAnims_Init)
