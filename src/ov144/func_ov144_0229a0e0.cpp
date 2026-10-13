/* func_ov144_0229a0e0 @ 0x0229a0e0, 0x1a bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);
class VirtualBase {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
class UnkStruct_0229a0e0 {
  public:
    char pad_00[0xc4];
    VirtualBase sub;
};
extern "C" void func_ov144_0229a0e0(UnkStruct_0229a0e0 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.v3();
}
