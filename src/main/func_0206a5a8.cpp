/* func_0206a5a8 @ 0x0206a5a8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a873c(void *, void *);

class TargetClass {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int call(unsigned char b);
};

struct OuterClass {
    char pad_00[0x24];
    char *unk_24;
};

extern "C" int func_0206a5a8(OuterClass *self)
{
    TargetClass *target = *(TargetClass **) (self->unk_24 + 0x14a8);
    unsigned char local[8];
    func_020a873c((char *) self + 0x38, local);
    return target->call(local[0]);
}
