/* func_ov004_0222c704 @ 0x0222c704, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222c704 {
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
    virtual int v25(void *);
};
extern "C" {
extern int func_02003420(void *, int);
extern void func_ov004_0222c2f8(void *, void *);
}

extern "C" int func_ov004_0222c704(char *self, int a1)
{
    // DECLS
    char frame[0xc];
    // ENDDECLS
    ((UnkStruct_0222c704 *) self)->v25(frame);
    func_ov004_0222c2f8(self + 0x250, frame);
    return func_02003420(self, a1);
}
