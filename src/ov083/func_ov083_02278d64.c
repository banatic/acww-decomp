/* func_ov083_02278d64 @ 0x02278d64, 0x18 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278d64 {
    struct UnkStruct_02278d64 *unk_00;
};

extern struct UnkStruct_02278d64 data_ov083_022791fc;
extern void func_0202eb20(struct UnkStruct_02278d64 *self);

struct UnkStruct_02278d64 *func_ov083_02278d64(struct UnkStruct_02278d64 *self)
{
    self->unk_00 = &data_ov083_022791fc;
    func_0202eb20(self);
    return self;
}
