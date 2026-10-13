/* func_ov112_0229f250 @ 0x0229f250, 0x20 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

class Member {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov002_0220a0ec(Member *m);

struct Container {
    char pad_00[0x4448];
    Member m;
};

extern "C" void func_ov112_0229f250(Container *self)
{
    func_ov002_0220a0ec(&self->m);
    self->m.v3();
}
