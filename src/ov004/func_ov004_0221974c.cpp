/* func_ov004_0221974c @ 0x0221974c, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221974c {
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
extern int func_020e895c(void *, int, int);
}

extern "C" int func_ov004_0221974c(char *self)
{
    // DECLS
    // ENDDECLS
    func_020e895c(self + 0x848, 0x0, 0xcc);
    if (*(int *) (self + 0x848) == 0x0) {
        return ((UnkStruct_0221974c *) self)->v28(0x0, 0xff);
    }
    return *(int *) (self + 0x848);
}
