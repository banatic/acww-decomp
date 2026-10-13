/* func_ov004_0222c934 @ 0x0222c934, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222c934 {
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
    virtual void vcall(int a);
};

extern "C" int func_02056f94(void *p);
extern "C" void func_02055124(void *p);

extern "C" void func_ov004_0222c934(UnkStruct_0222c934 *self)
{
    if (func_02056f94((char *) self + 0x188) != 0) {
        self->vcall(0);
    } else {
        func_02055124((char *) self + 0xec);
    }
}
