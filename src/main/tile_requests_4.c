/* tile_requests_4: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02043d18 @ 0x02043d18, 0x1c bytes, Thumb
 * func_02043cdc @ 0x02043cdc, 0x3a bytes, Thumb
 * func_02043b40 @ 0x02043b40, 0x19c bytes, Thumb
 * func_02043a70 @ 0x02043a70, 0xd0 bytes, Thumb
 * func_02043a4c @ 0x02043a4c, 0x24 bytes, Thumb
 * func_020439b4 @ 0x020439b4, 0x98 bytes, Thumb
 * func_02043990 @ 0x02043990, 0x24 bytes, Thumb
 * func_020438dc @ 0x020438dc, 0xb4 bytes, Thumb
 * func_02043830 @ 0x02043830, 0xac bytes, Thumb
 * func_020436a8 @ 0x020436a8, 0x188 bytes, Thumb
 * func_02043634 @ 0x02043634, 0x74 bytes, Thumb
 * func_020435fc @ 0x020435fc, 0x38 bytes, Thumb
 * func_020435a0 @ 0x020435a0, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02043cdc;

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    unsigned int lo;
    unsigned int hi;
} U64;

typedef struct {
    int x;
    int y;
} UnkStruct_020436a8;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020436a8_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    int unk_14;
    int unk_18;
    unsigned char unk_1C;
    unsigned char pad[7];
} UnkStruct_020436a8_3;

typedef struct {
    unsigned char pad[0x64];
    int unk_64;
} UnkStruct_020436a8_4;

typedef struct {
    unsigned char pad[0x5c];
    UnkStruct_020436a8_2 v;
} UnkStruct_020436a8_5;

typedef struct {
    int x;
    int y;
} Vec2;

typedef struct {
    u8 flag;
    u16 a;
    u16 b;
} UnkStruct_02043634;

extern int func_02044858(int);
extern int func_02043d34(int, int, int, int);
extern int func_020b6660(void);
extern int func_0204f294(void *ctx, int x, int y);
extern void *data_021c80bc;
extern int data_021c7c48[];
extern void *func_0204f5e0(void *obj, int a, int b, int c, int d, int flag);
extern int func_02042f20(void *table, int arg, int type, void *coords, int a5, int a6, int a7, int a8, int a9, int a10);
extern void *func_0204e414(void);
extern int func_0204eda8(void *ctx, int x, int y);
extern UnkStruct_020436a8_4 *data_020ccf94;
extern unsigned short data_020ca664[];
extern int func_02073d90(UnkStruct_020436a8_4 *g);
extern UnkStruct_020436a8_5 *func_020961a8(int n);
extern int func_0204ba94(volatile unsigned short *p);
extern int func_0204b710(volatile unsigned short *p);
extern void func_02045f08(UnkStruct_020436a8 *p, int a);
extern void func_ov003_02220e20(int a, int b, UnkStruct_020436a8 *p, UnkStruct_020436a8_2 *v);
extern int func_ov003_02221118(int a, int b, UnkStruct_020436a8 *p);
extern int func_02043368(void *, Vec2 *, u8 *);
extern int func_020445c0(u16 *, u16 *, u16);
extern int func_0204482c(void *);
extern void *func_02045b5c(void *);

int func_02043b40(void *a0, Pt *p);
int func_02043a70(int arg0, int *coords);

int func_02043d18(int a, int b, int c, int d)
{
    return func_02043d34(func_02044858(a), b, c, d);
}

int func_02043cdc(void *obj, UnkStruct_02043cdc *src, int value)
{
    if (func_020b6660()) {
        UnkStruct_02043cdc temp;
        temp.unk_00 = src->unk_00;
        temp.unk_04 = src->unk_04;
        return func_02043b40(obj, (Pt *) (&temp));
    } else {
        UnkStruct_02043cdc temp;
        temp.unk_00 = src->unk_00;
        temp.unk_04 = src->unk_04;
        return func_02043a70((int) obj, (int *) (&temp));
    }
}

int func_02043b40(void *a0, Pt *p)
{
    int ret;
    unsigned int d;
    unsigned int c;
    unsigned int b;
    unsigned int a;
    void *ctx;
    Pt v3;
    unsigned int e;
    unsigned int t;
    unsigned int v;
    unsigned int v2;
    unsigned short *o;
    int kind;
    int x, z;
    int cx, cz;
    int hi;

    ctx = data_021c80bc;
    ret = -1;
    if (ctx == 0) {
        goto tail;
    }
    x = p->x;
    z = p->y;
    cx = x >> 4;
    cz = z >> 4;
    o = (unsigned short *) func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (o == 0) {
        goto tail;
    }
    t = *o;
    kind = 0;
    if (t == 0xfff1) {
        ret = -1;
        goto done;
    }
    if ((t >= 0x21 && t <= 0x24) || t == 0x1f) {
        kind = 5;
        goto done;
    }
    hi = ((int) (t & 0xf000)) >> 12;
    if (hi == 1) {
        if (func_0204f294(ctx, p->x, p->y) == 0) {
            goto set3;
        }
    }
    d = 1;
    c = 1;
    b = 1;
    a = 0;
    v = *o;
    if (v <= 5) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 6 && v <= 0xb)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0xc && v <= 0x11)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
            d = 0;
        }
    }
    if (d != 0) {
        goto set3;
    }
    if (t == 0x1a) {
        goto set3;
    }
    if (t == 0x1d) {
        goto set3;
    }
    if (t == 0x1e) {
        goto set3;
    }
    hi = ((int) (v & 0xf000)) >> 12;
    if (hi == 3) {
        goto chk2;
    }
    if (hi == 4) {
    chk2:
        if (func_0204f294(ctx, p->x, p->y) == 0) {
            goto set3;
        }
    }
    e = 0;
    v2 = *o;
    if (v2 >= 0xa7 && v2 <= 0xc6) {
        e = 1;
    }
    if (e != 0) {
    set3:
        kind = 3;
        goto done;
    }
    if ((v2 >= 0x6e && v2 <= 0x73) || (v2 >= 0x74 && v2 <= 0x79) || (v2 >= 0x7a && v2 <= 0x7f) || (v2 >= 0x80 && v2 <= 0x87) ||
        (v2 >= 0x8a && v2 <= 0x8f) || (v2 >= 0x90 && v2 <= 0x95) || (v2 >= 0x96 && v2 <= 0x9b) || (v2 >= 0x9c && v2 <= 0xa3) ||
        v2 == 0xa5 || t == 0x88 || t == 0xa4) {
        kind = 5;
        goto done;
    }
    if (t == 0x20) {
        kind = 0x15;
    }
done:
    if (kind != 0) {
        v3.x = p->x;
        v3.y = p->y;
        ret = func_02042f20(((int *) data_021c7c48), (int) a0, kind, (void *) (&v3), 0xfff1, t, 0, 0, 0, -1);
    }
tail:
    return ret;
}

int func_02043a70(int arg0, int *coords)
{
    void *obj = data_021c80bc;
    int zero = 0;
    int result = ~zero;

    if (obj == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(obj, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }

        {
            int type = 0;
            int saved;
            int mode;
            int v = *(unsigned short *) p;

            if (((v & 0xf000) >> 12) == 1) {
                type = 3;
                saved = v;
                mode = 0;
                goto check;
            } else {
                int x2 = coords[0];
                int y2 = coords[1];
                int hx2 = x2 >> 4;
                int hy2 = y2 >> 4;
                void *p2 = func_0204f5e0(obj, hx2, hy2, x2 - (hx2 << 4), y2 - (hy2 << 4), 1);

                if (p2 != 0) {
                    int v2 = *(unsigned short *) p2;
                    if (((v2 & 0xf000) >> 12) == 1) {
                        type = 3;
                        saved = v2;
                        mode = 1;
                    }
                }
            }

        check:
            if (type != 0) {
                int local[2];
                local[0] = coords[0];
                local[1] = coords[1];
                result = func_02042f20(data_021c7c48, arg0, type, local, 0xfff1, saved, 0, mode, 0, -1);
            }
        }
    }

done:
    return result;
}

int func_02043a4c(int a, int *b, int c)
{
    int tmp[2];
    int x;
    x = func_02044858(a);
    tmp[0] = b[0];
    tmp[1] = b[1];
    return func_02043cdc((void *) x, (UnkStruct_02043cdc *) tmp, c);
}

int func_020439b4(int arg0, int *coords, int mode)
{
    void *obj = data_021c80bc;
    int zero = 0;
    int result = ~zero;

    if (obj == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(obj, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }

        {
            int type = 0;
            int a5 = 0xfff1;
            int ok = 0;
            unsigned int v = *(unsigned short *) p;

            if (v >= 0xfc && v <= 0xfd) {
                ok = 1;
            }
            if (ok != 0 && mode != 2) {
                type = 0x14;
                a5 = 0xfff1;
            }
            if (type != 0) {
                int local[2];
                local[0] = coords[0];
                local[1] = coords[1];
                result = func_02042f20(data_021c7c48, arg0, type, local, a5, a5, 1, 0, 0, -1);
            }
        }
    }

done:
    return result;
}

int func_02043990(unsigned int a, U64 *b, unsigned int c)
{
    int r;
    U64 local;
    r = func_02044858(a);
    local.lo = b->lo;
    local.hi = b->hi;
    return func_020439b4(r, (int *) (&local), c);
}

int func_020438dc(int a0, int *coords, int arg2)
{
    void *ctx;
    int zero;
    int result;
    int sel;
    int v;

    if (func_020b6660() == 0) {
        return ~0;
    }

    ctx = func_0204e414();
    zero = 0;
    result = ~zero;
    if (ctx == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(ctx, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }
        if (*(unsigned short *) p != 0x1566) {
            goto done;
        }
        if (func_0204f294(ctx, coords[0], coords[1]) == 0) {
            goto done;
        }
        sel = 0xfd;
        v = func_02044858(a0);
        if (func_0204eda8(ctx, coords[0], coords[1]) == 0) {
            sel = 0xfc;
        }
        {
            int local[2];
            local[0] = coords[0];
            local[1] = coords[1];
            result = func_02042f20(data_021c7c48, v, 0x19, local, sel, 0xfff1, 0, 0, 0, -1);
        }
    }

done:
    return result;
}

int func_02043830(int a0, int *coords)
{
    void *ctx;
    int zero;
    int result;
    int sel;

    if (func_020b6660() == 0) {
        return ~0;
    }

    ctx = func_0204e414();
    zero = 0;
    result = ~zero;
    if (ctx == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(ctx, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }
        if (*(unsigned short *) p != 0x1566) {
            goto done;
        }
        if (func_0204f294(ctx, coords[0], coords[1]) == 0) {
            goto done;
        }
        sel = 0xfd;
        if (func_0204eda8(ctx, coords[0], coords[1]) == 0) {
            sel = 0xfc;
        }
        {
            int local[2];
            local[0] = coords[0];
            local[1] = coords[1];
            result = func_02042f20(data_021c7c48, 0, 0x19, local, sel, 0xfff1, 0, 0, 0, a0);
        }
    }

done:
    return result;
}

int func_020436a8(unsigned int idx)
{
    UnkStruct_020436a8_3 *e;
    void *h;
    int res;
    UnkStruct_020436a8_4 *g;
    unsigned short *pp;
    int m;
    int n;
    UnkStruct_020436a8_5 *q;
    UnkStruct_020436a8_2 *vp;
    int ok;
    unsigned short lo;
    unsigned short hi;
    volatile unsigned short t;
    UnkStruct_020436a8 pt;
    UnkStruct_020436a8 pt2;
    UnkStruct_020436a8 pt3;
    UnkStruct_020436a8_2 vec;
    int x, y, hx, hy;

    h = data_021c80bc;
    res = 0;
    e = &((UnkStruct_020436a8_3 *) data_021c7c48)[idx];
    if (e->unk_08 == 0 || e->unk_0C == 0 || (g = data_020ccf94, func_02073d90(g) != 0 && e->unk_00 != g->unk_64)) {
        return 2;
    }
    if (h == 0) {
        return 0;
    }
    x = e->unk_14;
    y = e->unk_18;
    hx = x >> 4;
    hy = y >> 4;
    pp = (unsigned short *) func_0204f5e0(h, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if (pp == 0) {
        return 0;
    }
    switch (e->unk_08) {
        case 2:
            switch (e->unk_0C) {
                case 0x13:
                    if (e->unk_10 != 0xfff1) {
                        q = func_020961a8(4);
                        if (q != 0) {
                            m = e->unk_12;
                            vp = &q->v;
                            t = 0xfff1;
                            t = e->unk_10;
                            if (func_0204ba94(&t) != 0) {
                                ok = 0;
                                lo = t;
                                hi = t;
                                if (hi >= 0x2f && lo <= 0x56) {
                                    ok = 1;
                                }
                                if (ok != 0) {
                                    m = data_020ca664[func_0204b710(&t)];
                                } else if (e->unk_10 == 0xc8) {
                                    m = 0x1548;
                                }
                            }
                            vec.a = vp->a;
                            vec.b = vp->b;
                            vec.c = vp->c;
                            pt.x = e->unk_14;
                            pt.y = e->unk_18;
                            func_ov003_02220e20(e->unk_00, m, &pt, &vec);
                        }
                    }
                    res = 1;
                    break;
                case 3:
                case 0x15:
                    if (pp[0] == 0xfff1) {
                        n = e->unk_1C;
                        pt2.x = e->unk_14;
                        pt2.y = e->unk_18;
                        func_02045f08(&pt2, n);
                        res = 2;
                    } else {
                        res = 1;
                    }
                    break;
                case 0x18:
                case 0x1a:
                    if (func_02073d90(g) == 0) {
                        pt3.x = e->unk_14;
                        pt3.y = e->unk_18;
                        func_ov003_02221118(e->unk_00, e->unk_10, &pt3);
                    }
                    res = 1;
                    break;
                default:
                    res = 1;
                    break;
            }
            break;
        case 3:
            res = 2;
            break;
    }
    return res;
}

int func_02043634(int a0, int a1, u16 a2)
{
    UnkStruct_02043634 info;
    Vec2 vec;
    Vec2 vec2;
    int ret;

    vec.x = 0;
    vec.y = 0;
    ret = -1;

    if (func_02043368((void *) a1, &vec, &info.flag) != 0) {
        if (a1 == 0x18) {
            func_020445c0(&info.a, &info.b, a2);
        } else {
            info.a = a2;
            info.b = a2;
        }
        vec2.x = vec.x;
        vec2.y = vec.y;
        ret = func_02042f20(((int *) data_021c7c48), a0, a1, (void *) (&vec2), info.a, info.b, 0, info.flag, 0, -1);
    }
    return ret;
}

int func_020435fc(int p0, unsigned short p1)
{
    volatile unsigned short s;
    unsigned short a, b;
    int flag;
    s = 0xfff1;
    s = p1;
    flag = 0;
    b = s;
    a = s;
    if (a >= 0xa7 && b <= 0xc6) {
        flag = 1;
    }
    return func_02043634(p0, flag ? 0x1a : 0x10, p1);
}

int func_020435a0(void *a, int b)
{
    int ret = -1;
    void *p;
    unsigned short v;
    int buf[2];

    if (func_0204482c(a) == 0) {
        return -1;
    }

    p = func_02045b5c(a);
    if (p != 0) {
        v = *(unsigned short *) p;
        buf[0] = v >> 8;
        buf[1] = v & 0xff;
        ret = func_02042f20((void *) ((unsigned char *) data_021c7c48), (int) a, 0x11, (void *) buf, b, b, 0, 0, 0, -1);
    }
    return ret;
}
