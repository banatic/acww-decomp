/* func_ov116_0229e354 @ 0x0229e354, 0x18 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229e354 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class Main {
  public:
    char pad_00[0x94];
    UnkStruct_0229e354 sub;
};

extern "C" void func_ov116_0229e334(Main *self);

extern "C" void func_ov116_0229e354(Main *self)
{
    func_ov116_0229e334(self);
    self->sub.v3();
}
