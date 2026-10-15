/* func_ov004_02217a38 @ 0x02217a38, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02217a38 {
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
extern "C" int func_ov004_0220cdec(UnkStruct_02217a38 *self);
extern "C" int func_02053bc0(void *p);
extern "C" int func_0204bc64(void *p);
extern "C" int func_ov004_02211394(int a, int b, int c, int d, int e, int f);
extern "C" int func_ov004_0223c660(void *);

extern "C" void func_ov004_02217a38(UnkStruct_02217a38 *self)
{
    int a;
    int b;
    int r;
    char *s = (char *) self;
    if (func_ov004_0220cdec(self) == 0) {
        return;
    }
    a = *(int *) (s + 0x850);
    b = *(int *) (s + 0x854);
    if (*(int *) (s + 0x784) == 2 && *(u8 *) (s + 0x846) != 0) {
        a = a + 1;
    }
    r = func_02053bc0(s + 0x85c);
    if (*(u8 *) (s + 0x846) != 0 && r == 2) {
        a = a - 1;
    }
    if (func_ov004_0223c660((void *) func_ov004_02211394(a, b, func_0204bc64(s + 0x85c), 3, 0, 1)) != 0) {
        self->s28(0xd, 0xff);
    }
}
