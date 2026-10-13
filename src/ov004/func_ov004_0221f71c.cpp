/* func_ov004_0221f71c @ 0x0221f71c, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221f71c {
    unsigned short id;
} UnkStruct_0221f71c;

class UnkStruct_0221f71c_2 {
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

typedef struct UnkStruct_0221f71c_3 {
    char unk_00[0x1a4];
    UnkStruct_0221f71c_2 *obj;
    void *unk_1A8;
} UnkStruct_0221f71c_3;

extern "C" int func_0204bcdc(UnkStruct_0221f71c *p);
extern "C" int func_0204bc64(void *p);
extern "C" void func_0201b420(UnkStruct_0221f71c_2 *o, void *p);
extern "C" void func_0209a000(char *p, int k);
extern "C" int func_ov004_0223cd50(void);
extern "C" int func_ov004_0223cc5c(int a, int b, int c, int d);
extern "C" void func_ov004_0223bb14(int a);
extern "C" void func_0207f360(int a, char *p, int c, int d);

extern "C" void func_ov004_0221f71c(UnkStruct_0221f71c_3 *self)
{
    unsigned short tmp;
    UnkStruct_0221f71c *it;
    int t, cond, r;

    it = (UnkStruct_0221f71c *) ((char *) self->obj + 0x898);
    if (func_0204bcdc(it) != 0) {
        tmp = 0xfff1;
        t = func_0204bc64(it);
        cond = (t == func_0204bc64(&tmp)) ? 1 : 0;
    } else {
        cond = (it->id == 0xfff1) ? 1 : 0;
    }
    if (cond == 0) {
        func_0201b420(self->obj, self->unk_1A8);
        func_0209a000((char *) self->obj + 0x898, 0);
        r = func_ov004_0223cc5c(func_ov004_0223cd50(), *(int *) ((char *) self->obj + 0x89c),
                                *(int *) ((char *) self->obj + 0x8a0), 0);
        if (r != ~0) {
            func_ov004_0223bb14(r);
            if (self->obj->check() != 0) {
                func_0207f360(self->obj->check(), (char *) self->obj + 0x89c, *(int *) ((char *) self->obj + 0xa58),
                              *(int *) ((char *) self->obj + 0xa5c));
            }
        }
        *(unsigned short *) ((char *) self->obj + 0x898) = 0xfff1;
    }
}
