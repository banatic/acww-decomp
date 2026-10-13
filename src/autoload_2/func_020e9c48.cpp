/* func_020e9c48 @ 0x020e9c48, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020e9c48 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7(int param);
    char pad_04[12];
    int unk_10;
};

extern "C" void func_020ea0a4(void);
extern "C" void func_020ea084(UnkStruct_020e9c48 *obj);
extern void (*data_021fbe7c)(UnkStruct_020e9c48 *, int);

extern "C" void func_020e9c48(UnkStruct_020e9c48 *obj, int param)
{
    if (param == 0) {
        return;
    }
    func_020ea0a4();
    if (data_021fbe7c && (obj->unk_10 & 0x800)) {
        data_021fbe7c(obj, param);
    }
    obj->f7(param);
    func_020ea084(obj);
}
