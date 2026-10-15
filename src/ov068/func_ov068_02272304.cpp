/* func_ov068_02272304 @ 0x02272304, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272304Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_02055060(Obj_020dd05c *a, int b, int c, int d, int e, int f);

int Obj_ov068_02277750::func_ov068_02272304()
{
    int result = vfunc_64();
    int a = 0;
    int b = 0;
    func_02055060(&unk_13c, result, 1, 0x1000, a, b);
    return 1;
}
