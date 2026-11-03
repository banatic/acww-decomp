/* link_state: 31 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a617c @ 0x020a617c, 0xa bytes, Thumb
 * func_020a6170 @ 0x020a6170, 0xa bytes, Thumb
 * func_020a6160 @ 0x020a6160, 0x10 bytes, Thumb
 * func_020a6104 @ 0x020a6104, 0x5c bytes, Thumb
 * func_020a5c38 @ 0x020a5c38, 0x4cc bytes, Thumb
 * func_020a5c30 @ 0x020a5c30, 0x6 bytes, Thumb
 * func_020a5c28 @ 0x020a5c28, 0x6 bytes, Thumb
 * func_020a5c20 @ 0x020a5c20, 0x6 bytes, Thumb
 * func_020a5c18 @ 0x020a5c18, 0x6 bytes, Thumb
 * func_020a5c10 @ 0x020a5c10, 0x6 bytes, Thumb
 * func_020a5c08 @ 0x020a5c08, 0x6 bytes, Thumb
 * func_020a5c00 @ 0x020a5c00, 0x8 bytes, Thumb
 * func_020a5bf8 @ 0x020a5bf8, 0x6 bytes, Thumb
 * func_020a5bf0 @ 0x020a5bf0, 0x6 bytes, Thumb
 * func_020a5be8 @ 0x020a5be8, 0x8 bytes, Thumb
 * func_020a5be0 @ 0x020a5be0, 0x6 bytes, Thumb
 * func_020a5bd8 @ 0x020a5bd8, 0x6 bytes, Thumb
 * func_020a5bd0 @ 0x020a5bd0, 0x8 bytes, Thumb
 * func_020a5bc4 @ 0x020a5bc4, 0xa bytes, Thumb
 * func_020a5bb8 @ 0x020a5bb8, 0xa bytes, Thumb
 * func_020a5bac @ 0x020a5bac, 0xc bytes, Thumb
 * func_020a5b98 @ 0x020a5b98, 0x14 bytes, Thumb
 * func_020a5750 @ 0x020a5750, 0x448 bytes, Thumb
 * func_020a5748 @ 0x020a5748, 0x6 bytes, Thumb
 * func_020a5740 @ 0x020a5740, 0x6 bytes, Thumb
 * func_020a5738 @ 0x020a5738, 0x6 bytes, Thumb
 * func_020a5730 @ 0x020a5730, 0x6 bytes, Thumb
 * func_020a5728 @ 0x020a5728, 0x6 bytes, Thumb
 * func_020a5720 @ 0x020a5720, 0x6 bytes, Thumb
 * func_020a5718 @ 0x020a5718, 0x6 bytes, Thumb
 * func_020a5710 @ 0x020a5710, 0x6 bytes, Thumb
 */

struct UnkStruct_020a5c38_2;

struct UnkStruct_020a5c38 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    unsigned char pad_00[148];
    unsigned long unk_94;
} UnkStruct_020a5c30;

typedef struct {
    unsigned char pad_00[148];
    unsigned long unk_94;
} UnkStruct_020a5c28;

typedef struct {
    unsigned char pad_00[152];
    unsigned short unk_98;
} UnkStruct_020a5c20;

typedef struct {
    unsigned char pad_00[152];
    unsigned short unk_98;
} UnkStruct_020a5c18;

typedef struct {
    unsigned char pad_00[156];
    unsigned long unk_9C;
} UnkStruct_020a5c10;

typedef struct {
    unsigned char pad_00[156];
    unsigned long unk_9C;
} UnkStruct_020a5c08;

typedef struct {
    unsigned char pad_00[164];
    unsigned long unk_A4;
} UnkStruct_020a5be0;

typedef struct {
    unsigned char pad_00[164];
    unsigned long unk_A4;
} UnkStruct_020a5bd8;

struct UnkStruct_020a5b98 {
    char pad_00[0xa8];
    int arr[4];
};

