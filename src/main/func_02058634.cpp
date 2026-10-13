/* func_02058634 @ 0x02058634, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02058634.h"
typedef void (Base_02058634::*Pmf)();
extern "C" void func_02058634(Base_02058634 *self)
{
    static Pmf tbl[] = {&Base_02058634::func_02058964, &Base_02058634::func_02058788, &Base_02058634::func_020586b0};
    unsigned char i = self->unk_D4;
    if (i < 3) {
        (self->*(tbl[i]))();
    }
}
