/* func_020b9ccc @ 0x020b9ccc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b9ccc {
  public:
    virtual void v0();
    virtual void v1();
};

extern "C" void func_020b98ac(UnkStruct_020b9ccc *self);

extern "C" void func_020b9ccc(UnkStruct_020b9ccc *self)
{
    func_020b98ac(self);
    self->v1();
}
