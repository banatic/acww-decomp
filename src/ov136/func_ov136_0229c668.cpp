/* func_ov136_0229c668 @ 0x0229c668, 0x1a bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *ptr);

class UnkStruct_0229c668 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229c668_2 {
  public:
    char pad_00[0x94];
    UnkStruct_0229c668 inner;
};

extern "C" void func_ov136_0229c668(UnkStruct_0229c668_2 *self)
{
    func_ov002_0220a0ec(&self->inner);
    self->inner.f3();
}
