/* func_ov109_0229c828 @ 0x0229c828, 0x24 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c828 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void target();
};

extern "C" void func_ov002_0220a374(UnkStruct_0229c828 *, int);

class UnkStruct_0229c828_2 {
  public:
    char pad_00[0x2274];
    UnkStruct_0229c828 sub;
};

extern "C" void func_ov109_0229c828(UnkStruct_0229c828_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.target();
}
