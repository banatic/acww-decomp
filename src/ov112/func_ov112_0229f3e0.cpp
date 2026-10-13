/* func_ov112_0229f3e0 @ 0x0229f3e0, 0x24 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229f3e0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void method();
};

struct Big {
    char pad_00[0x4448];
    UnkStruct_0229f3e0 obj;
};

extern "C" void func_ov112_0229f3e0(void *base)
{
    Big *b = (Big *) base;
    func_ov002_0220a374((char *) b + 0x4448, 0);
    b->obj.method();
}
