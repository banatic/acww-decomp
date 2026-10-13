/* func_02047a28 @ 0x02047a28, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204a25c(int a, int b, int c, int d, int e);

void func_02047a28(int p0, int p1, int p2, int p3)
{
    int z2 = 0;
    int z1 = 0;
    int inner = 0;
    int outer = 0;
    do {
        inner = 0;
        do {
            unsigned short *r = func_0204f5e0(p1, p2 + 1, p3 + 1, inner, outer, z1);
            if (r != 0 && *r == 0x6d) {
                int out1, out2;
                func_0204f800(&out1, &out2, p2 + 1, p3 + 1, inner, outer);
                func_0204a25c(p1, out1, out2, 0x61, z2);
            }
            inner++;
        } while (inner < 16);
        outer++;
    } while (outer < 16);
}
