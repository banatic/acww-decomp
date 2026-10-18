/* func_02019450 @ 0x02019450, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02019450Ei
 */

#include "cpp/main/Obj_020d8bd4.h"

typedef void (Obj_020d8bd4::*PMF)(int arg);

extern int data_021c1514;
extern PMF data_020d8a84, data_020d8a8c;
extern PMF data_021c15ac[2];

void Obj_020d8bd4::func_02019450(int arg)
{
    if (!(data_021c1514 & 1)) {
        data_021c15ac[0] = data_020d8a8c;
        data_021c15ac[1] = data_020d8a84;
        data_021c1514 |= 1;
    }
    unsigned char n = unk_98;
    if (n < 2) {
        (this->*data_021c15ac[n])(arg);
    }
}
