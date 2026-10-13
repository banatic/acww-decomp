/* func_ov003_02211604 @ 0x02211604, 0x2b4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int a;
    int b;
    int c;
    u8 d;
    u8 e;
} UnkStruct_02211604;

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    char pad_00[0x2d4];
    int unk_2D4;
    int unk_2D8;
    char pad_2DC[0x62c - 0x2dc];
    int unk_62C;
    int unk_630;
    int unk_634;
    char pad_638[0x704 - 0x638];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    UnkStruct_02211604 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    int unk_800;
    char pad_804[0x81c - 0x804];
    int unk_81C;
    u16 unk_820;
    volatile u16 unk_822;
    int unk_824;
    int unk_828;
    int unk_82C;
    int unk_830;
    int unk_834;
    int unk_838;
    char pad_83C[0x8f0 - 0x83c];
    char unk_8F0[4];
} UnkStruct_02211604_2;

typedef struct {
    int a;
    int b;
    int c;
    u16 d;
    u8 e;
} MSub;

typedef struct {
    char pad_00[0xc];
    MSub sub;
} Msg;

extern void *data_021c80bc;
extern void *data_020ccf94;

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_020109a0(UnkStruct_02211604_2 *self, int a, int b, int c);
extern void func_0203f7d0(int *a, int *b);
extern void func_0200f268(UnkStruct_02211604_2 *self, int a);
extern void func_0204f818(int *x, int *y, int *pos);
extern void func_ov003_022118d8(char *a, Pair *p, int b, int c);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern void func_0200f27c(UnkStruct_02211604_2 *self, int a);
extern int func_02073908(void *g, int a);
extern void func_02035684(int a, int b, int c);
extern void func_02079750(char *p);

static __inline int same_item(u16 *p, u16 *t)
{
    if (func_0204bcdc(p) != 0) {
        *t = 0xfff1;
        return (func_0204bc64(p) == func_0204bc64(t)) ? 1 : 0;
    }
    return (*p == 0xfff1) ? 1 : 0;
}

void func_ov003_02211604(UnkStruct_02211604_2 *self, Msg *m)
{
    u16 sc[5];
    struct {
        int px;
        int py;
        Pair pr;
        int pos[3];
    } w;
    u16 *cell;
    int k;
    int gx;
    int gy;
    unsigned int ok;
    u16 n;
    MSub *q;
    UnkStruct_02211604 *s;
    int tx;
    int ty;
    int tz;
    int hh;
    int h;

    q = &m->sub;
    w.pos[0] = q->a;
    w.pos[1] = q->b;
    w.pos[2] = q->c;
    sc[0] = q->d;
    k = q->e;
    s = &self->unk_7D4;
    s->d = 0;
    s->a = w.pos[0];
    s->b = w.pos[1];
    s->c = w.pos[2];
    s->e = (u8) k;
    if (self->unk_704 == 0x49 || self->unk_704 == 0x4a || same_item(&sc[0], &sc[3]) == 0) {
        func_020109a0(self, 0x4f, 3, 0);
    } else {
        func_020109a0(self, 0x49, 3, 0);
    }
    tz = self->unk_634;
    ty = self->unk_630;
    tx = self->unk_62C;
    self->unk_824 = tx;
    self->unk_828 = ty;
    self->unk_82C = tz;
    func_0203f7d0(&self->unk_824, &self->unk_824);
    self->unk_830 = 0x1000;
    self->unk_834 = 0x1000;
    self->unk_838 = 0x1000;
    func_0200f268(self, 0xd);
    w.px = 0;
    w.py = 0;
    func_0204f818(&w.px, &w.py, w.pos);
    hh = self->unk_820;
    w.pr.x = w.px;
    w.pr.y = w.py;
    func_ov003_022118d8(self->unk_8F0, &w.pr, hh, k);
    {
        int px;
        int py;
        px = w.px;
        py = w.py;
        gx = px >> 4;
        gy = py >> 4;
        cell = func_0204f5e0(data_021c80bc, gx, gy, px - (gx << 4), py - (gy << 4), 0);
    }
    if (same_item(&sc[0], &sc[4]) == 0) {
        self->unk_822 = sc[0];
        self->unk_820 = self->unk_822;
        ok = 0;
        if (*cell >= 0xfc && *cell <= 0xfd) {
            ok = 1;
        }
        if (ok != 0) {
            n = (u16) (self->unk_2D4 >> 12);
            self->unk_2D8 = (u16) (n - 1) << 12;
            func_0200f27c(self, 0xd);
        }
    } else {
        if (same_item(&self->unk_820, &sc[2]) != 0 || func_02073908(data_020ccf94, self->unk_800) == 0) {
            if (cell == 0) {
                self->unk_822 = 0xfff1;
                self->unk_820 = self->unk_822;
            } else {
                self->unk_822 = *cell;
                self->unk_820 = self->unk_822;
            }
        }
    }
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_02035684(0x12, 0xf, 0);
        ok = 0;
        if (self->unk_820 >= 0x1549 && self->unk_820 <= 0x1549) {
            ok = 1;
        }
        if (ok != 0) {
            func_02079750((char *) self + 0x5c);
        }
    }
    self->unk_81C = 7;
    func_0200f27c(self, 0x1c);
}
