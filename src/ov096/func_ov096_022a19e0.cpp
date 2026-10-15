/* func_ov096_022a19e0 @ 0x022a19e0, 0x2a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov096_022a23e819func_ov096_022a19e0Ev
 */

#include "cpp/ov096/Obj_ov096_022a23e8.h"

extern "C" int func_ov096_022a192c(void *);
extern "C" void func_ov096_022a142c(void *);
extern "C" void func_ov096_022a1424(void *);

int Obj_ov096_022a23e8::func_ov096_022a19e0()
{
    void *p = (void *) this;
    if (func_ov096_022a192c(p)) {
        return 1;
    }
    func_ov096_022a142c(p);
    ((Obj_ov096_022a23e8 *) p)->func_ov096_022a1a0c();
    func_ov096_022a1424(p);
    return 1;
}
