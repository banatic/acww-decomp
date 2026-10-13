/* func_ov004_02214d34 @ 0x02214d34, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02214d34 {
  public:
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
    virtual void act(int a, int b);
    virtual void v29();
    virtual int get();
    char pad_04[0x860 - 4];
    unsigned short unk_860;
};

extern "C" void func_ov004_02215298(UnkStruct_02214d34 *self, char *p);
extern "C" void func_02054cdc(char *p);
extern "C" int func_ov004_022151d8(UnkStruct_02214d34 *self);
extern "C" int func_ov004_0220e220(char *p);
extern "C" int func_ov004_0220da04(int h, int k);
extern "C" void func_02054cac(char *p, int a, int b, int c, int d, int e, int f);
extern "C" int func_ov004_0220d2a8(char *p);
extern "C" void func_ov004_0220d280(char *p, int a, int b);
extern "C" int func_020b65c4(void);
extern "C" int func_ov004_0220fd8c(UnkStruct_02214d34 *self);
extern "C" void func_02051f4c(int a, char *p, int c);

extern "C" void func_ov004_02214d34(UnkStruct_02214d34 *self)
{
    int n;

    func_ov004_02215298(self, (char *) self + 0x5c);
    if (self->unk_860 != 0) {
        func_02054cdc((char *) self + 0x538);
        self->unk_860 = (unsigned short) (self->unk_860 - 1);
    }
    if (self->unk_860 == 0) {
        self->act(2, self->get());
    } else {
        n = func_ov004_022151d8(self);
        if (n >= 0) {
            self->unk_860 = (unsigned short) n;
            func_02054cac((char *) self + 0x538, func_ov004_0220da04(func_ov004_0220e220((char *) self + 0x6cc), 0),
                          (unsigned short) n, 0, 0, 0, 0);
        }
    }
    if (func_ov004_0220d2a8((char *) self + 0x740) != 0) {
        func_ov004_0220d280((char *) self + 0x740, 1, 0);
        func_02051f4c(func_020b65c4(), (char *) self + 0x5c, func_ov004_0220fd8c(self));
    }
}
