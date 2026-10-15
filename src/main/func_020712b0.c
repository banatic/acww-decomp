/* func_020712b0 @ 0x020712b0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020712ec(int, int);
extern int func_020984d4(void);
extern int func_020988d8(unsigned int);

int func_020712b0(int r4, int r5)
{
    int r0;

    r4 = func_020712ec(r4, r5);
    if (r4 == 0) {
        return 3;
    }
    if (r4 == 5) {
        return 2;
    }
    r5 = func_020984d4();
    r0 = func_020988d8(r5);
    if (r0 == 1 && r4 == r5 + 1) {
        return 0;
    }
    return 1;
}
