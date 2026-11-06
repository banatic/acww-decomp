/* pockets_box_scene_2: 15 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229e3a8 @ 0x0229e3a8, 0x8 bytes, Thumb
 * func_ov100_0229e374 @ 0x0229e374, 0x34 bytes, Thumb
 * func_ov100_0229e33c @ 0x0229e33c, 0x38 bytes, Thumb
 * func_ov100_0229e308 @ 0x0229e308, 0x32 bytes, Thumb
 * func_ov100_0229e2f4 @ 0x0229e2f4, 0x14 bytes, Thumb
 * func_ov100_0229e218 @ 0x0229e218, 0xdc bytes, Thumb
 * func_ov100_0229e208 @ 0x0229e208, 0x10 bytes, Thumb
 * func_ov100_0229e17c @ 0x0229e17c, 0x8c bytes, Thumb
 * func_ov100_0229e124 @ 0x0229e124, 0x58 bytes, Thumb
 * func_ov100_0229e098 @ 0x0229e098, 0x8c bytes, Thumb
 * func_ov100_0229df98 @ 0x0229df98, 0x100 bytes, Thumb
 * func_ov100_0229de18 @ 0x0229de18, 0x180 bytes, Thumb
 * func_ov100_0229dd54 @ 0x0229dd54, 0xc4 bytes, Thumb
 * func_ov100_0229dcd8 @ 0x0229dcd8, 0x7c bytes, Thumb
 * func_ov100_0229dc88 @ 0x0229dc88, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x218C];
    void *unk_218C;
    char pad_2190[0x2921 - 0x218C - 4];
    unsigned char unk_2921;
} UnkStruct_0229de18;

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x793];
    unsigned char unk_2920;
    unsigned char unk_2921;
} Object;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} Globals;

extern void func_ov100_0229d63c(void *);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov100_0229c5e0(void *);
extern void func_ov100_0229cf30(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);

// Twin of func_ov110_0229e1dc; only the overlay data symbols and the two tail calls differ.

extern void *data_021fbe94;
extern u8 data_ov100_0229ed18[];
extern u8 data_ov100_0229ed3c[];
extern u8 data_ov100_0229ed5c[];
extern u8 data_ov100_0229ed74[];
extern u8 data_ov100_0229ed8c[];
extern u8 data_ov100_0229eda4[];
extern u8 data_ov100_0229edbc[];
extern u8 data_ov100_0229edd4[];
extern u8 data_ov100_0229edec[];
extern u8 data_ov100_0229ee04[];
extern int func_02002ca4(u8 *, void *, int);
extern int func_02002c6c(u8 *, void *, int, int, int, int);
extern int func_02002d14(u8 *, void *, int, int, int, int);
extern int func_0206fca4(void);
extern void func_ov100_0229c56c(void *, int);
extern void func_ov100_0229c528(void *, int);
extern int func_ov094_0229a098(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov100_0229d8d0(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov100_0229d550(void *self, int a, int b, int c);
extern void func_ov100_0229d824(void *self, int n);
extern void func_ov100_0229c4ec(void *self);
extern void func_ov100_0229c3c0(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207ce4(unsigned char *p, int n);
extern int func_ov100_0229c2c0(unsigned char *p, int n);
extern int func_ov100_0229cfd0(void *self);
extern void func_ov100_0229d7d8(unsigned char *p, unsigned char c);
extern void func_ov100_0229c940(void *self);
extern int func_ov002_02208b00(void *ptr, int a, int b);
extern void func_ov002_02209114(void *ptr, int a, int b);
extern void func_ov100_0229ce58(void *self);
extern void func_ov100_0229d04c(void *self);
extern int func_ov100_0229d620(void *self, int a);
extern int func_ov100_0229d630(void *self, int a);
extern int func_ov100_0229d118(void *self, int a);
extern int func_ov100_0229d194(void *self, int a);
extern int func_ov100_0229d4f4(void *self, int a);
extern void func_ov100_0229d6d8(void *self, int a, int b);
extern void func_ov100_0229d8b0(void *self);
extern void func_ov100_0229d014(void *self, int a);
extern void func_ov094_022999d8(void);
extern int func_ov002_02208014(void *receiver);
extern int func_ov100_0229c60c(UnkStruct_0229de18 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov100_0229d90c(UnkStruct_0229de18 *s);
extern void func_ov100_0229cecc(UnkStruct_0229de18 *s);
extern void func_ov100_0229cbd4(UnkStruct_0229de18 *s);
extern int func_ov100_0229d158(UnkStruct_0229de18 *s, unsigned char b);
extern void func_ov100_0229ca1c(UnkStruct_0229de18 *s);
extern int func_ov100_0229d60c(UnkStruct_0229de18 *s, unsigned char b);
extern void func_ov100_0229ca5c(UnkStruct_0229de18 *s);
extern int func_ov100_0229d648(UnkStruct_0229de18 *s);
extern int func_ov100_0229d67c(void *receiver);
extern void func_ov100_0229d69c(UnkStruct_0229de18 *s, unsigned char b, int v);
extern void func_ov100_0229cc3c(UnkStruct_0229de18 *s);
extern int func_ov002_02208008(void *unused0);
extern void func_ov100_0229c9e0(void *self, unsigned char b);
extern void func_ov100_0229c994(void *self, unsigned char b);
extern void func_ov100_0229ce24(void *self);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov002_0220a1dc(void *p);
extern void func_ov100_0229cb80(void *p);
extern void func_ov100_0229cb1c(void *p);
extern unsigned short data_021fbe40[];
extern int func_0208e484(void *);

void func_ov100_0229e33c(void *self);

void func_ov100_0229e3a8(void *argument0)
{
    func_ov100_0229e33c(argument0);
}

void func_ov100_0229e374(void *self)
{
    func_ov100_0229d63c(self);
    func_ov094_0229a084((char *) self + 0xb54);
    func_ov094_0229af20((char *) self + 0xcc);
    func_ov094_0229bbc0((char *) self + 0xb2c);
    func_ov100_0229c5e0(self);
}

void func_ov100_0229e33c(void *self)
{
    func_ov002_022091cc((char *) self + 0x22d8);
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov100_0229cf30(self);
    }
}

void func_ov100_0229e308(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov100_0229e2f4(int a)
{
    func_ov094_0229a29c(a + 0xb54, 0);
}

void func_ov100_0229e218(void *o)
{
    void *p;
    u8 *a;
    u8 *b;
    int t;

    p = data_021fbe94;
    func_02002ca4(data_ov100_0229ed18, p, 4);
    func_02002c6c(data_ov100_0229ed3c, p, 4, 0x1b9, 0x1b9, 0x238);
    t = func_0206fca4();
    a = 0;
    b = a;
    switch (t) {
        case 0x1d:
            a = data_ov100_0229ed5c;
            b = data_ov100_0229ed74;
            break;
        case 0x1e:
            a = data_ov100_0229ed8c;
            b = data_ov100_0229eda4;
            break;
        case 0x1f:
            a = data_ov100_0229edbc;
            b = data_ov100_0229edd4;
            break;
        case 0x20:
            a = data_ov100_0229edec;
            b = data_ov100_0229ee04;
            break;
    }
    if (a != 0) {
        func_02002d14(a, p, 4, 3, 3, 5);
    }
    if (b != 0) {
        func_02002c6c(b, p, 4, 0x208, 0x208, 0x238);
    }
    func_ov100_0229c56c(o, 0);
    func_ov100_0229c528(o, 0);
}

int func_ov100_0229e208(int arg)
{
    return func_ov094_0229a098((void *) (arg + 0xb54));
}

void func_ov100_0229e17c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov100_0229d8d0(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov100_0229d550(self, a, b, 1);
    if (n != 0x20) {
        func_ov100_0229d824(self, n);
        return;
    }
    if (a < 0xc8) {
        return;
    }
    if (a > 0xf8) {
        return;
    }
    if (b < 0x50) {
        return;
    }
    if (b > 0x70) {
        return;
    }
    if (b >= 0x60) {
        func_ov100_0229c4ec(self);
        return;
    }
    func_ov100_0229c3c0(self);
}

void func_ov100_0229e124(unsigned char *p)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (p), 0);
        func_ov002_02207ce4(p + 0x218c, 0x3c);
    } else {
        if (func_ov100_0229c2c0(p, 4) != 0 && func_ov100_0229cfd0(p) != 0) {
            func_ov100_0229d7d8(p, p[0x291e]);
        } else {
            func_ov002_02207d00((void *) (p + 0x218c));
        }
    }
}

void func_ov100_0229e098(unsigned char *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov100_0229c940(self);
    } else {
        unsigned int cond = (data_021fbdd8 != 0 && (*(unsigned char *) &data_021fbddc) != 0);
        if (cond > 0) {
            int ret =
                func_ov002_02208b00(self + 0x22d8, (*(unsigned char *) &data_021f6c58), (*(unsigned char *) &data_021f6c54));
            if (ret >= 0) {
                func_ov002_02209114(self + 0x22d8, ret, 1);
                *(self + 0x2925) = *(self + ret + 0x26c5);
                func_ov002_02208098((void *) (self), 0x12);
            }
        }
    }
}

void func_ov100_0229df98(void *self)
{
    int extra, p2, state;

    func_ov100_0229ce58(self);
    func_ov100_0229d04c(self);

    extra = *(int *) ((char *) self + 0x28d8) + 8;
    p2 = *(int *) ((char *) self + 0x28d4) + 8;
    state = func_ov100_0229d550(self, p2, extra, 0);

    if (!func_ov100_0229c2c0((unsigned char *) self, 0x200)) {
        goto far;
    }
    if (func_ov100_0229d620(self, state) && func_ov100_0229d630(self, *(unsigned char *) ((char *) self + 0x2920))) {
        goto l2;
    }
    if (!func_ov100_0229d630(self, state)) {
        goto far;
    }
    if (!func_ov100_0229d620(self, *(unsigned char *) ((char *) self + 0x2920))) {
        goto far;
    }
l2:
    if (func_ov100_0229d118(self, state) == 0xfff1) {
        goto far;
    }
    state = 0x20;
far:
    if (state == 0x20) {
        goto bigend;
    }
    if (data_021fbdd8 != 0) {
        goto elsebranch;
    }
    if (func_ov100_0229d194(self, state)) {
        func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
        goto end;
    } else {
        if (func_ov100_0229d4f4(self, state)) {
            goto extblock;
        }
        func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
        goto end;
    extblock:
        func_ov094_022999d8();
        func_ov100_0229d8b0(self);
        goto end;
    }
elsebranch:
    func_ov100_0229d014(self, state);
    goto end;
bigend:
    if (data_021fbdd8 != 0) {
        goto end;
    }
    func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
end:
    return;
}

void func_ov100_0229de18(UnkStruct_0229de18 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov100_0229d90c(s);
        func_ov002_02207d24((char *) s + 0x218C, 1);
        return;
    }
    if (func_ov100_0229c60c(s, func_ov002_02208008((void *) s), 0) != 0) {
        func_ov100_0229cecc(s);
        func_ov100_0229cbd4(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov100_0229d194((void *) s, (unsigned char) s->unk_2921) == 0) {
        val = (*(struct {
                  char pad2[2];
                  unsigned short field;
              } *) data_021fbe40)
                  .field;
        if (val & 1) {
            if (func_ov100_0229d630((void *) s, (unsigned char) s->unk_2921) != 0 ||
                func_ov100_0229d620((void *) s, (unsigned char) s->unk_2921) != 0) {
                if (func_ov100_0229d158(s, s->unk_2921) == 0) {
                    func_ov100_0229ca1c(s);
                }
            } else if (func_ov100_0229d60c(s, s->unk_2921) != 0) {
                func_ov100_0229ca5c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov100_0229d630((void *) s, (unsigned char) s->unk_2921) != 0 ||
                func_ov100_0229d620((void *) s, (unsigned char) s->unk_2921) != 0) {
                if (func_ov100_0229d158(s, s->unk_2921) == 0) {
                    if (func_ov100_0229d630((void *) s, (unsigned char) s->unk_2921) != 0) {
                        r = func_ov100_0229d648(s);
                    } else {
                        r = func_ov100_0229d67c((void *) s);
                    }
                    if (r != 0x20) {
                        func_ov100_0229d69c(s, s->unk_2921, r);
                        func_ov002_02207d24((char *) s + 0x218C, 1);
                    }
                }
            }
            return;
        }
    }
    val = (*(struct {
              char pad2[2];
              unsigned short field;
          } *) data_021fbe40)
              .field;
    if (val & 2) {
        func_ov100_0229cc3c(s);
        func_ov100_0229c4ec((void *) s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (val & 8) {
        func_ov100_0229cc3c(s);
        func_ov100_0229c3c0((void *) s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x218C);
}

void func_ov100_0229dd54(Object *self)
{
    int r = func_ov002_02208008(self);
    if (func_ov100_0229c60c((UnkStruct_0229de18 *) self, r, 1) != 0) {
        func_ov100_0229cecc((UnkStruct_0229de18 *) self);
        func_ov100_0229cbd4((UnkStruct_0229de18 *) self);
        func_ov002_02207d24((void *) &self->unk_218C, 0);
    } else {
        unsigned short t = (*(Globals *) data_021fbe40).unk_02;
        if ((t & 1) != 0) {
            if (func_ov100_0229d630(self, (unsigned char) self->unk_2921) != 0 ||
                func_ov100_0229d620(self, (unsigned char) self->unk_2921) != 0) {
                if (func_ov100_0229d194(self, (unsigned char) self->unk_2921) == 0) {
                    if (func_ov100_0229d158((UnkStruct_0229de18 *) self, self->unk_2921) != 0) {
                        func_ov100_0229c9e0(self, self->unk_2921);
                    } else {
                        func_ov100_0229c994(self, self->unk_2921);
                    }
                }
            }
        } else if ((t & 2) != 0) {
            func_ov100_0229c9e0(self, self->unk_2920);
        } else {
            func_ov100_0229ce24(self);
            func_ov002_02207d00((void *) &self->unk_218C);
        }
    }
}

void func_ov100_0229dcd8(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov100_0229c940(arg);
        return;
    }
    {
        int v = func_ov002_02208008(arg);
        if (func_ov002_02209044((char *) arg + 0x22d8, v, (char *) arg + 0x2926, 0) != 0) {
            func_ov100_0229cb80(arg);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40[1];
        if (flags & 1) {
            func_ov002_0220a1dc((char *) arg + 0x2274);
            func_ov002_02208098((void *) (arg), 7);
            return;
        } else {
            if (flags & 2) {
                func_ov100_0229cb1c(arg);
            }
        }
    }
}

void func_ov100_0229dc88(unsigned char *self)
{
    if (func_0208e484(self + 0x2274) == 0) {
        return;
    }
    func_ov002_02209114(self + 0x22d8, (unsigned char) self[0x2926], 1);
    self[0x2925] = *(self + self[0x2926] + 0x26c5);
    func_ov002_02208098((void *) (self), 0x12);
}
