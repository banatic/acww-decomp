/* func_02048f54 @ 0x02048f54, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204ed80(void);

int func_02048f54(void)
{
    int r4;
    int r0;

    r4 = 0;
    r0 = func_0204ed80();
    if (r0 == 1) {
        r4 = 1;
    }
    r0 = r4;
    return r0;
}
