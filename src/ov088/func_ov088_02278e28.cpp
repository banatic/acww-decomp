/* func_ov088_02278e28 @ 0x02278e28, 0x3a bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278e28 {
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
    virtual void v34(int);
    char pad_04[0xB8];
    unsigned char flag;
};

extern "C" void func_ov088_02278f0c(UnkStruct_02278e28 *obj, int arg);

extern "C" void func_ov088_02278e28(UnkStruct_02278e28 *obj)
{
    if (obj->flag == 0x17) {
        obj->v34(0);
    } else {
        obj->v34(1);
    }
    obj->flag = 0xFF;
    func_ov088_02278f0c(obj, 0);
}
