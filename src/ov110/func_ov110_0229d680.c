/* func_ov110_0229d680 @ 0x0229d680, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5d4(int, int, int);
extern int func_ov110_0229d5e4(int, int, int);
extern int func_ov110_0229d628(int);
extern int func_ov110_0229d600(int);
extern int func_ov110_0229d6c4(int, int, int);

int func_ov110_0229d680(int a, int b, int c)
{
    int res;

    res = 0x1f;
    if (c >= 0x6c) {
        if (func_ov110_0229d5d4(a, b, c)) {
            res = func_ov110_0229d628(a);
        }
    } else {
        if (func_ov110_0229d5e4(a, b, c)) {
            res = func_ov110_0229d600(a);
        }
    }
    if (res != 0x1f) {
        b = res;
    }
    return func_ov110_0229d6c4(a, b, 4);
}
