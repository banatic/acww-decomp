/* func_0206ac64 @ 0x0206ac64, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206ac64.h"
typedef void (Base_0206ac64::*Pmf)();
extern Pmf __ptmf_null;
extern int data_021cda74;
extern Pmf data_020dec64, data_020deca4;
extern Pmf data_021cdad4[3];

extern "C" void func_0206ac64(Base_0206ac64 *self)
{
    if (!(data_021cda74 & 1)) {
        data_021cdad4[0] = data_020dec64;
        data_021cdad4[1] = __ptmf_null;
        data_021cdad4[2] = data_020deca4;
        data_021cda74 |= 1;
    }
    Pmf p = data_021cdad4[self->unk_3C];
    (self->*p)();
}
