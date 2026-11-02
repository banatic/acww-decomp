/* town_map_markers: 13 functions, module ov117
 * mwccarm 1.2/base -O4,s
 * func_ov117_0229a2f0 @ 0x0229a2f0, 0x22 bytes, Thumb
 * func_ov117_0229a2ec @ 0x0229a2ec, 0x2 bytes, Thumb
 * func_ov117_0229a2c8 @ 0x0229a2c8, 0x22 bytes, Thumb
 * func_ov117_0229a2a4 @ 0x0229a2a4, 0x24 bytes, Thumb
 * func_ov117_0229a280 @ 0x0229a280, 0x24 bytes, Thumb
 * func_ov117_0229a26c @ 0x0229a26c, 0x12 bytes, Thumb
 * func_ov117_0229a194 @ 0x0229a194, 0xd8 bytes, Thumb
 * func_ov117_0229a10c @ 0x0229a10c, 0x88 bytes, Thumb
 * func_ov117_0229a034 @ 0x0229a034, 0xd8 bytes, Thumb
 * func_ov117_02299f8c @ 0x02299f8c, 0xa8 bytes, Thumb
 * func_ov117_02299ee8 @ 0x02299ee8, 0xa4 bytes, Thumb
 * func_ov117_02299e44 @ 0x02299e44, 0xa4 bytes, Thumb
 * func_ov117_02299d9c @ 0x02299d9c, 0xa8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a2f0 {
    short a;
    short b;
    char c;
};

struct UnkStruct_0229a2c8 {
    short a;
    short b;
    char c;
};

struct entry {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
};

struct UnkStruct_0229a280 {
    short a;
    short b;
    char c;
};

struct UnkStruct_0229a26c {
    unsigned char pad_00[4];
    unsigned char b;
    unsigned char c;
};

typedef struct Map {
    void *tiles;
    unsigned int width;
    unsigned int height;
} Map;

extern void func_02030e4c(int);
extern Map *func_0204e414(void);
extern int func_02037d9c(void *);
extern int func_02031498(int *, int *, int, int);
extern void *func_0207cec0(void *base, int idx);
extern unsigned char *func_020800d0(void *p);
extern int func_02081f80(void *p);
extern unsigned short func_0204bbbc(int i);
extern int func_020b3b50(unsigned short *h);
extern void func_020b3c58(int flag, int *v0, int *v1, int *v2, int *v3);
extern unsigned char data_021e5a2c[];
extern unsigned int func_02060e78(void *);
extern int func_0204f3e4(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f800(int *, int *, int, int, int, int);
extern int func_0204f5e0(void *, int, int, int, int, int);
extern int data_021ebcd4;

void func_ov117_0229a2c8(struct UnkStruct_0229a2c8 *arr);

struct UnkStruct_0229a2f0 *func_ov117_0229a2f0(struct UnkStruct_0229a2f0 *arr)
{
    struct UnkStruct_0229a2f0 *p = arr;
    do {
        p->a = 0;
        p->b = 0;
        p++;
    } while (p != arr + 17);
    func_ov117_0229a2c8((struct UnkStruct_0229a2c8 *) arr);
    return arr;
}

void func_ov117_0229a2ec(void *object) {}

void func_ov117_0229a2c8(struct UnkStruct_0229a2c8 *arr)
{
    unsigned int i;
    for (i = 0; i < 17; i++) {
        arr[i].a = -1;
        arr[i].b = -1;
        arr[i].c = 0;
    }
}

void func_ov117_0229a2a4(struct entry *arr, int idx, int v0, int v2, unsigned char v4)
{
    if (idx < 0x11) {
        arr[idx].unk_00 = v0;
        arr[idx].unk_02 = v2;
        arr[idx].unk_04 = v4;
    }
}

struct UnkStruct_0229a280 *func_ov117_0229a280(struct UnkStruct_0229a280 *arr, unsigned int i)
{
    if (i < 0x11) {
        if (arr[i].a != -1) {
            arr += i;
            if (arr->b != -1) {
                return arr;
            }
        }
        return 0;
    }
    return 0;
}

unsigned char func_ov117_0229a26c(struct UnkStruct_0229a26c *arr, unsigned int i)
{
    if (i < 17) {
        return arr[i].b;
    } else {
        return arr[0].b;
    }
}

void func_ov117_0229a194(void *arg)
{
    Map *map;
    int row, col;
    int bx, by;
    int mode, count;
    void *tile;

    func_02030e4c(1);
    count = 0;
    map = func_0204e414();

    for (row = 1; row < 5; row++) {
        for (col = 1; col < 5; col++) {
            if (col < map->width && row < map->height && map->tiles != 0) {
                tile = (char *) map->tiles + 0x28 * (col + row * map->width);
            } else {
                tile = 0;
            }

            if ((func_02037d9c(tile) & 4) != 0) {
                mode = func_02031498(&bx, &by, col, row);

                if (mode != 4) {
                    bx *= 2;
                    by *= 2;
                    bx += 1;
                    by += 1;

                    switch (mode) {
                        case 0:
                            bx += 1;
                            by += 3;
                            break;
                        case 1:
                            bx += 3;
                            by += 1;
                            break;
                        case 2:
                            by += 4;
                            break;
                        case 3:
                            bx += 2;
                            by += 4;
                            break;
                    }

                    func_ov117_0229a2a4((struct entry *) arg, count, bx, by, (unsigned char) ((unsigned char) mode));
                    count++;
                }
            }
        }
    }

    func_02030e4c(0);
}

void func_ov117_0229a10c(void *param)
{
    int i;
    int x, y;
    int d = 0;
    void *obj;
    unsigned short h;
    int v0, v1, v2, v3;
    int flag;
    unsigned char b0, b1;
    for (i = 0; i < 8; i++) {
        obj = func_0207cec0((void *) data_021e5a2c, i);
        if (func_02081f80(func_020800d0(obj))) {
            h = func_0204bbbc(i);
            b0 = func_020800d0(obj)[0];
            b1 = func_020800d0(obj)[1];
            x = b0 * 2;
            y = b1 * 2;
            x += 1;
            y += 1;
            flag = func_020b3b50(&h);
            if (flag) {
                func_020b3c58(flag, &v0, &v1, &v2, &v3);
                x += (v0 >> 11);
                y += (v1 >> 11);
            }
            func_ov117_0229a2a4((struct entry *) param, i + 3, x, y, (unsigned char) d);
        }
    }
}

/* FAKEMATCH: the empty if keeps the y load before the x shift; the plain copies shift x first */

