/* func_ov004_02217af4 @ 0x02217af4, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02217af4 {
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28(int a, int b);
};
extern "C" int func_0206fbc0(UnkStruct_02217af4 *self);
extern "C" int func_0206fc6c(void);
extern "C" int func_0206fc8c(void);
extern "C" int func_0209a034(int h);
extern "C" int func_020984e8(void);
extern "C" void func_020996bc(int r, void *p);
extern "C" int func_ov004_0220fde0(UnkStruct_02217af4 *self);
extern "C" int func_0204bc50(int a, int b);
extern "C" void func_0209a088(void *p, int a, int h);
extern "C" void func_0203ee08(UnkStruct_02217af4 *self, void *q);
extern "C" void func_0203e020(UnkStruct_02217af4 *self);

extern "C" void func_ov004_02217af4(UnkStruct_02217af4 *self)
{
    char *s = (char *) self;
    int h;
    int v;
    u16 t;
    if (func_0206fbc0(self) == 0) {
        return;
    }
    if (func_0206fc6c() == 0) {
        char *q = s;
        if (s != 0) {
            q = q + 0xec;
        }
        func_0203ee08(self, q);
        func_0203e020(self);
        return;
    }
    h = func_0206fc8c();
    *(u16 *) (s + 0x85c) = (u16) func_0209a034(h);
    v = func_020984e8();
    if (v != 0) {
        func_020996bc(v, s + 0x85c);
    }
    t = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    func_0209a088(&t, 0, h);
    self->s28(0xc, 0xff);
}
