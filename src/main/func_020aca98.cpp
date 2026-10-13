/* func_020aca98 @ 0x020aca98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020aca98 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void method4(int, int);
};

struct UnkStruct_020aca98_2 {
    char pad_00[0x10];
    UnkStruct_020aca98 inner;
};

extern "C" void func_0208aef4(UnkStruct_020aca98_2 *o, int b, int c);

extern "C" void func_020aca98(UnkStruct_020aca98_2 *o, int b, int c)
{
    func_0208aef4(o, b, c);
    UnkStruct_020aca98 *obj = &o->inner;
    obj->method4(b, c);
}
