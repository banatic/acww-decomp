/* func_02049ca0 @ 0x02049ca0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Point;

extern unsigned short *func_0204f5e0(int p0, int qx, int qy, int rx, int ry, int k);
extern int func_02048ec8(int p0, int x, int y);
extern void func_0204a25c(int, int, int, unsigned short, int);

int func_02049ca0(int p0, Point *p, int u2, int u3, unsigned short id)
{
    unsigned short *c;
    int flag = 0;
    int px = p->x;
    int py = p->y;
    int qx = px >> 4;
    int qy = py >> 4;
    int ry = py - (qy << 4);
    c = func_0204f5e0(p0, qx, qy, px - (qx << 4), ry, flag);
    if (c == 0) {
        goto end;
    }
    if (*c != 0xfff1) {
        goto end;
    }
    if (func_02048ec8(p0, p->x, p->y) == 0) {
        goto end;
    }
    func_0204a25c(p0, p->x, p->y, id, flag);
    flag = 1;
end:
    return flag;
}
