/* func_ov004_0222ce1c @ 0x0222ce1c, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222ce1c {
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
    virtual void vf(int);
};
extern "C" {
extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern void func_020e8b60(void *, int, int, int);
extern void func_ov004_0222d30c(void *, void *);
extern int func_02056f94(void *);
extern int func_02056f28(void *, int);
extern void RtcSendPxiCommand(int);
}

extern "C" void func_ov004_0222ce1c(UnkStruct_0222ce1c *self)
{
    char *b = (char *) self;
    void *t;
    func_02055124(b + 0xec);
    func_02056ffc(b + 0x290);
    *(*(int **) (b + 0x2a8)) = *(int *) (b + 0x298);
    t = *(void **) (b + 0x494);
    func_020e8b60(&t, 0, 0x100, 0x1000);
    func_ov004_0222d30c(self, t);
    if (func_02056f94(b + 0x188) != 0) {
        self->vf(0);
    } else if (func_02056f28(b + 0x188, 0x3a) != 0) {
        RtcSendPxiCommand(0x4ee);
    }
}
