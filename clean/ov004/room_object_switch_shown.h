/* A class of overlay 4's room objects (vtable 0x02250ad8, receiver part 0x02250b84, 0x848
 * bytes, class number 0x27 in RoomObject.unk_780) that is drawn only while on, unless its
 * furniture's item code (ItemCode_MakeVariant of its number) is one of 0x4124 to 0x4223, which
 * are always drawn. Its state (SwitchShownObject.state, off or on) runs through tables of
 * member pointers (member_pointer.h); each frame it sets its switch, shown at once, and the
 * value of its node set (RoomObject.node_set) to the state.
 *
 * Once its model is bound it enters the state its switch says. Others turn it on or off by
 * requesting the state for the object at its cell (func_0205265c, through
 * func_ov004_0223b364 and func_ov004_0223b3c0). */
#ifndef CLEAN_OV004_ROOM_OBJECT_SWITCH_SHOWN_H
#define CLEAN_OV004_ROOM_OBJECT_SWITCH_SHOWN_H

#include "types.h"

#include "room_object.h"

typedef struct SwitchShownObject {
    RoomObject base;
    u8 state;        /* SwitchShownState */
    u8 always_drawn; /* its item code is one of 0x4124 to 0x4223 */
    u8 unk_846[2];
} SwitchShownObject;

enum SwitchShownState { SWITCH_SHOWN_OFF = 0, SWITCH_SHOWN_ON = 1, SWITCH_SHOWN_STATE_COUNT = 2 };

void SwitchShown_UpdateOn(SwitchShownObject *object);
int SwitchShown_EnterOn(SwitchShownObject *object);
void SwitchShown_UpdateOff(SwitchShownObject *object);
int SwitchShown_EnterOff(SwitchShownObject *object);
void SwitchShown_UpdateState(SwitchShownObject *object);
int SwitchShown_EnterState(SwitchShownObject *object, unsigned int state, int value);
u8 SwitchShown_StateIsOn(SwitchShownObject *object, unsigned int state);
int SwitchShown_RequestOn(SwitchShownObject *object);
int SwitchShown_RequestOff(SwitchShownObject *object);
int SwitchShown_CanDraw(SwitchShownObject *object);
int SwitchShown_Vfunc0C(void);
int SwitchShown_Update(SwitchShownObject *object);
int SwitchShown_Start(SwitchShownObject *object);
SwitchShownObject *SwitchShown_Delete(SwitchShownObject *object);
SwitchShownObject *SwitchShown_Destroy(SwitchShownObject *object);
SwitchShownObject *SwitchShown_Construct(SwitchShownObject *object);
void SwitchShown_Create(void);

#endif
