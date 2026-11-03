/* path_walker_9: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02013934 @ 0x02013934, 0x14 bytes, Thumb
 * func_02013910 @ 0x02013910, 0x22 bytes, Thumb
 * func_020138a8 @ 0x020138a8, 0x68 bytes, Thumb
 * func_020138a4 @ 0x020138a4, 0x4 bytes, Thumb
 * func_02013894 @ 0x02013894, 0xe bytes, Thumb
 * func_020137ec @ 0x020137ec, 0xa8 bytes, Thumb
 * func_02013738 @ 0x02013738, 0xb4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02013910 {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
};

struct Func02013894Data {
    unsigned char pad_00[8];
    unsigned int value;
};

typedef struct {
    u32 x, y;
} Pt;

typedef struct {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x10];
} UnkStruct_020137ec;

typedef struct {
    int x, y;
} Pt_02013738;

struct UnkStruct_02013738 {
    int dx, dy;
};

extern void func_0204f818(char *p1, char *p2, int p3);
extern void func_02013440(void *);
extern void func_02012e58(void *, void *);
extern int func_02034240(UnkStruct_020137ec *o, u32 x, u32 y, int a, int b);
extern void func_0203423c(UnkStruct_020137ec *o);
extern int func_0204ed58(void *ctx, u32 x, u32 y);
extern void func_0204f794(void *p, u32 x, u32 y);
extern void func_0204f828(Pt_02013738 *, Pt_02013738 *, int);
extern void func_0204f800(char *, char *, int, int, int, int);
extern int func_02078ec0(int, int, int);
extern int func_0207cc54(int, int, int);
extern void func_0204f7ac(int, int, int, int, int);
extern struct UnkStruct_02013738 data_021c172c[];

void func_02013934(char *a, int b)
{
    func_0204f818(a + 0x94, a + 0x98, b);
}

void func_02013910(struct UnkStruct_02013910 *self)
{
    if (self->unk_94 == 0 && self->unk_98 == 0) {
        self->unk_94 = 0xFF;
        self->unk_98 = 0xFF;
    }
}

void func_020138a8(void *r0, void *r1)
{
    int sp0, sp4;
    void *r5 = r0;
    void *r4 = r1;

    sp0 = 0;
    sp4 = 0;
    func_0204f818((char *) (&sp0), (char *) (&sp4), (int) r4);

    if (*(int *) ((char *) r5 + 0x94) != 0 && *(int *) ((char *) r5 + 0x98) != 0) {
        if (*(int *) ((char *) r5 + 0x94) != sp0 || *(int *) ((char *) r5 + 0x98) != sp4) {
            *(int *) ((char *) r5 + 4) = 3;
            func_02013440(r5);
            *(int *) ((char *) r5 + 0x88) = 0;
            *(int *) ((char *) r5 + 0x8c) = 2;
            func_02012e58(r5, r4);
            *(int *) ((char *) r5 + 0x90) = 4;
        }
    }
}

void func_020138a4(int *p0, int p1)
{
    p0[0] = p1;
}

int func_02013894(const struct Func02013894Data *data)
{
    if (data->value < 7) {
        return 1;
    }
    return 0;
}

int func_020137ec(int p1, void *p2, Pt *p3, Pt *step, int n, Pt *lim, int flagA, void *ctx)
{
    UnkStruct_020137ec obj;
    int cnt;
    int i;
    u32 x, y;

    x = p3->x;
    y = p3->y;
    cnt = 0;
    i = 0;
    while (i < n) {
        x += step->x;
        y += step->y;
        if (x < lim->x && y < lim->y) {
            if (flagA != 0) {
                func_02034240(&obj, x, y, 0, 0);
                if (obj.unk_30 != 0) {
                    cnt = cnt + 1;
                } else {
                    cnt = 0;
                }
                if (cnt >= 4) {
                    func_0203423c(&obj);
                    goto fail;
                }
                func_0203423c(&obj);
            }
            if (func_0204ed58(ctx, x, y) != 0) {
                func_0204f794(p2, x, y);
                return 1;
            }
        }
        i++;
    }
fail:
    return 0;
}

int func_02013738(int unused, int p1, int p2)
{
    Pt_02013738 p, q, r;
    int mask, cnt, i, k;
    unsigned int nx, ny;

    mask = 0;
    p.x = 0;
    p.y = 0;
    q.x = 0;
    q.y = 0;
    r.x = 0;
    r.y = 0;
    cnt = 0;
    func_0204f828(&p, &q, p1);
    for (i = 0; i < 4; i++) {
        nx = q.x + data_021c172c[i].dx;
        ny = q.y + data_021c172c[i].dy;
        if (nx < 0x10 && ny < 0x10) {
            func_0204f800((char *) &r.x, (char *) &r.y, p.x, p.y, nx, ny);
            if (func_02078ec0(r.x, r.y, p2) != 0) {
                mask = (unsigned char) (mask | (1 << i));
                cnt++;
            }
        }
    }
    k = func_0207cc54(mask, cnt, 4);
    if ((unsigned int) k < 4) {
        func_0204f7ac(p1, p.x, p.y, q.x + data_021c172c[k].dx, q.y + data_021c172c[k].dy);
        return k;
    }
    return 4;
}
