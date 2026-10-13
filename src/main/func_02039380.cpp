/* func_02039380 @ 0x02039380, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
