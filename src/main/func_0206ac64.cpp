/* func_0206ac64 @ 0x0206ac64, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206ac64.h"
typedef void (Base_0206ac64::*Pmf)();
extern Pmf data_0213dd98;
extern "C" void func_0206ac64(Base_0206ac64 *self)
{
    static Pmf tbl[] = {&Base_0206ac64::func_020692c8, data_0213dd98, &Base_0206ac64::func_02069270};
    Pmf p = tbl[self->unk_3C];
    (self->*p)();
}
