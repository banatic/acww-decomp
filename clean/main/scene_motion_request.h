/* Asking a scene object's motion (its member at 0x564, scene_motion.h) for a kind, starting
 * the kind, and the motion's construction.
 *
 * A request names a kind, a priority and the arguments the kind reads (`next_kind`,
 * `next_priority`, `next_args`); it is taken when its priority is at least that of the request
 * already waiting, or when that one gives way (priority 3), and SceneMotion_Update starts it on
 * the next frame. Starting a kind (SceneMotion_Start) points `entry` at the kind's row of the
 * table at data_021c1ad4 and calls the row's start with the motion and the object.
 *
 * The requests by kind (the arguments are SceneMotionPlan's, scene_motion_kinds.h):
 * - 0, stand: the word;
 * - 1 to 6 and 9 to 11 (SceneMotion_Request): the start and end points, the rate, the angle,
 *   the word and the frame; an end point of (0, 0) means the start point;
 * - 7, a gesture: the rate, the angle, the word and the gesture;
 * - 8, an act: the act's number and the word;
 * - 12, an animation: the animation, its play mode, the word and the first frame;
 * - 13 and 14: an item code, three values and a partner. */
#ifndef CLEAN_MAIN_SCENE_MOTION_REQUEST_H
#define CLEAN_MAIN_SCENE_MOTION_REQUEST_H

#include "scene_motion.h"
#include "types.h"

/* The kind a motion has before any starts, and the number of kinds in data_021c1ad4. */
#define SCENE_MOTION_KIND_NONE 0x16
#define SCENE_MOTION_KINDS 0x16

void SceneMotion_AskRelease(SceneMotion *self);
void SceneMotion_AskHold(SceneMotion *self);
int SceneMotion_RequestKind14(SceneMotion *self, int priority, u16 *item, int a, u8 b, int variant, int partner);
int SceneMotion_RequestKind13(SceneMotion *self, int priority, u16 *item, int a, u8 b, int variant, int partner);
int SceneMotion_RequestAnimation(SceneMotion *self, int priority, int animation, char mode, u16 word, u16 frame);
int SceneMotion_RequestStand(SceneMotion *self, int priority, int word);
int SceneMotion_RequestAct(SceneMotion *self, int priority, int act, int word);
int SceneMotion_RequestGesture(SceneMotion *self, int priority, int rate, int angle, int gesture, u16 word);
int SceneMotion_Request(SceneMotion *self, int kind, int priority, int from_x, int from_z, s16 rate, s16 angle, int to_x,
                        int to_z, u16 word, u16 frame);
void SceneMotion_SetNext(SceneMotion *self, int kind, int priority);
void SceneMotion_ClearRequest(SceneMotion *self);
void SceneMotion_Start(SceneMotion *self, u8 *object, int kind, int priority);
SceneMotionArgs *SceneMotion_Args(SceneMotion *self);
int SceneMotion_IsDone(SceneMotion *self);
u8 SceneMotion_ActNumber(SceneMotion *self);
int SceneMotion_Kind(SceneMotion *self);
void SceneMotion_StartNow(SceneMotion *self, u8 *object, int kind, int priority, u32 from_x, u32 from_z, s16 angle, u32 to_x,
                          u32 to_z);
void SceneMotionArgs_Copy(SceneMotionArgs *dst, SceneMotionArgs *src);
void SceneMotionArgs_Clear(SceneMotionArgs *args);
void SceneMotion_Destruct(SceneMotion *self);
SceneMotion *SceneMotion_Construct(SceneMotion *self);

#endif
