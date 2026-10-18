/* func_02068144 @ 0x02068144, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02068144.h"

typedef void (Base_02068144::*PMF)();

extern "C" void func_02067108(Base_02068144 *self);
extern "C" void func_02067c74(Base_02068144 *self);
extern "C" void func_020690ec(void *ptr);
extern "C" void func_020a9d38(void *ptr);
extern "C" void func_02067e4c(Base_02068144 *self);

extern int data_021cda5c;
extern PMF data_020de804, data_020de814, data_020de82c, data_020de83c, data_020de9e4, data_020deea4;
extern PMF data_021cdb14[6];

extern "C" void func_02068144(Base_02068144 *self)
{
    if (!(data_021cda5c & 1)) {
        data_021cdb14[0] = data_020deea4;
        data_021cdb14[1] = data_020de804;
        data_021cdb14[2] = data_020de814;
        data_021cdb14[3] = data_020de9e4;
        data_021cdb14[4] = data_020de82c;
        data_021cdb14[5] = data_020de83c;
        data_021cda5c |= 1;
    }
    (self->*data_021cdb14[self->idx])();
    func_02067108(self);
    func_02067c74(self);
    func_020690ec((char *) self + 0x1c);
    func_020a9d38((char *) self + 0xb4);
    if (self->idx != 0 && self->idx != 5) {
        func_02067e4c(self);
    }
}
