/* A class of overlay 4's room objects (vtable 0x022526f8, receiver part 0x022527a4) that plays
 * its model's animations from the start (variant 0) as soon as its model is bound, from the
 * frame ItemInfo_Zero gives (always 0). The rest is the base class's (room_object_life.h). */
#ifndef CLEAN_OV004_ROOM_OBJECT_ANIMATED_H
#define CLEAN_OV004_ROOM_OBJECT_ANIMATED_H

#include "types.h"

#include "room_object.h"

typedef struct AnimatedRoomObject {
    RoomObject base;
    s32 start_frame; /* what ItemInfo_Zero gave */
} AnimatedRoomObject;

int AnimatedRoomObject_Vfunc0C(void);
int AnimatedRoomObject_Vfunc80(void);
int AnimatedRoomObject_StartAnims(AnimatedRoomObject *object);
AnimatedRoomObject *AnimatedRoomObject_Delete(AnimatedRoomObject *object);
AnimatedRoomObject *AnimatedRoomObject_Destroy(AnimatedRoomObject *object);
AnimatedRoomObject *AnimatedRoomObject_Construct(AnimatedRoomObject *object);
void AnimatedRoomObject_Create(void);

AnimatedRoomObject *AnimatedRoomObjectReceiver_Delete(void *receiver);
AnimatedRoomObject *AnimatedRoomObjectReceiver_Destroy(void *receiver);

#endif
