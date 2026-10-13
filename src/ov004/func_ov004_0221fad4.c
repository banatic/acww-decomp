/* func_ov004_0221fad4 @ 0x0221fad4, 0xf0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov004_0221ef2c(char *self);
extern int func_ov004_0221ef70(char *self);
extern int *func_02095794(int n);
extern int func_0201c378(char *self, int n);
extern void func_0201b458(Vec3 *out, char *self, Vec3 *in);
extern int func_02019e00(char *p);
extern void func_02019d0c(char *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201b044(char *p, Vec3 *v);
extern int func_020eaa6c(Vec3 *a, char *b);
extern void func_ov004_0221fdf4(char *self, int n);
extern u16 data_020c80f8;

int func_ov004_0221fad4(char *self)
{
    // DECLS
    Vec3 v;
    Vec3 w;
    int h;
    int *p;
    // ENDDECLS

    if (func_ov004_0221ef2c(self) != 0) {
        return 1;
    }
    if (func_ov004_0221ef70(self) != 0) {
        return 1;
    }
    p = func_02095794(4);
    v.x = p[0];
    v.y = p[1];
    v.z = p[2];
    h = func_0201c378(self, 4);
    func_0201b458(&w, self, &v);
    if (h > 0x4000) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else if (func_02019e00(self + 0x564) == 2) {
        func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    func_0201b044(self + 0x350, &w);
    if (h <= 0x3000 || func_020eaa6c(&w, self + 0x5c) != 0) {
        func_ov004_0221fdf4(self, 4);
    }
    return 1;
}
