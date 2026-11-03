/* flea_market_buyer_2: 14 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02220c34 @ 0x02220c34, 0xc bytes, Thumb
 * func_ov004_02220aa8 @ 0x02220aa8, 0x18c bytes, Thumb
 * func_ov004_022209b4 @ 0x022209b4, 0xf4 bytes, Thumb
 * func_ov004_02220834 @ 0x02220834, 0x180 bytes, Thumb
 * func_ov004_02220808 @ 0x02220808, 0x2c bytes, Thumb
 * func_ov004_022207fc @ 0x022207fc, 0xc bytes, Thumb
 * func_ov004_022206d8 @ 0x022206d8, 0x124 bytes, Thumb
 * func_ov004_022206c0 @ 0x022206c0, 0x18 bytes, Thumb
 * func_ov004_0222050c @ 0x0222050c, 0x1b4 bytes, Thumb
 * func_ov004_022204ec @ 0x022204ec, 0x20 bytes, Thumb
 * func_ov004_022204cc @ 0x022204cc, 0x20 bytes, Thumb
 * func_ov004_022203e0 @ 0x022203e0, 0xec bytes, Thumb
 * func_ov004_02220318 @ 0x02220318, 0xc8 bytes, Thumb
 * func_ov004_02220210 @ 0x02220210, 0x108 bytes, Thumb
 */

#include "types.h"

#define OBJ (*(UnkStruct_022206d8 **) (self + 0x1a4))
#define W(p, o) (*(int *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))

struct OUT {
    void *unk_00;
    u8 unk_04;
};

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0xac8 - 0x834];
    u8 unk_AC8;
    char pad_AC9[0xadc - 0xac9];
    u8 unk_ADC;
} UnkStruct_022206d8;

typedef struct {
    u8 message;
    u16 item;
} UnkStruct_0222050c;

typedef void (*VF)(char *);

typedef struct {
    int x, y, z;
} Vec3;

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_020644cc(int n);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0204c878(void *p);
extern void *func_020984e8(void);
extern void *func_02099870(void *p);
extern int func_020807a8(void *a, void *b);
extern int func_02081d20(int h);
extern int _fflt(int x);
extern int _fadd(int a, int b);
extern int _fsub(int a, int b);
extern int _ffix(int f);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_0206f83c(void);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern void func_0208b520(void);
extern void *func_0208150c(void *p);
extern int func_0200366c(void *a, void *b, int n, void *c);
extern char data_ov004_02257df0[];
extern char data_ov004_02253ed0[];
extern int func_020804e8(int a);
extern void func_02081ac0(int a, char *b);
extern void func_0207df18(int a, char *b);
extern int func_ov004_0223bb14(int a);
extern int func_020804b8(void *a, void *b);
extern void func_02081e14(int r, int a, int b, int c);
extern void func_02015de4(void *self, void *p, int a, int b);
extern char data_ov004_02257e40[];
extern char data_ov004_02253ee4[];
extern char data_ov004_02253ef0[];
extern u8 data_020e54a8;
extern void func_0206844c(void *, u8 *, void *);
extern void func_0207d540(void *, void *);
extern void func_ov004_02221550(void *self, int a);
extern void func_0208b514(unsigned);
extern char data_ov004_02257e68;
extern char data_ov004_02253edc;
extern char data_021f43e8;
extern void *func_020160b4(void *);
extern void *func_02099734(void *);
extern int func_020ab504(void *);
extern int func_02015828(void *, int);
extern int func_0201b3c0(void *, int, int);
extern int func_0204c120(int, int, void *);
extern int func_02098a6c(void *, int, int, int);
extern void func_020157c8(void *, int, int);
extern void func_0201b3a4(void *, int);
extern int func_020154b4(void *, u16 *, int, int, int);
extern u8 data_ov004_02257e18[];
extern int func_02014868(int);
extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cdc0(int *);
extern void func_020b23d4(void);
extern int func_02030864(int a);
extern void func_ov004_0223d33c(void);
extern void func_0209e474(char *p);
extern int *func_02095794(int n);
extern int func_02030818(int *v);
extern int func_020307f8(void);
extern int func_0203e0a8(void *s, int a);
extern int func_0203ec98(void);
extern int func_0209e350(void *p, int *q);
extern u16 func_0204bc50(int a, int b);
extern int func_ov004_02220084(void *self, int i);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0220fde0(void *p);
extern void func_ov004_0220fefc(void *e, void *dst);
extern void func_ov004_02220018(void *self, void *e);
extern void func_ov004_0222005c(void *self, int i);

