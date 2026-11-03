/* outdoor_villager_acts_7: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02268514 @ 0x02268514, 0xbc bytes, Thumb
 * func_ov068_022684a4 @ 0x022684a4, 0x6e bytes, Thumb
 * func_ov068_0226840c @ 0x0226840c, 0x98 bytes, Thumb
 * func_ov068_0226831c @ 0x0226831c, 0xf0 bytes, Thumb
 * func_ov068_02268254 @ 0x02268254, 0xc8 bytes, Thumb
 */

typedef struct UnkStruct_0226840c {
    int a;
    int b;
    int c;
} UnkStruct_0226840c;

typedef struct StructR6 {
    char pad_00[0x1c];
    unsigned char unk_1C;
} StructR6;

typedef struct StructR5 {
    char pad_00[0x5c];
    UnkStruct_0226840c sub;
    char pad_68[0x188 - 0x68];
    int unk_188;
    char pad_18C[0x19c - 0x18c];
    unsigned char unk_19C;
    char pad_19D[0x334 - 0x19d];
    int unk_334;
} StructR5;

struct UnkStruct_0226831c {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned char pad_68[0x188 - 0x68];
    unsigned char unk_188;
    unsigned char pad_189[0x334 - 0x189];
    unsigned char unk_334;
    unsigned char pad_335[0x514 - 0x335];
    unsigned char unk_514;
    unsigned char pad_515[0x564 - 0x515];
    unsigned char unk_564;
    unsigned char pad_565[0x9b4 - 0x565];
    unsigned char unk_9B4;
};

struct UnkStruct_0226831c_2 {
    unsigned char pad_00[0x1c];
    unsigned char mode;
};

struct UnkStruct_02268254 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    unsigned char pad_1D[0x2c - 0x1d];
    unsigned short unk_2C;
    unsigned char pad_2E[0x30 - 0x2e];
    int unk_30;
};

extern void func_ov068_0226cfd4(void *self);
extern int func_02019c20(void *addr, int p1, int p2, int p3, unsigned short p4, int p5);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, char *f, int g, unsigned int h, int i);
extern void func_02012394(void *addr, unsigned short val, int p2);
extern void func_0202e194(void *self);
extern void func_02013c04(void *addr);
extern int func_0200442c(void *addr, int p1, int p2, int p3);
extern void func_0201cbbc(void *addr);
extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8;
extern int FX_MulFunc(int, int);
extern int func_020164a0(void *addr, int value);
extern void func_0204f7e0(void *dst, void *src);
extern int func_02056f94(void *addr);
extern int func_02034270(void *out, const void *in, int a, int b);
extern int func_ov003_02221228(int a, const void *b);
extern int func_02091254(int a, const void *b, int c, int d);
extern void func_0201233c(void *p, unsigned short a, int b);
extern void func_02016638(void *p, void *q, void *r, int a, int b);
extern void func_0203423c(void *p);
extern int func_02019de8(void *);
extern void func_0201651c(void *, int);
extern void func_020122e4(void *, int, int);
extern void func_020121a8(void *, int);
extern int func_020912d4(int, void *, int, int);
extern void func_0202e188(void *);

void func_ov068_0226831c(struct UnkStruct_0226831c_2 *obj, struct UnkStruct_0226831c *s);

