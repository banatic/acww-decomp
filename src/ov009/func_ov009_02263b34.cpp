/* func_ov009_02263b34 @ 0x02263b34, 0x44 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02055060(void *, int, int, int, int, int);

class UnkStruct_02263b34 {
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
    char pad_04[0x12e];
    short unk_132;
    char pad_134[8];
    char unk_13C;
};

extern "C" int func_ov009_02263b34(UnkStruct_02263b34 *obj)
{
    obj->unk_132 = 26;
    int ret = obj->v26();
    if (ret != 0) {
        func_02055060(&obj->unk_13C, ret, 1, 0x1000, 0, 0);
        return 1;
    } else {
        return 0;
    }
}
