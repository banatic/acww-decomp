/* letter_send_3: 19 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229d178 @ 0x0229d178, 0x20 bytes, Thumb
 * func_ov104_0229d158 @ 0x0229d158, 0x20 bytes, Thumb
 * func_ov104_0229d11c @ 0x0229d11c, 0x3c bytes, Thumb
 * func_ov104_0229d0d4 @ 0x0229d0d4, 0x48 bytes, Thumb
 * func_ov104_0229d08c @ 0x0229d08c, 0x48 bytes, Thumb
 * func_ov104_0229d010 @ 0x0229d010, 0x7c bytes, Thumb
 * func_ov104_0229cfe4 @ 0x0229cfe4, 0x2c bytes, Thumb
 * func_ov104_0229cf14 @ 0x0229cf14, 0xd0 bytes, Thumb
 * func_ov104_0229cec4 @ 0x0229cec4, 0x50 bytes, Thumb
 * func_ov104_0229cdf0 @ 0x0229cdf0, 0xd4 bytes, Thumb
 * func_ov104_0229cd18 @ 0x0229cd18, 0xd8 bytes, Thumb
 * func_ov104_0229ccb4 @ 0x0229ccb4, 0x64 bytes, Thumb
 * func_ov104_0229cc30 @ 0x0229cc30, 0x84 bytes, Thumb
 * func_ov104_0229cc0c @ 0x0229cc0c, 0x24 bytes, Thumb
 * func_ov104_0229cbe8 @ 0x0229cbe8, 0x24 bytes, Thumb
 * func_ov104_0229cb78 @ 0x0229cb78, 0x70 bytes, Thumb
 * func_ov104_0229cb70 @ 0x0229cb70, 0x8 bytes, Thumb
 * func_ov104_0229cb38 @ 0x0229cb38, 0x38 bytes, Thumb
 * func_ov104_0229cb04 @ 0x0229cb04, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229d08c {
    unsigned char pad_00[0xbc];
    unsigned char flag;
} UnkStruct_0229d08c;

typedef struct Overlay104Data {
    unsigned char pad_00[0xb9];
    unsigned char b9;
    unsigned char pad_BA[0x22fe];
    unsigned char unk_23B8;
    unsigned char pad_23B9[0x533];
    unsigned char unk_28EC;
} Overlay104Data;

typedef struct {
    unsigned char pad_00[0xB8];
    unsigned char b8;
} UnkStruct_0229cdf0;

typedef struct {
    char pad_00[0xb8];
    u8 unk_B8;
    char pad_B9[0x24a0 - 0xb9];
    char unk_24A0;
} UnkStruct_0229cd18;

struct UnkStruct_0229cc30 {
    char pad_00[0xB8];
    unsigned char unk_B8;
};

typedef struct UnkStruct_0229cb78 UnkStruct_0229cb78;

struct UnkStruct_0229cb78 {
    char pad_00[0xa8];
    int a8;
    int ac;
    char pad_B0[9];
    unsigned char c;
};

extern void func_ov002_0220a1dc(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a374(void *, int);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov104_0229dd00(void *);
extern int func_ov104_0229c364(char *p, int x);
extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov104_0229d8a8(char *p, unsigned char x);
extern int func_ov104_0229d858(char *p, unsigned char x);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov104_0229d1b8(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov104_0229c344(Overlay104Data *self, int a);
extern void func_ov002_02208d30(void *ptr, int size);
extern int func_ov104_0229d8f8(Overlay104Data *self, int param);
extern int func_0206fe54(void);
extern int func_ov002_02208d4c(void *ptr, int a, int b);
extern int func_02065ec0(int x);
extern int func_02065f18(int x);
extern void func_ov104_0229d378(Overlay104Data *self);
extern void func_ov104_0229c354(void *arg0, int arg1);
extern int func_ov002_022088bc(int);
extern int func_ov104_0229da80(void *, int);
extern void func_ov002_0220a314(void *);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov104_0229da70(UnkStruct_0229cd18 *self, int a);
extern void func_ov002_0220a2b4(void *);
extern int func_ov104_0229da5c(struct UnkStruct_0229cc30 *a, unsigned char b);
extern void func_ov002_02208090(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_0208f0c4(void *ptr, int value);
extern void func_0200467c(int cmd);
extern void func_ov104_0229d4a8(UnkStruct_0229cb78 *, unsigned char);
extern void func_ov094_0229b1d8(void *);
extern int func_02066830(void *dest, int value);
extern void func_ov104_0229d938(unsigned char *p1, unsigned char p2, unsigned char *p3);

void func_ov104_0229cc0c(int a);
void func_ov104_0229cb78(UnkStruct_0229cb78 *self);
void func_ov104_0229cb70(void *argument0);

void func_ov104_0229d178(void *arg)
{
    func_ov002_0220a1dc((char *) arg + 0x24a0);
    func_ov002_02208098((void *) (arg), 0xe);
}

void func_ov104_0229d158(char *p)
{
    func_ov002_0220a374(p + 0x24a0, 4);
    func_ov002_02208098((void *) (p), 0x10);
}

void func_ov104_0229d11c(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x23b8, 1);
    ((char *) self)[0xba] = val;
    func_ov002_0220a374((char *) self + 0x24a0, 5);
    func_ov002_02208098((void *) (self), 0x12);
}

void func_ov104_0229d0d4(void *p, unsigned char val)
{
    func_ov002_02207d24((char *) p + 0x23b8, 1);
    *((unsigned char *) ((char *) p + 0xbb)) = *((unsigned char *) ((char *) p + 0x8d));
    *((unsigned char *) ((char *) p + 0xba)) = val;
    func_ov002_0220a374((char *) p + 0x24a0, 6);
    func_ov002_02208098((void *) (p), 0x13);
}

void func_ov104_0229d08c(UnkStruct_0229d08c *p)
{
    switch (p->flag) {
        case 0:
            func_ov104_0229d158((char *) p);
            break;
        case 1:
            func_ov104_0229cc0c((int) p);
            break;
        case 2:
            func_ov104_0229cb78((UnkStruct_0229cb78 *) p);
            break;
        case 3:
            func_ov104_0229cb70(p);
            break;
        default:
        case 4:
            func_ov104_0229dd00(p);
            break;
    }
}

void func_ov104_0229d010(char *p, int flag)
{
    int res1, res2, res3;
    res1 = func_ov104_0229c364(p, 0x8000);
    func_ov002_02208c58(p + 0x2504, p + 0x28ec, res1);
    res2 = func_ov104_0229d8a8(p, *(unsigned char *) (p + 0xb9));
    res3 = func_ov104_0229d858(p, *(unsigned char *) (p + 0xb9));
    if (flag) {
        func_ov002_02209874(p + 0x2504, p + 0x23b8);
    } else {
        func_ov002_02209910(p + 0x2504, res2, res3);
    }
    func_ov002_0220970c(p + 0x2504, 0);
    func_ov002_02208098((void *) (p), 0x16);
}

void func_ov104_0229cfe4(void *self)
{
    unsigned char *p;
    p = (unsigned char *) self + 0xbc;
    *p = 4;
    func_ov104_0229d1b8(self);
    func_ov002_022096d8((char *) self + 0x2504, 0);
    func_ov002_02208098((void *) (self), 0x18);
}

void func_ov104_0229cf14(Overlay104Data *self, int param1, int param2)
{
    int result;
    int v5;

    func_ov104_0229c344(self, 0x8000);
    self->b9 = param1;
    func_ov002_02208d30(&self->unk_28EC, 4);
    result = func_ov104_0229d8f8(self, param1);
    if (func_0206fe54()) {
        func_ov002_02208d4c(&self->unk_28EC, 0, 0);
    }
    v5 = func_02065ec0(result);
    if (v5 != 0) {
        if (v5 == 7) {
            func_ov002_02208d4c(&self->unk_28EC, 0x17, 1);
        } else {
            func_ov002_02208d4c(&self->unk_28EC, 0x14, 1);
        }
    }
    if (func_02065f18(result) == 0xfff1) {
        if (v5 == 3 || v5 == 6 || v5 == 1 || v5 == 4) {
            func_ov002_02208d4c(&self->unk_28EC, 0x15, 3);
        }
    }
    func_ov002_02208d4c(&self->unk_28EC, 2, 4);
    func_ov104_0229d378(self);
    if (param2 == 0) {
        func_ov002_02207d24(&self->unk_23B8, 1);
    }
    func_ov104_0229d010((char *) self, param2);
}

void func_ov104_0229cec4(unsigned char *self)
{
    func_ov104_0229c354(self, 0x8000);
    func_ov002_02208d30(self + 0x28ec, 4);
    func_ov002_02208d4c(self + 0x28ec, 0x1a, 4);
    func_ov002_02208d4c(self + 0x28ec, 0x15, 2);
    func_ov002_02208d4c(self + 0x28ec, 0x19, 4);
    func_ov104_0229d010((char *) self, 0);
}

void func_ov104_0229cdf0(UnkStruct_0229cdf0 *a, int x, int c)
{
    int diff = a->b8 - 11;
    int half = diff >> 1;

    if (func_ov002_022088ac((void *) x)) {
        diff &= 1;
        if (diff > 0) {
            a->b8--;
        } else {
            a->b8 = (half << 1) + 22;
            return;
        }
    } else {
        if (func_ov002_0220889c((void *) x)) {
            diff &= 1;
            if (diff < 1) {
                a->b8++;
            }
        }
    }

    if (func_ov104_0229da80(a, a->b8) == 0) {
        return;
    }
    if (func_ov104_0229c364((char *) a, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc((void *) x)) {
        if (half > 0) {
            a->b8 -= 2;
        }
        return;
    }

    if (func_ov002_022088bc(x)) {
        if (half < 4) {
            a->b8 += 2;
        } else {
            if (c != 0) {
                return;
            }
            a->b8 = 0x1f;
            func_ov002_0220a314((char *) a + 0x24a0);
        }
    }
}

void func_ov104_0229cd18(UnkStruct_0229cd18 *self, void *pad, int flag)
{
    int v;
    int i;

    v = self->unk_B8 - 0x15;
    i = 0;
    while (v >= 2) {
        i++;
        v -= 2;
    }

    if (func_ov002_022088ac(pad) != 0) {
        if (v > 0) {
            self->unk_B8 = self->unk_B8 - 1;
        }
    } else if (func_ov002_0220889c(pad) != 0) {
        if (v < 1) {
            self->unk_B8 = self->unk_B8 + 1;
        } else {
            self->unk_B8 = (u8) (i * 2 + 0xb);
            return;
        }
    }

    if (func_ov104_0229da70(self, self->unk_B8) != 0) {
        if (func_ov104_0229c364((char *) self, 0x30) == 0) {
            if (func_ov002_022088cc(pad) != 0) {
                if (i > 0) {
                    self->unk_B8 = self->unk_B8 - 2;
                }
            } else if (func_ov002_022088bc((int) pad) != 0) {
                if (i < 4) {
                    self->unk_B8 = self->unk_B8 + 2;
                } else if (flag == 0) {
                    self->unk_B8 = 0x20;
                    func_ov002_0220a314(&self->unk_24A0);
                }
            }
        }
    }
}

void func_ov104_0229ccb4(void *param0, void *param1)
{
    if (func_ov002_022088ac(param1)) {
        ((unsigned char *) param0)[0xb8] = 0x20;
    } else if (func_ov002_0220889c(param1)) {
        ((unsigned char *) param0)[0xb8] = 0x1f;
    }
    if (func_ov002_022088cc(param1)) {
        func_ov002_0220a2b4((char *) param0 + 0x24a0);
        if (((unsigned char *) param0)[0xb8] == 0x20) {
            ((unsigned char *) param0)[0xb8] = 0x1d;
        } else {
            ((unsigned char *) param0)[0xb8] = 0x13;
        }
    }
}

int func_ov104_0229cc30(struct UnkStruct_0229cc30 *a, int b, int c)
{
    unsigned char initial = a->unk_B8;
    func_ov104_0229c344((Overlay104Data *) a, 0x30);
    if (b == 0) {
        return 0;
    }

    if (func_ov104_0229da80((void *) a, (unsigned char) a->unk_B8)) {
        func_ov104_0229cdf0((UnkStruct_0229cdf0 *) a, b, c);
    } else if (func_ov104_0229da70((UnkStruct_0229cd18 *) a, (unsigned char) a->unk_B8)) {
        func_ov104_0229cd18((UnkStruct_0229cd18 *) a, (void *) b, c);
    } else if (func_ov104_0229da5c(a, a->unk_B8)) {
        func_ov104_0229ccb4((void *) a, (void *) b);
    }

    if (initial != a->unk_B8) {
        return 1;
    }
    return 0;
}

void func_ov104_0229cc0c(int a)
{
    func_ov002_02208090(a, 4);
    func_ov002_022080a0((void *) (a), 1);
    func_ov104_0229c354((void *) a, 0x100);
}

void func_ov104_0229cbe8(void *param)
{
    func_ov002_02208098((void *) (param), 0x1a);
    func_0208f0c4((char *) param + 0x2d3c, 2);
    func_0200467c(0x29);
}

void func_ov104_0229cb78(UnkStruct_0229cb78 *self)
{
    unsigned char c;

    c = self->c;
    func_ov104_0229d4a8(self, c);
    self->a8 = func_ov104_0229d8a8((char *) self, c);
    self->ac = func_ov104_0229d858((char *) self, c);

    if (func_0206fe54()) {
        self->a8 -= 2;
        self->ac -= 2;
    }

    func_ov002_02208098((void *) (self), 0x1c);
    func_ov094_0229b1d8((char *) self + 0xd58);
}

void func_ov104_0229cb70(void *argument0)
{
    func_ov104_0229cec4((unsigned char *) argument0);
}

void func_ov104_0229cb38(void *base)
{
    unsigned char j;
    int i;

    i = 0;
    j = 11;

    do {
        int val = func_ov104_0229d8f8((Overlay104Data *) base, (unsigned char) j);
        func_02066830((char *) base + 0x37b4 + (i << 8), val);
        i++;
        j++;
    } while (j <= 20);
}

void func_ov104_0229cb04(unsigned char *base)
{
    unsigned char idx;
    int i;

    i = 0;
    idx = 0x0b;

    do {
        func_ov104_0229d938(base, idx, base + 0x37b4 + (i << 8));
        i++;
        idx = (unsigned char) (idx + 1);
    } while (idx <= 0x14);
}
