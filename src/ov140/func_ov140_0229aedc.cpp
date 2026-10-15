/* func_ov140_0229aedc @ 0x0229aedc, 0xbc bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov140_0229b40419func_ov140_0229aedcEv
 */

#include "cpp/ov140/Obj_ov140_0229b404.h"

typedef void (Obj_ov140_0229b404::*PMF)();

#define STATE_func_ov140_0229a894 (PMF) & Obj_ov140_0229b404::func_ov140_0229a894

void Obj_ov140_0229b404::func_ov140_0229aedc()
{
    static PMF table[8] = {&Obj_ov140_0229b404::func_ov140_0229aa4c, &Obj_ov140_0229b404::func_ov140_0229a9e4,
                           &Obj_ov140_0229b404::func_ov140_0229a9b4, &Obj_ov140_0229b404::func_ov140_0229a914,
                           &Obj_ov140_0229b404::func_ov140_0229a8c0, STATE_func_ov140_0229a894,
                           &Obj_ov140_0229b404::func_ov140_0229a85c, &Obj_ov140_0229b404::func_ov140_0229a800};

    (this->*table[subState])();
}

#undef STATE_func_ov140_0229a894
