/* sky_5: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bbcfc @ 0x020bbcfc, 0x32 bytes, Thumb
 * func_020bbc90 @ 0x020bbc90, 0x6c bytes, Thumb
 * func_020bbbf0 @ 0x020bbbf0, 0xa0 bytes, Thumb
 * func_020bbbc0 @ 0x020bbbc0, 0x2e bytes, Thumb
 * func_020bbb6c @ 0x020bbb6c, 0x54 bytes, Thumb
 * func_020bbb20 @ 0x020bbb20, 0x4c bytes, Thumb
 * func_020bba14 @ 0x020bba14, 0x10c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned short r : 5;
    unsigned short g : 5;
    unsigned short b : 5;
    unsigned short a : 1;
} RGB555;

typedef struct {
    unsigned char pad_00[0x120c];
    unsigned int unk_120C;
    unsigned char pad_1210[0x314];
    unsigned int unk_1524;
    unsigned int unk_1528;
} UnkStruct_020bbb6c;

struct UnkStruct_020bbb20 {
    int unk_00;
    int pad_04;
    int unk_08;
};

struct UnkStruct_020bbb20_2 {
    unsigned char pad_00[0x24];
    int unk_24;
    int unk_28;
};

typedef struct Spr {
    u8 pad_00[8];
    u16 unk_08;
    u16 unk_0A;
} Spr;

typedef struct Glob {
    Spr *unk_00;
    Spr *p1;
    Spr *p2;
} Glob;

extern int func_020e98d4(int);
extern void func_020642a8(void *, void *);
extern void func_0209e474(void *);
extern void func_020e930c(int *, int);
extern int func_020e92d0(int *, int);
extern unsigned char data_021dc7aa[];
extern void func_0209def4(void *buf);
extern int func_02002bd0(int a, int b, int c, int d, int e);
extern unsigned char data_020d22b4[];
extern struct UnkStruct_020bbb20 data_021f8b14;
extern struct UnkStruct_020bbb20_2 data_021f8ab0;
extern int data_021f75b0;
extern int data_021f8ad4;
extern int data_020d2364[];
extern int data_021f8af4[][2];
extern int data_021f6f70;
extern void func_020bb18c(void *a, int b, int c, int d);
extern void func_020bbf0c(int a, int b);

void func_020bba14(void);

int func_020bbcfc(int *param)
{
    int i;
    int *ptr = param;
    int val = 0x20;

    for (i = 0; i < 3; i++) {
        if (ptr[0] == 0) {
            ptr[0] = func_020e98d4(val);
            if (ptr[0] == 0) {
                return 0;
            }
        }
        ptr++;
    }
    return 1;
}

void func_020bbc90(void *out)
{
    struct UnkStruct_020bbc90 {
        unsigned char pad[3];
        unsigned char b0;
        unsigned char b1;
        unsigned char b2;
        unsigned char pad2;
        unsigned char pad3;
        int c;
        unsigned short d;
        unsigned char filler[14];
    } local;
    unsigned int r4;
    int val;

    *(unsigned int *) &local = 0;
    *((unsigned int *) ((char *) &local + 4)) = 0;

    func_020642a8((void *) data_021dc7aa, &local.d);

    func_0209e474(&local);

    r4 = local.b0 | (local.b1 << 5 | (((unsigned int) local.d << 16) | ((local.b2 & 0x1f) << 9)));

    func_020e930c(&local.c, 1);
    func_020e930c(&local.c, (int) r4);

    val = func_020e92d0(&local.c, 0x2aaa);
    val -= 0x1555;
    *(unsigned short *) ((char *) out + 0x1538) = (unsigned short) val;
}

void func_020bbbf0(RGB555 *dst, RGB555 *ca, RGB555 *cb, int weightB)
{
    int weightA = 0x1000 - weightB;

    dst->r = (ca->r * weightA + cb->r * weightB) >> 12;
    dst->g = (ca->g * weightA + cb->g * weightB) >> 12;
    dst->b = (ca->b * weightA + cb->b * weightB) >> 12;
    dst->a = 0;
}

void func_020bbbc0(void *p0, void *p1, void *p2, void *p3)
{
    int i;
    void *a = p0;
    void *b = p1;
    void *c = p2;
    void *d = p3;

    for (i = 0; i < 6; i++) {
        func_020bbbf0((RGB555 *) a, (RGB555 *) b, (RGB555 *) c, (int) d);
        a = (char *) a + 2;
        b = (char *) b + 2;
        c = (char *) c + 2;
    }
}

void func_020bbb6c(UnkStruct_020bbb6c *a, unsigned int *b, unsigned int *c)
{
    unsigned char buf[8];

    func_0209def4(buf);
    *b = ((unsigned int) buf[0] * 0x44445) >> 12;
    if (a->unk_1528 != a->unk_1524) {
        *c = (int) (a->unk_120C << 12) / 0x20;
    } else {
        *c = 0;
    }
}

int func_020bbb20(int arg)
{
    struct UnkStruct_020bbb20 *p = &data_021f8b14;
    func_020bba14();
    if (data_021f8ab0.unk_28 != data_021f8ab0.unk_24) {
        return func_02002bd0(p->unk_08, data_020d22b4[arg], 1, 1, 1);
    } else {
        return func_02002bd0(p->unk_00, data_020d22b4[arg], 1, 1, 1);
    }
}

/* FAKEMATCH: the empty if is a block boundary after the layout index load; without it the load is folded into the row-pointer temp and the hour and period scalings (hr1 * 32, ap1 * 4) are hoisted above it; inline helpers, locals, pointer types, C++ and earlier load positions all keep that order */
static inline int Tl(int hr, int v)
{
    return v + hr;
}

