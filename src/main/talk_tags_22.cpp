/* talk_tags_22: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a9bc @ 0x0206a9bc, 0x24 bytes, Thumb
 * func_0206a998 @ 0x0206a998, 0x24 bytes, Thumb
 */

extern "C" void func_020a8750(char *p);

class UnkStruct_0206a9bc {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual void f4() = 0;
    virtual void f5() = 0;
    virtual void f6() = 0;
    virtual void target(int) = 0;
};

struct UnkStruct_0206a9bc_2 {
    char pad_00[0x14a8];
    UnkStruct_0206a9bc *b;
};

struct UnkStruct_0206a9bc_3 {
    char pad_00[0x24];
    UnkStruct_0206a9bc_2 *a;
    char pad_28[0x10];
    char unk_38;
};

class UnkStruct_0206a998 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7(int);
};

struct Table {
    char pad_00[0x14A8];
    UnkStruct_0206a998 *obj;
};

struct Param {
    char pad_00[0x24];
    Table *table;
    char pad_28[0x10];
    char unk_38;
};

extern "C" void func_0206a9bc(UnkStruct_0206a9bc_3 *arg)
{
    UnkStruct_0206a9bc *b;
    b = arg->a->b;
    func_020a8750(&arg->unk_38);
    b->target(3);
}

extern "C" void func_0206a998(Param *p)
{
    UnkStruct_0206a998 *obj = p->table->obj;
    func_020a8750((char *) (&p->unk_38));
    obj->m7(4);
}
