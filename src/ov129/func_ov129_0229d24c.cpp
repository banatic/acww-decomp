/* func_ov129_0229d24c @ 0x0229d24c, 0x1c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d24c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov129_0229d218(void *arg);

extern "C" void func_ov129_0229d24c(void *self)
{
    func_ov129_0229d218(self);
    ((UnkStruct_0229d24c *) ((char *) self + 0x3a0))->v3();
}
