/* func_020489c4 @ 0x020489c4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Point;

extern int func_020644cc(int);
extern int func_02048a54(void *, Point *, Point *, int);
extern void func_02048cb8(void *, void *, int, int, unsigned short, void *, int);
extern void func_02048ee4(void);

void func_020489c4(void *obj, void *p1)
{
    Point pt;
    Point arr[3];
    int n, i, v;

    pt.x = 0;
    pt.y = 0;
    arr[0].x = 0;
    arr[0].y = 0;
    arr[1].x = 0;
    arr[1].y = 0;
    arr[2].x = 0;
    arr[2].y = 0;
    n = 0;
    for (i = 0; i < 3; i++) {
        do {
            v = func_020644cc(0x10);
            pt.x = v % 4;
            pt.y = v / 4;
        } while (func_02048a54(obj, &pt, arr, n) != 0);
        func_02048cb8(obj, p1, pt.x + 1, pt.y + 1, (unsigned short) (func_020644cc(4) + 0x21), (void *) func_02048ee4, 0);
        arr[n].x = pt.x;
        arr[n].y = pt.y;
        n++;
    }
}
