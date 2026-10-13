/* func_020b120c @ 0x020b120c, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020ba494(void);
extern int func_020ba488(void);
extern void *func_020b1530(int i);
extern void func_020b15b8(void *p, int *x, int *y);
extern int func_020b12b0(int a, int b, int x, int y);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

int func_020b120c(void)
{
    int lim;
    int base;
    int i;
    int best;
    void *p;
    int dx;
    int dy;
    int d;
    int bestDist;
    Pair a;
    struct {
        int x;
        int y;
    } v;

    a.unk_00 = 0;
    a.w1 = 0;
    func_0209e474(&a);
    if (((unsigned char *) &a)[2] >= 6 && ((unsigned char *) &a)[2] < 0x12) {
        return -1;
    }
    lim = func_020ba494();
    base = func_020ba488();
    best = -1;
    for (i = 0; i < 0x10; i++) {
        p = func_020b1530(i);
        if (p == 0) {
            continue;
        }
        func_020b15b8((char *) p + 0x2a, &v.x, &v.y);
        if (v.x < lim) {
            v.x += 0x200;
        }
        if (func_020b12b0(lim, base, v.x, v.y) == 0) {
            continue;
        }
        dy = v.y - (base + 0x60);
        dx = v.x - (lim + 0x80);
        d = dx * dx + dy * dy;
        if (best == -1 || bestDist > d) {
            best = i;
            bestDist = d;
        }
    }
    return best;
}
