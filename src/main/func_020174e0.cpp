/* func_020174e0 @ 0x020174e0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_020174e0Ei
 */

#include "cpp/main/Obj_020d8bd4.h"

typedef void (Obj_020d8bd4::*PMF)(int arg);

extern int data_021c151c;
extern PMF data_020d8774, data_020d8814;
extern PMF data_021c162c[2];

void Obj_020d8bd4::func_020174e0(int arg)
{
    if (!(data_021c151c & 1)) {
        data_021c162c[0] = data_020d8814;
        data_021c162c[1] = data_020d8774;
        data_021c151c |= 1;
    }
    unsigned char n = unk_98;
    if (n < 2) {
        (this->*data_021c162c[n])(arg);
    }
}
