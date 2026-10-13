/* func_0204c100 @ 0x0204c100, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c0b0(void);

int func_0204c100(void)
{
    int r0;
    int r1;

    r0 = func_0204c0b0();
    r1 = -1;
    if (r0 != r1) {
        r1 = r0 >> 3;
        r1 = r1 & 3;
    }
    r0 = r1;
    return r0;
}
