/* func_02018610 @ 0x02018610, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_02018610Ei
 */

#include "cpp/main/Obj_020d8bd4.h"

extern int data_021c14ec;
extern void (Obj_020d8bd4::*data_020d85dc)(int);
extern void (Obj_020d8bd4::*data_020d860c)(int);
extern void (Obj_020d8bd4::*data_020d890c)(int);
extern void (Obj_020d8bd4::*data_020d8914)(int);
extern void (Obj_020d8bd4::*data_020d891c)(int);
extern void (Obj_020d8bd4::*data_021c176c[5])(int);

void Obj_020d8bd4::func_02018610(int arg)
{
    if (!(data_021c14ec & 1)) {
        data_021c176c[0] = data_020d891c;
        data_021c176c[1] = data_020d8914;
        data_021c176c[2] = data_020d890c;
        data_021c176c[3] = data_020d860c;
        data_021c176c[4] = data_020d85dc;
        data_021c14ec |= 1;
    }
    if (unk_98 < 5) {
        (this->*data_021c176c[unk_98])(arg);
    }
}
