/* func_0206a9bc @ 0x0206a9bc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern "C" void func_0206a9bc(UnkStruct_0206a9bc_3 *arg)
{
    UnkStruct_0206a9bc *b;
    b = arg->a->b;
    func_020a8750(&arg->unk_38);
    b->target(3);
}
