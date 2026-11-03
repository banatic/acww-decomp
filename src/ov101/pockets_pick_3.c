/* pockets_pick_3: 48 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229d2c4 @ 0x0229d2c4, 0x38 bytes, Thumb
 * func_ov101_0229d29c @ 0x0229d29c, 0x28 bytes, Thumb
 * func_ov101_0229d26c @ 0x0229d26c, 0x30 bytes, Thumb
 * func_ov101_0229d240 @ 0x0229d240, 0x2c bytes, Thumb
 * func_ov101_0229d1f0 @ 0x0229d1f0, 0x50 bytes, Thumb
 * func_ov101_0229d1a8 @ 0x0229d1a8, 0x48 bytes, Thumb
 * func_ov101_0229d168 @ 0x0229d168, 0x40 bytes, Thumb
 * func_ov101_0229d134 @ 0x0229d134, 0x34 bytes, Thumb
 * func_ov101_0229d0f8 @ 0x0229d0f8, 0x3c bytes, Thumb
 * func_ov101_0229d0a8 @ 0x0229d0a8, 0x50 bytes, Thumb
 * func_ov101_0229d088 @ 0x0229d088, 0x20 bytes, Thumb
 * func_ov101_0229d054 @ 0x0229d054, 0x34 bytes, Thumb
 * func_ov101_0229cff0 @ 0x0229cff0, 0x64 bytes, Thumb
 * func_ov101_0229cfd4 @ 0x0229cfd4, 0x1c bytes, Thumb
 * func_ov101_0229cfa0 @ 0x0229cfa0, 0x34 bytes, Thumb
 * func_ov101_0229cf80 @ 0x0229cf80, 0x20 bytes, Thumb
 * func_ov101_0229cef8 @ 0x0229cef8, 0x88 bytes, Thumb
 * func_ov101_0229ceb4 @ 0x0229ceb4, 0x44 bytes, Thumb
 * func_ov101_0229ce50 @ 0x0229ce50, 0x64 bytes, Thumb
 * func_ov101_0229ce44 @ 0x0229ce44, 0xc bytes, Thumb
 * func_ov101_0229ce38 @ 0x0229ce38, 0xc bytes, Thumb
 * func_ov101_0229ce1c @ 0x0229ce1c, 0x1a bytes, Thumb
 * func_ov101_0229ce0c @ 0x0229ce0c, 0xe bytes, Thumb
 * func_ov101_0229cdd0 @ 0x0229cdd0, 0x3a bytes, Thumb
 * func_ov101_0229cd80 @ 0x0229cd80, 0x50 bytes, Thumb
 * func_ov101_0229cd40 @ 0x0229cd40, 0x3e bytes, Thumb
 * func_ov101_0229cd08 @ 0x0229cd08, 0x36 bytes, Thumb
 * func_ov101_0229ccd0 @ 0x0229ccd0, 0x38 bytes, Thumb
 * func_ov101_0229cc80 @ 0x0229cc80, 0x4e bytes, Thumb
 * func_ov101_0229cc50 @ 0x0229cc50, 0x2e bytes, Thumb
 * func_ov101_0229cc20 @ 0x0229cc20, 0x2e bytes, Thumb
 * func_ov101_0229cbec @ 0x0229cbec, 0x34 bytes, Thumb
 * func_ov101_0229cbbc @ 0x0229cbbc, 0x2e bytes, Thumb
 * func_ov101_0229cba0 @ 0x0229cba0, 0x1c bytes, Thumb
 * func_ov101_0229cb60 @ 0x0229cb60, 0x40 bytes, Thumb
 * func_ov101_0229cb44 @ 0x0229cb44, 0x1c bytes, Thumb
 * func_ov101_0229cb18 @ 0x0229cb18, 0x2a bytes, Thumb
 * func_ov101_0229caac @ 0x0229caac, 0x6c bytes, Thumb
 * func_ov101_0229ca58 @ 0x0229ca58, 0x54 bytes, Thumb
 * func_ov101_0229ca2c @ 0x0229ca2c, 0x2c bytes, Thumb
 * func_ov101_0229ca00 @ 0x0229ca00, 0x2c bytes, Thumb
 * func_ov101_0229c9d8 @ 0x0229c9d8, 0x28 bytes, Thumb
 * func_ov101_0229c970 @ 0x0229c970, 0x66 bytes, Thumb
 * func_ov101_0229c944 @ 0x0229c944, 0x2a bytes, Thumb
 * func_ov101_0229c90c @ 0x0229c90c, 0x36 bytes, Thumb
 * func_ov101_0229c8bc @ 0x0229c8bc, 0x50 bytes, Thumb
 * func_ov101_0229c878 @ 0x0229c878, 0x44 bytes, Thumb
 * func_ov101_0229c868 @ 0x0229c868, 0x10 bytes, Thumb
 */

