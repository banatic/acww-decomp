/* func_ov004_0222fb0c @ 0x0222fb0c, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222fb0c {
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
    virtual int v24(int);
};
extern "C" {
extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c574(void *);
extern void func_ov004_0222c590(void *, int);
extern int func_ov004_0222c5c8(void *, void *);
extern int func_ov004_0222f484(void *);
extern int func_ov004_0222f6e8(void *, int);
extern void *data_021c9b24;
extern void *data_ov004_022554cc;
extern void *data_ov004_02258490;
}

extern "C" int func_ov004_0222fb0c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) ((char *) &data_ov004_02258490) = self;
    func_ov004_0222c590(self, 0x0);
    func_ov004_0222c5c8(self, &data_ov004_022554cc);
    func_ov004_0222f484(self);
    if (func_ov004_0222c3c4(self + 0x1a4, 0x0) != 0x0 &&
        func_02055140(self + 0xec, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x1, 0x1000, 0x0, 0x0);
        func_02055050(self + 0xec);
    }
    func_ov004_0222f6e8(self, 0x0);
    ((UnkStruct_0222fb0c *) self)->v24(func_ov004_0222c574(self));
    return 0x1;
}
