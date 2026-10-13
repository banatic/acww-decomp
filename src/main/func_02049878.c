/* func_02049878 @ 0x02049878, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Point;

extern int func_02049944(Point *a, Point *b, Point *c, void (*cb)(void));
extern void func_02049fbc(void);

int func_02049878(int unused, Point *p1, Point *p2, Point *p3)
{
    Point local1, local2;
    int ret = 1;
    local2.x = p3->x;
    local2.y = p3->y;
    local1.x = p2->x;
    local1.y = p2->y;
    if (func_02049944(p1, &local1, &local2, func_02049fbc) != 0) {
        ret = 0;
    }
    return ret;
}
