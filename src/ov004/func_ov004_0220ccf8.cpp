/* func_ov004_0220ccf8 @ 0x0220ccf8, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/RoomObject.h"

typedef int (RoomObject::*PMF)();

extern "C" int func_ov004_0220ccf8(RoomObject *self, int idx)
{
    static PMF table[9] = {
        &RoomObject::func_ov004_0220cb68, &RoomObject::func_ov004_0220c9f8, &RoomObject::func_ov004_0220c930,
        &RoomObject::func_ov004_0220c7e0, &RoomObject::func_ov004_0220c6fc, &RoomObject::func_ov004_0220c6b8,
        &RoomObject::func_ov004_0220c640, &RoomObject::func_ov004_0220c9f8, &RoomObject::func_ov004_0220c5c8};

    if (idx < 9) {
        int result = (self->*table[idx])();
        if (result != 0) {
            self->unk_534 = idx;
            return 1;
        }
    }
    return 0;
}
