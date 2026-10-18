/* func_020148a0 @ 0x020148a0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020148a0Ev
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c1510;
extern Pmf data_020d85f4, data_020d8604, data_020d88f4;
extern Pmf data_021c1684[3];

int Obj_020d8bd4::func_020148a0()
{
    if (!(data_021c1510 & 1)) {
        data_021c1684[0] = data_020d88f4;
        data_021c1684[1] = data_020d85f4;
        data_021c1684[2] = data_020d8604;
        data_021c1510 |= 1;
    }
    unsigned char i = unk_AC;
    if (i < 3) {
        return (this->*(data_021c1684[i]))();
    }
    return 0;
}
