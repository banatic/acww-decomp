/* func_ov004_02225470 @ 0x02225470, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02225470 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
extern "C" void func_ov004_02225470(UnkStruct_02225470 *self, int v)
{
    self->v2();
    *(int *) ((char *) self + 0xb0) = v;
}
