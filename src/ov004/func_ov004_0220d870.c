/* func_ov004_0220d870 @ 0x0220d870, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern int func_ov004_0220d94c(void *self);
extern Vec3 *func_ov004_0220d934(void *self);
extern u16 *func_ov004_0220d930(void *self);
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern void func_ov004_02233b10(int id, Vec3 *a, Vec3 *b, int c, int d, int e);

void func_ov004_0220d870(void *self, char *b)
{
    Vec3 v;
    Vec3 out;
    Vec3 w;
    Vec3 s;
    int px, py, pz;

    if (func_ov004_0220d94c(self) != 0) {
        data_021fbe48 = *(Mtx43 *) (b + 0x59c);
        pz = func_ov004_0220d934(self)->z;
        py = func_ov004_0220d934(self)->y;
        px = func_ov004_0220d934(self)->x;
        func_020e9868(&data_021fbe48, px, py, pz);
        v.x = 0;
        v.y = 0;
        v.z = 0;
        MTX_MultVec43(&v, &data_021fbe48, &out);
        w.x = out.x;
        w.y = out.y;
        w.z = out.z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov004_02233b10(*func_ov004_0220d930(self), &w, &s, 0, 0, 0);
    }
}
