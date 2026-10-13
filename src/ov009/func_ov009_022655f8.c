/* func_ov009_022655f8 @ 0x022655f8, 0x38 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022655f8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
};

int func_ov009_022655f8(struct UnkStruct_022655f8 *self)
{
    if (self->unk_00 != 0 || self->unk_04 != 0 || self->unk_14 != 0 || self->unk_18 != 0 || self->unk_1C != 0 ||
        self->unk_08 != 0 || self->unk_0C != 0 || self->unk_10 != 0) {
        return 1;
    }
    return 0;
}
