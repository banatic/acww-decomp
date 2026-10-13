/* func_020be904 @ 0x020be904, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020be6ac(void *self, int a, int b);
extern int func_ov003_02220c8c(int flag, int v, int c);
extern void func_020bf2b8(int *out, int a, int b, int c);
extern void func_020be5d0(int *a, int b, int c, int *d);
extern void func_ov003_02219774(int arg);
extern void func_020be758(void *self);
extern int data_021fbb14;

struct UnkStruct_020be904 {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char pad_18[6];
    unsigned char unk_1E;
    unsigned char unk_1F;
    unsigned char unk_20;
    unsigned char unk_21;
};

void func_020be904(struct UnkStruct_020be904 *self)
{
    int flag;
    int v;

    func_020be6ac(self, 0x190, 0x190);

    if (self->unk_08 > 0) {
        self->unk_08--;
        if (self->unk_08 == 0) {
            flag = (self->unk_21 != 0) ? 1 : 0;
            v = ((self->unk_0C + 0x800) >> 12) - 0x80;
            if (func_ov003_02220c8c(flag, v, self->unk_0C) == 0) {
                self->unk_1E = 1;
            }
        }
    }

    if (self->unk_1F != 0 || self->unk_20 != 0) {
        int p;
        int local[3];

        p = (self->unk_1F != 0) ? 0x7f9 : 0x7fa;
        func_020bf2b8(local, self->unk_0C, self->unk_10, self->unk_14);
        func_020be5d0(&data_021fbb14, 0, p, local);
        self->unk_1F = 0;
        self->unk_20 = 0;
    }

    if (self->unk_1E != 0) {
        func_ov003_02219774(self->unk_1E);
        func_020be758(self);
    }
}
