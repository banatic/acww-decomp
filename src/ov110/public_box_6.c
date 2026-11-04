/* public_box_6: 2 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229d680 @ 0x0229d680, 0x44 bytes, Thumb
 * func_ov110_0229d648 @ 0x0229d648, 0x38 bytes, Thumb
 */

typedef struct UnkStruct_0229d648 {
    char pad_00[0xA8];
    int unk_A8;
    int unk_AC;
} UnkStruct_0229d648;

extern int func_ov110_0229d5d4(int, int);
extern int func_ov110_0229d5e4(int, int);
extern unsigned char func_ov110_0229d628(void *receiver);
extern int func_ov110_0229d600(int);
extern int func_ov110_0229d6c4(int, int, int);
extern void func_ov110_0229cd14(void *a, void *b);
extern int func_ov110_0229d3d8(void *a, void *b);
extern int func_ov110_0229d388(void *a, void *b);

int func_ov110_0229d680(int a, int b, int c)
{
    int res;

    res = 0x1f;
    if (c >= 0x6c) {
        if (func_ov110_0229d5d4(a, b)) {
            res = func_ov110_0229d628((void *) a);
        }
    } else {
        if (func_ov110_0229d5e4(a, b)) {
            res = func_ov110_0229d600(a);
        }
    }
    if (res != 0x1f) {
        b = res;
    }
    return func_ov110_0229d6c4(a, b, 4);
}

void func_ov110_0229d648(UnkStruct_0229d648 *p, void *q, int n)
{
    func_ov110_0229cd14(p, q);
    p->unk_A8 = func_ov110_0229d3d8(p, q);
    p->unk_AC = func_ov110_0229d388(p, q);
    func_ov110_0229d6c4((int) p, n, 4);
}
