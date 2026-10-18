/* func_02013d5c @ 0x02013d5c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02013d5cEPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c14f8;
extern Pmf data_020d89f4;
extern Pmf data_021c156c[1];

void Obj_020d8bd4::func_02013d5c(void *arg)
{
    if (!(data_021c14f8 & 1)) {
        data_021c156c[0] = data_020d89f4;
        data_021c14f8 |= 1;
    }
    unsigned char i = unk_0A;
    if (i < 1) {
        (this->*(data_021c156c[i]))(arg);
    }
}
