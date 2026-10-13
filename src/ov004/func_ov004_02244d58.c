/* func_ov004_02244d58 @ 0x02244d58, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244d58 {
    char unk_00[0x50];
    unsigned char unk_50;
    char unk_51[0x54 - 0x51];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x168 - 0xac];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02244d58;

extern int func_ov004_02244c20(UnkStruct_02244d58 *self);
extern void func_ov004_0224489c(UnkStruct_02244d58 *self, short *a, int *b, Vec3 *w);
extern int func_020644cc(int n);
extern void VEC_Subtract(Vec3 *d, Vec3 *a, Vec3 *b);
extern void func_ov004_02241b5c(Vec3 *d, Vec3 *a, int k);
extern void VEC_Add(Vec3 *d, Vec3 *a, Vec3 *b);

void func_ov004_02244d58(UnkStruct_02244d58 *self)
{
    short sh;
    int n;
    Vec3 w;
    Vec3 *p;
    int r;

    if (func_ov004_02244c20(self) != 0) {
        p = &self->pos;
        func_ov004_0224489c(self, &sh, &n, &w);
        if (n <= 0x400 && p->y <= w.y + 0x200 && p->y >= w.y - 0x200) {
            self->unk_172 = 6;
            self->unk_174 = (short) (0x14 * (func_020644cc(0xa) + 0xa));
            self->unk_168 = 0;
        } else {
            r = self->unk_50;
            if (func_020644cc(0x64) > r - 0x14) {
                if (n <= 0x3000) {
                    self->unk_54 = w.y;
                } else {
                    self->unk_54 = self->unk_A8;
                }
                self->unk_192 = (short) (sh + self->unk_192);
                VEC_Subtract(&w, p, &w);
                func_ov004_02241b5c(&w, &w, 1);
                VEC_Add(p, &w, p);
            }
        }
    } else {
        self->unk_54 = self->unk_A8;
    }
}
