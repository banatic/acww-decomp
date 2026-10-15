/* func_ov004_0220c6b8 @ 0x0220c6b8, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220c6b8_2 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
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
    virtual void f25();
    virtual void f26();
    virtual void f27();
    virtual void f28();
    virtual void f29();
    virtual void f30();
    virtual void f31();
    virtual void f32();
    virtual void f33();
    virtual void f34();
    virtual void f35();
    virtual void f36();
};

struct UnkStruct_0220c6b8 {
    int a, b, c, d;
};

extern "C" void func_ov004_0220fefc(UnkStruct_0220c6b8_2 *, UnkStruct_0220c6b8 *);
extern "C" void func_ov004_0223bac8(UnkStruct_0220c6b8 *);
extern "C" int func_02095380(int);

extern "C" int func_ov004_0220c6b8(UnkStruct_0220c6b8_2 *self)
{
    UnkStruct_0220c6b8 local;
    self->f36();
    *(short *) ((char *) self + 0x770) = 0;
    func_ov004_0220fefc(self, &local);
    func_ov004_0223bac8(&local);
    func_02095380(0x4c8);
    return 1;
}
