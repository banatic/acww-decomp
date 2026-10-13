/* func_020169b8 @ 0x020169b8, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020169b8EPv
 */

#include "cpp/main/Obj_020d8bd4.h"
typedef void (Obj_020d8bd4::*Pmf)(void *);
void Obj_020d8bd4::func_020169b8(void *arg)
{
    static Pmf tbl[] = {&Obj_020d8bd4::func_02016f30, &Obj_020d8bd4::func_02016d6c, &Obj_020d8bd4::func_02016bfc,
                        &Obj_020d8bd4::func_02016a48};
    unsigned char i = unk_98;
    if (i < 4) {
        (this->*(tbl[i]))(arg);
    }
}
