/* func_020191dc @ 0x020191dc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020191dcEi
 */

#include "cpp/main/Obj_020d8bd4.h"

typedef void (Obj_020d8bd4::*PMF)(int arg);

void Obj_020d8bd4::func_020191dc(int arg)
{
    static PMF table[2] = {&Obj_020d8bd4::func_02019304, &Obj_020d8bd4::func_0201924c};
    unsigned char n = unk_98;
    if (n < 2) {
        (this->*table[n])(arg);
    }
}
