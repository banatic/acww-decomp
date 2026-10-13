/* func_ov131_0229af24 @ 0x0229af24, 0x1a bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229af24 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229af24_2 {
    char pad_00[0x94];
    UnkStruct_0229af24 sub;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229af24 *sub);

extern "C" void func_ov131_0229af24(UnkStruct_0229af24_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.v3();
}
