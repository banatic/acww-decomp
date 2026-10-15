/* func_02043db4 @ 0x02043db4, 0xd2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Point;

extern void *func_0204e414(void);
extern int func_0204f5e0(void *node, int x4, int y4, int x_rem, int y_rem, int arg5);
extern int func_02044390(void *self, int t, Point *pt, int q);
extern int func_02044168(void *self, int t, Point *pt, int q);
extern int func_02043ed8(void *self, void *node, int t, Point *pt, u16 extra, int q);
extern int func_02043e88(void *self, int t, Point *pt, int q);

int func_02043db4(void *self, Point *pos, int op, int q, u16 extra)
{
    void *node;
    int result;
    int t;

    node = func_0204e414();
    result = -1;
    if (node != 0) {
        int x = pos->x;
        int y = pos->y;
        int x4 = x >> 4;
        int y4 = y >> 4;
        int y_rem = y - (y4 << 4);
        int x_rem = x - (x4 << 4);
        t = func_0204f5e0(node, x4, y4, x_rem, y_rem, 0);
        if (t != 0) {
            switch (op) {
                case 0: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02044390(self, t, &pt, q);
                    break;
                }
                case 1: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02044168(self, t, &pt, q);
                    break;
                }
                case 2: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02043ed8(self, node, t, &pt, extra, q);
                    break;
                }
                case 3:
                    break;
                case 4: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02043e88(self, t, &pt, q);
                    break;
                }
            }
        }
    }
    return result;
}
