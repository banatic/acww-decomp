/* func_ov105_0229cfc0 @ 0x0229cfc0, 0x24 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct SubClass {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229cfc0 {
    char pad_00[0x24a4];
    SubClass sub;
};

extern "C" void func_ov002_0220a374(void *p, int x);

extern "C" void func_ov105_0229cfc0(UnkStruct_0229cfc0 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}
