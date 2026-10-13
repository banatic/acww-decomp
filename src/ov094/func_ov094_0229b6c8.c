/* func_ov094_0229b6c8 @ 0x0229b6c8, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b3f0(void *a, void *b, int c, int d, int e);

void func_ov094_0229b6c8(void *a, int b, int c)
{
    int i;
    void *p = a;
    int *q = (int *) p;
    int r = q[1];
    int s = 0x23;
    int t = 0;

    for (i = 0; i < 10; i++) {
        func_ov094_0229b3f0(p, (void *) r, s, b, c);
        r += 0x100;
        s++;
    }
}
