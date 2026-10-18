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

extern int data_021d3150;
extern PMF data_020e20ec, data_020e2104, data_020e210c, data_020e2144, data_020e219c, data_020e21ac;
extern PMF data_021d31f0[6];

extern "C" void func_0208b3ac(Base_0208b3ac *self)
{
    if (!(data_021d3150 & 1)) {
        data_021d31f0[0] = data_020e21ac;
        data_021d31f0[1] = data_020e219c;
        data_021d31f0[2] = data_020e210c;
        data_021d31f0[3] = data_020e2104;
        data_021d31f0[4] = data_020e2144;
        data_021d31f0[5] = data_020e20ec;
        data_021d3150 |= 1;
    }

    (self->*data_021d31f0[self->mIndex])();

    func_0208dd50((char *) self + 8);
    func_0208d14c((char *) self + 0xe0);
    func_0208bfe8((char *) self + 0x1c4);
    func_0208b9f8((char *) self + 0x2c4);
    func_0208b034(self);
}
