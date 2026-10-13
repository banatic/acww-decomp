/* func_ov002_0220b04c @ 0x0220b04c, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220b04c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_0208a9ac(void *);

extern "C" void func_ov002_0220b04c(UnkStruct_0220b04c *self)
{
    func_0208a9ac(self);
    self->f3();
    self->f3();
}
