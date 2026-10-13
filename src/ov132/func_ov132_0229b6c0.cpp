/* func_ov132_0229b6c0 @ 0x0229b6c0, 0xbc bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov132_0229b99019func_ov132_0229b6c0Ev
 */

#include "cpp/ov132/Obj_ov132_0229b990.h"

typedef void (Obj_ov132_0229b990::*PMF)();

void Obj_ov132_0229b990::func_ov132_0229b6c0()
{
    static PMF table[8] = {&Obj_ov132_0229b990::func_ov132_0229b340, &Obj_ov132_0229b990::func_ov132_0229b2a4,
                           &Obj_ov132_0229b990::func_ov132_0229b27c, &Obj_ov132_0229b990::func_ov132_0229b23c,
                           &Obj_ov132_0229b990::func_ov132_0229b214, &Obj_ov132_0229b990::func_ov132_0229b1b0,
                           &Obj_ov132_0229b990::func_ov132_0229b184, &Obj_ov132_0229b990::func_ov132_0229b158};
    (this->*table[subState])();
}
