/* func_ov004_022173b8 @ 0x022173b8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022173b8 {
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
    virtual void vcall(int a, int b);
};

extern "C" void func_ov004_0220cfec(void *p, int a);
extern "C" int func_ov004_0220ffbc(UnkStruct_022173b8 *self);

extern "C" void func_ov004_022173b8(UnkStruct_022173b8 *self)
{
    func_ov004_0220cfec((char *) self + 0x764, 0x1);
    if (func_ov004_0220ffbc(self) != 0) {
        self->vcall(0x2, 0xff);
    }
}
