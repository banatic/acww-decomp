/* func_02067108 @ 0x02067108, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02068144.h"

extern int data_021cda94;
extern void (Base_02068144::*data_020de81c)();
extern void (Base_02068144::*data_020de844)();
extern void (Base_02068144::*data_020de884)();
extern void (Base_02068144::*data_020dec04)();
extern void (Base_02068144::*data_020ded0c)();
extern void (Base_02068144::*data_020dee1c)();
extern void (Base_02068144::*data_021cdb44[6])();

extern "C" void func_02067108(Base_02068144 *self)
{
    if (!(data_021cda94 & 1)) {
        data_021cdb44[0] = data_020dec04;
        data_021cdb44[1] = data_020ded0c;
        data_021cdb44[2] = data_020dee1c;
        data_021cdb44[3] = data_020de81c;
        data_021cdb44[4] = data_020de844;
        data_021cdb44[5] = data_020de884;
        data_021cda94 |= 1;
    }
    if (self->next == 6) {
        return;
    }
    self->idx = self->next;
    (self->*data_021cdb44[self->next])();
    self->next = 6;
}
