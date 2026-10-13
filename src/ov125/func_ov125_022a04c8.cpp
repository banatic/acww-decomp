/* func_ov125_022a04c8 @ 0x022a04c8, 0x1c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a04c8 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_022a04c8_2 {
    unsigned char pad_00[0x644];
    UnkStruct_022a04c8 sub;
};

extern "C" void func_ov125_022a04a0(UnkStruct_022a04c8_2 *);

extern "C" void func_ov125_022a04c8(UnkStruct_022a04c8_2 *self)
{
    func_ov125_022a04a0(self);
    self->sub.f3();
}