void func_ov004_02220c34(void *self, int v)
{
    *(int *) ((char *) self + 0x1ac) = v;
}

static __inline int chk(u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

void func_ov004_02220aa8(void *self)
{
    // DECLS
    int saved;
    int h;
    int v;
    int t;
    // ENDDECLS
    u8 code;

    saved = *(int *) ((char *) self + 0x40);
    code = (u8) (func_020644cc(2) + 8);
    *(int *) ((char *) self + 0x1a8) = 0;
    if (func_0206fbc0() == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        h = 0;
        v = 0;
        if (chk((u16 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898), 0xfff1) == 0) {
            *(int *) ((char *) self + 0x1a8) = func_0204c878((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
            if (func_020984e8() != 0) {
                h = func_020807a8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830),
                                  func_02099870(func_020984e8()));
            }
            if (h != 0) {
                v = func_02081d20(h);
            }
            v += 0xff;
            if (v > 0) {
                t = _fadd(0x3f000000, _fflt(v << 12));
            } else {
                t = _fsub(_fflt(v << 12), 0x3f000000);
            }
            v = FX_Div(_ffix(t), 0x200000);
            func_02015fb0(self, func_0206f83c(), 0, 0xa, 0, 0);
            v = FX_MulFunc(*(int *) ((char *) self + 0x1a8), v);
            if (v <= 0xa) {
                v = 0xa;
            }
            if (func_0206f83c() > v) {
                code = (u8) (func_020644cc(2) + 0xa);
            } else {
                *(int *) ((char *) self + 0x1a8) = func_0206f83c();
                code = (u8) (func_020644cc(2) + 0xc);
                func_0208b520();
            }
        }
    }
    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)), data_ov004_02257df0, 0x28,
                  data_ov004_02253ed0);
    func_0206844c((void *) saved, (u8 *) (&code), data_ov004_02257df0);
    func_ov004_02220c34(self, 0);
}

void func_ov004_022209b4(char *self)
{
    // DECLS
    u16 t;
    char *e;
    char *o;
    int ok;
    int r;
    int i;
    // ENDDECLS

    e = *(char **) (self + 0x1a4) + 0x898;
    if (func_0204bcdc((void *) e) != 0) {
        t = 0xfff1;
        ok = (func_0204bc64(e) == func_0204bc64(&t)) ? 1 : 0;
    } else {
        ok = (*(u16 *) e == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }
    o = *(char **) (self + 0x1a4);
    if (*(int *) (o + 0x8a8) == -1) {
        return;
    }
    if ((int) func_0208150c((void *) (*(int *) (o + 0x830))) != 0) {
        r = func_020804e8(*(int *) (*(char **) (self + 0x1a4) + 0x830));
        if (r != 0) {
            func_02081ac0(r, *(char **) (self + 0x1a4) + 0x898);
        }
        func_0207df18(*(int *) (*(char **) (self + 0x1a4) + 0x830), *(char **) (self + 0x1a4) + 0x898);
    }
    func_ov004_0223bb14(*(int *) (*(char **) (self + 0x1a4) + 0x8a8));
    *(int *) (*(char **) (self + 0x1a4) + 0x8a8) = -1;
    *(u16 *) (*(char **) (self + 0x1a4) + 0x898) = 0xfff1;
    (*(u8 *) (*(char **) (self + 0x1a4) + 0xae0))++;
    for (i = 0; i < 0x64; i++) {
        *(u8 *) (*(char **) (self + 0x1a4) + i + 0x8ac) = 0xff;
    }
}

void func_ov004_02220834(void *self, struct OUT *out)
{
    // DECLS
    int res;
    void *g;
    unsigned int st;
    u16 *p;
    // ENDDECLS

    res = func_020804b8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), func_02099870(func_020984e8()));
    if (res != 0) {
        func_02081e14(res, 0, 0, 0);
    }
    g = *(void **) ((char *) self + 0x1a4);
    st = *(u8 *) ((char *) g + 0xac8);
    if (st == 5) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ee4);
        out->unk_00 = data_ov004_02257e40;
        out->unk_04 = (u8) func_020644cc(3);
    } else if (st == 3) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
        out->unk_00 = data_ov004_02257e40;
        out->unk_04 = (u8) (func_020644cc(2) + 2);
    } else {
        switch (st) {
            case 0:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ef0);
                out->unk_04 = (u8) func_020644cc(3);
                break;
            case 1:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
                out->unk_04 = (u8) func_020644cc(2);
                break;
            case 2:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
                p = (u16 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
                if (chk(p, 0xfff1) || *(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x914) == 5) {
                    out->unk_04 = (u8) (func_020644cc(2) + 4);
                } else {
                    func_02015de4(self, (char *) *(void **) ((char *) self + 0x1a4) + 0x898, 0, 7);
                    out->unk_04 = (u8) (func_020644cc(2) + 6);
                }
                break;
        }
        out->unk_00 = data_ov004_02257e40;
    }
}

