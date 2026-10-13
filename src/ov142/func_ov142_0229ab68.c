/* func_ov142_0229ab68 @ 0x0229ab68, 0x18 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ab68 {
    unsigned char pad_00[0xbd];
    unsigned char unk_BD;
    unsigned char pad_BE[4];
    unsigned char unk_C2;
};

void func_ov142_0229ab68(struct UnkStruct_0229ab68 *self, unsigned char val)
{
    if (val == self->unk_BD) {
        return;
    }
    self->unk_BD = val;
    self->unk_C2 = 1;
}
