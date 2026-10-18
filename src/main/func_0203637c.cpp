/* func_0203637c @ 0x0203637c, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0203637c.h"
typedef void (Base_0203637c::*PMF)(void *);

extern int data_021c5270;
extern PMF data_020da254, data_020da25c, data_020da264, data_020da274, data_020da28c, data_020da294, data_020da29c,
    data_020da2a4;
extern PMF data_021c5274[8];

extern "C" void func_0203637c(Base_0203637c *self)
{
    if (!(data_021c5270 & 1)) {
        data_021c5274[0] = data_020da2a4;
        data_021c5274[1] = data_020da25c;
        data_021c5274[2] = data_020da28c;
        data_021c5274[3] = data_020da254;
        data_021c5274[4] = data_020da274;
        data_021c5274[5] = data_020da264;
        data_021c5274[6] = data_020da294;
        data_021c5274[7] = data_020da29c;
        data_021c5270 |= 1;
    }
    int i;
    for (i = 0; i < 8; i++) {
        (self->*data_021c5274[i])(&self->arr[i]);
    }
}
