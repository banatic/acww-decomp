/* func_ov147_02299fc8 @ 0x02299fc8, 0x38 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov147_0229aa2819func_ov147_02299fc8Ei
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"

struct PMFEntry {
    void (Obj_ov147_0229aa28::*pmf)();
    int pad_08[2];
};

extern PMFEntry data_ov147_0229ad4c[];

void Obj_ov147_0229aa28::func_ov147_02299fc8(int index)
{
    if (data_ov147_0229ad4c[index].pmf != 0) {
        (this->*data_ov147_0229ad4c[index].pmf)();
    }
    unk_50 = index;
}
