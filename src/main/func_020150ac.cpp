/* func_020150ac @ 0x020150ac, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020150acEv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef int (Obj_020d8bd4::*Pmf)();
extern int data_021c14e0;
extern Pmf data_020d8a4c, data_020d8a5c;
extern Pmf data_021c15dc[2];

int Obj_020d8bd4::func_020150ac()
{
    if (!(data_021c14e0 & 1)) {
        data_021c15dc[0] = data_020d8a5c;
        data_021c15dc[1] = data_020d8a4c;
        data_021c14e0 |= 1;
    }
    int r = 0;
    unsigned char i = unk_AC;
    if (i < 2) {
        r = (this->*(data_021c15dc[i]))();
    }
    return r;
}
