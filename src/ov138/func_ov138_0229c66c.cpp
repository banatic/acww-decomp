/* func_ov138_0229c66c @ 0x0229c66c, 0x1a bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);
class UnkStruct_0229c66c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};
extern "C" void func_ov138_0229c66c(void *self)
{
    func_ov002_0220a0ec((UnkStruct_0229c66c *) ((char *) self + 0x98));
    ((UnkStruct_0229c66c *) ((char *) self + 0x98))->f3();
}
