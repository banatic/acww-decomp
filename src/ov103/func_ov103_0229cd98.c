/* func_ov103_0229cd98 @ 0x0229cd98, 0x40 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bba4(char *p);
extern int func_ov094_0229b30c(char *p, int v);
extern int func_ov103_0229cdd8(char *p, int v);

int func_ov103_0229cd98(char *base, int a1, int a2, int flag)
{
    int res1;

    res1 = func_ov094_0229bba4(base + 0xb2c);
    if (res1 != 0x37) {
        if (flag != 0) {
            if (func_ov094_0229b30c(base + 0xb2c, res1) != 0) {
                return 0x15;
            }
        }
        return func_ov103_0229cdd8(base, res1);
    } else {
        return 0x15;
    }
}