void func_ov117_0229a034(int param)
{
    u16 ids[2];
    int x;
    int y;
    int v0;
    int v1;
    int v2;
    int v3;
    int w0;
    int w1;
    int w2;
    int w3;
    void *p;
    int sx;
    int sy;
    int rx;
    int ry;
    int ret;
    int ret2;
    p = (void *) func_0204e414();
    if (p == 0) {
        return;
    }
    func_02060e78(&data_021ebcd4);
    ids[0] = 0x5014;
    ids[1] = 0x501a;
    if (func_0204f3e4(p, &v0, &v1, &v2, &v3, ids, &ids[1], 1, 0) == 0) {
        return;
    }
    func_0204f800(&x, &y, v0, v1, v2, v3);
    {
        int xv = x;
        int yv = y;
        sx = xv >> 4;
        sy = yv >> 4;
        if (((!param) && (!param)) && (!param)) {
        }
        rx = xv - (sx << 4);
        ry = yv - (sy << 4);
    }
    ret = func_0204f5e0(p, sx, sy, rx, ry, 0);
    x = x * 2;
    y = y * 2;
    x += 1;
    y += 1;
    ret2 = func_020b3b50((unsigned short *) ret);
    if (ret2 != 0) {
        func_020b3c58(ret2, &w0, &w1, &w2, &w3);
        x += w0 >> 11;
        y += w1 >> 11;
    }
    func_ov117_0229a2a4((struct entry *) param, 0xb, x, y, 0);
}

