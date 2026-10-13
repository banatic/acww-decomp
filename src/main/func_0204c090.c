/* func_0204c090 @ 0x0204c090, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c0b0(void);

int func_0204c090(void)
{
    int r0;
    int r1;

    r0 = func_0204c0b0();
    r1 = -1;
    if (r0 != r1) {
        r0 = r0 & 7;
    } else {
        r0 = r1;
    }
    return r0;
}
