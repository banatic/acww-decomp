/* func_ov068_0226d598 @ 0x0226d598, 0x5a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_020984e8(void);
extern "C" int func_02099870(void *);
extern "C" int func_020951bc(int);
extern "C" void *func_0208150c(void *);
extern "C" int func_02003704(void *);
extern "C" int func_020807a8(void *, int);

class UnkStruct_0226d598 {
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
    virtual void *target();
};

extern "C" int func_ov068_0226d598(UnkStruct_0226d598 *param)
{
    int r4;
    void *x;
    void *result;

    x = func_020984e8();
    if (x != 0) {
        r4 = func_02099870(func_020984e8());
    } else {
        r4 = 0;
    }

    result = param->target();

    if (r4 != 0 && func_020951bc(r4) != 0 && result != 0 && func_02003704(func_0208150c(result)) != 0) {
        return func_020807a8(result, r4);
    }
    return 0;
}
