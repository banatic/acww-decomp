/* func_ov115_0229e5bc @ 0x0229e5bc, 0x2a bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov115_0229e8b819func_ov115_0229e5bcEv
 */

#include "cpp/ov115/Obj_ov115_0229e8b8.h"

extern "C" int func_ov115_0229e50c(void);
extern "C" void func_ov115_0229e354(int);
extern "C" void func_ov115_0229e34c(int);

int Obj_ov115_0229e8b8::func_ov115_0229e5bc()
{
    int param = (int) this;
    if (func_ov115_0229e50c()) {
        return 1;
    }
    func_ov115_0229e354(param);
    ((Obj_ov115_0229e8b8 *) param)->func_ov115_0229e5e8();
    func_ov115_0229e34c(param);
    return 1;
}
