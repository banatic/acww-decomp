/* func_ov004_022193cc @ 0x022193cc, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022193cc {
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
extern int func_0205265c(void *, int, int, int);
extern int func_ov004_0220d2a8(void *);
extern int func_ov004_0220e5c8(void *);
}

extern "C" void func_ov004_022193cc(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0220d2a8(self + 0x740) != 0x0) {
        func_0205265c(self, 0x3, 0xff, 0x1);
        return;
    } else {
        if (func_ov004_0220e5c8(self) != 0x0) {
            ((UnkStruct_022193cc *) self)->v28(0x3, 0xff);
        }
        return;
    }
}
