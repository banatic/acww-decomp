/* func_0208c04c @ 0x0208c04c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2234.h"

typedef void (Obj_020e2234::*PMF)();

extern "C" void func_0208c04c(Obj_020e2234 *self)
{
    static PMF tbl[7] = {&Obj_020e2234::func_0208be24, &Obj_020e2234::func_0208bdd0, &Obj_020e2234::func_0208bd50,
                         &Obj_020e2234::func_0208bcfc, &Obj_020e2234::func_0208bca4, &Obj_020e2234::func_0208bc60,
                         &Obj_020e2234::func_0208bc0c};
    (self->*tbl[self->idx])();
}
