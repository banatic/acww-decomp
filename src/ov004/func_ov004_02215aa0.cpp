/* func_ov004_02215aa0 @ 0x02215aa0, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02215aa0 {
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

extern "C" int func_ov004_0220d2b8(void *p);
extern "C" int func_ov004_0220d220(void *p, int a, void *b, int c);
extern "C" int func_ov004_0223c10c(void);
extern "C" void func_ov004_0221041c(void *p, int a, int b, int c, int d);
extern int data_ov004_022531d8;

extern "C" int func_ov004_02215aa0(UnkStruct_02215aa0 *self)
{
    int a;

    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    a = *(int *) ((char *) self + 0x594);

    func_ov004_0220d220((char *) self + 0x848, a, &data_ov004_022531d8, func_ov004_0220d2b8((char *) self + 0x740));
    if (func_ov004_0220d2b8((char *) self + 0x740) != 0 && func_ov004_0223c10c() == 0) {
        self->s28(2, 0xff);
    } else {
        self->s28(0, 0xff);
    }
    return 1;
}
