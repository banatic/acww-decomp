/* func_0206cd40 @ 0x0206cd40, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206cd40.h"
typedef void (Base_0206cd40::*Pmf)();
extern Pmf data_0213dd98;
extern "C" void func_0206cd40(Base_0206cd40 *self)
{
    static Pmf tbl[] = {data_0213dd98, data_0213dd98, &Base_0206cd40::func_0206c3b8};
    Pmf p = tbl[self->unk_38];
    if (p) {
        (self->*p)();
    }
}
