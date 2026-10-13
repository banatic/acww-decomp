/* func_020e9cdc @ 0x020e9cdc, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020e9cdc {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual void vfunc_0c();
    virtual void vfunc_10();
    virtual void vfunc_14();
    virtual void vfunc_18();
    virtual void vfunc_1c();
    virtual void vfunc_20();
    virtual void vfunc_24();
    virtual void vfunc_28();
    virtual int method(int a, int b);
};

extern "C" void func_020ea0a4();
extern "C" void func_020ea084(UnkStruct_020e9cdc *obj);

extern "C" int func_020e9cdc(UnkStruct_020e9cdc *obj, int a, int b)
{
    int result;
    func_020ea0a4();
    result = obj->method(a, b);
    func_020ea084(obj);
    return result;
}
