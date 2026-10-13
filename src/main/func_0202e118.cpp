/* func_0202e118 @ 0x0202e118, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_0207f270(int);
extern unsigned short *func_02079464(int);
}

class UnkStruct_0202e118 {
  public:
    virtual int f00();
    virtual int f01();
    virtual int f02();
    virtual int f03();
    virtual int f04();
    virtual int f05();
    virtual int f06();
    virtual int f07();
    virtual int f08();
    virtual int f09();
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

extern "C" void func_0202e118(unsigned short *out, UnkStruct_0202e118 *obj)
{
    *out = 0xfff1;
    if (obj->f25() == 0) {
        return;
    }
    if (func_02003704(func_0208150c(obj->f25())) == 0) {
        return;
    }
    if (func_0207f270(obj->f25()) == 0) {
        return;
    }
    *out = *func_02079464(func_0207f270(obj->f25()));
}