struct UnkStruct_020a5750_2;

struct UnkStruct_020a5750 {
    char pad_00[0x64];
    int unk_64;
};

struct Thr {
    unsigned long unk_00;
    unsigned long unk_04;
    unsigned long unk_08;
};

struct Nm {
    unsigned short h;
    unsigned char rest[0xc];
};

typedef struct {
    unsigned char pad_00[184];
    unsigned long unk_B8;
} UnkStruct_020a5748;

typedef struct {
    unsigned char pad_00[184];
    unsigned long unk_B8;
} UnkStruct_020a5740;

typedef struct {
    unsigned char pad_00[188];
    unsigned char unk_BC;
} UnkStruct_020a5738;

typedef struct {
    unsigned char pad_00[188];
    unsigned char unk_BC;
} UnkStruct_020a5730;

typedef struct {
    unsigned char pad_00[192];
    unsigned long unk_C0;
} UnkStruct_020a5728;

typedef struct {
    unsigned char pad_00[192];
    unsigned long unk_C0;
} UnkStruct_020a5720;

typedef struct {
    unsigned char pad_00[196];
    unsigned char unk_C4;
} UnkStruct_020a5718;

typedef struct {
    unsigned char pad_00[196];
    unsigned char unk_C4;
} UnkStruct_020a5710;

extern void func_02073820(void *p);
extern void func_020737f0(void *p, char *q, int r);
extern void func_02073770(void *p, int r, int b);
extern void *data_020ccf94;
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *p);
extern void func_020a76cc(unsigned char *p);
extern void func_020a76c8(unsigned char *p);
extern void func_020a76ac(unsigned char *out, int a, int b, int c);
extern int func_02073dd4(struct UnkStruct_020a5c38 *g, int i);
extern int func_02073918(struct UnkStruct_020a5c38 *g, int i);
extern void func_020a6cd4(void *p);
extern int func_020eae40(void);
extern unsigned char data_021f42f0;
extern unsigned long data_021f42f8;
extern int data_021f4308;
extern struct Thr data_021f4314;
extern struct UnkStruct_020a5750_2 data_021f4320;
extern struct Nm data_021dc7aa;
extern int func_0203df10(void);
extern int func_0203dee8(void);
extern void func_0206f5b0(void);
extern void func_020b8df0(unsigned long i);
extern void func_020b8e10(unsigned long i);
extern void func_020b8dd8(void);
extern void func_02073150(struct UnkStruct_020a5750 *g, int v);
extern int func_020740b4(void);
extern int func_02098420(unsigned long a);
extern void *func_0209847c(unsigned long a);
extern void *func_02099688(void *p);
extern int func_0208829c(void *p);
extern struct Nm *func_020882ec(void *record);
extern int memcmp(const void *a, const void *b, int n);
extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void *);
extern int func_020ec1f8(void);
extern int func_020732c0(struct UnkStruct_020a5750 *g);
extern void func_020732cc(struct UnkStruct_020a5750 *g, int v);
extern int func_020b6434(int a, int b, int c, int d);
extern int func_020b63f4(int dst, unsigned char val, struct Thr *src, unsigned int extra, short p1, unsigned char p2,
                         unsigned char p3);
extern void func_020a13c4(unsigned long a);
extern int func_020b5ee4(int a, int b);
extern void func_020a18e8(void);
extern void func_020a18c4(void);
extern void func_020a18dc(void);
extern void func_020a18b8(void);
extern void func_020a18a0(void);
extern void func_020a01e0(int a);

