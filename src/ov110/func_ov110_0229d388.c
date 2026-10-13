/* func_ov110_0229d388 @ 0x0229d388, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(char *, int);
extern int func_ov110_0229d5d4(char *, int);
extern int func_ov110_0229d590(char *, int);
extern int func_ov110_0229d5c8(char *, int);
extern int func_ov094_0229ab90(char *, int);

int func_ov110_0229d388(char *a, int b)
{
    if (func_ov110_0229d5e4(a, b) || func_ov110_0229d5d4(a, b)) {
        return func_ov094_0229ab90(a + 0x138, func_ov110_0229d590(a, b));
    } else {
        if (func_ov110_0229d5c8(a, b) != 0) {
            return 104;
        } else {
            return 0;
        }
    }
}
