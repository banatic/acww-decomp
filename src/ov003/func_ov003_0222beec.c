/* func_ov003_0222beec @ 0x0222beec, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int data_ov003_0223bda8;
extern int data_ov003_0223bda4;
extern void func_ov003_0222462c(int id, Vec3 *v, Vec3 *s, int a, int b, int c);
extern int func_ov003_0222c16c(char *o);
extern void func_ov003_0222803c(Vec3 *v, int a);
extern int func_0200322c(void *a, void *b);
extern void func_02031288(char *o, Vec3 *a, Vec3 *b, int d, int t, int e, int f);

void func_ov003_0222beec(void *unused, char *o)
{
    Vec3 v1;
    Vec3 s;
    Vec3 v2;
    Vec3 *p = (Vec3 *) (o + 0x34);
    int *n = (int *) (o + 0x58);
    int t;
    if (*n < 0x64) {
        v1.x = p->x;
        v1.y = p->y;
        v1.z = p->z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_0222462c(0x1520, &v1, &s, 0, 0, 0);
        if (func_ov003_0222c16c(o)) {
            *n = 0x64;
        }
    } else if (*n & 1) {
        v2.x = p->x;
        v2.y = p->y;
        v2.z = p->z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_0222462c(0x1520, &v2, &s, 0, 0, 0);
    }
    func_ov003_0222803c(p, data_ov003_0223bda8);
    p->y = p->y - data_ov003_0223bda4;
    t = (*n * 0x199a) >> 5;
    if (t > 0x199a) {
        t = 0x199a;
    }
    func_02031288(o, p, p, func_0200322c(o + 0x4c, o + 0x40), t, 0, 0xb);
    *n = *n + 1;
    if (*n >= 0x78) {
        *(u8 *) (o + 0x30) = 0;
        {
            Vec3 *q = (Vec3 *) (o + 0x4c);
            q->x = 0x1000;
            q->y = 0x1000;
            q->z = 0x1000;
        }
    }
}
