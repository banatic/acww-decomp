/* func_ov138_0229c554 @ 0x0229c554, 0xe bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c554 {
    char pad_00[0x92];
    unsigned short unk_92;
};

void func_ov138_0229c554(struct UnkStruct_0229c554 *self, unsigned short mask)
{
    unsigned short temp = self->unk_92;
    self->unk_92 = temp & ~mask;
}
