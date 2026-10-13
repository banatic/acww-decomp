/* func_ov004_02244224 @ 0x02244224, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244224 {
    char unk_00[0x40];
    Vec3 tgt;
    char unk_4C[0xae - 0x4c];
    unsigned char unk_AE;
    char unk_AF[0x172 - 0xaf];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02244224;

extern int func_020e91ac(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020644cc(int a);

void func_ov004_02244224(UnkStruct_02244224 *self)
{
    Vec3 *p, *q;
    int m, k;

    p = &self->pos;
    q = &self->tgt;
    switch (self->unk_196) {
        case 0x15:
            k = 0x148;
            m = 0x40;
            break;
        case 0x16:
            k = 0x19a;
            m = 0x49;
            break;
        default:
            k = 0x19a;
            m = 0x4e;
            break;
    }
    if (func_020e91ac(p, q, m, 0x1000, k) == 0) {
        self->unk_172 = 0x19;
        self->unk_174 = (func_020644cc(5) + 5) * 0x14;
        self->unk_AE = 1;
    } else {
        self->ang = (short) func_0200322c(p, q);
    }
}
