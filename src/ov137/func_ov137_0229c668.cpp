/* func_ov137_0229c668 @ 0x0229c668, 0x1a bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c668 {
  public:
    virtual void virt0();
    virtual void virt1();
    virtual void virt2();
    virtual void virt3();
};

struct Container {
    char pad_00[0x94];
    UnkStruct_0229c668 obj;
};

extern "C" void func_ov002_0220a0ec(void *);

extern "C" void func_ov137_0229c668(Container *self)
{
    func_ov002_0220a0ec(&self->obj);
    self->obj.virt3();
}
