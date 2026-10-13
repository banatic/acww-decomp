/* func_02048ee4 @ 0x02048ee4, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O3,s
 */

extern int func_02048f54(void *p0, int x, int y);
extern unsigned short *func_0204f5e0(void *p0, int qx, int qy, int rx, int ry, int k);
extern int func_0204a034(unsigned short *c);

int func_02048ee4(void *p0, int x, int y)
{
    unsigned short *c;
    int ok = 0;
    int qx, qy, yy;

    if (func_02048f54(p0, x, y) == 0) {
        goto end;
    }
    yy = y + 1;
    qx = x >> 4;
    qy = yy >> 4;
    c = func_0204f5e0(p0, qx, qy, x - (qx << 4), yy - (qy << 4), ok);
    if (c == 0) {
        goto end;
    }
    if (func_0204a034(c) != 0) {
        goto end;
    }
    yy = y + 2;
    qx = x >> 4;
    qy = yy >> 4;
    c = func_0204f5e0(p0, qx, qy, x - (qx << 4), yy - (qy << 4), ok);
    if (c == 0) {
        goto end;
    }
    if (func_0204a034(c) != 0) {
        goto end;
    }
    ok = 1;
end:
    return ok;
}
