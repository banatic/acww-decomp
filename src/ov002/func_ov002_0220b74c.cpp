/* func_ov002_0220b74c @ 0x0220b74c, 0x16 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220b74c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" int func_ov002_02207d5c(void *);

extern "C" void func_ov002_0220b74c(UnkStruct_0220b74c *self)
{
    func_ov002_02207d5c(self);
    self->f2();
}
