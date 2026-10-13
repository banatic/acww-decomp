/* func_02002bd0 @ 0x02002bd0, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned char *p, int r);
extern void GX_LoadOBJPltt(unsigned char *p, int q, int r);
extern void GXS_LoadOBJPltt(unsigned char *p, int q, int r);
extern void GX_LoadBGPltt(unsigned char *p, int q, int r);
extern void GXS_LoadBGPltt(unsigned char *p, int q, int r);

int func_02002bd0(unsigned char *base, unsigned int mode, int a, int b, unsigned char c)
{
    unsigned char *p;
    int q, r;

    p = base + ((b - a) << 5);
    r = ((c - b + 1) << 5);
    q = b << 5;

    DC_FlushRange(p, r);

    if (mode == 7) {
        GX_LoadOBJPltt(p, q, r);
    } else if (mode == 8) {
        GXS_LoadOBJPltt(p, q, r);
    } else if (mode <= 2) {
        if (q == 0) {
            q = 2;
            r -= 2;
            p += 2;
        }
        GX_LoadBGPltt(p, q, r);
    } else if (mode <= 6) {
        if (q == 0) {
            q = 2;
            r -= 2;
            p += 2;
        }
        GXS_LoadBGPltt(p, q, r);
    }

    return 1;
}
