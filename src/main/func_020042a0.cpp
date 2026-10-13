/* func_020042a0 @ 0x020042a0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020042a0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int arg);
};

extern "C" void func_020042a0(UnkStruct_020042a0 *self, int arg)
{
    self->v2(arg);
}
