/* func_ov113_0229a880 @ 0x0229a880, 0xd8 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov113_0229ac0019func_ov113_0229a880Ev
 */

#include "cpp/ov113/Obj_ov113_0229ac00.h"

int Obj_ov113_0229ac00::func_ov113_0229a880()
{
    static void (Obj_ov113_0229ac00::*tbl[9])() = {
        &Obj_ov113_0229ac00::func_ov113_0229a74c, &Obj_ov113_0229ac00::func_ov113_0229a71c,
        &Obj_ov113_0229ac00::func_ov113_0229a6d4, &Obj_ov113_0229ac00::func_ov113_0229a6a4,
        &Obj_ov113_0229ac00::func_ov113_0229a658, &Obj_ov113_0229ac00::func_ov113_0229a5c0,
        &Obj_ov113_0229ac00::func_ov113_0229a590, &Obj_ov113_0229ac00::func_ov113_0229a504,
        &Obj_ov113_0229ac00::func_ov113_0229a4a4};
    func_ov113_0229a398();
    (this->*tbl[state])();
    func_ov113_0229a350();
    return 1;
}
