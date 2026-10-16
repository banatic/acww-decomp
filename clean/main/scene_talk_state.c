/* A scene object's talking state (scene_talk_state.h). */
#include "scene_talk_state.h"

#include "clean.h"

static_assert(offsetof(SceneTalkState, style) == 0x04, "SceneTalkState layout");

/* func_0201a7b8: the talking style. */
void SceneTalkState_SetStyle(SceneTalkState *self, int style)
{
    self->style = style;
}
CLEAN_AS(func_0201a7b8, SceneTalkState_SetStyle)

/* func_0201a7bc: whether the object talks (the byte is exactly 1). */
int SceneTalkState_IsTalking(const SceneTalkState *self)
{
    return self->talking == 1;
}
CLEAN_AS(func_0201a7bc, SceneTalkState_IsTalking)

/* func_0201a7cc: the object stops talking. */
void SceneTalkState_Stop(SceneTalkState *self)
{
    self->talking = 0;
}
CLEAN_AS(func_0201a7cc, SceneTalkState_Stop)

/* func_0201a7d4: the object starts talking. */
void SceneTalkState_Start(SceneTalkState *self)
{
    self->talking = 1;
}
CLEAN_AS(func_0201a7d4, SceneTalkState_Start)

/* func_0201a7dc: not talking, in the style without a talking animation (2). */
void SceneTalkState_Reset(SceneTalkState *self)
{
    self->talking = 0;
    self->style = SCENE_TALK_STATE_STYLE_NONE;
}
CLEAN_AS(func_0201a7dc, SceneTalkState_Reset)

/* func_0201a7e8: the destructor, which has nothing to do. */
void SceneTalkState_Destruct(SceneTalkState *self)
{
    (void) self;
}
CLEAN_AS(func_0201a7e8, SceneTalkState_Destruct)

/* func_0201a7ec: the constructor (SceneTalkState_Reset). Returns the state. */
SceneTalkState *SceneTalkState_Construct(SceneTalkState *self)
{
    SceneTalkState_Reset(self);
    return self;
}
CLEAN_AS(func_0201a7ec, SceneTalkState_Construct)
