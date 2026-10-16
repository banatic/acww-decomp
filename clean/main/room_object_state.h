/* Three byte values (data_021dc6cc) that overlay 4's room objects keep by the number in their
 * byte 0xea (0-2; 0xff for an object without one). An object sets its value (one of 1 or 3, as
 * overlay 4 passes) through its vtable entry 24; with data_020e54a8 at 1 (the case in which the
 * pockets scene can put up wallpaper, ov097/pockets_room.h) RoomObjectState_Change does that
 * and, while the session is linked, tells every other system with message 0x25, a byte holding
 * the number (bits 0-3) and the value (bits 4-7). Its handler (func_02076f2c) stores the value
 * here with RoomObjectState_Receive. The values are cleared when the session's state is reset
 * (func_02075104) and by func_0209e604. */
#ifndef CLEAN_MAIN_ROOM_OBJECT_STATE_H
#define CLEAN_MAIN_ROOM_OBJECT_STATE_H

#include "types.h"

#define ROOM_OBJECT_STATES 3
#define ROOM_OBJECT_STATE_NONE 0xff /* RoomObject.state_number of an object without one */

/* The part of an overlay 4 room object read here. */
typedef struct RoomObject {
    const u32 *vtable; /* 0x00: entry 24 sets the object's value */
    u8 unk_04[0xe6];
    u8 state_number; /* 0xea: its value's number, or ROOM_OBJECT_STATE_NONE */
} RoomObject;

/* Message 0x25: the number and the value in one byte. */
typedef struct RoomObjectStateMessage {
    u8 number : 4;
    u8 value : 4;
} RoomObjectStateMessage;

int RoomObjectState_Receive(RoomObjectStateMessage *message);
int RoomObjectState_Set(unsigned int number, unsigned int value);
unsigned int RoomObjectState_Get(unsigned int number);
void RoomObjectState_Clear(void);
int RoomObjectState_Change(RoomObject *object, unsigned char value);

#endif
