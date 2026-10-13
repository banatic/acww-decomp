/* func_020e9e78 @ 0x020e9e78, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020ea0a4(void *);
extern "C" void func_020ea084(void *);

class UnkStruct_020e9e78 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void target();
};

extern "C" void func_020e9e78(UnkStruct_020e9e78 *self)
{
    func_020ea0a4(self);
    self->target();
    func_020ea084(self);
}
