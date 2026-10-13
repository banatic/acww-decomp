/* func_ov003_02219b90 @ 0x02219b90, 0x4e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern void func_0204f818(int *, int *, int);
extern int func_ov003_02210c24(int, int, int *, unsigned short, int, int);

int func_ov003_02219b90(int p1, unsigned short *p2)
{
    int r6 = func_02096718(4);
    if (r6) {
        int a = 0, b = 0;
        int c[2];
        unsigned short tmp;
        func_0204f818(&a, &b, p1);
        tmp = *p2;
        c[0] = a;
        c[1] = b;
        return func_ov003_02210c24(r6, 1, c, tmp, 6, -1);
    } else {
        return 0;
    }
}