typedef struct {
    char pad_00[0xb6];
    unsigned char unk_B6;
    char pad_B7[0x229c - 0xb7];
    char unk_229C;
} UnkStruct_0229d168;

typedef struct {
    char pad_00[0x229c];
    char unk_229C;
    char pad_229D[0x573];
    char unk_2810;
} UnkStruct_0229cff0;

typedef struct {
    char pad_00[0x9C];
    int word1;
    int word2;
    char pad_A4[0xB0 - 0xA4];
    unsigned char byte1;
    unsigned char byte2;
    char pad_B2[0xB9 - 0xB2];
    unsigned char byte3;
    char pad_BA[0x21B4 - 0xBA];
    char unk_21B4;
} UnkStruct_0229cef8;

typedef struct UnkStruct_0229ceb4 {
    char pad_00[0xaf];
    unsigned char unk_AF;
    char pad_B0[0xb2 - 0xaf - 1];
    char unk_B2;
    char pad_B3[0xb6 - 0xb2 - 1];
    unsigned char unk_B6;
    char pad_B7[0x21b4 - 0xb6 - 1];
    char unk_21B4[1];
} UnkStruct_0229ceb4;

struct UnkStruct_0229cb60 {
    char pad_00[0xf4];
    char unk_F4;
    char pad_F5[0xb54 - 0xf4 - 1];
    char unk_B54;
};

struct UnkStruct_0229ca58 {
    char pad_00[0xB1];
    unsigned char unk_B1;
    char pad_B2[1];
    unsigned char unk_B3;
    char pad_B4[0x2100];
    char unk_21B4;
};

struct Game {
    char pad_00[0xac];
    unsigned short unk_AC;
    unsigned char unk_AE;
    unsigned char unk_AF;
    char pad_B0[0x44];
    char unk_F4;
};

struct UnkStruct_0229c944 {
    unsigned char pad_00[0xac];
    unsigned short unk_AC;
    unsigned char unk_AE;
    unsigned char unk_AF;
};

extern int func_0208e484(void *);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_0200467c(int);
extern void func_ov101_0229c680(void *);
extern int func_ov002_02209f9c(void *p);
extern void func_ov101_0229c29c(int, int);
extern int func_ov002_02209f70(int);
extern void func_ov101_0229c28c(void *p, int n);
extern int func_ov002_02209d8c(void *);
extern int func_ov002_02208e28(char *);
extern int func_0206fe54(void);
extern void func_ov101_0229c6d4(char *);
extern int func_ov002_0220909c(char *addr);
extern void func_ov002_022096d8(char *addr, int val);
extern int func_ov002_02207d24(char *addr, int val);
extern int func_0208e4bc(char *addr);
extern void func_ov101_0229c6a0(char *obj);
extern int func_ov002_02208e18(void *addr);
extern void func_ov101_0229c5b8(void *addr);
extern int func_ov002_0220b8ac(void *, int);
extern void func_0208e5cc(void *);
extern int func_ov002_0220a700(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int a);
extern int func_ov002_0220a72c(void *p, int a);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov101_0229c4ac(void *p);
extern void func_ov101_0229c844(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov002_02207cf8(void *p);
extern void func_ov002_02207d00(void *p);
extern void func_ov094_022999cc(void);
extern void func_ov002_02209d68(void *, void *, void *);
extern int func_ov002_02209d38(void *, int, int, int);
extern void func_020b9ccc(void *p);
extern int func_ov094_0229aee8(int, int arg1, int arg2);
extern int func_ov094_0229a69c(int, int);
extern void func_ov094_0229aa14(int, int, int, int);
extern void func_ov094_0229a9b4(int, int);
extern int func_ov094_0229aba4(void *, int);
extern int func_ov094_0229ab90(int, int);
extern unsigned int func_0206f9cc(void);
extern void func_ov094_0229a888(char *p, int v);
extern int func_ov094_0229a8bc(char *a, int b);
extern int func_ov094_0229aaac(void *arg0, int arg1);
extern int func_ov094_0229aa84(char *addr, int val);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229ab1c(void *a, void *b);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229aafc(int, int);
extern void func_0208aa60(unsigned char *, int, int);
extern void func_ov094_0229abb8(unsigned char *, unsigned char *, int);
extern void func_ov002_02207cf0(void *p);
extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);
extern int func_ov002_02209d84(void *);
extern int func_ov002_02209d7c(void *);
extern void func_ov094_0229aa58(char *ptr, void *p);
extern void func_ov094_0229a99c(char *ptr, int a, int b);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_ov101_0229c2ac(void *p, int v);

