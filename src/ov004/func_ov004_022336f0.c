/* func_ov004_022336f0 @ 0x022336f0, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern int func_0203f8d0(Vec3 *, void *);
extern void func_020e96c8(void *, int, int, int);
extern void func_020e9774(void *, int);
extern void func_020e9838(void *, int, int, int);
extern void func_ov004_02233dc0(void *, u16, Vec3 *, Vec3 *, short, short, short);
extern char data_021fbe48;
extern void *data_ov004_02258ae4;

void func_ov004_022336f0(char *self)
{
    volatile u16 t = 0xfff1;
    Vec3 v;
    Vec3 a, b;
    int r;
    int i;
    int z;
    char *p = self;
    i = 0;
    z = i;
    do {
        t = *(u16 *) (p + 8);
        if (*(int *) (p + 4) != 0) {
            if (t != 0xfff1) {
                char *q = p + 0x3c;
                u16 id;
                u16 m;
                int k;
                r = func_0203f8d0(&v, p + 0x24);
                func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
                func_020e9774(&data_021fbe48, r);
                func_020e9838(&data_021fbe48, *(int *) (p + 0x3c), *(int *) (q + 4), *(int *) (q + 8));
                id = t;
                m = t;
                k = (m & 0xf000) >> 12;
                switch (k) {
                    case 1:
                    case 3:
                    case 4: {
                        char *s = p + 0x24;
                        a.x = *(int *) (p + 0x24);
                        a.y = *(int *) (s + 4);
                        a.z = *(int *) (s + 8);
                        b.x = 0x1000;
                        b.y = 0x1000;
                        b.z = 0x1000;
                        func_ov004_02233dc0(data_ov004_02258ae4, id, &a, &b, z, z, z);
                        break;
                    }
                }
            }
        }
        p += 0x94;
        i++;
    } while (i < 0xf);
}
