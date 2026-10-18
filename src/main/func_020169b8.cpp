/* func_020169b8 @ 0x020169b8, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020169b8EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c1530;
extern Pmf data_020d87b4, data_020d87e4, data_020d8a1c, data_020d8a6c;
extern Pmf data_021c174c[4];

void Obj_020d8bd4::func_020169b8(void *arg)
{
    if (!(data_021c1530 & 1)) {
        data_021c174c[0] = data_020d87e4;
        data_021c174c[1] = data_020d8a1c;
        data_021c174c[2] = data_020d8a6c;
        data_021c174c[3] = data_020d87b4;
        data_021c1530 |= 1;
    }
    unsigned char i = unk_98;
    if (i < 4) {
        (this->*(data_021c174c[i]))(arg);
    }
}
