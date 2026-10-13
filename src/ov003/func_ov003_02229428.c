/* func_ov003_02229428 @ 0x02229428, 0x8a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_020ea990(void *a, void *b);
int func_0200322c(void *a, void *b);
void func_ov003_0222be78(void *dst, int q, int w);

int func_ov003_02229428(char *dst, char *a, char *b, int s, int h, int n)
{
    int nn;
    int v;
    volatile int t;
    volatile int p;
    int q;
    int w;
    int z;
    if (n <= s) {
        return 0;
    }
    v = *(int *) (b + 4);
    nn = n * n;
    t = ((h - (v >> 1)) << 3) / nn;
    p = func_020ea990(a, b);
    w = func_0200322c(a, b);
    nn = t * nn;
    q = (v + (nn >> 1)) / n;
    z = s * s;
    *(int *) (dst + 4) = *(int *) (a + 4) + (s * q - ((z * t) >> 1));
    func_ov003_0222be78(dst, p / n, w);
    return 1;
}