void func_ov101_0229cf80(int arg);
void func_ov101_0229ceb4(UnkStruct_0229ceb4 *obj, int value);
void func_ov101_0229ce50(char *self, int a, int b);
int func_ov101_0229cd80(int r5, int r4);
void func_ov101_0229cd40(int r0, int r1, int r2, int r3);
int func_ov101_0229cd08(void *p, int n);
int func_ov101_0229ccd0(int a, int b);
int func_ov101_0229cc50(void *a, int b);
int func_ov101_0229cc20(char *a, int b);
int func_ov101_0229cbec(void *arg0, int arg1);
int func_ov101_0229cbbc(void *a, int b);
void func_ov101_0229cba0(void *arg);
void func_ov101_0229cb60(struct UnkStruct_0229cb60 *s, int arg1);
void func_ov101_0229ca58(struct UnkStruct_0229ca58 *self);
void func_ov101_0229ca00(char *p);
void func_ov101_0229c9d8(char *self);
void func_ov101_0229c970(struct Game *self, void *other);
void func_ov101_0229c944(struct UnkStruct_0229c944 *p, int a);
void func_ov101_0229c90c(void *self, int other);
void func_ov101_0229c8bc(unsigned char *self);
int func_ov101_0229c878(void *p);
int func_ov101_0229c868(void *p);

void func_ov101_0229d2c4(void *r0)
{
    if (func_0208e484((char *) r0 + 0x229c)) {
        func_ov002_0220a720((char *) r0 + 0x2810, 9);
        func_ov002_02208098(r0, 0x17);
        func_0200467c(0x28);
    }
}

void func_ov101_0229d29c(void *self)
{
    if (func_0208e484((char *) self + 0x229c)) {
        func_ov101_0229c680(self);
        func_ov002_02208098(self, 6);
    }
}

void func_ov101_0229d26c(void *p)
{
    if (func_ov002_02209f9c((char *) p + 0x229c)) {
        func_ov101_0229ceb4((UnkStruct_0229ceb4 *) p, (unsigned char) (*(unsigned char *) ((char *) p + 0xb3)));
        func_ov002_02208098(p, 0xe);
    }
}

void func_ov101_0229d240(void *p)
{
    if (func_0208e484((char *) p + 0x229c) != 0) {
        func_ov002_02208098(p, *((unsigned char *) ((char *) p + 0xb6)));
    }
    func_ov101_0229ca00((char *) p);
}

void func_ov101_0229d1f0(unsigned char *p)
{
    if (func_ov002_02209f9c((void *) (p + 0x229C)) == 0) {
        if (p[0xB3] == p[0xB5]) {
            func_ov101_0229cd80((int) p, (int) (*(
                       unsigned char *) ((char *) (((unsigned int) (((unsigned int) (((unsigned int) (p) + (0x0))) + (0x0))) +
                                                    (0xb5))) +
                                         0)));
            func_ov101_0229ca58((struct UnkStruct_0229ca58 *) p);
            func_ov002_02208098((void *) p, 6);
        } else {
            func_ov101_0229ce50((char *) p, (unsigned char) p[0xB5], 4);
        }
    } else {
        func_ov101_0229ca00((char *) p);
    }
}

