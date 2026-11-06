/* collision_map: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02030ddc @ 0x02030ddc, 0x70 bytes, Thumb
 * func_02030dcc @ 0x02030dcc, 0x10 bytes, Thumb
 * func_02030db8 @ 0x02030db8, 0x14 bytes, Thumb
 * func_02030d68 @ 0x02030d68, 0x50 bytes, Thumb
 * func_02030d48 @ 0x02030d48, 0x1e bytes, Thumb
 * func_02030c84 @ 0x02030c84, 0xc4 bytes, Thumb
 * func_02030c34 @ 0x02030c34, 0x50 bytes, Thumb
 * func_02030bc0 @ 0x02030bc0, 0x74 bytes, Thumb
 * func_02030bac @ 0x02030bac, 0x14 bytes, Thumb
 * func_02030b80 @ 0x02030b80, 0x2c bytes, Thumb
 * func_02030a18 @ 0x02030a18, 0x168 bytes, Thumb
 * func_02030920 @ 0x02030920, 0xf8 bytes, Thumb
 * func_020308e0 @ 0x020308e0, 0x3e bytes, Thumb
 * func_020308a4 @ 0x020308a4, 0x3c bytes, Thumb
 * func_02030890 @ 0x02030890, 0x14 bytes, Thumb
 * func_02030864 @ 0x02030864, 0x2c bytes, Thumb
 * func_02030818 @ 0x02030818, 0x4c bytes, Thumb
 * func_020307f8 @ 0x020307f8, 0x20 bytes, Thumb
 * func_02030738 @ 0x02030738, 0xc0 bytes, Thumb
 */

#include "types.h"

struct Elem {
    unsigned char pad_00[0x120];
    int unk_120;
    int unk_124;
    int unk_128;
    unsigned char pad_12C[0x130 - 0x128 - 4];
    unsigned char unk_130;
    unsigned char pad_131[0x138 - 0x130 - 1];
};

typedef struct {
    int pad_00;
    unsigned char *data;
} UnkStruct_02030d68;

typedef struct {
    int unk_00;
    unsigned char pad[0x138 - 4];
} RecA;

typedef struct {
    unsigned char pad[0x128];
    int unk_128;
    unsigned char pad_12C[0x138 - 0x12c];
} RecB;

typedef unsigned char RecC[0x138];

typedef struct {
    unsigned char unk_00;
    unsigned char pad[0x138 - 1];
} RecE;

typedef struct {
    int unk_00;
    int w1;
} CellT;

typedef struct {
    unsigned int x;
    unsigned int y;
} Pair;

struct UnkStruct_02030bc0 {
    Pair cells[6][6];
    unsigned int pad_120;
    unsigned int width;
    unsigned int height;
    unsigned int pad_12C;
    unsigned int pad_130;
    unsigned int pad_134;
};

typedef struct UnkStruct_02030a18 {
    u8 pad_00[6];
    short unk_06;
    u8 pad_08[0xc - 8];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 pad_10[0x1e - 0x10];
} UnkStruct_02030a18;

// keep holds the loaded value because v is reassigned by the fourth flag test.

typedef struct UnkStruct_02030920 {
    u8 pad_00[0xc];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 pad_10[0x1e - 0x10];
} UnkStruct_02030920;

struct UnkStruct_020308a4 {
    unsigned char pad_00[300];
    int unk_12C;
};

struct UnkStruct_02030864 {
    char header[300];
    int value;
};

typedef struct {
    char pad_00[0x12c];
    int unk_12C;
} UnkStruct_020307f8;

extern struct Elem data_021c31ec[];
extern void func_02030e4c(int);
extern void func_02034664(int *ptr);
extern int func_020346c4(int *, int, int);
extern unsigned int func_02031a08(int, int);
extern RecA data_021c3310[];
extern RecA data_021c3314[];
extern RecB data_021c31e8[];
extern RecE data_021c331c[];
extern void func_02034714(void *);
extern void func_0203242c(void *);
extern void func_020326b0(void *);
extern void func_020346fc(void *);
extern char data_021c3fe8[];
extern char data_021c49e8[];
extern char data_021c4c78[];
extern char data_021c4c79[];
extern char data_021c5124[];
extern struct UnkStruct_02030b80 {
    char pad_00[0x132];
    short unk_132;
    short unk_134;
} *data_020da1a8;
extern UnkStruct_02030a18 data_020c907c[];
extern u8 data_020c9082[];
extern u8 data_020c9088[];
extern u8 data_020c9089[];
extern u8 data_020c908a[];
extern u8 data_020c908b[];
extern u8 **func_01ffcb5c(int a, int b);
extern int func_01ffcb2c(int, int);
extern int func_0203160c(int);

