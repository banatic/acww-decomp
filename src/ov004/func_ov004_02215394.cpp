/* func_ov004_02215394 @ 0x02215394, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02215394 {
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
};

extern "C" void func_ov004_0220fde0(UnkStruct_02215394 *self);
extern "C" int func_ov004_0223a730(void);
extern "C" void func_ov004_022152d0(UnkStruct_02215394 *self, int h);
extern "C" void func_ov004_0221041c(UnkStruct_02215394 *self, int a, int b, int c, int d);
extern "C" void func_ov004_0220ffa4(UnkStruct_02215394 *self);
extern "C" int func_0209d324(void);
extern "C" void func_02055478(char *p, int h);
extern "C" void func_ov004_0220d280(char *p, int a, int b);
extern "C" int func_020b65c4(void);
extern "C" int func_ov004_0220fd8c(UnkStruct_02215394 *self);
extern "C" void func_02051f4c(int a, char *p, int c);
extern "C" int func_ov004_0220e5c8(UnkStruct_02215394 *self);
extern "C" int func_ov004_0220d2b8(char *p);

extern "C" int func_ov004_02215394(UnkStruct_02215394 *self)
{
    *(int *) ((char *) self + 0x85c) = 0;
    *((unsigned char *) self + 0x77c) = 0xff;
    func_ov004_0220fde0(self);
    func_ov004_022152d0(self, func_ov004_0223a730());
    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    func_ov004_0220ffa4(self);
    func_02055478((char *) self + 0x538, func_0209d324());
    if (*(int *) ((char *) self + 0x76c) == 1) {
        func_ov004_0220d280((char *) self + 0x740, 0, 0);
        func_02051f4c(func_020b65c4(), (char *) self + 0x5c, func_ov004_0220fd8c(self));
    } else if (func_ov004_0220e5c8(self) != 0) {
        self->act(0, 0xff);
    } else if (func_ov004_0220d2b8((char *) self + 0x740) != 0) {
        self->act(1, 0xff);
    } else {
        self->act(0, 0xff);
    }
    return 1;
}
