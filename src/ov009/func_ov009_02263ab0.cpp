/* func_ov009_02263ab0 @ 0x02263ab0, 0x84 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" int func_0204bba8(void *);
extern "C" void func_02055124(Obj_020dd05c *);
extern "C" int func_02056f94(Obj_020dd184 *);
extern "C" void func_ov009_02262ef0(Obj_0213f090 *, int);

void Obj_ov009_022658dc::func_ov009_02263ab0()
{
    unsigned short tmp = unk_132;
    if (tmp != 0) {
        tmp--;
        unk_132 = tmp;
        if (unk_132 == 0) {
            if (func_0204bba8(&unk_136)) {
                func_ov009_02262ef0(&unk_238, 0x807);
            } else {
                func_ov009_02262ef0(&unk_238, 0x809);
            }
        }
    }
    if (unk_132 == 0) {
        func_02055124(&unk_13c);
        if (func_02056f94(static_cast<Obj_020dd184 *>(&unk_13c))) {
            vfunc_6c(0);
        }
    }
}
