/* func_ov101_0229cd40 @ 0x0229cd40, 0x3e bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(int arg0, unsigned int arg1);
extern int func_ov101_0229ce1c(int, int);
extern void func_ov094_0229aa14(int, int, int, int);
extern void func_ov094_0229a9b4(int, int);

void func_ov101_0229cd40(int r0, int r1, int r2, int r3)
{
    int r4 = r0;
    int r5 = r1;
    int r6 = r2;
    int r7 = r3;

    if (func_ov101_0229ce38(r0, r1) != 0) {
        r5 = func_ov101_0229ce1c(r4, r5);
        func_ov094_0229aa14(r4 + 0xf4, r5, r6, r7);
        func_ov094_0229a9b4(r4 + 0xf4, r5);
    }
}
