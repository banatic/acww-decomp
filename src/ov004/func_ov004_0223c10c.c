/* func_ov004_0223c10c @ 0x0223c10c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int x);
extern int func_020b6730(int a);
int func_ov004_0223c10c(int x)
{
    int r;
    int a = func_020b65c4(x);
    if (func_020b6730(a) != 0 || a == 0xa || a == 0xf) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
