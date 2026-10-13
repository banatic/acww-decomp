/* func_ov134_022995c0 @ 0x022995c0, 0x12 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_ov134_022995c0 {
    unsigned char pad_00[0x90];
    unsigned short unk_90;
};

int func_ov134_022995c0(struct UnkStruct_ov134_022995c0 *self, unsigned int mask)
{
    if ((self->unk_90 & mask) == 0) {
        return 0;
    }
    return 1;
}
