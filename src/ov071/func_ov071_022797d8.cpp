/* func_ov071_022797d8 @ 0x022797d8, 0x80 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov071_0227a27819func_ov071_022797d8Ev
 */

#include "cpp/ov071/Obj_ov071_0227a278.h"

typedef void (Obj_ov071_0227a278::*PMF)();

int Obj_ov071_0227a278::func_ov071_022797d8()
{
    static PMF pf[3] = {&Obj_ov071_0227a278::func_ov071_02279a78, &Obj_ov071_0227a278::func_ov071_022799c0,
                        &Obj_ov071_0227a278::func_ov071_022798f8};
    unsigned char idx = unk_729;
    if (idx < 3) {
        (this->*pf[idx])();
    }
    return 0;
}
