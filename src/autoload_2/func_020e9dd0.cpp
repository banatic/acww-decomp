/* func_020e9dd0 @ 0x020e9dd0, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020ea0a4(void *);
extern "C" void func_020ea084(void *);

class UnkStruct_020e9dd0 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int target();
};

extern "C" int func_020e9dd0(UnkStruct_020e9dd0 *obj)
{
    func_020ea0a4(obj);
    int result = obj->target();
    func_020ea084(obj);
    return result;
}
