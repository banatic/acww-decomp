/* func_0206d26c @ 0x0206d26c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206d26c.h"
typedef void (Base_0206d26c::*Pmf)();

// 0x0213dd98: an 8-byte member-pointer object in BSS.
extern Pmf data_0213dd98;

extern "C" void func_0206d26c(Base_0206d26c *self)
{
    static Pmf tbl[] = {
        &Base_0206d26c::func_0206cd28,
        &Base_0206d26c::func_0206cd10,
        data_0213dd98,
        data_0213dd98,
        data_0213dd98,
        data_0213dd98,
        &Base_0206d26c::func_0206ccf8,
        &Base_0206d26c::func_0206cce0,
        &Base_0206d26c::func_0206ccc8,
        data_0213dd98,
        data_0213dd98,
    };
    Pmf p = tbl[self->unk_38];
    (self->*p)();
}
