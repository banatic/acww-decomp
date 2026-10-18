/* func_02014f78 @ 0x02014f78, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014f78Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c1518;
extern Pmf data_020d868c, data_020d8694;
extern Pmf data_021c15ec[2];

int Obj_020d8bd4::func_02014f78()
{
    if (!(data_021c1518 & 1)) {
        data_021c15ec[0] = data_020d8694;
        data_021c15ec[1] = data_020d868c;
        data_021c1518 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c15ec[i]))();
    }
    return r;
}