void func_020a5c30(UnkStruct_020a5c30 *p, unsigned long v);
void func_020a5c10(UnkStruct_020a5c10 *p, unsigned long v);
unsigned long func_020a5c08(UnkStruct_020a5c08 *p);
void func_020a5bf8(int p0, int v);
int func_020a5bf0(int p0);
void func_020a5be0(UnkStruct_020a5be0 *p, unsigned long v);
unsigned long func_020a5bd8(UnkStruct_020a5bd8 *p);
void func_020a5bc4(char *base, int idx, int v);
int func_020a5bb8(char *base, int idx);
void func_020a5748(UnkStruct_020a5748 *p, unsigned long v);
unsigned long func_020a5740(UnkStruct_020a5740 *p);
void func_020a5738(UnkStruct_020a5738 *p, unsigned char v);
unsigned char func_020a5730(UnkStruct_020a5730 *p);
void func_020a5728(UnkStruct_020a5728 *p, unsigned long v);

void func_020a617c(char *base, int idx, int v)
{
    *(int *) (base + idx * 4 + 0x84) = v;
}

int func_020a6170(char *base, int idx)
{
    return *(int *) (base + idx * 4 + 0x84);
}

void func_020a6160(int *p)
{
    int i;
    int *q = p + 0x21;
    for (i = 3; i >= 0; i--) {
        *q++ = 7;
    }
}

void func_020a6104(int a, int b, int c)
{
    if (c) {
        func_020a617c((char *) a, b, 6);
    } else {
        if (b == 0) {
            func_020a617c((char *) a, 0, 6);
        } else {
            char v = 6;
            void *p = data_020ccf94;
            func_02073820(p);
            func_020737f0(p, &v, 1);
            func_02073770(p, 1, b);
            func_020a617c((char *) a, b, 7);
        }
    }
}

