/* tune_editor_2: 18 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_02299f6c @ 0x02299f6c, 0x18 bytes, Thumb
 * func_ov143_02299f48 @ 0x02299f48, 0x24 bytes, Thumb
 * func_ov143_02299ed8 @ 0x02299ed8, 0x6e bytes, Thumb
 * func_ov143_02299e18 @ 0x02299e18, 0xc0 bytes, Thumb
 * func_ov143_02299c14 @ 0x02299c14, 0x202 bytes, Thumb
 * func_ov143_02299bd0 @ 0x02299bd0, 0x44 bytes, Thumb
 * func_ov143_02299ba0 @ 0x02299ba0, 0x30 bytes, Thumb
 * func_ov143_02299b70 @ 0x02299b70, 0x30 bytes, Thumb
 * func_ov143_02299b2c @ 0x02299b2c, 0x44 bytes, Thumb
 * func_ov143_02299b04 @ 0x02299b04, 0x28 bytes, Thumb
 * func_ov143_02299ad4 @ 0x02299ad4, 0x30 bytes, Thumb
 * func_ov143_02299a9c @ 0x02299a9c, 0x38 bytes, Thumb
 * func_ov143_02299a64 @ 0x02299a64, 0x38 bytes, Thumb
 * func_ov143_02299a38 @ 0x02299a38, 0x2c bytes, Thumb
 * func_ov143_022999a4 @ 0x022999a4, 0x94 bytes, Thumb
 * func_ov143_02299924 @ 0x02299924, 0x80 bytes, Thumb
 * func_ov143_022998dc @ 0x022998dc, 0x48 bytes, Thumb
 * func_ov143_02299880 @ 0x02299880, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x8D];
    unsigned char unk_8D;
    char pad_8E[0x10];
    unsigned char unk_9E;
    char pad_9F[0xD];
    char unk_AC;
} UnkStruct_02299f48;

typedef struct {
    int x;
    int y;
} TempStruct;

typedef struct UnkStruct_02299e18 {
    u8 pad_00[0x9a];
    u16 unk_9A;
    u8 pad_9C[0xa0 - 0x9a - 2];
    u8 *unk_A0;
    u8 unk_A4;
    u8 unk_A5;
    u8 pad_A6[2];
    int unk_A8;
} UnkStruct_02299e18;

typedef struct {
    unsigned char pad_00[0xa4];
    volatile unsigned char unk_A4;
} UnkStruct_02299c14;

struct UnkStruct_02299b04 {
    char pad_00[0x9a];
    short unk_9A;
};

typedef struct {
    unsigned char pad_00[0x9f];
    volatile unsigned char idx;
} func_ov143_02299a64_Struct;

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char *array;
} UnkStruct_02299880;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *p);
extern void func_ov143_022996a4(void *obj, TempStruct *out, int idx);
extern int func_0206fe60(void);
extern u8 data_021f6c54;
extern void func_0206e9ac(u8 v);
extern void func_0200467c(int a);
extern void func_ov143_0229a230(UnkStruct_02299e18 *self);
extern void func_ov143_0229a200(UnkStruct_02299e18 *self);
extern void func_ov143_0229a404(UnkStruct_02299e18 *self);
extern void func_ov143_0229a3e0(UnkStruct_02299e18 *self);
extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov143_02299650(void *obj, int);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov143_02299630(void *obj, int);
extern void func_ov143_02299640(void *self, int a);
extern void func_0206fdd4(void *p, int a, int b, int c, int d, int e);
extern void func_0206ea10(int a);
extern void func_ov143_0229a014(void *a);
extern void func_ov143_0229a2e0(void *p);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov002_02207e9c(void *p, int x, int y);
extern void func_ov143_02299664(int);
extern void func_02070b84(void *);
extern void *func_02089300(int p1, void *p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9);
extern void func_02088df8(int p1, void *p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12);
extern void *data_ov143_0229b178[];
extern unsigned char data_ov143_0229af08[];
extern unsigned char data_ov143_0229b038[];
extern unsigned char data_ov143_0229b050[];
extern int func_ov143_022997d8(int, int);
extern int func_020896b8(int, void *, int, int, int, int, int);
extern int data_ov143_0229af90;

void func_ov143_02299b2c(void *s);
void func_ov143_02299ad4(void *p);

void func_ov143_02299f6c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0xac);
    func_ov002_02208098(self, 5);
}

void func_ov143_02299f48(UnkStruct_02299f48 *p)
{
    func_ov002_0220a164(&p->unk_AC);
    p->unk_9E = p->unk_8D;
    func_ov002_02208098(p, 6);
}

int func_ov143_02299ed8(void *obj, int b, int c)
{
    int i;
    TempStruct tmp;
    for (i = 0; i < 16; i++) {
        func_ov143_022996a4(obj, &tmp, i);
        if (tmp.x > b || tmp.x + 0x14 <= b || tmp.y > c || tmp.y + 0x12 <= c) {
            continue;
        }
        return (unsigned char) i;
    }
    if (b >= 0 && b < 0x38 && c >= 0x90 && c < 0xac) {
        return 0x10;
    }
    if (b >= 0x60 && b < 0xb0 && c >= 0x90 && c < 0xb8) {
        return 0x11;
    }
    return 0x16;
}

int func_ov143_02299e18(UnkStruct_02299e18 *self, unsigned int p)
{
    if (p <= 0xf) {
        self->unk_9A = (u16) p;
        self->unk_A4 = (u8) p;
        if (func_0206fe60() != 0) {
            self->unk_A8 = data_021f6c54;
            self->unk_A5 = (u8) func_ov143_022997d8((int) self, (u8) self->unk_A0[p]);
            func_ov002_02208098((void *) self, 1);
        } else {
            func_ov002_02208098((void *) self, 3);
        }
        func_0206e9ac(self->unk_A0[p]);
        return 1;
    }

    switch (p - 0x10) {
        case 0:
            func_ov143_02299ad4((void *) self);
            func_0200467c(0x2a);
            return 1;
        case 1:
            func_ov143_02299b2c((void *) self);
            return 1;
        case 2:
            func_ov143_0229a230(self);
            return 1;
        case 3:
            func_ov143_0229a200(self);
            return 1;
        case 4:
            func_ov143_0229a404(self);
            return 1;
        case 5:
            func_ov143_0229a3e0(self);
            return 1;
    }
    return 0;
}

int func_ov143_02299c14(UnkStruct_02299c14 *o, void *in)
{
    unsigned int st;
    int n;

    if (in == 0) {
        return 0;
    }
    st = o->unk_A4;
    if (st < 8) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_A4 = o->unk_A4 + 8;
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->unk_A4 != 0) {
                o->unk_A4 = o->unk_A4 - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            o->unk_A4 = o->unk_A4 + 1;
        }
    } else if (st >= 8 && st <= 0xf) {
        if (func_ov002_022088bc(in) != 0) {
            n = o->unk_A4 - 8;
            if (n < 2) {
                o->unk_A4 = 0x10;
            } else if (n < 6) {
                o->unk_A4 = 0x11;
            } else {
                o->unk_A4 = 0x12;
            }
        } else if (func_ov002_022088cc(in) != 0) {
            o->unk_A4 = o->unk_A4 - 8;
        } else if (func_ov002_022088ac(in) != 0) {
            o->unk_A4 = o->unk_A4 - 1;
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->unk_A4 < 0xfU) {
                o->unk_A4 = o->unk_A4 + 1;
            }
        }
    } else {
        switch (st) {
            case 0x10:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 8;
                } else if (func_ov002_0220889c(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
            case 0x11:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0xb;
                } else if (func_ov002_0220889c(in) != 0) {
                    o->unk_A4 = 0x12;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x10;
                }
                break;
            case 0x12:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0xe;
                } else if (func_ov002_022088bc(in) != 0) {
                    o->unk_A4 = 0x13;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
            case 0x13:
                if (func_ov002_022088cc(in) != 0) {
                    o->unk_A4 = 0x12;
                } else if (func_ov002_022088ac(in) != 0) {
                    o->unk_A4 = 0x11;
                }
                break;
        }
    }
    if (st != o->unk_A4) {
        return 1;
    }
    return 0;
}

void func_ov143_02299bd0(void *obj)
{
    if (func_ov143_02299650(obj, 4)) {
        if (func_020b9bbc((char *) obj + 0x119c, (char *) obj + 0x099c, 4, 0x800, 0)) {
            func_ov143_02299630(obj, 4);
        }
    }
}

void func_ov143_02299ba0(void *self, int param2)
{
    func_ov143_02299640(self, 4);
    func_0206fdd4((char *) self + 0x99c, 0xc, 0x12, 0x15, 0x16, param2);
}

void func_ov143_02299b70(void *a, int b)
{
    func_ov143_02299640(a, 4);
    func_0206fdd4((char *) a + 0x99c, 0, 0x11, 9, 0x17, b);
}

void func_ov143_02299b2c(void *s)
{
    func_0206ea10(0x190);
    *(signed short *) ((char *) s + 0x9a) = -1;
    func_ov002_02208098(s, 0xa);
    func_ov143_02299640(s, 2);
    func_ov143_02299640(s, 8);
    func_ov143_02299ba0(s, 4);
    func_ov143_0229a014(s);
}

void func_ov143_02299b04(struct UnkStruct_02299b04 *p)
{
    func_ov143_02299630(p, 2);
    p->unk_9A = -1;
    func_ov143_0229a2e0(p);
    func_ov143_02299ba0(p, 3);
}

void func_ov143_02299ad4(void *p)
{
    int zero;

    func_ov143_02299b70(p, 6);
    func_ov143_0229a014(p);
    func_ov002_02208090(p, 4);
    func_ov002_022080a0(p, 1);
    zero = 0;
    func_ov002_02207e9c(p, zero, zero);
}

void func_ov143_02299a9c(int r0)
{
    int r4 = r0;
    *(unsigned char *) (r4 + 0xa4) = 0x10;
    func_ov002_02208098((void *) r4, 9);
    func_ov002_02207e9c((void *) r4, 0, 0);
    func_ov002_02208090((void *) r4, 6);
    func_ov143_02299b70((void *) r4, 5);
    func_ov143_02299664(r4);
}

void *func_ov143_02299a64(func_ov143_02299a64_Struct *obj)
{
    if (obj->idx >= 16) {
        return (void *) ((char *) obj + 0x930);
    } else {
        obj->idx = obj->idx + 1;
        return (void *) ((char *) obj + 0x2dc + ((obj->idx - 1) * 0x6c));
    }
}

void func_ov143_02299a38(void *arg0)
{
    int i;
    char *p = (char *) arg0 + 0x9f;
    *p = 0;
    for (i = 0; i < 16; i++) {
        func_02070b84((char *) arg0 + 0x2dc + i * 0x6c);
    }
}

void func_ov143_022999a4(int a, unsigned int b, int c, int d)
{
    void *p;
    int result;
    int diff;
    unsigned int field;
    void *ptr;

    p = data_ov143_0229b178[b];
    result = func_ov143_022997d8(a, b);
    diff = d - (result << 1);

    if (b == 15) {
        func_02089300(1, data_ov143_0229af08, c - 0x5c, diff - 0x18, -1, 2, 0x1000, 0xeaab, 0);
    } else {
        field = (*(unsigned int *) ((char *) p + 0x14) << 16) >> 28;
        if (b < 6 || b == 14) {
            ptr = data_ov143_0229b038;
        } else {
            ptr = data_ov143_0229b050;
        }
        func_02088df8(1, ptr, c, diff, field, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void func_ov143_02299924(int a0, int a1, int a2, int a3)
{
    char *p = (char *) data_ov143_0229b178[a1];
    int ret = func_ov143_022997d8(a0, a1);
    int y = a3 - (ret << 1);

    func_020896b8(1, p, a2, y, 13, 2, 0);
    func_020896b8(1, p + 8, a2, y, 13, 2, 0);
    func_02088df8(1, p + 16, a2, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov143_022998dc(int a, int b, int c, int d)
{
    int t = d - 2 * func_ov143_022997d8(a, b);
    func_02088df8(1, (void *) (((int *) data_ov143_0229b178)[b]), c, t, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov143_02299880(UnkStruct_02299880 *a, int b, int c, int d)
{
    if (func_ov143_02299650((void *) a, 2) != 0) {
        func_ov143_022999a4((int) a, (unsigned char) a->array[b], c, d);
    } else {
        func_ov143_02299924((int) a, (unsigned char) a->array[b], c, d);
    }
    func_020896b8(1, &data_ov143_0229af90, c, d, -1, -1, 0);
}
