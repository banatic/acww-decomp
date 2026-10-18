/* func_02058634 @ 0x02058634, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02058634.h"
typedef void (Base_02058634::*Pmf)();
extern int data_021c9370;
extern Pmf data_020dd284, data_020dd29c, data_020dd2fc;
extern Pmf data_021c9410[3];

extern "C" void func_02058634(Base_02058634 *self)
{
    if (!(data_021c9370 & 1)) {
        data_021c9410[0] = data_020dd284;
        data_021c9410[1] = data_020dd29c;
        data_021c9410[2] = data_020dd2fc;
        data_021c9370 |= 1;
    }
    unsigned char i = self->unk_D4;
    if (i < 3) {
        (self->*(data_021c9410[i]))();
    }
}
