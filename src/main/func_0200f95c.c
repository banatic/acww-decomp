/* func_0200f95c @ 0x0200f95c, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_0200f95c;

typedef struct {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x8e - 0x64];
    short unk_8E;
    unsigned char pad_90[0x2d0 - 0x90];
    int unk_2D0;
    unsigned char pad_2D4[0x6c8 - 0x2d4];
    int fAx, fAy, fAz;
    int fBx, fBy, fBz;
    unsigned char pad_6E0[0x704 - 0x6e0];
    int unk_704;
} UnkStruct_0200f95c_2;

extern int func_02056f28(void *flags, int bit);
extern void func_020912d4(int type, void *a, void *b, int c);
extern void func_0200f888(UnkStruct_0200f95c_2 *self);

void func_0200f95c(UnkStruct_0200f95c_2 *self)
{
    short arr[2];
    UnkStruct_0200f95c v;

    if (!(func_02056f28(&self->unk_2D0, 1) || func_02056f28(&self->unk_2D0, 9))) {
        return;
    }

    arr[0] = self->unk_8E;
    arr[1] = arr[0] + 0x8000;

    if (func_02056f28(&self->unk_2D0, 9)) {
        v.x = self->fAx;
        v.y = self->fAy;
        v.z = self->fAz;
    } else {
        v.x = self->fBx;
        v.y = self->fBy;
        v.z = self->fBz;
    }
    v.y = self->unk_60;

    if (self->unk_704 == 2) {
        func_020912d4(0, &v, &arr[1], 0);
    }
    func_020912d4(0x27, &v, &arr[0], 0);

    func_0200f888(self);
}
