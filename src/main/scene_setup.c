/* scene_setup: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b0ea8 @ 0x020b0ea8, 0xac bytes, Thumb
 * func_020b0d08 @ 0x020b0d08, 0x1a0 bytes, Thumb
 * func_020b0c4c @ 0x020b0c4c, 0xbc bytes, Thumb
 * func_020b0bbc @ 0x020b0bbc, 0x90 bytes, Thumb
 * func_020b0b00 @ 0x020b0b00, 0xbc bytes, Thumb
 * func_020b0ae0 @ 0x020b0ae0, 0x20 bytes, Thumb
 * func_020b0ad4 @ 0x020b0ad4, 0xc bytes, Thumb
 * func_020b0abc @ 0x020b0abc, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_020b0ea8;

typedef struct {
    u16 unk_00;
    short unk_02;
    short unk_04;
    short unk_06;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020b0ea8_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[2];
    UnkStruct_020b0ea8_2 *e;
} UnkStruct_020b0ea8_3;

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

typedef struct {
    unsigned char pad_00[4];
    void *target;
} self_t;

typedef struct {
    int arrA[2];
    int valA;
    int arrB[1];
    unsigned char pad_10[4];
    int valB;
    int arrC[3];
    int arrD[1];
    unsigned char pad_end[8];
} LocalData;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020b0c4c;

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_020b0bbc;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[2];
    UnkStruct_020b0bbc *e;
} UnkStruct_020b0bbc_2;

typedef struct {
    u8 unk_00;
    u8 pad[7];
} UnkStruct_020b0b00;

typedef struct {
    u16 unk_00;
    u16 pad;
    UnkStruct_020b0b00 *e;
} UnkStruct_020b0b00_2;

typedef int (*Fn)(UnkStruct_020b0b00 *e, u8 *flag, u64 t);

struct UnkParam {
    unsigned char pad_00[6];
    unsigned short unk_06;
};

struct UnkStruct_020b0ad4 {
    int unk_00;
    int unk_04;
    void *unk_08;
};

typedef struct UnkStruct_020b0b00_2_020b0abc UnkStruct_020b0b00_2_020b0abc;

extern u64 OS_GetTick(void);
extern int func_02003348(u16 a, int b, UnkStruct_020b0ea8 *v, void *p, int z);
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
extern int func_020b65c4(void);
extern int func_020b6788(void);
extern unsigned char func_02073dd4(void *a, int b);
extern void func_020952ac(int idx, int *a, int *b, int val);
extern int func_020961c0(void);
extern void func_020961f0(int a, int b);
extern int func_0202f134(int a, int b, int c, int d);
extern int data_021f42f4;
extern Fn data_020e41ec[];

int func_020b0ea8(UnkStruct_020b0ea8_3 *self, u8 *cnt, u64 start)
{
    unsigned int ok;
    UnkStruct_020b0ea8 v;
    int i;
    UnkStruct_020b0ea8_2 *e;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    for (;;) {
        {
            int t2 = ((int) e->unk_06 << 12) >> 4;
            int t1 = ((int) e->unk_04 << 12) >> 4;
            int t0 = ((int) e->unk_02 << 12) >> 4;
            v.x = t0;
            v.y = t1;
            v.z = t2;
        }
        func_02003348(e->unk_00, e->unk_10, &v, &e->unk_08, 0);
        e++;
        i++;
        if (cnt != 0) {
            *cnt = (u8) (*cnt + 1);
        }
        if (i >= self->unk_01) {
            break;
        }
        if (cnt != 0) {
            if ((u32) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                ok = 0;
                break;
            }
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}

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

int func_020b0c4c(self_t *self)
{
    LocalData data;
    void *target = self->target;
    unsigned int idx;

    if (target != 0) {
        if (func_020b65c4() != 0xd && func_020b65c4() != 0xe && func_020b65c4() != 0x2f) {
            if (func_020b6788() != 0) {
                func_02073dd4((*(UnkStruct_020b0c4c **) &data_020ccf94), (*(UnkStruct_020b0c4c **) &data_020ccf94)->unk_64);
                for (idx = 0; idx < 4; idx++) {
                    if (func_020b0d08((UnkStruct_020b0d08 *) target, idx, 1, (Vec *) data.arrC, (Rot *) data.arrA,
                                      &data.valA) != 0) {
                        func_020952ac(idx, data.arrC, data.arrA, data.valA);
                    }
                }
            } else {
                for (idx = 0; idx < 4; idx++) {
                    if (func_020b0d08((UnkStruct_020b0d08 *) target, idx, 0, (Vec *) data.arrD, (Rot *) data.arrB,
                                      &data.valB) != 0) {
                        func_020961f0(idx, func_020961c0());
                        func_020952ac(idx, data.arrD, data.arrB, data.valB);
                    }
                }
            }
        }
    }

    func_0202f134(0xb, data_021f42f4, 0, 0);
    return 1;
}

int func_020b0bbc(UnkStruct_020b0bbc_2 *self, u8 *cnt, u64 start)
{
    unsigned int ok;
    u8 i;
    UnkStruct_020b0bbc *e;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    for (;;) {
        func_0202f134(e->a, data_021f42f4, e->b, 0);
        e++;
        i = (u8) (i + 1);
        if (cnt != 0) {
            *cnt = (u8) (*cnt + 1);
        }
        if (i >= self->unk_01) {
            break;
        }
        if (cnt != 0) {
            if ((unsigned int) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                ok = 0;
                break;
            }
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}

int func_020b0b00(UnkStruct_020b0b00_2 *self, u8 *cnt, u8 *flag, u64 start)
{
    unsigned int ok;
    int ret;
    int i;
    UnkStruct_020b0b00 *e;
    Fn fn;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    while (i < (int) self->unk_00) {
        ret = ok;
        fn = data_020e41ec[e->unk_00];
        if (fn != 0) {
            ret = fn(e, flag, start);
        }
        if (ret != 0) {
            e++;
            i++;
            if (flag != 0) {
                *flag = 0;
            }
            if (cnt != 0) {
                *cnt = (u8) (*cnt + 1);
            }
            if (i >= (int) self->unk_00) {
                break;
            }
            if (cnt != 0) {
                if ((u32) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                    ok = 0;
                    break;
                }
            }
            continue;
        }
        ok = 0;
        break;
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}

void func_020b0ae0(struct UnkParam *param)
{
    func_0202f134(0xc, (int) ((*(void **) &data_021f42f4)), (unsigned short) param->unk_06, 0);
}

void func_020b0ad4(struct UnkStruct_020b0ad4 *self)
{
    func_020b0ae0((struct UnkParam *) self->unk_08);
}

int func_020b0abc(UnkStruct_020b0b00_2_020b0abc **ptr, u8 *cnt, u8 *flag, u64 start)
{
    return func_020b0b00((UnkStruct_020b0b00_2 *) (*ptr), cnt, flag, start);
}
