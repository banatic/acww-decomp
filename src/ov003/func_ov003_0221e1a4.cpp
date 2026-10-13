/* func_ov003_0221e1a4 @ 0x0221e1a4, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02055060(void *, int, int, int, int, int);

class UnkStruct_0221e1a4 {
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
    virtual int v25();
    char pad_04[0x138];
    int member;
};

extern "C" int func_ov003_0221e1a4(UnkStruct_0221e1a4 *obj)
{
    int result = obj->v25();
    func_02055060(&obj->member, result, 1, 0x1000, 0, 0);
    return 1;
}
