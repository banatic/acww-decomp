/* func_ov003_0222040c @ 0x0222040c, 0x52 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b3b50(int);
extern unsigned int func_020b3ed4(void *);
extern int func_020b3db8(void *, int *, int *, int *, unsigned int);
extern int func_02030920(int, int, unsigned char);

int func_ov003_0222040c(int unused, int key, int baseX, int baseY)
{
    void *A;
    unsigned int n, i;

    A = func_020b3b50(key);
    if (A != 0) {
        int v1, v2, v3;
        n = func_020b3ed4(A);
        for (i = 0; i < n; i++) {
            if (func_020b3db8(A, &v3, &v1, &v2, i)) {
                func_02030920(baseX + v1, baseY + v2, (unsigned char) v3);
            }
        }
    }
    return 1;
}
