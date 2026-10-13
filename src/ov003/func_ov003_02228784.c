/* func_ov003_02228784 @ 0x02228784, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern u8 data_ov003_0223c01c[];
extern void func_ov003_0222be08(char *obj);
extern void func_02031288(char *a, Vec3 *b, Vec3 *c, short h, int d, int e, int f);
extern void func_ov003_022286ac(char *self, Vec3 *v, char *p, short h);
extern void func_ov003_022286f4(char *self, char *obj);
extern void func_02055124(char *p);
extern void func_ov003_022283e4(char *self, char *obj, void *k);

void func_ov003_02228784(char *self, char *obj, void *k)
{
    Vec3 *d;
    Vec3 *s;
    Vec3 t;
    func_ov003_0222be08(obj);
    d = (Vec3 *) (obj + 0x218);
    s = (Vec3 *) (obj + 0x120);
    func_02031288(obj + 0x4c, s, d, *(short *) (obj + 0x138), (data_ov003_0223c01c[*(u8 *) (obj + 0x1ff) * 0x14] << 12) / 10,
                  0, 0xb);
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
    t.x = s->x;
    t.y = s->y;
    t.z = s->z;
    t.y = 0xffffeccd;
    func_ov003_022286ac(self, &t, obj + 0x144, *(short *) (obj + 0x138));
    if (*(u8 *) (obj + 0x7f)) {
        func_ov003_022286f4(self, obj);
    } else {
        func_02055124(obj + 0x144);
    }
    func_ov003_022283e4(self, obj, k);
}
