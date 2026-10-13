/* func_ov003_02219f88 @ 0x02219f88, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_022382ac19func_ov003_02219f88Ev
 */

#include "cpp/ov003/Obj_ov003_022382ac.h"

typedef void (Obj_ov003_022382ac::*PMF)();

void Obj_ov003_022382ac::func_ov003_02219f88()
{
    static PMF arr[3] = {&Obj_ov003_022382ac::func_ov003_02219f80, &Obj_ov003_022382ac::func_ov003_02219e98,
                         &Obj_ov003_022382ac::func_ov003_02219e64};
    int idx = state_3a0;
    if (idx < 3) {
        (this->*arr[idx])();
    }
}
