/* func_ov004_0223383c @ 0x0223383c, 0xdc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0223383c {
    char unk_00[0xa];
    unsigned short unk_0A;
    char unk_0C[0x1c - 0xc];
    int unk_1C;
    char unk_20[8];
    int unk_28;
    char unk_2C[4];
    int unk_30, unk_34, unk_38, unk_3C;
    char unk_40[4];
    int unk_44;
    char unk_48[0x8c - 0x48];
    signed char unk_8C;
} UnkStruct_0223383c;

extern void VEC_Add(char *d, char *a, char *b);
extern void func_020044c0(char *p, int a, int b, int c);
extern void func_ov004_022339e0(UnkStruct_0223383c *self);

void func_ov004_0223383c(UnkStruct_0223383c *self)
{
    volatile unsigned short t;
    int ok;
    unsigned short lo, hi;

    self->unk_3C = self->unk_3C + 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_34 = self->unk_34 - 0x400;
    VEC_Add((char *) self + 0x24, (char *) self + 0x30, (char *) self + 0x24);
    if (self->unk_34 < 0 && self->unk_28 < self->unk_1C) {
        if (self->unk_8C < 2) {
            t = 0xfff1;
            t = self->unk_0A;
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok != 0) {
                func_020044c0((char *) self + 0x4c, 0x70, 0x7f, 0);
            }
        }
        self->unk_28 = self->unk_1C;
        if (self->unk_8C == 0) {
            self->unk_8C = 1;
            self->unk_34 = 0x600;
            self->unk_30 = (0x4cd * self->unk_30) >> 12;
            self->unk_38 = (0x4cd * self->unk_38) >> 12;
        } else {
            self->unk_30 = 0;
            self->unk_34 = 0;
            self->unk_38 = 0;
            func_ov004_022339e0(self);
        }
    }
}
