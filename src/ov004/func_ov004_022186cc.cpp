/* func_ov004_022186cc @ 0x022186cc, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022186cc {
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
extern int func_020b67ac(void);
extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_0220d0a0(void *, int, int);
extern void func_ov004_0221041c(void *, int, int, int, int);
}

extern "C" int func_ov004_022186cc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x0);
    if (*(int *) (self + 0x780) == 0x2a) {
        func_ov004_0221041c(self, 0x0, 0x0, 0x1000, 0x0);
        func_ov004_0220d0a0(self + 0x860, *(int *) (self + 0x594), 0x1);
    }
    if (func_020b67ac() != 0x0) {
        ((UnkStruct_022186cc *) self)->v28(0x1, 0xff);
    }
    return 0x1;
}
