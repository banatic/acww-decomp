/* field_collision_3: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203364c @ 0x0203364c, 0x2c bytes, Thumb
 * func_02033614 @ 0x02033614, 0x36 bytes, Thumb
 * func_02033118 @ 0x02033118, 0x4fc bytes, Thumb
 * func_02033100 @ 0x02033100, 0x18 bytes, Thumb
 * func_020330e8 @ 0x020330e8, 0x18 bytes, Thumb
 * func_020330bc @ 0x020330bc, 0x2a bytes, Thumb
 * func_02032fc0 @ 0x02032fc0, 0xfa bytes, Thumb
 * func_02032f94 @ 0x02032f94, 0x2c bytes, Thumb
 * func_02032f78 @ 0x02032f78, 0x1c bytes, Thumb
 * func_02032f0c @ 0x02032f0c, 0x6a bytes, Thumb
 */

typedef struct {
    char pad_00[0x480];
    volatile unsigned int unk_480;
} UnkStruct_0203364c;

struct Node {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned char unk_12;
    unsigned char unk_13;
};

struct InputStruct {
    int unk_00;
    int pad_04;
    int unk_08;
};

struct OutputStruct {
    char pad_00[0x14];
    char sub[0x8];
    int unk_1C;
    short unk_20;
    short unk_22;
};

typedef struct {
    int x;
    int y;
} Vec2;

typedef struct UnkStruct_02032fc0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[12];
    short unk_20;
    short unk_22;
} UnkStruct_02032fc0;

typedef struct {
    int unk_00;
    char unk_04;
} UnkStruct_02032f94;

typedef struct Src {
    int a, b, c;
} Src;

typedef struct Node_02032f0c {
    char pad_00[0x14];
    unsigned char unk_14;
    char pad_15[0x1c - 0x15];
    int type;
    char pad_20[0x24 - 0x20];
} Node_02032f0c;

typedef struct Header {
    int count;
    Node_02032f0c arr[1];
} Header;

extern int func_020338f8(void *a, void *b);
extern int *func_0203394c(void *buf, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8);
extern void *func_020339b8(void *buf);
extern struct Node *func_020342c0(int, int, int);
extern void func_0202f8fc(int *, int, int);
extern void __register_global_object(void *, void *, void *);
extern void func_0202f2f0(void *);
extern int data_021c30cc;
extern int data_021c30d4;
extern int data_021c30d8;
extern int data_021c30e8;
extern int data_021c30ec;
extern int data_021c30f0;
extern int data_021c30f4;
extern int data_021c30fc;
extern int data_021c3100[2];
extern int data_021c3108[2];
extern int data_021c3110[2];
extern int data_021c3118[2];
extern int data_021c3120[2];
extern int data_021c3128[2];
extern int data_021c3130[2];
extern int data_021c3138[2];
extern char data_021c3140[];
extern char data_021c314c[];
extern char data_021c3164[];
extern char data_021c3188[];
extern char data_021c31ac[];
extern char data_021c31c4[];
extern char data_021c31d0[];
extern char data_021c31dc[];
extern void *func_02030690(void *);
extern void func_020342a4(void *);
extern void func_02034294(void *arg);
extern int func_02030658(void *arg);
void func_02030640(struct OutputStruct *out, struct InputStruct *in, int p3, int p4);
void func_0203428c(void *ptr, int arg, int arg2);
extern void func_0202f898(void *dst, void *src1, void *src2);
extern int func_0202f7f4(void *v);
extern void func_0202f7a0(void *dst, void *a, void *b);
extern int FX_MulFunc(int x, int y);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __arm __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int func_020305b0(Node_02032f0c *p, Src *src, int extra);
extern void func_020eaca0(int *outvec, Src *src, Node_02032f0c *p);
extern int func_020e8ed8(int a, int b);
extern int func_02032cac(int *outp, int val, int type, int b14);

