/* func_0206aa04 @ 0x0206aa04, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206aa04 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual void f4() = 0;
    virtual void f5() = 0;
    virtual void f6() = 0;
    virtual void method(int x) = 0;
};

struct UnkStruct_0206aa04_2 {
    char pad_00[0x14a8];
    UnkStruct_0206aa04 *c;
};

struct UnkStruct_0206aa04_3 {
    char pad_00[0x24];
    UnkStruct_0206aa04_2 *b;
    char pad_28[0x10];
    char sub;
};

extern "C" void func_020a8750(void *p);

extern "C" void func_0206aa04(UnkStruct_0206aa04_3 *a)
{
    UnkStruct_0206aa04 *c = a->b->c;
    func_020a8750(&a->sub);
    c->method(1);
}
