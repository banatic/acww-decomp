/* func_ov068_0226d374 @ 0x0226d374, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226d374 {
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
    virtual int v25();
};

extern "C" int func_0208150c(int);
extern "C" int func_02003704(int);
extern "C" int func_0207f270(int);
extern "C" int func_020794cc(int);
extern "C" int func_0207f1c8(int);
extern "C" int func_0209b5ec(void *object);
extern "C" void func_0209e474(int *);
extern "C" int func_0209c38c(int);
extern "C" int func_0209c330(int);
extern "C" int func_0209c1cc(int, int *, int);
extern "C" int func_0201cddc(UnkStruct_0226d374 *);
extern "C" void func_ov068_0226d408(UnkStruct_0226d374 *);

extern "C" void func_ov068_0226d374(UnkStruct_0226d374 *self)
{
    int obj;
    int r4;
    int local[2];

    obj = self->v25();
    if (obj == 0) {
        return;
    }
    if (func_02003704(func_0208150c(obj)) == 0) {
        return;
    }
    r4 = func_020794cc(func_0207f270(obj));
    obj = func_0209b5ec((void *) (func_0207f1c8(obj)));
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (!((func_0209c38c(r4) != 0 || r4 == 8) && (r4 == func_0209c330(obj) || func_0209c1cc(obj, local, 3) != 0)) ||
        func_0201cddc(self) == 3 || func_0201cddc(self) == 4 || func_0201cddc(self) == 5) {
        func_ov068_0226d408(self);
    }
}
