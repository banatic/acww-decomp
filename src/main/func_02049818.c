/* func_02049818 @ 0x02049818, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x;
    int y;
} Point;

extern int func_0204ed80(int, int, int);
extern void func_0204a198(int a, unsigned short b, int c, int d);
extern int func_02049878(int a, int b, Point *c, Point *d);

void func_02049818(int a, int b, unsigned short *c, Point *d, int e, int f)
{
    int e2, f2;
    f2 = f;
    e2 = e;
    if (func_0204ed80(b, e2, f2) != 1) {
        func_0204a198(b, *c, e, f);
        return;
    }
    {
        Point local2;
        Point local;
        int ret;
        local.x = e2;
        local.y = f2;
        local2.x = d->x;
        local2.y = d->y;
        ret = func_02049878(a, b, &local2, &local);
        if (ret == 0) {
            func_0204a198(b, *c, e, f);
        }
    }
}
