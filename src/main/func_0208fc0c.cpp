/* func_0208fc0c @ 0x0208fc0c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e23e4.h"

extern int data_021d3624;
extern void (Obj_020e23e4::*data_020e23b4)();
extern void (Obj_020e23e4::*data_020e23d4)();
extern void (Obj_020e23e4::*data_021d3634[2])();

extern "C" void func_0208fc0c(Obj_020e23e4 *obj)
{
    if (!(data_021d3624 & 1)) {
        data_021d3634[0] = data_020e23b4;
        data_021d3634[1] = data_020e23d4;
        data_021d3624 |= 1;
    }
    obj->count += 0x1111;
    (obj->*data_021d3634[obj->index])();
}
