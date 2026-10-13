/* func_ov126_0229ffdc @ 0x0229ffdc, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *ptr, int zero);
struct Callbacks {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};
extern "C" int func_ov126_0229ffdc(char *self)
{
    func_ov002_0220a374(self + 0x3f90, 0);
    return ((Callbacks *) (self + 0x3f90))->f3();
}
