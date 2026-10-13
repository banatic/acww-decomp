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

extern "C" void func_02068144(Base_02068144 *self)
{
    static PMF table[6] = {&Base_02068144::func_020670f8, &Base_02068144::func_02066f2c, &Base_02068144::func_02066dc4,
                           &Base_02068144::func_02066cd4, &Base_02068144::func_02066be0, &Base_02068144::func_02066bd0};
    (self->*table[self->idx])();
    func_02067108(self);
    func_02067c74(self);
    func_020690ec((char *) self + 0x1c);
    func_020a9d38((char *) self + 0xb4);
    if (self->idx != 0 && self->idx != 5) {
        func_02067e4c(self);
    }
}
