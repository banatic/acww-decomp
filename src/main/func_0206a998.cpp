/* func_0206a998 @ 0x0206a998, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern "C" void func_020a8750(void *);

extern "C" void func_0206a998(Param *p)
{
    UnkStruct_0206a998 *obj = p->table->obj;
    func_020a8750(&p->unk_38);
    obj->m7(4);
}
