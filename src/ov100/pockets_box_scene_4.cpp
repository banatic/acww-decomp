/* pockets_box_scene_4: 2 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229ea10 @ 0x0229ea10, 0xa0 bytes, Thumb
 * func_ov100_0229e954 @ 0x0229e954, 0xbc bytes, Thumb, emits _ZN18Obj_ov100_0229ecb819func_ov100_0229e954Ev
 */

#include "types.h"
#include "cpp/ov100/Obj_ov100_0229ecb8.h"

extern "C" int func_ov100_0229c2c0(void *self, int mode);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *ptr);
extern "C" void func_ov100_0229ce90(void *self);
extern "C" void func_ov094_0229a7cc(void *ptr, int a, int b);
extern "C" void func_ov094_0229a850(void *ptr, int a, int b);
extern "C" void func_ov094_0229b738(void *ptr, int a, int b);
extern "C" void func_ov094_02299d84(void *receiver, int value);

class VtblClass {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

extern "C" void func_ov100_0229e374(Obj_ov100_0229ecb8 *);
extern "C" void func_ov100_0229e33c(Obj_ov100_0229ecb8 *);

extern "C" int func_ov100_0229ea10(void *self)
{
    if (func_ov100_0229c2c0(self, 1) == 0) {
        return 1;
    }

    if (((void) (((VtblClass *) ((char *) self + 0x218c))->f2()), func_0206fe54()) != 0) {
        func_ov002_02209eb8((char *) self + 0x2274);
    }

    func_ov100_0229ce90(self);

    if (func_ov100_0229c2c0(self, 0x80)) {
        func_ov094_0229a7cc((char *) self + 0xcc, 0, *(u32 *) ((char *) self + 0x28c8));
    }

    if (func_ov100_0229c2c0(self, 2)) {
        func_ov094_0229a850((char *) self + 0xcc, 0, *(u32 *) ((char *) self + 0x28c4));
        func_ov094_0229b738((char *) self + 0xb2c, 0, *(u32 *) ((char *) self + 0x28c4));
        func_ov094_02299d84((char *) self + 0xb54, *(u32 *) ((char *) self + 0x28c4));
    }

    return 1;
}

int Obj_ov100_0229ecb8::func_ov100_0229e954()
{
    static void (Obj_ov100_0229ecb8::*table[7])() = {
        &Obj_ov100_0229ecb8::func_ov100_0229e77c, &Obj_ov100_0229ecb8::func_ov100_0229e6ec,
        &Obj_ov100_0229ecb8::func_ov100_0229e668, &Obj_ov100_0229ecb8::func_ov100_0229e62c,
        &Obj_ov100_0229ecb8::func_ov100_0229e5b8, &Obj_ov100_0229ecb8::func_ov100_0229e54c,
        &Obj_ov100_0229ecb8::func_ov100_0229e4fc};
    func_ov100_0229e374(this);
    (this->*table[state])();
    func_ov100_0229e33c(this);
    return 1;
}
