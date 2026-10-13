/* func_020712b0 @ 0x020712b0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020712ec(void);
extern int func_020984d4(void);
extern int func_020988d8(void);

int func_020712b0(void)
{
    int r4;
    int r5;
    int r0;

    r4 = func_020712ec();
    if (r4 == 0) {
        return 3;
    }
    if (r4 == 5) {
        return 2;
    }
    r5 = func_020984d4();
    r0 = func_020988d8();
    if (r0 == 1 && r4 == r5 + 1) {
        return 0;
    }
    return 1;
}
