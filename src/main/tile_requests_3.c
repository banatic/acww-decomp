/* tile_requests_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02043540 @ 0x02043540, 0x14 bytes, Thumb
 * func_02043484 @ 0x02043484, 0xbc bytes, Thumb
 * func_02043368 @ 0x02043368, 0x11c bytes, Thumb
 * func_020431c8 @ 0x020431c8, 0x1a0 bytes, Thumb
 * func_020431b8 @ 0x020431b8, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y;
} Pair;

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    int e[9];
} Row;

typedef struct {
    u16 unk_00;
} Res;

typedef struct {
    u8 pad_00[0x68];
    int unk_68;
} UnkStruct_02043368;

typedef struct {
    u8 pad_00[0x5c];
    u8 unk_5C[0x8e - 0x5c];
    short unk_8E;
} UnkStruct_02043368_2;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020431c8;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    u16 unk_10;
    u16 unk_12;
    int unk_14;
    int unk_18;
    u8 unk_1C;
    u8 pad_1D[7];
} Entry;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_020431c8 vec;
} UnkStruct_020431c8_2;

extern int func_02044858(int a);
extern int func_020435a0(int a, int b);
extern void *func_0204f5e0(int a, int hi2, int hi3, int lo2, int lo3, int z);
extern int func_020317c4(int a, int b, int c, int d, int e);
extern int func_0204ed80(int a, int b, int c);
extern void *data_021c80bc;
extern UnkStruct_02043368 *data_020ccf94;
extern Row data_020cb638[];
extern u8 data_020ca634[];
extern UnkStruct_02043368_2 *func_020961a8(int);
extern int func_020644e4(short);
extern void func_0204f818(volatile int *, volatile int *, u8 *);
extern int func_02045d80(Pt *, int);
extern int func_02045ac4(Pt *, int);
extern int func_020b6660(void);
extern int func_02051d44(int, int);
extern int func_ov003_02221118(int a, int w, Pt *p);
extern int func_ov003_02221304(int a, int w, Pt *p, UnkStruct_020431c8 *v);
extern int func_ov004_022335b8(int a, int w, Pt *p, UnkStruct_020431c8 *v, int z);
extern Entry data_021c7c48[];
extern u8 data_020e54a8;
extern void func_02042f10(void *a, void *b);

int func_02043540(int a, int b)
{
    return func_020435a0(func_02044858(a), b);
}

void *func_02043484(int p0, int p1, int p2, int p3, Pair *p4)
{
    int hi2 = p2 >> 4;
    int hi3 = p3 >> 4;
    int lo3 = p3 - (hi3 << 4);
    int lo2 = p2 - (hi2 << 4);
    void *r5;

    r5 = func_0204f5e0(p1, hi2, hi3, lo2, lo3, 0);
    if (r5 == 0) {
        goto exit;
    }
    if (*(unsigned short *) r5 != 0xFFF1) {
        r5 = 0;
        goto exit;
    }

    switch ((unsigned int) (p0 - 16)) {
        case 0:
        case 1:
        case 2:
            if (func_020317c4(p4->x, p4->y, p2, p3, 0) == 0) {
                r5 = 0;
            }
            break;
        case 8: {
            int res = func_0204ed80(p1, p2, p3);
            if (res != 0 && res != 1) {
                r5 = 0;
            }
            break;
        }
        case 10:
            if (func_020317c4(p4->x, p4->y, p2, p3, 1) == 0) {
                r5 = 0;
            }
            break;
        default:
            break;
    }

exit:
    return r5;
}

int func_02043368(void *a0, volatile Pt *a1, u8 *a2)
{
    int ret;
    int *p;
    int i;
    void *ptr;
    UnkStruct_02043368 *g2;
    int w;
    Pt tmp;
    Pt pt;
    Pt pt2;
    UnkStruct_02043368_2 *obj;
    int v;
    int b;
    int nx;
    int ny;
    Res *res;
    int n;

    ptr = data_021c80bc;
    obj = func_020961a8(4);
    ret = 0;
    if (ptr != 0 && obj != 0) {
        p = data_020cb638[func_020644e4(obj->unk_8E)].e;
        func_0204f818(&a1->x, &a1->y, obj->unk_5C);
        i = 0;
        g2 = data_020ccf94;
        w = i;
        for (; i < 9; i++) {
            v = *p;
            b = data_020ca634[v];
            nx = a1->x + ((b >> 4) - 8);
            ny = a1->y + ((b & 0xf) - 8);
            tmp.x = a1->x;
            tmp.y = a1->y;
            res = (Res *) func_02043484((int) a0, (int) ptr, nx, ny, (Pair *) (&tmp));
            if (res != 0 && res->unk_00 == 0xfff1) {
                pt.x = nx;
                pt.y = ny;
                if (func_02045d80(&pt, w) < 0) {
                    n = g2->unk_68;
                    pt2.x = nx;
                    pt2.y = ny;
                    if (func_02045ac4(&pt2, n)) {
                        a1->x = nx;
                        a1->y = ny;
                        if (a2) {
                            *a2 = 0;
                        }
                        ret = 1;
                        break;
                    }
                }
            }
            if (func_020b6660() == 0) {
                if (func_02051d44(nx, ny)) {
                    a1->x = nx;
                    a1->y = ny;
                    if (a2) {
                        *a2 = 1;
                    }
                    ret = 1;
                    break;
                }
            }
            p++;
        }
    }
    return ret;
}

int func_020431c8(int idx)
{
    UnkStruct_020431c8 *q;
    unsigned int s4;
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int s8;
    unsigned int sc;
    unsigned int s10;
    unsigned int s14;
    volatile u16 w;
    Pt pa;
    Pt pb;
    Pt pc_;
    UnkStruct_020431c8 va;
    UnkStruct_020431c8 vb;
    void *ctx;
    int ret;
    Entry *e;
    int k;
    UnkStruct_020431c8_2 *o;
    unsigned int f;
    unsigned int v;
    unsigned int v2;
    int bb;

    ctx = data_021c80bc;
    ret = 0;
    e = &data_021c7c48[idx];
    if (ctx == 0) {
        return ret;
    }
    switch (e->unk_08) {
        case 2:
            o = (UnkStruct_020431c8_2 *) func_020961a8(4);
            if (ctx == 0) {
                goto end;
            }
            if (o == 0) {
                goto end;
            }
            q = &o->vec;
            if (data_020e54a8 == 0) {
                f = 1;
            } else {
                f = 0;
            }
            if (f == 0) {
                goto third;
            }
            w = 0xfff1;
            w = e->unk_10;
            s10 = sc = s8 = rc = rb = ra = s4 = 1;
            s14 = 0;
            v = w;
            v2 = w;
            if (v2 <= 5) {
                s14 = 1;
            }
            if (s14 == 0) {
                if (!(v >= 6 && v <= 0xb)) {
                    s10 = 0;
                }
            }
            if (s10 == 0) {
                if (!(v >= 0xc && v <= 0x11)) {
                    sc = 0;
                }
            }
            if (sc == 0) {
                if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
                    s8 = 0;
                }
            }
            if (s8 == 0) {
                if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
                      (v >= 0x9c && v <= 0xa3) || v == 0xa5)) {
                    rc = 0;
                }
            }
            if (rc == 0) {
                if (v != 0x1a) {
                    rb = 0;
                }
            }
            if (rb == 0) {
                if (v != 0xa4) {
                    ra = 0;
                }
            }
            if (ra == 0) {
                if (v != 0x1d) {
                    s4 = 0;
                }
            }
            if (s4 != 0 || (v >= 0xa7 && v <= 0xc6) || v == 0x1e) {
                pa.x = e->unk_14;
                pa.y = e->unk_18;
                if (func_ov003_02221118(e->unk_00, e->unk_10, &pa) == 0) {
                    goto end;
                }
                ret = 1;
                goto end;
            }
            va.a = q->a;
            va.b = q->b;
            va.c = q->c;
            pb.x = e->unk_14;
            pb.y = e->unk_18;
            if (func_ov003_02221304(e->unk_00, e->unk_10, &pb, &va) == 0) {
                goto end;
            }
            ret = 1;
            goto end;
        third:
            vb.a = q->a;
            vb.b = q->b;
            vb.c = q->c;
            bb = e->unk_1C;
            pc_.x = e->unk_14;
            pc_.y = e->unk_18;
            if (func_ov004_022335b8(e->unk_00, e->unk_10, &pc_, &vb, bb) == 0) {
                goto end;
            }
            ret = 1;
            goto end;
        case 3:
            ret = 2;
            break;
    }
end:
    return ret;
}

void func_020431b8(void *arg)
{
    func_02042f10(((char *) data_021c7c48), arg);
}
