/* func_ov004_0220cc28 @ 0x0220cc28, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN10RoomObject19func_ov004_0220cc28Ev
 */

#include "cpp/ov004/RoomObject.h"

typedef void (RoomObject::*PMF)();

void RoomObject::func_ov004_0220cc28()
{
    static PMF tbl[9] = {
        &RoomObject::func_ov004_0220c9fc, &RoomObject::func_ov004_0220c9f4, &RoomObject::func_ov004_0220c858,
        &RoomObject::func_ov004_0220c774, &RoomObject::func_ov004_0220c6f4, &RoomObject::func_ov004_0220c648,
        &RoomObject::func_ov004_0220c5cc, &RoomObject::func_ov004_0220c9f4, &RoomObject::func_ov004_0220c560,
    };
    if (unk_534 < 9) {
        (this->*tbl[unk_534])();
    }
}
