/* func_ov126_022a1480 @ 0x022a1480, 0x1c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

class C023A1480 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};
extern "C" void func_ov126_022a1448(void *);
extern "C" void func_ov126_022a1480(void *self)
{
    func_ov126_022a1448(self);
    ((C023A1480 *) ((char *) self + 0x3f90))->f3();
}
