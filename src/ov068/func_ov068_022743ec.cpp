/* func_ov068_022743ec @ 0x022743ec, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_02277dc019func_ov068_022743ecEPv
 */

#include "cpp/ov068/Obj_ov068_02277dc0.h"

struct inner_022743ec {
    char pad_00[0x730];
    int value;
};

struct outer_022743ec {
    char pad_00[0xb4];
    struct inner_022743ec *inner;
};

void Obj_ov068_02277dc0::func_ov068_022743ec(void *b)
{
    struct outer_022743ec *a = (struct outer_022743ec *) this;
    if (a->inner->value == 7) {
        ((Obj_ov068_02277dc0 *) a)->func_ov068_02274358(b);
    }
}