void func_ov101_0229d1a8(int r0)
{
    if (func_ov002_02209f70(r0 + 0x229c) == 0) {
        func_ov101_0229c90c((void *) r0, (unsigned char) (*(unsigned char *) (r0 + 0xb5)));
        func_ov101_0229c29c(r0, 0x20);
        func_ov002_02208098((void *) r0, 0x11);
        func_ov101_0229ca58((struct UnkStruct_0229ca58 *) r0);
    } else {
        func_ov002_02208098((void *) r0, 6);
    }
}

void func_ov101_0229d168(UnkStruct_0229d168 *self)
{
    if (func_0208e484(&self->unk_229C)) {
        func_ov002_02208098(self, self->unk_B6);
    }
    if (func_ov002_02209f9c(&self->unk_229C)) {
        func_ov101_0229c28c(self, 0x20);
        func_ov101_0229ca00((char *) self);
    }
}

void func_ov101_0229d134(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x2284)) {
        func_ov101_0229c944((struct UnkStruct_0229c944 *) self, (unsigned char) (*(unsigned char *) ((char *) self + 0xb2)));
        func_ov101_0229cf80((int) self);
    } else {
        func_ov101_0229c9d8((char *) self);
    }
}

void func_ov101_0229d0f8(char *param)
{
    if (func_ov002_02208e28(param + 0x2300)) {
        if (func_0206fe54()) {
            func_ov101_0229c6d4(param);
            func_ov002_02208098((void *) param, 8);
        } else {
            func_ov002_02208098((void *) param, 4);
        }
    }
}

void func_ov101_0229d0a8(char *obj)
{
    if (func_ov002_0220909c(obj + 0x2300) == 0) {
        return;
    }
    func_ov002_022096d8(obj + 0x2300, 0);
    func_ov002_02207d24(obj + 0x21b4, 1);
    if (func_0208e4bc(obj + 0x229c) != 0) {
        func_ov101_0229c6a0(obj);
    }
    func_ov002_02208098((void *) obj, 0x15);
}

void func_ov101_0229d088(void *obj)
{
    if (func_ov002_02208e18((char *) obj + 0x2300) != 0) {
        func_ov101_0229c5b8(obj);
    }
}

void func_ov101_0229d054(unsigned char *param)
{
    if (func_ov002_0220b8ac(param + 0x26f4, 0) != 0) {
        func_ov002_02208098(param, *(param + 0xb6));
        func_0208e5cc(param + 0x229c);
    }
}

void func_ov101_0229cff0(UnkStruct_0229cff0 *p)
{
    if (func_ov002_0220a700(&p->unk_2810) != 0) {
        if (func_0208e4bc((char *) (&p->unk_229C)) != 0) {
            int r4, r6, r2;
            r4 = func_ov002_0220a6e0(&p->unk_2810);
            r6 = func_ov002_0220a768(&p->unk_2810, -1);
            r2 = func_ov002_0220a72c(&p->unk_2810, -1);
            func_ov002_0220a0b4(&p->unk_229C, r4 + r6, r4 + r2);
        }
    } else {
        func_ov101_0229c4ac(p);
    }
}

void func_ov101_0229cfd4(void *p)
{
    func_ov101_0229c844(p);
    func_ov101_0229cba0(p);
    func_ov002_02208098(p, 0);
}

void func_ov101_0229cfa0(void *self)
{
    unsigned char *p = (unsigned char *) self;
    p[0xb1] = 0x10;
    func_ov101_0229c8bc((unsigned char *) self);
    func_ov002_02207fc0(self);
    func_ov101_0229ca58((struct UnkStruct_0229ca58 *) self);
    func_ov002_02208098(self, 6);
    func_ov101_0229cb60((struct UnkStruct_0229cb60 *) self, (unsigned char) p[0xb3]);
}

void func_ov101_0229cf80(int arg)
{
    if (func_0206fe60() != 0) {
        func_ov101_0229cfd4((void *) arg);
    } else {
        func_ov101_0229cfa0((void *) arg);
    }
}

