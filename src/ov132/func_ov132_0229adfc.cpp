/* func_ov132_0229adfc @ 0x0229adfc, 0x1a bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

class UnkStruct_0229adfc {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229adfc_2 {
    char pad_00[0x94];
    UnkStruct_0229adfc sub;
};

extern "C" void func_ov132_0229adfc(UnkStruct_0229adfc_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.f3();
}
