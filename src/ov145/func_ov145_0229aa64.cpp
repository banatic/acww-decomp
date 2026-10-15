/* func_ov145_0229aa64 @ 0x0229aa64, 0xd8 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov145_0229ae0019func_ov145_0229aa64Ev
 */

#include "cpp/ov145/Obj_ov145_0229ae00.h"

typedef void (Obj_ov145_0229ae00::*PMF)();

#define STATE_func_ov145_0229a57c (PMF) & Obj_ov145_0229ae00::func_ov145_0229a57c

void Obj_ov145_0229ae00::func_ov145_0229aa64()
{
    static PMF table[10] = {&Obj_ov145_0229ae00::func_ov145_0229a5b0, STATE_func_ov145_0229a57c,
                            &Obj_ov145_0229ae00::func_ov145_0229a548, &Obj_ov145_0229ae00::func_ov145_0229a4e4,
                            &Obj_ov145_0229ae00::func_ov145_0229a498, &Obj_ov145_0229ae00::func_ov145_0229a458,
                            &Obj_ov145_0229ae00::func_ov145_0229a430, &Obj_ov145_0229ae00::func_ov145_0229a3fc,
                            &Obj_ov145_0229ae00::func_ov145_0229a3d8, &Obj_ov145_0229ae00::func_ov145_0229a370};

    (this->*table[subState])();
}

#undef STATE_func_ov145_0229a57c
