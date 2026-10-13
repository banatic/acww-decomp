/* func_02015c7c @ 0x02015c7c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Param {
    char pad_00[0x54];
    unsigned char byte;
};

class VBase {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void method(int);
};

extern "C" {
void *func_02015da0(struct Param *p, unsigned char b);
VBase *func_0201c274(void);
void *func_02015d44(void);
void *func_0201c2c8(void *a, void *b);
void func_0201ad18(void *a, int b, int c, int d, void *e, void *f, int g, int h);
void func_02019d0c(void *a, int b, int c, int d, int e, int f, void *g, int h, int i, unsigned short j, int k);
extern unsigned short data_020c80f8;
void func_02015c7c(struct Param *p);
}

extern unsigned char data_021fbee8[];

void func_02015c7c(struct Param *p)
{
    void *r5;
    VBase *r4;
    void *r7;
    void *r6;

    r5 = func_02015da0(p, p->byte);
    if (r5) {
        r4 = func_0201c274();
        r7 = func_02015d44();
        r6 = func_0201c2c8(r5, r7);
        if (r4) {
            r4->method(0);
        }
        func_0201ad18((char *) r5 + 0x3b0, 4, 0, 0, (void *) data_021fbee8, r7, 0, 0);
        func_02019d0c((char *) r5 + 0x564, 3, 2, 0, 0, 0, r6, 0, 0, data_020c80f8, 0);
    }
}
