/* func_ov004_02211b98 @ 0x02211b98, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02211b98 {
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
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0220d2b8(void *);
extern int func_ov004_022118bc(void *, int);
}

extern "C" int func_ov004_02211b98(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x76c) == 0x1) {
        func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    }
    if (func_ov004_0220d2b8(self + 0x740) != 0x0) {
        ((UnkStruct_02211b98 *) self)->v28(0x2, 0xff);
    } else {
        ((UnkStruct_02211b98 *) self)->v28(0x0, 0xff);
    }
    func_ov004_022118bc(self, 0x0);
    return 0x1;
}
