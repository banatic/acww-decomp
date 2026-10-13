/* func_ov004_02244094 @ 0x02244094, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244094 {
    char unk_00[0x34];
    Vec3 tgt;
    char unk_40[0x4c - 0x40];
    int unk_4C;
    char unk_50[0xa8 - 0x50];
    int unk_A8;
    char unk_AC[0x16c - 0xac];
    int unk_16C;
    unsigned char unk_170;
    char unk_171[0x172 - 0x171];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02244094;

extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_020e8bb0(int *a, int b, int c, int d, int e);
extern int func_0200322c(Vec3 *a, Vec3 *b);

void func_ov004_02244094(UnkStruct_02244094 *self)
{
    Vec3 *p, *q;
    int n;

    q = &self->tgt;
    p = &self->pos;
    n = self->unk_16C;
    if (func_020e908c(p, q, n, 0x1000, self->unk_4C) == 0) {
        self->unk_172 = 0x19;
    } else {
        self->ang = (short) func_0200322c(p, q);
    }
    if (self->unk_170 != 0) {
        func_020e8bb0(&p->y, self->unk_A8, n, 0x1000, 0xcd);
    } else {
        if (func_020e8bb0(&p->y, self->unk_A8 - 0x1000, n, 0x1000, 0xcd) == 0) {
            self->unk_170 = 1;
        }
    }
}
