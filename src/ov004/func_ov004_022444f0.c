/* func_ov004_022444f0 @ 0x022444f0, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022444f0 {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x16a - 0xac];
    short unk_16A;
    char unk_16C[0x170 - 0x16c];
    unsigned char unk_170;
    char unk_171[0x2c8 - 0x171];
    Vec3 pos;
} UnkStruct_022444f0;

void func_ov004_022444f0(UnkStruct_022444f0 *self, short *p)
{
    int lim, base;
    unsigned char f;
    Vec3 *q;

    lim = 0x300;
    base = self->unk_A8;
    f = self->unk_170;
    q = &self->pos;
    if (base != self->unk_54) {
        base = self->unk_54;
    }
    lim = lim + base;
    if (self->unk_16A < *p) {
        *p = 0;
        if (f != 0) {
            *p = 0;
            self->unk_16A = 0x10;
        } else {
            *p = 8;
            self->unk_16A = 0x14;
        }
    }
    if (f != 0 && q->y > lim) {
        self->unk_170 = 0;
    } else if (q->y < base) {
        if (q->y > base - 0x320) {
            q->y = base;
        }
        self->unk_170 = 1;
    }
}
