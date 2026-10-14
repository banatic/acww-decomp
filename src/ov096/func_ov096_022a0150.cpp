/* func_ov096_022a0150 @ 0x022a0150, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov096_022a23e819func_ov096_022a0150Ev
 */

#include "cpp/ov096/Obj_ov096_022a23e8.h"

extern "C" int func_ov002_02208e18(int *param1);

void Obj_ov096_022a23e8::func_ov096_022a0150()
{
    int *param1 = (int *) this;
    int *r4 = param1;
    if (func_ov002_02208e18(r4 + 0x959)) {
        ((Obj_ov096_022a23e8 *) r4)->func_ov096_0229d268();
    }
}
