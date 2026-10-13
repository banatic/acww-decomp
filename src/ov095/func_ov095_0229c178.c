/* func_ov095_0229c178 @ 0x0229c178, 0x4c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char unk_1B;
} Struct_ov095_0229c178;

extern int func_ov095_022999b0(void *p, int n);
extern void func_ov095_022999a0(void *p, int n);
extern void func_ov095_0229c22c(void *p, int a, int b, int c);

void func_ov095_0229c178(Struct_ov095_0229c178 *p, int param)
{
    if (func_ov095_022999b0(p, 0x20) != 0) {
        p->unk_1B = 2;
        func_ov095_022999a0(p, 0x20);
    }
    switch (p->unk_1B) {
        case 2:
            func_ov095_0229c22c(p, 3, param, 1);
            break;
        case 3:
            func_ov095_0229c22c(p, 2, param, 1);
            break;
        default:
            break;
    }
}
