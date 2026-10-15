/* func_0203ead0 @ 0x0203ead0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203ead0 {
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
    virtual void v19(int, int);
};

extern "C" int func_0203ed8c(UnkStruct_0203ead0 *);
extern "C" int func_0203f338(void);
extern "C" int func_0203efbc(UnkStruct_0203ead0 *);
extern "C" void func_0203f320(int, int);

extern "C" void func_0203ead0(UnkStruct_0203ead0 *obj, int arg1)
{
    int r = func_0203ed8c(obj);
    if (r) {
        if (func_0203f338() == 1) {
            func_0203f320(func_0203efbc(obj), arg1);
        }
    }
    obj->v19(arg1, 4);
}
