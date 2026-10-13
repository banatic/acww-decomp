/* func_0207c818 @ 0x0207c818, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int len);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern unsigned int func_020036e8(int x);
extern int func_0207cc54(int a, int b, int c);

int func_0207c818(char *p, int mask)
{
    unsigned char hist[6];
    int t;
    int cnt;
    int i;
    unsigned char best;
    int maxv;
    int v;
    unsigned int k;
    int r;
    int j;

    best = 0;
    cnt = 0;
    maxv = 9;
    MI_CpuFill8(hist, 0, 6);
    for (i = 0; i < 8; i++) {
        t = func_0208150c(p);
        if (func_02003704(t)) {
            if (func_020036e8(t) < 6) {
                k = func_020036e8(t);
                hist[k] = hist[k] + 1;
            }
        }
        p += 0x7ec;
    }
    for (j = 0; j < 6; j++) {
        if (((mask >> j) & 1) == 0) {
            v = hist[j];
            if (v < maxv) {
                best = 1 << j;
                cnt = 1;
                maxv = v;
            } else if (v == maxv) {
                best |= 1 << j;
                cnt++;
            }
        }
    }
    r = func_0207cc54(best, cnt, 6);
    if ((unsigned int) r < 6) {
        return (unsigned char) r;
    }
    return 0;
}
