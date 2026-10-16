/* The bromide (a photo): a class of overlay 4's room objects (vtable 0x02251b40, receiver part
 * 0x02251bec, 0x848 bytes) whose receiver part is named "obj_etc_bromide". It talks over its
 * receiver like the telephone (telephone.h), through tables of member pointers
 * (member_pointer.h, func_ov004_02213504 and func_ov004_02213590): it waits for its link to
 * open (BROMIDE_TALK), then for it to close, when it hands the receiver back and lets the scene
 * go on (BROMIDE_TALK_END). */
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

#endif
