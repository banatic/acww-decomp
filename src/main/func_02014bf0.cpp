/* func_02014bf0 @ 0x02014bf0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014bf0Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c1500;
extern Pmf data_020d85ac, data_020d863c;
extern Pmf data_021c161c[2];

int Obj_020d8bd4::func_02014bf0()
{
    if (!(data_021c1500 & 1)) {
        data_021c161c[0] = data_020d85ac;
        data_021c161c[1] = data_020d863c;
        data_021c1500 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c161c[i]))();
    }
    return r;
}
