/* letter_storage: 34 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229cd7c @ 0x0229cd7c, 0x20 bytes, Thumb
 * func_ov105_0229cd5c @ 0x0229cd5c, 0x20 bytes, Thumb
 * func_ov105_0229cd30 @ 0x0229cd30, 0x2c bytes, Thumb
 * func_ov105_0229ccf4 @ 0x0229ccf4, 0x3c bytes, Thumb
 * func_ov105_0229cca8 @ 0x0229cca8, 0x4c bytes, Thumb
 * func_ov105_0229cc5c @ 0x0229cc5c, 0x4c bytes, Thumb
 * func_ov105_0229cbe0 @ 0x0229cbe0, 0x7c bytes, Thumb
 * func_ov105_0229cbb0 @ 0x0229cbb0, 0x30 bytes, Thumb
 * func_ov105_0229cadc @ 0x0229cadc, 0xd4 bytes, Thumb
 * func_ov105_0229ca8c @ 0x0229ca8c, 0x50 bytes, Thumb
 * func_ov105_0229c9ac @ 0x0229c9ac, 0xe0 bytes, Thumb
 * func_ov105_0229c8b4 @ 0x0229c8b4, 0xf8 bytes, Thumb
 * func_ov105_0229c888 @ 0x0229c888, 0x2c bytes, Thumb
 * func_ov105_0229c82c @ 0x0229c82c, 0x5c bytes, Thumb
 * func_ov105_0229c758 @ 0x0229c758, 0xd4 bytes, Thumb
 * func_ov105_0229c734 @ 0x0229c734, 0x24 bytes, Thumb
 * func_ov105_0229c710 @ 0x0229c710, 0x24 bytes, Thumb
 * func_ov105_0229c6a0 @ 0x0229c6a0, 0x70 bytes, Thumb
 * func_ov105_0229c698 @ 0x0229c698, 0x8 bytes, Thumb
 * func_ov105_0229c694 @ 0x0229c694, 0x2 bytes, Thumb
 * func_ov105_0229c668 @ 0x0229c668, 0x2c bytes, Thumb
 * func_ov105_0229c62c @ 0x0229c62c, 0x3c bytes, Thumb
 * func_ov105_0229c5fc @ 0x0229c5fc, 0x30 bytes, Thumb
 * func_ov105_0229c55c @ 0x0229c55c, 0xa0 bytes, Thumb
 * func_ov105_0229c4cc @ 0x0229c4cc, 0x90 bytes, Thumb
 * func_ov105_0229c490 @ 0x0229c490, 0x3c bytes, Thumb
 * func_ov105_0229c438 @ 0x0229c438, 0x58 bytes, Thumb
 * func_ov105_0229c3ec @ 0x0229c3ec, 0x4c bytes, Thumb
 * func_ov105_0229c3c8 @ 0x0229c3c8, 0x24 bytes, Thumb
 * func_ov105_0229c3ac @ 0x0229c3ac, 0x1c bytes, Thumb
 * func_ov105_0229c354 @ 0x0229c354, 0x58 bytes, Thumb
 * func_ov105_0229c340 @ 0x0229c340, 0x12 bytes, Thumb
 * func_ov105_0229c330 @ 0x0229c330, 0xe bytes, Thumb
 * func_ov105_0229c320 @ 0x0229c320, 0xe bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229cca8 {
    char pad_00[0x8d];
    unsigned char byte_at_8d;
    char pad_8E[0x22e];
    unsigned char byte_at_2bc;
    unsigned char byte_at_2bd;
    char pad_2BE[0x20fe];
    unsigned int unk_23BC;
    char pad_23C0[0xe4];
    unsigned int unk_24A4;
};

typedef struct {
    char pad_00[0x2be];
    unsigned char unk_2BE;
} UnkStruct_ov105_0229cc5c;

typedef struct UnkStruct_0229cbe0 {
    unsigned char pad_00[0x2bb];
    unsigned char unk_2BB;
    unsigned char pad_2BC[0x2100];
    unsigned char arr_23bc[0x14c];
    unsigned char arr_2508[0x3e8];
    unsigned char arr_28f0[1];
} UnkStruct_0229cbe0;

typedef struct UnkStruct_0229c758 {
    unsigned char pad_00[0x2ba];
    unsigned char unk_2BA;
    unsigned char pad_2BB[0x21e9];
    unsigned char unk_24A4;
} UnkStruct_0229c758;

typedef struct {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    char pad_B4[0x2bb - 0xb4];
    unsigned char unk_2BB;
} UnkStruct_0229c6a0;

struct UnkStruct_0229c55c {
    unsigned char pad_00[0xa0];
    unsigned char *ptr;
    unsigned char pad_A4[0x21c];
    unsigned char byte;
};

struct UnkStruct_0229c438 {
    char pad_00[0x2c0];
    unsigned char unk_2C0;
};

struct UnkStruct_0229c3ec {
    char pad_00[0x8c];
    unsigned char unk_8C;
    char pad_8D[0x2c0 - 0x8d];
    unsigned char unk_2C0;
    char pad_2C1[0x23bc - 0x2c1];
    unsigned char unk_23BC[1];
};

struct UnkStruct_0229c330 {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *ptr);
extern void func_ov002_0220a374(void *ptr, int size);
extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov105_0229db14(void *p);
extern void func_ov002_02208c58(char *dst, char *src, int a);
extern int func_ov105_0229d530(void *self, unsigned char b);
extern int func_ov105_0229d4c4(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov105_0229cdbc(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208d30(void *ptr, int a);
extern int func_ov105_0229d59c(int a, int b);
extern int func_0206fe54(void);
extern int func_ov002_02208d4c(void *ptr, int a, int b);
extern int func_02065ec0(int a);
extern int func_02065f18(int a);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov105_0229d76c(void *, unsigned char);
extern void func_ov002_0220a314(void *);
extern int func_ov105_0229d75c(u8 *, unsigned char);
extern void func_ov002_0220a2b4(void *ptr);
extern int func_ov105_0229d73c(UnkStruct_0229c758 *self, unsigned char field);
extern int func_ov105_0229d750(UnkStruct_0229c758 *self, unsigned char field);
extern void func_0208e4c0(void *ptr, int val);
extern void func_ov002_02208090(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_0208f0c4(void *p, int n);
extern void func_0200467c(int cmd);
extern void func_ov105_0229d0f8(void *obj, unsigned char b);
extern void func_ov094_0229b1d8(void *ptr);
extern void *func_ov002_0220a720(void *ptr, int val);
extern int func_020896b8(int, void *, void *, int, int, int, int);
extern char data_ov105_0229fa80[];
extern void func_ov094_0229b288(void *a, void *b);
extern int func_02002c6c(void *a, void *b, int c, int d, int e, int f);
extern void func_ov002_02207f20(void *a, int b, int c, int d, int e);
extern void func_ov002_02207e90(void *a, int b);
extern void func_02002708(int a);
extern void func_ov105_0229ed78(void *a);
extern void *data_ov105_0229f890[];
extern void *data_021fbe94;
extern void func_ov105_0229cfc0(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_02088d34(unsigned short *, int, int, int, int);
extern unsigned short data_ov105_0229f85c[];
extern void func_02001a7c(void);
extern void func_02001a1c(int);
extern void func_ov002_0220a6b8(void *);
extern void func_02001a5c(void);
extern void func_ov002_0220a690(void *);
extern struct UnkStruct_0229c354 {
    unsigned short pad_00;
    unsigned short flags;
} data_021fbe40;

void func_ov105_0229c734(void *p);
void func_ov105_0229c6a0(UnkStruct_0229c6a0 *obj);
void func_ov105_0229c698(unsigned char *arg0);
int func_ov105_0229c340(int *r0, int r1);
void func_ov105_0229c330(struct UnkStruct_0229c330 *self, unsigned int mask);
void func_ov105_0229c320(unsigned int *p, unsigned int mask);

void func_ov105_0229cd7c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x24a4);
    func_ov002_02208098(self, 0xe);
}

void func_ov105_0229cd5c(void *self)
{
    func_ov002_0220a164((char *) self + 0x24a4);
    func_ov002_02208098(self, 0xf);
}

void func_ov105_0229cd30(void *arg0)
{
    func_ov002_0220a374((char *) arg0 + 0x24a4, 4);
    func_ov002_02208098(arg0, 0x10);
    func_ov105_0229c330((struct UnkStruct_0229c330 *) arg0, 0x1000);
}

void func_ov105_0229ccf4(char *arg0, char arg1)
{
    func_ov002_02207d24((void *) (arg0 + 0x23bc), 1);
    arg0[0x2bc] = arg1;
    func_ov002_0220a374((void *) (arg0 + 0x24a4), 5);
    func_ov002_02208098((void *) arg0, 0x12);
}

void func_ov105_0229cca8(struct UnkStruct_0229cca8 *p, unsigned char c)
{
    func_ov002_02207d24(&p->unk_23BC, 1);
    p->byte_at_2bd = p->byte_at_8d;
    p->byte_at_2bc = c;
    func_ov002_0220a374(&p->unk_24A4, 6);
    func_ov002_02208098(p, 0x13);
}

void func_ov105_0229cc5c(UnkStruct_ov105_0229cc5c *p)
{
    switch (p->unk_2BE) {
        case 0:
            func_ov105_0229cd30(p);
            break;
        case 1:
            func_ov105_0229c734(p);
            break;
        case 2:
            func_ov105_0229c6a0((UnkStruct_0229c6a0 *) p);
            break;
        case 3:
            func_ov105_0229c698((unsigned char *) p);
            break;
        case 4:
        default:
            func_ov105_0229db14(p);
            break;
    }
}

void func_ov105_0229cbe0(UnkStruct_0229cbe0 *self, int flag)
{
    int a, b, c;
    a = func_ov105_0229c340((int *) self, 0x800);
    func_ov002_02208c58((char *) self->arr_2508, (char *) self->arr_28f0, a);
    b = func_ov105_0229d530(self, self->unk_2BB);
    c = func_ov105_0229d4c4(self, self->unk_2BB);
    if (flag) {
        func_ov002_02209874((char *) self->arr_2508, (char *) self->arr_23bc);
    } else {
        func_ov002_02209910((char *) self->arr_2508, b, c);
    }
    func_ov002_0220970c((char *) self->arr_2508, 0);
    func_ov002_02208098(self, 0x16);
}

void func_ov105_0229cbb0(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;
    p[0x2be] = 4;
    func_ov105_0229cdbc(arg0);
    func_ov002_022096d8((char *) arg0 + 0x2508, 0);
    func_ov002_02208098(arg0, 0x18);
}

void func_ov105_0229cadc(int a, int b, int c)
{
    char *base = (char *) a;
    int tmp, res;

    func_ov105_0229c320((unsigned int *) ((int) base), 0x800);
    base[0x2bb] = (char) b;
    func_ov002_02208d30(base + 0x28f0, 4);
    tmp = func_ov105_0229d59c((int) base, b);
    if (func_0206fe54() != 0) {
        func_ov002_02208d4c(base + 0x28f0, 0, 0);
    }
    res = func_02065ec0(tmp);
    if (res != 0) {
        if (res == 7) {
            func_ov002_02208d4c(base + 0x28f0, 0x17, 1);
        } else {
            func_ov002_02208d4c(base + 0x28f0, 0x14, 1);
        }
    }
    if (func_02065f18(tmp) == 0xfff1) {
        if (res == 3 || res == 6 || res == 1 || res == 4) {
            func_ov002_02208d4c(base + 0x28f0, 0x15, 3);
        }
    }
    func_ov002_02208d4c(base + 0x28f0, 2, 4);
    func_ov105_0229cfc0((void *) ((int) base));
    if (c == 0) {
        func_ov002_02207d24(base + 0x23bc, 1);
    }
    func_ov105_0229cbe0((UnkStruct_0229cbe0 *) ((int) base), c);
}

void func_ov105_0229ca8c(unsigned char *base)
{
    func_ov105_0229c330((struct UnkStruct_0229c330 *) base, 0x800);
    func_ov002_02208d30((void *) (base + 0x28f0), 4);
    func_ov002_02208d4c((void *) (base + 0x28f0), 0x1a, 4);
    func_ov002_02208d4c((void *) (base + 0x28f0), 0x15, 2);
    func_ov002_02208d4c((void *) (base + 0x28f0), 0x19, 4);
    func_ov105_0229cbe0((UnkStruct_0229cbe0 *) base, 0);
}

void func_ov105_0229c9ac(unsigned char *self, void *other, int param)
{
    int t = self[0x2ba] - 0x1a;
    int k = t >> 1;

    if (!func_ov002_022088ac(other)) {
        goto L3;
    }

    // func_022088ac succeeded
    if ((t & 1) <= 0) {
        goto L2;
    }
    self[0x2ba] -= 1;
    goto Lcommon;

L2:
    self[0x2ba] = (unsigned char) (k * 5 + 0x28);
    goto Lend;

L3:
    if (!func_ov002_0220889c(other)) {
        goto Lcommon;
    }
    if ((t & 1) >= 1) {
        goto L4;
    }
    self[0x2ba] += 1;
    goto Lcommon;

L4:
    self[0x2ba] = (unsigned char) (k * 5 + 0x24);
    func_ov105_0229c330((struct UnkStruct_0229c330 *) self, 0x20);
    goto Lend;

Lcommon:
    if (func_ov105_0229d76c(self, self[0x2ba]) == 0) {
        goto Lend;
    }
    if (func_ov105_0229c340((int *) self, 0x30) != 0) {
        goto Lend;
    }
    if (func_ov002_022088cc(other) != 0) {
        if (k <= 0) {
            goto Lend;
        }
        self[0x2ba] -= 2;
        goto Lend;
    } else {
        if (func_ov002_022088bc(other) == 0) {
            goto Lend;
        }
        if (k >= 4) {
            goto L5;
        }
        self[0x2ba] += 2;
        goto Lend;
    }
L5:
    if (param != 0) {
        goto Lend;
    }
    self[0x2ba] = 0x3d;
    func_ov002_0220a314(self + 0x24a4);
Lend:
    return;
}

void func_ov105_0229c8b4(u8 *self, void *p, int arg2)
{
    int r4;
    int r6;

    r4 = (int) self[0x2ba] - 0x24;
    r6 = 0;
    while (r4 >= 5) {
        r6++;
        r4 -= 5;
    }

    if (func_ov002_022088ac(p) != 0) {
        if (r4 > 0) {
            self[0x2ba]--;
            r4--;
            goto common;
        } else {
            self[0x2ba] = r6 * 2 + 0x1b;
            func_ov105_0229c330((struct UnkStruct_0229c330 *) self, 0x10);
            return;
        }
    } else {
        if (func_ov002_0220889c(p) != 0) {
            if (r4 < 4) {
                self[0x2ba]++;
                r4++;
                goto common;
            } else {
                self[0x2ba] = r6 * 2 + 0x1a;
                return;
            }
        } else {
            goto common;
        }
    }

common:
    if (func_ov105_0229d75c(self, self[0x2ba]) != 0) {
        if (func_ov105_0229c340((int *) self, 0x30) == 0) {
            if (func_ov002_022088cc(p) != 0) {
                if (r6 > 0) {
                    self[0x2ba] -= 5;
                } else {
                    if (r4 < 2) {
                        r4 += 0x3e;
                        self[0x2ba] = (u8) r4;
                    } else {
                        self[0x2ba] = 0x3f;
                    }
                }
            } else {
                if (func_ov002_022088bc(p) != 0) {
                    if (r6 < 4) {
                        self[0x2ba] += 5;
                    } else {
                        if (arg2 == 0) {
                            self[0x2ba] = 0x3d;
                            func_ov002_0220a314(self + 0x24a4);
                        }
                    }
                }
            }
        }
    }
    return;
}

void func_ov105_0229c888(void *p, int x)
{
    if (func_ov002_022088cc((void *) x) != 0) {
        func_ov002_0220a2b4((char *) p + 0x24a4);
        *((char *) p + 0x2ba) = 0x22;
    }
}

void func_ov105_0229c82c(unsigned char *p, int id)
{
    if (func_ov002_022088ac((void *) id)) {
        if (p[0x2ba] > 0x3e) {
            p[0x2ba]--;
        }
    } else if (func_ov002_0220889c((void *) id)) {
        if (p[0x2ba] < 0x3f) {
            p[0x2ba]++;
        }
    }
    if (func_ov002_022088bc((void *) id)) {
        p[0x2ba] -= 0x1a;
    }
}

int func_ov105_0229c758(UnkStruct_0229c758 *self, int param1, int param2)
{
    unsigned char field = self->unk_2BA;

    func_ov105_0229c320((unsigned int *) self, 0x30);

    if (param1 == 0) {
        return 0;
    }

    if (func_ov105_0229d76c((void *) self, self->unk_2BA) != 0) {
        func_ov105_0229c9ac((unsigned char *) self, (void *) param1, param2);
    } else if (func_ov105_0229d75c((u8 *) self, self->unk_2BA) != 0) {
        func_ov105_0229c8b4((u8 *) self, (void *) param1, param2);
        if (func_ov105_0229d73c(self, self->unk_2BA) != 0 && param2 == 1) {
            func_ov002_0220a374(&self->unk_24A4, 1);
        }
    } else {
        if (func_ov105_0229d750(self, self->unk_2BA) != 0) {
            func_ov105_0229c888((void *) self, param1);
        } else {
            if (func_ov105_0229d73c(self, self->unk_2BA) != 0) {
                func_ov105_0229c82c((unsigned char *) self, param1);
                if (func_ov105_0229d73c(self, self->unk_2BA) == 0 && param2 == 1) {
                    func_0208e4c0(&self->unk_24A4, 4);
                }
            }
        }
    }

    return (field != self->unk_2BA) ? 1 : 0;
}

void func_ov105_0229c734(void *p)
{
    func_ov002_02208090(p, 4);
    func_ov002_022080a0(p, 1);
    func_ov105_0229c330((struct UnkStruct_0229c330 *) p, 0x100);
}

void func_ov105_0229c710(void *arg)
{
    func_ov002_02208098(arg, 0x1a);
    func_0208f0c4((char *) arg + 0x2d40, 2);
    func_0200467c(0x29);
}

void func_ov105_0229c6a0(UnkStruct_0229c6a0 *obj)
{
    unsigned char b = obj->unk_2BB;
    func_ov105_0229d0f8(obj, b);
    obj->unk_AC = func_ov105_0229d530(obj, b);
    obj->unk_B0 = func_ov105_0229d4c4(obj, b);
    if (func_0206fe54() != 0) {
        obj->unk_AC -= 2;
        obj->unk_B0 -= 2;
    }
    func_ov002_02208098(obj, 0x1c);
    func_ov094_0229b1d8((char *) obj + 0x0d5c);
}

void func_ov105_0229c698(unsigned char *arg0)
{
    func_ov105_0229ca8c((unsigned char *) arg0);
}

void func_ov105_0229c694(void *self) {}

void func_ov105_0229c668(void *param)
{
    void *r4 = param;
    func_0200467c(0x29);
    func_ov002_0220a720((char *) r4 + 0x5fb8, 9);
    func_ov002_02208098(r4, 0x1b);
    *((unsigned char *) ((char *) r4 + 0x8c)) = 0xe;
}

void func_ov105_0229c62c(int param)
{
    int local;
    func_0200467c(0x27);
    local = param + 0x5fb8;
    func_ov002_0220a720((void *) local, 3);
    *(unsigned char *) (param + 0x8c) = 4;
    func_ov105_0229c320((unsigned int *) param, 0x100);
    func_ov002_02208098((void *) param, 0x1b);
}

void func_ov105_0229c5fc(void *param)
{
    void *r4;
    r4 = param;
    func_0200467c(0x2a);
    func_ov002_0220a720((char *) r4 + 0x5fb8, 4);
    *(char *) ((char *) r4 + 0x8c) = 0x12;
    func_ov002_02208098(r4, 0x1b);
}

void func_ov105_0229c55c(struct UnkStruct_0229c55c *self)
{
    char *base;
    int i, j, a, b, c, d, e;

    base = (char *) self->ptr + 0x80;
    i = 0;
    j = 0;
    a = 0;
    b = 0;
    c = 0;

    do {
        if (i == self->byte) {
            d = 0x52;
            e = 4;
        } else {
            d = 0x50;
            e = 5;
        }
        func_020896b8(1, data_ov105_0229fa80 + j * 8, base, d, -1, 1, a);
        func_020896b8(1, data_ov105_0229fa80 + (j + 1) * 8, base, d, e, 1, b);
        func_020896b8(1, data_ov105_0229fa80 + (j + 2) * 8, base, 0x50, -1, 1, c);
        i++;
        j += 3;
    } while (i < 2);
}

void func_ov105_0229c4cc(void *self)
{
    func_ov094_0229b288((char *) self + 0x0d5c,
                        (char *) self + 0x2db8 + (((*(unsigned char *) ((char *) self + 0x2c0)) * 25) << 8));
    func_02002c6c(data_ov105_0229f890[*(unsigned char *) ((char *) self + 0x2c0)], data_021fbe94, 4, 0x1e2, 0x1e2, 0x1ed);
    func_ov002_02207f20(self, 2, 0, 2, 0x30);
    func_ov002_02207e90(self, 0xc0);
    func_02002708(4);
    func_ov105_0229c330((struct UnkStruct_0229c330 *) self, 0x200);
    func_ov105_0229ed78(self);
}

void func_ov105_0229c490(void *p)
{
    func_ov002_02207d24((char *) p + 0x23bc, 1);
    func_ov105_0229cfc0(p);
    func_ov002_02207f04(p, 2, 0, 2, 0x30);
    func_ov002_02207e90(p, 0xc0);
}

int func_ov105_0229c438(struct UnkStruct_0229c438 *p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    int i = 0;
    int j = 0;

    while (i < 2) {
        if (i != p0->unk_2C0) {
            if (func_02088d34(&((unsigned short *) data_ov105_0229fa80)[j * 4], a, b, 2, 2) != 0) {
                p0->unk_2C0 = (unsigned char) i;
                return 1;
            }
        }
        i++;
        j += 3;
    }
    return 0;
}

void func_ov105_0229c3ec(struct UnkStruct_0229c3ec *self)
{
    func_0200467c(data_ov105_0229f85c[self->unk_2C0]);
    func_ov002_02207d24(&self->unk_23BC, 1);
    func_ov105_0229cfc0(self);
    self->unk_8C = 0xb;
    func_ov002_022080a0(self, 1);
    func_ov105_0229c330((struct UnkStruct_0229c330 *) self, 0x40);
}

void func_ov105_0229c3c8(void *arg)
{
    func_02001a7c();
    func_02001a1c(~5);
    func_ov002_0220a6b8((char *) arg + 0x5fb8);
}

void func_ov105_0229c3ac(void *arg0)
{
    func_02001a5c();
    func_ov002_0220a690((char *) arg0 + 0x5fb8);
}

int func_ov105_0229c354(unsigned char *self)
{
    int x = 0;
    unsigned short f = data_021fbe40.flags;

    if (f & 0x200) {
        x = -1;
    } else if (f & 0x100) {
        x = 1;
    }

    if (x != 0) {
        x += self[0x2c0];
        if (x < 0) {
            x = 1;
        } else if (x > 1) {
            x = 0;
        }
        self[0x2c0] = (unsigned char) x;
        func_ov105_0229c3ec((struct UnkStruct_0229c3ec *) ((void *) self));
    }

    return 0;
}

int func_ov105_0229c340(int *r0, int r1)
{
    if ((*(r0 + 0x25) & r1) != 0) {
        return 1;
    }
    return 0;
}

void func_ov105_0229c330(struct UnkStruct_0229c330 *self, unsigned int mask)
{
    self->unk_94 |= mask;
}

void func_ov105_0229c320(unsigned int *p, unsigned int mask)
{
    p[0x25] = p[0x25] & ~mask;
}
