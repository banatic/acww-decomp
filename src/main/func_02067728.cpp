/* func_02067728 @ 0x02067728, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8c1c(void *);
extern "C" int func_020984e8(void);
extern "C" int func_02099870(int);
extern "C" int func_02080190(int, void *, int);

class VBase {
  public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual int method();
};

struct UnkStruct_02067728 {
    char pad_00[0x14a8];
    VBase *obj;
    char pad_14AC[0x978];
    char sub;
};

extern "C" int func_02067728(UnkStruct_02067728 *self)
{
    int r6 = self->obj->method();
    int ret = 0;
    func_020a8c1c(&self->sub);
    if (r6 != 0) {
        int x = func_02099870((int) func_020984e8());
        func_02080190(r6, &self->sub, x);
        ret = 1;
    }
    return ret;
}