void func_02030c34(int param);

int func_02030ddc(unsigned int a0, unsigned int a1, int a2, int a3)
{
    struct Elem *e = &data_021c31ec[a3];
    int result = 1;

    func_02030c34(a3);

    if (a0 <= 6) {
        e->unk_124 = (unsigned char) a0;
    } else {
        result = 0;
    }

    if (a1 <= 6) {
        e->unk_128 = (unsigned char) a1;
    } else {
        result = 0;
    }

    e->unk_120 = a2;
    e->unk_130 = 0;

    func_02030e4c(0);

    return result;
}

void func_02030dcc(void)
{
    func_02034664(((int *) data_021c5124));
}

int func_02030db8(int a, int b)
{
    return func_020346c4(((int *) data_021c5124), a, b);
}

void func_02030d68(int a, int b, int c)
{
    UnkStruct_02030d68 *ret = (UnkStruct_02030d68 *) func_01ffcb5c(a >> 4, b >> 4);
    if (ret) {
        int idx = (a & 0xf) + ((b & 0xf) << 4);
        unsigned char *p = ret->data + (idx >> 1);
        if (idx & 1) {
            *p &= ~0xf0;
            *p |= (c << 4);
        } else {
            *p &= ~0x0f;
            *p |= c;
        }
    }
}

void func_02030d48(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int t = func_02031a08(a, b) & ~c;
    func_02030d68(a, b, t);
}

int func_02030c84(int x, int y, int value, int idx)
{
    CellT *cell;
    int rows, cols, flag;
    unsigned char *colBase;
    unsigned char *gridBase;
    unsigned char *rowBase;
    CellT *c;

    if (x < 0) {
        goto fail;
    }
    if (y < 0) {
        goto fail;
    }
    if ((unsigned int) x >= (unsigned int) data_021c3310[idx].unk_00) {
        goto fail;
    }
    if ((unsigned int) y >= (unsigned int) data_021c3314[idx].unk_00) {
        goto fail;
    }

    cell = (CellT *) (((RecC *) data_021c31ec)[idx] + y * 0x30 + x * 8);
    goto have_cell;

fail:
    cell = 0;

have_cell:
    if (cell != 0) {
        cell->unk_00 = value;
        cell->w1 = value + 0x100;

        rows = data_021c3314[idx].unk_00 - 1;
        colBase = (unsigned char *) &data_021c31e8[idx];
        gridBase = ((RecC *) data_021c31ec)[idx];

        for (; rows >= 0; rows--) {
            cols = *(int *) (colBase + 0x128) - 1;
            rowBase = gridBase + rows * 0x30;

            for (; cols >= 0; cols--) {
                int occupied;
                c = (CellT *) (rowBase + cols * 8);
                occupied = (c->unk_00 != 0) && (c->w1 != 0);
                if (occupied == 0) {
                    flag = 0;
                    goto store;
                }
            }
        }
        flag = 1;

    store:
        data_021c331c[idx].unk_00 = (unsigned char) flag;
        return 1;
    }

    return 0;
}

void func_02030c34(int param)
{
    func_02034714(((char *) data_021c31ec) + 0x138 * param);
    *(int *) (data_021c3fe8 + 0x44) = 0;
    *(int *) (data_021c49e8 + 0x48) = 0;
    *(int *) (data_021c49e8 + 0x4c) = 0;
    func_0203242c(data_021c4c78);
    func_020326b0(data_021c4c79);
    func_020346fc(data_021c5124);
}

