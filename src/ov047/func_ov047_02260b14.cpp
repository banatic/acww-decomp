/* func_ov047_02260b14 @ 0x02260b14, 0x88 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov047_02262c1419func_ov047_02260b14Ei
 */

#include "cpp/ov047/Obj_ov047_02262c14.h"

typedef void (Obj_ov047_02262c14::*PMF)(int);

extern "C" int func_020a12e8(void);
extern "C" void func_020984e8(void);
extern "C" void func_02099640(void);

void Obj_ov047_02262c14::func_ov047_02260b14(int arg)
{
    if (func_020a12e8()) {
        return;
    }
    static PMF arr[2] = {&Obj_ov047_02262c14::func_ov047_022608f8, &Obj_ov047_02262c14::func_ov047_02260a88};
    int idx = 0;
    func_020984e8();
    func_02099640();
    if (unk_B0 == 1) {
        idx = 1;
    }
    (this->*arr[idx])(arg);
}
