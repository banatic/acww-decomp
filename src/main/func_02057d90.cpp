/* func_02057d90 @ 0x02057d90, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02057d90.h"
typedef void (Base_02057d90::*Pmf)();
extern "C" void func_02057d90(Base_02057d90 *self)
{
    static Pmf tbl[] = {&Base_02057d90::func_02058064, &Base_02057d90::func_02057f38, &Base_02057d90::func_02057e0c};
    unsigned char i = self->unk_D4;
    if (i < 3) {
        (self->*(tbl[i]))();
    }
}
