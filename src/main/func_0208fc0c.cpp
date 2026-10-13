/* func_0208fc0c @ 0x0208fc0c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e23e4.h"

extern "C" void func_0208fc0c(Obj_020e23e4 *obj)
{
    static void (Obj_020e23e4::*const funcs[2])() = {&Obj_020e23e4::func_0208fbbc, &Obj_020e23e4::func_0208fb70};
    obj->count += 0x1111;
    (obj->*funcs[obj->index])();
}
