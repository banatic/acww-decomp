/* pockets_pick_7: 4 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229ddf4 @ 0x0229ddf4, 0xa0 bytes, Thumb
 * func_ov101_0229dd54 @ 0x0229dd54, 0xa0 bytes, Thumb, emits _ZN18Obj_ov101_0229e07819func_ov101_0229dd54Ev
 * func_ov101_0229dbb0 @ 0x0229dbb0, 0x1a4 bytes, Thumb, emits _ZN18Obj_ov101_0229e07819func_ov101_0229dbb0Ev
 * func_ov101_0229db94 @ 0x0229db94, 0x1c bytes, Thumb, emits _ZN18Obj_ov101_0229e07819func_ov101_0229db94Ev
 */

#include "cpp/ov101/Obj_ov101_0229e078.h"

extern "C" void func_ov002_0220919c(void *);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);
extern "C" int func_ov101_0229c2ac(void *, int);
extern "C" void func_ov002_0220ad18(void *, void *);
extern "C" void func_ov094_0229a850(void *, int, int);
extern "C" void func_ov094_0229b738(void *, int, int);
extern "C" void func_ov094_02299d84(void *receiver, int value);
extern "C" void func_ov101_0229d8e0(Obj_ov101_0229e078 *self);
extern "C" void func_ov101_0229d8a8(Obj_ov101_0229e078 *self);

typedef void (Obj_ov101_0229e078::*PMF)();

extern "C" void func_ov101_0229d924(void *);
extern "C" void func_ov101_0229d91c(void *);

extern "C" int func_ov101_0229ddf4(unsigned char *self)
{
    func_ov002_0220919c(self + 0x2300);
    if (func_ov101_0229c2ac(self, 1) == 0) {
        return 1;
    }

    (*(int (**)(void *))((char *) *(void **) (self + 0x21b4) + 8))(self + 0x21b4);
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x229c);
    }

    if (func_ov101_0229c2ac(self, 2) != 0) {
        func_ov002_0220ad18(self + 0x2810, *(void **) (self + 0x98));
        int n = *(int *) (self + 0x98) - 0x10;
        func_ov094_0229a850(self + 0xf4, 0, n);
        func_ov094_0229b738(self + 0xb54, 0, n);
        {
            void *hook_object = (void *) (self + 0xb7c);
            int hook_value = (int) (n);
            func_ov094_02299d84(hook_object, hook_value);
        }
    }
    return 1;
}

int Obj_ov101_0229e078::func_ov101_0229dd54()
{
    static void (Obj_ov101_0229e078::*tbl[5])() = {
        &Obj_ov101_0229e078::func_ov101_0229db60, &Obj_ov101_0229e078::func_ov101_0229dad4,
        &Obj_ov101_0229e078::func_ov101_0229da98, &Obj_ov101_0229e078::func_ov101_0229da38,
        &Obj_ov101_0229e078::func_ov101_0229d9ec};

    func_ov101_0229d8e0(this);
    (this->*tbl[state])();
    func_ov101_0229d8a8(this);

    return 1;
}

void Obj_ov101_0229e078::func_ov101_0229dbb0()
{
    static struct {
        PMF a[16];
        PMF b[8];
    } table = {{&Obj_ov101_0229e078::func_ov101_0229d7c0, &Obj_ov101_0229e078::func_ov101_0229d720,
                &Obj_ov101_0229e078::func_ov101_0229d704, &Obj_ov101_0229e078::func_ov101_0229d6bc,
                &Obj_ov101_0229e078::func_ov101_0229d624, &Obj_ov101_0229e078::func_ov101_0229d5a8,
                &Obj_ov101_0229e078::func_ov101_0229d4b4, &Obj_ov101_0229e078::func_ov101_0229d410,
                &Obj_ov101_0229e078::func_ov101_0229d398, &Obj_ov101_0229e078::func_ov101_0229d34c,
                &Obj_ov101_0229e078::func_ov101_0229d2fc, &Obj_ov101_0229e078::func_ov101_0229d2c4,
                &Obj_ov101_0229e078::func_ov101_0229d29c, &Obj_ov101_0229e078::func_ov101_0229d26c,
                &Obj_ov101_0229e078::func_ov101_0229d240, &Obj_ov101_0229e078::func_ov101_0229d1f0},
               {&Obj_ov101_0229e078::func_ov101_0229d1a8, &Obj_ov101_0229e078::func_ov101_0229d168,
                &Obj_ov101_0229e078::func_ov101_0229d134, &Obj_ov101_0229e078::func_ov101_0229d0f8,
                &Obj_ov101_0229e078::func_ov101_0229d0a8, &Obj_ov101_0229e078::func_ov101_0229d088,
                &Obj_ov101_0229e078::func_ov101_0229d054, &Obj_ov101_0229e078::func_ov101_0229cff0}};
    (this->*table.a[subState])();
}

int Obj_ov101_0229e078::func_ov101_0229db94()
{
    void *arg = (void *) this;
    func_ov101_0229d924(arg);
    ((Obj_ov101_0229e078 *) arg)->func_ov101_0229dbb0();
    func_ov101_0229d91c(arg);
    return 1;
}
