/* func_020f3a90 @ 0x020f3a90, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020f44f8(void *self);

struct UnkStruct_020f3a90 {
    virtual void method0();
};

struct UnkStruct_020f3a90_2 {
    char pad_00[8];
    UnkStruct_020f3a90 sub;
};

extern "C" void func_020f3a90(UnkStruct_020f3a90_2 *self)
{
    func_020f44f8(self);
    self->sub.method0();
}
