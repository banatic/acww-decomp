/* The values of overlay 4's room objects, kept for the session (room_object_state.h). */
#include "room_object_state.h"

#include "clean.h"
#include "session.h"

static_assert(offsetof(RoomObject, state_number) == 0xea, "RoomObject.state_number is at 0xea");
static_assert(sizeof(RoomObjectStateMessage) == 1, "RoomObjectStateMessage is one byte");

#define ROOM_OBJECT_STATE_MSG 0x25
#define ROOM_OBJECT_STATE_TO 4   /* where the message goes: every other system */
#define ROOM_OBJECT_SET_ENTRY 24 /* the vtable entry that sets an object's value */

extern NetSession *data_020ccf94; /* the session */
extern u8 data_020e54a8;
extern u8 data_021dc6cc[ROOM_OBJECT_STATES];

/* func_0209d3a8 (message 0x25's payload): the value stored by RoomObjectState_Set; whether it
 * was. */
int RoomObjectState_Receive(RoomObjectStateMessage *message)
{
    return RoomObjectState_Set(message->number, message->value);
}
CLEAN_AS(func_0209d3a8, RoomObjectState_Receive)

/* func_0209d3bc: value `number` set to `value` (cut to a byte); 0 for a number of 3 or more,
 * else 1. */
int RoomObjectState_Set(unsigned int number, unsigned int value)
{
    if (number >= ROOM_OBJECT_STATES) {
        return 0;
    }
    data_021dc6cc[number] = (u8) value;
    return 1;
}
CLEAN_AS(func_0209d3bc, RoomObjectState_Set)

/* func_0209d3d0: value `number`; 0 for a number of 3 or more. */
unsigned int RoomObjectState_Get(unsigned int number)
{
    if (number >= ROOM_OBJECT_STATES) {
        return 0;
    }
    return data_021dc6cc[number];
}
CLEAN_AS(func_0209d3d0, RoomObjectState_Get)

/* func_0209d3e4: every value 0. */
void RoomObjectState_Clear(void)
{
    for (unsigned int i = 0; i < ROOM_OBJECT_STATES; i++) {
        data_021dc6cc[i] = 0;
    }
}
CLEAN_AS(func_0209d3e4, RoomObjectState_Clear)

/* func_0209d3f8: only with data_020e54a8 at 1, the object's vtable entry 24 sets `value`;
 * when it did, and the object has a number below 3 and the session is linked, message 0x25
 * tells every other system. Whether entry 24 was called and answered nonzero.
 * QUIRK: the value is not stored here; only the low four bits of `value` are sent. */
int RoomObjectState_Change(RoomObject *object, unsigned char value)
{
    if (data_020e54a8 != 1) {
        return 0;
    }
    typedef int SetValue(RoomObject * object, unsigned char value);
    SetValue *set_value = (SetValue *) (uintptr_t) object->vtable[ROOM_OBJECT_SET_ENTRY];
    if (set_value(object, value) == 0) {
        return 0;
    }
    u8 number = object->state_number;
    if (number < ROOM_OBJECT_STATES && Session_IsLinked(data_020ccf94)) {
        RoomObjectStateMessage message;
        message.number = (u8) (number & 0xf);
        message.value = (u8) (value & 0xf);
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &message, sizeof(message));
        Session_EndMessage(session, ROOM_OBJECT_STATE_MSG, ROOM_OBJECT_STATE_TO);
    }
    return 1;
}
CLEAN_AS(func_0209d3f8, RoomObjectState_Change)
