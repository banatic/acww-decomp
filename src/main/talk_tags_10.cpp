/* talk_tags_10: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a62c @ 0x0206a62c, 0x20 bytes, Thumb
 * func_0206a600 @ 0x0206a600, 0x2c bytes, Thumb
 * func_0206a5d4 @ 0x0206a5d4, 0x2c bytes, Thumb
 * func_0206a5a8 @ 0x0206a5a8, 0x2c bytes, Thumb
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

extern "C" void func_020a873c(void *, void *);

class UnkStruct_0206a600 {
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
    virtual void f9(unsigned char);
};

struct Table {
    char pad_00[0x14a8];
    void *entry;
};

struct UnkStruct_0206a600_2 {
    char pad_00[0x24];
    Table *unk_24;
    char pad_28[0x10];
    char unk_38;
};

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

extern "C" void func_0206a62c(UnkStruct_0206a62c_3 *self)
{
    Something *ptr = self->unk_24;
    UnkStruct_0206a62c *obj = ptr->unk_14A8;
    func_020a8750(&self->sub);
    obj->m8();
}

extern "C" void func_0206a600(UnkStruct_0206a600_2 *obj)
{
    unsigned char local;
    UnkStruct_0206a600 *p = (UnkStruct_0206a600 *) obj->unk_24->entry;
    func_020a873c(&obj->unk_38, &local);
    p->f9(local);
}

extern "C" void func_0206a5d4(UnkStruct_0206a5d4_3 *self)
{
    UnkStruct_0206a5d4_2 *a = self->a;
    UnkStruct_0206a5d4 *b = a->target;
    unsigned char local[8];
    func_020a873c(&self->sub, local);
    b->m10(local[0]);
}

extern "C" void func_0206a5a8(OuterClass *self)
{
    TargetClass *target = *(TargetClass **) (self->unk_24 + 0x14a8);
    unsigned char local[8];
    func_020a873c((char *) self + 0x38, local);
    target->call(local[0]);
}
