/* func_0206a62c @ 0x0206a62c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206a62c_2 {
    char data;
};
extern "C" void func_020a8750(struct UnkStruct_0206a62c_2 *sub);

class UnkStruct_0206a62c {
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
};

struct Something {
    char pad_00[0x14a8];
    UnkStruct_0206a62c *unk_14A8;
};

struct UnkStruct_0206a62c_3 {
    char pad_00[0x24];
    Something *unk_24;
    char pad_28[0x10];
    UnkStruct_0206a62c_2 sub;
};

extern "C" void func_0206a62c(UnkStruct_0206a62c_3 *self)
{
    Something *ptr = self->unk_24;
    UnkStruct_0206a62c *obj = ptr->unk_14A8;
    func_020a8750(&self->sub);
    obj->m8();
}
