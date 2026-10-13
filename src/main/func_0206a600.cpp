/* func_0206a600 @ 0x0206a600, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern "C" void func_0206a600(UnkStruct_0206a600_2 *obj)
{
    unsigned char local;
    UnkStruct_0206a600 *p = (UnkStruct_0206a600 *) obj->unk_24->entry;
    func_020a873c(&obj->unk_38, &local);
    p->f9(local);
}
