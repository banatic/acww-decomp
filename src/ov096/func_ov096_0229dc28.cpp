/* func_ov096_0229dc28 @ 0x0229dc28, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);
class MyVirt {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};
extern "C" void func_ov096_0229dc28(char *self)
{
    func_ov002_0220a0ec(self + 0x2500);
    ((MyVirt *) (self + 0x2500))->m3();
}
