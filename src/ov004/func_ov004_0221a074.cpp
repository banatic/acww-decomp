/* func_ov004_0221a074 @ 0x0221a074, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221a074 {
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void vcall(int a, int b);
};

extern "C" void func_ov004_0220d280(void *p, int a, int b);
extern "C" void func_ov004_0221041c(UnkStruct_0221a074 *self, int a, int b, int c, int d);
extern "C" void func_ov004_02210054(UnkStruct_0221a074 *self, int a, int b, int c);

extern "C" int func_ov004_0221a074(UnkStruct_0221a074 *self)
{
    func_ov004_0220d280((char *) self + 0x740, 0, 0);
    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    func_ov004_02210054(self, 0, 1, 0x1000);
    self->vcall(0, 0xff);
    return 1;
}
