/* star_designer_input_4: 17 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229cd54 @ 0x0229cd54, 0x208 bytes, Thumb
 * func_ov129_0229cc9c @ 0x0229cc9c, 0xb8 bytes, Thumb
 * func_ov129_0229cc4c @ 0x0229cc4c, 0x50 bytes, Thumb
 * func_ov129_0229cc08 @ 0x0229cc08, 0x44 bytes, Thumb
 * func_ov129_0229cbdc @ 0x0229cbdc, 0x2c bytes, Thumb
 * func_ov129_0229cb08 @ 0x0229cb08, 0xd4 bytes, Thumb
 * func_ov129_0229cadc @ 0x0229cadc, 0x2c bytes, Thumb
 * func_ov129_0229ca70 @ 0x0229ca70, 0x6c bytes, Thumb
 * func_ov129_0229ca04 @ 0x0229ca04, 0x6c bytes, Thumb
 * func_ov129_0229c8ec @ 0x0229c8ec, 0x118 bytes, Thumb
 * func_ov129_0229c8b8 @ 0x0229c8b8, 0x34 bytes, Thumb
 * func_ov129_0229c890 @ 0x0229c890, 0x28 bytes, Thumb
 * func_ov129_0229c874 @ 0x0229c874, 0x1c bytes, Thumb
 * func_ov129_0229c848 @ 0x0229c848, 0x2a bytes, Thumb
 * func_ov129_0229c820 @ 0x0229c820, 0x26 bytes, Thumb
 * func_ov129_0229c79c @ 0x0229c79c, 0x84 bytes, Thumb
 * func_ov129_0229c758 @ 0x0229c758, 0x44 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
    char pad_9C[0xae - 0x9c];
    u8 unk_AE;
    char pad_AF[0x1d4 - 0xaf];
    char unk_1D4[0x3a0 - 0x1d4];
    char unk_3A0[0x734 - 0x3a0];
    char unk_734[4];
} UnkStruct_0229cd54;

typedef struct UnkStruct_0229cb08 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
    u8 pad_9C[0xad - 0x9c];
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_end[0x734 - 0xaf];
} UnkStruct_0229cb08;

struct UnkStruct_0229c8ec {
    char pad_00[0xaf];
    unsigned char unk_AF;
};

struct UnkStruct_0229c8ec_2 {
    unsigned short unk_00;
    unsigned short unk_02;
};

extern int func_ov002_02208014(void *receiver);
extern void func_ov129_0229c328(UnkStruct_0229cd54 *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov129_0229c39c(UnkStruct_0229cd54 *);
extern void func_ov129_0229c2d8(UnkStruct_0229cd54 *);
extern int func_ov002_0220a620(void *, int);
extern void func_ov127_02299b58(void *, int);
extern int func_ov127_02299abc(void *, int, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov129_0229b7dc(void *self, int arg);
extern void func_ov129_0229c1f8(void *self);
extern void func_ov129_0229c3f4(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov129_0229c574(void *self, int arg);
extern unsigned short data_021fbe40[];
extern void func_ov129_0229c2fc(void *);
extern void func_ov127_02299bbc(void *, unsigned char);
extern void func_ov127_02299c08(void *, unsigned char, int);
extern void func_ov129_0229c348(void *p);
extern int func_0208e484(void *p);
extern int func_ov127_02299b78(void *p);
extern int func_ov002_02209f64(void *p);
extern void func_ov129_0229d780(void *p);
extern int func_ov129_0229b7ec(UnkStruct_0229cb08 *, int);
extern int func_ov129_0229bd4c(UnkStruct_0229cb08 *, s32, s32);
extern int func_ov129_0229b800(UnkStruct_0229cb08 *);
extern int func_ov002_0220a700(unsigned char *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220a6e0(unsigned char *);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a72c(unsigned char *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208054(void *p, int a);
extern int func_ov002_0220a784(void *p, int a);
extern unsigned char *func_ov129_0229d380(void *p);
extern void func_ov129_0229c684(void *p);
extern void func_ov129_0229c644(void *p);
extern unsigned char *func_ov129_0229d3e0(struct UnkStruct_0229c8ec *self);
extern void func_ov002_0220a1dc(void *ptr);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern void func_ov129_0229c368(struct UnkStruct_0229c8ec *self, int a, int b);
extern int func_ov002_0220b8ac(char *p, int n);
extern void func_0208e5cc(char *p);
extern void func_ov129_0229c4b8(void *p);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);
extern void func_ov129_0229b7cc(void *p, int n);
extern void *func_ov002_0220a720(void *p, int n);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov129_0229bee4(void *p, int n);
extern void func_020b15b8(void *p, int *a, int *b);
extern void func_ov127_022999c0(void *p, int x, int y);
extern void func_0200467c(int cmd);

void func_ov129_0229c874(void *r0);
void func_ov129_0229c820(int r0);
void func_ov129_0229c79c(unsigned char *self);
void func_ov129_0229c758(void *param);

void func_ov129_0229cd54(UnkStruct_0229cd54 *p)
{
    int x0;
    int y0;

    if (func_ov002_02208014(p) != 0) {
        func_ov129_0229c874((void *) p);
        return;
    }
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h2 &
         1) != 0) {
        func_ov129_0229c328(p);
        return;
    }
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h2 &
         0x800) != 0) {
        func_ov129_0229b7cc((void *) p, 2);
        func_ov002_02208098((void *) (p), 4);
        func_ov129_0229c39c(p);
        func_ov129_0229c2d8(p);
        return;
    }
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h2 &
         8) != 0) {
        if (func_ov002_0220a620(p->unk_1D4, 6) != 0) {
            return;
        }
        func_ov129_0229b7cc((void *) p, 2);
        p->unk_AE = 4;
        func_ov129_0229c2d8(p);
        func_ov129_0229c3f4((void *) p);
        func_ov129_0229c79c((unsigned char *) p);
        return;
    }
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h2 &
         2) != 0) {
        func_ov129_0229b7cc((void *) p, 2);
        p->unk_AE = 5;
        func_ov129_0229c2d8(p);
        func_ov129_0229c3f4((void *) p);
        func_ov129_0229c758((void *) p);
        return;
    }

    x0 = p->unk_94;
    y0 = p->unk_98;
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h0 &
         0x20) != 0) {
        p->unk_94 = p->unk_94 - 4;
    } else if (((*(struct {
                    u16 h0;
                    u16 h2;
                } *) data_021fbe40)
                    .h0 &
                0x10) != 0) {
        p->unk_94 = p->unk_94 + 4;
    }
    if (((*(struct {
             u16 h0;
             u16 h2;
         } *) data_021fbe40)
             .h0 &
         0x40) != 0) {
        p->unk_98 = p->unk_98 - 4;
    } else if (((*(struct {
                    u16 h0;
                    u16 h2;
                } *) data_021fbe40)
                    .h0 &
                0x80) != 0) {
        p->unk_98 = p->unk_98 + 4;
    }
    if (x0 == p->unk_94 && y0 == p->unk_98) {
        return;
    }
    if (p->unk_94 < 0x30) {
        p->unk_94 = 0x30;
        func_ov127_02299b58(p->unk_734, -4);
        func_ov129_0229b7dc((void *) p, 0x40);
    } else if (p->unk_94 > 0xd0) {
        p->unk_94 = 0xd0;
        func_ov127_02299b58(p->unk_734, 4);
        func_ov129_0229b7dc((void *) p, 0x40);
    }
    if (p->unk_98 < 0x1c) {
        p->unk_98 = 0x1c;
        if (func_ov127_02299abc(p->unk_734, -4, 0) != 0) {
            func_ov129_0229b7dc((void *) p, 0x40);
        }
    } else if (p->unk_98 > 0xac) {
        p->unk_98 = 0xac;
        if (func_ov127_02299abc(p->unk_734, 4, 0) != 0) {
            func_ov129_0229b7dc((void *) p, 0x40);
        }
    }
    func_ov129_0229c1f8((void *) p);
    func_ov002_0220a0b4(p->unk_3A0, p->unk_94, p->unk_98);
}

void func_ov129_0229cc9c(void *self)
{
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov129_0229c874(self);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        func_ov129_0229c328((UnkStruct_0229cd54 *) self);
        return;
    } else if (flags & 0x800) {
        func_ov129_0229b7dc(self, 2);
        func_ov129_0229c1f8(self);
        func_ov002_02208098((void *) (self), 3);
        func_ov129_0229c39c((UnkStruct_0229cd54 *) self);
        return;
    } else if (flags & 8) {
        if (func_ov002_0220a620((char *) self + 0x1d4, 6) == 0) {
            func_ov129_0229c3f4(self);
            func_ov129_0229c79c((unsigned char *) self);
        }
        return;
    } else if (flags & 2) {
        func_ov129_0229c3f4(self);
        func_ov129_0229c758(self);
        return;
    } else {
        if (func_ov129_0229c574(self, func_ov002_02208008(self)) != 0) {
            func_ov129_0229c39c((UnkStruct_0229cd54 *) self);
        }
        return;
    }
}

void func_ov129_0229cc4c(unsigned char *a)
{
    if (!((*(unsigned short *) data_021fbe40) & 1)) {
        func_ov002_02208098((void *) (a), 4);
        func_ov129_0229c2fc(a);
        func_ov002_02208098((void *) (a), 6);
        func_ov127_02299bbc(a + 0x734, *(unsigned char *) (a + 0xad));
    } else {
        func_ov127_02299c08(a + 0x734, *(unsigned char *) (a + 0xad), 0);
    }
}

void func_ov129_0229cc08(void *p)
{
    if (func_ov127_02299b78((char *) p + 0x734)) {
        func_ov129_0229c348(p);
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xac));
    }
    if (func_0208e484((char *) p + 0x3a0)) {
        func_ov129_0229c348(p);
    }
}

void func_ov129_0229cbdc(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x3a0) == 0) {
        func_ov002_02208098((void *) (self), *((unsigned char *) self + 0xac));
        func_ov129_0229d780(self);
    }
}

void func_ov129_0229cb08(UnkStruct_0229cb08 *self)
{
    if (func_0208e484((char *) self + 0x3a0) == 0) {
        return;
    }
    if (func_ov129_0229b7ec(self, 2)) {
        if (func_ov129_0229bd4c(self, self->unk_94, self->unk_98) != 0) {
            if (func_ov129_0229b800(self) == 3) {
                return;
            }
        }
        func_ov129_0229c1f8((void *) self);
        func_ov002_02208098((void *) (self), 3);
        func_ov129_0229c2fc((void *) self);
    } else {
        switch (self->unk_AE) {
            case 4:
                if (func_ov002_0220a620((char *) self + 0x1d4, 6) == 0) {
                    func_ov129_0229c79c((unsigned char *) self);
                } else {
                    func_ov002_02208098((void *) (self), 4);
                    func_ov129_0229c2fc((void *) self);
                }
                break;
            case 5:
                func_ov129_0229c758((void *) self);
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                self->unk_AD = self->unk_AE;
                func_ov127_02299c08((char *) self + 0x734, self->unk_AD, 0);
                func_ov002_02208098((void *) (self), 5);
                break;
            default:
                break;
        }
    }
}

void func_ov129_0229cadc(void *p)
{
    if (func_0208e484((char *) p + 0x3a0)) {
        func_ov129_0229c348(p);
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xac));
    }
}

void func_ov129_0229ca70(unsigned char *p)
{
    if (func_ov002_0220a700(p + 0x1d4)) {
        if (func_0208e4bc(p + 0x3a0)) {
            int a = func_ov002_0220a6e0(p + 0x1d4);
            int b = func_ov002_0220a768(p + 0x1d4, -1);
            int c = func_ov002_0220a72c(p + 0x1d4, -1);
            func_ov002_0220a0b4((void *) (p + 0x3a0), a + b, a + c);
        }
    } else {
        func_ov129_0229c3f4((void *) p);
        func_ov002_022080a0((void *) (p), 1);
    }
}

void func_ov129_0229ca04(void *param)
{
    unsigned int flag;

    if (func_ov002_02208054(param, 1)) {
        func_ov129_0229d380(param);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (flag != 0) {
        if (func_ov002_0220a784((char *) param + 0x1d4, 3)) {
            func_ov129_0229c684(param);
            return;
        }
        if (func_ov002_0220a784((char *) param + 0x1d4, 4)) {
            func_ov129_0229c644(param);
            return;
        }
    }
}

void func_ov129_0229c8ec(struct UnkStruct_0229c8ec *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov129_0229d3e0(self);
        return;
    }
    {
        unsigned short flags = (*(struct UnkStruct_0229c8ec_2 *) data_021fbe40).unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc((char *) self + 0x3a0);
            func_ov002_02208098((void *) (self), 0xd);
            return;
        }
        if ((flags & 2) != 0) {
            func_ov129_0229c3f4((void *) self);
            func_ov129_0229c644((void *) self);
            return;
        }
        if ((flags & 8) != 0) {
            func_ov129_0229c3f4((void *) self);
            func_ov129_0229c684((void *) self);
            return;
        }
    }
    {
        unsigned char old = ((unsigned char *) self)[0xaf];
        void *p = (void *) func_ov002_02208008((void *) self);
        if (func_ov002_022088ac(p) != 0) {
            if (((unsigned char *) self)[0xaf] != 0) {
                ((unsigned char *) self)[0xaf]--;
            }
        } else {
            if (func_ov002_0220889c(p) != 0) {
                if (((unsigned char *) self)[0xaf] < 1) {
                    ((unsigned char *) self)[0xaf]++;
                }
            }
        }
        {
            unsigned char cur = ((unsigned char *) self)[0xaf];
            if (old != cur) {
                if (cur != 0) {
                    int x = func_ov002_0220a768((unsigned char *) ((char *) self + 0x1d4), 4);
                    int y = func_ov002_0220a72c((unsigned char *) ((char *) self + 0x1d4), 4);
                    func_ov129_0229c368(self, x, y);
                } else {
                    int x = func_ov002_0220a768((unsigned char *) ((char *) self + 0x1d4), 3);
                    int y = func_ov002_0220a72c((unsigned char *) ((char *) self + 0x1d4), 3);
                    func_ov129_0229c368(self, x, y);
                }
            }
        }
    }
}

void func_ov129_0229c8b8(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x3a0) != 0) {
        if (*(unsigned char *) ((char *) arg0 + 0xaf) != 0) {
            func_ov129_0229c644(arg0);
        } else {
            func_ov129_0229c684(arg0);
        }
    }
}

void func_ov129_0229c890(char *p)
{
    if (func_ov002_0220b8ac(p + 0xb8, 0)) {
        func_ov129_0229c820((int) p);
        func_0208e5cc(p + 0x3a0);
    }
}

void func_ov129_0229c874(void *r0)
{
    void *r4 = r0;
    func_ov129_0229c3f4(r4);
    func_ov129_0229c2d8((UnkStruct_0229cd54 *) r4);
    func_ov002_02208098((void *) (r4), 0);
}

void func_ov129_0229c848(void *p)
{
    func_ov129_0229b7dc(p, 2);
    func_ov129_0229c4b8(p);
    func_ov002_02207fc0(p);
    func_ov129_0229c1f8(p);
    func_ov002_02208098((void *) (p), 3);
}

void func_ov129_0229c820(int r0)
{
    int r4 = r0;
    func_ov129_0229b7dc((void *) r4, 0x80);
    if (func_0206fe60() != 0) {
        func_ov129_0229c874((void *) r4);
    } else {
        func_ov129_0229c848((void *) r4);
    }
}

void func_ov129_0229c79c(unsigned char *self)
{
    int x, y;

    func_ov129_0229b7cc(self, 4);
    func_ov002_0220a720(self + 0x1d4, 6);
    func_ov002_02208090(self, 4);
    func_ov002_02208098((void *) (self), 10);
    func_ov129_0229b7cc(self, 16);
    func_ov129_0229bee4(self, 0);
    func_020b15b8(self + 0x2f78, &x, &y);
    x &= 0xfffc;
    y &= 0xfffc;
    func_ov127_022999c0(self + 0x734, x, y);
    func_0200467c(0x87f);
    func_ov129_0229b7cc(self, 0x80);
}

void func_ov129_0229c758(void *param)
{
    func_ov129_0229b7dc(param, 4);
    func_ov002_0220a720((char *) param + 0x1d4, 5);
    func_ov002_02208090(param, 4);
    func_ov002_02208098((void *) (param), 0xa);
    func_ov129_0229b7cc(param, 0x10);
    func_0200467c(0x2a);
    func_ov129_0229b7cc(param, 0x80);
}
