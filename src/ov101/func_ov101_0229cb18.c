/* func_ov101_0229cb18 @ 0x0229cb18, 0x2a bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void);
extern int func_ov101_0229ce1c(int, int);
extern void func_ov094_0229aafc(int, int);

void func_ov101_0229cb18(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;

    if (func_ov101_0229ce38() != 0) {
        int r0_2 = r5;
        int r1_2 = r4;
        int r0_3 = func_ov101_0229ce1c(r0_2, r1_2);
        int r1_3 = r0_3;
        r5 += 0xf4;
        func_ov094_0229aafc(r5, r1_3);
    }
}
