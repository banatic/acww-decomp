/* func_ov004_0221ee1c @ 0x0221ee1c, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221ee1c {
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
    virtual void *vcall();
};

typedef void (*Fn)(void *p);

extern "C" int func_0202e364(UnkStruct_0221ee1c *self);
extern "C" void func_0201c280(UnkStruct_0221ee1c *self, void *p);
extern "C" void func_02084e90(void *p);
extern "C" int func_0208150c(void *p);
extern "C" int func_02003704(int x);
extern "C" int func_0207f270(void *p);
extern "C" int func_0207944c(void);
extern "C" void func_02079438(int x);

extern "C" int func_ov004_0221ee1c(UnkStruct_0221ee1c *self)
{
    void *p;

    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x680);
    (*(Fn **) ((char *) self + 0x680))[2]((char *) self + 0x680);
    func_02084e90((char *) self + 0x8b4);
    *(int *) ((char *) self + 0x8d8) = 0;
    *((char *) self + 0x8d4) = 0;
    p = self->vcall();
    if (p != 0 && func_02003704(func_0208150c(p)) != 0 && func_0207f270(p) != 0) {
        func_02079438(func_0207944c());
    }
    return 1;
}
