/* The commands a scene (class 0x020d8bd4, include/cpp/main/Obj_020d8bd4.h) carries out one at a
 * time: the number at 0x64 picks one of twelve sub-machines (SceneCommand_Run, through a table
 * of C++ pointers to member functions), each stepping on the scene's byte 0xac. A command is
 * asked for by one of the SceneCommand_Request* functions (or SceneTalk_Request), which fill
 * the command's values in the block at 0x68 (SceneCommandParams); the scene then runs it each
 * frame until its step says it is finished, when the command goes back to "none" and the
 * scene's vtable slot 0x84 is told which one ended.
 *
 * The commands work on the scene's talk (its word at 0x40, as in scene_talk.h: word 4 is 5 once
 * the line is shown to its end, word 8 is set to 1 to show the next line, word 0x14 is set by
 * the commands; func_02068440 sets its byte 0x1e93 while a command holds the talk and
 * func_02068434 clears it) and on the motion of its first speaker (a scene object of class
 * 0x020d8c64 at 0x4c; its motion at 0x564, as in scene_action.h: func_02019d0c sets a kind of
 * motion, func_02019e00 gives the kind, func_02019de8 whether it is done):
 * - 0: opens a screen of overlay group 9 or 12 (group_params.h), by `screen`, then shows the
 *   talk's next line unless `stay_on_line`;
 * - 1: shows the talk's next line once the current one is shown;
 * - 2: sets the talk's word 0x14 to `talk_mode` and waits for the line to be shown;
 * - 3 and 4: the speaker's motion of kind 13 or 14 with an item (func_02019bd0, func_02019b80);
 * - 5 to 9: the speaker's motion of kind 15 to 19;
 * - 10: the speaker's sound (its vtable slot 0x84), played through the sound set, waiting for
 *   it to start and end;
 * - 11: the talk's turns between the two speakers (scene_talk.h). */
#ifndef CLEAN_MAIN_SCENE_COMMAND_H
#define CLEAN_MAIN_SCENE_COMMAND_H

#include "pockets.h"
#include "types.h"

#define SCENE_COMMAND_SCREEN 0
#define SCENE_COMMAND_NEXT_LINE 1
#define SCENE_COMMAND_TALK_MODE 2
#define SCENE_COMMAND_MOTION_13 3
#define SCENE_COMMAND_MOTION_14 4
#define SCENE_COMMAND_MOTION_15 5
#define SCENE_COMMAND_MOTION_16 6
#define SCENE_COMMAND_MOTION_17 7
#define SCENE_COMMAND_MOTION_18 8
#define SCENE_COMMAND_MOTION_19 9
#define SCENE_COMMAND_SOUND 10
#define SCENE_COMMAND_TALK_TURNS 11
#define SCENE_COMMAND_COUNT 12
#define SCENE_COMMAND_NONE 12

/* The screens command 0 opens (`screen`). */
#define SCENE_COMMAND_SCREEN_POCKETS 0   /* GroupParams_OpenWithMask */
#define SCENE_COMMAND_SCREEN_MODE_25 1   /* func_0206f99c */
#define SCENE_COMMAND_SCREEN_MODE 2      /* GroupParams_Open */
#define SCENE_COMMAND_SCREEN_MODE_ARG 3  /* GroupParams_OpenWithArg */
#define SCENE_COMMAND_SCREEN_MODE_3D 4   /* func_0206f7dc */
#define SCENE_COMMAND_SCREEN_GROUP_12 5  /* GroupParams_OpenGroup12 */
#define SCENE_COMMAND_SCREEN_MODE_TEXT 6 /* func_0206f640 */
#define SCENE_COMMAND_SCREEN_NONE 7      /* only the next line */

/* The values of the commands, at 0x68 of the scene (offsets in the scene in brackets). */
typedef struct SceneCommandParams {
    u32 screen;                       /* 0x00 (0x68) */
    s32 screen_a;                     /* 0x04 (0x6c): func_0206f7dc's arguments */
    s32 screen_b;                     /* 0x08 (0x70) */
    u32 group_12_pointer;             /* 0x0c (0x74): the address group 12 is opened with */
    PocketPredicate pocket_predicate; /* 0x10 (0x78): picks the pockets, or null */
    u16 pocket_mask;                  /* 0x14 (0x7c): the pockets without a predicate */
    u16 item;                         /* 0x16 (0x7e): an item code, 0xfff1 for none */
    u32 motion_a;                     /* 0x18 (0x80) */
    u8 pocket_arg;                    /* 0x1c (0x84) */
    u8 unk_1d;
    u8 mode;         /* 0x1e (0x86): the mode group 9 is opened in */
    u8 mode_arg;     /* 0x1f (0x87) */
    u8 stay_on_line; /* 0x20 (0x88): 1 to leave the talk on its line after the screen */
    u8 unk_21[3];
    u32 sound_values[2]; /* 0x24 (0x8c): sixteen 4-bit values for the sound (func_0206ea5c) */
    u8 motion_b;         /* 0x2c (0x94) */
    u8 unk_2d[3];
    u32 motion_c;            /* 0x30 (0x98) */
    u32 text;                /* 0x34 (0x9c): the address of a text for screen 6 */
    u32 text_units;          /* 0x38 (0xa0): its length in 16-bit units */
    u8 start_with_camera;    /* 0x3c (0xa4): for the talk turns (scene_talk.h) */
    u8 sound_without_values; /* 0x3d (0xa5) */
    u8 unk_3e[2];
    s32 talk_mode; /* 0x40 (0xa8): what command 2 writes to the talk's word 0x14 */
} SceneCommandParams;

