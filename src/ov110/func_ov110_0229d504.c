/* func_ov110_0229d504 @ 0x0229d504, 0x7c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d580(int, int);
extern int func_ov110_0229d428(int, int);
extern int func_ov094_0229aee8(int, int unused1, int unused2);
extern int func_ov094_0229a69c(int, int);
extern int func_ov094_0229aeb8(int, int, int);

int func_ov110_0229d504(int r5, int r7, int r2, int r4)
{
    int r6;
    int sp_val = r2;
    r6 = func_ov094_0229aee8(r5 + 0x138, r7, r2);
    if (r6 != 0x23) {
        if (r4 != 0) {
            if (func_ov094_0229a69c(r5 + 0x138, r6) != 0) {
                return 0x1f;
            }
        }
        return func_ov110_0229d580(r5, r6);
    }
    r6 = func_ov094_0229aeb8(r5 + 0x138, r7, sp_val);
    if (r6 != 0x23) {
        if (r4 != 0) {
            if (func_ov094_0229a69c(r5 + 0x138, r6) != 0) {
                return 0x1f;
            }
        }
        return func_ov110_0229d428(r5, r6);
    }
    return 0x1f;
}
