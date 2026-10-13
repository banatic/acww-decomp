/* func_0204d8e4 @ 0x0204d8e4, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204d924(void);

int func_0204d8e4(int a, int b, int c)
{
    int r4 = 0;
    int r1;
    int r2;
    int r0;

    if (func_0204d924() != 0) {
        r1 = a + (b << 3);
        r2 = *(int *) r1;
        if (r2 != 0) {
            r0 = *(int *) (r1 + 4);
            if (c < r0) {
                r1 = 0;
                while (r1 < c) {
                    r4 += *(unsigned short *) r2;
                    r2 += 2;
                    r1++;
                }
            }
        }
    }
    return r4;
}
