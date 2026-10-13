/* func_ov004_02244904 @ 0x02244904, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244904_2 {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0x9a - 0x58];
    unsigned char unk_9A;
    char unk_9B[1];
    short unk_9C;
    short unk_9E;
    char unk_A0[0xa8 - 0xa0];
    int unk_A8;
    char unk_AC[0x172 - 0xac];
    short unk_172;
    int unk_174;
    char unk_178[0x2c8 - 0x178];
    Vec3 pos;
} UnkStruct_02244904_2;

typedef struct {
    Vec3 v;
    char unk_0C[0x14 - 0x0c];
    unsigned char unk_14;
    char unk_15[7];
} UnkStruct_02244904;

extern int func_ov004_02244658(UnkStruct_02244904_2 *self, UnkStruct_02244904 *s);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020644cc(int a);

int func_ov004_02244904(UnkStruct_02244904_2 *self)
{
    UnkStruct_02244904 s;
    int r;

    r = func_ov004_02244658(self, &s);
    if (s.unk_14 != 0 && self->unk_9A == 0 && self->unk_9C >= self->unk_9E) {
        *(short *) ((char *) self + 0xac) = (short) func_0200322c(&s.v, &self->pos);
        self->unk_174 = (func_020644cc(4) + 0xa) * 0x14;
        self->unk_172 = 7;
        self->unk_9A = 1;
        self->unk_54 = self->unk_A8;
    }
    return r;
}
