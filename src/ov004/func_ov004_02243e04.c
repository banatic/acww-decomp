/* func_ov004_02243e04 @ 0x02243e04, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243e04 {
    char unk_00[0x20];
    unsigned char unk_20;
    char unk_21[1];
    unsigned char unk_22;
    char unk_23[0x34 - 0x23];
    Vec3 unk_34;
    char unk_40[0x98 - 0x40];
    short unk_98;
    char unk_9A[0x9c - 0x9a];
    short unk_9C;
    char unk_9E[0xa4 - 0x9e];
    unsigned char unk_A4;
    char unk_A5[0xac - 0xa5];
    short unk_AC;
    char unk_AE[0x168 - 0xae];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short unk_192;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02243e04;

extern void func_ov004_02244774(UnkStruct_02243e04 *self, int a, int b);
extern void func_ov004_02243cb0(UnkStruct_02243e04 *self);
extern void func_ov004_02243c04(UnkStruct_02243e04 *self);
extern int func_ov004_02243c30(UnkStruct_02243e04 *self, short *p);
extern int func_ov004_02244764(UnkStruct_02243e04 *self);
extern int func_ov004_0224105c(int a);
extern int func_020644cc(int a);
extern void func_ov004_02244f48(Vec3 *a, Vec3 *b, int c, int d);
extern int func_0200322c(Vec3 *a, Vec3 *b);

void func_ov004_02243e04(UnkStruct_02243e04 *self)
{
    short *p;
    short *q;
    int a, b, c;

    switch (self->unk_172) {
        case 3:
        case 0xf:
            func_ov004_02244774(self, 1, 4);
            break;
        case 4:
            func_ov004_02243cb0(self);
            break;
        default:
            p = &self->unk_168;
            if (self->unk_22 != 0) {
                func_ov004_02243c04(self);
            }
            if (func_ov004_02243c30(self, p) != 0) {
                break;
            }
            q = &self->unk_98;
            if (func_ov004_02244764(self) == 1) {
                *p = (short) (5 * *q);
            } else if (self->unk_22 == 0 && *p == 0) {
                *q = (short) (5 * *q);
            }
            *p = (short) (*p + 1);
            if (*p >= *q || self->unk_20 != 0) {
                a = self->unk_192;
                c = func_ov004_0224105c(0xc);
                self->unk_AC = (short) (c + a);
                b = self->unk_AC;
                func_ov004_02244f48(&self->unk_34, &self->pos, b, (self->unk_A4 + func_020644cc(3)) << 12);
                self->unk_AC = (short) func_0200322c(&self->pos, &self->unk_34);
                self->unk_172 = 3;
                *p = 0;
                self->unk_9C = 0;
            }
            break;
    }
    self->unk_20 = 0;
}
