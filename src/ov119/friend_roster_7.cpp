/* friend_roster_7: 2 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c75c @ 0x0229c75c, 0x150 bytes, Thumb, emits _ZN18Obj_ov119_0229cea019func_ov119_0229c75cEv
 * func_ov119_0229c730 @ 0x0229c730, 0x2a bytes, Thumb, emits _ZN18Obj_ov119_0229cea019func_ov119_0229c730Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" int func_ov119_0229c648(void *arg0);
extern "C" void func_ov119_0229c2e4(int);
extern "C" void func_ov119_0229c2dc(int);

void Obj_ov119_0229cea0::func_ov119_0229c75c()
{
    static void (Obj_ov119_0229cea0::*table[18])() = {
        &Obj_ov119_0229cea0::func_ov119_0229c13c, &Obj_ov119_0229cea0::func_ov119_0229c090,
        &Obj_ov119_0229cea0::func_ov119_0229c008, &Obj_ov119_0229cea0::func_ov119_0229bfdc,
        &Obj_ov119_0229cea0::func_ov119_0229bfa4, &Obj_ov119_0229cea0::func_ov119_0229bf7c,
        &Obj_ov119_0229cea0::func_ov119_0229bee0, &Obj_ov119_0229cea0::func_ov119_0229be8c,
        &Obj_ov119_0229cea0::func_ov119_0229be50, &Obj_ov119_0229cea0::func_ov119_0229bdf0,
        &Obj_ov119_0229cea0::func_ov119_0229bdbc, &Obj_ov119_0229cea0::func_ov119_0229bd80,
        &Obj_ov119_0229cea0::func_ov119_0229bd64, &Obj_ov119_0229cea0::func_ov119_0229bd40,
        &Obj_ov119_0229cea0::func_ov119_0229bcf8, &Obj_ov119_0229cea0::func_ov119_0229bcb0,
        &Obj_ov119_0229cea0::func_ov119_0229bc74, &Obj_ov119_0229cea0::func_ov119_0229bc48};
    int n = subState;
    (this->*table[n])();
}

int Obj_ov119_0229cea0::func_ov119_0229c730()
{
    int r0 = (int) this;
    int r4 = r0;
    if (func_ov119_0229c648((void *) this) != 0) {
        return 1;
    }
    func_ov119_0229c2e4(r4);
    ((Obj_ov119_0229cea0 *) r4)->func_ov119_0229c75c();
    func_ov119_0229c2dc(r4);
    return 1;
}
