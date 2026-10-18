/* func_02019030 @ 0x02019030, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02019030EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c14f0;
extern Pmf data_020d854c;
extern Pmf data_021c1554[1];

void Obj_020d8bd4::func_02019030(void *arg)
{
    if (!(data_021c14f0 & 1)) {
        data_021c1554[0] = data_020d854c;
        data_021c14f0 |= 1;
    }
    unsigned char i = unk_98;
    if (i < 1) {
        (this->*(data_021c1554[i]))(arg);
    }
}
