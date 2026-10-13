/* func_0208f9b8 @ 0x0208f9b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2400.h"

extern "C" void func_0208f9b8(Obj_020e2400 *self)
{
    static void (Obj_020e2400::*table[2])() = {&Obj_020e2400::func_0208f838, &Obj_020e2400::func_0208f748};
    (self->*table[self->unk_20])();
}
