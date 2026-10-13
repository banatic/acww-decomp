/* func_020f2eb0 @ 0x020f2eb0, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f2eb0_2 {
    virtual void vfunc0();
};

struct UnkStruct_020f2eb0 {
    int unk_00;
    int unk_04;
    UnkStruct_020f2eb0_2 base;
};

extern "C" void func_020f44f8(UnkStruct_020f2eb0 *self);
extern "C" void func_020f2eb0(UnkStruct_020f2eb0 *self)
{
    func_020f44f8(self);
    self->base.vfunc0();
}
