/* func_0208c6b0 @ 0x0208c6b0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2250.h"
typedef void (Obj_020e2250::*Pmf)();
extern int data_021d314c;
extern Pmf data_020e211c, data_020e2124, data_020e21bc, data_020e21c4;
extern Pmf data_021d31d0[4];

extern "C" void func_0208c6b0(Obj_020e2250 *self)
{
    if (!(data_021d314c & 1)) {
        data_021d31d0[0] = data_020e211c;
        data_021d31d0[1] = data_020e2124;
        data_021d31d0[2] = data_020e21bc;
        data_021d31d0[3] = data_020e21c4;
        data_021d314c |= 1;
    }
    (self->*(data_021d31d0[self->unk_C0]))();
}
