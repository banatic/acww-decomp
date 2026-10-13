/* func_020bba14 @ 0x020bba14, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the data_020d2364 index load before the hr1 * 32 stack store; without it the store comes first */

#include "types.h"

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
extern Glob data_021f8b14;
extern int data_021f75b0;
extern int data_021f8ad4;
extern int data_020d2364[];
extern int data_021f8af4[][2];
extern struct Ab {
    u8 pad_00[0x28];
    int unk_28;
} data_021f8ab0;
extern int data_021f6f70;
extern void func_020bbb6c(void *a, int *b, int *c);
extern void func_0209def4(void *buf);
extern void func_020bbbc0(void *a, int b, int c, int d);
extern void func_020bb18c(void *a, int b, int c, int d);
extern void func_020bbf0c(int a, int b);
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
    g = &data_021f8b14;
    b = 0;
    c = 0;
    func_020bbb6c(&data_021f75b0, &b, &c);
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
    func_020bbbc0(g->unk_00, x1, x2, b);
    if (data_021f8ab0.unk_28 != data_021f8ad4) {
        ix = data_020d2364[data_021f8ab0.unk_28];
        x1 = Tl(hr1 * 32, tbl[ix][ap1]);
        x2 = Tl(hr2 * 32, tbl[ix][ap2]);
        func_020bbbc0(g->p1, x1, x2, b);
        func_020bbbc0(g->p2, (int) g->unk_00, (int) g->p1, c);
        func_020bb18c(&data_021f6f70, 0, g->p2->unk_08, 0);
        func_020bb18c(&data_021f6f70, 1, g->p2->unk_0A, 0xc0);
    } else {
        func_020bb18c(&data_021f6f70, 0, g->unk_00->unk_08, 0);
        func_020bb18c(&data_021f6f70, 1, g->unk_00->unk_0A, 0xc0);
    }
    func_020bbf0c(b, c);
}
