/* func_020b66ec @ 0x020b66ec, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b671c(void);

int func_020b66ec(void)
{
    int r0;
    int r2;

    r0 = func_020b671c();
    r2 = 0;
    if (r0 != ~r2) {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
