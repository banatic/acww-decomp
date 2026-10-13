/* func_ov004_0222fddc @ 0x0222fddc, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222fddc {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void m0(int);
};
extern "C" int func_020643dc(int, int, int, int, int);

extern "C" void func_ov004_0222fddc(char *self)
{
    int r = 0x1000 - func_020643dc(*(int *) (self + 0x43c), 0, 0x28000, 0xa000, 0xa000);
    *(int *) (self + 0x198) = r;
    *(int *) (self + 0x428) = r;
    *(int *) (self + 0x43c) += 0x1000;
    if (r == 0) {
        ((UnkStruct_0222fddc *) self)->m0(0);
    }
}
