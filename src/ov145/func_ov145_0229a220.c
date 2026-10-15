/* func_ov145_0229a220 @ 0x0229a220, 0x78 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a220 {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x78];
    int unk_12C;
} UnkStruct_0229a220;

extern int func_020e895c(void *ptr, int value, int size);
extern void func_ov002_0220a4c8(void *ptr);
extern void func_ov145_0229a0fc(UnkStruct_0229a220 *self);
extern void func_ov145_0229a134(UnkStruct_0229a220 *self);

void func_ov145_0229a220(UnkStruct_0229a220 *self, int value, int flag)
{
    int clamped;
    int diff;

    if (flag) {
        clamped = value - 0x1d;
    } else {
        clamped = value + self->unk_AC;
    }
    if (clamped < 0) {
        clamped = 0;
    }
    if (clamped > 0x78) {
        clamped = 0x78;
    }

    if (flag) {
        func_020e895c(&self->unk_A8, clamped, 8);
    } else {
        self->unk_A8 = clamped;
    }

    func_ov145_0229a0fc(self);
    func_ov145_0229a134(self);

    diff = self->unk_B0 - self->unk_A8;
    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(&self->unk_12C);
        self->unk_B0 = self->unk_A8;
    }
}
