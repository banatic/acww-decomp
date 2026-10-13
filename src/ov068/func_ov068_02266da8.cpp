/* func_ov068_02266da8 @ 0x02266da8, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02266da8 {
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
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual int v45();
    char pad_04[0x8b4];
    char unk_8B8[4];
};

extern "C" int func_0201ce5c(UnkStruct_02266da8 *p, void *q);
extern "C" int func_0201ce44(UnkStruct_02266da8 *p, int q);
extern "C" void func_ov068_0226ccd8(void *p);
extern "C" void func_ov068_0226cce8(void *p, UnkStruct_02266da8 *q, int r);

extern "C" int func_ov068_02266da8(UnkStruct_02266da8 *self, void *arg)
{
    if (self->v45()) {
        func_0201ce5c(self, arg);
        func_0201ce44(self, 1);
        func_ov068_0226ccd8(self->unk_8B8);
        func_ov068_0226cce8(self->unk_8B8, self, 9);
        return 1;
    }
    return 0;
}
