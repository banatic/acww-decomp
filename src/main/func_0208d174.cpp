/* func_0208d174 @ 0x0208d174, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2218.h"
typedef void (Obj_020e2218::*Pmf)();
extern "C" void func_0208c978(Obj_020e2218 *);
extern "C" void func_0208cc44(Obj_020e2218 *);
extern "C" void func_0208c8ac(Obj_020e2218 *);
extern int data_021d3154;
extern Pmf data_020e20dc, data_020e20fc, data_020e2164, data_020e21b4;
extern Pmf data_021d3190[4];

extern "C" void func_0208d174(Obj_020e2218 *self)
{
    func_0208c978(self);
    if (!(data_021d3154 & 1)) {
        data_021d3190[0] = data_020e21b4;
        data_021d3190[1] = data_020e2164;
        data_021d3190[2] = data_020e20fc;
        data_021d3190[3] = data_020e20dc;
        data_021d3154 |= 1;
    }
    (self->*(data_021d3190[self->unk_20]))();
    func_0208cc44(self);
    if (self->unk_20) {
        func_0208c8ac(self);
    }
}
