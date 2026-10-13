/* func_020e9abc @ 0x020e9abc, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020e9abc {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual int f19();
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

extern "C" void func_020ea0a4(UnkStruct_020e9abc *self);
extern "C" void func_020ea084(UnkStruct_020e9abc *self);
extern "C" void OS_Terminate(void);

extern "C" int func_020e9abc(UnkStruct_020e9abc *self)
{
    func_020ea0a4(self);
    int result = self->f19();
    if (result == 0 && (self->unk_10 & 0x4000)) {
        OS_Terminate();
    }
    func_020ea084(self);
    return result;
}
