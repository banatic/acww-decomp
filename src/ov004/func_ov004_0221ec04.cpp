/* func_ov004_0221ec04 @ 0x0221ec04, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221ec04 {
    unsigned short id;
} UnkStruct_0221ec04;

class UnkStruct_0221ec04_2 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual int check();
};

extern "C" void *data_020ccf94;

extern "C" void func_ov004_0221ebb8(char *p, UnkStruct_0221ec04_2 *self);
extern "C" int func_02073d90(void *g);
extern "C" int func_020164a0(char *p, int k);
extern "C" UnkStruct_0221ec04 *func_02080ce4(int h);
extern "C" UnkStruct_0221ec04 *func_0202defc(char *p);
extern "C" int func_0204bcdc(UnkStruct_0221ec04 *p);
extern "C" int func_0204bc64(UnkStruct_0221ec04 *p);
extern "C" void func_0202df18(char *p, UnkStruct_0221ec04_2 *self, UnkStruct_0221ec04 *it);
extern "C" void func_0201c6d0(char *p, UnkStruct_0221ec04_2 *self);

extern "C" int func_ov004_0221ec04(UnkStruct_0221ec04_2 *self)
{
    void *g;
    UnkStruct_0221ec04 *a, *b, *p;
    int t, cond, ok;

    func_ov004_0221ebb8((char *) self + 0x8a0, self);
    g = data_020ccf94;
    if (func_02073d90(g) != 0 && func_020164a0((char *) self + 0x334, 0) != 6 && self->check() != 0) {
        a = func_02080ce4(self->check());
        b = func_0202defc((char *) self + 0x64c);
        if (func_0204bcdc(b) != 0) {
            t = func_0204bc64(b);
            cond = (t == func_0204bc64(a)) ? 1 : 0;
        } else {
            cond = (b->id == a->id) ? 1 : 0;
        }
        if (cond == 0) {
            p = func_02080ce4(self->check());
            ok = 0;
            if (p->id >= 0x11a8 && p->id <= 0x12a7) {
                ok = 1;
            }
            if (ok != 0) {
                func_0202df18((char *) self + 0x64c, self, func_02080ce4(self->check()));
            }
        }
    }
    func_0201c6d0((char *) self + 0x83c, self);
    return 1;
}
