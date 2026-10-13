/* func_ov003_0221d10c @ 0x0221d10c, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8164(void *, void *);
extern "C" void *data_ov003_02238ef8;
extern "C" void func_02094fd4(void *);
extern "C" void func_02082438(void *, void *);
extern "C" void func_02094fbc(void *);
extern "C" void func_02066954(void *, int, int);

struct LocalObj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

class Self0221 {
  public:
    virtual void d00();
    virtual void d01();
    virtual void d02();
    virtual void d03();
    virtual void d04();
    virtual void d05();
    virtual void d06();
    virtual void d07();
    virtual void d08();
    virtual void d09();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual int check();

    unsigned char pad_04[0xec - 4];
    unsigned char unk_EC[4];
    unsigned char pad_F0[0x10a - 0xf0];
    unsigned char unk_10A;
};

extern "C" void func_ov003_0221d10c(Self0221 *self)
{
    unsigned char localbuf[4];
    unsigned char obj[0x24];

    func_020a8164(self->unk_EC, &data_ov003_02238ef8);

    if (self->check() == 0) {
        self->unk_10A = 0xf;
    } else {
        self->unk_10A = 0x12;
    }

    func_02094fd4(obj);
    *(unsigned short *) (localbuf + 2) = 0xd00a;
    func_02082438(obj, localbuf + 2);

    {
        int r = ((LocalObj *) obj)->f3();
        func_02066954(self->unk_EC, r, 1);
    }

    func_02094fbc(obj);
}
