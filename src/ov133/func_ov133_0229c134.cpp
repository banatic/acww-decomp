/* func_ov133_0229c134 @ 0x0229c134, 0x1c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c134 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov133_0229c158(char *self);

extern "C" void func_ov133_0229c134(char *self)
{
    func_ov133_0229c158(self);
    ((UnkStruct_0229c134 *) (self + 0x11c))->f3();
}
