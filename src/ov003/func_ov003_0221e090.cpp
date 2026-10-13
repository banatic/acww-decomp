/* func_ov003_0221e090 @ 0x0221e090, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221e090 {
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
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual void f25();
    virtual int GetValue();
};

extern "C" void func_02055060(void *p, int a, int b, int c, int d, int e);
extern "C" void func_ov009_02262ef0(void *p, int v);

extern "C" int func_ov003_0221e090(UnkStruct_0221e090 *self)
{
    int v = self->GetValue();
    func_02055060((char *) self + 0x13c, v, 1, 0x1000, 0, 0);
    func_ov009_02262ef0((char *) self + 0x238, 0x819);
    return 1;
}
