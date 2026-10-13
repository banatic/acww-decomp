/* func_ov107_0229dbfc @ 0x0229dbfc, 0x1c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov107_0229dbb4(void *self);

class UnkStruct_0229dbfc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_0229dbfc_2 {
  public:
    char pad_00[0x22b4];
    UnkStruct_0229dbfc inner;
};

extern "C" void func_ov107_0229dbfc(UnkStruct_0229dbfc_2 *self)
{
    func_ov107_0229dbb4(self);
    self->inner.v3();
}
