/* quick_message_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020393b4 @ 0x020393b4, 0x36 bytes, Thumb
 * func_02039380 @ 0x02039380, 0x34 bytes, Thumb
 */

class UnkStruct_020393b4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void called();
    char pad_04[0xb4];
};

struct Container {
    int header;
    UnkStruct_020393b4 arr[4];
};

extern "C" void func_02039540(Container *p);
extern "C" void func_02039510(Container *p);
extern "C" void func_020394a4(Container *p);

class UnkStruct_02039380 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct Owner {
    char pad_00[0x2f4];
    UnkStruct_02039380 *items[4];
};

extern "C" void func_02039f30(UnkStruct_02039380 *);

extern "C" void func_020393b4(Container *p)
{
    int i;
    func_02039540(p);
    func_02039510(p);
    for (i = 0; i < 4; i++) {
        p->arr[i].called();
    }
    func_020394a4(p);
}

extern "C" void func_02039380(Owner *self)
{
    int i;
    for (i = 3; i >= 0; i--) {
        UnkStruct_02039380 *obj = self->items[i];
        if (obj != 0) {
            func_02039f30(obj);
            obj->f2();
        }
    }
}
