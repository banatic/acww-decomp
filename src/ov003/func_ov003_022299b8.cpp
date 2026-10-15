/* func_ov003_022299b8 @ 0x022299b8, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_022299b8;

extern "C" {
UnkStruct_022299b8 *func_02096190(void *obj);
void func_ov003_0222933c(char *self, UnkStruct_022299b8 *o, Vec3 *v);
int func_0205fb28(Vec3 *w, int a, void *b, void *c, int d);
int func_ov003_0222a88c(char *self, void *obj);

int func_ov003_022299b8(char *self, void *obj)
{
    int r = 0;
    Vec3 v;
    Vec3 w;
    if (*(u8 *) (self + 0x80) == 0) {
        UnkStruct_022299b8 *o = func_02096190(obj);
        if (o == 0) {
            *(int *) (self + 0x40) = 4;
            return r;
        }
        func_ov003_0222933c(self, o, &v);
        r = 1;
        w = v;
        if (func_0205fb28(&w, *(int *) (self + 0x4c), self + 0x54, self + 0x50, r)) {
            *(u8 *) (self + 0x80) = r;
            *(int *) (self + 0x6c) = v.x;
            *(int *) (self + 0x70) = v.y;
            *(int *) (self + 0x74) = v.z;
        }
    } else if (*(u8 *) (self + 0xa0) == 0) {
        func_ov003_0222a88c(self, obj);
        r = 1;
    }
    return r;
}
}
