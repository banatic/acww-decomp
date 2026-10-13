/* func_020e9b9c @ 0x020e9b9c, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020e9b9c {
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
    int unk_04;
    int unk_08;
    int unk_0C;
    int flags;
};

extern "C" void func_020ea0a4(UnkStruct_020e9b9c *);
extern "C" void func_020ea084(UnkStruct_020e9b9c *);
extern "C" void (*data_021fbe7c)(UnkStruct_020e9b9c *, int);

extern "C" void func_020e9b9c(UnkStruct_020e9b9c *obj)
{
    func_020ea0a4(obj);
    if (data_021fbe7c != 0 && (obj->flags & 0x800) != 0) {
        data_021fbe7c(obj, 0);
    }
    obj->v8();
    func_020ea084(obj);
}
