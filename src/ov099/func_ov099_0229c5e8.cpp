/* func_ov099_0229c5e8 @ 0x0229c5e8, 0x20 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

class SubClass {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov099_0229c5e8(char *self)
{
    func_ov002_0220a0ec(self + 0x2274);
    ((SubClass *) (self + 0x2274))->f3();
}
