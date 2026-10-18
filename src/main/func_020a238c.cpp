/* func_020a238c @ 0x020a238c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020a238c.h"
typedef int (Base_020a238c::*Pmf)();
extern int data_021f3c28;
extern Pmf data_020e3828, data_020e3838, data_020e3868, data_020e38f0;
extern Pmf data_021f3c64[4];

extern "C" int func_020a238c(Base_020a238c *self)
{
    int r = 0;
    if (!(data_021f3c28 & 1)) {
        data_021f3c64[0] = data_020e3828;
        data_021f3c64[1] = data_020e3838;
        data_021f3c64[2] = data_020e38f0;
        data_021f3c64[3] = data_020e3868;
        data_021f3c28 |= 1;
    }
    unsigned char i = self->unk_A0;
    if (data_021f3c64[i]) {
        r = (self->*(data_021f3c64[i]))();
    }
    if (r != 3) {
        self->unk_A0 = 0;
        return r;
    }
    return 3;
}
