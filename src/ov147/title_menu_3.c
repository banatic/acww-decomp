/* title_menu_3: 3 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_0229977c @ 0x0229977c, 0x70 bytes, Thumb
 * func_ov147_022996b4 @ 0x022996b4, 0xc8 bytes, Thumb
 * func_ov147_02299698 @ 0x02299698, 0x1a bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229977c {
    u8 pad_00[0x40];
    void *unk_40;
};

struct Cfg {
    u8 *arrA;
    u8 *arrB;
    u8 count;
};

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_022996b4;

typedef struct {
    int b[8];
} UnkStruct_022996b4_2;

extern void *func_0206837c(void *arg);
extern void func_020ab670(void *ctx, int a, int b);
extern void func_020ab628(void *ctx, int i, u8 *pair, int c4, u8 *p5, int c6, int c7);
extern void func_020ab5f8(void *ctx);
extern void func_02068388(void *arg, int flag);
extern char data_021dc7bc[];
extern void func_020ab5e4(void *g);
extern int func_020988a4(char *t, int i);
extern void *func_02094fd4(UnkStruct_022996b4_2 *c);
extern void *func_02094fbc(UnkStruct_022996b4_2 *c);
extern void *func_02098844(char *t, int i);
extern void *func_02099870(void *p);
extern void *func_02095074(void *p, UnkStruct_022996b4_2 *c);
extern void *func_020ab550(void *g, int n);
extern void func_020ab76c(void *e, u8 *p);
extern void func_020ab778(void *e, u8 *p);
extern void *func_020ab798(void *e);
extern void *func_020a8bb8(void *h, UnkStruct_022996b4_2 *c);
extern void *func_020ab39c(int a);
extern void func_020ab774(void *e, void *p);
extern void func_020ab71c(void *e);
extern void func_020ab4bc(void *g, int n);
extern void func_020ab4a8(void *g);
extern void func_0200467c(int);

void func_ov147_0229977c(struct UnkStruct_0229977c *obj, struct Cfg *cfg)
{
    void *base;
    void *ctx;
    int zero1;
    int zero2;
    u8 pair[2];
    u8 *arrA;
    u8 *arrB;
    u8 count;
    int i;
    u8 b0;
    int flag;

    base = obj->unk_40;
    ctx = func_0206837c(base);

    arrA = cfg->arrA;
    arrB = cfg->arrB;
    count = cfg->count;

    func_020ab670(ctx, count, count - 1);

    zero1 = 0;
    zero2 = 0;

    for (i = 0; i < count; i++) {
        flag = zero1;
        b0 = arrA[i];
        if (b0 == 0x12 || b0 <= 1) {
            flag = 1;
        }
        pair[0] = b0;
        pair[1] = arrB[i];
        func_020ab628(ctx, i, pair, 1, &pair[1], zero2, flag);
    }

    func_020ab5f8(ctx);
    func_02068388(base, 1);
}

void func_ov147_022996b4(UnkStruct_022996b4 *self)
{
    u8 b[3];
    UnkStruct_022996b4_2 ctx;
    void *h0;
    void *g;
    void *e;
    void *e2;
    int n;
    int i;

    h0 = self->unk_40;
    g = func_0206837c(h0);
    func_020ab5e4(g);
    n = 0;
    for (i = 0; i < 4; i++) {
        if (func_020988a4(data_021dc7bc, i) != 0) {
            func_02094fd4(&ctx);
            func_02095074(func_02099870(func_02098844(data_021dc7bc, i)), &ctx);
            e = func_020ab550(g, n);
            b[0] = 4;
            func_020ab76c(e, &b[0]);
            func_020a8bb8(func_020ab798(e), &ctx);
            n++;
            func_02094fbc(&ctx);
        }
    }
    e2 = func_020ab550(g, n);
    b[1] = 0x10;
    func_020ab778(e2, &b[1]);
    func_020ab774(e2, func_020ab39c(1));
    b[2] = 0;
    func_020ab76c(e2, &b[2]);
    func_020ab71c(e2);
    func_020ab4bc(g, n + 1);
    func_020ab4a8(g);
    func_02068388(h0, 1);
}

void func_ov147_02299698(unsigned char *param)
{
    unsigned char val = param[0x1e];
    if (val == 0x24 || val == 0x27) {
        func_0200467c(0x3a);
    }
}
