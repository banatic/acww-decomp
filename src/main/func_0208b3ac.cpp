/* func_0208b3ac @ 0x0208b3ac, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_0208dd50(void *);
extern "C" void func_0208d14c(void *);
extern "C" void func_0208bfe8(void *);
extern "C" void func_0208b9f8(void *);
extern "C" void func_0208b034(void *);

#include "cpp/main/Base_0208b3ac.h"

typedef void (Base_0208b3ac::*PMF)();

extern "C" void func_0208b3ac(Base_0208b3ac *self)
{
    static PMF table[6] = {&Base_0208b3ac::func_0208b34c, &Base_0208b3ac::func_0208b2cc, &Base_0208b3ac::func_0208b234,
                           &Base_0208b3ac::func_0208b1dc, &Base_0208b3ac::func_0208b1b8, &Base_0208b3ac::func_0208b148};

    (self->*table[self->mIndex])();

    func_0208dd50((char *) self + 8);
    func_0208d14c((char *) self + 0xe0);
    func_0208bfe8((char *) self + 0x1c4);
    func_0208b9f8((char *) self + 0x2c4);
    func_0208b034(self);
}
