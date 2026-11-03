/* player_actor_ops_4: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02096188 @ 0x02096188, 0x8 bytes, Thumb
 * func_02096180 @ 0x02096180, 0x8 bytes, Thumb
 * func_02096174 @ 0x02096174, 0xc bytes, Thumb
 * func_02096168 @ 0x02096168, 0xc bytes, Thumb
 * func_0209615c @ 0x0209615c, 0xc bytes, Thumb
 * func_02096150 @ 0x02096150, 0xc bytes, Thumb
 * func_02096144 @ 0x02096144, 0xc bytes, Thumb
 * func_02096124 @ 0x02096124, 0x1e bytes, Thumb
 * func_020960f8 @ 0x020960f8, 0x2c bytes, Thumb
 * func_020960d8 @ 0x020960d8, 0x20 bytes, Thumb
 * func_02095fc0 @ 0x02095fc0, 0x118 bytes, Thumb
 * func_02095f90 @ 0x02095f90, 0x30 bytes, Thumb
 * func_02095f58 @ 0x02095f58, 0x38 bytes, Thumb
 * func_02095f4c @ 0x02095f4c, 0xc bytes, Thumb
 * func_02095f28 @ 0x02095f28, 0x24 bytes, Thumb
 * func_02095f08 @ 0x02095f08, 0x20 bytes, Thumb
 * func_02095eec @ 0x02095eec, 0x1c bytes, Thumb
 * func_02095ed0 @ 0x02095ed0, 0x1c bytes, Thumb
 * func_02095ec4 @ 0x02095ec4, 0xc bytes, Thumb
 * func_02095ea4 @ 0x02095ea4, 0x20 bytes, Thumb
 * func_02095e84 @ 0x02095e84, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct UnkStruct_02095fc0 {
    unsigned char pad_00[0x5c];
    Vec vec;
    unsigned char pad_68[0x8e - 0x68];
    s16 unk_8E;
    unsigned char pad_90[0x7f0 - 0x90];
    int unk_7F0;
} UnkStruct_02095fc0;

typedef struct {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x514];
    int unk_7F0;
} UnkStruct_02095f58;

extern int func_02096718(int);
extern int func_0200f290(int, int);
extern void func_ov004_02228774(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_02228ac4(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_02228b90(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222b85c(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222ae34(UnkStruct_02095fc0 *o, int a);
extern void func_ov004_0222b2d8(UnkStruct_02095fc0 *o, int a);
extern void func_0200fa1c(Vec *out, UnkStruct_02095fc0 *o, Vec *save, s16 *ang, void *tbl);
extern int data_020d18b4;
extern int func_0200f05c(int, int);
extern unsigned int *func_0200f27c(int, int);
extern void func_0200f268(int, int);

int func_02096124(int a, int b);
int func_020960f8(void *param1, void *param2);
int func_02095ea4(int a, int b);
int func_02095e84(int a, int b);

int func_02096188(int p0)
{
    return ((int) ((unsigned int) (p0) >> 30) & 3);
}

int func_02096180(int p0)
{
    return ((int) ((unsigned int) (p0) >> 22) & 255);
}

int func_02096174(void)
{
    return func_02096124(1, 4);
}

int func_02096168(void)
{
    int r0;
    int r1;

    r0 = 4;
    r1 = r0;
    return func_02096124(r0, r1);
}

int func_0209615c(int a)
{
    return func_02096124(5, a);
}

int func_02096150(void)
{
    return func_020960f8((void *) 5, (void *) 4);
}

int func_02096144(void)
{
    return func_020960f8((void *) 0x90, (void *) 4);
}

int func_02096124(int a, int b)
{
    int result = func_02096718(b);
    if (result != 0) {
        return func_0200f290(result, a);
    }
    return 0;
}

int func_020960f8(void *param1, void *param2)
{
    void *r4;
    void *r0;
    int result;

    r4 = param1;
    r0 = param2;
    result = func_02096718((int) r0);
    if (result != 0) {
        if (*(int *) ((char *) result + 0x7f0) == (int) r4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int func_020960d8(int object)
{
    int result;
    int *ptr;

    result = func_02096718(object);
    if (result != 0) {
        result = *(int *) ((char *) result + 0x7f0);
    } else {
        result = 0x93;
    }
    return result;
}

int func_02095fc0(Vec *outv, s16 *outang)
{
    UnkStruct_02095fc0 *o;
    Vec save;
    Vec tmp;
    Vec *q;
    s16 ang;
    int v;

    o = (UnkStruct_02095fc0 *) func_02096718(4);
    if (o == 0) {
        goto fail;
    }
    q = &o->vec;
    save.x = o->vec.x;
    save.y = q->y;
    save.z = q->z;
    ang = o->unk_8E;
    v = o->unk_7F0;
    switch (v) {
        case 16:
            v = 2;
            break;
        case 0x2c:
            v = 2;
            func_ov004_02228774(o, v);
            break;
        case 0x29:
        case 0x2a:
            if (v == 0x29) {
                func_ov004_02228ac4(o, 0x2c);
            } else {
                func_ov004_02228b90(o, 0x2c);
            }
            v = 2;
            func_0200fa1c(&tmp, o, &save, &o->unk_8E, &data_020d18b4);
            q = &o->vec;
            o->vec.x = tmp.x;
            q->y = tmp.y;
            q->z = tmp.z;
            break;
        case 14:
            v = 2;
            break;
        case 9:
        case 11:
        case 12:
            v = 8;
            break;
        case 10:
            v = 2;
            func_ov004_0222b85c(o, v);
            break;
        case 15:
            v = 8;
            func_ov004_0222ae34(o, v);
            break;
        case 13:
            v = 8;
            func_ov004_0222b2d8(o, v);
            break;
    }
    q = &o->vec;
    outv->x = o->vec.x;
    outv->y = q->y;
    outv->z = q->z;
    *outang = o->unk_8E;
    o->vec.x = save.x;
    q->y = save.y;
    q->z = save.z;
    o->unk_8E = ang;
    return v;
fail:
    return 0x93;
}

int func_02095f90(void)
{
    void *p;
    int v;

    p = (void *) func_02096718(4);
    if (p != 0) {
        v = *(int *) ((char *) p + 0x7f0);
        if (v != 0) {
            return v;
        }
        return (*(unsigned int *) ((char *) p + 8) >> 22) & 0xff;
    } else {
        return 0x93;
    }
}

int func_02095f58(void)
{
    UnkStruct_02095f58 *p;
    p = (UnkStruct_02095f58 *) func_02096718(4);
    if (p != 0 && p->unk_7F0 == 7 && p->unk_2D8 < 0x13000) {
        return 1;
    }
    return 0;
}

int func_02095f4c(void)
{
    return func_020960f8((void *) 0x3f, (void *) 4);
}

int func_02095f28(void)
{
    void *ptr = (void *) func_02096718(4);
    if (ptr) {
        return func_0200f05c((int) ptr, *(int *) ((char *) ptr + 0x7f0));
    }
    return 0;
}

int func_02095f08(int param)
{
    if (param) {
        return func_02095ea4(0xb, 4);
    } else {
        return func_02095e84(0xb, 4);
    }
}

void func_02095eec(int param, int argument1)
{
    if (param != 0) {
        func_02095ea4(14, (int) argument1);
    } else {
        func_02095e84(14, argument1);
    }
}

int func_02095ed0(int param, int argument1)
{
    if (param != 0) {
        return func_02095ea4(0x10, argument1);
    } else {
        return func_02095e84(0x10, (int) argument1);
    }
}

int func_02095ec4(void)
{
    return func_02095ea4(0x17, 4);
}

int func_02095ea4(int a, int b)
{
    int result;
    result = func_02096718(b);
    if (result != 0) {
        func_0200f27c(result, a);
        return 1;
    }
    return 0;
}

int func_02095e84(int a, int b)
{
    int ret;
    if ((ret = func_02096718(b))) {
        func_0200f268(ret, a);
        return 1;
    }
    return 0;
}
