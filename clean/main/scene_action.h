/* The actions a scene object (class 0x020d8c64, obj_020d8c64.h) is asked to play: the member at
 * 0x618 of the object. One request waits at a time (`pending`, made by SceneAction_Request);
 * each frame (func_0201b910 runs SceneAction_Run) a request waiting while no action runs
 * starts, and the running action takes a step of its phase. The five actions are a table of
 * C++ pointers to member functions at data_021c17c4 (a start and a run for each, filled at
 * start-up); each run dispatches on `phase` through a table of its own.
 *
 * The actions work on the object's motion (its member at 0x564: func_02019d0c sets a kind of
 * motion with a priority and arguments, func_02019e00 gives the kind, func_02019de8 whether it
 * is done) and on the scene the object talks in (the object's word at 0x634; a scene of class
 * 0x020d8bd4, scene_talk.h, whose word at 0x50 is the other speaker and whose word at 0x40 the
 * talk's state):
 * - 0: the motion of kind 3 with `motion_b` and `motion_c` (it turns the object to the angle
 *   `motion_c`); once there, the talk opens (SceneAction_OpenTalk) and the action waits for its
 *   end;
 * - 1: (the motion of kind 0 first, with `reset_motion`) the talk opens and the action waits
 *   for its end;
 * - 2: the motion of kind 3; once done, kind 0 and the motion's byte 0x19 is 1 until
 *   `released`, then 2;
 * - 3: (the motion of kind 0 first, with `reset_motion`) the motion's byte 0x19 is 1 until
 *   `released`, then 2;
 * - 4: the motion of kind 7 (func_02019cc8) until it is done, then kind 0.
 * Actions 0 and 1 aim the camera at the object (and the other speaker) unless `keep_camera`,
 * and turn it back at their end. While an action runs, bit 2 of the object's flags at 0x4e8
 * is set. */
#ifndef CLEAN_MAIN_SCENE_ACTION_H
#define CLEAN_MAIN_SCENE_ACTION_H

#include "types.h"

#define SCENE_ACTION_COUNT 5
#define SCENE_ACTION_NONE 5

typedef struct SceneAction {
    s32 motion_arg;  /* 0x00: action 4's word for the motion (at 0x40 in it) */
    u16 motion_b;    /* 0x04 */
    s16 motion_c;    /* 0x06 */
    u8 action;       /* 0x08: the action running, SCENE_ACTION_NONE for none */
    u8 pending;      /* 0x09: the action requested, SCENE_ACTION_NONE for none */
    u8 phase;        /* 0x0a */
    u8 set_flag;     /* 0x0b: 1 once an action found bit 2 of the object's flags clear */
    u8 keep_camera;  /* 0x0c */
    u8 reset_motion; /* 0x0d */
    u8 released;     /* 0x0e: set by others; what actions 2 and 3 wait for */
    u8 unk_0f;
} SceneAction;

void SceneAction_RunPhase4(SceneAction *self, void *object);
void SceneAction_WaitMotion7(SceneAction *self, void *object);
void SceneAction_Start4(SceneAction *self, void *object);
void SceneAction_RunPhase3(SceneAction *self, void *object);
void SceneAction_Start3(SceneAction *self, void *object);
void SceneAction_RunPhase1(SceneAction *self, void *object);
void SceneAction_WaitSpeakers1(SceneAction *self, void *object);
void SceneAction_WaitTalk1(SceneAction *self, void *object);
void SceneAction_OpenTalk1(SceneAction *self, void *object);
void SceneAction_Start1(SceneAction *self, void *object);
void SceneAction_RunPhase2(SceneAction *self, void *object);
void SceneAction_WaitRelease(SceneAction *self, void *object);
void SceneAction_WaitMotion3(SceneAction *self, void *object);
void SceneAction_Start2(SceneAction *self, void *object);
void SceneAction_RunPhase0(SceneAction *self, void *object);
void SceneAction_WaitSpeakers0(SceneAction *self, void *object);
void SceneAction_WaitTalk0(SceneAction *self, void *object);
void SceneAction_WaitTurn0(SceneAction *self, void *object);
void SceneAction_Start0(SceneAction *self, void *object);
void SceneAction_Finish(SceneAction *self, void *object);
void SceneAction_Run(SceneAction *self, void *object);
void SceneAction_StartPending(SceneAction *self, void *object);
void SceneAction_OpenTalk(SceneAction *self, void *object);
int SceneAction_Request(SceneAction *self, u8 action, s32 motion_arg, u16 motion_b, s16 motion_c, u8 reset_motion,
                        u8 keep_camera);
int SceneAction_RequestMotion7(SceneAction *self, int motion_arg, int motion_b, int motion_c, u8 keep_camera);
int SceneAction_RequestTalk(SceneAction *self, int reset_motion, int keep_camera);
int SceneAction_RequestTurnAndTalk(SceneAction *self, int motion_b, int angle, int keep_camera);
void SceneAction_ShowTalking(void *unused, void *object);
int SceneAction_IsBusy(const SceneAction *self);
void SceneAction_Init(SceneAction *self);
void SceneAction_Destruct(SceneAction *self);
void SceneAction_Construct(SceneAction *self);

#endif
