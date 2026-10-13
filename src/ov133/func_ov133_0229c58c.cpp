/* func_ov133_0229c58c @ 0x0229c58c, 0xa0 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov133_0229c90819func_ov133_0229c58cEv
 */

#include "cpp/ov133/Obj_ov133_0229c908.h"

extern "C" {
void func_ov133_0229c158(void *self);
void func_ov133_0229c150(void *self);
}

typedef void (Obj_ov133_0229c908::*PMF)();

int Obj_ov133_0229c908::func_ov133_0229c58c()
{
    static PMF table[5] = {&Obj_ov133_0229c908::func_ov133_0229c39c, &Obj_ov133_0229c908::func_ov133_0229c340,
                           &Obj_ov133_0229c908::func_ov133_0229c2fc, &Obj_ov133_0229c908::func_ov133_0229c2b0,
                           &Obj_ov133_0229c908::func_ov133_0229c25c};
    func_ov133_0229c158(this);
    (this->*table[state])();
    func_ov133_0229c150(this);
    return 1;
}
