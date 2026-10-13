/* func_02032d8c @ 0x02032d8c, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_02032d8c;

struct UnkStruct_02032d8c_2 {
    virtual int v0();
    virtual int v1();
    virtual int v2(int *a, int *b, int *c, int x, int y);
};

extern "C" {
extern u8 data_021c5124;
extern void *func_02034600(u8 *g, int x, int y);
extern void func_02032e80(void *p0, UnkStruct_02032d8c *v, int a, int b, int m, int n);
}

extern "C" void func_02032d8c(void *p0, UnkStruct_02032d8c_2 *o, int x0, int x1, int y0, int y1, int flag)
{
    UnkStruct_02032d8c v1, v2, v3;
    int a, b, c;
    int y, x;
    int zz;
    void *r;

    for (y = y0; y <= y1; y++) {
        x = x0;
        zz = (y << 13) + 0x1000;
        for (; x <= x1; x++) {
            if (o->v2(&a, &b, &c, x, y) != 0) {
                if (c == 2) {
                    if (flag == 0) {
                        continue;
                    }
                    v1.x = (x << 13) + 0x1000;
                    v1.y = 0;
                    v1.z = zz;
                    v1.y = 0;
                    func_02032e80(p0, &v1, a, b, 2, c);
                } else {
                    v2.x = (x << 13) + 0x1000;
                    v2.y = 0;
                    v2.z = zz;
                    v2.y = 0;
                    func_02032e80(p0, &v2, a, b, 1, c);
                }
            } else {
                if (flag == 0) {
                    continue;
                }
                if (data_021c5124 == 0) {
                    continue;
                }
                r = func_02034600(&data_021c5124, x, y);
                if (r == 0) {
                    continue;
                }
                v3.x = (x << 13) + 0x1000;
                v3.y = 0;
                v3.z = zz;
                v3.y = 0;
                func_02032e80(p0, &v3, (int) r, 0x1000, 2, 2);
            }
        }
    }
}
