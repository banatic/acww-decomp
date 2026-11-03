/* talk_tags_9: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a57c @ 0x0206a57c, 0x2c bytes, Thumb
 * func_0206a510 @ 0x0206a510, 0x6c bytes, Thumb
 */

extern "C" void func_020a873c(void *src, unsigned char *dst);

class UnkStruct_0206a57c_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void method(unsigned char);
};

struct UnkStruct_0206a57c {
    char pad_00[0x24];
    void *ptr;
};

extern "C" {
int func_020679fc(char *p);
int func_020a82f8(int p);
void func_020a9334(void *p, int q);
void func_020a7994(char *p, int q);
}

class UnkStruct_0206a510 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

struct UnkStruct_0206a510_2 {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x5c - 0x28];
    int unk_5C;
};

extern "C" void func_0206a57c(UnkStruct_0206a57c *self)
{
    unsigned char buf[8];
    UnkStruct_0206a57c_2 *obj = *(UnkStruct_0206a57c_2 **) ((char *) self->ptr + 0x14a8);
    func_020a873c((char *) self + 0x38, buf);
    obj->method(buf[0]);
}

extern "C" void func_0206a510(UnkStruct_0206a510_2 *p)
{
    int a, b, c, d;
    func_020679fc(p->unk_24);
    a = func_020a82f8(p->unk_5C);
    func_020a9334(p, a);
    b = ((UnkStruct_0206a510 *) (p->unk_24 + 0x1cac))->f3();
    func_020a9334(p, b);
    c = func_020a82f8(5);
    func_020a9334(p, c);
    d = ((UnkStruct_0206a510 *) (p->unk_24 + 0x1cac))->f3();
    func_020a7994(p->unk_24 + 0x1a58, d);
    *(int *) (p->unk_24 + 0x1a60) = 0;
}
