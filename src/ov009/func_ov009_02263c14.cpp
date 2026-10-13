/* func_ov009_02263c14 @ 0x02263c14, 0x70 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" void func_02055124(Obj_020dd05c *p);
extern "C" int func_02056f94(Obj_020dd184 *p);
extern "C" int func_02056f28(Obj_020dd184 *p, int n);
extern "C" void func_ov009_02262ef0(Obj_0213f090 *p, int n);

void Obj_ov009_022658dc::func_ov009_02263c14()
{
    func_02055124(&unk_13c);
    if (func_02056f94(static_cast<Obj_020dd184 *>(&unk_13c)) != 0) {
        vfunc_6c(0);
    } else {
        if (func_02056f28(static_cast<Obj_020dd184 *>(&unk_13c), 0x12) != 0) {
            func_ov009_02262ef0(&unk_238, 0x7d3);
        } else if (func_02056f28(static_cast<Obj_020dd184 *>(&unk_13c), 0x18) != 0) {
            func_ov009_02262ef0(&unk_238, 0x7d4);
        }
    }
}
