/* func_ov144_0229a4c8 @ 0x0229a4c8, 0x78 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a4c8 {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x128 - 0xb4];
} UnkStruct_0229a4c8;

extern void *func_020e895c(void *s, int c, unsigned int n);
extern void func_ov144_0229a3a4(UnkStruct_0229a4c8 *self);
extern void func_ov144_0229a3dc(UnkStruct_0229a4c8 *self);
extern void func_ov002_0220a4c8(void *receiver);

void func_ov144_0229a4c8(UnkStruct_0229a4c8 *self, int a, int flag)
{
    int d;

    if (flag) {
        a -= 0x1d;
    } else {
        a += self->unk_AC;
    }

    if (a < 0) {
        a = 0;
    }
    if (a > 0x78) {
        a = 0x78;
    }

    if (flag) {
        func_020e895c((char *) self + 0xa8, a, 8);
    } else {
        self->unk_A8 = a;
    }

    func_ov144_0229a3a4(self);
    func_ov144_0229a3dc(self);

    d = self->unk_B0 - self->unk_A8;
    if (d >= 4 || d <= -4) {
        func_ov002_0220a4c8((char *) self + 0x128);
        self->unk_B0 = self->unk_A8;
    }
}
