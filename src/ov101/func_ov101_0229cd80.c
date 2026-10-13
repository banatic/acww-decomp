/* func_ov101_0229cd80 @ 0x0229cd80, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void);
extern int func_ov101_0229cbec(int, int);
extern int func_ov101_0229cbbc(int, int);
extern void func_ov101_0229cd40(int, int, int, int);
extern void func_ov101_0229c944(int, int);

int func_ov101_0229cd80(int r5, int r4)
{
    int r6;
    int r3;
    int r0;
    int r1;
    int r2;

    r0 = func_ov101_0229ce38();
    if (r0 != 0) {
        r0 = r5;
        r1 = r4;
        r6 = func_ov101_0229cbec(r0, r1);
        if (r6 != 0x0000fff1) {
            r0 = r5;
            r1 = r4;
            r3 = func_ov101_0229cbbc(r0, r1);
            r0 = r5;
            r1 = r5;
            r1 += 0xb2;
            r1 = *(unsigned char *) r1;
            r2 = r6;
            func_ov101_0229cd40(r0, r1, r2, r3);
        }
        r0 = r5;
        r1 = r4;
        func_ov101_0229c944(r0, r1);
        r0 = 1;
    } else {
        r0 = 0;
    }
    return r0;
}
