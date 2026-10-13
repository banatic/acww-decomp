/* func_020b6744 @ 0x020b6744, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6774(void);

int func_020b6744(void)
{
    int r0;
    int r2;
    int r1;

    r0 = func_020b6774();
    r2 = 0;
    r1 = ~r2;
    if (r0 == r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
