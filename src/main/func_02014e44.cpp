/* func_02014e44 @ 0x02014e44, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014e44Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c14dc;
extern Pmf data_020d8574, data_020d866c;
extern Pmf data_021c15fc[2];

int Obj_020d8bd4::func_02014e44()
{
    if (!(data_021c14dc & 1)) {
        data_021c15fc[0] = data_020d8574;
        data_021c15fc[1] = data_020d866c;
        data_021c14dc |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c15fc[i]))();
    }
    return r;
}
