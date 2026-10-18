/* func_0206cd40 @ 0x0206cd40, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206cd40.h"
typedef void (Base_0206cd40::*Pmf)();
extern Pmf __ptmf_null;
extern int data_021cda84;
extern Pmf data_021cdaa4[3];

extern "C" void func_0206cd40(Base_0206cd40 *self)
{
    if (!(data_021cda84 & 1)) {
        data_021cdaa4[0] = __ptmf_null;
        data_021cdaa4[1] = __ptmf_null;
        data_021cdaa4[2] = &Base_0206cd40::func_0206c3b8;
        data_021cda84 |= 1;
    }
    Pmf p = data_021cdaa4[self->unk_38];
    if (p) {
        (self->*p)();
    }
}
