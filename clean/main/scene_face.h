/* A scene object's face (class 0x020d8c64, obj_020d8c64.h: its member at 0x2ac), as the field
 * actor's face (field_actor_anim.c): two animations of the face's texture, bound to the
 * object's model, picked by the body's animation (func_0205cf28 for the first, func_0205cf1c
 * for the second; SCENE_FACE_ANIM_NONE when the body's has none).
 *
 * The first animation rests at its first frame while it is number 0 until the timer at the
 * face's start lets it go on. The second follows the object's talking (its member at 0x418,
 * SceneTalkState): while the object talks in style 0 or 1 it plays that style's talking
 * animation (0x137 or 0x138, data_020c8170) in cycles, each over frames 0 to 5 or from frame 5
 * to the end, picked at random (SceneFace_PickTalkVariant); the animation it played before is
 * kept and comes back once the talking stops. */
#ifndef CLEAN_MAIN_SCENE_FACE_H
#define CLEAN_MAIN_SCENE_FACE_H

#include "frame_ctrl.h"
#include "types.h"

/* An animation number of none, and the defaults that replace it. */
#define SCENE_FACE_ANIM_NONE 0x16f
#define SCENE_FACE_ANIM_A_DEFAULT 0
#define SCENE_FACE_ANIM_B_DEFAULT 0xba

/* The talking animations of styles 0 and 1. */
#define SCENE_FACE_TALK_0 0x137
#define SCENE_FACE_TALK_1 0x138

/* An animation of the face (0x2c bytes): its frame control first. */
typedef struct SceneFaceAnim {
    FrameCtrl ctrl;
    u8 unk_18[0x14];
} SceneFaceAnim;

typedef struct SceneFace {
    u8 timer[4];           /* 0x00: lets animation 0 go on (func_020645e0) */
    u8 part_link[8];       /* 0x04: the part whose heap the animations use */
    u8 texture_link[8];    /* 0x0c: the block slot the face's texture is read into */
    u8 set_link[8];        /* 0x14: the set of the face's animations */
    SceneFaceAnim anim_a;  /* 0x1c */
    SceneFaceAnim anim_b;  /* 0x48 */
    s32 anim_a_number;     /* 0x74 */
    s32 anim_b_number;     /* 0x78 */
    s32 anim_b_after_talk; /* 0x7c: the second animation to play once the talking stops */
    s32 talk_variant;      /* 0x80: 0 plays frames 0 to 5, 1 from frame 5 to the end */
    u8 ready;              /* 0x84: set once the face is loaded */
} SceneFace;

void SceneFace_Step(SceneFace *self, u8 *object);
void SceneFace_Release(SceneFace *self);
void SceneFace_ResetTimer(SceneFace *self);
void SceneFace_DisableNamed(SceneFace *self);
void SceneFace_MapNamed(SceneFace *self, void *target);
int SceneFace_MapEntry(SceneFace *self, void *anim, const void *name, void *target);
void SceneFace_MatchBody(SceneFace *self, int animation, int flags, int style);
void SceneFace_Play(SceneFace *self, int number_a, int number_b, int flags, int style);
void SceneFace_EndTalk(SceneFace *self);
void SceneFace_StartTalk(SceneFace *self, int style);
void SceneFace_PlayB(SceneFace *self, int number, int flags);
int SceneFace_TalkCycleDone(SceneFace *self);
void SceneFace_StartTalkCycle(SceneFace *self);
int SceneFace_TalkCycleEnded(SceneFace *self, int variant, int frame, int end);
int SceneFace_TalkStartFrame(SceneFace *self, int variant);
void SceneFace_PickTalkCycle(SceneFace *self);
int SceneFace_IsTalkAnim(SceneFace *self, int number);
int SceneFace_Load(SceneFace *self, void *model);
int SceneFace_AnimB(SceneFace *self);
int SceneFace_IsReady(SceneFace *self);
SceneFace *SceneFace_Destruct(SceneFace *self);
SceneFace *SceneFace_Construct(SceneFace *self);
int SceneFace_PickTalkVariant(void);

/* The object's talking state (its member at 0x418): byte 0 is 1 while it talks, word 4 the
 * style. */
int SceneTalkState_Style(int *talk);

#endif
