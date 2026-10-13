/* func_ov091_0229936c @ 0x0229936c, 0xa4 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov091_0229953019func_ov091_0229936cEv
 */

#include "cpp/ov091/Obj_ov091_02299530.h"

int Obj_ov091_02299530::func_ov091_0229936c()
{
    static void (Obj_ov091_02299530::*table[6])() = {
        &Obj_ov091_02299530::func_ov091_02299244, &Obj_ov091_02299530::func_ov091_022991e8,
        &Obj_ov091_02299530::func_ov091_022991b0, &Obj_ov091_02299530::func_ov091_0229914c,
        &Obj_ov091_02299530::func_ov091_022990f4, &Obj_ov091_02299530::func_ov091_022990b0};
    unsigned char idx = state;
    (this->*table[idx])();
    return 1;
}
