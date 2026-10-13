/* func_ov116_0229deb4 @ 0x0229deb4, 0x1c bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229deb4 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct Class {
    unsigned char pad_00[0x94];
    UnkStruct_0229deb4 sub;
};

extern "C" void func_ov002_0220a374(UnkStruct_0229deb4 *sub, int flag);

extern "C" void func_ov116_0229deb4(Class *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.m3();
}
