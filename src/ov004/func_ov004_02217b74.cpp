/* func_ov004_02217b74 @ 0x02217b74, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02217b74 {
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
    virtual int v28(int, int);
};
extern "C" {
extern int func_0206f9d8(void *);
extern int func_0206fa28(int, int);
extern void func_ov004_02217bb0();
}

extern "C" void func_ov004_02217b74(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x12c) != 0x0 && *(int *) ((char *) *(int *) (self + 0x12c) + 0x4) == 0x0 &&
        func_0206fa28(func_0206f9d8((void *) func_ov004_02217bb0), 0x28) != 0x0) {
        ((UnkStruct_02217b74 *) self)->v28(0xb, 0xff);
        return;
    }
}
