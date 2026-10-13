/* func_020c3b98 @ 0x020c3b98, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020c3b98.h"
typedef void (Base_020c3b98::*Pmf)(void *);
extern "C" void func_020c3b98(Base_020c3b98 *self, void *arg)
{
    static Pmf tbl[] = {&Base_020c3b98::func_020c3c08};
    int i = self->unk_B0;
    if (i >= 0 && i < 1 && tbl[i]) {
        (self->*(tbl[i]))(arg);
    }
}
