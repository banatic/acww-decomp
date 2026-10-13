/* func_ov046_02260d50 @ 0x02260d50, 0x12 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260d50 {
    char pad_00[0xdc];
    int unk_DC;
};

extern int func_ov046_022610fc(struct UnkStruct_02260d50 *self);

void func_ov046_02260d50(struct UnkStruct_02260d50 *self)
{
    self->unk_DC = func_ov046_022610fc(self);
}