void func_ov101_0229cef8(UnkStruct_0229cef8 *self, int val)
{
    unsigned char a;
    unsigned char b;
    self->byte1 = val;
    func_ov002_02208098((void *) self, 1);
    a = data_021f6c58;
    b = data_021f6c54;
    self->word1 = func_ov101_0229cd08((void *) self, self->byte1) - a;
    self->word2 = func_ov101_0229ccd0((int) self, self->byte1) - b;
    self->byte2 = val;
    func_ov002_02207cf8(&self->unk_21B4);
    func_ov002_02207d00(&self->unk_21B4);
    self->byte3 = 2;
    if (func_ov101_0229cc50((void *) self, val) == 0) {
        func_ov094_022999cc();
    }
}

void func_ov101_0229ceb4(UnkStruct_0229ceb4 *obj, int value)
{
    obj->unk_B2 = value;
    func_ov002_02207d24((char *) obj->unk_21B4, 1);
    func_ov101_0229c970((struct Game *) obj, (void *) value);
    if (obj->unk_AF == 1) {
        obj->unk_B6 = 7;
    }
    func_ov101_0229ca00((char *) obj);
}

void func_ov101_0229ce50(char *self, int a, int b)
{
    int res1, res2;

    self[0xb2] = (char) a;
    func_ov002_02209d68(self + 0x2284, *(void **) (self + 0xa4), *(void **) (self + 0xa8));
    res1 = func_ov101_0229cd08(self, a);
    res2 = func_ov101_0229ccd0((int) self, a);
    func_ov002_02209d38(self + 0x2284, res1, res2, b);
    func_ov002_02209d8c(self + 0x2284);
    func_ov101_0229c9d8((char *) self);
    func_ov002_02208098(self, 0x12);
}

void func_ov101_0229ce44(void *p)
{
    func_020b9ccc((char *) p + 0xbc);
}

int func_ov101_0229ce38(int arg0, unsigned int arg1)
{
    if (arg1 > 14) {
        return 0;
    }
    return 1;
}

int func_ov101_0229ce1c(int a1, int a2)
{
    int r4;
    int result;

    r4 = a2;
    if (func_ov101_0229ce38(a1, a2) != 0) {
        result = (unsigned char) r4;
    } else {
        result = 0;
    }
    return result;
}

unsigned char func_ov101_0229ce0c(int unused, unsigned int b)
{
    if (b <= 14) {
        return (unsigned char) b;
    } else {
        return 16;
    }
}

int func_ov101_0229cdd0(int a, int b, int c, int d)
{
    int v;

    v = func_ov094_0229aee8(a + 0xf4, b, c);
    if (v == 0x23) {
        goto ret10;
    }
    if (d && func_ov094_0229a69c(a + 0xf4, v) != 0) {
        return 0x10;
    }
    return (int) func_ov101_0229ce0c(a, v);
ret10:
    return 0x10;
}

int func_ov101_0229cd80(int r5, int r4)
{
    int r6;
    int r3;
    int r0;
    int r1;
    int r2;

    r0 = func_ov101_0229ce38(r5, r4);
    if (r0 != 0) {
        r0 = r5;
        r1 = r4;
        r6 = func_ov101_0229cbec((void *) r0, r1);
        if (r6 != 0x0000fff1) {
            r0 = r5;
            r1 = r4;
            r3 = func_ov101_0229cbbc((void *) r0, r1);
            r0 = r5;
            r1 = r5;
            r1 += 0xb2;
            r1 = *(unsigned char *) r1;
            r2 = r6;
            func_ov101_0229cd40(r0, r1, r2, r3);
        }
        r0 = r5;
        r1 = r4;
        func_ov101_0229c944((struct UnkStruct_0229c944 *) r0, r1);
        r0 = 1;
    } else {
        r0 = 0;
    }
    return r0;
}

void func_ov101_0229cd40(int r0, int r1, int r2, int r3)
{
    int r4 = r0;
    int r5 = r1;
    int r6 = r2;
    int r7 = r3;

    if (func_ov101_0229ce38(r0, r1) != 0) {
        r5 = func_ov101_0229ce1c(r4, r5);
        func_ov094_0229aa14(r4 + 0xf4, r5, r6, r7);
        func_ov094_0229a9b4(r4 + 0xf4, r5);
    }
}

