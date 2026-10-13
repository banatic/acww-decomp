/* func_0206781c @ 0x0206781c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8c1c(void *p);
extern "C" int func_0207f184(void *a, void *b);

class UnkStruct_0206781c {
  public:
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
    virtual void *f4();
    virtual void *f5();
    virtual void *f6();
    virtual void *f7();
    virtual void *f8();
    virtual void *f9();
    virtual void *f10();
    virtual void *f11();
    virtual void *f12();
    virtual void *f13();
    virtual void *f14();
    virtual void *f15();
    virtual void *f16();
    virtual void *f17();
    virtual void *f18();
    virtual void *f19();
    virtual void *f20();
    virtual void *f21();
    virtual void *f22();
    virtual void *f23();
    virtual void *f24();
    virtual void *f25();
    virtual void *f26();
};

extern "C" int func_0206781c(char *self)
{
    int ret;
    UnkStruct_0206781c *obj = *(UnkStruct_0206781c **) (self + 0x14a8);
    void *result = obj->f26();
    ret = 0;
    func_020a8c1c(self + 0x1d4c);
    if (result != 0) {
        if (func_0207f184(result, self + 0x1d4c) != 0) {
            ret = 1;
        }
    }
    return ret;
}
