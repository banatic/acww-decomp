/* func_020f31c4 @ 0x020f31c4, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213e9d0;

struct UnkStruct_020f31c4 {
    void *unk_00;
};

extern void func_020f4514(struct UnkStruct_020f31c4 *self);

struct UnkStruct_020f31c4 *func_020f31c4(struct UnkStruct_020f31c4 *self)
{
    self->unk_00 = &data_0213e9d0;
    func_020f4514(self);
    return self;
}
