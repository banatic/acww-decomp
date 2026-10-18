/* func_0205927c @ 0x0205927c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0205927c.h"
typedef void (Base_0205927c::*Pmf)();
extern int data_021c934c;
extern Pmf data_020dd1ac, data_020dd1b4, data_020dd2bc, data_020dd2ec;
extern Pmf data_021c9440[4];

extern "C" void func_0205927c(Base_0205927c *self)
{
    if (!(data_021c934c & 1)) {
        data_021c9440[0] = data_020dd2bc;
        data_021c9440[1] = data_020dd2ec;
        data_021c9440[2] = data_020dd1ac;
        data_021c9440[3] = data_020dd1b4;
        data_021c934c |= 1;
    }
    unsigned char i = self->unk_D4;
    if (i < 4) {
        (self->*(data_021c9440[i]))();
    }
}
