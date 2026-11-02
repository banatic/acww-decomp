/* clock_setter_flags: 3 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_022995c0 @ 0x022995c0, 0x12 bytes, Thumb
 * func_ov134_022995b0 @ 0x022995b0, 0xe bytes, Thumb
 * func_ov134_022995a0 @ 0x022995a0, 0xe bytes, Thumb
 */

struct UnkStruct_ov134_022995c0 {
    unsigned char pad_00[0x90];
    unsigned short unk_90;
};

typedef struct {
    char pad_00[0x90];
    unsigned short unk_90;
} UnkStruct_022995a0;

int func_ov134_022995c0(struct UnkStruct_ov134_022995c0 *self, unsigned int mask)
{
    if ((self->unk_90 & mask) == 0) {
        return 0;
    }
    return 1;
}

void func_ov134_022995b0(unsigned short *p, unsigned int val)
{
    p[0x48] |= val;
}

void func_ov134_022995a0(UnkStruct_022995a0 *self, unsigned short mask)
{
    self->unk_90 &= ~mask;
}
