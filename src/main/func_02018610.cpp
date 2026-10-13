/* func_02018610 @ 0x02018610, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02018610Ei
 */

#include "cpp/main/Obj_020d8bd4.h"

void Obj_020d8bd4::func_02018610(int arg)
{
    static void (Obj_020d8bd4::*tbl[5])(int) = {&Obj_020d8bd4::func_020187b8, &Obj_020d8bd4::func_0201875c,
                                                &Obj_020d8bd4::func_0201873c, &Obj_020d8bd4::func_02018714,
                                                &Obj_020d8bd4::func_020186b0};
    if (unk_98 < 5) {
        (this->*tbl[unk_98])(arg);
    }
}
