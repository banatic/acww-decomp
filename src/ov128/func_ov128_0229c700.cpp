/* func_ov128_0229c700 @ 0x0229c700, 0x94 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov128_0229cbc019func_ov128_0229c700Ev
 */

#include "cpp/ov128/Obj_ov128_0229cbc0.h"

typedef void (Obj_ov128_0229cbc0::*PMF)();

int Obj_ov128_0229cbc0::func_ov128_0229c700()
{
    static PMF table[4] = {&Obj_ov128_0229cbc0::func_ov128_0229c58c, &Obj_ov128_0229cbc0::func_ov128_0229c554,
                           &Obj_ov128_0229cbc0::func_ov128_0229c50c, &Obj_ov128_0229cbc0::func_ov128_0229c4d0};
    func_ov128_0229c350();
    (this->*table[state])();
    func_ov128_0229c334();
    return 1;
}
