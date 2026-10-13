/* func_ov068_02272238 @ 0x02272238, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272238Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_02055060(Obj_020dd05c *, int, int, int, int, int);
extern "C" void func_ov009_02262ef0(Obj_0213f090 *, int);

int Obj_ov068_02277750::func_ov068_02272238()
{
    int ret = vfunc_68();
    func_02055060(&unk_13c, ret, 1, 0x1000, 0, 0);
    func_ov009_02262ef0(&unk_238, 0x088a);
    return 1;
}
