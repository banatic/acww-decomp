/* func_02057d90 @ 0x02057d90, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02057d90.h"
typedef void (Base_02057d90::*Pmf)();
extern int data_021c936c;
extern Pmf data_020dd1ec, data_020dd1f4, data_020dd2a4;
extern Pmf data_021c9428[3];

extern "C" void func_02057d90(Base_02057d90 *self)
{
    if (!(data_021c936c & 1)) {
        data_021c9428[0] = data_020dd1ec;
        data_021c9428[1] = data_020dd1f4;
        data_021c9428[2] = data_020dd2a4;
        data_021c936c |= 1;
    }
    unsigned char i = self->unk_D4;
    if (i < 3) {
        (self->*(data_021c9428[i]))();
    }
}
