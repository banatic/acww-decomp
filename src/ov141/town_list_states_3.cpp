/* town_list_states_3: 3 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229ac60 @ 0x0229ac60, 0xa0 bytes, Thumb, emits _ZN18Obj_ov141_0229af4819func_ov141_0229ac60Ev
 * func_ov141_0229abc0 @ 0x0229abc0, 0xa0 bytes, Thumb, emits _ZN18Obj_ov141_0229af4819func_ov141_0229abc0Ev
 * func_ov141_0229aba4 @ 0x0229aba4, 0x1c bytes, Thumb, emits _ZN18Obj_ov141_0229af4819func_ov141_0229aba4Ev
 */

#include "cpp/ov141/Obj_ov141_0229af48.h"

extern "C" void func_ov141_0229a934(void *);
extern "C" void func_ov141_0229a91c(void *);
extern "C" void func_ov141_0229a968(int parameter);
extern "C" void func_ov141_0229a960(int parameter);

int Obj_ov141_0229af48::func_ov141_0229ac60()
{
    static void (Obj_ov141_0229af48::*table[5])() = {
        &Obj_ov141_0229af48::func_ov141_0229ab04, &Obj_ov141_0229af48::func_ov141_0229aac4,
        &Obj_ov141_0229af48::func_ov141_0229aa94, &Obj_ov141_0229af48::func_ov141_0229aa54,
        &Obj_ov141_0229af48::func_ov141_0229aa28};
    func_ov141_0229a934(this);
    (this->*table[state])();
    func_ov141_0229a91c(this);
    return 1;
}

void Obj_ov141_0229af48::func_ov141_0229abc0()
{
    static void (Obj_ov141_0229af48::*const tbl[6])(void) = {
        &Obj_ov141_0229af48::func_ov141_0229a774, &Obj_ov141_0229af48::func_ov141_0229a6e4,
        &Obj_ov141_0229af48::func_ov141_0229a6b4, &Obj_ov141_0229af48::func_ov141_0229a634,
        &Obj_ov141_0229af48::func_ov141_0229a5e0, &Obj_ov141_0229af48::func_ov141_0229a5b4};
    (this->*tbl[subState])();
}

int Obj_ov141_0229af48::func_ov141_0229aba4()
{
    int parameter = (int) this;
    func_ov141_0229a968(parameter);
    ((Obj_ov141_0229af48 *) parameter)->func_ov141_0229abc0();
    func_ov141_0229a960(parameter);
    return 1;
}
