/* func_ov003_0223141c @ 0x0223141c, 0xde bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void *func_0204e414(int a);
extern void func_0204f818(int *x, int *y, int a);
extern unsigned short *func_0204f5e0(void *hnd, int i, int j, int u, int v, int w);

int func_ov003_0223141c(int a)
{
    void *hnd;
    unsigned short *e;
    int x, y, i, j, px, py;
    unsigned int h, g, f, ee, d, c, b, aa;
    unsigned short lo;

    hnd = func_0204e414(a);
    if (hnd != 0) {
        func_0204f818(&x, &y, a);
        px = x;
        py = y;
        i = px >> 4;
        j = py >> 4;
        e = func_0204f5e0(hnd, i, j, px - (i << 4), py - (j << 4), 0);
        if (e != 0) {
            h = 1;
            g = 1;
            f = 1;
            ee = 1;
            d = 1;
            c = 1;
            b = 1;
            aa = 0;
            lo = *e;
            if (lo <= 5) {
                aa = 1;
            }
            if (aa == 0) {
                if (!(lo >= 6 && lo <= 0xb)) {
                    b = 0;
                }
            }
            if (b == 0) {
                if (!(lo >= 0xc && lo <= 0x11)) {
                    c = 0;
                }
            }
            if (c == 0) {
                if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
                    d = 0;
                }
            }
            if (d == 0) {
                if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
                      (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
                    ee = 0;
                }
            }
            if (ee == 0) {
                if (lo != 0x1a) {
                    f = 0;
                }
            }
            if (f == 0) {
                if (lo != 0xa4) {
                    g = 0;
                }
            }
            if (g == 0) {
                if (lo != 0x1d) {
                    h = 0;
                }
            }
            if (h != 0) {
                return 1;
            }
        }
    }
    return 0;
}
