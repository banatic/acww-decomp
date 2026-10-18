/* func_020aad9c @ 0x020aad9c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020aad9c.h"
typedef void (Base_020aad9c::*Pmf)();
extern "C" int func_020aabe0(void);
extern "C" void func_020aaabc(Base_020aad9c *);
extern "C" void func_020aab48(Base_020aad9c *);
extern int data_021f45a8;
extern Pmf data_020e3f54, data_020e3f5c;
extern Pmf data_021f45c0[2];

extern "C" void func_020aad9c(Base_020aad9c *self)
{
    if (!func_020aabe0()) {
        if (!(data_021f45a8 & 1)) {
            data_021f45c0[0] = data_020e3f5c;
            data_021f45c0[1] = data_020e3f54;
            data_021f45a8 |= 1;
        }
        func_020aaabc(self);
        func_020aab48(self);
        (self->*(data_021f45c0[self->unk_2C]))();
    }
}
