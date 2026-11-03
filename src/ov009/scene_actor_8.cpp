/* scene_actor_8: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02263a80 @ 0x02263a80, 0x12 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02263a80Ev
 * func_ov009_022639a0 @ 0x022639a0, 0xe0 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_022639a0Ei
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

typedef int (Obj_ov009_022658dc::*PMF)();

void Obj_ov009_022658dc::func_ov009_02263a80()
{
    vfunc_6c(0);
}

int Obj_ov009_022658dc::func_ov009_022639a0(int state)
{
    static PMF table[9] = {
        &Obj_ov009_022658dc::func_ov009_022638cc, &Obj_ov009_022658dc::func_ov009_02263888,
        &Obj_ov009_022658dc::func_ov009_022637bc, &Obj_ov009_022658dc::func_ov009_0226378c,
        &Obj_ov009_022658dc::func_ov009_02263734, &Obj_ov009_022658dc::func_ov009_02263694,
        &Obj_ov009_022658dc::func_ov009_02263648, &Obj_ov009_022658dc::func_ov009_02263568,
        &Obj_ov009_022658dc::func_ov009_02263548,
    };
    if (state < 9) {
        if ((this->*table[state])()) {
            state_27c = state;
            return 1;
        }
    }
    return 0;
}
