/* func_02014d1c @ 0x02014d1c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014d1cEv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c14e8;
extern Pmf data_020d858c, data_020d8654;
extern Pmf data_021c160c[2];

int Obj_020d8bd4::func_02014d1c()
{
    if (!(data_021c14e8 & 1)) {
        data_021c160c[0] = data_020d858c;
        data_021c160c[1] = data_020d8654;
        data_021c14e8 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c160c[i]))();
    }
    return r;
}
