/* func_ov096_0229f75c @ 0x0229f75c, 0x40 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229aee8(char *p, int unused1, int unused2);
extern int func_ov094_0229a69c(char *p, int v);
extern int func_ov096_0229f79c(char *p, int v);

int func_ov096_0229f75c(char *a, int b, int c, int cond)
{
    int v;

    v = func_ov094_0229aee8(a + 0x358, b, c);
    if (v != 0x23) {
        if (cond) {
            if (func_ov094_0229a69c(a + 0x358, v) != 0) {
                return 0x26;
            }
        }
        return func_ov096_0229f79c(a, v);
    } else {
        return 0x26;
    }
}