int func_ov068_02268514(int unused, char *self)
{
    unsigned short r4;

    func_ov068_0226cfd4(self);
    r4 = data_020c80f8;
    func_02019c20(self + 0x564, 1, 0x127, 0, r4, 0);
    func_ov068_02266c34(self + 0x898, self, 0, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    func_02012394(self + 0x9b4, r4, 0);
    *(unsigned int *) (self + 0x4e8) |= 2;
    func_0202e194(self);
    func_02013c04(self + 0x558);
    func_0200442c(self + 0x514, 0x7ee, 0x7f, 0);
    func_0201cbbc(self + 0x83c);
    return 1;
}

void func_ov068_022684a4(int *p, int target, int a, int limit1, int limit2)
{
    int diff, adiff, res, ares;

    if (*p == target) {
        return;
    }

    diff = target - *p;
    adiff = (diff < 0) ? -diff : diff;

    if (adiff < limit2) {
        *p = target;
        return;
    }

    res = FX_MulFunc(diff, a);
    ares = (res < 0) ? -res : res;

    if (ares > limit1) {
        if (res >= 0) {
            *p += limit1;
        } else {
            *p -= limit1;
        }
        return;
    } else {
        if (ares < limit2) {
            if (res >= 0) {
                *p += limit2;
            } else {
                *p -= limit2;
            }
            return;
        } else {
            *p += res;
            return;
        }
    }
}

void func_ov068_0226840c(StructR6 *r6, StructR5 *r5)
{
    UnkStruct_0226840c local;
    if (func_020164a0(&r5->unk_334, 0) == 0x127) {
        UnkStruct_0226840c *p = &r5->sub;
        func_0204f7e0(&local, p);
        func_ov068_022684a4((int *) p, local.a, 0xe66, 0x1ec, 0x31);
        func_ov068_022684a4((int *) (&p->c), local.c, 0xe66, 0x1ec, 0x31);
        r5->unk_19C = 1;
        if (r5->sub.a == local.a && p->c == local.c) {
            if (func_02056f94(&r5->unk_188) != 0) {
                func_ov068_0226831c((struct UnkStruct_0226831c_2 *) r6, (struct UnkStruct_0226831c *) r5);
            } else {
                r6->unk_1C = 1;
            }
        }
    }
}

void func_ov068_0226831c(struct UnkStruct_0226831c_2 *obj, struct UnkStruct_0226831c *s)
{
    unsigned short h;
    unsigned int vec[3];
    unsigned int matrix[16];
    unsigned int vec2[3];
    int r;
    unsigned int *vp;

    if (func_020164a0(&s->unk_334, 0) != 0x127) {
        return;
    }
    if (func_02056f94(&s->unk_188) == 0) {
        return;
    }

    h = (*(volatile unsigned short *) &data_020c80f8);
    func_02019c20(&s->unk_564, 1, 0x128, 1, h, 0);

    vp = &s->unk_5C;
    vec[0] = s->unk_5C;
    vec[1] = vp[1];
    vec[2] = vp[2];

    func_02034270(matrix, vec, 0, 0);
    r = matrix[13];

    vec2[0] = vec[0];
    vec2[1] = vec[1];
    vec2[2] = vec[2];
    func_ov003_02221228(0, vec2);

    if (r == 0x13) {
        func_02091254(0x8f, vec, 0, 0);
    } else {
        func_02091254(0x8e, vec, 0, 0);
    }

    func_0200442c(&s->unk_514, 0x7e8, 0x7f, 0);
    func_0201233c(&s->unk_9B4, h, 1);
    func_02016638(&s->unk_334, s, &s->unk_9B4, 0x128, 3);

    obj->mode = 2;
    func_0203423c(matrix);
}

void func_ov068_02268254(struct UnkStruct_02268254 *self, unsigned char *a1)
{
    int r0;
    unsigned short r6;

    r0 = func_020164a0(a1 + 0x334, 0);
    if (r0 != 0x128) {
        return;
    }

    r0 = func_02019de8(a1 + 0x564);
    if (r0 == 0) {
        return;
    }

    self->unk_30 = 0x1400;
    r6 = data_020c80f8;

    func_02019c20(a1 + 0x564, 1, 0x129, 0, r6, 0);

    *(int *) (a1 + 0x198) = self->unk_30;

    func_0201651c(a1 + 0x334, 1);

    func_020122e4(a1 + 0x9b4, r6, 0);

    func_020121a8(a1 + 0x9b4, self->unk_30);

    self->unk_2C = 0x64;

    {
        int buf[3];
        int *p = (int *) (a1 + 0x5c);
        buf[0] = *(int *) (a1 + 0x5c);
        buf[1] = p[1];
        buf[2] = p[2];
        r0 = func_020912d4(0x4c, buf, 0, 0);
    }

    *(int *) (a1 + 0xa00) = r0;
    *(unsigned char *) (a1 + 0xa04) = 1;

    func_0202e188(a1);

    self->unk_1C = 3;
}
