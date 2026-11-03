/* town_acre_count: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b184 @ 0x0204b184, 0x2 bytes, Thumb
 * func_0204b170 @ 0x0204b170, 0x12 bytes, Thumb
 * func_0204b160 @ 0x0204b160, 0x10 bytes, Thumb
 * func_0204b15c @ 0x0204b15c, 0x2 bytes, Thumb
 * func_0204b0c0 @ 0x0204b0c0, 0x9c bytes, Thumb
 * func_0204b038 @ 0x0204b038, 0x86 bytes, Thumb
 * func_0204aff0 @ 0x0204aff0, 0x48 bytes, Thumb
 * func_0204abc8 @ 0x0204abc8, 0x428 bytes, Thumb
 * func_0204a848 @ 0x0204a848, 0x380 bytes, Thumb
 * func_0204a824 @ 0x0204a824, 0x24 bytes, Thumb
 * func_0204a5d4 @ 0x0204a5d4, 0x250 bytes, Thumb
 * func_0204a3cc @ 0x0204a3cc, 0x208 bytes, Thumb
 * func_0204a398 @ 0x0204a398, 0x32 bytes, Thumb
 * func_0204a370 @ 0x0204a370, 0x26 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0204b0c0;

typedef struct {
    int unk_00, unk_04;
} In2;

typedef struct {
    char pad_00[4];
    unsigned char unk_04, unk_05, unk_06, unk_07;
    unsigned short unk_08, unk_0A;
    unsigned short unk_0C;
    char pad_0E[0x20 - 0xe];
    int unk_20;
} Params;

struct UnkStruct_0204b038 {
    int value;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    unsigned char pad_10[16];
    signed int flag : 1;
};

typedef struct Stats {
    u8 pad_00[4];
    u8 cnt[2][2];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    int unk_10;
    int unk_14;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[2];
    union {
        int all;
        struct {
            int b0 : 1;
            int b1 : 5;
            int b6 : 4;
        } b;
    } unk_20;
} Stats;

typedef struct Stats_0204a848 {
    u8 pad_00[4];
    u8 cnt[2][2];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    int unk_10;
    int unk_14;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[2];
    int unk_20;
} Stats_0204a848;

typedef struct Cell {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    int unk_10;
    int unk_14;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
    int c0 : 1;
    int c1 : 1;
    int c2 : 1;
    int c3 : 1;
    int c4 : 1;
    int c5 : 1;
    int d6 : 4;
    int c10 : 1;
    int c11 : 1;
    int c12 : 1;
    int c13 : 1;
    int c14 : 1;
    int c15 : 17;
} Cell;

typedef union UnkStruct_0204a5d4 {
    unsigned char v;
    struct {
        int d0 : 4;
        int b4 : 1;
        int b5 : 1;
        int b6 : 1;
        int b7 : 1;
        int b8 : 24;
    } b;
} UnkStruct_0204a5d4;

typedef struct UnkStruct_0204a5d4_2 {
    int unk_00;
    char pad_04[0x18 - 4];
    char unk_18;
    char pad_19[0x24 - 0x19];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned short unk_26;
    unsigned short unk_28;
    unsigned short unk_2A;
    unsigned char unk_2C;
    unsigned char unk_2D;
    unsigned char unk_2E;
    char pad_2F[1];
    UnkStruct_0204a5d4 unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    Cell grid[1][4];
} UnkStruct_0204a5d4_2;

typedef struct UnkStruct_0204a5d4_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204a5d4_3;

typedef struct Pair {
    int a;
    int b;
} Pair;

typedef struct GS {
    int hdr;
    int counts[5];
} GS;

typedef struct Cell_0204a3cc {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    int unk_10;
    int unk_14;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
    int c0 : 1;
    int c1 : 1;
    int c2 : 1;
    int c3 : 1;
    int c4 : 1;
    int c5 : 8;
    int c13 : 1;
    int c14 : 1;
    int c15 : 17;
} Cell_0204a3cc;

typedef union UnkStruct_0204a3cc_2 {
    unsigned char v;
    struct {
        int b0 : 5;
        int b5 : 1;
        int b6 : 1;
        int b7 : 1;
        int b8 : 24;
    } b;
} UnkStruct_0204a3cc_2;

typedef struct UnkStruct_0204a3cc {
    int unk_00;
    char pad_04[0x18 - 4];
    char unk_18;
    char pad_19[0x24 - 0x19];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned short unk_26;
    unsigned short unk_28;
    unsigned short unk_2A;
    unsigned char unk_2C;
    unsigned char unk_2D;
    unsigned char unk_2E;
    char pad_2F[1];
    UnkStruct_0204a3cc_2 unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    Cell_0204a3cc grid[1][4];
} UnkStruct_0204a3cc;

typedef struct UnkStruct_0204a3cc_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204a3cc_3;

extern void func_0204f800(int *, int *, int, int, int, int);
extern void func_0204a25c(int, int, int, int, int);
extern u16 *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204f2b8(int, int, int, int, int);
extern int func_0204b910(u16 *);
extern int func_0204b998(u16 *);
extern GS data_021c79c4;

void func_0204b15c(void *object);
int func_0204a398(int a, int *p, int b, int c);

void func_0204b184(void *object) {}

char *func_0204b170(char *ptr)
{
    func_0204b15c(ptr + 0x18);
    return ptr;
}

void func_0204b160(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    unsigned int zero = 0;
    unsigned int ones;

    p[0] = zero;
    p[1] = zero;

    ones = ~zero;
    p[0] = ones;
    p[1] = ones;
    p[2] = ones;
}

void func_0204b15c(void *object) {}

void func_0204b0c0(UnkStruct_0204b0c0 *out, In2 *src, Params *p)
{
    out->unk_00 = src->unk_00;
    out->unk_04 = src->unk_04;

    if (out->unk_00 < 0) {
        out->unk_08 = -1;
        return;
    }

    {
        int local[6];
        int *lp;
        int sum;
        int i, maxv, maxi;
        unsigned char v7, v5, v4, v6;

        lp = local;
        for (i = 0; i < 6; i++) {
            *lp++ = 0;
        }
        {
            volatile unsigned char *pb = (volatile unsigned char *) p;
            v7 = pb[7];
            v5 = pb[5];
            v4 = pb[4];
            v6 = pb[6];
        }
        sum = v4 + v6 + v5 + v7;

        if (sum > 0xf) {
            local[0] = (sum - 0xf) * 2;
        } else if (sum < 0xc) {
            local[1] = (0xc - sum) * 2;
        }
        if ((int) p->unk_08 >= 3) {
            local[2] = p->unk_08 - 2;
        }
        if ((int) p->unk_0A >= 3) {
            local[3] = p->unk_0A - 2;
        }
        local[4] = p->unk_0C * 0xa;
        if (((p->unk_20 << 31) >> 31) != 0) {
            local[5] = 0x32;
        }

        maxv = -1;
        maxi = -1;
        lp = local;
        for (i = 0; i < 6; lp++, i++) {
            if (*lp > maxv) {
                maxv = *lp;
                maxi = i;
            }
        }
        out->unk_08 = maxi;
    }
}

void func_0204b038(struct UnkStruct_0204b038 *s)
{
    int sum = s->unk_04 + s->unk_06 + s->unk_05 + s->unk_07;
    s->value = 100;
    if (sum > 15) {
        s->value += -2 * (sum - 15);
    } else if (sum < 12) {
        s->value += -2 * (12 - sum);
    }
    if (s->unk_08 >= 3) {
        s->value -= s->unk_08 - 2;
    }
    if (s->unk_0A >= 3) {
        s->value -= s->unk_0A - 2;
    }
    s->value += -10 * s->unk_0C;
    if (s->flag == 1) {
        s->value -= 50;
    }
    if (s->unk_0E >= 3) {
        s->value += s->unk_0E - 2;
    }
}

void func_0204aff0(int u0, int p1, int p2, int p3, int p4)
{
    int l1, l2;
    int hi, lo;

    hi = p4 % 16;
    lo = p4 / 16;
    func_0204f800(&l1, &l2, p2, p3, hi, lo);
    func_0204a25c(p1, l1, l2, 0xfff1, 0);
}

void func_0204abc8(Stats *pd, int a1, int a2, int a3)
{
    int j;
    int i;
    int n;
    u16 *p;
    int ok;
    int ok3;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            pd->cnt[j][i] = 0;
        }
    }
    pd->unk_08 = 0;
    pd->unk_0A = 0;
    pd->unk_0C = 0;
    pd->unk_0E = 0;
    pd->unk_20.all = 0;
    pd->unk_10 = -1;
    pd->unk_14 = -1;
    pd->unk_18 = 0;
    pd->unk_1A = 0;
    pd->unk_1C = 0;
    pd->unk_1D = 0;

    p = func_0204f5e0(a1, a2, a3, 0, 0, 0);

    for (n = 0; n < 0x100; p++, n++) {
        switch ((*p & 0xf000) >> 12) {
            case 0:
                if ((*p >= 0x26 && *p <= 0x2a) || (*p >= 0x5d && *p <= 0x61) || (*p >= 0x2f && *p <= 0x56) ||
                    (*p >= 0x57 && *p <= 0x5b) || (*p >= 0x66 && *p <= 0x68) || *p == 0x69 || (*p >= 0x6a && *p <= 0x6c) ||
                    *p == 0x6d || (*p >= 0xc8 && *p <= 0xcf)) {
                    pd->cnt[(n & 0xf) >> 3][n >> 7]++;
                    switch (*p) {
                        case 0x66:
                        case 0x6a:
                            pd->unk_20.all |= 0x10;
                            break;
                        case 0x67:
                        case 0x6b:
                            pd->unk_20.all |= 0x8;
                            break;
                        case 0x68:
                        case 0x6c:
                            pd->unk_20.all |= 0x20;
                            break;
                    }
                    ok = 0;
                    if (*p >= 0x26 && *p <= 0x2a) {
                        ok = 1;
                    }
                    if (ok != 0 || (*p >= 0x66 && *p <= 0x68)) {
                        pd->unk_20.all |= 0x800;
                        break;
                    }
                    if (*p >= 0x5d && *p <= 0x61) {
                        if (func_0204b998(p) != 0 || func_0204b910(p) != 0) {
                            pd->unk_20.all |= 0x1000;
                            break;
                        }
                    }
                    if (*p == 0x6d) {
                        pd->unk_1A++;
                    }
                    break;
                }
                if (*p == 0x25 || *p == 0x5c || *p == 0xc7 || (*p >= 0x6e && *p <= 0x73) || (*p >= 0x74 && *p <= 0x79) ||
                    (*p >= 0x7a && *p <= 0x7f) || (*p >= 0x80 && *p <= 0x87) || *p == 0x89) {
                    func_0204aff0((int) pd, a1, a2, a3, n);
                    break;
                }
                if (*p >= 0x21 && *p <= 0x24) {
                    pd->unk_08++;
                    break;
                }
                ok = 0;
                if (*p <= 0x1d) {
                    ok = 1;
                }
                if (ok != 0) {
                    switch (*p) {
                        case 0x1b:
                            pd->unk_10 = n % 0x10;
                            pd->unk_14 = n / 0x10;
                            pd->unk_20.b.b0 = 1;
                            break;
                        case 0x1a:
                            pd->unk_20.all |= 0x2;
                            pd->unk_0E++;
                            break;
                        case 0x1c:
                        case 0x1d:
                            pd->unk_0E++;
                            break;
                        default:
                            pd->unk_20.all |= 0x4;
                            pd->unk_0E++;
                            break;
                    }
                    break;
                }
                if ((*p >= 0x8a && *p <= 0x8f) || (*p >= 0x90 && *p <= 0x95) || (*p >= 0x96 && *p <= 0x9b) ||
                    (*p >= 0x9c && *p <= 0xa3) || *p == 0xa5) {
                    pd->unk_20.all |= 0x4;
                    pd->unk_0E++;
                    break;
                }
                if (*p >= 0xe3 && *p <= 0xe7) {
                    pd->unk_18++;
                    break;
                }
                if (*p < 0xe8) {
                    break;
                }
                if (*p > 0xfb) {
                    break;
                }
                pd->unk_20.b.b6 |= 1 << ((*p - 0xe8) / 5);
                break;
            case 1:
                if (*p == 0x1548) {
                    pd->unk_20.all |= 0x400;
                    break;
                }
                if (*p >= 0x1320 && *p <= 0x1322) {
                    pd->unk_0C++;
                    break;
                }
                if (*p == 0x1568) {
                    func_0204aff0((int) pd, a1, a2, a3, n);
                    break;
                }
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    ok3 = 0;
                    if (*p >= 0x1554 && *p <= 0x155c) {
                        ok3 = 1;
                    }
                    if (ok3 != 0) {
                        pd->unk_1C++;
                        break;
                    }
                    if (*p >= 0x154a && *p <= 0x1553) {
                        pd->unk_20.all |= 0x4000;
                        break;
                    }
                    if (*p >= 0x1518 && *p <= 0x151c) {
                        break;
                    }
                    if (*p >= 0x1542 && *p <= 0x1546) {
                        break;
                    }
                    pd->unk_0A++;
                } else {
                    switch (*p) {
                        case 0x1549:
                            pd->unk_1D++;
                            break;
                        case 0x1566:
                            pd->unk_20.all |= 0x2000;
                            break;
                    }
                }
                break;
            case 2:
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    pd->unk_0A++;
                }
                break;
            case 3:
            case 4:
                pd->unk_0A++;
                break;
        }
    }

    func_0204b038((struct UnkStruct_0204b038 *) pd);
}

void func_0204a848(Stats_0204a848 *pd, int a1, int a2, int a3)
{
    int j;
    int i;
    int n;
    u16 *p;
    int ok;
    int ok3;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            pd->cnt[j][i] = 0;
        }
    }
    pd->unk_08 = 0;
    pd->unk_0A = 0;
    pd->unk_0C = 0;
    pd->unk_0E = 0;
    pd->unk_20 = 0;
    pd->unk_10 = -1;
    pd->unk_14 = -1;
    pd->unk_18 = 0;
    pd->unk_1A = 0;
    pd->unk_1C = 0;
    pd->unk_1D = 0;

    p = func_0204f5e0(a1, a2, a3, 0, 0, 0);

    for (n = 0; n < 0x100; p++, n++) {
        switch ((*p & 0xf000) >> 12) {
            case 0:
                if ((*p >= 0x26 && *p <= 0x2a) || (*p >= 0x5d && *p <= 0x61) || (*p >= 0x2f && *p <= 0x56) ||
                    (*p >= 0x57 && *p <= 0x5b) || (*p >= 0x66 && *p <= 0x68) || *p == 0x69 || (*p >= 0x6a && *p <= 0x6c) ||
                    *p == 0x6d || (*p >= 0xc8 && *p <= 0xcf)) {
                    pd->cnt[(n & 0xf) >> 3][n >> 7]++;
                    switch (*p) {
                        case 0x66:
                        case 0x6a:
                            pd->unk_20 |= 0x10;
                            break;
                        case 0x67:
                        case 0x6b:
                            pd->unk_20 |= 0x8;
                            break;
                        case 0x68:
                        case 0x6c:
                            pd->unk_20 |= 0x20;
                            break;
                    }
                    ok = 0;
                    if (*p >= 0x26 && *p <= 0x2a) {
                        ok = 1;
                    }
                    if (ok != 0 || (*p >= 0x66 && *p <= 0x68)) {
                        pd->unk_20 |= 0x800;
                        break;
                    }
                    if (*p >= 0x5d && *p <= 0x61) {
                        if (func_0204b910(p) != 0) {
                            pd->unk_20 |= 0x1000;
                            break;
                        }
                    }
                    if (*p == 0x6d) {
                        pd->unk_1A++;
                    }
                    break;
                }
                if (*p >= 0x21 && *p <= 0x24) {
                    pd->unk_08++;
                    break;
                }
                ok = 0;
                if (*p <= 0x1d) {
                    ok = 1;
                }
                if (ok != 0) {
                    switch (*p) {
                        case 0x1b:
                            pd->unk_10 = n % 0x10;
                            pd->unk_14 = n / 0x10;
                            pd->unk_20 = (pd->unk_20 & ~1) | 1;
                            break;
                        case 0x1a:
                            pd->unk_20 |= 0x2;
                            pd->unk_0E++;
                            break;
                        case 0x1c:
                        case 0x1d:
                            pd->unk_0E++;
                            break;
                        default:
                            pd->unk_20 |= 0x4;
                            pd->unk_0E++;
                            break;
                    }
                    break;
                }
                if ((*p >= 0x8a && *p <= 0x8f) || (*p >= 0x90 && *p <= 0x95) || (*p >= 0x96 && *p <= 0x9b) ||
                    (*p >= 0x9c && *p <= 0xa3) || *p == 0xa5 || (*p >= 0x6e && *p <= 0x73) || (*p >= 0x74 && *p <= 0x79) ||
                    (*p >= 0x7a && *p <= 0x7f) || (*p >= 0x80 && *p <= 0x87)) {
                    pd->unk_20 |= 0x4;
                    pd->unk_0E++;
                }
                break;
            case 1:
                if (*p >= 0x1320 && *p <= 0x1322) {
                    pd->unk_0C++;
                    break;
                }
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    ok3 = 0;
                    if (*p >= 0x1554 && *p <= 0x155c) {
                        ok3 = 1;
                    }
                    if (ok3 != 0) {
                        pd->unk_1C++;
                        break;
                    }
                    if (*p >= 0x154a && *p <= 0x1553) {
                        pd->unk_20 |= 0x4000;
                        break;
                    }
                    if (*p >= 0x1518 && *p <= 0x151c) {
                        break;
                    }
                    if (*p >= 0x1542 && *p <= 0x1546) {
                        break;
                    }
                    pd->unk_0A++;
                } else {
                    switch (*p) {
                        case 0x1549:
                            pd->unk_1D++;
                            break;
                        case 0x1566:
                            pd->unk_20 |= 0x2000;
                            break;
                    }
                }
                break;
            case 2:
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    pd->unk_0A++;
                }
                break;
            case 3:
            case 4:
                pd->unk_0A++;
                break;
        }
    }

    func_0204b038((struct UnkStruct_0204b038 *) pd);
}

int func_0204a824(int first, int second)
{
    if (second < 0x4b) {
        return 0;
    }
    if (second < 0x50) {
        return 1;
    }
    if (second < 0x5f) {
        return 2;
    }
    if (second < 0x65) {
        return 3;
    }
    return 4;
}

void func_0204a5d4(UnkStruct_0204a5d4_2 *p, UnkStruct_0204a5d4_3 *q, int nx, int ny)
{
    int j;
    int i;
    int C;
    int t;
    int A;
    int B;
    int k;
    Cell *c;
    int u;
    Pair loc;

    C = 0;
    A = -1;
    B = -1;
    p->unk_24 = 0;
    p->unk_26 = 0;
    p->unk_25 = 0;
    p->unk_28 = 0;
    p->unk_2A = 0;
    p->unk_2C = 0;
    p->unk_2D = 0;
    p->unk_34 = A;
    p->unk_38 = A;
    p->unk_3C = A;
    p->unk_40 = A;
    p->unk_2E = 0;
    p->unk_30.v = 0;
    j = 0;
    for (k = 0; k < 5; k++) {
        data_021c79c4.counts[k] = 0;
    }
    for (j = 0; j < ny; j++) {
        for (i = 0; i < nx; i++) {
            c = &p->grid[i][j];
            func_0204abc8((Stats *) c, (int) q, i + 1, j + 1);
            if (c->c1) {
                p->unk_24 = p->unk_24 + 1;
            }
            if (c->c2) {
                p->unk_25 = p->unk_25 + 1;
            }
            if (c->c4) {
                p->unk_2C = p->unk_2C + 1;
            }
            if (c->unk_1D) {
                p->unk_2D = p->unk_2D + c->unk_1D;
            }
            p->unk_2E = p->unk_2E + c->unk_18;
            p->unk_30.b.d0 = p->unk_30.b.d0 | c->d6;
            p->unk_30.b.b4 = p->unk_30.b.b4 | c->c10;
            p->unk_30.b.b5 = p->unk_30.b.b5 | c->c13;
            p->unk_2A = p->unk_2A + (c->unk_07 + (c->unk_05 + (c->unk_04 + c->unk_06)));
            p->unk_26 = p->unk_26 + c->unk_0E;
            p->unk_28 = p->unk_28 + c->unk_08;
            if ((int) c->unk_0C > 0) {
                p->unk_30.b.b7 = 1;
            }
            p->unk_30.b.b6 = p->unk_30.b.b6 | c->c14;
            t = c->unk_00;
            data_021c79c4.counts[func_0204a824((int) p, t)]++;
            if (t < C) {
                A = i;
                B = j;
                C = t;
            }
            if (c->c0) {
                p->unk_34 = i;
                p->unk_38 = j;
                u = c->unk_14;
                p->unk_3C = c->unk_10;
                p->unk_40 = u;
            }
        }
    }
    loc.a = A;
    loc.b = B;
    func_0204b0c0((UnkStruct_0204b0c0 *) (&p->unk_18), (In2 *) (&loc), (Params *) (&p->grid[A][B]));
    p->unk_00 = func_0204a398((int) p, data_021c79c4.counts, nx, ny);
}

int func_0204a3cc(UnkStruct_0204a3cc *p, UnkStruct_0204a3cc_3 *q)
{
    int result;

    int i;
    int j;
    int nx;
    int ny;
    int C;
    int t;
    int A;
    int B;
    Cell_0204a3cc *c;
    int u;
    Pair loc;

    A = -1;
    B = -1;
    C = 0x2710;
    p->unk_24 = 0;
    p->unk_26 = 0;
    p->unk_25 = 0;
    p->unk_28 = 0;
    p->unk_2A = 0;
    p->unk_2C = 0;
    p->unk_2D = 0;
    p->unk_34 = A;
    p->unk_38 = A;
    p->unk_3C = A;
    p->unk_40 = A;
    p->unk_2E = 0;
    p->unk_30.v = 0;
    i = 0;
    for (j = 0; j < 5; j++) {
        data_021c79c4.counts[j] = 0;
    }
    nx = q->unk_04 - 2;
    ny = q->unk_08 - 2;
    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            c = &p->grid[i][j];
            func_0204a848((Stats_0204a848 *) c, (int) q, i + 1, j + 1);
            if (c->c1) {
                p->unk_24 = p->unk_24 + 1;
            }
            if (c->c2) {
                p->unk_25 = p->unk_25 + 1;
            }
            if (c->c4) {
                p->unk_2C = p->unk_2C + 1;
            }
            if (c->unk_1D) {
                p->unk_2D = p->unk_2D + c->unk_1D;
            }
            p->unk_30.b.b5 = p->unk_30.b.b5 | c->c13;
            p->unk_2A = p->unk_2A + (c->unk_07 + (c->unk_05 + (c->unk_04 + c->unk_06)));
            p->unk_26 = p->unk_26 + c->unk_0E;
            p->unk_28 = p->unk_28 + c->unk_08;
            if ((int) c->unk_0C > 0) {
                p->unk_30.b.b7 = 1;
            }
            p->unk_30.b.b6 = p->unk_30.b.b6 | c->c14;
            t = c->unk_00;
            data_021c79c4.counts[func_0204a824((int) p, t)]++;
            if (t < C) {
                A = i;
                B = j;
                C = t;
            }
            if (c->c0) {
                p->unk_34 = i;
                p->unk_38 = j;
                u = c->unk_14;
                p->unk_3C = c->unk_10;
                p->unk_40 = u;
            }
        }
    }
    loc.a = A;
    loc.b = B;
    func_0204b0c0((UnkStruct_0204b0c0 *) (&p->unk_18), (In2 *) (&loc), (Params *) (&p->grid[A][B]));
    result = func_0204a398((int) p, data_021c79c4.counts, nx, ny);
    p->unk_00 = result;
    return result;
}

int func_0204a398(int a, int *p, int b, int c)
{
    if (*p == b * c) {
        return 0;
    }
    if (*p > 0 || p[1] > 0) {
        return 1;
    }
    if (p[2] > 0) {
        return 2;
    }
    if (p[4] < 8) {
        return 3;
    }
    return 4;
}

void func_0204a370(void *base, int a, int i, int j)
{
    char *ptr = (char *) base + 0x44 + i * 144 + j * 36;
    i++;
    j++;
    func_0204a848((Stats_0204a848 *) ptr, a, i, j);
}
