/* func_0204e7dc @ 0x0204e7dc, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Point;

extern unsigned short *func_0204ea00(void *p0, Point *pt);

int func_0204e7dc(void *p0)
{
    Point pt;
    int count;
    int result;
    int startx;
    int startk;
    int flag0;
    unsigned short *p;
    int k;
    int flag;

    count = 0;
    pt.x = 0;
    pt.y = 0;
    result = 0;
    startx = 0;
    startk = 0;
    flag0 = 0;
    for (pt.y = 0; pt.y < 6; pt.y++) {
        for (pt.x = startx; pt.x < 6; pt.x++) {
            p = func_0204ea00(p0, &pt);
            if (p != 0) {
                for (k = startk; k < 0x100; k++) {
                    flag = flag0;
                    if (*p >= 0xe3 && *p <= 0xe7) {
                        flag = 1;
                    }
                    if (flag != 0) {
                        count++;
                    }
                    p++;
                }
            }
        }
    }
    if (count >= 5) {
        result = 1;
    }
    return result;
}
