/* func_ov002_0220b57c @ 0x0220b57c, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220b57c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" int func_0208f098(void *);

extern "C" int func_ov002_0220b57c(UnkStruct_0220b57c *self)
{
    if (func_0208f098(self) == 0) {
        self->f3();
        return 1;
    }
    return 0;
}
