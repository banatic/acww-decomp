/* design: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02071d8c @ 0x02071d8c, 0x170 bytes, Thumb
 * func_02071d60 @ 0x02071d60, 0x2c bytes, Thumb
 * func_02071aa8 @ 0x02071aa8, 0x2b8 bytes, Thumb
 * func_0207172c @ 0x0207172c, 0x37c bytes, Thumb
 * func_020716f4 @ 0x020716f4, 0x38 bytes, Thumb
 * func_020716e8 @ 0x020716e8, 0xc bytes, Thumb
 * func_020716dc @ 0x020716dc, 0xc bytes, Thumb
 * func_020716d0 @ 0x020716d0, 0xc bytes, Thumb
 * func_020716c4 @ 0x020716c4, 0xc bytes, Thumb
 * func_020716b4 @ 0x020716b4, 0x10 bytes, Thumb
 * func_0207169c @ 0x0207169c, 0x18 bytes, Thumb
 * func_02071678 @ 0x02071678, 0x24 bytes, Thumb
 * func_02071658 @ 0x02071658, 0x20 bytes, Thumb
 * func_02071648 @ 0x02071648, 0x10 bytes, Thumb
 * func_02071628 @ 0x02071628, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 w[0x80];
} Head;

typedef struct {
    u16 h[6];
} UnkStruct_02071d8c;

typedef struct {
    u16 h[10];
} H10;

typedef struct {
    Head head; // 0x000
    u16 unk_200;
    UnkStruct_02071d8c unk_202;
    u16 unk_20E;
    UnkStruct_02071d8c unk_210;
    s8 unk_21C;
    u8 unk_21D;
    H10 unk_21E;
    u8 unk_232;
} Rec;

typedef struct {
    u32 a : 4;
    u32 b : 10;
    u32 c : 4;
    u32 d : 10;
    u32 e : 1;
    u32 f : 3;
} Packed;

struct UnkStruct_02071d60 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    u32 w[0x80];
} Big;

typedef struct {
    u16 v[6];
} UnkStruct_02071aa8;

typedef struct {
    u16 v[10];
} A10;

typedef struct {
    Big big;
    u16 unk_200;
    UnkStruct_02071aa8 unk_202;
    u16 unk_20E;
    UnkStruct_02071aa8 unk_210;
    char unk_21C;
    u8 unk_21D;
    A10 unk_21E;
    u8 unk_232;
} UnkStruct_02071aa8_2;

// The division is signed, so it calls the division helper.

typedef struct World {
    void *unk_00;
    int unk_04;
    int unk_08;
} World;

typedef struct UnkStruct_0207172c {
    u16 id;
} UnkStruct_0207172c;

extern Rec *func_02071604(int, int);
extern int func_020720ac(int, int);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern char *func_02072dbc(UnkStruct_02071aa8_2 *p);
extern void __register_global_object(void *, void *, void *);
extern void *func_02072da4(void *);
extern int data_021d0474;
extern UnkStruct_02071aa8_2 data_021d05cc;
extern int data_021d0498;
extern int data_021d0488;
extern u16 data_021d046c;
extern int data_021d048c;
extern int data_021ebcd4;
extern void func_020051b0(void *);
extern World *func_0204e414(void);
extern UnkStruct_0207172c *func_02037e0c(void *t, int a, int b, int c);
extern int func_02037e44(void *t, u16 *p, int a, int b, int c);
extern World *func_0204df30(int i);
extern void *func_02060ee0(void *g, int i);
extern UnkStruct_0207172c *func_02061204(void *e, int k);
extern void func_020611bc(void *e, u16 *p, int k);
extern UnkStruct_0207172c *func_020611e8(void *e, int k);
extern void func_02061194(void *e, u16 *p, int k);
extern int func_020984fc(int);
extern int func_020996b8(void *object);
extern int func_02072bd0(int, int);
extern unsigned int func_02072a48(unsigned int a, unsigned int b);
extern unsigned char data_021ed278[];
extern void *func_020b374c(void *ptr);
extern void *func_020b3848(void *record);
extern unsigned char data_021f34b0[];
extern int func_0207cec0(void *ptr, int param);
extern int func_02081500(int arg);
extern char data_021e5a2c[];
extern int func_02072824(void);
extern int func_02072830(int, int);
extern void *func_0207282c(void *record);
extern int data_021f3278;
extern void *func_02088220(void *record);
extern int func_020984e8(void);

int func_02071d60(int param);

int func_02071d8c(int a0, int a1, int a2, int a3, u8 flag)
{
    Packed t;
    int x, y;
    Rec *p, *q;

    x = func_02071d60(a0);
    y = func_02071d60(a2);
    if (y == 7) {
        return 0;
    }
    p = func_02071604(x, a1);
    q = func_02071604(y, a3);
    q->head = p->head;
    q->unk_200 = p->unk_200;
    q->unk_202 = p->unk_202;
    q->unk_20E = p->unk_20E;
    q->unk_210 = p->unk_210;
    q->unk_21C = p->unk_21C;
    q->unk_21D = p->unk_21D;
    q->unk_21E = p->unk_21E;
    q->unk_232 = p->unk_232;
    func_020720ac(y, a3);
    if (flag != 0 && func_02073d90(data_020ccf94) != 0) {
        void *o;
        t.a = x;
        t.b = a1;
        t.c = y;
        t.d = a3;
        t.e = 0;
        t.f = 0;
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &t, 4);
        func_02073770(o, 0x15, 4);
    }
    return 1;
}

int func_02071d60(int param)
{
    struct UnkStruct_02071d60 *p = (*(struct UnkStruct_02071d60 * *) &data_020ccf94);
    if (func_02073d90((void *) p) && param == 9) {
        return p->unk_64;
    }
    return param;
}

int func_02071aa8(void *a0, int a1, void *a2, int a3, u8 a5)
{
    int k1;
    int k2;
    UnkStruct_02071aa8_2 *p1;
    UnkStruct_02071aa8_2 *p2;
    unsigned int u;
    void *h;

    k1 = func_02071d60((int) a0);
    k2 = func_02071d60((int) a2);
    if (k1 == 7 || k2 == 7) {
        return 0;
    }
    p1 = (UnkStruct_02071aa8_2 *) func_02071604(k1, a1);
    p2 = (UnkStruct_02071aa8_2 *) func_02071604(k2, a3);
    if ((data_021d0474 & 1) == 0) {
        func_02072dbc(&data_021d05cc);
        __register_global_object((void *) (&data_021d05cc), (((void *) func_02072da4)), (void *) (&data_021d0498));
        data_021d0474 |= 1;
    }

    data_021d05cc.big = p2->big;
    data_021d05cc.unk_200 = p2->unk_200;
    data_021d05cc.unk_202 = p2->unk_202;
    data_021d05cc.unk_20E = p2->unk_20E;
    data_021d05cc.unk_210 = p2->unk_210;
    data_021d05cc.unk_21C = p2->unk_21C;
    data_021d05cc.unk_21D = p2->unk_21D;
    data_021d05cc.unk_21E = p2->unk_21E;
    data_021d05cc.unk_232 = p2->unk_232;

    p2->big = p1->big;
    p2->unk_200 = p1->unk_200;
    p2->unk_202 = p1->unk_202;
    p2->unk_20E = p1->unk_20E;
    p2->unk_210 = p1->unk_210;
    p2->unk_21C = p1->unk_21C;
    p2->unk_21D = p1->unk_21D;
    p2->unk_21E = p1->unk_21E;
    p2->unk_232 = p1->unk_232;

    p1->big = data_021d05cc.big;
    p1->unk_200 = data_021d05cc.unk_200;
    p1->unk_202 = data_021d05cc.unk_202;
    p1->unk_20E = data_021d05cc.unk_20E;
    p1->unk_210 = data_021d05cc.unk_210;
    p1->unk_21C = data_021d05cc.unk_21C;
    p1->unk_21D = data_021d05cc.unk_21D;
    p1->unk_21E = data_021d05cc.unk_21E;
    p1->unk_232 = data_021d05cc.unk_232;

    func_020720ac(k1, a1);
    func_020720ac(k2, a3);
    if (a5 != 0 && func_02073d90(data_020ccf94) != 0) {
        k1 &= 0xf;
        u = (u & ~0xf) | k1;
        a1 &= 0x3ff;
        u = (u & 0xffffc00f) | (a1 << 4);
        k2 &= 0xf;
        u = (u & 0xfffc3fff) | (k2 << 14);
        a3 &= 0x3ff;
        u = (u & 0xf003ffff) | (a3 << 18);
        u = u | 0x10000000;
        u = u & 0x1fffffff;
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, (void *) (&u), 4);
        func_02073770(h, 0x15, 4);
    }
    return 1;
}

static __inline void *tile_at(World *p, int x, int y)
{
    void *t;
    if ((unsigned int) x < (unsigned int) p->unk_04 && (unsigned int) y < (unsigned int) p->unk_08 && p->unk_00 != 0) {
        t = (void *) ((char *) p->unk_00 + 0x28 * (x + y * p->unk_04));
    } else {
        t = (void *) 0;
    }
    return t;
}

void func_0207172c(int arg)
{
    // DECLS
    int a;
    int b;
    int i;
    void *tile;
    World *w;
    void *q;
    World *p;
    void *e;
    UnkStruct_0207172c *obj;
    unsigned int f;
    int y;
    int x;
    unsigned int id;
    int v;
    int y2;
    int x2;
    // ENDDECLS
    u16 buf[4];

    if ((data_021d0488 & 1) == 0) {
        data_021d046c = 0xfff1;
        __register_global_object((void *) (&data_021d046c), (((void *) func_020051b0)), (void *) (&data_021d048c));
        data_021d0488 |= 1;
    }
    w = func_0204e414();
    if (w != 0) {
        for (y = 1; y < w->unk_08 - 1; y++) {
            for (x = 1; x < w->unk_04 - 1; x++) {
                if ((unsigned int) x < (unsigned int) w->unk_04 && (unsigned int) y < (unsigned int) w->unk_08 &&
                    w->unk_00 != 0) {
                    tile = (void *) ((char *) w->unk_00 + 0x28 * (x + y * w->unk_04));
                } else {
                    tile = (void *) 0;
                }
                if (tile == 0) {
                    continue;
                }
                for (a = 0; a < 0x10; a++) {
                    for (b = 0; b < 0x10; b++) {
                        obj = func_02037e0c(tile, b, a, 0);
                        if (obj == 0) {
                            continue;
                        }
                        f = 0;
                        id = obj->id;
                        if (id >= 0xa7 && id <= 0xc6) {
                            f = 1;
                        }
                        if (f == 0) {
                            continue;
                        }
                        if (arg == ((int) id - 0xa7) / 8) {
                            func_02037e44(tile, &data_021d046c, b, a, 0);
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        p = func_0204df30(i);
        if (p != 0) {
            q = tile_at(p, 0, 0);
            if (q != 0) {
                for (y2 = 0; y2 < 0x10; y2++) {
                    for (x2 = 0; x2 < 0x10; x2++) {
                        obj = func_02037e0c(q, x2, y2, 0);
                        if (obj == 0) {
                            continue;
                        }
                        f = 0;
                        id = obj->id;
                        if (id >= 0x3d84 && id <= 0x3e03) {
                            f = 1;
                        }
                        if (f != 0) {
                            v = (id >= 0x3d84 && id <= 0x3e03) ? (int) (id - 0x3d84) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x3ea4 && id <= 0x3f23) {
                            v = (id >= 0x3ea4 && id <= 0x3f23) ? (int) (id - 0x3ea4) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x3f24 && id <= 0x3fa3) {
                            v = (id >= 0x3f24 && id <= 0x3fa3) ? (int) (id - 0x3f24) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x4224 && id <= 0x42a3) {
                            v = (id >= 0x4224 && id <= 0x42a3) ? (int) (id - 0x4224) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        }
                    }
                }
            }
        }
        e = func_02060ee0(&data_021ebcd4, i);
        if (e == 0) {
            continue;
        }
        obj = func_02061204(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        if (f != 0) {
            obj = func_02061204(e, 0);
            f = 0;
            id = obj->id;
            if (id >= 0x1188 && id <= 0x11a7) {
                f = 1;
            }
            v = f ? (int) (id - 0x1188) : -1;
            if (((v >> 3) & 3) == arg) {
                buf[0] = 0x113e;
                func_020611bc(e, &buf[0], 0);
            }
        }
        obj = func_020611e8(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        if (f == 0) {
            continue;
        }
        obj = func_020611e8(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        v = f ? (int) (id - 0x1188) : -1;
        if (((v >> 3) & 3) == arg) {
            buf[1] = 0x1182;
            func_02061194(e, &buf[1], 0);
        }
    }
}

int func_020716f4(int arg0, int arg1)
{
    int forwarded_value;

    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) && (forwarded_value = (int) func_020984fc(arg0))) {
        return func_02072bd0(func_020996b8((void *) forwarded_value), arg1);
    }
    return 0;
}

int func_020716e8(int a)
{
    return func_020716f4(0, a);
}

int func_020716dc(int arg)
{
    return func_020716f4(1, arg);
}

int func_020716d0(int r0)
{
    return func_020716f4(2, r0);
}

int func_020716c4(int r0)
{
    return func_020716f4(3, r0);
}

int func_020716b4(int selector)
{
    return (int) func_02072a48((unsigned int) data_021ed278, (unsigned int) selector);
}

int func_0207169c(int selector)
{
    return (int) func_020b3848(func_020b374c((void *) data_021f34b0));
}

int func_02071678(int param)
{
    int ret;

    ret = func_0207cec0(data_021e5a2c, param);
    if (ret != 0) {
        return func_02081500(ret);
    }
    return 0;
}

int func_02071658(int arg)
{
    int ret1 = func_02072824();
    func_02072830(ret1, arg);
    return (int) func_0207282c((void *) ret1);
}

int func_02071648(int selector)
{
    return (int) func_02088220(&data_021f3278);
}

int func_02071628(int arg)
{
    int a = func_020984e8();
    if (a != 0) {
        return func_02072bd0(func_020996b8((void *) a), arg);
    }
    return 0;
}
