/* func_ov144_02299ea8 @ 0x02299ea8, 0x2c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA4];
    int unk_A4;
    char pad_A8[0xB8 - (0xA4 + 4)];
    short unk_B8;
    char pad_BA[0xBC - (0xB8 + 2)];
    short unk_BC;
} UnkStruct_02299ea8;

extern int func_ov144_02299694(UnkStruct_02299ea8 *self, int val);

int func_ov144_02299ea8(UnkStruct_02299ea8 *self)
{
    self->unk_A4 = (self->unk_B8 - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    return func_ov144_02299694(self, self->unk_BC);
}
