/* func_ov095_0229bb34 @ 0x0229bb34, 0x5e bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051c14(const unsigned short *a, int b, int c, int *d, int e);
extern int func_02051d30(int v);

unsigned char func_ov095_0229bb34(int unused, const unsigned short *arr, int p3, int p4, unsigned char threshold,
                                  unsigned char *dst)
{
    int count;
    int i;
    int sum;
    int lim;
    func_02051c14(arr, p3, p4, &count, 0);
    sum = 0;
    i = 0;
    lim = threshold;
    while (i < count) {
        int v = func_02051d30(arr[i]);
        if (sum + (v >> 1) > lim) {
            if (dst != 0) {
                *dst = (unsigned char) i;
            }
            return (unsigned char) sum;
        }
        sum += v;
        i++;
    }
    if (dst != 0) {
        *dst = (unsigned char) count;
    }
    return (unsigned char) sum;
}
