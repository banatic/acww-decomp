/* star_view_3: 3 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229c700 @ 0x0229c700, 0x94 bytes, Thumb, emits _ZN18Obj_ov128_0229cbc019func_ov128_0229c700Ev
 * func_ov128_0229c618 @ 0x0229c618, 0xe8 bytes, Thumb, emits _ZN18Obj_ov128_0229cbc019func_ov128_0229c618Ev
 * func_ov128_0229c5fc @ 0x0229c5fc, 0x1c bytes, Thumb, emits _ZN18Obj_ov128_0229cbc019func_ov128_0229c5fcEv
 */

#include "cpp/ov128/Obj_ov128_0229cbc0.h"

typedef void (Obj_ov128_0229cbc0::*PMF)();

extern "C" {
void func_ov128_0229c390(void *argument0);
void func_ov128_0229c37c(int);
}

int Obj_ov128_0229cbc0::func_ov128_0229c700()
{
    static PMF table[4] = {&Obj_ov128_0229cbc0::func_ov128_0229c58c, &Obj_ov128_0229cbc0::func_ov128_0229c554,
                           &Obj_ov128_0229cbc0::func_ov128_0229c50c, &Obj_ov128_0229cbc0::func_ov128_0229c4d0};
    func_ov128_0229c350();
    (this->*table[state])();
    func_ov128_0229c334();
    return 1;
}

void Obj_ov128_0229cbc0::func_ov128_0229c618()
{
    static void (Obj_ov128_0229cbc0::*tbl[11])() = {
        &Obj_ov128_0229cbc0::func_ov128_0229c208, &Obj_ov128_0229cbc0::func_ov128_0229c1bc,
        &Obj_ov128_0229cbc0::func_ov128_0229c144, &Obj_ov128_0229cbc0::func_ov128_0229bff0,
        &Obj_ov128_0229cbc0::func_ov128_0229bf80, &Obj_ov128_0229cbc0::func_ov128_0229bf34,
        &Obj_ov128_0229cbc0::func_ov128_0229bf0c, &Obj_ov128_0229cbc0::func_ov128_0229bedc,
        &Obj_ov128_0229cbc0::func_ov128_0229bea8, &Obj_ov128_0229cbc0::func_ov128_0229be78,
        &Obj_ov128_0229cbc0::func_ov128_0229be5c};
    (this->*tbl[subState])();
}

int Obj_ov128_0229cbc0::func_ov128_0229c5fc()
{
    int param1 = (int) this;
    func_ov128_0229c390((void *) this);
    ((Obj_ov128_0229cbc0 *) param1)->func_ov128_0229c618();
    func_ov128_0229c37c(param1);
    return 1;
}
