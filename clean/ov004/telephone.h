/* The telephone: a class of overlay 4's room objects (vtable 0x02252950, receiver part
 * 0x022529fc, 0x85c bytes) whose receiver part is named "obj_etc_tel". It runs two state
 * machines besides the base class's (room_object.h), each through tables of member pointers
 * (member_pointer.h):
 *
 * - its call (Telephone.state): idle until its switch is asked to change, when it takes the
 *   values of its entry among two (func_ov004_0223ca9c of data_ov004_02259784) and asks the
 *   scene for an event (func_0203e0a8); events 0 and 1 then open it (its switch turns on, one
 *   frame), it talks over its receiver while the link is open, closes (its switch turns off,
 *   one frame) and lets the scene go on (func_0203e020); event 8 makes it idle;
 * - its switch (Telephone.switch_state), entered through vtable slot 0x70: off, turning on (one
 *   frame, with sound 1), on, and turning off (one frame, with sound 1).
 *
 * Once its model is bound it shows its switch as the town's map record left it and is idle;
 * each frame it runs the call, then the switch. */
#ifndef CLEAN_OV004_TELEPHONE_H
#define CLEAN_OV004_TELEPHONE_H

#include "types.h"

#include "room_object.h"

typedef struct Telephone {
    RoomObject base;
    s32 entry_words[3]; /* at 0x2c in its entry (func_ov004_0223cb24) */
    u16 entry_value;    /* at 0x38 in its entry (func_ov004_0223cb18) */
    u16 wait;           /* frames left in TELEPHONE_OPEN and TELEPHONE_CLOSE */
    u8 switch_state;    /* TelephoneSwitch */
    u8 unk_855[3];
    s32 state; /* TelephoneState */
} Telephone;

enum TelephoneState {
    TELEPHONE_IDLE = 0,
    TELEPHONE_OPEN = 1,
    TELEPHONE_TALK = 2,     /* waits for the link to open */
    TELEPHONE_TALK_END = 3, /* waits for it to close */
    TELEPHONE_CLOSE = 4,
    TELEPHONE_STATE_COUNT = 5
};

enum TelephoneSwitch {
    TELEPHONE_SWITCH_OFF = 0,
    TELEPHONE_SWITCH_TURNING_ON = 1,
    TELEPHONE_SWITCH_ON = 2,
    TELEPHONE_SWITCH_TURNING_OFF = 3,
    TELEPHONE_SWITCH_STATE_COUNT = 4
};

void Telephone_UpdateClose(Telephone *phone);
int Telephone_EnterClose(Telephone *phone);
void Telephone_UpdateTalkEnd(Telephone *phone);
int Telephone_EnterTalkEnd(Telephone *phone);
void Telephone_UpdateTalk(Telephone *phone);
int Telephone_EnterTalk(Telephone *phone);
void Telephone_UpdateOpen(Telephone *phone);
int Telephone_EnterOpen(Telephone *phone);
void Telephone_UpdateIdle(Telephone *phone);
int Telephone_EnterIdle(Telephone *phone);
void Telephone_UpdateState(Telephone *phone);
int Telephone_EnterState(Telephone *phone, int state);
void Telephone_UpdateSwitchTurningOff(Telephone *phone);
int Telephone_EnterSwitchTurningOff(Telephone *phone);
void Telephone_UpdateSwitchOn(Telephone *phone);
int Telephone_EnterSwitchOn(Telephone *phone);
void Telephone_UpdateSwitchTurningOn(Telephone *phone);
int Telephone_EnterSwitchTurningOn(Telephone *phone);
void Telephone_UpdateSwitchOff(Telephone *phone);
int Telephone_EnterSwitchOff(Telephone *phone);
void Telephone_UpdateSwitch(Telephone *phone);
int Telephone_EnterSwitch(Telephone *phone, unsigned int state, int value);
u8 Telephone_SwitchStateIsOn(Telephone *phone, unsigned int state);
void Telephone_OnSceneEvent(Telephone *phone, int event);
int Telephone_Vfunc0C(void);
int Telephone_Update(Telephone *phone);
int Telephone_Start(Telephone *phone);
Telephone *Telephone_Delete(Telephone *phone);
Telephone *Telephone_Destroy(Telephone *phone);
Telephone *Telephone_Construct(Telephone *phone);
void Telephone_Create(void);

Telephone *TelephoneReceiver_Delete(void *receiver);
Telephone *TelephoneReceiver_Destroy(void *receiver);

#endif
