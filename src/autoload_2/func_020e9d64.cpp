/* func_020e9d64 @ 0x020e9d64, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020e9d64 {
  public:
    virtual int f0(int);
    virtual int f1(int);
    virtual int f2(int);
    virtual int f3(int);
    virtual int f4(int);
    virtual int f5(int);
    virtual int f6(int);
    virtual int f7(int);
    virtual int f8(int);
    virtual int f9(int);
    virtual int f10(int);
    virtual int f11(int);
    virtual int f12(int);
    virtual int f13(int);
    virtual int f14(int);
    virtual int target(int);
};

extern "C" {
void func_020ea0a4(UnkStruct_020e9d64 *);
void func_020ea084(UnkStruct_020e9d64 *);

int func_020e9d64(UnkStruct_020e9d64 *obj, int value)
{
    int result;
    func_020ea0a4(obj);
    result = obj->target(value);
    func_020ea084(obj);
    return result;
}
}
