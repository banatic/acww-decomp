/* func_020e9d64 @ 0x020e9d64, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020e9d64 {
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
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual void vfunc_34();
    virtual void vfunc_38();
    virtual int vfunc_3c(int);
};

extern "C" {
void func_020ea0a4(UnkStruct_020e9d64 *);
void func_020ea084(UnkStruct_020e9d64 *);

int func_020e9d64(UnkStruct_020e9d64 *obj, int value)
{
    int result;
    func_020ea0a4(obj);
    result = obj->vfunc_3c(value);
    func_020ea084(obj);
    return result;
}
}
