/* func_ov004_02219034 @ 0x02219034, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02219034 {
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

extern "C" void func_ov004_0220d280(void *p, int a, int b);
extern "C" void func_ov004_022107d4(UnkStruct_02219034 *self);
extern "C" int func_ov004_0220ffbc(UnkStruct_02219034 *self);

extern "C" void func_ov004_02219034(UnkStruct_02219034 *self)
{
    func_ov004_0220d280((char *) self + 0x740, 1, 0);
    func_ov004_022107d4(self);
    if (func_ov004_0220ffbc(self) != 0) {
        self->s28(2, 0xff);
    }
}
