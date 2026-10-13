/* func_ov120_0229bb54 @ 0x0229bb54, 0x2c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov120_0229bc4c(void *);

class UnkStruct_0229bb54 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void virt();
};

struct Container {
    char pad_00[0x674];
    UnkStruct_0229bb54 obj1;
    char pad_678[0x44];
    UnkStruct_0229bb54 obj2;
};

extern "C" void func_ov120_0229bb54(Container *self)
{
    func_ov120_0229bc4c(self);
    self->obj1.virt();
    self->obj2.virt();
}
