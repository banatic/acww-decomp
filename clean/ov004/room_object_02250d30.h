/* A class of overlay 4's room objects (vtable 0x02250d30, receiver part 0x02250ddc, 0x848
 * bytes) that, once its model is bound, keeps the word at 0x10 of data_ov004_022596b0
 * (func_ov004_0223d03c, func_ov004_0223d2ac) cut to 16 bits. The rest is the base class's
 * (room_object_life.h). */
#ifndef CLEAN_OV004_ROOM_OBJECT_02250D30_H
#define CLEAN_OV004_ROOM_OBJECT_02250D30_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02250d30 {
    RoomObject base;
    u16 unk_844; /* func_ov004_0223d2ac of data_ov004_022596b0 */
    u8 unk_846[2];
} RoomObject02250d30;

int RoomObject02250d30_Vfunc0C(void);
int RoomObject02250d30_Vfunc80(void);
int RoomObject02250d30_Start(RoomObject02250d30 *object);
RoomObject02250d30 *RoomObject02250d30_Delete(RoomObject02250d30 *object);
RoomObject02250d30 *RoomObject02250d30_Destroy(RoomObject02250d30 *object);
RoomObject02250d30 *RoomObject02250d30_Construct(RoomObject02250d30 *object);
void RoomObject02250d30_Create(void);

RoomObject02250d30 *RoomObject02250d30Receiver_Delete(void *receiver);
RoomObject02250d30 *RoomObject02250d30Receiver_Destroy(void *receiver);

#endif
