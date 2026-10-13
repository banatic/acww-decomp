/* func_ov144_02299a30 @ 0x02299a30, 0x94 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a784(void *ptr, int arg);

struct UnkStruct_02299a30 {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xb8 - 0xa4];
    signed short unk_B8;
    char pad_BA[0x170 - 0xba];
    int unk_170;
};

int func_ov144_02299a30(struct UnkStruct_02299a30 *self, int x, int y)
{
    if (func_ov002_0220a784(&self->unk_170, 6) != 0) {
        return 9;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x20 && y <= 0x40)) {
        return 0xb;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x78 && y <= 0x88)) {
        return 0xc;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x60 && y <= 0x70)) {
        return 0xd;
    }

    if (x >= 0x40 && x <= 0xc0 && y >= 0x18 && y < 0x98) {
        int res = (y - (0x18 - (self->unk_A0 & 0xf))) >> 4;
        if (res >= self->unk_B8) {
            goto fail;
        }
        return (unsigned char) res;
    }
fail:
    return 0xe;
}
