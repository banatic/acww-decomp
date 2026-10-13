/* func_ov142_0229ba00 @ 0x0229ba00, 0x18 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ba00 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229ba00_2 {
    char pad_00[0xe8];
    UnkStruct_0229ba00 embedded;
};

extern "C" void func_ov142_0229b99c(UnkStruct_0229ba00_2 *self);

extern "C" void func_ov142_0229ba00(UnkStruct_0229ba00_2 *self)
{
    func_ov142_0229b99c(self);
    self->embedded.f3();
}
