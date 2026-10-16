/* The bromide (a photo): a class of overlay 4's room objects (vtable 0x02251b40, receiver part
 * 0x02251bec, 0x848 bytes) whose receiver part is named "obj_etc_bromide". It talks over its
 * receiver like the telephone (telephone.h), through tables of member pointers
 * (member_pointer.h): idle until its switch is asked to change, when it asks the scene for an
 * event (func_0203e0a8); event 1 opens it, event 8 makes it idle again. Open, it talks at once:
 * it takes the receiver, names it, and gives it the photo's number (its item code among
 * 0x47d8-0x4a47, four codes a photo); it waits for its link to open (BROMIDE_TALK), then for
 * it to close, when it hands the receiver back and lets the scene go on (BROMIDE_TALK_END).
 * Each frame it runs its state's update. */
#ifndef CLEAN_OV004_BROMIDE_H
#define CLEAN_OV004_BROMIDE_H

#include "types.h"

#include "room_object.h"

typedef struct Bromide {
    RoomObject base;
    s32 state; /* BromideState */
} Bromide;

enum BromideState {
    BROMIDE_IDLE = 0,
    BROMIDE_OPEN = 1,
    BROMIDE_TALK = 2,     /* waits for the link to open */
    BROMIDE_TALK_END = 3, /* waits for it to close */
    BROMIDE_STATE_COUNT = 4
};

void Bromide_UpdateTalkEnd(Bromide *bromide);
int Bromide_EnterTalkEnd(Bromide *bromide);
void Bromide_UpdateTalk(Bromide *bromide);
int Bromide_EnterTalk(Bromide *bromide);
void Bromide_UpdateOpen(Bromide *bromide);
int Bromide_EnterOpen(Bromide *bromide);
int Bromide_UpdateIdle(Bromide *bromide);
int Bromide_EnterIdle(Bromide *bromide);
void Bromide_UpdateState(Bromide *bromide);
int Bromide_EnterState(Bromide *bromide, int state);
void Bromide_OnSceneEvent(Bromide *bromide, int event);
int Bromide_Vfunc0C(void);
int Bromide_Update(Bromide *bromide);
int Bromide_Start(void);
Bromide *Bromide_Delete(Bromide *bromide);
Bromide *Bromide_Destroy(Bromide *bromide);
Bromide *Bromide_Construct(Bromide *bromide);
void Bromide_Create(void);

#endif
