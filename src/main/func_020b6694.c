/* func_020b6694 @ 0x020b6694, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b66c4(void);

int func_020b6694(void)
{
    int r2;
    int r1;
    int r0;

    r0 = func_020b66c4();
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