int func_ov101_0229cd08(void *p, int n)
{
    if (func_ov101_0229ce38((int) (p), (unsigned int) (n))) {
        int tmp = func_ov101_0229ce1c((int) p, n);
        p = (void *) ((char *) p + 0xf4);
        return func_ov094_0229aba4(p, tmp);
    } else {
        if (n == 0xf) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}

int func_ov101_0229ccd0(int a, int b)
{
    int result;
    if (func_ov101_0229ce38(a, b)) {
        result = func_ov094_0229ab90(a + 0xf4, func_ov101_0229ce1c(a, b)) - 0x10;
    } else if (b == 0xf) {
        result = 0xb6;
    } else {
        result = 0;
    }
    return result;
}

void func_ov101_0229cc80(char *a)
{
    unsigned char i;
    int b;
    unsigned int mask;
    int ret;

    mask = func_0206f9cc();
    for (i = 0, b = 0; i <= 14; i++, b++) {
        if (func_ov101_0229cc20(a, (unsigned char) i) != 0) {
            continue;
        }
        if (mask & (1 << b)) {
            continue;
        }
        ret = func_ov101_0229ce1c((int) a, (unsigned char) i);
        func_ov094_0229a888(a + 0xf4, ret);
    }
}

int func_ov101_0229cc50(void *a, int b)
{
    if (func_ov101_0229ce38((int) a, b)) {
        int r = func_ov101_0229ce1c((int) a, b);
        return func_ov094_0229a8bc((char *) a + 0xf4, r);
    }
    return 0;
}

int func_ov101_0229cc20(char *a, int b)
{
    if (func_ov101_0229ce38((int) a, b)) {
        return func_ov094_0229a69c((int) (a + 0xf4), func_ov101_0229ce1c((int) a, b));
    }
    return 1;
}

int func_ov101_0229cbec(void *arg0, int arg1)
{
    if (func_ov101_0229ce38((int) arg0, arg1) != 0) {
        int tmp = func_ov101_0229ce1c((int) arg0, arg1);
        return func_ov094_0229aaac((char *) arg0 + 0xf4, tmp);
    }
    return 0x0000fff1;
}

int func_ov101_0229cbbc(void *a, int b)
{
    if (func_ov101_0229ce38((int) a, b)) {
        return func_ov094_0229aa84((char *) a + 0xf4, func_ov101_0229ce1c((int) a, b));
    } else {
        return 0xf1;
    }
}

void func_ov101_0229cba0(void *arg)
{
    void *p = arg;
    func_ov094_0229ab5c((char *) p + 0xf4);
    func_ov094_0229b98c((char *) p + 0xb54);
}

void func_ov101_0229cb60(struct UnkStruct_0229cb60 *s, int arg1)
{
    char *tmp;

    if (func_ov101_0229ce38((int) s, arg1)) {
        tmp = (char *) func_ov101_0229ce1c((int) s, arg1);
        func_ov094_0229ab1c(&s->unk_F4, tmp);
        func_ov094_0229b98c(&s->unk_B54);
    } else {
        func_ov101_0229cba0(s);
    }
}

void func_ov101_0229cb44(void *self)
{
    func_ov094_0229ab0c((char *) self + 0xf4);
    func_ov094_0229b944((char *) self + 0xb54);
}

void func_ov101_0229cb18(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;

    if (func_ov101_0229ce38(r0, r1) != 0) {
        int r0_2 = r5;
        int r1_2 = r4;
        int r0_3 = func_ov101_0229ce1c(r0_2, r1_2);
        int r1_3 = r0_3;
        r5 += 0xf4;
        func_ov094_0229aafc(r5, r1_3);
    }
}

void func_ov101_0229caac(unsigned char *p)
{
    int ret1;
    int v1;
    int ret2;
    int v2;
    int ret3;

    ret1 = func_ov101_0229cd08((void *) p, (unsigned char) p[0xb1]);
    v1 = ret1 - 0x6d;
    ret2 = func_ov101_0229ccd0((int) p, (unsigned char) p[0xb1]);
    v2 = ret2 - 0x78;
    if (func_0206fe54() != 0) {
        v2 -= 8;
    }
    func_0208aa60(p + 0x21b4, v1, v2);
    if (func_ov101_0229ce38((int) p, (unsigned char) p[0xb1]) != 0) {
        ret3 = func_ov101_0229ce1c((int) p, (unsigned char) p[0xb1]);
        func_ov094_0229abb8(p + 0xf4, p + 0x21b4, ret3);
    }
}

void func_ov101_0229ca58(struct UnkStruct_0229ca58 *self)
{
    if (func_ov101_0229ce38((int) self, (unsigned char) self->unk_B3)) {
        if (func_ov101_0229cc20((char *) self, (unsigned char) self->unk_B3)) {
            func_ov002_02207cf0(&self->unk_21B4);
        } else {
            self->unk_B1 = self->unk_B3;
            func_ov002_02207cf8(&self->unk_21B4);
        }
    } else {
        func_ov002_02207cf0(&self->unk_21B4);
    }
}

void func_ov101_0229ca2c(void *self)
{
    unsigned int tmp;
    unsigned int tmp2;

    tmp = *(unsigned int *) ((char *) self + 0x9c) + data_021f6c58;
    *(unsigned int *) ((char *) self + 0xa4) = tmp;

    tmp2 = *(unsigned int *) ((char *) self + 0xa0) + data_021f6c54;
    *(unsigned int *) ((char *) self + 0xa8) = tmp2;
}

void func_ov101_0229ca00(char *p)
{
    *(int *) (p + 0xa4) = func_ov002_02209f3c(p + 0x229c) - 2;
    *(int *) (p + 0xa8) = func_ov002_02209f14(p + 0x229c) - 4;
}

void func_ov101_0229c9d8(char *self)
{
    *(int *) (self + 0xa4) = func_ov002_02209d84(self + 0x2284);
    *(int *) (self + 0xa8) = func_ov002_02209d7c(self + 0x2284);
}

void func_ov101_0229c970(struct Game *self, void *other)
{
    if (func_ov101_0229ce38((int) self, (unsigned int) other)) {
        void *p = (void *) func_ov101_0229ce1c((int) self, (int) other);
        self->unk_AF = 1;
        self->unk_AC = (unsigned short) func_ov094_0229aaac((void *) (&self->unk_F4), (int) p);
        self->unk_AE = (unsigned char) func_ov094_0229aa84(&self->unk_F4, (int) p);
        func_ov094_0229aa58(&self->unk_F4, p);
        func_ov094_0229a99c(&self->unk_F4, self->unk_AC, self->unk_AE);
    }
}

void func_ov101_0229c944(struct UnkStruct_0229c944 *p, int a)
{
    if (p->unk_AF == 1) {
        func_ov101_0229cd40((int) p, a, (unsigned short) p->unk_AC, (unsigned char) p->unk_AE);
    }
    p->unk_AF = 0;
}

void func_ov101_0229c90c(void *self, int other)
{
    if (((unsigned char *) self)[0xaf] == 1) {
        unsigned short a = *(unsigned short *) ((unsigned char *) self + 0xac);
        unsigned char b = ((unsigned char *) self)[0xae];
        func_ov101_0229c970((struct Game *) self, (void *) other);
        func_ov101_0229cd40((int) self, other, (unsigned short) a, (unsigned char) b);
    }
}

void func_ov101_0229c8bc(unsigned char *self)
{
    int a, b;

    a = func_ov101_0229c878((void *) self);
    b = func_ov101_0229c868((void *) self);
    func_ov002_0220a0b4((void *) (self + 0x229c), a, b);
    if (self[0xb3] == 15) {
        func_ov002_0220a374(self + 0x229c, 7);
    } else {
        func_ov002_0220a374(self + 0x229c, 1);
    }
    func_ov101_0229c680((void *) self);
}

int func_ov101_0229c878(void *p)
{
    int r = func_ov101_0229cd08(p, (unsigned char) (*(unsigned char *) ((char *) p + 0xb3)));
    if (func_ov101_0229c2ac(p, 0x10)) {
        r += 0x100;
    } else if (func_ov101_0229c2ac(p, 8)) {
        r -= 0x100;
    }
    return r + 8;
}

int func_ov101_0229c868(void *p)
{
    return func_ov101_0229ccd0((int) p, (unsigned char) (((unsigned char *) p)[0xB3]));
}
