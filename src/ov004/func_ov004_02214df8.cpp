/* func_ov004_02214df8 @ 0x02214df8, 0x1d0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02214df8 {
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
    virtual void v28();
    virtual void v29();
    virtual int get();
};

extern "C" void *data_020ccf94;

extern "C" void func_ov004_0221078c(UnkStruct_02214df8 *self);
extern "C" void func_ov004_0220d280(char *p, int a, int b);
extern "C" void func_0204f818(int *a, int *b, char *p);
extern "C" int func_020b6680(void);
extern "C" void func_02004108(char *p, int k);
extern "C" int func_020040a4(char *p);
extern "C" int func_020b65c4(void);
extern "C" void func_02052e98(int a, int b, int c, int d);
extern "C" int func_02052ec0(int a, int b, int c);
extern "C" int func_ov004_0220e220(char *p);
extern "C" int func_ov004_0220da04(int h, int k);
extern "C" void func_02055060(char *p, int a, int b, int c, int d, int e);
extern "C" void func_02054cdc(char *p);
extern "C" void func_ov004_0221524c(UnkStruct_02214df8 *self, int k);
extern "C" void func_ov004_02215228(UnkStruct_02214df8 *self, int k);
extern "C" int func_ov004_0223b22c(void);
extern "C" int func_ov004_0223adf4(int h);
extern "C" int func_02073d90(void *g);
extern "C" int func_ov004_02215200(UnkStruct_02214df8 *self);

extern "C" int func_ov004_02214df8(UnkStruct_02214df8 *self)
{
    int a, b;
    int k;

    func_ov004_0221078c(self);
    func_ov004_0220d280((char *) self + 0x740, 1, 0);
    *(unsigned short *) ((char *) self + 0x860) = 0xffff;
    func_0204f818(&a, &b, (char *) self + 0x5c);
    if (*((unsigned char *) self + 0x77e) != 0) {
        if (*(int *) ((char *) self + 0x76c) != 0 || func_020b6680() != 0) {
            func_02004108((char *) self + 0x844, 1);
            k = func_020040a4((char *) self + 0x844) & 0xf;
            func_02052e98(a, b, (unsigned char) k, func_020b65c4());
            *((unsigned char *) self + 0x77c) = (unsigned char) k;
            func_02055060((char *) self + 0x538, func_ov004_0220da04(func_ov004_0220e220((char *) self + 0x6cc), 0), 0, 0, 0,
                          0);
            func_02054cdc((char *) self + 0x538);
            *(unsigned short *) ((char *) self + 0x860) = 0;
        } else {
            func_ov004_0221524c(self, 2);
            k = func_02052ec0(a, b, func_020b65c4()) & 0xf;
            func_ov004_02215228(self, (unsigned char) k);
            *((unsigned char *) self + 0x77c) = (unsigned char) k;
            func_02055060((char *) self + 0x538, func_ov004_0223adf4(func_ov004_0223b22c()), 0, 0, 0, 0);
            func_02054cdc((char *) self + 0x538);
        }
    } else if (func_02073d90(data_020ccf94) != 0 && self->get() != 0xff) {
        func_ov004_0221524c(self, 1);
        k = self->get();
        func_02052e98(a, b, (unsigned char) (k & 0xf), func_020b65c4());
        func_02055060((char *) self + 0x538, func_ov004_0223adf4(func_ov004_0223b22c()), 0, 0, 0, 0);
        func_02054cdc((char *) self + 0x538);
    } else {
        func_ov004_0221524c(self, 1);
        k = func_ov004_02215200(self) & 0xf;
        func_02052e98(a, b, (unsigned char) k, func_020b65c4());
        *((unsigned char *) self + 0x77c) = (unsigned char) k;
        func_02055060((char *) self + 0x538, func_ov004_0223adf4(func_ov004_0223b22c()), 0, 0, 0, 0);
        func_02054cdc((char *) self + 0x538);
    }
    return 1;
}
