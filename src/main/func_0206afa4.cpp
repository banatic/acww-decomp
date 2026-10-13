/* func_0206afa4 @ 0x0206afa4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206afa4.h"
typedef void (Base_0206afa4::*Pmf)();
extern "C" void func_0206afa4(Base_0206afa4 *self)
{
    static Pmf tbl[] = {&Base_0206afa4::func_0206965c, &Base_0206afa4::func_02069658, &Base_0206afa4::func_02069654};
    Pmf p = tbl[self->unk_3C];
    (self->*p)();
}
