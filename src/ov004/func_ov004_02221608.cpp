/* func_ov004_02221608 @ 0x02221608, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02221608 {
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
    char pad_04[0xac8 - 4];
    unsigned char state;
};

extern "C" int func_0202e1a0(UnkStruct_02221608 *self);
extern "C" void func_020b23c8(void);
extern "C" void func_02079174(int a);
extern "C" int func_0207f270(int a);
extern "C" void func_02079500(int a);

extern "C" int func_ov004_02221608(UnkStruct_02221608 *self)
{
    if (func_0202e1a0(self) == 0) {
        return 0;
    }
    if (self->state == 6 || self->state == 4) {
        func_020b23c8();
        func_02079174(~0);
    }
    if (self->check() != 0) {
        func_02079500(func_0207f270(self->check()));
    }
    return 1;
}
