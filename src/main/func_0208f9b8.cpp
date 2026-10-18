/* func_0208f9b8 @ 0x0208f9b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2400.h"

extern int data_021d3620;
extern void (Obj_020e2400::*data_020e23bc)();
extern void (Obj_020e2400::*data_020e23cc)();
extern void (Obj_020e2400::*data_021d3644[2])();

extern "C" void func_0208f9b8(Obj_020e2400 *self)
{
    if (!(data_021d3620 & 1)) {
        data_021d3644[0] = data_020e23cc;
        data_021d3644[1] = data_020e23bc;
        data_021d3620 |= 1;
    }
    (self->*data_021d3644[self->unk_20])();
}
