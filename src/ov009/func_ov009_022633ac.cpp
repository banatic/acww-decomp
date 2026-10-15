/* func_ov009_022633ac @ 0x022633ac, 0x64 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_022633acEji
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" {
void func_020b23ec(unsigned short a, int b);
void func_020b23c8(void);
int func_020b5e10(void);
void func_020b5e90(void);
}

void Obj_ov009_022658dc::func_ov009_022633ac(unsigned int event, int arg)
{
    switch (event) {
        case 6:
            func_020b23ec(unk_136, 0);
            func_020b23c8();
            func_020b5e10();
            func_020b5e90();
            *((unsigned char *) this + 0x234) = 1;
            break;
        case 0:
        case 1:
            func_ov009_022639a0(1);
            break;
        case 8:
            func_ov009_022639a0(0);
            break;
        default:
            break;
    }
}
