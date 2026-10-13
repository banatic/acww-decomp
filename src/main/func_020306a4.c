/* func_020306a4 @ 0x020306a4, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int pad_04;
    int y;
    int threshold;
} Point;

extern int FX_MulFunc(int, int);

int func_020306a4(Point *a, Point *b)
{
    int dx = b->x - a->x;
    int dy = b->y - a->y;
    int dy2, dx2, limit2;

    if ((dx < 0 ? -dx : dx) > a->threshold) {
        return 0;
    }
    if ((dy < 0 ? -dy : dy) > a->threshold) {
        return 0;
    }
    dy2 = FX_MulFunc(dy, dy);
    dx2 = FX_MulFunc(dx, dx);
    limit2 = FX_MulFunc(a->threshold, a->threshold);
    if (dx2 + dy2 > limit2) {
        return 0;
    }
    return 1;
}
