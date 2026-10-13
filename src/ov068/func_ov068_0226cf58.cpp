/* func_ov068_0226cf58 @ 0x0226cf58, 0x32 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208150c(void);
extern "C" int func_02003704(void);
extern "C" int func_0207f270(void *p);
extern "C" int func_0207944c(void);

class UnkStruct_0226cf58 {
  public:
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *v25();
};

extern "C" int func_ov068_0226cf58(UnkStruct_0226cf58 *obj)
{
    void *ret;
    ret = obj->v25();
    if (ret != 0) {
        func_0208150c();
        if (func_02003704() != 0) {
            if (func_0207f270(ret) != 0) {
                return func_0207944c();
            }
        }
    }
    return 0;
}
