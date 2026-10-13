/* func_02018c3c @ 0x02018c3c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02018c3cEPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_02018c3c(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_02018ca4};
    unsigned char i = unk_98;
    if (i < 1) {
        (this->*(tbl[i]))(arg);
    }
}