void func_02030bc0(int idx)
{
    struct UnkStruct_02030bc0 *d;
    int row, col;
    Pair *fallback;
    Pair *p;

    fallback = 0;
    d = &((struct UnkStruct_02030bc0 *) data_021c31ec)[idx];

    for (row = 0; row < d->height; row++) {
        for (col = 0; col < d->width; col++) {
            if (col >= 0 && row >= 0 && col < d->width && row < d->height) {
                p = &d->cells[row][col];
            } else {
                p = fallback;
            }
            if (p) {
                p->x = 0;
                p->y = 0;
            }
        }
    }
}

void func_02030bac(void *arg)
{
    func_02030bc0((int) arg);
    func_02030c34((int) arg);
}

void func_02030b80(short value)
{
    if (data_020da1a8->unk_134 != value) {
        data_020da1a8->unk_132 = data_020da1a8->unk_134;
        data_020da1a8->unk_134 = value;
    }
}

int func_02030a18(int x, int y)
{
    u8 **cellp;
    u8 *base;
    u8 *cell;
    int off;
    int v;
    int k;
    int a7;
    int a4;
    int a5;
    int a6;
    int t;
    unsigned int i;

    cellp = func_01ffcb5c(x >> 4, y >> 4);
    if (cellp == 0) {
        goto ret0b;
    }
    base = *cellp;
    x = x & 0xf;
    y = y & 0xf;
    off = x + (y << 4);
    cell = base + off;
    v = base[off];
    if (v < 0x7c) {
        k = *(short *) (data_020c9082 + v * 0x1e);
        if (k > 0) {
            k = 1;
        }
    } else {
        k = -1;
    }
    if (k != 1) {
        goto ret1;
    }
    if (v == 3) {
        *cell = 0x1d;
        return 1;
    }
    if (v == 9) {
        *cell = 0x1e;
        return 1;
    }
    if (v < 0x7c) {
        a7 = data_020c9088[v * 0x1e];
    } else {
        a7 = 0;
    }
    if (v < 0x7c) {
        a4 = data_020c9089[v * 0x1e];
    } else {
        a4 = 0;
    }
    if (v < 0x7c) {
        a5 = data_020c908a[v * 0x1e];
    } else {
        a5 = 0;
    }
    if (v < 0x7c) {
        a6 = data_020c908b[v * 0x1e];
    } else {
        a6 = 0;
    }
    i = 0;
    goto test;
body:
    if ((int) i < 0x7c) {
        t = data_020c907c[i].unk_06;
        if (t > 0) {
            t = 1;
        }
    } else {
        t = -1;
    }
    if (t == 0) {
        if ((int) i < 0x7c) {
            t = data_020c907c[i].unk_0C;
        } else {
            t = 0;
        }
        if (a7 == t) {
            if ((int) i < 0x7c) {
                t = data_020c907c[i].unk_0D;
            } else {
                t = 0;
            }
            if (a4 == t) {
                if ((int) i < 0x7c) {
                    t = data_020c907c[i].unk_0E;
                } else {
                    t = 0;
                }
                if (a5 == t) {
                    if ((int) i < 0x7c) {
                        t = data_020c907c[i].unk_0F;
                    } else {
                        t = 0;
                    }
                    if (a6 == t) {
                        *cell = (u8) i;
                        return 1;
                    }
                }
            }
        }
    }
    i++;
test:
    if (i < 0x7c) {
        goto body;
    }
    return 0;
ret1:
    return 1;
ret0b:
    return 0;
}

