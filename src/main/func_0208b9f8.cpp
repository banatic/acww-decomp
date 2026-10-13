/* func_0208b9f8 @ 0x0208b9f8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208b9f8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_0208b658(UnkStruct_0208b9f8 *self);

extern "C" void func_0208b9f8(UnkStruct_0208b9f8 *self)
{
    self->v3();
    func_0208b658(self);
}
