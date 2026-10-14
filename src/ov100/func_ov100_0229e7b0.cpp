/* func_ov100_0229e7b0 @ 0x0229e7b0, 0x1c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov100_0229ecb819func_ov100_0229e7b0Ev
 */

#include "cpp/ov100/Obj_ov100_0229ecb8.h"

extern "C" void func_ov100_0229e3b0(void *);
extern "C" void func_ov100_0229e3a8(void *);

int Obj_ov100_0229ecb8::func_ov100_0229e7b0()
{
    void *p = (void *) this;
    func_ov100_0229e3b0(p);
    ((Obj_ov100_0229ecb8 *) p)->func_ov100_0229e7cc();
    func_ov100_0229e3a8(p);
    return 1;
}
