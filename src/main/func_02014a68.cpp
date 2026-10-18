/* func_02014a68 @ 0x02014a68, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02014a68Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c14fc;
extern Pmf data_020d861c, data_020d8624, data_020d862c;
extern Pmf data_021c166c[3];

int Obj_020d8bd4::func_02014a68()
{
    if (!(data_021c14fc & 1)) {
        data_021c166c[0] = data_020d862c;
        data_021c166c[1] = data_020d8624;
        data_021c166c[2] = data_020d861c;
        data_021c14fc |= 1;
    }
    unsigned char i = unk_AC;
    if (i < 3) {
        return (this->*(data_021c166c[i]))();
    }
    return 0;
}
