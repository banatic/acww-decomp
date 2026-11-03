/* mailbox_scene: 25 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229ca1c @ 0x0229ca1c, 0x20 bytes, Thumb
 * func_ov106_0229c9fc @ 0x0229c9fc, 0x20 bytes, Thumb
 * func_ov106_0229c9dc @ 0x0229c9dc, 0x20 bytes, Thumb
 * func_ov106_0229c9a0 @ 0x0229c9a0, 0x3c bytes, Thumb
 * func_ov106_0229c958 @ 0x0229c958, 0x48 bytes, Thumb
 * func_ov106_0229c910 @ 0x0229c910, 0x48 bytes, Thumb
 * func_ov106_0229c894 @ 0x0229c894, 0x7c bytes, Thumb
 * func_ov106_0229c868 @ 0x0229c868, 0x2c bytes, Thumb
 * func_ov106_0229c798 @ 0x0229c798, 0xd0 bytes, Thumb
 * func_ov106_0229c748 @ 0x0229c748, 0x50 bytes, Thumb
 * func_ov106_0229c638 @ 0x0229c638, 0x110 bytes, Thumb
 * func_ov106_0229c54c @ 0x0229c54c, 0xec bytes, Thumb
 * func_ov106_0229c524 @ 0x0229c524, 0x28 bytes, Thumb
 * func_ov106_0229c4a0 @ 0x0229c4a0, 0x84 bytes, Thumb
 * func_ov106_0229c47c @ 0x0229c47c, 0x24 bytes, Thumb
 * func_ov106_0229c458 @ 0x0229c458, 0x24 bytes, Thumb
 * func_ov106_0229c418 @ 0x0229c418, 0x40 bytes, Thumb
 * func_ov106_0229c3a8 @ 0x0229c3a8, 0x70 bytes, Thumb
 * func_ov106_0229c3a0 @ 0x0229c3a0, 0x8 bytes, Thumb
 * func_ov106_0229c378 @ 0x0229c378, 0x28 bytes, Thumb
 * func_ov106_0229c364 @ 0x0229c364, 0x12 bytes, Thumb
 * func_ov106_0229c354 @ 0x0229c354, 0xe bytes, Thumb
 * func_ov106_0229c344 @ 0x0229c344, 0xe bytes, Thumb
 * func_ov106_0229c260 @ 0x0229c260, 0xe4 bytes, Thumb
 * func_ov106_0229c180 @ 0x0229c180, 0xe0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xb7];
    u8 unk_B7;
    u8 unk_B8;
} SelfType;

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned char unk_B8;
} SelfType_0229c54c;

struct UnkStruct_0229c4a0 {
    unsigned char pad_00[0xb8];
    unsigned char flag;
};

struct UnkStruct_0229c3a8;

struct UnkStruct_0229c3a8 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    char pad_B4[5];
    unsigned char unk_B9;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov002_02207d24(void *p, int n);
extern void func_ov106_0229d73c(void *self);
extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov106_0229d170(char *p, unsigned char x);
extern int func_ov106_0229d128(char *p, unsigned char x);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov106_0229ca5c(void *p);
extern void func_ov002_022096d8(void *p, int v);
extern void func_ov002_02208d30(void *ptr, int val);
extern int func_ov106_0229d20c(void *self, int a);
extern int func_0206fe54(void);
extern int func_02065ec0(int x);
extern int func_02065f18(int x);
extern int func_ov002_02208d4c(void *ptr, int val1, int val2);
extern void func_ov106_0229cc50(void *self);
extern int func_ov002_022088ac(void *ctx);
extern int func_ov002_0220889c(void *ctx);
extern int func_ov002_022088cc(void *ctx);
extern int func_ov002_022088bc(void *ctx);
extern void func_ov002_0220a314(void *p);
extern int func_ov106_0229d3a0(void *self, u8 b);
extern int func_ov106_0229d390(void *self, int b);
extern void func_ov002_0220a2b4(void *);
extern int func_ov106_0229d384(struct UnkStruct_0229c4a0 *p, unsigned char value);
extern void func_ov002_02208090(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_0208f0c4(void *p, int n);
extern void func_0200467c(int cmd);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov106_0229cd88(struct UnkStruct_0229c3a8 *self, unsigned char b);
extern void func_ov094_0229b1d8(void *addr);
extern void *func_ov002_0220a720(void *, int);
extern void func_02066688(void *);
extern void *func_0206e35c(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220b464(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern char data_ov106_0229f6e0[];

void func_ov106_0229c47c(void *p);
void func_ov106_0229c3a8(struct UnkStruct_0229c3a8 *self);
void func_ov106_0229c3a0(unsigned int argument0);
int func_ov106_0229c364(int *arg0, int arg1);
void func_ov106_0229c354(void *r0, unsigned int r1);
void func_ov106_0229c344(void *self, unsigned int mask);

void func_ov106_0229ca1c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x22a0);
    func_ov002_02208098((void *) (self), 0xe);
}

void func_ov106_0229c9fc(void *arg0)
{
    func_ov002_0220a164((char *) arg0 + 0x22a0);
    func_ov002_02208098((void *) (arg0), 0xf);
}

void func_ov106_0229c9dc(void *p)
{
    func_ov002_0220a374((char *) p + 0x22a0, 4);
    func_ov002_02208098((void *) (p), 0x10);
}

void func_ov106_0229c9a0(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x21b8, 1);
    ((char *) self)[0xba] = val;
    func_ov002_0220a374((char *) self + 0x22a0, 5);
    func_ov002_02208098((void *) (self), 0x12);
}

void func_ov106_0229c958(void *self, unsigned char val)
{
    unsigned char tmp;

    func_ov002_02207d24((char *) self + 0x21b8, 1);
    tmp = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0xbb) = tmp;
    *(unsigned char *) ((char *) self + 0xba) = val;
    func_ov002_0220a374((char *) self + 0x22a0, 6);
    func_ov002_02208098((void *) (self), 0x13);
}

void func_ov106_0229c910(void *self)
{
    switch (((unsigned char *) self)[0xbc]) {
        case 0:
            func_ov106_0229c9dc(self);
            break;
        case 1:
            func_ov106_0229c47c(self);
            break;
        case 2:
            func_ov106_0229c3a8((struct UnkStruct_0229c3a8 *) self);
            break;
        case 3:
            func_ov106_0229c3a0((unsigned int) self);
            break;
        case 4:
        default:
            func_ov106_0229d73c(self);
            break;
    }
}

void func_ov106_0229c894(char *p, int flag)
{
    int res1, res2, res3;
    res1 = func_ov106_0229c364((int *) p, 0x10000);
    func_ov002_02208c58(p + 0x2304, p + 0x26ec, res1);
    res2 = func_ov106_0229d170(p, *(unsigned char *) (p + 0xb9));
    res3 = func_ov106_0229d128(p, *(unsigned char *) (p + 0xb9));
    if (flag) {
        func_ov002_02209874(p + 0x2304, p + 0x21b8);
    } else {
        func_ov002_02209910(p + 0x2304, res2, res3);
    }
    func_ov002_0220970c(p + 0x2304, 0);
    func_ov002_02208098((void *) (p), 0x16);
}

void func_ov106_0229c868(void *self)
{
    unsigned char *p = (unsigned char *) self + 0xbc;
    *p = 4;
    func_ov106_0229ca5c(self);
    func_ov002_022096d8((char *) self + 0x2304, 0);
    func_ov002_02208098((void *) (self), 0x18);
}

void func_ov106_0229c798(unsigned char *self, int a, int b)
{
    int x, y;

    func_ov106_0229c344(self, 0x10000);
    self[0xb9] = (unsigned char) a;
    func_ov002_02208d30(self + 0x26ec, 4);
    x = func_ov106_0229d20c(self, a);
    if (func_0206fe54()) {
        func_ov002_02208d4c(self + 0x26ec, 0, 0);
    }
    y = func_02065ec0(x);
    if (y != 0) {
        if (y == 7) {
            func_ov002_02208d4c(self + 0x26ec, 0x17, 1);
        } else {
            func_ov002_02208d4c(self + 0x26ec, 0x14, 1);
        }
    }
    if (func_02065f18(x) == 0xfff1) {
        if (y == 3 || y == 6 || y == 1 || y == 4) {
            func_ov002_02208d4c(self + 0x26ec, 0x15, 3);
        }
    }
    func_ov002_02208d4c(self + 0x26ec, 2, 4);
    func_ov106_0229cc50(self);
    if (b == 0) {
        func_ov002_02207d24(self + 0x21b8, 1);
    }
    func_ov106_0229c894((char *) self, b);
}

static __inline void *base(unsigned int self)
{
    return (void *) (self + 0x26ec);
}

void func_ov106_0229c748(unsigned int self)
{
    func_ov106_0229c354((void *) self, 0x00010000);
    func_ov002_02208d30(base(self), 4);
    func_ov002_02208d4c(base(self), 0x1a, 4);
    func_ov002_02208d4c(base(self), 0x15, 2);
    func_ov002_02208d4c(base(self), 0x19, 4);
    func_ov106_0229c894((char *) self, 0);
}

void func_ov106_0229c638(SelfType *self, void *ctx, int flag)
{
    int r6;
    int r4;

    r6 = (int) self->unk_B8 - 0xb;
    r4 = r6 >> 1;

    if (func_ov002_022088ac(ctx) != 0) {
        if ((r6 & 1) > 0) {
            self->unk_B8--;
        } else {
            if (flag == 1 && func_ov106_0229d3a0(self, self->unk_B7) != 0) {
                goto common;
            }
            self->unk_B8 = (r4 << 1) + 0x16;
            return;
        }
    } else {
        if (func_ov002_0220889c(ctx) != 0) {
            if ((r6 & 1) < 1) {
                self->unk_B8++;
            } else {
                if (flag == 1 && func_ov106_0229d3a0(self, self->unk_B7) != 0) {
                    goto common;
                }
                self->unk_B8 = (r4 << 1) + 0x15;
                func_ov106_0229c354(self, 0x20);
                return;
            }
        }
    }

common:
    if (func_ov106_0229d3a0(self, self->unk_B8) == 0) {
        return;
    }
    if (func_ov106_0229c364((int *) self, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc(ctx) != 0) {
        if (r4 > 0) {
            self->unk_B8 -= 2;
        }
        return;
    }

    if (func_ov002_022088bc(ctx) != 0) {
        if (r4 < 4) {
            self->unk_B8 += 2;
            return;
        }
        if (flag == 0) {
            self->unk_B8 = 0x1f;
            func_ov002_0220a314((char *) self + 0x22a0);
        }
    }
}

void func_ov106_0229c54c(SelfType_0229c54c *self, void *ctx, int flag)
{
    int r6, r4;

    r6 = (int) self->unk_B8 - 0x15;
    r4 = 0;
    while (r6 >= 2) {
        r4++;
        r6 -= 2;
    }

    if (func_ov002_022088ac(ctx) != 0) {
        if (r6 > 0) {
            self->unk_B8--;
        } else {
            self->unk_B8 = (unsigned char) (r4 * 2 + 0xc);
            func_ov106_0229c354(self, 0x10);
            return;
        }
    } else {
        if (func_ov002_0220889c(ctx) != 0) {
            if (r6 < 1) {
                self->unk_B8++;
            } else {
                self->unk_B8 = (unsigned char) (r4 * 2 + 0xb);
                return;
            }
        }
    }

    if (func_ov106_0229d390(self, self->unk_B8) != 0) {
        if (func_ov106_0229c364((int *) self, 0x30) == 0) {
            if (func_ov002_022088cc(ctx) != 0) {
                if (r4 > 0) {
                    self->unk_B8 -= 2;
                }
                return;
            } else {
                if (func_ov002_022088bc(ctx) != 0) {
                    if (r4 < 4) {
                        self->unk_B8 += 2;
                        return;
                    } else {
                        if (flag == 0) {
                            self->unk_B8 = 0x1f;
                            func_ov002_0220a314((char *) self + 0x22a0);
                        }
                    }
                }
            }
        }
    }
}

void func_ov106_0229c524(char *p, int param1)
{
    if (func_ov002_022088cc((void *) param1)) {
        func_ov002_0220a2b4(p + 0x22a0);
        p += 0xb8;
        *p = 0x13;
    }
}

int func_ov106_0229c4a0(struct UnkStruct_0229c4a0 *p, int a2, int a3)
{
    unsigned char old = p->flag;

    func_ov106_0229c344((void *) p, 0x30);
    if (a2 == 0) {
        return 0;
    }
    if (func_ov106_0229d3a0((void *) p, (unsigned char) p->flag)) {
        func_ov106_0229c638((SelfType *) p, (void *) a2, a3);
    } else if (func_ov106_0229d390((void *) p, (unsigned char) p->flag)) {
        func_ov106_0229c54c((SelfType_0229c54c *) p, (void *) a2, a3);
    } else if (func_ov106_0229d384(p, p->flag)) {
        func_ov106_0229c524((char *) p, a2);
    }
    return old != p->flag;
}

void func_ov106_0229c47c(void *p)
{
    func_ov002_02208090(p, 4);
    func_ov002_022080a0((void *) (p), 1);
    func_ov106_0229c354(p, 0x100);
}

void func_ov106_0229c458(char *param)
{
    func_ov002_02208098((void *) (param), 0x22);
    func_0208f0c4(param + 0x2b3c, 2);
    func_0200467c(0x29);
}

void func_ov106_0229c418(void *p)
{
    func_ov106_0229c458((char *) p);
    func_ov106_0229c354(p, 0x8000);
    func_ov106_0229cc50(p);
    func_ov002_02208090(p, 9);
    func_ov002_022080a0((void *) (p), 1);
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
}

void func_ov106_0229c3a8(struct UnkStruct_0229c3a8 *self)
{
    unsigned char b;
    b = self->unk_B9;
    func_ov106_0229cd88(self, b);
    self->unk_AC = func_ov106_0229d170((char *) self, b);
    self->unk_B0 = func_ov106_0229d128((char *) self, b);
    if (func_0206fe54() != 0) {
        self->unk_AC -= 2;
        self->unk_B0 -= 2;
    }
    func_ov002_02208098((void *) (self), 0x26);
    func_ov094_0229b1d8((char *) self + 0x0b58);
}

void func_ov106_0229c3a0(unsigned int argument0)
{
    func_ov106_0229c748(argument0);
}

void func_ov106_0229c378(void *param)
{
    void *r4 = param;
    func_0200467c(0x27);
    func_ov002_0220a720((char *) r4 + 0x3fb4, 9);
    func_ov002_02208098((void *) (r4), 0x23);
}

int func_ov106_0229c364(int *arg0, int arg1)
{
    if ((*(int *) ((char *) arg0 + 0x94) & arg1) != 0) {
        return 1;
    }
    return 0;
}

void func_ov106_0229c354(void *r0, unsigned int r1)
{
    unsigned int *p = (unsigned int *) ((char *) r0 + 0x94);
    *p |= r1;
}

void func_ov106_0229c344(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    *p &= ~mask;
}

void *func_ov106_0229c260(void *self)
{
    char *p = (char *) self;
    *(unsigned int *) p = (unsigned int) ((char *) data_ov106_0229f6e0);
    func_02066688(p + 0x4280);
    func_02066688(p + 0x4180);
    func_ov002_0220afdc(p + 0x3fb4);
    __cxa_vec_cleanup(p + 0x35b4, 10, 0x100, func_02066688);
    __cxa_vec_cleanup(p + 0x2bb4, 10, 0x100, func_02066688);
    func_ov002_0220b464(p + 0x2b3c);
    func_0206e35c(p + 0x2814);
    func_ov002_0220ba0c(p + 0x26f8);
    func_ov002_02209ac8(p + 0x2304);
    func_ov002_02209cb4(p + 0x22a0);
    func_ov002_02209e38(p + 0x2288);
    func_ov002_02207e28(p + 0x21b8);
    func_ov094_0229a2d0(p + 0x0b80);
    func_ov094_0229bc30(p + 0x0b58);
    func_ov094_0229afe0(p + 0xf8);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return self;
}

void *func_ov106_0229c180(char *self)
{
    *(void **) self = data_ov106_0229f6e0;

    func_02066688(self + 0x4280);
    func_02066688(self + 0x4180);
    func_ov002_0220afdc(self + 0x3fb4);
    __cxa_vec_cleanup(self + 0x35b4, 0xa, 0x100, func_02066688);
    __cxa_vec_cleanup(self + 0x2bb4, 0xa, 0x100, func_02066688);
    func_ov002_0220b464(self + 0x2b3c);
    func_0206e35c(self + 0x2814);
    func_ov002_0220ba0c(self + 0x26f8);
    func_ov002_02209ac8(self + 0x2304);
    func_ov002_02209cb4(self + 0x22a0);
    func_ov002_02209e38(self + 0x2288);
    func_ov002_02207e28(self + 0x21b8);
    func_ov094_0229a2d0(self + 0xb80);
    func_ov094_0229bc30(self + 0xb58);
    func_ov094_0229afe0(self + 0xf8);
    func_ov002_0220826c(self);
    return self;
}
