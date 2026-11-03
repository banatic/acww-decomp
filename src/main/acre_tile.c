/* acre_tile: 24 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204f564 @ 0x0204f564, 0x44 bytes, Thumb
 * func_0204f538 @ 0x0204f538, 0x2a bytes, Thumb
 * func_0204f490 @ 0x0204f490, 0xa6 bytes, Thumb
 * func_0204f3e4 @ 0x0204f3e4, 0xac bytes, Thumb
 * func_0204f3a4 @ 0x0204f3a4, 0x3e bytes, Thumb
 * func_0204f380 @ 0x0204f380, 0x22 bytes, Thumb
 * func_0204f340 @ 0x0204f340, 0x3e bytes, Thumb
 * func_0204f31c @ 0x0204f31c, 0x22 bytes, Thumb
 * func_0204f2b8 @ 0x0204f2b8, 0x64 bytes, Thumb
 * func_0204f294 @ 0x0204f294, 0x22 bytes, Thumb
 * func_0204f260 @ 0x0204f260, 0x32 bytes, Thumb
 * func_0204ef74 @ 0x0204ef74, 0x2ec bytes, Thumb
 * func_0204ef24 @ 0x0204ef24, 0x50 bytes, Thumb
 * func_0204eea4 @ 0x0204eea4, 0x80 bytes, Thumb
 * func_0204ee7c @ 0x0204ee7c, 0x28 bytes, Thumb
 * func_0204ee48 @ 0x0204ee48, 0x34 bytes, Thumb
 * func_0204ee20 @ 0x0204ee20, 0x28 bytes, Thumb
 * func_0204edf8 @ 0x0204edf8, 0x28 bytes, Thumb
 * func_0204edd0 @ 0x0204edd0, 0x28 bytes, Thumb
 * func_0204eda8 @ 0x0204eda8, 0x28 bytes, Thumb
 * func_0204ed80 @ 0x0204ed80, 0x28 bytes, Thumb
 * func_0204ed58 @ 0x0204ed58, 0x28 bytes, Thumb
 * func_0204ed30 @ 0x0204ed30, 0x28 bytes, Thumb
 * func_0204ed08 @ 0x0204ed08, 0x28 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0204f564 {
    char *base;
    unsigned int width;
    unsigned int height;
};

typedef struct {
    unsigned char pad_00[0x28];
} Cell;

typedef struct {
    int w, h;
} Size;

typedef struct {
    Cell *cells;
    Size size;
} Grid;

typedef struct {
    void *data;
    unsigned int width;
    unsigned int height;
} SInfo;

typedef struct CollisionMap {
    unsigned char *data;
    unsigned int width;
    unsigned int height;
} CollisionMap;

typedef struct {
    unsigned char pad_00[0x1c];
    int unk_1C;
} Func0204ee7c_Struct;

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
} UnkStruct_0204edf8;

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
} UnkStruct_0204ed80;

extern int func_02037e44(void *ptr, int a, int b, int c, unsigned char d);
extern int func_02037d80(Cell *c, int a);
extern int func_02037da8(Cell *c, int a, int b, int c2, int d, int e);
extern int func_02037d64(Cell *c, int a);
extern int func_02037d48(void *ptr, int a, int b);
extern int func_02037d2c(void *ptr, int a, int b);
extern void func_0204f828(unsigned int *p0, unsigned int *p1, unsigned int p2);
extern u16 *func_0204f5e0(void *b, int cx, int cy, int ox, int oy, int layer);
extern int func_0204bd08(u16 *p);
extern int func_0204bcdc(u16 *p);
extern void func_0203a76c(u16 v);
extern void *func_020b3b50(u16 *o);
extern unsigned int func_020b3eb8(void *l);
extern int func_020b3e08(void *l, int *a, int *b, unsigned int k);
extern unsigned int func_020b3f2c(void *l);
extern int func_020b3e58(void *l, int *a, int *b, unsigned int k);
extern int func_02073d90(void *p);
extern int func_0204bb54(u16 *p);
extern int func_0204bb2c(u16 *p);
extern int func_020b0650(u8 *base, unsigned int idx);
extern int func_0204bc64(u16 *p);
extern int func_0204ba94(u16 *p);
extern int func_0204b5ac(u16 *p);
extern void *data_020ccf94;
extern u8 data_021f3b56[];
extern void func_02030e4c(int arg);
extern int func_02031b38(int a, int b);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02031af0(int, int);
extern int func_02031b14(int, int);
extern int func_02031a74(int, int);
extern int func_02031acc(int, int);
extern int func_02031aa0(int a, int b);
extern int func_02031a08(int, int);
extern void func_0204f818(int *p1, int *p2, int p3);
extern int func_02030a18(int, int);

int func_0204f564(struct UnkStruct_0204f564 *self, int a, unsigned x, unsigned y, int b, int c, unsigned char d)
{
    unsigned w;
    char *ptr;
    int ret;

    w = self->width;
    if (x < w && y < self->height && self->base != 0) {
        ptr = self->base + (x + y * w) * 0x28;
    } else {
        ptr = 0;
    }
    ret = 0;
    if (ptr) {
        ret = func_02037e44(ptr, a, b, c, d);
    }
    return ret;
}

int func_0204f538(int a, int b, int c, int d, unsigned char e)
{
    int c_high = c >> 4;
    int d_high = d >> 4;
    int c_low = c - (c_high << 4);
    int d_low = d - (d_high << 4);
    return func_0204f564((struct UnkStruct_0204f564 *) a, b, c_high, d_high, c_low, d_low, e);
}

int func_0204f490(Grid *g, int *outX, int *outY, int p3, int p4, int p5, int p6, int p7, int p8)
{
    Size *sz = &g->size;
    int w = sz->w;
    int h = sz->h;
    int x, y;
    Cell *cell;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if ((unsigned int) x < (unsigned int) g->size.w && (unsigned int) y < (unsigned int) g->size.h && g->cells != 0) {
                cell = &g->cells[y * g->size.w + x];
            } else {
                cell = 0;
            }
            if (cell != 0 && func_02037d80(cell, p7) != 0 && func_02037da8(cell, p3, p4, p5, p6, p8) != 0) {
                *outX = x;
                *outY = y;
                return 1;
            }
        }
    }
    return 0;
}

int func_0204f3e4(Grid *g, int *outX, int *outY, int p3, int p4, int p5, int p6, int p7, int p8)
{
    Size *sz = &g->size;
    int w = sz->w;
    int h = sz->h;
    int x, y;
    Cell *cell;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if ((unsigned int) x < (unsigned int) g->size.w && (unsigned int) y < (unsigned int) g->size.h && g->cells != 0) {
                cell = &g->cells[y * g->size.w + x];
            } else {
                cell = 0;
            }
            if (cell != 0 && (!p7 || func_02037d64(cell, p7) != 0) && func_02037da8(cell, p3, p4, p5, p6, p8) != 0) {
                *outX = x;
                *outY = y;
                return 1;
            }
        }
    }
    return 0;
}

int func_0204f3a4(SInfo *s, unsigned int x, unsigned int y, int arg3, int arg4)
{
    void *ptr;
    int result;

    if (x < s->width && y < s->height && s->data != 0) {
        ptr = (char *) s->data + (x + y * s->width) * 0x28;
    } else {
        ptr = 0;
    }

    result = 0;
    if (ptr != 0) {
        result = func_02037d48(ptr, arg3, arg4);
    }

    return result;
}

void func_0204f380(int a, int b, int c)
{
    int b_hi = b >> 4;
    int c_hi = c >> 4;
    int c_lo = c - (c_hi << 4);
    func_0204f3a4((SInfo *) a, b_hi, c_hi, b - (b_hi << 4), c_lo);
}

int func_0204f340(SInfo *s, unsigned int x, unsigned int y, int arg3, int arg4)
{
    void *ptr;
    int result;

    if (x < s->width && y < s->height && s->data != 0) {
        ptr = (char *) s->data + (x + y * s->width) * 0x28;
    } else {
        ptr = 0;
    }

    result = 0;
    if (ptr != 0) {
        result = func_02037d2c(ptr, arg3, arg4);
    }

    return result;
}

int func_0204f31c(int a, int b, int c)
{
    int q1;
    int q2;
    int r1;
    int r2;
    q1 = b >> 4;
    q2 = c >> 4;
    r2 = c - (q2 << 4);
    r1 = b - (q1 << 4);
    return func_0204f340((SInfo *) a, q1, q2, r1, r2);
}

int func_0204f2b8(CollisionMap *map, unsigned int qx, unsigned int qy, unsigned int rx, unsigned int ry)
{
    unsigned char *tile;
    unsigned short *table;
    int result;
    unsigned short bits;
    int mask;

    if (qx < map->width && qy < map->height && map->data != 0) {
        tile = map->data + (qx + qy * map->width) * 0x28;
    } else {
        tile = 0;
    }

    result = 0;
    if (tile == 0) {
        return result;
    }
    table = (unsigned short *) *(unsigned int *) (tile + 0x24);
    if (table == 0) {
        return result;
    }

    if (rx < 0x10 && ry < 0x10) {
        result = 1;
    }
    if (result != 0) {
        if (rx < 0x10) {
            bits = table[ry];
            mask = 1 << rx;
            if ((bits & mask) != 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

int func_0204f294(int a, int x, int y)
{
    int qx;
    int qy;
    int rx;
    int ry;

    qx = x >> 4;
    qy = y >> 4;
    ry = y - (qy << 4);
    rx = x - (qx << 4);

    return func_0204f2b8((CollisionMap *) a, qx, qy, rx, ry);
}

int func_0204f260(unsigned int a, unsigned int b)
{
    unsigned int arr[4];

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    func_0204f828(&arr[0], &arr[2], b);
    return func_0204f2b8((CollisionMap *) a, arr[0], arr[1], arr[2], arr[3]);
}

int func_0204ef74(void *grid, u16 *item1, u16 *item2, u16 *item3, volatile int x, volatile int y)
{
    int result;
    void *list = 0;
    unsigned int n;
    unsigned int n2;
    int i, h, g, f, e, d, c, b, a;
    int ty2;
    int px;
    int py;
    void *gp;
    int ty;
    unsigned int j;
    u16 *t3;
    int cx, cy;
    int xl, yl;
    unsigned int k;
    int tx, tx2;
    u16 *tile;
    u16 *t2;
    int ok;
    u16 id;
    int m;
    unsigned int t;
    int cx2, cy2, cx3, cy3;
    u16 buf[3];
    int ox, oy;

    result = 0;
    xl = x;
    yl = y;
    cx = xl >> 4;
    cy = yl >> 4;
    tile = func_0204f5e0(grid, cx, cy, xl - (cx << 4), yl - (cy << 4), 0);
    if (tile != 0) {
        buf[0] = *tile;
        if (func_0204bd08(&buf[0]) != 0 || func_0204bcdc(&buf[0]) != 0) {
            func_0203a76c(buf[0]);
        }
    }
    ok = 0;
    id = *item2;
    if (id >= 0x5000 && id <= 0x5021) {
        ok = 1;
    }
    if (ok != 0) {
        list = func_020b3b50(item2);
    }
    if (list != 0) {
        n = func_020b3eb8(list);
        k = 0;
        px = x;
        py = y;
        gp = data_020ccf94;
        for (; k < n; k++) {
            if (func_020b3e08(list, &ox, &oy, k) != 0) {
                tx = px + ox;
                ty = py + oy;
                cx2 = tx >> 4;
                cy2 = ty >> 4;
                t2 = func_0204f5e0(grid, cx2, cy2, tx - (cx2 << 4), ty - (cy2 << 4), 0);
                if (t2 != 0) {
                    if (func_0204bcdc(t2) != 0 || func_0204bd08(t2) != 0) {
                        if (func_02073d90(gp) == 0) {
                            func_0203a76c(*t2);
                        }
                    } else if (func_0204bb54(t2) != 0) {
                        func_020b0650(data_021f3b56, func_0204bb2c(t2));
                    }
                }
                func_0204f538((int) grid, (int) item3, tx, ty, 0);
                func_0204f31c((int) grid, tx, ty);
            }
        }
        func_0204f538((int) grid, (int) item1, x, y, 0);
        if (func_0204bcdc(item3) != 0) {
            buf[2] = 0xf030;
            m = func_0204bc64(item3) == func_0204bc64(&buf[2]);
        } else {
            m = *item3 == 0xf030;
        }
        if (m != 0) {
            n2 = func_020b3f2c(list);
            j = 0;
            for (; j < n2; j++) {
                if (func_020b3e58(list, &ox, &oy, j) != 0) {
                    tx2 = px + ox;
                    ty2 = py + oy;
                    cx3 = tx2 >> 4;
                    cy3 = ty2 >> 4;
                    t3 = func_0204f5e0(grid, cx3, cy3, tx2 - (cx3 << 4), ty2 - (cy3 << 4), 0);
                    if (t3 != 0) {
                        i = 1;
                        h = 1;
                        g = 1;
                        f = 1;
                        e = 1;
                        d = 1;
                        c = 1;
                        b = 1;
                        a = 0;
                        t = *t3;
                        if (t >= 0x26 && t <= 0x2a) {
                            a = 1;
                        }
                        if (a == 0) {
                            if (t < 0x5d || t > 0x61) {
                                b = 0;
                            }
                        }
                        if (b == 0) {
                            if (t < 0x2f || t > 0x56) {
                                c = 0;
                            }
                        }
                        if (c == 0) {
                            if (t < 0x57 || t > 0x5b) {
                                d = 0;
                            }
                        }
                        if (d == 0) {
                            if (t < 0x66 || t > 0x68) {
                                e = 0;
                            }
                        }
                        if (e == 0) {
                            if (t != 0x69) {
                                f = 0;
                            }
                        }
                        if (f == 0) {
                            if (t < 0x6a || t > 0x6c) {
                                g = 0;
                            }
                        }
                        if (g == 0) {
                            if (t != 0x6d) {
                                h = 0;
                            }
                        }
                        if (h == 0) {
                            if (t < 0xc8 || t > 0xcf) {
                                i = 0;
                            }
                        }
                        if (i == 0 || func_0204ba94(t3) != 0) {
                            if (func_0204b5ac(t3) == -1) {
                                continue;
                            }
                        }
                        buf[1] = 0xfff1;
                        func_0204f538((int) grid, (int) (&buf[1]), tx2, ty2, 0);
                    }
                }
            }
        }
        result = 1;
    }
    return result;
}

int func_0204ef24(int a, const unsigned short *p, int c, int d)
{
    unsigned short local;
    int result;
    int flag;
    unsigned short v;

    result = 0;
    flag = result;
    v = *p;

    if (v >= 0x5000 && v <= 0x5021) {
        flag = 1;
    }

    if (flag) {
        local = 0xf030;
        result = func_0204ef74((void *) a, (u16 *) p, (u16 *) p, (u16 *) (&local), c, d);
    }
    return result;
}

int func_0204eea4(void *p0, int x, int y, unsigned short *src)
{
    unsigned short *c;
    unsigned short v[2];
    int ret;
    int ok;
    int qx, qy;

    qx = x >> 4;
    qy = y >> 4;
    c = (unsigned short *) func_0204f5e0(p0, qx, qy, x - (qx << 4), y - (qy << 4), 0);
    ret = 0;
    if (c == 0) {
        goto end;
    }
    ok = ret;
    if (*c >= 0x5000 && *c <= 0x5021) {
        ok = 1;
    }
    if (ok == 0) {
        goto end;
    }
    v[0] = 0xfff1;
    if (src != 0) {
        v[0] = *src;
    }
    v[1] = 0xfff1;
    ret = func_0204ef74(p0, (u16 *) (&v[0]), (u16 *) c, (u16 *) (&v[1]), x, y);
end:
    return ret;
}

int func_0204ee7c(Func0204ee7c_Struct *obj, int a, int b)
{
    int result;
    func_02030e4c(obj->unk_1C);
    result = func_02031b38(a, b);
    func_02030e4c(0);
    return result;
}

int func_0204ee48(int a, int b, int c, int d, int e)
{
    int out1 = 0;
    int out2 = 0;

    func_0204f800(&out1, &out2, b, c, d, e);
    return func_0204ee7c((Func0204ee7c_Struct *) a, out1, out2);
}

int func_0204ee20(int a, int b, int c)
{
    int e;

    func_02030e4c(*(int *) (a + 0x1c));
    e = func_02031af0(b, c);
    func_02030e4c(0);
    return e;
}

int func_0204edf8(UnkStruct_0204edf8 *a, int b, int c)
{
    int result;
    func_02030e4c(a->unk_1C);
    result = func_02031b14(b, c);
    func_02030e4c(0);
    return result;
}

int func_0204edd0(int arg0, int arg1, int arg2)
{
    int local_4;
    int result;

    result = ((int) (func_02030e4c(*(int *) (arg0 + 0x1c)), *(int *) (arg0 + 0x1c)));
    result = func_02031a74(arg1, arg2);
    func_02030e4c(0);
    return result;
}

int func_0204eda8(int a1, int a2, int a3)
{
    int v2;

    func_02030e4c(*(int *) (a1 + 0x1c));
    v2 = func_02031acc(a2, a3);
    func_02030e4c(0);
    return v2;
}

int func_0204ed80(UnkStruct_0204ed80 *a, int b, int c)
{
    int ret;
    func_02030e4c(a->unk_1C);
    ret = func_02031aa0(b, c);
    func_02030e4c(0);
    return ret;
}

int func_0204ed58(int a1, int a2, int a3)
{
    int v2;

    func_02030e4c(*(int *) (a1 + 0x1c));
    v2 = func_02031a08(a2, a3);
    func_02030e4c(0);
    return v2;
}

int func_0204ed30(int a, int b)
{
    int x = 0;
    int y = 0;
    func_0204f818(&x, &y, b);
    return func_0204ed58(a, x, y);
}

int func_0204ed08(int a, int b, int c)
{
    int e;

    func_02030e4c(*(int *) (a + 0x1c));
    e = func_02030a18(b, c);
    func_02030e4c(0);
    return e;
}
