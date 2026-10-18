/* func_02015370 @ 0x02015370, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02015370Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c1544;
extern Pmf data_020d8a44, data_020d8a74;
extern Pmf data_021c165c[2];

int Obj_020d8bd4::func_02015370()
{
    if (!(data_021c1544 & 1)) {
        data_021c165c[0] = data_020d8a44;
        data_021c165c[1] = data_020d8a74;
        data_021c1544 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c165c[i]))();
    }
    return r;
}
