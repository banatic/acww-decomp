/* func_ov068_0226b648 @ 0x0226b648, 0x104 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020984e8(void);
extern "C" int func_02099020(int, int);
extern "C" void *func_0207f270(int);
extern "C" void func_ov068_0226cfd4(void *);
extern "C" void func_ov068_02266c34(void *, void *, int, int, int, void *, int, int, int);
extern "C" int func_02019c6c(void *, int, unsigned short);
extern "C" void func_02079540(void *, int);
extern "C" int func_0207d578(int, int);
extern "C" void func_020794d4(void *, int);
extern "C" void func_0207f454(int);
extern "C" void func_0202e194(void *);
extern "C" void *func_020644cc(int);
extern "C" void func_0201cbbc(void *);

extern unsigned short data_020c80f8;
extern int data_020c814c;

class UnkStruct_0226b648 {
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
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual int f25();
};

extern unsigned char data_021fbee8[];

extern "C" int func_ov068_0226b648(void *r6, void *r5)
{
    int t = func_020984e8();
    int r7;
    if (t != 0) {
        r7 = func_02099020(t, 1);
    } else {
        r7 = 0;
    }

    int vret = ((UnkStruct_0226b648 *) r5)->f25();
    void *r4 = func_0207f270(vret);
    func_ov068_0226cfd4(r5);

    func_ov068_02266c34((char *) r5 + 0x898, r5, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);

    func_02019c6c((char *) r5 + 0x564, 1, data_020c80f8);
    func_02079540(r4, 0);

    *((unsigned char *) r4 + 0x1d) &= ~2;

    {
        int flag = (r7 != 0) ? 1 : 0;
        if (flag == 0) {
            if (func_0207d578(vret, 0) != 0) {
                func_020794d4(r4, 2);
                goto after_call;
            }
        }
        func_020794d4(r4, 0);
    }
after_call:

    func_0207f454(vret);
    func_0202e194(r5);

    *(int *) ((char *) r6 + 0x20) = (int) func_020644cc(0x28) + 0x258;
    *((unsigned char *) r5 + 0x562) = 0;
    r6 = (char *) r6 + 0xf8;
    *(int *) r6 = 0x384;
    func_0201cbbc((char *) r5 + 0x83c);
    *((unsigned char *) r5 + 0x9f0) = 0;

    return 1;
}