/* func_020b3c58 @ 0x020b3c58, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b3ed4(void *);
extern int func_020b3db8(void *, int *, int *, int *, unsigned int);

void func_020b3c58(void *obj, int *ocx, int *ocy, int *ow, int *oh)
{
    int minx, maxx, miny, maxy;
    unsigned int n;
    unsigned int i;
    int a, b, c;
    int t, y1, y0, x1, x0;

    maxx = 0;
    minx = 0;
    maxy = 0;
    miny = 0;
    n = func_020b3ed4(obj);
    if (n != 0) {
        maxx = -1;
        minx = 1;
        maxy = -1;
        miny = 1;
        for (i = 0; i < n; i++) {
            if (func_020b3db8(obj, &a, &b, &c, i) != 0) {
                if (b < minx) {
                    minx = b;
                }
                if (c < miny) {
                    miny = c;
                }
                if (b > maxx) {
                    maxx = b;
                }
                if (c > maxy) {
                    maxy = c;
                }
            }
        }
    }
    x1 = (maxx << 13) + 0x1000;
    x0 = (minx << 13) - 0x1000;
    y1 = (maxy << 13) + 0x1000;
    y0 = (miny << 13) - 0x1000;
    *ocx = (x1 + x0) >> 1;
    *ocy = (y1 + y0) >> 1;
    t = x1 - x0;
    if (t < 0) {
        t = -t;
    }
    *ow = t;
    t = y1 - y0;
    if (t < 0) {
        t = -t;
    }
    *oh = t;
}
