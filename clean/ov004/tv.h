/* The televisions: two classes of overlay 4's room objects (0x868 bytes) whose screen is the
 * material "tv_m" of their model. On, the screen shows the picture of func_ov004_0223b314 and
 * glows (a Glow, room_object_parts.h, at 0x848); off, it shows its own texture "tv.0" with the
 * palette "tv_pl" and the glow fades out. Their states run through tables of member pointers
 * (member_pointer.h), entered through vtable slot 0x70.
 *
 * Tv (vtable 0x02251438, receiver part 0x022514e4) has two states:
 * - TV_OFF (0): entered with the sound at 4, the switch off; when the switch is asked to change
 *   it requests TV_ON for the object at its cell (func_0205265c);
 * - TV_ON (1): entered with the sound at 2, the switch on; when the switch is asked to change
 *   it requests TV_OFF.
 * Each frame its glow is updated and `heard` cleared: func_ov004_0223bdac sets it on the TV
 * that is on and nearest to the player, whose sound is heard from where it stands.
 *
 * TvAnimated (vtable 0x02250f88, receiver part 0x02251034) is derived from Tv and plays the
 * animations of variant 0 when it is switched, with its own four states (at 0x865):
 * - TV_ANIMATED_OFF (0): the animations in mode 3 from frame 0, silently; when the switch is
 *   asked to change it requests TV_ANIMATED_TURNING_ON;
 * - TV_ANIMATED_TURNING_ON (1): the animations once from the start, with the sound at 2; at
 *   their end TV_ANIMATED_ON;
 * - TV_ANIMATED_ON (2): the animations once from their last frame, silently; when the switch is
 *   asked to change it requests TV_ANIMATED_TURNING_OFF;
 * - TV_ANIMATED_TURNING_OFF (3): the animations in mode 3 from their last frame, with the sound
 *   at 4; at their end TV_ANIMATED_OFF.
 *
 * Once their model is bound both bind the glow (on as the switch is) and enter their "on"
 * state when the switch is on and func_ov004_0223c10c says no, else "off". */
#ifndef CLEAN_OV004_TV_H
#define CLEAN_OV004_TV_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct Tv {
    RoomObject base;
    u8 state; /* TvState */
    u8 unk_845[3];
    Glow screen;       /* the material "tv_m" */
    u8 heard;          /* set by func_ov004_0223bdac, cleared by Tv_Update */
    u8 animated_state; /* TvAnimatedState, in a TvAnimated */
    u8 unk_866[2];
} Tv;

typedef struct TvAnimated {
    Tv base;
} TvAnimated;

enum TvState { TV_OFF = 0, TV_ON = 1, TV_STATE_COUNT = 2 };

enum TvAnimatedState {
    TV_ANIMATED_OFF = 0,
    TV_ANIMATED_TURNING_ON = 1,
    TV_ANIMATED_ON = 2,
    TV_ANIMATED_TURNING_OFF = 3,
    TV_ANIMATED_STATE_COUNT = 4
};

void TvAnimated_UpdateTurningOff(TvAnimated *tv);
int TvAnimated_EnterTurningOff(TvAnimated *tv);
int TvAnimated_UpdateOn(TvAnimated *tv);
int TvAnimated_EnterOn(TvAnimated *tv);
void TvAnimated_UpdateTurningOn(TvAnimated *tv);
int TvAnimated_EnterTurningOn(TvAnimated *tv);
void TvAnimated_UpdateOff(TvAnimated *tv);
int TvAnimated_EnterOff(TvAnimated *tv);
void TvAnimated_UpdateState(TvAnimated *tv);
int TvAnimated_EnterState(TvAnimated *tv, unsigned int state, int value);
u8 TvAnimated_StateIsOn(TvAnimated *tv, unsigned int state);
int TvAnimated_Vfunc0C(void);
int TvAnimated_Update(TvAnimated *tv);
int TvAnimated_Start(TvAnimated *tv);
TvAnimated *TvAnimated_Delete(TvAnimated *tv);
TvAnimated *TvAnimated_Destroy(TvAnimated *tv);
TvAnimated *TvAnimated_Construct(TvAnimated *tv);
void TvAnimated_Create(void);

int Tv_UpdateOn(Tv *tv);
int Tv_EnterOn(Tv *tv);
void Tv_UpdateOff(Tv *tv);
int Tv_EnterOff(Tv *tv);
void Tv_UpdateState(Tv *tv);
int Tv_EnterState(Tv *tv, unsigned int state, int value);
u8 Tv_StateIsOn(Tv *tv, unsigned int state);
Tv *Tv_SetHeard(Tv *tv);
int Tv_ShowScreen(Tv *tv, int on);
int Tv_Vfunc0C(void);
int Tv_Update(Tv *tv);
int Tv_Start(Tv *tv);
Tv *Tv_DestroyBase(Tv *tv);
Tv *Tv_Delete(Tv *tv);
Tv *Tv_Destroy(Tv *tv);
Tv *Tv_Construct(Tv *tv);
Tv *Tv_ConstructBase(Tv *tv);
void Tv_Create(void);
Tv *TvReceiver_Delete(void *receiver);
Tv *TvReceiver_Destroy(void *receiver);
TvAnimated *TvAnimatedReceiver_Delete(void *receiver);
TvAnimated *TvAnimatedReceiver_Destroy(void *receiver);

#endif
