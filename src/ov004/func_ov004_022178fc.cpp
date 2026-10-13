/* func_ov004_022178fc @ 0x022178fc, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_022178fc {
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
extern "C" int func_0206837c(int h);
extern "C" void func_020ab670(int q, int a, int b);
extern "C" void func_020ab628(int q, int a, u8 *p, int b, u8 *c, int d, int e);
extern "C" void func_020ab5f8(int q);
extern "C" void func_02068388(int h, int a);
extern "C" u8 data_021f43e8;

extern "C" void func_ov004_022178fc(UnkStruct_022178fc *self)
{
    char *s = (char *) self;
    u8 buf[4];
    int h;
    int q;
    if (*(u8 *) (s + 0x10a) == 0) {
        h = *(int *) (s + 0x12c);
        q = func_0206837c(h);
        func_020ab670(q, 2, 1);
        buf[0] = 0xc;
        buf[1] = data_021f43e8;
        func_020ab628(q, 0, &buf[0], 1, &buf[1], 0, 2);
        buf[2] = 0xd;
        buf[3] = data_021f43e8;
        func_020ab628(q, 1, &buf[2], 1, &buf[3], 0, 0);
        func_020ab5f8(q);
        func_02068388(h, 1);
    }
    if (*(u8 *) (s + 0x10a) == 0x19) {
        self->s28(5, 0xff);
    }
}
