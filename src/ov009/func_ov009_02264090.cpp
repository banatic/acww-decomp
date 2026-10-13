/* func_ov009_02264090 @ 0x02264090, 0x48 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02264090 {
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
    virtual int GetValue();
};

extern "C" int func_ov009_02264c90(void *self);
extern "C" void func_02055060(void *p, int a, int b, int c, int d, int e);

extern "C" int func_ov009_02264090(UnkStruct_02264090 *self)
{
    int t = func_ov009_02264c90(self);
    switch (t) {
        case 1:
        case 2: {
            int v = self->GetValue();
            if (v == 0) {
                return 0;
            }
            func_02055060((char *) self + 0x13c, v, 0, 0x1000, 0, 0);
            break;
        }
    }
    return 1;
}
