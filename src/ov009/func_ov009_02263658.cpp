/* func_ov009_02263658 @ 0x02263658, 0x3c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263658Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" int func_02096168(void *);
extern "C" int func_ov009_02264c90(void *);
extern "C" void func_0203aec4(int);

void Obj_ov009_022658dc::func_ov009_02263658()
{
    void *arg = (void *) this;
    if (func_02096168(arg)) {
        int res = func_ov009_02264c90(arg);
        switch (res) {
            case 2:
                func_0203aec4(res);
                ((Obj_ov009_022658dc *) arg)->func_ov009_022639a0(6);
                break;
            case 3:
                func_0203aec4(res);
                ((Obj_ov009_022658dc *) arg)->func_ov009_022639a0(6);
                break;
        }
    }
}
