/* func_ov004_0223c700 @ 0x0223c700, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c72c(void);
extern int func_020b65c4(void);
int func_ov004_0223c700(void)
{
    int v;
    if (func_ov004_0223c72c() != 0) {
        return 1;
    }
    v = func_020b65c4();
    switch (v) {
        case 0x1f:
        case 0x21:
        case 0x22:
            return 1;
    }
    return 0;
}
