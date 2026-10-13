/* func_ov111_0229efb8 @ 0x0229efb8, 0xe bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229efb8 {
    char pad_00[0xa4];
    unsigned short unk_A4;
};

void func_ov111_0229efb8(struct UnkStruct_0229efb8 *self, unsigned short mask)
{
    self->unk_A4 &= ~mask;
}