int func_ov004_02220808(u8 *self)
{
    unsigned int t;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t == 0 || self[0xade] == 0) {
        return 1;
    }
    return 0;
}

void *func_ov004_022207fc(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xade) = 0x1;
    return self;
}

void func_ov004_022206d8(char *self)
{
    u8 state;
    u8 mode;
    u8 buf;

    {
        UnkStruct_022206d8 *obj = OBJ;
        mode = obj->unk_AC8;
    }
    if (mode == 5 || mode == 3) {
        if (mode == 5) {
            OBJ->unk_AC8 = 6;
        } else {
            OBJ->unk_AC8 = 4;
        }
        func_0200366c(func_0208150c(OBJ->unk_830), &data_ov004_02257e68, 0x28, &data_ov004_02253edc);
        buf = (u8) func_020644cc(3);
        func_0206844c(*(void **) (self + 0x40), &buf, &data_ov004_02257e68);
        return;
    }

    state = *(u8 *) (self + 0x1e);

    switch (state) {
        case 0:
        case 1:
        case 2:
            if (mode == 6 || mode == 1) {
                func_0206844c(*(void **) (self + 0x40), (u8 *) &data_021f43e8, 0);
            } else if (mode == 0) {
                void *have;
                if (func_020984e8() != 0) {
                    have = func_02099870(func_020984e8());
                } else {
                    have = 0;
                }
                if (OBJ->unk_830 != 0 && have != 0) {
                    func_0207d540(OBJ->unk_830, have);
                }
                OBJ->unk_AC8 = 1;
                OBJ->unk_ADC = 0x28;
                func_0206844c(*(void **) (self + 0x40), (u8 *) &data_021f43e8, 0);
                func_ov004_02221550(OBJ, 1);
            }
            break;
        case 8:
        case 9:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            func_0208b514(mode);
            break;
        default:
            break;
    }
}

int func_ov004_022206c0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) ((char *) *(int *) (self + 0x1a4) + 0x898) = 0xfff1;
    return 0x898;
}

void func_ov004_0222050c(u8 *self)
{
    int status;
    u8 message;
    UnkStruct_0222050c local;
    status = func_020ab504(func_020160b4(self));
    message = 255;
    if (P(self, 0x1a4)[0xac8] == 2) {
        switch (self[0x1e]) {
            case 6:
            case 7:
            case 10:
            case 11:
                func_0200366c(func_0208150c(P(P(self, 0x1a4), 0x830)), data_ov004_02257e18, 40, ((u8 *) data_ov004_02253ed0));
                if (status == 0) {
                    func_020157c8(self, 0x38, 0);
                    func_02015828(self, 2);
                    func_ov004_02220c34(self, 1);
                } else {
                    message = func_020644cc(2) + 8;
                    func_ov004_022206c0((char *) self);
                }
                break;
            case 12:
            case 13:
                func_0200366c(func_0208150c(P(P(self, 0x1a4), 0x830)), data_ov004_02257e18, 40, ((u8 *) data_ov004_02253ed0));
                if (status == 0) {
                    void *inventory = func_02099734(func_020984e8());
                    int type = func_0201b3c0(P(self, 0x1a4), W(self, 0x1a8), 0);
                    local.item = func_0204c120(W(self, 0x1a8), 0, 0);
                    if (local.item == 0xfff1) {
                        local.item = 0x1492;
                    }
                    if (!func_02098a6c(inventory, W(self, 0x1a8), 1, 0)) {
                        message = func_020644cc(2) + 18;
                    } else {
                        switch (type) {
                            case 0:
                                func_020154b4(self, &local.item, 0, 5, 0);
                                func_0201b3a4(P(self, 0x1a4), W(self, 0x1a8));
                                message = func_020644cc(2) + 14;
                                func_ov004_022209b4((char *) self);
                                break;
                            case 1:
                                func_020154b4(self, &local.item, 0, 5, 0);
                                message = func_020644cc(2) + 14;
                                func_0201b3a4(P(self, 0x1a4), W(self, 0x1a8));
                                func_ov004_022209b4((char *) self);
                                break;
                            case 2:
                            default:
                                break;
                        }
                    }
                } else {
                    message = func_020644cc(2) + 16;
                    func_ov004_022206c0((char *) self);
                }
                break;
        }
        if (message != 255) {
            local.message = message;
            func_0206844c(P(self, 0x40), &local.message, data_ov004_02257e18);
        }
    }
}

