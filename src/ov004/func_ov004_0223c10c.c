/* func_ov004_0223c10c @ 0x0223c10c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b6730(void);
int func_ov004_0223c10c(void)
{
    int r;
    int a = func_020b65c4();
    if (func_020b6730() != 0 || a == 0xa || a == 0xf) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
