/* func_ov009_02263ba8 @ 0x02263ba8, 0x6c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02055060(void *a, int b, int c, int d, int e, int f);
extern "C" int func_0204bba8(void *a);
extern "C" void func_ov009_02262ef0(void *a, int b);

class Vtbl {
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
    virtual int f25();
};

extern "C" int func_ov009_02263ba8(Vtbl *obj)
{
    int ret = obj->f25();
    if (ret != 0) {
        func_02055060((char *) obj + 0x13c, ret, 1, 0x1000, 0, 0);
        if (func_0204bba8((char *) obj + 0x136) != 0) {
            func_ov009_02262ef0((char *) obj + 0x238, 0x806);
        } else {
            func_ov009_02262ef0((char *) obj + 0x238, 0x808);
        }
        return 1;
    }
    return 0;
}
