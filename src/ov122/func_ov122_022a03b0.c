/* func_ov122_022a03b0 @ 0x022a03b0, 0xd8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a03b0 UnkStruct_022a03b0;

struct UnkStruct_022a03b0 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x29];
    unsigned char b6;
    unsigned char b7;
    unsigned char pad_B8[4];
    void *unk_BC;
    unsigned char pad_C0[0x3ce8 - 0xc0];
    unsigned char unk_3CE8;
    unsigned char pad_3CE9[0x42b0 - 0x3ce9];
    unsigned char sub;
};

extern int func_ov002_02208e18(void *);
extern int func_ov002_02208a24(void *, void *, unsigned char);
extern void func_0206e1d8(void *, void *);
extern void func_ov122_022a15b8(UnkStruct_022a03b0 *, int, int);
extern void func_ov002_022080a0(UnkStruct_022a03b0 *, int);
extern unsigned int func_ov002_02208ad0(void *);
extern void func_ov122_0229f0dc(UnkStruct_022a03b0 *, int);
extern int func_ov122_0229efe8(UnkStruct_022a03b0 *, int);
extern void func_ov122_022a1e00(UnkStruct_022a03b0 *);

void func_ov122_022a03b0(UnkStruct_022a03b0 *self)
{
    int r;

    if (func_ov002_02208e18(&self->sub) == 0) {
        return;
    }

    r = func_ov002_02208a24(&self->sub, self->unk_BC, self->b6);

    switch (r) {
        case 1:
            func_0206e1d8(&self->unk_3CE8, self->unk_BC);
            func_ov122_022a15b8(self, 1, 0);
            self->unk_8C = 0xa;
            func_ov002_022080a0(self, 1);
            break;

        case 2:
            self->b7 = self->b7 + 1;
            if (self->b7 >= func_ov002_02208ad0(&self->sub)) {
                self->b7 = 0;
            }
            func_ov122_0229f0dc(self, 0);
            break;

        case 3:
            if (func_ov122_0229efe8(self, 0x2000) != 0) {
                func_ov122_022a1e00(self);
            } else {
                self->unk_8C = 0xa;
                func_ov002_022080a0(self, 1);
            }
            break;

        default:
            self->unk_8C = 0xa;
            func_ov002_022080a0(self, 1);
            break;
    }
}
