/* func_020b5b18 @ 0x020b5b18, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e5408.h"
typedef void (Obj_020e5408::*Pmf)();
extern "C" int func_020b5b18(Obj_020e5408 *self)
{
    static Pmf tbl[] = {&Obj_020e5408::func_020b5c04, &Obj_020e5408::func_020b5be4, &Obj_020e5408::func_020b5be0};
    (self->*(tbl[self->unk_50]))();
    return 1;
}
