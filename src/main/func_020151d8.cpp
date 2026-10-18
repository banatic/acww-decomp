/* func_020151d8 @ 0x020151d8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020151d8Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c14e4;
extern Pmf data_020d8a94, data_020d8b24;
extern Pmf data_021c15bc[2];

int Obj_020d8bd4::func_020151d8()
{
    if (!(data_021c14e4 & 1)) {
        data_021c15bc[0] = data_020d8b24;
        data_021c15bc[1] = data_020d8a94;
        data_021c14e4 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c15bc[i]))();
    }
    return r;
}
