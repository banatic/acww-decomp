/* func_ov003_022298f0 @ 0x022298f0, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} UnkStruct_022298f0;

extern void *func_02096190(void *obj);
extern void func_ov003_0222933c(char *self, void *o, Vec3 *v);
extern int func_0205fb28(Vec3 *w, int a, void *b, void *c, int d);
extern void func_ov003_0222a88c(char *self, void *obj);
extern void func_0209549c(UnkStruct_022298f0 *m, void *obj);
extern void func_ov003_02219668(UnkStruct_022298f0 *m, Vec3 *axis);
extern void func_0203f7d0(Vec3 *a, Vec3 *b);

int func_ov003_022298f0(char *self, void *obj)
{
    Vec3 v;
    UnkStruct_022298f0 m1;
    Vec3 u;
    Vec3 w;
    UnkStruct_022298f0 mtx;
    int r;
    void *o = func_02096190(obj);
    if (o == 0) {
        *(int *) (self + 0x40) = 4;
        return 0;
    }
    if (*(u8 *) (self + 0x80) == 0) {
        func_ov003_0222933c(self, o, &v);
        r = 1;
        w.x = v.x;
        w.y = v.y;
        w.z = v.z;
        if (func_0205fb28(&w, *(int *) (self + 0x4c), self + 0x54, self + 0x50, r)) {
            *(u8 *) (self + 0x80) = r;
            *(int *) (self + 0x6c) = v.x;
            *(int *) (self + 0x70) = v.y;
            *(int *) (self + 0x74) = v.z;
        }
    } else {
        func_ov003_0222a88c(self, obj);
        func_0209549c(&mtx, obj);
        m1 = mtx;
        func_ov003_02219668(&m1, 0);
        u.x = m1.w[9];
        u.y = m1.w[10];
        u.z = m1.w[11];
        func_0203f7d0(&u, &u);
        *(int *) (self + 0x54) = u.x;
        *(int *) (self + 0x58) = u.y;
        *(int *) (self + 0x5c) = u.z;
        *(int *) (self + 0x6c) = u.x;
        *(int *) (self + 0x70) = u.y;
        *(int *) (self + 0x74) = u.z;
        r = 1;
    }
    return r;
}
