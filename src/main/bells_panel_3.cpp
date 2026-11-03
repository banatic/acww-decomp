/* bells_panel_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b9f8 @ 0x0208b9f8, 0x16 bytes, Thumb
 * func_0208b9e0 @ 0x0208b9e0, 0x16 bytes, Thumb
 */

class UnkStruct_0208b9f8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_0208b658(UnkStruct_0208b9f8 *self);

class UnkStruct_0208b9e0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void func_0208b6ec(UnkStruct_0208b9e0 *self);

extern "C" void func_0208b9f8(UnkStruct_0208b9f8 *self)
{
    self->v3();
    func_0208b658(self);
}

extern "C" void func_0208b9e0(UnkStruct_0208b9e0 *self)
{
    func_0208b6ec(self);
    self->v2();
}
