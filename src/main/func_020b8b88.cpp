/* func_020b8b88 @ 0x020b8b88, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020b8b88.h"

extern "C" void func_020b8af0(Base_020b8b88 *self);

extern "C" void func_020b8b88(Base_020b8b88 *self)
{
    typedef void (Base_020b8b88::*MFN)();
    static MFN table[4] = {&Base_020b8b88::func_020b87ac, &Base_020b8b88::func_020b8744, &Base_020b8b88::func_020b86e4,
                           &Base_020b8b88::func_020b866c};
    func_020b8af0(self);
    (self->*table[self->index])();
    self->flag = 0;
    self->sub.vfunc_0c();
}
