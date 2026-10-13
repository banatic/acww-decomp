/* func_0208bfd0 @ 0x0208bfd0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208bfd0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x28 - 4];
    char sub[4];
};

extern "C" void func_0208c638(void *sub);

extern "C" void func_0208bfd0(UnkStruct_0208bfd0 *self)
{
    self->v2();
    func_0208c638(self->sub);
}
