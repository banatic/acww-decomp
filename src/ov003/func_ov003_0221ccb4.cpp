/* func_ov003_0221ccb4 @ 0x0221ccb4, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_02238c5419func_ov003_0221ccb4Ej
 */

#include "cpp/ov003/Obj_ov003_02238c54.h"

extern "C" int func_020b30e8(unsigned short, int);

typedef int (Obj_ov003_02238c54::*PMF)();

int Obj_ov003_02238c54::func_ov003_0221ccb4(unsigned int mode)
{
    static PMF pmf[2] = {&Obj_ov003_02238c54::func_ov003_0221cc10, &Obj_ov003_02238c54::func_ov003_0221cb88};
    if (mode >= 3) {
        goto fail;
    }
    if ((this->*pmf[mode])() == 0) {
        goto fail;
    }
    if (func_020b30e8(unk_136, mode) == 0) {
        goto fail;
    }
    state_134 = mode;
    return 1;
fail:
    return 0;
}
