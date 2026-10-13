/* func_0208d174 @ 0x0208d174, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2218.h"
typedef void (Obj_020e2218::*Pmf)();
extern "C" void func_0208c978(Obj_020e2218 *);
extern "C" void func_0208cc44(Obj_020e2218 *);
extern "C" void func_0208c8ac(Obj_020e2218 *);
extern "C" void func_0208d174(Obj_020e2218 *self)
{
    func_0208c978(self);
    static Pmf tbl[] = {&Obj_020e2218::func_0208cffc, &Obj_020e2218::func_0208cf8c, &Obj_020e2218::func_0208cf6c,
                        &Obj_020e2218::func_0208cf00};
    (self->*(tbl[self->unk_20]))();
    func_0208cc44(self);
    if (self->unk_20) {
        func_0208c8ac(self);
    }
}
