/* func_02015b0c @ 0x02015b0c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void *func_02015da0(void *self, int param);
extern unsigned int func_0201c274(void *ptr);
extern int func_0201c314(void *r0, void *r1);
extern int func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);
extern void func_02015bfc(void *self, void *a);
extern unsigned short data_020c80f8;
}

class UnkStruct_02015b0c {
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
    virtual void f20();
};

class VObj2 {
  public:
    virtual int g0();
    virtual int g1();
    virtual int g2();
    virtual int g3();
    virtual int g4();
    virtual int g5();
    virtual int g6();
    virtual int g7();
    virtual int g8();
    virtual int g9();
    virtual int g10();
    virtual int g11();
    virtual int g12();
    virtual int g13();
    virtual void g14(int);
};

extern "C" void func_02015b0c(void *selfv)
{
    char *self = (char *) selfv;
    void *a = func_02015da0(self, 0);
    unsigned char state;

    if (a == 0) {
        goto ret;
    }

    state = ((unsigned char *) self)[0x54];

    switch (state) {
        case 1:
            goto case1;
        case 2:
            goto case2;
        default:
            goto ret;
    }

case1: {
    void *b = func_02015da0(self, state);
    if (b == 0) {
        goto ret;
    }

    {
        unsigned int c1 = func_0201c274(b);
        int e1 = func_0201c314(b, a);

        ((UnkStruct_02015b0c *) self)->f20();

        if (c1 != 0) {
            ((VObj2 *) c1)->g14(0);
        }

        func_02019d0c((char *) b + 0x564, 3, 2, 0, 0, 0, e1, 0, 0, data_020c80f8, 0);
    }
}
    goto ret;

case2:
    func_02015bfc(self, a);

ret:
    return;
}
