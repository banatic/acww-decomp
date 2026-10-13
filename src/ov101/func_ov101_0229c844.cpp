/* func_ov101_0229c844 @ 0x0229c844, 0x24 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c844 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229c844_2 {
    char pad_00[0x229c];
    UnkStruct_0229c844 obj;
};

extern "C" void func_ov002_0220a374(UnkStruct_0229c844 *p, int flag);

extern "C" void func_ov101_0229c844(UnkStruct_0229c844_2 *self)
{
    func_ov002_0220a374(&self->obj, 0);
    self->obj.v3();
}
