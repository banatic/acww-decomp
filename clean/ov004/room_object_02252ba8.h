/* A class of overlay 4's room objects (vtable 0x02252ba8, receiver part 0x02252c54, 0x864 bytes)
 * that plays a sound (the sound at 6 of the furniture's row, func_ov004_0223a730) through a
 * sound cue of the main program (main/sound.h) and moves its joints with it. The cue's step is
 * the sound library's variable 2 (taken 0-15); the object keeps it in RoomObject.unk_77C, which
 * the map's record gets, and at its cell in the scene's record (func_02052e98).
 *
 * Its state (RoomObject02252ba8.state) runs through tables of member pointers
 * (member_pointer.h):
 *
 * - OFF (0): the cue off, the sound at 4, the switch off and the step 0xff; the joints take the
 *   animation of the room's object at func_ov004_0223b22c. When the switch is asked to change,
 *   it is set off and the change is handed on (func_02051f4c);
 * - STARTING (1): the switch on and the sound at 2; the cue starts or waits for its step; each
 *   frame the countdown runs down, the cue's start (3 frames) setting it, and at 0 PLAYING;
 * - PLAYING (2): the switch on and the animations of variant 0 looped; each frame the joints
 *   take the frame the cue's update gives (20.12 fixed point).
 *
 * In STARTING and PLAYING a change asked of the switch sets it on and is handed on. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252BA8_H
#define CLEAN_OV004_ROOM_OBJECT_02252BA8_H

#include "types.h"

#include "room_object.h"
#include "room_object_methods.h" /* NodeHookState */

typedef struct RoomObject02252ba8 {
    RoomObject base;
    u8 cue[0x14]; /* a SoundCue (main/sound.h) */
    u8 cue_ready; /* the cue was set up (RoomObject02252ba8_InitCue) */
    u8 unk_859[3];
    u32 frames;    /* counts the updates since the start */
    u16 countdown; /* frames left in STARTING */
    u8 state;      /* RoomObject02252ba8State */
    u8 unk_863;
} RoomObject02252ba8;

enum RoomObject02252ba8State {
    ROOM_OBJECT_02252BA8_OFF = 0,
    ROOM_OBJECT_02252BA8_STARTING = 1,
    ROOM_OBJECT_02252BA8_PLAYING = 2,
    ROOM_OBJECT_02252BA8_STATE_COUNT = 3
};

void RoomObject02252ba8_UpdatePlaying(RoomObject02252ba8 *object);
int RoomObject02252ba8_EnterPlaying(RoomObject02252ba8 *object);
void RoomObject02252ba8_UpdateStarting(RoomObject02252ba8 *object);
int RoomObject02252ba8_EnterStarting(RoomObject02252ba8 *object);
void RoomObject02252ba8_UpdateOff(RoomObject02252ba8 *object);
int RoomObject02252ba8_EnterOff(RoomObject02252ba8 *object);
void RoomObject02252ba8_UpdateState(RoomObject02252ba8 *object);
int RoomObject02252ba8_EnterState(RoomObject02252ba8 *object, unsigned int state, int value);
u8 RoomObject02252ba8_StateIsOn(RoomObject02252ba8 *object, unsigned int state);
int RoomObject02252ba8_CueStart(RoomObject02252ba8 *object);
int RoomObject02252ba8_CueStep(RoomObject02252ba8 *object);
void RoomObject02252ba8_CueSetTarget(RoomObject02252ba8 *object, int value);
void RoomObject02252ba8_CueSetMode(RoomObject02252ba8 *object, int mode);
int RoomObject02252ba8_StopCue(RoomObject02252ba8 *object);
int RoomObject02252ba8_UpdateCue(RoomObject02252ba8 *object, const Vec3 *point);
int RoomObject02252ba8_InitCue(RoomObject02252ba8 *object, u16 sound);
void RoomObject02252ba8_NodeDescAfterHook(RoomObject02252ba8 *object, int node, NodeHookState *state);
void RoomObject02252ba8_NodeDescHook(RoomObject02252ba8 *object, int node, NodeHookState *state);
int RoomObject02252ba8_Vfunc0C(RoomObject02252ba8 *object);
int RoomObject02252ba8_UpdateUnsettled(RoomObject02252ba8 *object);
int RoomObject02252ba8_Update(RoomObject02252ba8 *object);
int RoomObject02252ba8_Start(RoomObject02252ba8 *object);
RoomObject02252ba8 *RoomObject02252ba8_Delete(RoomObject02252ba8 *object);
RoomObject02252ba8 *RoomObject02252ba8_Destroy(RoomObject02252ba8 *object);
RoomObject02252ba8 *RoomObject02252ba8_Construct(RoomObject02252ba8 *object);
void RoomObject02252ba8_Create(void);

#endif
