/* func_ov121_0229bdc0 @ 0x0229bdc0, 0x178 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov121_0229c3a819func_ov121_0229bdc0Ev
 */

#include "cpp/ov121/Obj_ov121_0229c3a8.h"

typedef Obj_ov121_0229c3a8 S;
typedef void (S::*PMF)();

void Obj_ov121_0229c3a8::func_ov121_0229bdc0()
{
    static PMF tbl[21] = {&S::func_ov121_0229b764, &S::func_ov121_0229b6f0, &S::func_ov121_0229b64c, &S::func_ov121_0229b574,
                          &S::func_ov121_0229b484, &S::func_ov121_0229b40c, &S::func_ov121_0229b3e0, &S::func_ov121_0229b3a4,
                          &S::func_ov121_0229b37c, &S::func_ov121_0229b340, &S::func_ov121_0229b31c, &S::func_ov121_0229b2a4,
                          &S::func_ov121_0229b214, &S::func_ov121_0229b184, &S::func_ov121_0229b148, &S::func_ov121_0229b104,
                          &S::func_ov121_0229b0e4, &S::func_ov121_0229b0bc, &S::func_ov121_0229b09c, &S::func_ov121_0229b078,
                          &S::func_ov121_0229b020};
    unsigned char idx = subState;
    (this->*tbl[idx])();
}
