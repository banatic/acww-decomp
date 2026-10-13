/* func_ov051_0226101c @ 0x0226101c, 0x1a bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226101c {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xac];
    int val;
};

extern "C" void func_ov051_0226101c(UnkStruct_0226101c *self, int v)
{
    self->f2();
    self->val = v;
}
