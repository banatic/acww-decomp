/* func_0208e2c4 @ 0x0208e2c4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e22f8.h"
typedef void (Obj_020e22f8::*Pmf)();
extern "C" void func_0208a0c8(void *);
extern int data_021d35a4;
extern Pmf data_020e22d0, data_020e22d8, data_020e22e0, data_020e22e8;
extern Pmf data_021d35a8[4];

extern "C" void func_0208e2c4(Obj_020e22f8 *self)
{
    if (!(data_021d35a4 & 1)) {
        data_021d35a8[0] = data_020e22d8;
        data_021d35a8[1] = data_020e22e8;
        data_021d35a8[2] = data_020e22d0;
        data_021d35a8[3] = data_020e22e0;
        data_021d35a4 |= 1;
    }
    (self->*(data_021d35a8[self->unk_70]))();
    if (self->unk_70) {
        func_0208a0c8(self->unk_14);
    }
}
