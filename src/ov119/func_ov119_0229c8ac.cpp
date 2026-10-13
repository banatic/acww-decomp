/* func_ov119_0229c8ac @ 0x0229c8ac, 0xa0 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229c8acEv
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" void func_ov119_0229c318(Obj_ov119_0229cea0 *self);
extern "C" void func_ov119_0229c300(Obj_ov119_0229cea0 *self);

int Obj_ov119_0229cea0::func_ov119_0229c8ac()
{
    static void (Obj_ov119_0229cea0::*table[5])(void) = {
        &Obj_ov119_0229cea0::func_ov119_0229c598, &Obj_ov119_0229cea0::func_ov119_0229c534,
        &Obj_ov119_0229cea0::func_ov119_0229c4d4, &Obj_ov119_0229cea0::func_ov119_0229c488,
        &Obj_ov119_0229cea0::func_ov119_0229c434};
    func_ov119_0229c318(this);
    unsigned char idx = state;
    (this->*table[idx])();
    func_ov119_0229c300(this);
    return 1;
}
