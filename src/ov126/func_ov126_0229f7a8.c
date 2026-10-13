/* func_ov126_0229f7a8 @ 0x0229f7a8, 0xe bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f7a8 {
    unsigned char pad_00[0xa4];
    unsigned short unk_A4;
};

void func_ov126_0229f7a8(struct UnkStruct_0229f7a8 *self, unsigned short mask)
{
    self->unk_A4 &= ~mask;
}
