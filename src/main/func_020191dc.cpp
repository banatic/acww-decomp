/* func_020191dc @ 0x020191dc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020191dcEi
 */

#include "cpp/main/Obj_020d8bd4.h"

typedef void (Obj_020d8bd4::*PMF)(int arg);

extern int data_021c1548;
extern PMF data_020d86b4, data_020d8a64;
extern PMF data_021c15cc[2];

void Obj_020d8bd4::func_020191dc(int arg)
{
    if (!(data_021c1548 & 1)) {
        data_021c15cc[0] = data_020d86b4;
        data_021c15cc[1] = data_020d8a64;
        data_021c1548 |= 1;
    }
    unsigned char n = unk_98;
    if (n < 2) {
        (this->*data_021c15cc[n])(arg);
    }
}