void func_ov117_02299f8c(void *param)
{
    short s;
    int x, y;
    int a, b, c, d;
    int e, f, g, h;
    void *hand;

    hand = (void *) func_0204e414();
    if (hand == 0) {
        return;
    }

    s = 0x5011;
    if (func_0204f3e4(hand, &a, &b, &c, &d, (u16 *) (&s), (u16 *) (&s), 0x800, 0) == 0) {
        return;
    }

    func_0204f800(&x, &y, a, b, c, d);

    x = x * 2;
    y = y * 2;
    x = x + 1;
    y = y + 1;

    hand = (void *) func_020b3b50((unsigned short *) (&s));
    if (hand != 0) {
        func_020b3c58((int) hand, &e, &f, &g, &h);
        x += e >> 11;
        y += f >> 11;
    }

    func_ov117_0229a2a4((struct entry *) param, 0xd, x, y, 0);
}

void func_ov117_02299ee8(void *self)
{
    u16 local_14;
    u32 local_18;
    u32 local_1c;
    u32 local_20;
    u32 local_24;
    u32 local_28;
    u32 local_2c;
    int local_30;
    int local_34;
    u32 local_38;
    u32 local_3c;
    int v;
    int ret3;

    v = (int) func_0204e414();
    if (v == 0) {
        return;
    }

    local_14 = 0x500b;
    if (!func_0204f3e4((void *) v, (int *) (&local_20), (int *) (&local_24), (int *) (&local_28), (int *) (&local_2c), (u16 *) (&local_14), (u16 *) (&local_14), 0, 0)) {
        return;
    }

    func_0204f800((int *) (&local_18), (int *) (&local_1c), (int) local_20, (int) local_24, (int) local_28, (int) local_2c);

    local_18 <<= 1;
    local_1c <<= 1;
    local_18 += 1;
    local_1c += 1;

    ret3 = func_020b3b50((unsigned short *) (&local_14));
    if (ret3 == 0) {
        goto skip;
    }

    func_020b3c58(ret3, (int *) (&local_30), (int *) (&local_34), (int *) (&local_38), (int *) (&local_3c));
    local_18 += local_30 >> 11;
    local_1c += local_34 >> 11;

skip:
    func_ov117_0229a2a4((struct entry *) self, 0x10, (int) local_18, (int) local_1c, 0);
}

void func_ov117_02299e44(void *self)
{
    unsigned short v14;
    int v18, v1c, v20, v24, v28, v2c;
    int v30, v34, v38, v3c;
    int ret1, ret2;

    ret1 = (int) func_0204e414();
    if (ret1 == 0) {
        return;
    }

    v14 = 0x500c;
    if (func_0204f3e4((void *) ret1, (int *) (&v20), (int *) (&v24), (int *) (&v28), (int *) (&v2c), (u16 *) (&v14), (u16 *) (&v14), 2, 0) == 0) {
        return;
    }

    func_0204f800(&v18, &v1c, v20, v24, v28, v2c);

    v18 = v18 << 1;
    v1c = v1c << 1;
    v18 += 1;
    v1c += 1;

    ret2 = func_020b3b50((unsigned short *) (&v14));
    if (ret2 != 0) {
        func_020b3c58(ret2, (int *) (&v30), (int *) (&v34), (int *) (&v38), (int *) (&v3c));
        v18 += v30 >> 11;
        v1c += v34 >> 11;
    }

    func_ov117_0229a2a4((struct entry *) self, 0xf, v18, v1c, 0);
}

void func_ov117_02299d9c(int arg)
{
    unsigned short h;
    int v18, v1c, v20, v24, v28, v2c, v30, v34, v38, v3c;
    int ret1;

    ret1 = (int) func_0204e414();
    if (ret1) {
        h = 0x5000;
        if (func_0204f3e4((void *) ret1, &v20, &v24, &v28, &v2c, (u16 *) (&h), (u16 *) (&h), 0x200, 0)) {
            func_0204f800(&v18, &v1c, v20, v24, v28, v2c);
            v18 <<= 1;
            v1c <<= 1;
            v18 += 1;
            v1c += 1;
            {
                int ret3 = func_020b3b50(&h);
                if (ret3) {
                    func_020b3c58(ret3, &v30, &v34, &v38, &v3c);
                    v18 += v30 >> 11;
                    v1c += v34 >> 11;
                }
            }
            func_ov117_0229a2a4((struct entry *) arg, 0xC, v18, v1c, 0);
        }
    }
}