int func_0203364c(void *p0, void *buf)
{
    unsigned int c;
    if (((UnkStruct_0203364c *) p0)->unk_480 >= 0x18) {
        goto fail;
    }
    c = ((UnkStruct_0203364c *) p0)->unk_480;
    ((UnkStruct_0203364c *) p0)->unk_480 = c + 1;
    func_020338f8((char *) p0 + c * 0x30, buf);
    return 1;
fail:
    return 0;
}

void *func_02033614(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8)
{
    unsigned char buf[48];
    void *result;

    func_0203394c(buf, a2, a3, a4, a5, a6, a7, a8);
    result = (void *) func_0203364c(a1, buf);
    func_020339b8(buf);
    return result;
}

void func_02033118(void *a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    int r4 = 1;
    int i;
    int j;

    i = a5;
    for (; i >= a4; i--) {
        j = a3;
        for (; j >= a2; j--) {
            struct Node *r5;
            struct Node *sp_24;
            struct Node *sp_28;
            int sp_2c;

            int sp_30[2];
            int sp_38[2];
            int sp_40[2];
            int sp_48[2];
            int sp_50[2];
            int sp_58[2];
            int sp_60[2];
            int sp_68[2];
            volatile int sp_70;
            volatile int sp_74;
            volatile int sp_78;

            r5 = func_020342c0(a1, j, i);
            if (r5 == (void *) 0) {
                continue;
            }

            sp_24 = func_020342c0(a1, j + 1, i);
            sp_28 = func_020342c0(a1, j, i + 1);

            sp_2c = (i << 13) + 0x1000;
            sp_70 = (j << 13) + 0x1000;
            sp_74 = 0;
            sp_78 = sp_2c;

            // Block 1
            if (sp_24 != (void *) 0 && r5->unk_0C != sp_24->unk_04) {
                if ((data_021c30e8 & r4) == 0) {
                    func_0202f8fc(data_021c3128, (int) 0x00001000, 0);
                    __register_global_object((void *) (data_021c3128), (((void *) func_0202f2f0)), (void *) (data_021c31c4));
                    data_021c30e8 |= r4;
                }
                if ((data_021c30d8 & r4) == 0) {
                    func_0202f8fc(data_021c3138, (int) 0xfffff000, 0);
                    __register_global_object((void *) (data_021c3138), (((void *) func_0202f2f0)), (void *) (data_021c31dc));
                    data_021c30d8 |= r4;
                }
                func_0202f8fc(sp_30, sp_70 + 0x1000u, sp_78 - 0x1000u);
                func_0202f8fc(sp_38, sp_30[0], sp_78 + 0x1000u);

                if (r5->unk_0C > sp_24->unk_04) {
                    func_02033614(a0, (void *) sp_30, (void *) sp_38, (void *) data_021c3128, (void *) r5->unk_0C, (void *) 1,
                                  (void *) r5->unk_13, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_30, (void *) sp_38, (void *) data_021c3138, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                } else {
                    func_02033614(a0, (void *) sp_30, (void *) sp_38, (void *) data_021c3138, (void *) sp_24->unk_00,
                                  (void *) 1, (void *) sp_24->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_30, (void *) sp_38, (void *) data_021c3128, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                }
            }

            // Block 2
            if (sp_28 != (void *) 0 && r5->unk_08 != sp_28->unk_00) {
                if ((data_021c30d4 & r4) == 0) {
                    func_0202f8fc(data_021c3100, 0, (int) 0x00001000);
                    __register_global_object((void *) (data_021c3100), (((void *) func_0202f2f0)), (void *) (data_021c3140));
                    data_021c30d4 |= r4;
                }
                if ((data_021c30cc & r4) == 0) {
                    func_0202f8fc(data_021c3110, 0, (int) 0xfffff000);
                    __register_global_object((void *) (data_021c3110), (((void *) func_0202f2f0)), (void *) (data_021c3164));
                    data_021c30cc |= r4;
                }
                func_0202f8fc(sp_40, sp_70 - 0x1000u, sp_78 + 0x1000u);
                func_0202f8fc(sp_48, sp_70 + 0x1000u, sp_40[1]);

                if (r5->unk_08 > sp_28->unk_00) {
                    func_02033614(a0, (void *) sp_40, (void *) sp_48, (void *) data_021c3100, (void *) r5->unk_08, (void *) 1,
                                  (void *) r5->unk_12, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_40, (void *) sp_48, (void *) data_021c3110, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                } else {
                    func_02033614(a0, (void *) sp_40, (void *) sp_48, (void *) data_021c3110, (void *) sp_28->unk_00,
                                  (void *) 1, (void *) sp_28->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_40, (void *) sp_48, (void *) data_021c3100, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                }
            }

            // Block 3 and 4 are mutually exclusive
            if (r5->unk_00 != r5->unk_04) {
                // Block 3
                if ((data_021c30f0 & r4) == 0) {
                    func_0202f8fc(data_021c3120, (int) 0xfffff4b0, (int) 0x00000b50);
                    __register_global_object((void *) (data_021c3120), (((void *) func_0202f2f0)), (void *) (data_021c3188));
                    data_021c30f0 |= r4;
                }
                if ((data_021c30ec & r4) == 0) {
                    int *ptr = data_021c3120;
                    func_0202f8fc(data_021c3118, -ptr[0], -ptr[1]);
                    __register_global_object((void *) (data_021c3118), (((void *) func_0202f2f0)), (void *) (data_021c31ac));
                    data_021c30ec |= r4;
                }
                func_0202f8fc(sp_50, sp_70 - 0x1000u, sp_78 - 0x1000u);
                func_0202f8fc(sp_58, sp_70 + 0x1000u, sp_78 + 0x1000u);

                if (r5->unk_00 > r5->unk_04) {
                    func_02033614(a0, (void *) sp_50, (void *) sp_58, (void *) data_021c3120, (void *) r5->unk_00, (void *) 1,
                                  (void *) r5->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_50, (void *) sp_58, (void *) data_021c3118, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                } else {
                    func_02033614(a0, (void *) sp_50, (void *) sp_58, (void *) data_021c3118, (void *) r5->unk_04, (void *) 1,
                                  (void *) r5->unk_11, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_50, (void *) sp_58, (void *) data_021c3120, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                }
            } else if (r5->unk_00 != r5->unk_0C) {
                // Block 4
                if ((data_021c30fc & r4) == 0) {
                    func_0202f8fc(data_021c3130, (int) 0x00000b50, (int) 0x00000b50);
                    __register_global_object((void *) (data_021c3130), (((void *) func_0202f2f0)), (void *) (data_021c31d0));
                    data_021c30fc |= r4;
                }
                if ((data_021c30f4 & r4) == 0) {
                    int *ptr = data_021c3130;
                    func_0202f8fc(data_021c3108, -ptr[0], -ptr[1]);
                    __register_global_object((void *) (data_021c3108), (((void *) func_0202f2f0)), (void *) (data_021c314c));
                    data_021c30f4 |= r4;
                }
                func_0202f8fc(sp_60, sp_70 - 0x1000u, sp_78 + 0x1000u);
                func_0202f8fc(sp_68, sp_70 + 0x1000u, sp_78 - 0x1000u);

                if (r5->unk_00 > r5->unk_0C) {
                    func_02033614(a0, (void *) sp_60, (void *) sp_68, (void *) data_021c3130, (void *) r5->unk_00, (void *) 1,
                                  (void *) r5->unk_10, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_60, (void *) sp_68, (void *) data_021c3108, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                } else {
                    func_02033614(a0, (void *) sp_60, (void *) sp_68, (void *) data_021c3108, (void *) r5->unk_0C, (void *) 1,
                                  (void *) r5->unk_13, 0);
                    if (a6 != 0) {
                        func_02033614(a0, (void *) sp_60, (void *) sp_68, (void *) data_021c3130, (void *) 0x8000, (void *) 2,
                                      (void *) 2, 0);
                    }
                }
            }
        }
    }
}

void *func_02033100(void *ptr)
{
    func_02030690(ptr);
    func_020342a4((char *) ptr + 0x14);
    return ptr;
}

void *func_020330e8(void *p)
{
    func_02034294((char *) p + 0x14);
    func_02030658(p);
    return p;
}

void func_020330bc(struct OutputStruct *out, struct InputStruct *in, int p3, int p4, int p5, int p6)
{
    int t1 = in->unk_08 >> 13;
    int t2 = in->unk_00 >> 13;
    out->unk_20 = t2;
    out->unk_22 = t1;

    func_02030640(out, in, p3, p4);

    out->unk_1C = p5;

    func_0203428c(out->sub, p6, 0);
}

int func_02032fc0(UnkStruct_02032fc0 *a, void *b, UnkStruct_02032fc0 *c)
{
    int dx, dy;
    Vec2 v1, v2, v3, v4, v5, v6, v7;
    int ty, tx;
    int ty2, tx2;
    int min;

    dx = c->unk_20 - a->unk_20;
    dy = c->unk_22 - a->unk_22;

    if ((dx == 0 && dy == 1) || (dx == 1 && (unsigned) (dy + 1) <= 2)) {
        func_0202f8fc((int *) (&v1), a->unk_00, a->unk_08);
        func_0202f8fc((int *) (&v2), c->unk_00, c->unk_08);
        func_0202f898(&v3, &v2, &v1);
        func_0202f7f4(&v3);

        ty = v1.y - FX_MulFunc(v3.y, a->unk_0C);
        tx = v1.x - FX_MulFunc(v3.x, a->unk_0C);
        func_0202f8fc((int *) (&v4), tx, ty);

        ty2 = v2.y + FX_MulFunc(v3.y, c->unk_0C);
        tx2 = v2.x + FX_MulFunc(v3.x, c->unk_0C);
        func_0202f8fc((int *) (&v5), tx2, ty2);

        func_0202f8fc((int *) (&v6), 0, 0);
        func_0202f7a0(&v6, &v1, &v2);
        func_0202f8fc((int *) (&v7), -v6.x, -v6.y);

        min = c->unk_10;
        if (c->unk_10 > a->unk_10) {
            min = a->unk_10;
        }

        func_02033614(b, &v4, &v5, &v6, (void *) min, (void *) 3, 0, 0);
        func_02033614(b, &v4, &v5, &v7, (void *) min, (void *) 3, 0, 0);

        return 1;
    }

    return 0;
}

UnkStruct_02032f94 *func_02032f94(UnkStruct_02032f94 *obj)
{
    __cxa_vec_ctor((void *) (&obj->unk_04), 0x10, 0x24, (((void (*)(void *)) func_02033100)),
                   (((void (*)(void *)) func_020330e8)));
    obj->unk_00 = 0;
    return obj;
}

void *func_02032f78(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 4), 0x10, 0x24, (((void (*)(void *)) func_020330e8)));
    return arg;
}

int func_02032f0c(Header *h, Src *src, int extra, int *out, unsigned int mode, int value)
{
    Node_02032f0c *start;
    Node_02032f0c *p;
    int result = 0;
    start = h->arr;
    for (p = start; p < start + h->count; p++) {
        volatile int a, b, c;
        a = src->a;
        b = src->b;
        c = src->c;
        if (func_020305b0(p, src, extra)) {
            int vec[3];
            int combined;
            func_020eaca0(vec, src, p);
            combined = func_020e8ed8(vec[0], vec[2]);
            func_02032cac(out + 3, combined, p->type, p->unk_14);
            result = 1;
        }
    }
    return result;
}
