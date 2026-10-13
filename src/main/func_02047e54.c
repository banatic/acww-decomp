/* func_02047e54 @ 0x02047e54, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204f2b8(int, int, int, int, int);
extern void func_0204a200(int, int, int, int, int, int, int, int);

void func_02047e54(int p0, int p1, int p2, int p3)
{
    volatile int start = 1;
    volatile int something = 1;
    int r5, r6, r4, r7;
    unsigned short *p;

    for (r5 = 1; r5 < p3 + 1; r5++) {
        for (r6 = start; r6 < p2 + 1; r6++) {
            for (r4 = 0; r4 < 16; r4++) {
                for (r7 = 0; r7 < 16; r7++) {
                    if ((p = func_0204f5e0(p1, r6, r5, r7, r4, 0)) != 0) {
                        if (*p == 0x1369) {
                            if (func_0204f2b8(p1, r6, r5, r7, r4) != 0) {
                                func_0204a200(p0, p1, r6, r5, r7, r4, 0x136a, something);
                            }
                        }
                    }
                }
            }
        }
    }
}
