/* func_ov004_0221a420 @ 0x0221a420, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221a420 {
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
extern "C" int func_ov004_0221062c(UnkStruct_0221a420 *self, int a);
extern "C" int func_020644cc(int);
extern "C" void func_ov004_0221041c(UnkStruct_0221a420 *self, int a, int b, int c, int d);
extern "C" void func_ov004_0220d0a0(void *p, int a, int b);
extern "C" int func_ov004_0220d2b8(void *p);

extern "C" int func_ov004_0221a420(UnkStruct_0221a420 *self)
{
    char *s = (char *) self;
    int r;
    int t;
    if (*(int *) (s + 0x780) == 1) {
        r = func_ov004_0221062c(self, 0);
        if (*(int *) (s + 0x76c) == 1) {
            t = 0;
        } else {
            t = func_020644cc(r);
        }
        func_ov004_0221041c(self, 0, 0, 0x1000, (unsigned short) t);
        func_ov004_0220d0a0(s + 0x848, *(int *) (s + 0x594), 1);
    }
    if (func_ov004_0220d2b8(s + 0x740) != 0) {
        self->s28(1, 0xff);
    } else {
        self->s28(0, 0xff);
    }
    return 1;
}