void func_020a5c38(struct UnkStruct_020a5c38_2 *self)
{
    struct UnkStruct_020a5c38 *g;
    struct UnkStruct_020a5c38 *h;
    unsigned int i;
    int j;
    unsigned int st;
    int st2;
    int ok;
    int ok2;
    int ok3;
    int ok4;
    int ok5;
    int me;
    int zA, zB, zC, zD, zE, zF, zG;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;

    i = 0;
    zA = 0;
    zB = 0;
    zC = 0;
    zD = 0;
    zE = 0;
    zF = 0;
    zG = 0;

    for (; i < 4; i++) {
        st = func_020a6170((char *) self, i);
        if (st > 3) {
            continue;
        }
        ok = 1;
        for (j = 3; j >= 0; j--) {
            switch (func_020a6170((char *) self, j)) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    break;
                default:
                    ok = zC;
                    break;
            }
            if (!ok) {
                break;
            }
        }
        if (ok) {
            if ((int) func_020a5c08((UnkStruct_020a5c08 *) self) != 4) {
                ok = zD;
            }
        }
        if (ok) {
            if (func_020b65c4() == 0x2e || func_020b65c4() == 0x2f || func_020b65c4() == 0xd) {
                ok = zE;
            }
        }
        if (ok) {
            if (func_020b5e84((unsigned char *) func_020b5e10()) == 0x2e ||
                func_020b5e84((unsigned char *) func_020b5e10()) == 0x2f ||
                func_020b5e84((unsigned char *) func_020b5e10()) == 0xd) {
                ok = zF;
            }
        }
        if (ok) {
            func_020a5c10((UnkStruct_020a5c10 *) self, zA);
            func_020a5bf8((int) self, (unsigned long) i);
            if (st == 0) {
                func_020a5be0((UnkStruct_020a5be0 *) self, zB);
            } else if (st == 1) {
                func_020a5be0((UnkStruct_020a5be0 *) self, 1);
            } else if (st == 2) {
                func_020a5be0((UnkStruct_020a5be0 *) self, 2);
            } else {
                func_020a5be0((UnkStruct_020a5be0 *) self, 3);
            }
            func_020a617c((char *) self, i, 4);
        } else {
            func_020a6104((int) self, i, st == 0 ? 1 : zG);
        }
    }

    if ((int) func_020a5c08((UnkStruct_020a5c08 *) self) == 0) {
        me = (unsigned long) func_020a5bf0((int) self);
        j = 3;
        g = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(g, j)) {
                if (j == 0) {
                    func_020a5bc4((char *) self, 0, 0);
                } else {
                    func_020a76cc(&b0);
                    func_020a76ac(&b0, 0, func_020a5bd8((UnkStruct_020a5bd8 *) self), (unsigned long) func_020a5bf0((int) self));
                    func_02073820((void *) g);
                    func_020737f0((void *) g, (char *) (&b0), 1);
                    func_02073770((void *) g, 0xc, j);
                    func_020a5bc4((char *) self, j, 1);
                    func_020a76c8(&b0);
                }
            }
        }
        func_020a5c10((UnkStruct_020a5c10 *) self, 1);
    }

    if ((int) func_020a5c08((UnkStruct_020a5c08 *) self) == 1) {
        ok2 = 1;
        me = (unsigned long) func_020a5bf0((int) self);
        j = 3;
        h = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(h, j)) {
                st2 = func_020a5bb8((char *) self, j);
                if (st2 != 2 && st2 != 3) {
                    ok2 = 0;
                    break;
                }
            }
        }
        if (ok2) {
            ok3 = 1;
            for (j = 3; j >= 0; j--) {
                if (j != me && func_02073dd4(h, j)) {
                    if (func_020a5bb8((char *) self, j) == 3) {
                        ok3 = 0;
                        break;
                    }
                }
            }
            if (ok3) {
                for (j = 3; j >= 0; j--) {
                    if (j != me && func_02073dd4(h, j)) {
                        if (j == 0) {
                            func_020a5bc4((char *) self, 0, 5);
                        } else {
                            func_020a76cc(&b1);
                            func_020a76ac(&b1, 5, 4, (unsigned long) func_020a5bf0((int) self));
                            func_02073820((void *) h);
                            func_020737f0((void *) h, (char *) (&b1), 1);
                            func_02073770((void *) h, 0xc, j);
                            func_020a5bc4((char *) self, j, 5);
                            func_020a76c8(&b1);
                        }
                    }
                }
                if (func_020a5bd8((UnkStruct_020a5bd8 *) self) == 0 || func_02073918(h, me) != 0) {
                    func_020a617c((char *) self, me, 5);
                } else {
                    b2 = 5;
                    h = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
                    func_02073820((void *) h);
                    func_020737f0((void *) h, (char *) (&b2), 1);
                    func_02073770((void *) h, 1, me);
                    func_020a617c((char *) self, me, 7);
                }
                if (func_020a5bd8((UnkStruct_020a5bd8 *) self) == 0) {
                    func_020a6cd4(0);
                }
                func_020a5c30((UnkStruct_020a5c30 *) self, me);
                func_020a5c10((UnkStruct_020a5c10 *) self, 2);
            } else {
                for (j = 3; j >= 0; j--) {
                    if (j != me && func_02073dd4(h, j)) {
                        if (func_020a5bb8((char *) self, j) == 2) {
                            if (j == 0) {
                                func_020a5bc4((char *) self, 0, 4);
                            } else {
                                func_020a76cc(&b3);
                                func_020a76ac(&b3, 4, 4, (unsigned long) func_020a5bf0((int) self));
                                func_02073820((void *) h);
                                func_020737f0((void *) h, (char *) (&b3), 1);
                                func_02073770((void *) h, 0xc, j);
                                func_020a5bc4((char *) self, j, 4);
                                func_020a76c8(&b3);
                            }
                        } else {
                            func_020a5bc4((char *) self, j, 6);
                        }
                    }
                }
                func_020a5c10((UnkStruct_020a5c10 *) self, 3);
            }
        }
    }

    if ((int) func_020a5c08((UnkStruct_020a5c08 *) self) == 2) {
        ok4 = 1;
        me = (unsigned long) func_020a5bf0((int) self);
        j = 3;
        g = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(g, j)) {
                if (func_020a5bb8((char *) self, j) != 6) {
                    ok4 = 0;
                    break;
                }
            }
        }
        if (ok4) {
            func_020a5c10((UnkStruct_020a5c10 *) self, 4);
        }
    }

    if ((int) func_020a5c08((UnkStruct_020a5c08 *) self) == 3) {
        ok5 = 1;
        me = (unsigned long) func_020a5bf0((int) self);
        j = 3;
        h = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
        for (; j >= 0; j--) {
            if (j != me && func_02073dd4(h, j)) {
                if (func_020a5bb8((char *) self, j) != 6) {
                    ok5 = 0;
                    break;
                }
            }
        }
        if (ok5) {
            if (func_020a5bd8((UnkStruct_020a5bd8 *) self) == 0 || func_02073918(h, me) != 0) {
                func_020a617c((char *) self, me, 6);
            } else {
                b4 = 6;
                h = (*(struct UnkStruct_020a5c38 * *) &data_020ccf94);
                func_02073820((void *) h);
                func_020737f0((void *) h, (char *) (&b4), 1);
                func_02073770((void *) h, 1, me);
                func_020a617c((char *) self, me, 7);
            }
            if (func_020a5bd8((UnkStruct_020a5bd8 *) self) == 0) {
                func_020eae40();
            }
            func_020a5c10((UnkStruct_020a5c10 *) self, 4);
        }
    }
}

