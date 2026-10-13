/* func_ov003_022226c8 @ 0x022226c8, 0xd0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Add(void *a, void *b, void *c);
extern void func_020044c0(void *p, int a, int b, int c);
extern void func_ov003_02222860(void *self);

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x18 - 0xa];
    Vec3 unk_18;
    char pad_24[0x30 - 0x24];
    Vec3 unk_30;
    int unk_3C;
    char pad_40[0x44 - 0x40];
    int unk_44;
    char pad_48[0x4c - 0x48];
    short unk_4C;
    char pad_4E[0x60 - 0x4e];
    int unk_60;
} UnkStruct_022226c8;

void func_ov003_022226c8(UnkStruct_022226c8 *self)
{
    volatile unsigned short t;
    unsigned int ok;
    unsigned short lo, hi;

    self->unk_3C = self->unk_3C + 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_30.y = self->unk_30.y - 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_18.y < 0) {
        ok = 0;
        self->unk_18.y = 0;
        if (self->unk_4C == 0) {
            self->unk_4C = 1;
            self->unk_30.x = (self->unk_30.x * 0x4cd) >> 12;
            self->unk_30.y = 0x600;
            self->unk_30.z = (self->unk_30.z * 0x4cd) >> 12;
            t = 0xfff1;
            t = self->unk_08;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        } else {
            self->unk_4C = 2;
            self->unk_30.x = 0;
            self->unk_30.y = 0;
            self->unk_30.z = 0;
            func_ov003_02222860(self);
        }
    }
}
