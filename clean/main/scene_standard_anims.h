/* A scene object's three standard animation numbers (class 0x020d8c64, obj_020d8c64.h: its
 * member at 0x2a0): the animations 0, 1 and 2 a motion asks for stand for these
 * (SpeakerAnim_Resolve, speaker_anim.h). A new set is 0, 1 and 2; overlays set their own. */
#ifndef CLEAN_MAIN_SCENE_STANDARD_ANIMS_H
#define CLEAN_MAIN_SCENE_STANDARD_ANIMS_H

#include "types.h"

#define SCENE_STANDARD_ANIMS 3

typedef struct SceneStandardAnims {
    s32 number[SCENE_STANDARD_ANIMS];
} SceneStandardAnims;

int SceneStandardAnims_Third(SceneStandardAnims *self);
int SceneStandardAnims_Second(SceneStandardAnims *self);
int SceneStandardAnims_First(SceneStandardAnims *self);
void SceneStandardAnims_SetThird(SceneStandardAnims *self, int number);
void SceneStandardAnims_SetSecond(SceneStandardAnims *self, int number);
void SceneStandardAnims_SetFirst(SceneStandardAnims *self, int number);
void SceneStandardAnims_Destruct(SceneStandardAnims *self);
void SceneStandardAnims_Init(SceneStandardAnims *self);

#endif
