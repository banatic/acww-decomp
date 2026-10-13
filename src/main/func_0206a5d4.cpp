/* func_0206a5d4 @ 0x0206a5d4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a873c(void *src, void *dst);

class UnkStruct_0206a5d4 {
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
    virtual void m10(unsigned char c);
};

struct UnkStruct_0206a5d4_2 {
    char pad_00[0x14a8];
    UnkStruct_0206a5d4 *target;
};

struct UnkStruct_0206a5d4_3 {
    char pad_00[0x24];
    UnkStruct_0206a5d4_2 *a;
    char pad_28[0x10];
    char sub;
};

extern "C" void func_0206a5d4(UnkStruct_0206a5d4_3 *self)
{
    UnkStruct_0206a5d4_2 *a = self->a;
    UnkStruct_0206a5d4 *b = a->target;
    unsigned char local[8];
    func_020a873c(&self->sub, local);
    b->m10(local[0]);
}