void func_020a5c30(UnkStruct_020a5c30 *p, unsigned long v)
{
    p->unk_94 = v;
}

unsigned long func_020a5c28(UnkStruct_020a5c28 *p)
{
    return p->unk_94;
}

void func_020a5c20(UnkStruct_020a5c20 *p, unsigned short v)
{
    p->unk_98 = v;
}

unsigned short func_020a5c18(UnkStruct_020a5c18 *p)
{
    return p->unk_98;
}

void func_020a5c10(UnkStruct_020a5c10 *p, unsigned long v)
{
    p->unk_9C = v;
}

unsigned long func_020a5c08(UnkStruct_020a5c08 *p)
{
    return p->unk_9C;
}

void func_020a5c00(int p0)
{
    *(int *) ((char *) (((int) (p0) + (156))) + (0)) = 4;
}

void func_020a5bf8(int p0, int v)
{
    *(int *) ((char *) p0 + 0xa0) = v;
}

int func_020a5bf0(int p0)
{
    return *(int *) ((char *) p0 + 0xa0);
}

void func_020a5be8(int p0)
{
    *(int *) ((char *) (((int) (p0) + (160))) + (0)) = 4;
}

void func_020a5be0(UnkStruct_020a5be0 *p, unsigned long v)
{
    p->unk_A4 = v;
}

unsigned long func_020a5bd8(UnkStruct_020a5bd8 *p)
{
    return p->unk_A4;
}

void func_020a5bd0(int p0)
{
    *(int *) ((char *) (((int) (p0) + (164))) + (0)) = 4;
}

void func_020a5bc4(char *base, int idx, int v)
{
    *(int *) (base + idx * 4 + 0xa8) = v;
}

int func_020a5bb8(char *base, int idx)
{
    return *(int *) (base + idx * 4 + 0xa8);
}

void func_020a5bac(void *r0, int r1)
{
    int *ptr;
    ptr = (int *) ((char *) r0 + (r1 << 2) + 0xa8);
    *ptr = 6;
}

void func_020a5b98(struct UnkStruct_020a5b98 *s)
{
    int i = 3;
    do {
        s->arr[i] = 6;
        i--;
    } while (i >= 0);
}

