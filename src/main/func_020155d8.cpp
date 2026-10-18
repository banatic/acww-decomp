/* func_020155d8 @ 0x020155d8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020155d8Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c1540;
extern Pmf data_020d89cc, data_020d89e4, data_020d89ec;
extern Pmf data_021c1714[3];

int Obj_020d8bd4::func_020155d8()
{
    if (!(data_021c1540 & 1)) {
        data_021c1714[0] = data_020d89cc;
        data_021c1714[1] = data_020d89e4;
        data_021c1714[2] = data_020d89ec;
        data_021c1540 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 3) {
        r = (this->*(data_021c1714[i]))();
    }
    return r;
}