typedef struct SceneCommandScene {
    const u8 *vtable;
    u8 unk_04[0x3c];
    s32 *talk; /* 0x40 */
    u8 unk_44[4];
    s32 motion_d;    /* 0x48: the last argument of func_02019b80 and func_02019bd0 */
    u8 *speakers[2]; /* 0x4c */
    u8 unk_54;
    u8 speaking; /* 0x55 */
    u8 unk_56[0xa];
    u8 unk_60; /* func_0201600c sets it, func_02016004 clears it */
    u8 unk_61[3];
    s32 command;               /* 0x64: SCENE_COMMAND_* */
    SceneCommandParams params; /* 0x68 */
    u8 state;                  /* 0xac: the step of the command */
    u8 busy;                   /* 0xad: a command was asked for and has not ended */
} SceneCommandScene;

int SceneCommand_RunSound(SceneCommandScene *scene);
int SceneCommand_SoundEnd(SceneCommandScene *scene);
int SceneCommand_SoundWaitStart(SceneCommandScene *scene);
int SceneCommand_SoundStart(SceneCommandScene *scene);
int SceneCommand_RequestSound(SceneCommandScene *scene);
int SceneCommand_RequestSoundWith(SceneCommandScene *scene, const u32 *values);
int SceneCommand_RunMotion19(SceneCommandScene *scene);
int SceneCommand_WaitMotion19(SceneCommandScene *scene);
int SceneCommand_StartMotion19(SceneCommandScene *scene);
int SceneCommand_RequestMotion19(SceneCommandScene *scene);
int SceneCommand_RunMotion18(SceneCommandScene *scene);
int SceneCommand_WaitMotion18(SceneCommandScene *scene);
int SceneCommand_StartMotion18(SceneCommandScene *scene);
int SceneCommand_RequestMotion18(SceneCommandScene *scene);
int SceneCommand_RunMotion17(SceneCommandScene *scene);
int SceneCommand_WaitMotion17(SceneCommandScene *scene);
int SceneCommand_StartMotion17(SceneCommandScene *scene);
int SceneCommand_RequestMotion17(SceneCommandScene *scene);
int SceneCommand_RunMotion16(SceneCommandScene *scene);
int SceneCommand_WaitMotion16(SceneCommandScene *scene);
int SceneCommand_StartMotion16(SceneCommandScene *scene);
int SceneCommand_RequestMotion16(SceneCommandScene *scene);
int SceneCommand_RunMotion15(SceneCommandScene *scene);
int SceneCommand_WaitMotion15(SceneCommandScene *scene);
int SceneCommand_StartMotion15(SceneCommandScene *scene);
int SceneCommand_RequestMotion15(SceneCommandScene *scene);
int SceneCommand_RunMotion14(SceneCommandScene *scene);
int SceneCommand_WaitMotion14(SceneCommandScene *scene);
int SceneCommand_StartMotion14(SceneCommandScene *scene);
int SceneCommand_RequestMotion14(SceneCommandScene *scene, const u16 *item, u32 a, u8 b, u32 c);
int SceneCommand_RunMotion13(SceneCommandScene *scene);
int SceneCommand_WaitMotion13(SceneCommandScene *scene);
int SceneCommand_StartMotion13(SceneCommandScene *scene);
int SceneCommand_RequestMotion13(SceneCommandScene *scene, const u16 *item, u32 a, u8 b, u32 c);
int SceneCommand_RunTalkMode(SceneCommandScene *scene);
int SceneCommand_LineShown(SceneCommandScene *scene);
int SceneCommand_SetTalkMode(SceneCommandScene *scene);
int SceneCommand_RequestTalkMode(SceneCommandScene *scene, s32 mode);
void *SceneCommand_NextLine(SceneCommandScene *scene);
int SceneCommand_RequestNextLine(SceneCommandScene *scene);
int SceneCommand_RunScreen(SceneCommandScene *scene);
int SceneCommand_WaitScreen(SceneCommandScene *scene);
int SceneCommand_OpenScreen(SceneCommandScene *scene);
int SceneCommand_BeginScreen(SceneCommandScene *scene);
void SceneCommand_SetScreenText(SceneCommandScene *scene, u8 mode, u32 text, u32 units, u8 stay_on_line);
void SceneCommand_SetScreenPointer(SceneCommandScene *scene, int pointer, int stay_on_line);
void SceneCommand_SetScreenArgs(SceneCommandScene *scene, s32 a, s32 b, int stay_on_line);
void SceneCommand_SetScreenModeArg(SceneCommandScene *scene, u8 mode, u8 arg, u8 stay_on_line);
void SceneCommand_SetScreenMode(SceneCommandScene *scene, char mode, char stay_on_line);
void SceneCommand_SetPocketPredicate(SceneCommandScene *scene, PocketPredicate predicate, u8 arg, u8 stay_on_line);
void SceneCommand_SetPocketMask(SceneCommandScene *scene, u16 mask, u8 arg, u8 stay_on_line);
int SceneCommand_RequestScreen(SceneCommandScene *scene, int screen);
void SceneCommand_Ended(SceneCommandScene *scene, int command);
void SceneCommand_Run(SceneCommandScene *scene);
int SceneCommand_IsBusy(const SceneCommandScene *scene);
int SceneCommand_Request(SceneCommandScene *scene, u32 command);
void SceneCommand_ResetParams(int unused, SceneCommandParams *params);
void SceneCommand_Init(SceneCommandScene *scene);

#endif
