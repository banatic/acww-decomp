/* func_020154f4 @ 0x020154f4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020154f4Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c152c;
extern Pmf data_020d8a0c, data_020d8a24;
extern Pmf data_021c164c[2];

int Obj_020d8bd4::func_020154f4()
{
    if (!(data_021c152c & 1)) {
        data_021c164c[0] = data_020d8a0c;
        data_021c164c[1] = data_020d8a24;
        data_021c152c |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c164c[i]))();
    }
    return r;
}
