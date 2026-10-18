/* func_020142e4 @ 0x020142e4, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020142e4EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c150c;
extern Pmf data_020d8764, data_020d87dc, data_020d88fc;
extern Pmf data_021c16cc[3];

void Obj_020d8bd4::func_020142e4(void *arg)
{
    if (!(data_021c150c & 1)) {
        data_021c16cc[0] = data_020d8764;
        data_021c16cc[1] = data_020d88fc;
        data_021c16cc[2] = data_020d87dc;
        data_021c150c |= 1;
    }
    unsigned char i = unk_0A;
    if (i < 3) {
        (this->*(data_021c16cc[i]))(arg);
    }
}
