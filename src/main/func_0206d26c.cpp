/* func_0206d26c @ 0x0206d26c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0206d26c.h"

typedef void (Base_0206d26c::*Pmf)();

// 0x0213dd98: an 8-byte member-pointer object in BSS.
extern Pmf __ptmf_null;

extern int data_021cda58;
extern Pmf data_020de88c, data_020de8c4, data_020dea2c, data_020dea54, data_020deec4;
extern Pmf data_021cdcdc[11];

extern "C" void func_0206d26c(Base_0206d26c *self)
{
    if (!(data_021cda58 & 1)) {
        data_021cdcdc[0] = data_020deec4;
        data_021cdcdc[1] = data_020de88c;
        data_021cdcdc[2] = __ptmf_null;
        data_021cdcdc[3] = __ptmf_null;
        data_021cdcdc[4] = __ptmf_null;
        data_021cdcdc[5] = __ptmf_null;
        data_021cdcdc[6] = data_020de8c4;
        data_021cdcdc[7] = data_020dea2c;
        data_021cdcdc[8] = data_020dea54;
        data_021cdcdc[9] = __ptmf_null;
        data_021cdcdc[10] = __ptmf_null;
        data_021cda58 |= 1;
    }
    Pmf p = data_021cdcdc[self->unk_38];
    (self->*p)();
}
