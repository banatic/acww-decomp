/* func_ov108_0229c5d4 @ 0x0229c5d4, 0x20 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c5d4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
extern "C" void func_ov002_0220a0ec(UnkStruct_0229c5d4 *sub);
class UnkStruct_0229c5d4_2 {
  public:
    char pad_00[0x2498];
    UnkStruct_0229c5d4 sub;
};
extern "C" void func_ov108_0229c5d4(UnkStruct_0229c5d4_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.v3();
}
