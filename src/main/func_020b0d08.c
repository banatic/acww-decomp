/* func_020b0d08 @ 0x020b0d08, 0x1a0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;
typedef struct Rot {
    s16 x, y, z;
} Rot;
typedef struct UnkStruct_020b0d08 {
    s16 unk_00;
    s16 x;
    s16 y;
    s16 z;
    s16 r[3];
    s16 pad_0E;
    int unk_10;
} UnkStruct_020b0d08;

extern int func_02096284(int);
extern int func_020988a4(void *, int);
extern int func_02073908(void *, int);
extern void *func_020b5e10(void);
extern int func_020b5e24(void *mgr);
extern Vec *func_020b5e40(void *mgr);
extern int func_020b5e38(void *mgr);
extern int func_020b5e34(void *mgr);
extern int func_020b6660(void);
extern void func_020ea6e0(Vec *, int);
extern void func_01ffd070(Vec *, Vec *, Vec *);
extern int data_021dc7bc;
extern void *data_020ccf94;

static inline void GetEnt(UnkStruct_020b0d08 *e, Vec *out, Rot *rot, int *pw)
{
    s16 *q = e->r;
    int x, y, z;
    z = (e->z << 12) >> 4;
    y = (e->y << 12) >> 4;
    x = (e->x << 12) >> 4;
    out->x = x;
    out->y = y;
    out->z = z;
    rot->x = q[0];
    rot->y = q[1];
    rot->z = q[2];
    *pw = e->unk_10;
}
int func_020b0d08(UnkStruct_020b0d08 *arr, int p1, int p2, Vec *out, Rot *rot, int *pw)
{
    int idx;
    Vec v;
    Vec o2;
    Vec *s;
    int t;

    if (p2 != 0) {
        idx = func_02096284(p1);
        if (idx >= 4) {
            goto fail;
        }
        if (func_020988a4(&data_021dc7bc, func_02096284(p1)) == 0) {
            goto fail;
        }
        if (func_02073908(data_020ccf94, p1) != 0) {
            if (func_020b5e24(func_020b5e10()) == 0) {
                goto alt;
            }
        }
        GetEnt(&arr[idx], out, rot, pw);
        goto ok1;
    alt:
        s = func_020b5e40(func_020b5e10());
        out->x = s->x;
        out->y = s->y;
        out->z = s->z;
        t = func_020b5e38(func_020b5e10());
        rot->x = 0;
        rot->y = (s16) t;
        rot->z = 0;
        *pw = func_020b5e34(func_020b5e10());
    ok1:
        return 1;
    }
    if (func_02073908(data_020ccf94, p1) == 0) {
        goto fail;
    }
    if (func_020b5e24(func_020b5e10()) != 0) {
        GetEnt(arr, out, rot, pw);
        goto ok2;
    }
    v.x = 0;
    v.y = 0;
    v.z = 0;
    if (func_020b6660() == 0) {
        p1 = p1 & 3;
        v.x = (p1 << 10) - 0x800;
        v.y = 0;
        v.z = 0;
        func_020ea6e0(&v, func_020b5e38(func_020b5e10()));
    }
    func_01ffd070(&o2, func_020b5e40(func_020b5e10()), &v);
    out->x = o2.x;
    out->y = o2.y;
    out->z = o2.z;
    t = func_020b5e38(func_020b5e10());
    rot->x = 0;
    rot->y = (s16) t;
    rot->z = 0;
    *pw = func_020b5e34(func_020b5e10());
ok2:
    return 1;
fail:
    return 0;
}
