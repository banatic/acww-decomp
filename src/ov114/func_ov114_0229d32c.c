/* func_ov114_0229d32c @ 0x0229d32c, 0xc8 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov114_0229d4c0(void *self);
extern void func_ov002_0220a4c8(void *ptr);
extern int func_020e895c(int *ptr, int value, int arg2);

struct UnkStruct_0229d32c {
    unsigned char pad_00[0x121c];
    unsigned char unk_121C;
    unsigned char pad_121D[0x53];
    int unk_1270;
    int unk_1274;
    int unk_1278;
    unsigned char pad_127C[0x3f];
    unsigned char unk_12BB;
};

void func_ov114_0229d32c(struct UnkStruct_0229d32c *self, int param)
{
    int old = self->unk_1270;
    int diff;

    switch (self->unk_12BB) {
        case 2:
            param += self->unk_1274;
            self->unk_1270 = param;
            break;
        case 0:
            param = old - 2;
            self->unk_1270 = param;
            break;
        case 1:
            param = old + 2;
            self->unk_1270 = param;
            break;
        case 3:
            param -= 0x3a;
            func_020e895c(&self->unk_1270, param, 4);
            break;
    }

    if (self->unk_1270 < 0) {
        self->unk_1270 = 0;
    }
    if (self->unk_1270 > 0x8c) {
        self->unk_1270 = 0x8c;
    }

    func_ov114_0229d4c0(self);

    if (self->unk_12BB == 2) {
        diff = self->unk_1278 - self->unk_1270;
        if (diff >= 4 || diff <= -4) {
            func_ov002_0220a4c8(&self->unk_121C);
            self->unk_1278 = self->unk_1270;
        }
    } else {
        if (self->unk_1270 != old) {
            func_ov002_0220a4c8(&self->unk_121C);
        }
    }
}
