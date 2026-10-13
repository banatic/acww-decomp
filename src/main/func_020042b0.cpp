/* func_020042b0 @ 0x020042b0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020042b0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(int arg);
};

extern "C" void func_020042b0(UnkStruct_020042b0 *self, int arg)
{
    self->v4(arg);
}
