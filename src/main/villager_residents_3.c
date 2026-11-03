/* villager_residents_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207c818 @ 0x0207c818, 0xb0 bytes, Thumb
 * func_0207c76c @ 0x0207c76c, 0xac bytes, Thumb
 */

extern void MI_CpuFill8(void *dst, int val, int len);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern unsigned int func_020036e8(int x);
extern int func_0207cc54(int a, int b, int c);
extern void func_0207cf80(void *self);
extern int func_0207c8c8(void *self, int idx, int flag);
extern void func_02081518(void *dst, unsigned char data, int a, int b, int c);
extern void func_0207ca74(void *dst, unsigned char data);
extern void func_0209e474(void *dst);
extern void func_0207a188(void *dst, void *src);
extern void func_0209df64(void *dst);

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

void func_0207c76c(void *self)
{
    int local1, local2, i;
    unsigned char mask;

    mask = 0;
    func_0207cf80(self);

    i = 0;
    local1 = 0;
    local2 = 0;

    do {
        unsigned int idx;
        int v;

        idx = func_0207c818((char *) self, (unsigned char) mask);
        if (idx >= 6) {
            continue;
        }

        v = func_0207c8c8(self, idx, 1);
        if (v == ~local2) {
            continue;
        }

        func_02081518((char *) self + 0x7ec * i, (unsigned char) v, local1, local1, 1);
        func_0207ca74((char *) self + 0x4060, (unsigned char) v);

        mask = (unsigned char) (mask | (1 << idx));
    } while (++i < 3);

    func_0209e474((char *) self + 0x4050);
    func_0207a188((char *) self + 0x3f7c, self);
    func_0209df64((char *) self + 0x407a);

    *(((signed char *) self) + 0x4076) = -1;
}
