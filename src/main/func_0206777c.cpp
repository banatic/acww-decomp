/* func_0206777c @ 0x0206777c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8c1c(void *);
extern "C" int func_020984e8(void);
extern "C" int func_02099870(int);
extern "C" void func_020802ec(int, void *, int);

class UnkStruct_0206777c {
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
    virtual int v26();
};

struct UnkStruct_0206777c_2 {
    char pad_00[0x14a8];
    UnkStruct_0206777c *c;
    char pad_14AC[0x1e04 - 0x14a8 - 4];
    char unk_1E04;
};

extern "C" int func_0206777c(UnkStruct_0206777c_2 *obj)
{
    int res = obj->c->v26();
    int ret = 0;
    func_020a8c1c(&obj->unk_1E04);
    if (res != 0) {
        int other = func_02099870((int) func_020984e8());
        func_020802ec(res, &obj->unk_1E04, other);
        ret = 1;
    }
    return ret;
}
