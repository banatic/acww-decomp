/* func_ov131_0229b498 @ 0x0229b498, 0x18 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229b498 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229b498_2 {
    char pad_00[0x94];
    UnkStruct_0229b498 sub;
};

extern "C" void func_ov131_0229b474(UnkStruct_0229b498_2 *self);

extern "C" void func_ov131_0229b498(UnkStruct_0229b498_2 *self)
{
    func_ov131_0229b474(self);
    UnkStruct_0229b498 *p = &self->sub;
    p->v3();
}