void func_020bba14(void)
{
    u8 buf[4];
    int hr2;
    int h;
    int ix;
    int x1;
    int x2;
    int (*tbl)[2];
    int b;
    Glob *g;
    int ap1;
    int ap2;
    int hr1;
    int c;

    tbl = data_021f8af4;
    g = ((Glob *) &data_021f8b14);
    b = 0;
    c = 0;
    func_020bbb6c((UnkStruct_020bbb6c *) (&data_021f75b0), (unsigned int *) (&b), (unsigned int *) (&c));
    func_0209def4(buf);
    h = buf[1];
    hr1 = h;
    if (h < 12) {
        ap1 = 0;
    } else {
        hr1 -= 12;
        ap1 = 1;
    }
    hr2 = (unsigned int) (h + 1) % 24;
    if (hr2 < 12) {
        ap2 = 0;
    } else {
        hr2 -= 12;
        ap2 = 1;
    }
    ix = data_020d2364[data_021f8ad4];
    if (ix && ix) {
    }
    x1 = Tl(hr1 * 32, tbl[ix][ap1]);
    x2 = Tl(hr2 * 32, tbl[ix][ap2]);
    func_020bbbc0(g->unk_00, (void *) x1, (void *) x2, (void *) b);
    if ((*(struct Ab {
            u8 pad_00[0x28];
            int unk_28;
        } *) &data_021f8ab0)
            .unk_28 != data_021f8ad4) {
        ix = data_020d2364[(*(struct Ab {
                               u8 pad_00[0x28];
                               int unk_28;
                           } *) &data_021f8ab0)
                               .unk_28];
        x1 = Tl(hr1 * 32, tbl[ix][ap1]);
        x2 = Tl(hr2 * 32, tbl[ix][ap2]);
        func_020bbbc0(g->p1, (void *) x1, (void *) x2, (void *) b);
        func_020bbbc0(g->p2, (void *) ((int) g->unk_00), (void *) ((int) g->p1), (void *) c);
        func_020bb18c(&data_021f6f70, 0, g->p2->unk_08, 0);
        func_020bb18c(&data_021f6f70, 1, g->p2->unk_0A, 0xc0);
    } else {
        func_020bb18c(&data_021f6f70, 0, g->unk_00->unk_08, 0);
        func_020bb18c(&data_021f6f70, 1, g->unk_00->unk_0A, 0xc0);
    }
    func_020bbf0c(b, c);
}
