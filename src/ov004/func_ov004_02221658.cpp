/* func_ov004_02221658 @ 0x02221658, 0x174 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02221658 {
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
    virtual int check();
    char pad_04[0x5c - 4];
    int unk_5C, unk_60, unk_64, unk_68, unk_6C, unk_70;
};

extern "C" int func_0202e1fc(UnkStruct_02221658 *self);
extern "C" void func_02013c0c(char *p);
extern "C" void func_0201addc(char *p);
extern "C" int func_020984e8(void);
extern "C" int func_02099870(int h);
extern "C" void func_020b65b8(void);
extern "C" int func_020b6654(void);
extern "C" int func_020951bc(int h);
extern "C" int func_020807a8(int a, int h);
extern "C" int func_02081898(int a);
extern "C" void func_ov004_0223ce84(void);
extern "C" int func_ov004_0223cdc0(void);
extern "C" void func_020b23d4(void);
extern "C" void func_02030864(int a);
extern "C" void func_ov004_0223d33c(void);
extern "C" void func_0209e474(char *p);
extern "C" void func_ov004_02221550(UnkStruct_02221658 *self, int k);
extern "C" int func_0207f270(int a);
extern "C" void func_02079540(int a, int b);

extern "C" int func_ov004_02221658(UnkStruct_02221658 *self)
{
    int h;
    int i;

    if (func_0202e1fc(self) == 0) {
        return 0;
    }
    *(unsigned short *) ((char *) self + 0x898) = 0xfff1;
    func_02013c0c((char *) self + 0x558);
    *(int *) ((char *) self + 0x89c) = self->unk_5C;
    *(int *) ((char *) self + 0x8a0) = self->unk_60;
    *(int *) ((char *) self + 0x8a4) = self->unk_64;
    *(int *) ((char *) self + 0xad8) = 0x3000;
    for (i = 0; i < 0x64; i++) {
        *((unsigned char *) self + i + 0x8ac) = 0xff;
    }
    func_0201addc((char *) self + 0x3b0);
    if (func_020984e8() != 0) {
        h = func_02099870(func_020984e8());
    } else {
        h = 0;
    }
    func_020b65b8();
    if (func_020b6654() != 0 ||
        (self->check() != 0 && h != 0 && func_020951bc(h) != 0 && func_020807a8(self->check(), h) != 0 &&
         func_02081898(func_020807a8(self->check(), h)) != 0)) {
        func_ov004_0223ce84();
        *(int *) ((char *) self + 0xae4) = func_ov004_0223cdc0();
        func_020b23d4();
        func_02030864(0);
        func_ov004_0223d33c();
        func_0209e474((char *) self + 0xad0);
        *((unsigned char *) self + 0xac8) = 2;
        func_ov004_02221550(self, 3);
    } else {
        self->unk_5C = 0x10000;
        self->unk_68 = 0x10000;
        self->unk_64 = 0x23000;
        self->unk_70 = 0x23000;
        *((unsigned char *) self + 0xadf) = 0x64;
        *(int *) ((char *) self + 0xae8) = 1;
        func_ov004_02221550(self, 0);
    }
    if (self->check() != 0) {
        func_02079540(func_0207f270(self->check()), 2);
    }
    return 1;
}
