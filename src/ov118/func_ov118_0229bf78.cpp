/* func_ov118_0229bf78 @ 0x0229bf78, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov118_0229c070(void *p);

class VBase {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct Container {
    char pad_00[0x678];
    VBase a;
    char pad1[0x6c0 - 0x678 - sizeof(VBase)];
    VBase b;
};

extern "C" void func_ov118_0229bf78(Container *self)
{
    func_ov118_0229c070(self);
    self->a.v3();
    self->b.v3();
}
