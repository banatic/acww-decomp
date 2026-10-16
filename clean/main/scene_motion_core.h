/* How a scene object's motion (its member at 0x564, scene_motion.h) runs, and the note it keeps
 * of the motion it plays.
 *
 * The object's frame (func_0201b910) runs SceneMotion_Run before it moves and SceneMotion_After
 * once it has moved. SceneMotion_Run first starts the motion asked for (SceneMotion_Update),
 * then calls the run of the running kind; SceneMotion_After calls the kind's after-step. A kind
 * is a row of three C++ pointers to member functions in the table at data_021c1ad4 (the start,
 * the run and the after-step; `entry` points at the row), each called with the motion and the
 * object; a null pointer is not called. Once a motion is done its priority falls to 0, so any
 * motion asked for next can start.
 *
 * The motion's byte 0x19 asks for a change of its byte 0x18 on the next update: 1 sets it
 * (SceneMotion_Hold), 2 clears it (SceneMotion_Release).
 *
 * The note (the motion's bytes 0x04 to 0x13) says which kind runs, at which priority, and what
 * it was given, packed in bytes (packed_bytes.h); the object's frame reads such a note back
 * (func_0201beb0) to start the same motion with the same values:
 * - kinds 1 and 2, a path: the start and end points (5 bytes each), the mover's rate (2 bytes)
 *   and the low byte of the word;
 * - kind 3, a turn: the rate and the angle (2 bytes each) and the low byte of the word;
 * - kind 12, an animation: the low bytes of the animation, its mode, the word and the frame;
 * - kind 20: an item code (2 bytes). */
#ifndef CLEAN_MAIN_SCENE_MOTION_CORE_H
#define CLEAN_MAIN_SCENE_MOTION_CORE_H

#include "scene_motion.h"
#include "types.h"

#define SCENE_MOTION_HOLD_SET 1
#define SCENE_MOTION_HOLD_CLEAR 2

/* A motion of this priority gives way to any motion asked for. */
#define SCENE_MOTION_PRIORITY_YIELDS 3

void SceneMotion_SetDone(SceneMotion *self, u32 done);
void SceneMotion_Update(SceneMotion *self, u8 *object);
void SceneMotion_Hold(SceneMotion *self);
void SceneMotion_Release(SceneMotion *self);
void SceneMotion_Run(SceneMotion *self, u8 *object);
void SceneMotion_After(SceneMotion *self, u8 *object);

void SceneMotionNote_UnpackItem(u16 *item, const u8 *note);
void SceneMotionNote_PackItem(SceneMotion *self, u8 *note, const u16 *item);
void SceneMotionNote_UnpackAnimation(u32 *animation, u8 *mode, u16 *word, u16 *frame, const u8 *note);
void SceneMotionNote_PackAnimation(u8 *note, u8 animation, u8 mode, u8 word, u16 frame);
void SceneMotionNote_UnpackTurn(s16 *rate, s16 *angle, u16 *word, const u8 *note);
void SceneMotionNote_PackTurn(u8 *note, u16 rate, u16 angle, char word);
void SceneMotionNote_UnpackPath(u32 *from_x, u32 *from_z, u32 *to_x, u32 *to_z, s16 *rate, s16 *word, const u8 *note);
void SceneMotionNote_PackPath(u8 *note, s32 from_x, s32 from_z, s32 to_x, s32 to_z, s16 rate, u16 word);

#endif
