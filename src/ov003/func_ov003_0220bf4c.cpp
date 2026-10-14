/* func_ov003_0220bf4c @ 0x0220bf4c, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223801019func_ov003_0220bf4cEv
 */

#include "cpp/ov003/Obj_ov003_02238010.h"

struct UnkInner {
    int unk_00;
    void *unk_04;
};

struct UnkOuter {
    char pad_00[0x12c];
    struct UnkInner *unk_12C;
};

void Obj_ov003_02238010::func_ov003_0220bf4c()
{
    struct UnkOuter *obj = (struct UnkOuter *) this;
    if (obj->unk_12C != 0 && obj->unk_12C->unk_04 != 0) {
        ((Obj_ov003_02238010 *) obj)->func_ov003_0220c064(2);
    }
}
