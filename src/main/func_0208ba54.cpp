/* func_0208ba54 @ 0x0208ba54, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e21fc.h"

typedef void (Obj_020e21fc::*Pmf)();
extern "C" void func_0208ba54(Obj_020e21fc *self)
{
    static Pmf tbl[] = {&Obj_020e21fc::func_0208b990, &Obj_020e21fc::func_0208b930, &Obj_020e21fc::func_0208b900,
                        &Obj_020e21fc::func_0208b8a8};
    (self->*(tbl[self->unk_20]))();
}
