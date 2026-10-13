/* func_020beba4 @ 0x020beba4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020952ec(void);

void func_020beba4(int *r5, int r4)
{
    int r0;

    r0 = func_020952ec();
    if (r4 == r0) {
        r5[0] = 1;
        r5[1] = r4;
        r5[2] = 0x2b;
    }
}
