/* func_ov068_02272900 @ 0x02272900, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272900Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_02055060(Obj_020dd05c *dst, int src, int flag, int size, int opt1, int opt2);

int Obj_ov068_02277750::func_ov068_02272900()
{
    int v = vfunc_64();
    func_02055060(&unk_13c, v, 1, 0x1000, 0, 0);
    return 1;
}
