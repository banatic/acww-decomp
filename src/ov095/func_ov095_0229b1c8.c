/* func_ov095_0229b1c8 @ 0x0229b1c8, 0xb8 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_020896b8(int, void *, int, int, int, int, int);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);
extern int func_ov095_022999b0(void *, int);
extern void func_ov095_0229b18c(void *, int, int);

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_0229b1c8 {
    unsigned char pad_00[0x16];
    unsigned char flag;
    unsigned char pad_17[0x44 - 0x17];
    Pair *arr;
};

void func_ov095_0229b1c8(struct UnkStruct_0229b1c8 *self, int a, int b, int c)
{
    int mode;
    int v0;
    int v1;
    int i;

    mode = 0;
    v0 = 0;
    v1 = 0;

    switch (self->flag) {
        case 1:
            mode = 1;
            break;
        case 2:
            mode = 2;
            break;
        case 4:
            break;
        default:
            break;
    }

    for (i = 0; i < 3; i++) {
        if (mode == i) {
            func_020896b8(1, self->arr + i, a, b + 2, 0xb, c, v0);
        } else {
            func_020896b8(1, self->arr + i, a, b, 0xa, c, v1);
        }
    }
    func_02088df8(1, self->arr + 3, a, b, -1, c, 0x1000, 0x1000, 0, -1, 0, 0);
    if (func_ov095_022999b0(self, 4) == 0) {
        b -= 8;
    }
    func_ov095_0229b18c(self, a, b);
}
