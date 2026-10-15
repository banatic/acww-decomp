/* func_ov116_0229e5bc @ 0x0229e5bc, 0x2a bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov116_0229e8b819func_ov116_0229e5bcEv
 */

#include "cpp/ov116/Obj_ov116_0229e8b8.h"

extern "C" int func_ov116_0229e50c(void *arg0);
extern "C" void func_ov116_0229e354(int);
extern "C" void func_ov116_0229e34c(int);

int Obj_ov116_0229e8b8::func_ov116_0229e5bc()
{
    int r0 = (int) this;
    int r4 = r0;
    if (func_ov116_0229e50c((void *) this) != 0) {
        return 1;
    }
    func_ov116_0229e354(r4);
    ((Obj_ov116_0229e8b8 *) r4)->func_ov116_0229e5e8();
    func_ov116_0229e34c(r4);
    return 1;
}
