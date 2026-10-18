/* func_020175d4 @ 0x020175d4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020175d4EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
extern int data_021c1508;
extern Pmf data_020d882c, data_020d8834, data_020d883c;
extern Pmf data_021c169c[3];

void Obj_020d8bd4::func_020175d4(void *arg)
{
    if (!(data_021c1508 & 1)) {
        data_021c169c[0] = data_020d883c;
        data_021c169c[1] = data_020d8834;
        data_021c169c[2] = data_020d882c;
        data_021c1508 |= 1;
    }
    unsigned char i = unk_98;
    if (i < 3) {
        (this->*(data_021c169c[i]))(arg);
    }
}
