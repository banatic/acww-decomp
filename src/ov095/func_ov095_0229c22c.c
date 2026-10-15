/* func_ov095_0229c22c @ 0x0229c22c, 0x1f4 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c22c UnkStruct_0229c22c;

extern int func_0206f5e4(int);
extern void func_0206f5d8(int, int);
extern int func_ov095_022999b0(UnkStruct_0229c22c *, int);
extern int func_02002d14(void *, void *, unsigned int, int, int, int);
extern int func_02064af4(const void *, void *, unsigned int);
extern unsigned char *func_02064b2c(const void *, void *, int, int);
extern void MI_CpuCopy8(void *, void *, unsigned int);
extern void func_ov095_0229bf70(UnkStruct_0229c22c *);
extern void func_020e993c(void *, void *);
extern int func_020b9c10(void *, void *, unsigned int, int, int, int);
extern void func_ov095_0229cef4(UnkStruct_0229c22c *, int);
extern void func_ov095_0229ce84(UnkStruct_0229c22c *, int);
extern void func_ov095_0229b3ec(UnkStruct_0229c22c *);
extern void func_ov095_0229cd30(UnkStruct_0229c22c *);

extern void *data_021fbe94;
extern const void *const data_ov095_0229e5f8[];
extern const void *const data_ov095_0229e61c[];
extern const void *const data_ov095_0229e640[];

struct UnkStruct_0229c22c {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x1b - 0x17];
    unsigned char unk_1B;
    unsigned char pad_1C[0x48 - 0x1c];
    unsigned char unk_48[1];
    unsigned char pad_49[0x2308 - 0x49];
    unsigned char unk_2308[1];
    unsigned char pad_2309[0x2668 - 0x2309];
    unsigned char unk_2668[1];
};

extern unsigned char data_ov095_0229ee74[];

void func_ov095_0229c22c(UnkStruct_0229c22c *self, int state, unsigned int p2, int p3)
{
    void *v;
    const void *ptr;
    unsigned char *ret;

    if (state == 9) {
        state = func_0206f5e4(self->unk_16);
    }
    if (state == 3 && func_ov095_022999b0(self, 0x20)) {
        func_0206f5d8(self->unk_16, 2);
    } else {
        func_0206f5d8(self->unk_16, state);
    }

    v = data_021fbe94;

    if (p3 == 0) {
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 1, 4);
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 7, 7);
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 9, 9);
    }

    if (self->unk_1B == state && p3 != 0) {
        goto done;
    }

    ptr = data_ov095_0229e5f8[state];
    func_02064af4(ptr, self->unk_48, 0x22c0);

    if (func_ov095_022999b0(self, 4) != 0) {
        ptr = data_ov095_0229e61c[state];
    } else {
        ptr = data_ov095_0229e640[state];
    }

    ret = func_02064b2c(ptr, v, -4, 0);
    MI_CpuCopy8(ret + 0x240, self->unk_2668, 0x380);
    func_ov095_0229bf70(self);
    func_020e993c(v, ret);
    func_020b9c10(self->unk_2308, self->unk_48, p2, 0x1ea, 0x1ea, 0x2ff);

    self->unk_1B = state;

    switch (self->unk_1B) {
        case 0:
            func_ov095_0229cef4(self, 1);
            func_ov095_0229ce84(self, 2);
            break;
        case 1:
            func_ov095_0229ce84(self, 1);
            func_ov095_0229cef4(self, 2);
            break;
        case 2:
        case 3:
            func_ov095_0229cef4(self, 8);
            func_ov095_0229ce84(self, 9);
            func_ov095_0229ce84(self, 10);
            func_ov095_0229ce84(self, 7);
            func_ov095_0229ce84(self, 13);
            break;
        case 4:
            func_ov095_0229ce84(self, 8);
            func_ov095_0229cef4(self, 9);
            func_ov095_0229ce84(self, 10);
            func_ov095_0229cef4(self, 7);
            func_ov095_0229cef4(self, 13);
            break;
        case 5:
            func_ov095_0229ce84(self, 8);
            func_ov095_0229ce84(self, 9);
            func_ov095_0229cef4(self, 10);
            func_ov095_0229cef4(self, 7);
            func_ov095_0229cef4(self, 13);
            break;
        case 6:
            break;
    }

    func_ov095_0229b3ec(self);

done:
    func_ov095_0229cd30(self);
}
