/* func_ov004_02243fec @ 0x02243fec, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243fec {
    char unk_00[0x34];
    Vec3 dst;
    char unk_40[0x9a - 0x40];
    unsigned char unk_9A;
    char unk_9B[0xa4 - 0x9b];
    unsigned char unk_A4;
    char unk_A5[0xac - 0xa5];
    short unk_AC;
    char unk_AE[0x168 - 0xae];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02243fec;

extern int func_ov004_02245174(UnkStruct_02243fec *self);
extern short func_ov004_022447c0(short ang, int mode);
extern void func_ov004_02244f48(Vec3 *out, Vec3 *base, int ang, int r);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020644cc(int a);

void func_ov004_02243fec(UnkStruct_02243fec *self)
{
    int m;
    short d;
    int k;

    m = func_ov004_02245174(self);
    if (m != 0) {
        self->unk_AC = func_ov004_022447c0(self->ang, m);
        d = self->unk_AC;
        k = func_020644cc(3);
        func_ov004_02244f48(&self->dst, &self->pos, d, (self->unk_A4 + k) << 12);
        self->unk_AC = (short) func_0200322c(&self->pos, &self->dst);
        if (self->unk_9A != 0) {
            self->unk_172 = 0xf;
        } else {
            self->unk_172 = 0xc;
            if (self->unk_196 == 0x17) {
                self->unk_168 = 0;
            } else {
                self->unk_168 = (short) ((func_020644cc(5) + 2) * 0xa);
            }
        }
    }
}
