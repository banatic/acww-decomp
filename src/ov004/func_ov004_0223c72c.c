/* func_ov004_0223c72c @ 0x0223c72c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223d348(void);
extern int func_020b67d4(void);
extern int func_020b6680(void);
int func_ov004_0223c72c(void)
{
    if (func_ov004_0223d348() != 0) {
        return 0;
    }
    if (func_020b67d4() != 0 || func_020b6680() != 0) {
        return 1;
    }
    return 0;
}
