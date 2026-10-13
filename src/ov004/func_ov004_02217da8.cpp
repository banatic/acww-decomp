/* func_ov004_02217da8 @ 0x02217da8, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02217da8 {
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

extern "C" void *func_ov004_0223cb10(UnkStruct_02217da8 *self);
extern "C" void *func_ov004_0223ca9c(void *a, UnkStruct_02217da8 *self);
extern "C" u16 func_ov004_0223cb18(void *h);
extern "C" char *func_ov004_0223cb28(void *h);
extern "C" int func_ov004_0222c14c(char *a, char *b, u16 *t, s16 d, int e);

extern "C" void func_ov004_02217da8(UnkStruct_02217da8 *self)
{
    u16 t;
    void *h;
    char *a;

    h = func_ov004_0223ca9c(func_ov004_0223cb10(self), self);
    t = func_ov004_0223cb18(h);
    a = func_ov004_0223cb28(h);
    if (func_ov004_0222c14c(a, func_ov004_0223cb28(h) + 8, &t, (s16) (*(s16 *) ((char *) self + 0x8e) - 0x4000), 1)) {
        self->s28(3, 0xff);
    }
}
