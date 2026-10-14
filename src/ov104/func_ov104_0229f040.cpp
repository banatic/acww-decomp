/* func_ov104_0229f040 @ 0x0229f040, 0x1c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov104_0229f6d019func_ov104_0229f040Ev
 */

#include "cpp/ov104/Obj_ov104_0229f6d0.h"

extern "C" void func_ov104_0229ea40(int a);
extern "C" void func_ov104_0229ea38(int a);

int Obj_ov104_0229f6d0::func_ov104_0229f040()
{
    int param = (int) this;
    func_ov104_0229ea40(param);
    ((Obj_ov104_0229f6d0 *) param)->func_ov104_0229f05c();
    func_ov104_0229ea38(param);
    return 1;
}
