/* func_ov132_0229b77c @ 0x0229b77c, 0x94 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov132_0229b99019func_ov132_0229b77cEv
 */

#include "cpp/ov132/Obj_ov132_0229b990.h"

extern "C" void func_ov132_0229b4fc(void *);
extern "C" void func_ov132_0229b4f8(void *);

int Obj_ov132_0229b990::func_ov132_0229b77c()
{
    static void (Obj_ov132_0229b990::*pmfs[4])() = {
        &Obj_ov132_0229b990::func_ov132_0229b630, &Obj_ov132_0229b990::func_ov132_0229b608,
        &Obj_ov132_0229b990::func_ov132_0229b5c8, &Obj_ov132_0229b990::func_ov132_0229b598};
    func_ov132_0229b4fc(this);
    (this->*pmfs[state])();
    func_ov132_0229b4f8(this);
    return 1;
}
