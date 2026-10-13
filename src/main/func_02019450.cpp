/* func_02019450 @ 0x02019450, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02019450Ei
 */

#include "cpp/main/Obj_020d8bd4.h"

typedef void (Obj_020d8bd4::*PMF)(int arg);

void Obj_020d8bd4::func_02019450(int arg)
{
    static PMF table[2] = {&Obj_020d8bd4::func_020194c8, &Obj_020d8bd4::func_020194c0};
    unsigned char n = unk_98;
    if (n < 2) {
        (this->*table[n])(arg);
    }
}
