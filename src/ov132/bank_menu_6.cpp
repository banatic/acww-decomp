/* bank_menu_6: 3 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229b77c @ 0x0229b77c, 0x94 bytes, Thumb, emits _ZN18Obj_ov132_0229b99019func_ov132_0229b77cEv
 * func_ov132_0229b6c0 @ 0x0229b6c0, 0xbc bytes, Thumb, emits _ZN18Obj_ov132_0229b99019func_ov132_0229b6c0Ev
 * func_ov132_0229b6a4 @ 0x0229b6a4, 0x1c bytes, Thumb, emits _ZN18Obj_ov132_0229b99019func_ov132_0229b6a4Ev
 */

#include "cpp/ov132/Obj_ov132_0229b990.h"

extern "C" void func_ov132_0229b4fc(void *);
extern "C" void func_ov132_0229b4f8(void *);

typedef void (Obj_ov132_0229b990::*PMF)();

extern "C" void func_ov132_0229b51c(void *p);
extern "C" void func_ov132_0229b514(void *p);

int Obj_ov132_0229b990::func_ov132_0229b77c()
{
    static void (Obj_ov132_0229b990::*pmfs[4])() = {
        &Obj_ov132_0229b990::func_ov132_0229b630, &Obj_ov132_0229b990::func_ov132_0229b608,
        &Obj_ov132_0229b990::func_ov132_0229b5c8, &Obj_ov132_0229b990::func_ov132_0229b598};
    func_ov132_0229b4fc(this);
    (this->*pmfs[state])();
    func_ov132_0229b4f8(this);
    return 1;
}

void Obj_ov132_0229b990::func_ov132_0229b6c0()
{
    static PMF table[8] = {&Obj_ov132_0229b990::func_ov132_0229b340, &Obj_ov132_0229b990::func_ov132_0229b2a4,
                           &Obj_ov132_0229b990::func_ov132_0229b27c, &Obj_ov132_0229b990::func_ov132_0229b23c,
                           &Obj_ov132_0229b990::func_ov132_0229b214, &Obj_ov132_0229b990::func_ov132_0229b1b0,
                           &Obj_ov132_0229b990::func_ov132_0229b184, &Obj_ov132_0229b990::func_ov132_0229b158};
    (this->*table[subState])();
}

int Obj_ov132_0229b990::func_ov132_0229b6a4()
{
    void *p = (void *) this;
    func_ov132_0229b51c(p);
    ((Obj_ov132_0229b990 *) p)->func_ov132_0229b6c0();
    func_ov132_0229b514(p);
    return 1;
}
