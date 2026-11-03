/* field_actor_59: 14 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02219e58 @ 0x02219e58, 0xc bytes, Thumb
 * func_ov003_02219e14 @ 0x02219e14, 0x42 bytes, Thumb
 * func_ov003_02219d8c @ 0x02219d8c, 0x88 bytes, Thumb
 * func_ov003_02219d04 @ 0x02219d04, 0x88 bytes, Thumb
 * func_ov003_02219cb4 @ 0x02219cb4, 0x50 bytes, Thumb
 * func_ov003_02219c80 @ 0x02219c80, 0x34 bytes, Thumb
 * func_ov003_02219be0 @ 0x02219be0, 0xa0 bytes, Thumb
 * func_ov003_02219b90 @ 0x02219b90, 0x4e bytes, Thumb
 * func_ov003_02219b38 @ 0x02219b38, 0x58 bytes, Thumb
 * func_ov003_02219ad0 @ 0x02219ad0, 0x66 bytes, Thumb
 * func_ov003_02219a64 @ 0x02219a64, 0x6c bytes, Thumb
 * func_ov003_02219a40 @ 0x02219a40, 0x22 bytes, Thumb
 * func_ov003_02219a14 @ 0x02219a14, 0x2c bytes, Thumb
 * func_ov003_022199d8 @ 0x022199d8, 0x3c bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_02219d8c_2 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
};

struct UnkStruct_02219d8c {
    Vec v;
    Vec v2;
};

struct UnkStruct_02219d04 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x7d4 - 0x2dc];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
    char pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
};

struct UnkStruct_02219cb4 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
};

struct UnkStruct_02219be0 {
    char pad_00[0x7d4];
    unsigned char unk_7D4[0x1c];
    int unk_7F0;
    char pad_7F4[0x820 - 0x7f4];
    unsigned short unk_820;
};

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02219b38;

typedef struct {
    unsigned char unk_00;
    char pad_01[11];
} Arg;

struct Triple {
    int a;
    int b;
    int c;
};

extern int func_02096124(int, int);
extern void func_0204f818(int *a, int *b, int c);
extern void *func_02096718(int);
extern void func_0204f794(void *, int, int);
extern void func_0200fa8c(void *, void *);
extern int func_ov003_02210c24(int, int, int *, unsigned short, int, int);
extern int func_ov003_0220d498(void *, void *, int, int, int);
extern int func_ov003_02213ae4(void *, int, int, int, int, int);
extern int func_0200fc90(void *argument0);
extern int func_ov003_02217c5c(int, int, int, int, int, int, int, int);
extern unsigned int *func_0200f27c(int, int);
extern int func_ov003_022188d0(int, int, int, int, int, int);
extern int func_ov003_022186cc(void *, unsigned int, int, int, int, int, int);
extern int func_ov003_02218388(int, int, int);
extern int func_ov003_0220f538(int, struct Triple, int, int);
extern int func_ov003_0220f3d8(void *, int, int);
extern int func_ov003_0220f344(void *, int, int);

int func_ov003_02219e58(int a)
{
    return func_02096124(9, a);
}

int func_ov003_02219e14(int p0, int p1)
{
    int x = 0, y = 0, z = 0, w = 0;
    func_0204f818(&x, &y, p1);
    func_0204f818(&z, &w, p0);
    if (x == z && y == w) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov003_02219d8c(void *p0, int slot)
{
    struct UnkStruct_02219d8c t;
    unsigned int h;
    int n;
    struct S7d4 *p;
    struct UnkStruct_02219d8c_2 *o = (struct UnkStruct_02219d8c_2 *) func_02096718(slot);
    if (o != 0) {
        h = (unsigned int) (o->unk_2D8 << 4) >> 16;
        n = 0;
        t.v.x = 0;
        t.v.y = 0;
        t.v.z = 0;
        if (o->unk_7F0 == 0x5e) {
            p = &o->unk_7D4;
            t.v.x = p->unk_04;
            t.v.y = p->unk_08;
            t.v.z = p->unk_0C;
            if (o->unk_704 == 0x4e) {
                n = 0x16 - h;
            } else if (o->unk_704 == 0x4b) {
                n = 9 - h;
            }
        }
        if (n > 0) {
            t.v2.x = t.v.x;
            t.v2.y = t.v.y;
            t.v2.z = t.v.z;
            if (func_ov003_02219e14((int) p0, (int) (&t.v2)) != 0) {
                return n;
            }
        }
    }
    return 0;
}

int func_ov003_02219d04(void *p0, int slot)
{
    Vec v;
    Vec v2;
    unsigned int h;
    int n;
    unsigned char *p;
    struct UnkStruct_02219d04 *o = (struct UnkStruct_02219d04 *) func_02096718(slot);
    if (o != 0) {
        h = (unsigned int) (o->unk_2D8 << 4) >> 16;
        n = 0;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        if (o->unk_7F0 == 0x49) {
            p = &o->unk_7D4;
            func_0204f794(&v, *p, *(p + 1));
            n = 8 - h;
        } else if (o->unk_7F0 == 0x5d) {
            p = &o->unk_7D4;
            func_0204f794(&v, *p, *(p + 1));
            n = 5 - h;
        }
        if (n > 0) {
            v2.x = v.x;
            v2.y = v.y;
            v2.z = v.z;
            if (func_ov003_02219e14((int) p0, (int) (&v2)) != 0) {
                return n;
            }
        }
    }
    return 0;
}

int func_ov003_02219cb4(void *self)
{
    struct UnkStruct_02219cb4 *p;
    int val;
    int tag;
    char buf[0x10];

    p = (struct UnkStruct_02219cb4 *) func_02096718(4);
    if (p != 0) {
        val = (int) ((unsigned int) (p->unk_2D8 << 4) >> 16);
        tag = p->unk_704;
        if ((tag == 0x67 && val == 5) || (tag == 0x44 && val == 8)) {
            func_0200fa8c(buf, p);
            return func_ov003_02219e14((int) self, (int) buf);
        }
    }
    return 0;
}

int func_ov003_02219c80(void)
{
    int result;
    int *ptr;

    result = (int) func_02096718(4);
    if (result != 0) {
        ptr = (int *) result;
        if (ptr[0x1fc] == 6) {
            if (((unsigned char *) ptr)[0x7e1] == 1) {
                return 1;
            }
        }
    }
    return 0;
}

unsigned int func_ov003_02219be0(void)
{
    unsigned int r;
    struct UnkStruct_02219be0 *o = (struct UnkStruct_02219be0 *) func_02096718(4);
    r = 0xfff1;
    if (o != 0) {
        switch (o->unk_7F0) {
            case 0x57: {
                unsigned char *p = o->unk_7D4;
                if (p[6] == 0) {
                    unsigned int i = p[8];
                    if (i < 0x38) {
                        r = (unsigned short) (i + 0x12b0);
                    } else {
                        r = 0x12b0;
                    }
                }
                break;
            }
            case 0x54: {
                unsigned char *p = o->unk_7D4;
                if (p[4] == 0) {
                    unsigned int i = p[3];
                    if (i < 0x38) {
                        if (i < 0x38) {
                            r = (unsigned short) (i + 0x12e8);
                        } else {
                            r = 0x12e8;
                        }
                    }
                }
                break;
            }
            case 0x5f: {
                int in = 0;
                unsigned int v = o->unk_820;
                if (v >= 0x1549 && v <= 0x1549) {
                    in = 1;
                }
                if (in) {
                    r = v;
                }
                break;
            }
        }
    }
    return r;
}

int func_ov003_02219b90(int p1, unsigned short *p2)
{
    int r6 = (int) func_02096718(4);
    if (r6) {
        int a = 0, b = 0;
        int c[2];
        unsigned short tmp;
        func_0204f818(&a, &b, p1);
        tmp = *p2;
        c[0] = a;
        c[1] = b;
        return func_ov003_02210c24(r6, 1, c, tmp, 6, -1);
    } else {
        return 0;
    }
}

int func_ov003_02219b38(Arg a)
{
    UnkStruct_02219b38 *x = (UnkStruct_02219b38 *) func_02096718(4);
    if (x != 0) {
        if (a.unk_00 != 0) {
            unsigned int f;
            if (x->unk_7F0 == 5) {
                f = 1;
            } else {
                f = 0;
            }
            return func_ov003_0220d498(x, &a, f, 6, -1);
        }
        return func_ov003_02213ae4(x, 1, 0, 0, 6, -1);
    }
    return 0;
}

int func_ov003_02219ad0(int *a1, int *a2, short *a3)
{
    int r = (int) func_02096718(4);
    if (r != 0) {
        if (func_0200fc90((void *) r)) {
            return func_ov003_02217c5c(r, 0x38, 0, *a1, *a2, *a3, 6, -1);
        } else {
            func_0200f27c(r, 1);
            return func_ov003_022188d0(r, *a1, *a2, *a3, 6, -1);
        }
    } else {
        return 0;
    }
}

int func_ov003_02219a64(unsigned int a, int *b, int *c, int d)
{
    void *p = func_02096718(4);
    if (p != 0) {
        if (func_0200fc90(p)) {
            return func_ov003_02217c5c((int) p, 0x39, (a << 26) >> 24, *b, *c, d, 6, -1);
        } else {
            func_0200f27c((int) p, 1);
            return func_ov003_022186cc(p, a, *b, *c, d, 6, -1);
        }
    }
    return 0;
}

int func_ov003_02219a40(void)
{
    int ret;
    ret = (int) func_02096718(4);
    if (ret) {
        return func_ov003_02218388(ret, 6, -1);
    }
    return 0;
}

int func_ov003_02219a14(struct Triple *param)
{
    int r = (int) func_02096718(4);
    if (r) {
        return func_ov003_0220f538(r, *param, 6, -1);
    }
    return 0;
}

int func_ov003_022199d8(int a)
{
    void *x = func_02096718(4);
    if (x != 0) {
        switch (a) {
            case 1:
                return func_ov003_0220f3d8(x, 6, -1);
            case 2:
                return func_ov003_0220f344(x, 6, -1);
        }
        return 0;
    }
    return 0;
}
