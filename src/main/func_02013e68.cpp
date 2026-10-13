/* func_02013e68 @ 0x02013e68, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02013e68EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_02013e68(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_0201404c, &Obj_020d8bd4::func_02013f58, &Obj_020d8bd4::func_02013ee4};
    unsigned char i = unk_0A;
    if (i < 3) {
        (this->*(tbl[i]))(arg);
    }
}
