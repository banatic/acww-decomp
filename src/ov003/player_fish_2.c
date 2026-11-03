/* player_fish_2: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222924c @ 0x0222924c, 0xf0 bytes, Thumb
 * func_ov003_022291e4 @ 0x022291e4, 0x68 bytes, Thumb
 * func_ov003_022291c8 @ 0x022291c8, 0x1c bytes, Thumb
 * func_ov003_02229184 @ 0x02229184, 0x44 bytes, Thumb
 * func_ov003_02229100 @ 0x02229100, 0x84 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x80 - 0x44];
    u8 unk_80;
    char pad_81[0xa4 - 0x81];
} UnkStruct_0222924c;

typedef struct {
    int a;
    int b;
} UnkStruct_022291e4;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xa4 - 0x44];
} UnkStruct_022291e4_2;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x60];
} UnkStruct_022291c8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[4];
    int unk_48;
    char pad_4C[0x14];
    Vec3 unk_60;
    char pad_6C[0x24];
    int unk_90;
    char pad_94[0x10];
} UnkStruct_02229184;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char p2[0x60 - 0x44];
    Vec3 unk_60;
    char p3[0xa4 - 0x6c];
} UnkStruct_02229100;

extern UnkStruct_0222924c data_ov003_0225f4dc[];
extern void *data_020ccf94;
extern int func_02073918(void *h, int i);
extern int func_0204fee8(u8 i);
extern void func_0204ff00(u8 i, int a, int b, int c, int d);
extern int func_0204fed0(u8 k);
extern int func_0204feac(UnkStruct_022291e4 *p, int *q, u8 k);
extern int func_ov003_0222a960(unsigned i, int k);

void func_ov003_022291e4(void *a0, int idx);
int func_ov003_022291c8(void *a, unsigned int i);
int func_ov003_02229184(void *a, unsigned int i, int k, Vec3 *v);
int func_ov003_02229100(void *a0, unsigned i);

void func_ov003_0222924c(char *self)
{
    void *h;
    int i;
    i = 0;
    h = data_020ccf94;
    for (; i < 4; i++) {
        int st;
        UnkStruct_0222924c *e;
        if (func_02073918(h, i)) {
            continue;
        }
        st = func_0204fee8((u8) i);
        if (st == 9) {
            st = 1;
        }
        switch (st) {
            case 0:
                func_ov003_022291e4((void *) self, i);
                break;
            case 6:
                e = &data_ov003_0225f4dc[i];
                e->unk_80 = 1;
                func_ov003_022291e4((void *) self, i);
                break;
            case 1:
                if (func_ov003_022291c8((void *) self, (u8) ((u8) i))) {
                    func_0204ff00((u8) i, 8, -1, 0, 0);
                } else {
                    e = &data_ov003_0225f4dc[i];
                    e->unk_40 = 4;
                }
                break;
            case 9:
                break;
            case 2:
                if (func_ov003_02229100((void *) self, (u8) ((u8) i))) {
                    func_0204ff00((u8) i, 8, -1, 0, 0);
                } else {
                    e = &data_ov003_0225f4dc[i];
                    e->unk_40 = 4;
                }
                break;
        }
    }
}

void func_ov003_022291e4(void *a0, int idx)
{
    UnkStruct_022291e4 p;
    int q;
    int t;
    t = func_0204fed0((u8) idx);
    p.b = 0xffffeccd;
    if (func_0204feac(&p, &q, (u8) idx)) {
        if (func_ov003_02229184(a0, (u8) ((u8) idx), t, (Vec3 *) (&p))) {
            func_0204ff00((u8) idx, 3, -1, 0, 0);
        } else {
            UnkStruct_022291e4_2 *e = &((UnkStruct_022291e4_2 *) data_ov003_0225f4dc)[idx];
            e->unk_40 = 4;
        }
    }
}

int func_ov003_022291c8(void *a, unsigned int i)
{
    UnkStruct_022291c8 *e;
    if (i >= 4) {
        return 0;
    }
    e = &((UnkStruct_022291c8 *) data_ov003_0225f4dc)[i];
    e->unk_40 = 4;
    return 1;
}

int func_ov003_02229184(void *a, unsigned int i, int k, Vec3 *v)
{
    UnkStruct_02229184 *e;
    Vec3 *q;
    if (i >= 4) {
        return 0;
    }
    e = &((UnkStruct_02229184 *) data_ov003_0225f4dc)[i];
    if (e->unk_40 != 0) {
        return 0;
    }
    q = &e->unk_60;
    q->x = v->x;
    q->y = v->y;
    q->z = v->z;
    e->unk_90 = k;
    e->unk_40 = 1;
    e->unk_48 = 2;
    return 1;
}

int func_ov003_02229100(void *a0, unsigned i)
{
    UnkStruct_02229100 *e;
    volatile Vec3 v;
    Vec3 *s;
    int st;
    if (i >= 4) {
        return 0;
    }
    e = &((UnkStruct_02229100 *) data_ov003_0225f4dc)[i];
    s = &e->unk_60;
    v.x = s->x;
    v.y = s->y;
    v.z = s->z;
    st = e->unk_40;
    if (st == 3) {
        if (func_ov003_0222a960(i, 0) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    } else if (st == 0) {
        if (func_ov003_0222a960(i, 1) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    } else if (st == 2) {
        e->unk_40 = 3;
        if (func_ov003_0222a960(i, 0) == 0) {
            e->unk_40 = 4;
            return 0;
        }
    }
    return 1;
}
