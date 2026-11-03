/* tile_changes_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020460ec @ 0x020460ec, 0x68 bytes, Thumb
 * func_02046024 @ 0x02046024, 0xc8 bytes, Thumb
 * func_02045f24 @ 0x02045f24, 0x100 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 x;
    u32 y;
} Pair;

struct Entry {
    unsigned char b0_low : 3;
    unsigned char b0_high : 5;
    unsigned char b1_low : 7;
    unsigned char b1_high : 1;
    unsigned char pad_02[14];
};

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    u8 low3 : 3;
    u8 kind : 5;
    u8 p1 : 7;
    u8 flag : 1;
    u8 pad_02[10];
    u16 w;
    u16 pad_0E;
} UnkStruct_02045f24;

extern int func_02046154(int *);
extern int func_02045c48(void);
extern int func_02046194(int, int, int *, int, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
                         signed char);
extern struct Entry data_021c7884[];
extern int func_02045cec(void *pair, u8 b);
extern void func_ov003_02222d8c(u16 *a, int b, Pt *c);
extern void func_0204629c(UnkStruct_02045f24 *e);

int func_020460ec(int a1, int *a2, int a3, int a4, unsigned char p5, unsigned char p6, unsigned char p7, unsigned char p8,
                  unsigned char p9, signed char p10)
{
    int local1[2];
    int local2[2];
    int result;
    int ret = 0;

    local1[0] = a2[0];
    local1[1] = a2[1];
    if (func_02046154(local1) == 0) {
        goto done;
    }

    result = func_02045c48();
    if (result < 0) {
        goto done;
    }

    local2[0] = a2[0];
    local2[1] = a2[1];
    func_02046194(result, a1, local2, a3, a4, p5, p6, p7, p8, p9, p10);
    ret = 1;

done:
    return ret;
}

int func_02046024(int p0, Pair *p1, u32 p2, u32 p3, u8 p4, u8 p5, u8 p6, u8 p7, u8 p8, s8 p9)
{
    int result;
    Pair tmp0;
    Pair tmp2;
    Pair tmp1;
    int idx;

    result = 0;
    tmp0.x = p1->x;
    tmp0.y = p1->y;
    idx = func_02045cec(&tmp0, p8);

    if (idx >= 0) {
        if ((p0 & 3) == data_021c7884[idx].b0_low && data_021c7884[idx].b1_high != 0) {
            tmp2.x = p1->x;
            tmp2.y = p1->y;
            func_02046194(idx, p0, (int *) (&tmp2), p2, p3, (u8) p4, (u8) p5, (u8) p6, (u8) p7, (u8) p8, (s8) p9);
            result = 1;
        }
    } else {
        tmp1.x = p1->x;
        tmp1.y = p1->y;
        result = func_020460ec(p0, (int *) (&tmp1), p2, p3, (u8) p4, (u8) p5, (u8) p6, (u8) p7, (u8) p8, (s8) p9);
    }

    return result;
}

int func_02045f24(void *a, Pt *b, void *c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10)
{
    u16 u;
    Pt t1;
    Pt t2;
    Pt t3;
    Pt t4;
    int i;
    UnkStruct_02045f24 *e;

    t1.x = b->x;
    t1.y = b->y;
    i = func_02045cec((void *) (&t1), p9);
    if (i >= 0) {
        e = &((UnkStruct_02045f24 *) data_021c7884)[i];
        if (!e->flag) {
            switch (e->kind) {
                case 1:
                case 2:
                case 6:
                case 7:
                    u = 0xfff1;
                    u = e->w;
                    t2.x = b->x;
                    t2.y = b->y;
                    func_ov003_02222d8c(&u, e->low3, &t2);
                    break;
            }
            func_0204629c(e);
        }
        t3.x = b->x;
        t3.y = b->y;
        return func_02046194(i, (int) a, (int *) (&t3), (int) c, d, (u8) p5, (u8) p6, (u8) p7, (u8) p8, (u8) p9, (s8) p10);
    } else {
        t4.x = b->x;
        t4.y = b->y;
        return func_020460ec((int) a, (int *) (&t4), (int) c, d, (u8) p5, (u8) p6, (u8) p7, (u8) p8, (u8) p9, (s8) p10);
    }
}
