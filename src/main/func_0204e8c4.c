/* func_0204e8c4 @ 0x0204e8c4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Point;
typedef struct {
    int a;
    int b;
    int c;
    int d;
} UnkStruct_0204e8c4;

extern UnkStruct_0204e8c4 *func_0204f86c(int size, int);
extern int func_0204ea00(unsigned char *p0, Point *pt);
extern int func_0204e9c0(unsigned char *p0, Point *pt);

UnkStruct_0204e8c4 *func_0204e8c4(unsigned char *p0, int argument1)
{
    Point pt;
    Point o;
    UnkStruct_0204e8c4 *arr;
    int n;
    UnkStruct_0204e8c4 *e;

    pt.x = 0;
    pt.y = 0;
    arr = func_0204f86c(0x24, (int) argument1);
    if (arr == 0) {
        goto ret;
    }
    n = 0;
    pt.y = 0;
    o.x = 0;
    o.y = 0;
    for (; pt.y < 6; pt.y++) {
        for (pt.x = o.x; pt.x < 6; pt.x++) {
            e = &arr[n];
            e->a = *(p0 + pt.y * 6 + pt.x);
            e->b = func_0204ea00(p0, &pt);
            e->c = o.y;
            e->d = func_0204e9c0(p0, &pt);
            n++;
        }
    }
ret:
    return arr;
}
