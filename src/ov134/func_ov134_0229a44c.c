/* func_ov134_0229a44c @ 0x0229a44c, 0x98 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a44c {
    int unk_00;
    char pad_04[161];
    unsigned char unk_A5;
    char pad_A6[5];
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char unk_AD;
};

extern int func_ov134_0229aaa8(struct UnkStruct_0229a44c *, int);
extern int func_ov134_0229aa4c(struct UnkStruct_0229a44c *, int);
extern int func_ov134_02299bcc(struct UnkStruct_0229a44c *, int);

int func_ov134_0229a44c(struct UnkStruct_0229a44c *p, int n, int m)
{
    int shifted;
    int low;
    int diff;
    int pos;

    if (m <= 0x28 || m >= 0xa8) {
        return 0;
    }

    shifted = n >> 3;

    if (func_ov134_0229aaa8(p, p->unk_A5) > shifted || func_ov134_0229aa4c(p, p->unk_A5) < shifted) {
        return 0;
    }

    low = p->unk_00 & 0xf;

    if (m >= 0xb2 - low) {
        return 2;
    }

    if (m <= ((0x10 - low) & 0xf) + 0x1e) {
        return 2;
    }

    diff = m - (p->unk_AB - p->unk_00);

    if (diff < 0) {
        return 2;
    }

    pos = diff >> 4;

    if (pos >= p->unk_AC) {
        return 2;
    }

    if (func_ov134_02299bcc(p, pos) != 0) {
        return 2;
    }

    p->unk_AD = pos;
    return 1;
}
