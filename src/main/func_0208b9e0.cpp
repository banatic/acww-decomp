/* func_0208b9e0 @ 0x0208b9e0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208b9e0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void func_0208b6ec(UnkStruct_0208b9e0 *self);

extern "C" void func_0208b9e0(UnkStruct_0208b9e0 *self)
{
    func_0208b6ec(self);
    self->v2();
}
