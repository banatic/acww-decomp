/* func_ov102_0229e0ec @ 0x0229e0ec, 0x1c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct SubClass {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct MainObject {
    char pad_00[0x2274];
    SubClass sub;
};

extern "C" void func_ov102_0229e0b0(struct MainObject *self);

extern "C" void func_ov102_0229e0ec(struct MainObject *self)
{
    func_ov102_0229e0b0(self);
    self->sub.m3();
}
