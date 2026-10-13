/* func_02069534 @ 0x02069534, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *p);

class UnkStruct_02069534 {
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
    virtual void called();
};

struct Param {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x10];
    int unk_38;
};

extern "C" void func_02069534(Param *param)
{
    UnkStruct_02069534 *obj;
    obj = *(UnkStruct_02069534 **) ((char *) param->unk_24 + 0x14a8);
    func_020a8750((void *) &param->unk_38);
    obj->called();
}
