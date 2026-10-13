/* func_0204eea4 @ 0x0204eea4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0204f5e0(void *p0, int qx, int qy, int rx, int ry, int k);
extern int func_0204ef74(void *p0, unsigned short *a, unsigned short *c, unsigned short *b, int x, int y);

int func_0204eea4(void *p0, int x, int y, unsigned short *src)
{
    unsigned short *c;
    unsigned short v[2];
    int ret;
    int ok;
    int qx, qy;

    qx = x >> 4;
    qy = y >> 4;
    c = func_0204f5e0(p0, qx, qy, x - (qx << 4), y - (qy << 4), 0);
    ret = 0;
    if (c == 0) {
        goto end;
    }
    ok = ret;
    if (*c >= 0x5000 && *c <= 0x5021) {
        ok = 1;
    }
    if (ok == 0) {
        goto end;
    }
    v[0] = 0xfff1;
    if (src != 0) {
        v[0] = *src;
    }
    v[1] = 0xfff1;
    ret = func_0204ef74(p0, &v[0], c, &v[1], x, y);
end:
    return ret;
}
