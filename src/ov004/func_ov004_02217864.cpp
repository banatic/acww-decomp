/* func_ov004_02217864 @ 0x02217864, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02217864 {
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
extern "C" int func_020ab504(int q);
extern "C" void func_0206844c(int h, void *p, int k);
extern "C" u8 data_021f43e8;

extern "C" void func_ov004_02217864(UnkStruct_02217864 *self)
{
    char *s = (char *) self;
    int r = func_020ab504(func_0206837c(*(int *) (s + 0x12c)));
    if (*(int *) (s + 0x858) == 1) {
        switch (r) {
            case 0:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                self->s28(6, 0xff);
                break;
            case 1:
                self->s28(5, 0xff);
                break;
        }
    } else {
        switch (r) {
            case 0:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                self->s28(0xa, 0xff);
                break;
            case 1:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                self->s28(9, 0xff);
                break;
        }
    }
}
