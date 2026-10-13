/* func_ov120_0229a6d0 @ 0x0229a6d0, 0x20 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);

class SubClass {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229a6d0 {
    char pad_00[0x6bc];
    SubClass sub;
};

extern "C" void func_ov120_0229a6d0(UnkStruct_0229a6d0 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.v3();
}