void func_020a5750(struct UnkStruct_020a5750_2 *self)
{
    struct UnkStruct_020a5750 *g;
    struct UnkStruct_020a5750 *h;
    struct Nm *r;
    struct Nm *nm;
    void *q;
    int n;
    int flag;
    int x;
    int f;
    unsigned long t;
    int m;
    unsigned long k;
    unsigned long e;
    unsigned long v;
    unsigned short mask;
    unsigned char c;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;

    g = (*(struct UnkStruct_020a5750 * *) &data_020ccf94);

    n = g->unk_64;
    if (func_020a5bb8((char *) self, n) == 0) {
        func_020a5748((UnkStruct_020a5748 *) self, 0);
        func_020a5bc4((char *) self, n, 1);
    }

    n = g->unk_64;
    if (func_020a5bb8((char *) self, n) == 1) {
        flag = 0;
        x = func_020b65c4();
        if (x != 0x2e && x != 0xc && x != 0xd && x != 0xe && x != 0x2f &&
            func_020b5e84((unsigned char *) func_020b5e10()) == 0x3f && data_021f42f0 == 0 && func_0203df10()) {
            flag = 1;
        }
        t = func_020a5bd8((UnkStruct_020a5bd8 *) self);
        if (flag) {
            func_020a5738((UnkStruct_020a5738 *) self, 0x28);
            func_020a5748((UnkStruct_020a5748 *) self, 0);
            if (n != 0) {
                func_020a76cc(&b0);
                func_020a76ac(&b0, 2, 4, (unsigned long) func_020a5bf0((int) self));
                h = (*(struct UnkStruct_020a5750 * *) &data_020ccf94);
                func_02073820((void *) h);
                func_020737f0((void *) h, (char *) (&b0), 1);
                func_02073770((void *) h, 0xc, 0);
                func_020a76c8(&b0);
            }
            func_020b8df0(t);
            func_020a5bc4((char *) self, n, 2);
            func_02073150(g, func_020740b4());
        } else {
            v = func_020a5740((UnkStruct_020a5740 *) self) + 1;
            if (v >= 0xa0) {
                if (n == 0) {
                    func_020a5bc4((char *) self, 0, 3);
                } else {
                    func_020a76cc(&b1);
                    func_020a76ac(&b1, 3, 4, (unsigned long) func_020a5bf0((int) self));
                    h = (*(struct UnkStruct_020a5750 * *) &data_020ccf94);
                    func_02073820((void *) h);
                    func_020737f0((void *) h, (char *) (&b1), 1);
                    func_02073770((void *) h, 0xc, 0);
                    func_020a5bc4((char *) self, n, 6);
                    func_020a76c8(&b1);
                }
                func_0206f5b0();
                func_020a5748((UnkStruct_020a5748 *) self, 0);
            } else {
                func_020a5748((UnkStruct_020a5748 *) self, v);
            }
            func_020b8e10(t);
        }
    }

    m = g->unk_64;
    x = func_020a5bb8((char *) self, m);
    if (x == 2) {
        func_020b8df0(func_020a5bd8((UnkStruct_020a5bd8 *) self));
    } else if (x == 4) {
        func_0203dee8();
        func_0206f5b0();
        func_020b8dd8();
        func_020a5738((UnkStruct_020a5738 *) self, 0);
        if (m != 0) {
            func_020a76cc(&b2);
            func_020a76ac(&b2, 6, 4, (unsigned long) func_020a5bf0((int) self));
            h = (*(struct UnkStruct_020a5750 * *) &data_020ccf94);
            func_02073820((void *) h);
            func_020737f0((void *) h, (char *) (&b2), 1);
            func_02073770((void *) h, 0xc, 0);
            func_020a76c8(&b2);
        }
        func_020a5bc4((char *) self, m, 6);
    } else if (x == 5) {
        k = func_020a5bd8((UnkStruct_020a5bd8 *) self);
        func_020b8df0(k);
        c = func_020a5730((UnkStruct_020a5730 *) (&data_021f4320));
        if (c != 0) {
            func_020a5738((UnkStruct_020a5738 *) (&data_021f4320), c - 1);
        }
        flag = 0;
        if (func_020a5730((UnkStruct_020a5730 *) self) != 0) {
            flag = 1;
        }
        if (!flag) {
            if (k == 0) {
                e = (unsigned long) func_020a5bf0((int) self);
                if (func_02098420(e + 3) == 0) {
                    flag = 1;
                    if (m == 0) {
                        x = func_020ec1f8();
                        mask = (unsigned short) (1 << e);
                        if (mask != (mask & x)) {
                            f = func_020732c0(g);
                            if ((f & 4) == 0) {
                                func_020732cc(g, f | 4);
                            }
                        }
                    }
                }
            } else if (k == 1) {
                func_020a5c30((UnkStruct_020a5c30 *) self, (unsigned long) func_020a5bf0((int) self));
            }
        }
        if (!flag) {
            func_020a5728((UnkStruct_020a5728 *) self, func_020a5bd8((UnkStruct_020a5bd8 *) self));
            func_020a13c4((unsigned long) func_020a5bf0((int) self));
            func_020b5ee4(func_020b5e10(), 0);
            if (func_020a5bd8((UnkStruct_020a5bd8 *) self) == 0) {
                nm = &data_021dc7aa;
                q = func_0209847c((unsigned long) func_020a5bf0((int) self) + 3);
                if (q != 0 && func_0208829c(func_02099688(q)) != 0 &&
                    ((r = func_020882ec((void *) func_02099688(q))), r->h == nm->h) && memcmp(r->rest, nm->rest, 0xc) == 0) {
                    func_020b6434(func_020b5e10(), 0x2f, 2, 2);
                } else {
                    if ((data_021f42f8 & 1) == 0) {
                        data_021f4314.unk_00 = 0x10000;
                        data_021f4314.unk_04 = 0;
                        data_021f4314.unk_08 = 0x5000;
                        __register_global_object((void *) (&data_021f4314), (((void *) func_020012dc)),
                                                 (void *) (&data_021f4308));
                        data_021f42f8 |= 1;
                    }
                    func_020b63f4(func_020b5e10(), 0xd, &data_021f4314, 0x800000, 0, 2, 2);
                }
            } else {
                func_020b6434(func_020b5e10(), 0x2e, 2, 3);
            }

            if (func_02073918((struct UnkStruct_020a5c38 *) g, 0)) {
                if (k == 0) {
                    func_020a18e8();
                } else if (k == 1) {
                    func_020a18c4();
                }
            } else {
                if (k == 0) {
                    func_020a18dc();
                } else if (k == 1) {
                    func_020a18b8();
                } else if (k == 2) {
                    func_020a18a0();
                    func_020a01e0(0);
                } else {
                    func_020a18a0();
                    func_020a01e0(1);
                }
            }

            if (m != 0) {
                func_020a76cc(&b3);
                func_020a76ac(&b3, 6, 4, (unsigned long) func_020a5bf0((int) self));
                h = (*(struct UnkStruct_020a5750 * *) &data_020ccf94);
                func_02073820((void *) h);
                func_020737f0((void *) h, (char *) (&b3), 1);
                func_02073770((void *) h, 0xc, 0);
                func_020a76c8(&b3);
            }
            func_020a5bc4((char *) self, m, 6);
        }
    }
}

void func_020a5748(UnkStruct_020a5748 *p, unsigned long v)
{
    p->unk_B8 = v;
}

unsigned long func_020a5740(UnkStruct_020a5740 *p)
{
    return p->unk_B8;
}

void func_020a5738(UnkStruct_020a5738 *p, unsigned char v)
{
    p->unk_BC = v;
}

unsigned char func_020a5730(UnkStruct_020a5730 *p)
{
    return p->unk_BC;
}

void func_020a5728(UnkStruct_020a5728 *p, unsigned long v)
{
    p->unk_C0 = v;
}

unsigned long func_020a5720(UnkStruct_020a5720 *p)
{
    return p->unk_C0;
}

void func_020a5718(UnkStruct_020a5718 *p, unsigned char v)
{
    p->unk_C4 = v;
}

unsigned char func_020a5710(UnkStruct_020a5710 *p)
{
    return p->unk_C4;
}
