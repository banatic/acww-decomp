/* The scene base class (vtable 0x020d8bd4, include/cpp/main/Obj_020d8bd4.h): a message
 * receiver (Base_02066994) whose talk is the receiver's word at 0x40, with two speakers (scene
 * objects of class 0x020d8c64, obj_020d8c64.h) at 0x4c and 0x50, the commands of
 * scene_command.h at 0x64 and the talk's turns of scene_talk.h.
 *
 * Most of its own vtable slots act on the scene's `focus` (byte 0x54), which one of the three
 * people the scene's next turn or look applies to: the first speaker (0), the second (1) or the
 * player (2):
 * - 0x3c, 0x40, 0x44: set the focus to the player, the first or the second speaker;
 * - 0x48 and 0x4c: the focus speaker looks at the player, or turns to face the player;
 * - 0x50 and 0x58: the focus looks at the first or the second speaker;
 * - 0x54 and 0x5c: the focus turns to face the first or the second speaker;
 * - 0x38: the focus speaker takes the talking motion in a style (SceneBase_SetSpeakerTalkStyle).
 *
 * A speaker "looks" through the request at 0x3b0 of the object (func_0201ad18) and "turns" with
 * the motion of kind 3 at 0x564 (scene_action.h). The player looks by func_02095518 and turns by
 * func_02095a8c, on the field actor numbered by SceneBase_PlayerActorId.
 *
 * Also here: the scene's helpers that put a value as text into one of the talk's slots
 * (func_02068404 and func_020683b4). */
#ifndef CLEAN_MAIN_SCENE_BASE_H
#define CLEAN_MAIN_SCENE_BASE_H

#include "types.h"

#define SCENE_BASE_FOCUS_FIRST 0
#define SCENE_BASE_FOCUS_SECOND 1
#define SCENE_BASE_FOCUS_PLAYER 2

typedef struct SceneBase {
    const u8 *vtable;
    u8 receiver[0x3c];
    u8 *talk; /* 0x40: the receiver's link */
    u8 unk_44[4];
    s32 motion_arg;  /* 0x48: SceneCommandScene's motion_d */
    u8 *speakers[2]; /* 0x4c */
    u8 focus;        /* 0x54: SCENE_BASE_FOCUS_* */
    u8 speaking;     /* 0x55: the speaker whose turn it is */
    u8 unk_56[6];
    s32 talk_style; /* 0x5c: the style of the talking motion last set through this scene */
    u8 holding;     /* 0x60: set while command 3 or 4 holds the first speaker's motion */
    u8 unk_61[3];
    s32 command; /* 0x64: SCENE_COMMAND_* */
    u8 params[0x16];
    u16 item; /* 0x7e: SceneCommandParams' item */
} SceneBase;

void SceneBase_FaceSecond(SceneBase *scene);
void SceneBase_LookAtSecond(SceneBase *scene);
void SceneBase_FaceFirst(SceneBase *scene);
void SceneBase_LookAtFirst(SceneBase *scene);
void SceneBase_PlayerFaces(SceneBase *scene, u8 *speaker);
int SceneBase_PlayerLooksAt(SceneBase *scene, u8 *speaker);
void SceneBase_FacePlayer(SceneBase *scene);
void SceneBase_LookAtPlayer(SceneBase *scene);
int SceneBase_PlayerActorId(void);
u8 SceneBase_Speaking(const SceneBase *scene);
int SceneBase_SpeakingSpeaker(SceneBase *scene);
unsigned int SceneBase_SpeakerOf(SceneBase *scene, int number);
int SceneBase_FocusSpeaker(SceneBase *scene);
int SceneBase_Speaker(SceneBase *scene, int number);
void SceneBase_FocusSecond(SceneBase *scene);
void SceneBase_FocusFirst(SceneBase *scene);
void SceneBase_FocusPlayer(SceneBase *scene);
void SceneBase_Nothing34(void);
int SceneBase_PutBytes(SceneBase *scene, int slot, const void *bytes, int size, const void *unused);
void SceneBase_PutItemName(SceneBase *scene, int item, int slot, int kind);
void SceneBase_PutNpcName(SceneBase *scene, const void *npc, int slot);
void SceneBase_PutNameAt10(SceneBase *scene, void *from, int slot);
void *SceneBase_PutNameAt2(SceneBase *scene, unsigned int from, unsigned int slot);
void SceneBase_PutNumber(SceneBase *scene, int value, int slot);
void SceneBase_PutNumberAlt(SceneBase *scene, void *value, int slot);
void SceneBase_PutDecimal(SceneBase *scene, int value, int slot, int format, int unused);
void SceneBase_PutCount(SceneBase *scene, int value, int slot, int format, u8 with_unit, int a, int b);
void SceneBase_PutValue(SceneBase *scene, int value, int slot, int format, int a, int b);
int SceneBase_IsHolding(const SceneBase *scene);
void SceneBase_ClearHolding(SceneBase *scene);
void SceneBase_SetHolding(SceneBase *scene);
int SceneBase_FocusTalkStyle(SceneBase *scene, int style);
int SceneBase_SetSpeakerTalkStyle(SceneBase *scene, int style, int speaker);
int SceneBase_SpeakingKind(SceneBase *scene);
int SceneBase_TalkChoices(SceneBase *scene);
void SceneBase_SetFirstSpeaker(SceneBase *scene, u8 *speaker);
int SceneBase_SecondSpeaker(SceneBase *scene);
void SceneBase_SetSecondSpeaker(SceneBase *scene, u8 *speaker);
int SceneBase_MotionArg(SceneBase *scene);
void SceneBase_SetMotionArg(SceneBase *scene, int value);
void SceneBase_Nothing7c(void *scene);
void SceneBase_Update(SceneBase *scene);
void SceneBase_Nothing80(void *scene);
void SceneBase_Reset(SceneBase *scene);
void *SceneBase_DestructBody(void *scene);
void *SceneBase_DestructDelete(SceneBase *scene);
void *SceneBase_Destruct(void *scene);
SceneBase *SceneBase_Construct(SceneBase *scene);

#endif
