/* func_020128cc @ 0x020128cc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern char *func_02137550(void *, unsigned int);
extern int func_0208150c(int);
extern int func_0207cc94(void *, void *, int);
extern unsigned char *func_020800d0(int object);
extern void func_020131dc(unsigned int *, void *, unsigned int *, void *);
extern void *data_021c80bc;
extern int data_021e5a2c;
}

class UnkStruct_020128cc {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
    virtual int f4();
    virtual int f5();
    virtual int f6();
    virtual int f7();
    virtual int f8();
    virtual int f9();
    virtual int f10();
    virtual int f11();
    virtual int f12();
    virtual int f13();
    virtual int f14();
    virtual int f15();
    virtual int f16();
    virtual int f17();
    virtual int f18();
    virtual int f19();
    virtual int f20();
    virtual int f21();
    virtual int f22();
    virtual int f23();
    virtual int f24();
    virtual int f25();
};

extern "C" void func_020128cc(unsigned int *out, void *a1, void *a2, void *a3)
{
    int forwarded_value;

    unsigned int local;
    unsigned int coords[2];
    unsigned int result[2];
    void *g = data_021c80bc;

    *out = 0;
    *(out + 1) = 0;

    if (g == 0) {
        return;
    }

    if (((UnkStruct_020128cc *) a3)->f25() == 0) {
        return;
    }

    func_02137550(&local, 4);
    local = func_0208150c(((UnkStruct_020128cc *) a3)->f25());

    if ((forwarded_value = (int) func_0207cc94(&data_021e5a2c, &local, 1)) == 0) {
        return;
    }

    {
        unsigned char *p = func_020800d0((int) forwarded_value);
        coords[0] = 0;
        coords[1] = 0;
        unsigned char b1 = p[1];
        unsigned char b0 = p[0];
        coords[0] = b0 >> 4;
        coords[1] = b1 >> 4;
    }

    func_020131dc(result, a1, coords, g);
    *out = result[0];
    *(out + 1) = result[1];
}
