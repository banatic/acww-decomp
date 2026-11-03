/* carried_letters_12: 2 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229dd60 @ 0x0229dd60, 0x1b4 bytes, Thumb, emits _ZN18Obj_ov103_0229e2e019func_ov103_0229dd60Ev
 * func_ov103_0229dd44 @ 0x0229dd44, 0x1c bytes, Thumb, emits _ZN18Obj_ov103_0229e2e019func_ov103_0229dd44Ev
 */

#include "cpp/ov103/Obj_ov103_0229e2e0.h"

typedef void (Obj_ov103_0229e2e0::*PMF)();

extern "C" void func_ov103_0229d944(int);
extern "C" void func_ov103_0229d93c(int);

void Obj_ov103_0229e2e0::func_ov103_0229dd60()
{
    static PMF table[25] = {&Obj_ov103_0229e2e0::func_ov103_0229d82c, &Obj_ov103_0229e2e0::func_ov103_0229d7bc,
                            &Obj_ov103_0229e2e0::func_ov103_0229d724, &Obj_ov103_0229e2e0::func_ov103_0229d6f0,
                            &Obj_ov103_0229e2e0::func_ov103_0229d664, &Obj_ov103_0229e2e0::func_ov103_0229d580,
                            &Obj_ov103_0229e2e0::func_ov103_0229d4e4, &Obj_ov103_0229e2e0::func_ov103_0229d450,
                            &Obj_ov103_0229e2e0::func_ov103_0229d430, &Obj_ov103_0229e2e0::func_ov103_0229d3b4,
                            &Obj_ov103_0229e2e0::func_ov103_0229d364, &Obj_ov103_0229e2e0::func_ov103_0229d318,
                            &Obj_ov103_0229e2e0::func_ov103_0229d2f8, &Obj_ov103_0229e2e0::func_ov103_0229d2d0,
                            &Obj_ov103_0229e2e0::func_ov103_0229d2a0, &Obj_ov103_0229e2e0::func_ov103_0229d270,
                            &Obj_ov103_0229e2e0::func_ov103_0229d21c, &Obj_ov103_0229e2e0::func_ov103_0229d1d4,
                            &Obj_ov103_0229e2e0::func_ov103_0229d190, &Obj_ov103_0229e2e0::func_ov103_0229d158,
                            &Obj_ov103_0229e2e0::func_ov103_0229d11c, &Obj_ov103_0229e2e0::func_ov103_0229d0d8,
                            &Obj_ov103_0229e2e0::func_ov103_0229d0b8, &Obj_ov103_0229e2e0::func_ov103_0229d080,
                            &Obj_ov103_0229e2e0::func_ov103_0229d018};
    (this->*table[subState])();
}

int Obj_ov103_0229e2e0::func_ov103_0229dd44()
{
    int param = (int) this;
    func_ov103_0229d944(param);
    ((Obj_ov103_0229e2e0 *) param)->func_ov103_0229dd60();
    func_ov103_0229d93c(param);
    return 1;
}
