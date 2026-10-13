/* func_ov102_0229e6e4 @ 0x0229e6e4, 0xe8 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov102_0229ea6019func_ov102_0229e6e4Ev
 */

#include "cpp/ov102/Obj_ov102_0229ea60.h"

typedef void (Obj_ov102_0229ea60::*PMF)();

int Obj_ov102_0229ea60::func_ov102_0229e6e4()
{
    static PMF table[10] = {&Obj_ov102_0229ea60::func_ov102_0229e4d8, &Obj_ov102_0229ea60::func_ov102_0229e458,
                            &Obj_ov102_0229ea60::func_ov102_0229e410, &Obj_ov102_0229ea60::func_ov102_0229e380,
                            &Obj_ov102_0229ea60::func_ov102_0229e308, &Obj_ov102_0229ea60::func_ov102_0229e29c,
                            &Obj_ov102_0229ea60::func_ov102_0229e24c, &Obj_ov102_0229ea60::func_ov102_0229e224,
                            &Obj_ov102_0229ea60::func_ov102_0229e1cc, &Obj_ov102_0229ea60::func_ov102_0229e1c4};
    func_ov102_0229e0b0();
    (this->*table[state])();
    func_ov102_0229e084();
    return 1;
}
