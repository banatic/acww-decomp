/* func_ov068_02272550 @ 0x02272550, 0x104 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_02262ed4(void *a, int b);
extern void func_ov068_02272be4(void *self);
extern int func_02056f94(void *a);
extern void func_ov068_02272a7c(void *self, int a);
extern void func_02055124(void *a);
extern void *func_020961a8(int a);
extern int func_ov068_02272cd4(void *self);
extern int func_020e8b4c(int a, int b);
extern void func_02095518(int a, int b, int c);
extern int func_ov003_02220174(int a);
extern int func_ov009_0226321c(int a, int *b, int *c);
extern void func_02095ab0(void *a, int b, int c);

struct UnkStruct_02272550 {
    char pad_00[0x13c];
    char unk_13C;
    char pad_13D[0x1d8 - 0x13d];
    char unk_1D8;
    char pad_1D9[0x238 - 0x1d9];
    char unk_238;
    char pad_239[0x2c0 - 0x239];
    int unk_2C0;
    int unk_2C4;
    int unk_2C8;
    char pad_2CC[0x2dc - 0x2cc];
    unsigned char unk_2DC;
};

void func_ov068_02272550(struct UnkStruct_02272550 *self)
{
    void *p;
    int r;
    short val;
    int result;
    int arr[4];

    func_ov009_02262ed4(&self->unk_238, 0x889);
    func_ov068_02272be4(self);
    if (func_02056f94(&self->unk_1D8) != 0) {
        func_ov068_02272a7c(self, 7);
        return;
    }
    func_02055124(&self->unk_13C);
    p = func_020961a8(4);
    if (p == 0) {
        return;
    }
    val = *(short *) ((char *) p + 0x8e);
    result = func_020e8b4c(val, func_ov068_02272cd4(self));
    if (result < 0x1200) {
        func_02095518(0, (short) (func_ov068_02272cd4(self) - val), 4);
        return;
    } else {
        if (self->unk_2DC < 0xc8) {
            self->unk_2DC++;
        }
        if (self->unk_2DC != 0x10) {
            return;
        }
        r = func_ov003_02220174(0x5000);
        if (r == 0) {
            return;
        }
        if (func_ov009_0226321c(r, &arr[1], &arr[0])) {
            self->unk_2C0 = arr[1];
            self->unk_2C4 = arr[2];
            self->unk_2C8 = arr[3];
            self->unk_2C8 += 0x200;
            func_02095518(0, 0, 4);
            func_02095ab0(&self->unk_2C0, 0x400, 4);
        }
    }
}
