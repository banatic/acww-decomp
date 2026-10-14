/* func_ov003_0221be34 @ 0x0221be34, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221be34Ev
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

extern "C" int func_020b2470(int);

void Obj_ov003_02238630::func_ov003_0221be34()
{
    int state = func_020b2470(unk_136);
    if (state != 0) {
        int flag;
        if (state == 2) {
            flag = 1;
        } else {
            flag = 0;
        }
        // the ROM rewrites the byte, not the bit
        unsigned char *flags = (unsigned char *) this + 0x236;
        unsigned int v = *flags;
        v &= ~2;
        v |= (flag & 1) << 1;
        *flags = (unsigned char) v;
        func_ov003_0221bfa8(2);
    }
}
