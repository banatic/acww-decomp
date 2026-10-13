/* func_ov004_022311bc @ 0x022311bc, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022311bc {
    int a;
    ~UnkStruct_022311bc() {}
};
struct A {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual int m(void *);
};
extern "C" {
extern void *func_020b6590(void);
extern void *func_020b74f0(void *, int, int);
extern void *func_020961a8(int);
extern void *func_02096190(int);
extern void func_0203e0a8(void *, int);
extern void func_020b7e04(void *, void *);
}
extern "C" void func_ov004_022311bc(char *self)
{
    UnkStruct_022311bc t;
    void *a = func_020b74f0(func_020b6590(), 0, 0);
    void *b = func_020961a8(4);
    if (a != 0) {
        if (b != 0) {
            if (a == b) {
                if (((A *) self)->m(func_02096190(4)) != 0) {
                    func_0203e0a8(self, 0);
                    return;
                }
            }
        }
    }
    func_020b7e04(func_020b6590(), self + 0x374);
}
