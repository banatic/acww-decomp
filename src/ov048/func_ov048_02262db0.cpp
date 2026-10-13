/* func_ov048_02262db0 @ 0x02262db0, 0xb8 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov048_0226429819func_ov048_02262db0Ev
 */

#include "cpp/ov048/Obj_ov048_02264298.h"

int Obj_ov048_02264298::func_ov048_02262db0()
{
    static int (Obj_ov048_02264298::*table[6])() = {
        &Obj_ov048_02264298::func_ov048_02263238, &Obj_ov048_02264298::func_ov048_022631cc,
        &Obj_ov048_02264298::func_ov048_02263174, &Obj_ov048_02264298::func_ov048_02263084,
        &Obj_ov048_02264298::func_ov048_02262f58, &Obj_ov048_02264298::func_ov048_02262e94};
    if (unk_E71 < 6) {
        if ((this->*table[unk_E71])()) {
            unk_E71++;
        }
    }
    return 1;
}
