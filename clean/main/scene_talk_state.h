/* A scene object's talking state (class 0x020d8c64, obj_020d8c64.h: its member at 0x418): a
 * byte that is 1 while the object talks and the talking style (scene_face.h reads the style,
 * SceneTalkState_Style; speaker_anim.h plays the talking animation of styles 0 and 1). */
#ifndef CLEAN_MAIN_SCENE_TALK_STATE_H
#define CLEAN_MAIN_SCENE_TALK_STATE_H

#include "types.h"

/* The style a new state has: one without a talking animation. */
#define SCENE_TALK_STATE_STYLE_NONE 2

typedef struct SceneTalkState {
    u8 talking; /* 0x00: 1 while the object talks */
    u8 unk_01[3];
    s32 style; /* 0x04 */
} SceneTalkState;

void SceneTalkState_SetStyle(SceneTalkState *self, int style);
int SceneTalkState_IsTalking(const SceneTalkState *self);
void SceneTalkState_Stop(SceneTalkState *self);
void SceneTalkState_Start(SceneTalkState *self);
void SceneTalkState_Reset(SceneTalkState *self);
void SceneTalkState_Destruct(SceneTalkState *self);
SceneTalkState *SceneTalkState_Construct(SceneTalkState *self);

#endif
