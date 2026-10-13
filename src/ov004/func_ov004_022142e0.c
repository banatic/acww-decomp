/* func_ov004_022142e0 @ 0x022142e0, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;
typedef struct {
    u8 data[0x44];
} UnkStruct_022142e0;

extern Mtx43 data_021fbe48;
extern int func_ov004_0220cfd4(void *p);
extern void MTX_MultVec43(Vec3 *a, Mtx43 *m, Vec3 *out);
extern void func_02034270(UnkStruct_022142e0 *o, Vec3 *v, int a, int b);
extern int func_020341c8(UnkStruct_022142e0 *o, int a);
extern void func_02052738(void *self, int a, int b, int c);
extern void func_0203423c(UnkStruct_022142e0 *o);

void func_ov004_022142e0(char *self, int unused, char *arg2)
{
    Vec3 v;
    Vec3 out;
    UnkStruct_022142e0 obj;
    Vec3 *q;

    if (func_ov004_0220cfd4(self + 0x764) != 0 && *(u8 *) (self + 0x844) == 1) {
        q = (Vec3 *) ((char *) *(void **) (arg2 + 0xb4) + 0x4c);
        v.x = q->x;
        v.y = q->y;
        v.z = q->z;
        data_021fbe48 = *(Mtx43 *) (self + 0x59c);
        MTX_MultVec43(&v, &data_021fbe48, &out);
        func_02034270(&obj, &out, 0, 0);
        if (func_020341c8(&obj, 0) > 0) {
            func_02052738(self, 0, 0xff, 1);
        }
        func_0203423c(&obj);
    }
}
