/* func_ov102_0229cb50 @ 0x0229cb50, 0x24 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229cb50 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229cb50_2 {
    char pad_00[0x2274];
    UnkStruct_0229cb50 sub;
};

extern "C" void func_ov102_0229cb50(UnkStruct_0229cb50_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}
