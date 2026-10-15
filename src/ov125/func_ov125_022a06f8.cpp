/* func_ov125_022a06f8 @ 0x022a06f8, 0x1c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov125_022a0ab819func_ov125_022a06f8Ev
 */

#include "cpp/ov125/Obj_ov125_022a0ab8.h"

extern "C" void func_ov125_022a04c8(int arg);
extern "C" void func_ov125_022a04c0(int arg);

int Obj_ov125_022a0ab8::func_ov125_022a06f8()
{
    int arg = (int) this;
    func_ov125_022a04c8(arg);
    ((Obj_ov125_022a0ab8 *) arg)->func_ov125_022a0714();
    func_ov125_022a04c0(arg);
    return 1;
}