int func_ov004_022204ec(int arg0)
{
    int result;
    int ret;

    result = func_02014868(arg0 + 0x618);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

int func_ov004_022204cc(int arg0)
{
    int result;
    int ret;

    result = func_02014868(arg0 + 0x618);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void func_ov004_022203e0(char *self, int n)
{
    // DECLS
    int t[3];
    char *o;
    int *p;
    // ENDDECLS

    switch (n) {
        case 1:
            o = self + 0x918;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x918, func_0201c2a4(self, 4));
            if (*(u8 *) (self + 0xac8) == 5 || *(u8 *) (self + 0xac8) == 3) {
                func_ov004_02221550((void *) self, 7);
            } else {
                func_ov004_02221550((void *) self, 6);
            }
            if (*(u8 *) (self + 0xac8) == 0) {
                *(int *) (self + 0xae4) = func_ov004_0223cdc0((int *) func_ov004_0223ce84());
                func_020b23d4();
                func_02030864(0);
                func_ov004_0223d33c();
                func_0209e474(self + 0xad0);
            }
            break;
        case 0:
            o = self + 0x918;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x918, func_0201c2a4(self, 4));
            func_ov004_02221550((void *) self, 6);
            break;
        case 8:
            if (*(u8 *) (self + 0xac8) == 6) {
                p = func_02095794(4);
                t[0] = p[0];
                t[1] = p[1];
                t[2] = p[2];
                if (func_02030818(t) != 0) {
                    func_020307f8();
                    break;
                }
            }
            func_ov004_02221550((void *) self, 3);
            break;
    }
}

int func_ov004_02220318(char *s)
{
    int pair[2];
    Vec3 v;
    Vec3 *q;
    int r;
    q = (Vec3 *) func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    if (func_02030818((int *) (&v)) != 0) {
        *(u8 *) (s + 0xac8) = 5;
        func_0203e0a8(s, 0);
        return 1;
    }
    if (func_0203ec98() != 0) {
        return 0;
    }
    if (*(int *) (s + 0xacc) != 0) {
        *(int *) (s + 0xacc) = *(int *) (s + 0xacc) - 1;
        if (*(int *) (s + 0xacc) == 1) {
            *(u8 *) (s + 0xac8) = 3;
            func_0203e0a8(s, 0);
            return 1;
        }
    }
    pair[0] = 0;
    pair[1] = 0;
    func_0209e474((char *) pair);
    r = func_0209e350(s + 0xad0, pair);
    if (*(int *) (s + 0xae8) != 0) {
        *(int *) (s + 0xae8) = *(int *) (s + 0xae8) + 1;
    }
    if (r >= 0x3c || *(int *) (s + 0xae8) > 0x258) {
        *(u8 *) (s + 0xac8) = 3;
        func_0203e0a8(s, 0);
        return 1;
    }
    return 0;
}

int func_ov004_02220210(void *self)
{
    // DECLS
    int start;
    int i;
    void *e;
    int n;
    // ENDDECLS

    if (chk((u16 *) ((char *) self + 0x898), 0xfff1) == 0) {
        return 1;
    }
    n = *(int *) ((char *) self + 0xae4);
    if (n == 0 || *(u8 *) ((char *) self + 0xae0) >= 3) {
        if (*(int *) ((char *) self + 0xacc) == 0) {
            *(int *) ((char *) self + 0xacc) = 0x258;
        }
        return 0;
    }
    start = func_020644cc(n);
    i = start;
    do {
        if (func_ov004_02220084(self, i) != 0) {
            e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
            func_ov004_0220fefc(e, (char *) self + 0x89c);
            func_ov004_02220018(self, e);
            func_ov004_0222005c(self, i);
            *(int *) ((char *) self + 0x8a8) = i;
            goto ok;
        }
        i++;
        if (i >= *(int *) ((char *) self + 0xae4)) {
            i = 0;
        }
    } while (i != start);
    if (*(int *) ((char *) self + 0xacc) == 0) {
        *(int *) ((char *) self + 0xacc) = 0x258;
    }
    return 0;
ok:
    return 1;
}
