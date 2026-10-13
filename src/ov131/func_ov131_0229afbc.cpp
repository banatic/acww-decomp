/* func_ov131_0229afbc @ 0x0229afbc, 0x1c bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *p, int v);

class UnkStruct_0229afbc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void vm();
};

struct UnkStruct_0229afbc_2 {
    char pad_00[0x94];
    UnkStruct_0229afbc sub;
};

extern "C" void func_ov131_0229afbc(UnkStruct_0229afbc_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.vm();
}