int func_02030920(int x, int y, int flags)
{
    u8 **cellp;
    u8 *base;
    u8 *cell;
    int off;
    int v;
    int keep;
    int a0, a1, a2;
    int t0, t1, t2, t3;
    unsigned int i;

    cellp = func_01ffcb5c(x >> 4, y >> 4);
    if (cellp == 0) {
        goto ret0b;
    }
    base = *cellp;
    x = x & 0xf;
    y = y & 0xf;
    off = x + (y << 4);
    cell = base + off;
    v = base[off];
    keep = v;
    if (flags & 1) {
        a0 = 0xa;
    } else {
        a0 = v;
    }
    if ((flags >> 1) & 1) {
        a1 = 0xa;
    } else {
        a1 = v;
    }
    if ((flags >> 2) & 1) {
        a2 = 0xa;
    } else {
        a2 = v;
    }
    if ((flags >> 3) & 1) {
        v = 0xa;
    }
    i = 0;
    goto test;
body:
    if ((int) i < 0x7c) {
        t0 = ((UnkStruct_02030920 *) data_020c907c)[i].unk_0C;
    } else {
        t0 = 0;
    }
    if (a0 == t0) {
        if ((int) i < 0x7c) {
            t1 = ((UnkStruct_02030920 *) data_020c907c)[i].unk_0D;
        } else {
            t1 = 0;
        }
        if (a1 == t1) {
            if ((int) i < 0x7c) {
                t2 = ((UnkStruct_02030920 *) data_020c907c)[i].unk_0E;
            } else {
                t2 = 0;
            }
            if (a2 == t2) {
                if ((int) i < 0x7c) {
                    t3 = ((UnkStruct_02030920 *) data_020c907c)[i].unk_0F;
                } else {
                    t3 = 0;
                }
                if (v == t3) {
                    goto found;
                }
            }
        }
    }
    i++;
test:
    if (i < 0x7c) {
        goto body;
    }
    i = 0;
found:
    if (keep != 0) {
        *cell = (u8) i;
        return 1;
    }
    *cell = 0xa;
    return 0;
ret0b:
    return 0;
}

void func_020308e0(int x, int y)
{
    func_02030d68(x, y, 0);
    func_02030d48(x, y - 1, 4);
    func_02030d48(x, y + 1, 1);
    func_02030d48(x - 1, y, 8);
    func_02030d48(x + 1, y, 2);
}

int func_020308a4(int argument0, int argument1)
{
    int r;
    r = func_01ffcb2c((int) argument0, (int) argument1);
    if (r >= 104 && r <= 110) {
        r -= 104;
    } else {
        r = -1;
    }
    if (r < 0 || r == (*(struct UnkStruct_020308a4 **) &data_020da1a8)->unk_12C) {
        r = -1;
    }
    return r;
}

int func_02030890(int *param)
{
    int a;
    int b;
    int *ptr;

    ptr = param;
    a = *ptr >> 13;
    b = *(ptr + 2) >> 13;
    return func_020308a4(a, b);
}

int func_02030864(int value)
{
    if ((*(struct UnkStruct_02030864 **) &data_020da1a8)->value == -1) {
        (*(struct UnkStruct_02030864 **) &data_020da1a8)->value = value;
        return 1;
    }
    return 0;
}

int func_02030818(int *p)
{
    int x;
    int val;
    x = func_01ffcb2c(p[0] >> 13, p[2] >> 13);
    if (x >= 0x68 && x <= 0x6e) {
        x -= 0x68;
    } else {
        x = -1;
    }
    if (x >= 0) {
        val = *(int *) ((char *) (*(int **) &data_020da1a8) + 0x12c);
        if (x == val) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int func_020307f8(void)
{
    if ((*(UnkStruct_020307f8 **) &data_020da1a8)->unk_12C == -1) {
        return 0;
    }
    (*(UnkStruct_020307f8 **) &data_020da1a8)->unk_12C = -1;
    return 1;
}

int func_02030738(int *a, int *b, int *c, int *d)
{
    volatile unsigned char s[24];
    (void) &s;
    if (func_0203160c(0) != 0) {
        int minX = 0x10;
        int maxX = 0;
        int minY = 0x10;
        int maxY = 0;
        int y = 0;
        int x0 = 0;

        do {
            int x = x0;
            do {
                if (func_01ffcb2c(x, y) != 0x15) {
                    if (x < minX) {
                        minX = x;
                    } else if (x > maxX) {
                        maxX = x;
                    }
                    if (y < minY) {
                        minY = y;
                    } else if (y > maxY) {
                        maxY = y;
                    }
                }
                x++;
            } while (x < 0x20);
            y++;
        } while (y < 0x20);

        {
            int temp = (maxY << 13) + 0x1000;
            *a = minX << 13;
            *b = (maxX << 13) + 0x2000;
            *c = minY << 13;
            if (d) {
                *d = temp + 0x1000;
            }
        }
        return 1;
    } else {
        *c = 0;
        *b = *c;
        *a = *b;
        if (d) {
            *d = 0;
        }
        return 0;
    }
}
