/* func_ov131_0229b644 @ 0x0229b644, 0xbc bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov131_0229b8f019func_ov131_0229b644Ev
 */

#include "cpp/ov131/Obj_ov131_0229b8f0.h"

void Obj_ov131_0229b8f0::func_ov131_0229b644()
{
    static void (Obj_ov131_0229b8f0::*tbl[8])() = {
        &Obj_ov131_0229b8f0::func_ov131_0229b338, &Obj_ov131_0229b8f0::func_ov131_0229b304,
        &Obj_ov131_0229b8f0::func_ov131_0229b274, &Obj_ov131_0229b8f0::func_ov131_0229b24c,
        &Obj_ov131_0229b8f0::func_ov131_0229b1f0, &Obj_ov131_0229b8f0::func_ov131_0229b1c8,
        &Obj_ov131_0229b8f0::func_ov131_0229b188, &Obj_ov131_0229b8f0::func_ov131_0229b124};
    int idx = subState;
    (this->*tbl[idx])();
}
