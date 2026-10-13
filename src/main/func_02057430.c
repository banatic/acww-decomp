/* func_02057430 @ 0x02057430, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020574a0(void);

int func_02057430(int a0, int a1, int a2)
{
    int r5 = a0;
    int r6 = a1;
    int r4 = a2;
    int r0;

    if (func_020574a0() == 0) {
        r0 = -1;
        if (r4 != r0) {
            r0 = *(unsigned char *) (r6 + *(int *) (r6 + 8) + 5);
            if (r4 < r0) {
                *(unsigned char *) (r5 + 4) = r4;
                *(int *) r5 = r6;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
