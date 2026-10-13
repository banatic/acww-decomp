/* func_0202e0c8 @ 0x0202e0c8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202e0c8 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
    virtual int f4();
    virtual int f5();
    virtual int f6();
    virtual int f7();
    virtual int f8();
    virtual int f9();
    virtual int f10();
    virtual int f11();
    virtual int f12();
    virtual int f13();
    virtual int f14();
    virtual int f15();
    virtual int f16();
    virtual int f17();
    virtual int f18();
    virtual int f19();
    virtual int f20();
    virtual int f21();
    virtual int f22();
    virtual int f23();
    virtual int f24();
    virtual int f25();
};

extern "C" void func_0208150c(int);
extern "C" int func_02003704(void);
extern "C" int func_0207f270(int);
extern "C" void func_0207945c(int, int);

extern "C" void func_0202e0c8(UnkStruct_0202e0c8 *obj, int param2)
{
    if (obj->f25() == 0) {
        return;
    }
    func_0208150c(obj->f25());
    if (func_02003704() == 0) {
        return;
    }
    if (func_0207f270(obj->f25()) == 0) {
        return;
    }
    func_0207945c(func_0207f270(obj->f25()), param2);
}
