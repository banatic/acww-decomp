/* func_ov068_0226e008 @ 0x0226e008, 0xf0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;
typedef struct Subst {
    u16 type;
    u16 type2;
    s32 dest[3];
    Vec3 *vec;
    s32 counter;
} Subst;
typedef struct UnkStruct_0226e008 {
    u8 pad_00[0x110];
    s32 pos[3];
    u8 pad_11C[0x100];
    Subst sub;
} UnkStruct_0226e008;
extern void func_0203caa4(UnkStruct_0226e008 *self, int a, int b);
extern void func_0203c99c(UnkStruct_0226e008 *self, int a);
extern void func_0203ad68(void);
extern int func_0204f490(Vec3 *a, s32 *b, s32 *c, s32 *d, s32 *e, u16 *f, u16 *g, int h, int i);
extern void func_0204f7ac(s32 *out, s32 v0, s32 v1, s32 v2, s32 v3);
extern Vec3 *data_021c80bc;
extern Vec3 *data_ov068_022772f0;
int func_ov068_0226e008(UnkStruct_0226e008 *self)
{
    Vec3 *g;
    u16 arr[2];
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 out[3];
    Subst *p;
    func_0203caa4(self, 0, 0);
    func_0203c99c(self, 0);
    func_0203ad68();
    g = data_021c80bc;
    v0 = 0;
    v1 = 0;
    v2 = 0;
    v3 = 0;
    p = &self->sub;
    p->type = 0x3c;
    p->type2 = 0;
    if (g) {
        arr[0] = 0x5014;
        arr[1] = 0x501a;
        if (func_0204f490(g, &v0, &v1, &v2, &v3, arr, arr + 1, 1, 0) == 1) {
            func_0204f7ac(out, v0, v1, v2, v3);
            p->vec = data_ov068_022772f0;
            self->pos[0] = out[0];
            self->pos[1] = out[1];
            self->pos[2] = out[2];
        }
    }
    p->dest[0] = self->pos[0];
    p->dest[1] = self->pos[1];
    p->dest[2] = self->pos[2];
    self->pos[0] += p->vec->x;
    self->pos[1] += p->vec->y;
    self->pos[2] += p->vec->z;
    p->counter = 0;
    return 1;
}
