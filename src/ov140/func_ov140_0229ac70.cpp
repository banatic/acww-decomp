/* func_ov140_0229ac70 @ 0x0229ac70, 0x1c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ac70 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229ac70_2 {
    char pad_00[0x128c];
    UnkStruct_0229ac70 sub;
};

extern "C" void func_ov140_0229ac34(UnkStruct_0229ac70_2 *self);

extern "C" void func_ov140_0229ac70(UnkStruct_0229ac70_2 *self)
{
    func_ov140_0229ac34(self);
    self->sub.v3();
}
