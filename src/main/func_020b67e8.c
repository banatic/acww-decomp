/* func_020b67e8 @ 0x020b67e8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6818(void);

int func_020b67e8(void)
{
    int result;
    int r0;
    int r2;

    r0 = func_020b6818();
    r2 = 0;
    if (r0 != ~r2) {
        r2 = 1;
    }
    result = r2;
    return result;
}
