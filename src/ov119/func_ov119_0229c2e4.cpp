/* func_ov119_0229c2e4 @ 0x0229c2e4, 0x1c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct Vtbl {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229c2e4 {
    char pad_00[0xda8];
    Vtbl member;
};

extern "C" void func_ov119_0229c318(UnkStruct_0229c2e4 *self);

extern "C" void func_ov119_0229c2e4(UnkStruct_0229c2e4 *self)
{
    func_ov119_0229c318(self);
    self->member.v3();
}
