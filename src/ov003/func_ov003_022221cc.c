/* func_ov003_022221cc @ 0x022221cc, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Add(void *a, void *b, void *c);
extern void func_0204f794(int *out, int a, int b);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_ov003_02222860(void *self);

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x10 - 0xa];
    int unk_10;
    int unk_14;
    Vec3 unk_18;
    char pad_24[0x30 - 0x24];
    Vec3 unk_30;
    char pad_3C[0x4c - 0x3c];
    short unk_4C;
    char pad_4E[0x60 - 0x4e];
    int unk_60;
} UnkStruct_022221cc;

void func_ov003_022221cc(UnkStruct_022221cc *self)
{
    volatile unsigned short t;
    int out[3];
    unsigned int ok;
    unsigned short lo, hi;
    int q;

    self->unk_30.y = self->unk_30.y - 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_18.y < 0) {
        if (self->unk_4C == 0) {
            func_0204f794(out, self->unk_10, self->unk_14);
            q = (out[2] - self->unk_18.z) / 8;
            self->unk_30.x = (out[0] - self->unk_18.x) / 8;
            self->unk_30.y = 0x1000;
            self->unk_30.z = q;
            self->unk_4C = 1;
            t = 0xfff1;
            t = self->unk_08;
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        } else {
            self->unk_30.x = 0;
            self->unk_30.y = 0;
            self->unk_30.z = 0;
            func_ov003_02222860(self);
        }
        self->unk_18.y = 0;
    }
}
