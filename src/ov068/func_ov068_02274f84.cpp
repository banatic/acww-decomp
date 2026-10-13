/* func_ov068_02274f84 @ 0x02274f84, 0x8c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_02277f3c19func_ov068_02274f84Ej
 */

#include "cpp/ov068/Obj_ov068_02277f3c.h"

extern "C" int func_ov004_0222c558(void *, unsigned int);

typedef int (Obj_ov068_02277f3c::*PMF)();

int Obj_ov068_02277f3c::func_ov068_02274f84(unsigned int mode)
{
    static PMF pmf[2] = {&Obj_ov068_02277f3c::func_ov068_02274f08, &Obj_ov068_02277f3c::func_ov068_02274eec};
    if (mode >= 2) {
        goto fail;
    }
    if ((this->*pmf[mode])() == 0) {
        goto fail;
    }
    if (func_ov004_0222c558(this, mode) == 0) {
        goto fail;
    }
    unk_24c = mode;
    return 1;
fail:
    return 0;
}
