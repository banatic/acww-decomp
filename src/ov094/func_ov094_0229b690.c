/* func_ov094_0229b690 @ 0x0229b690, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b3f0(void *p, int a, int b, int c, int d);

void func_ov094_0229b690(void *p, int a, int b)
{
    int i;
    int *q = (int *) p;
    int v = q[1];
    int c = 0x2d;
    int d = 0;

    for (i = 0; i < 10; i++) {
        func_ov094_0229b3f0(p, v, c, a, b);
        v += 0x100;
        c++;
    }
}
