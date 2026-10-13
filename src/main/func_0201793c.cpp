/* func_0201793c @ 0x0201793c, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_0201793cEi
 */

#include "cpp/main/Obj_020d8bd4.h"

void Obj_020d8bd4::func_0201793c(int p2)
{
    static int (Obj_020d8bd4::*table[20])(int) = {
        &Obj_020d8bd4::func_020183cc, &Obj_020d8bd4::func_02018340, &Obj_020d8bd4::func_02018304,
        &Obj_020d8bd4::func_02018298, &Obj_020d8bd4::func_02018090, &Obj_020d8bd4::func_02017ff4,
        &Obj_020d8bd4::func_02017ee4, &Obj_020d8bd4::func_02017e7c, &Obj_020d8bd4::func_02017e20,
        &Obj_020d8bd4::func_02017e00, &Obj_020d8bd4::func_02017dd8, &Obj_020d8bd4::func_02017d80,
        &Obj_020d8bd4::func_02017d14, &Obj_020d8bd4::func_02017cf8, &Obj_020d8bd4::func_02017cac,
        &Obj_020d8bd4::func_02017c70, &Obj_020d8bd4::func_02017c18, &Obj_020d8bd4::func_02017b44,
        &Obj_020d8bd4::func_02017af0, &Obj_020d8bd4::func_02017ab4};
    if (unk_98 < 20) {
        (this->*table[unk_98])(p2);
    }
}
