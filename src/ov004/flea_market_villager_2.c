/* flea_market_villager_2: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221f474 @ 0x0221f474, 0x2a8 bytes, Thumb
 * func_ov004_0221f448 @ 0x0221f448, 0x2c bytes, Thumb
 * func_ov004_0221f43c @ 0x0221f43c, 0xc bytes, Thumb
 * func_ov004_0221f438 @ 0x0221f438, 0x2 bytes, Thumb
 * func_ov004_0221f334 @ 0x0221f334, 0x104 bytes, Thumb
 * func_ov004_0221f308 @ 0x0221f308, 0x2c bytes, Thumb
 * func_ov004_0221f2e8 @ 0x0221f2e8, 0x20 bytes, Thumb
 * func_ov004_0221f254 @ 0x0221f254, 0x94 bytes, Thumb
 */

#include "types.h"

struct OUT {
    void *unk_00;
    u8 unk_04;
};

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0xa54 - 0x834];
    u8 unk_A54;
} UnkStruct_0221f334;

struct UnkStruct_0221f254;

struct UnkStruct_0221f254_2 {
    void (*unk_00)(struct UnkStruct_0221f254 *);
    void (*unk_04)(struct UnkStruct_0221f254 *);
    void (*unk_08)(struct UnkStruct_0221f254 *);
};

struct UnkStruct_0221f254 {
    struct UnkStruct_0221f254_2 *vt;
};

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void *func_020984e8(void);
extern void *func_02099870(void *p);
extern int func_020804b8(void *a, void *b);
extern void func_02081e14(int r, int a, int b, int c);
extern void *func_0208150c(void *p);
extern int func_0200366c(void *a, void *b, int n, void *c);
extern int func_020644cc(int n);
extern void func_02015de4(void *self, void *p, int a, int b);
extern int func_0204c878(void *p);
extern int func_020807a8(void *a, void *b);
extern int func_02081d20(int h);
extern int _fflt(int x);
extern int _fadd(int a, int b);
extern int _fsub(int a, int b);
extern int _ffix(int f);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern int _s32_div_f(int a, int b);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern int func_0207f708(void *a, u16 *p);
extern int func_02099fe8(void);
extern int func_0201b43c(void *a, int b);
extern char data_ov004_02257d30[];
extern char data_ov004_02253c98[];
extern char data_ov004_02253ca4[];
extern char data_ov004_02253cb0[];
extern char data_ov004_02253cbc[];
extern u8 data_020e54a8;
extern int func_020160b4(void *arg0);
extern int func_020ab504(void *);
extern void func_0208b520(void);
extern void func_ov004_0221f71c(void *self);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov004_02257d08;
extern char data_ov004_02253c74;
extern char data_ov004_02253c80;
extern char data_ov004_02253c88;
extern char data_ov004_02253c90;
extern int func_02014868(void *);
extern int func_ov004_0221ef70(void *);
extern int func_0201c2a4(void *s, int a);
extern void func_02016108(void *p, int a);
extern void func_ov004_0221fdf4(void *s, int a);

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

void func_ov004_0221f474(void *self, struct OUT *out)
{
    // DECLS
    int h;
    void *g;
    u16 *pi;
    int c;
    int n;
    int t;
    int w;
    int r;
    int k;
    // ENDDECLS
    u16 tmp;

    h = func_020804b8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), func_02099870(func_020984e8()));
    if (h != 0) {
        func_02081e14(h, 0, 0, 0);
    }
    g = *(void **) ((char *) self + 0x1a4);
    if (*(u8 *) ((char *) g + 0xa54) == 3) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257d30, 0x28, data_ov004_02253c98);
        out->unk_00 = data_ov004_02257d30;
        out->unk_04 = (u8) (func_020644cc(3) + 3);
    } else {
        pi = (u16 *) ((char *) g + 0x898);
        if (chk(pi, 0xfff1) == 0) {
            c = 0;
            func_02015de4(self, (char *) *(void **) ((char *) self + 0x1a4) + 0x898, c, 7);
            *(int *) ((char *) self + 0x1a8) = func_0204c878((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
            if (*(int *) ((char *) self + 0x1a8) < 0xa) {
                *(int *) ((char *) self + 0x1a8) = 0xa;
            }
            if (func_020984e8() != 0) {
                h = func_020807a8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830),
                                  func_02099870(func_020984e8()));
            }
            if (h != 0) {
                c = func_02081d20(h);
            }
            n = 0xff - c;
            if (n > 0) {
                t = _fadd(0x3f000000, _fflt(n << 12));
            } else {
                t = _fsub(_fflt(n << 12), 0x3f000000);
            }
            *(int *) ((char *) self + 0x1a8) = FX_Div(FX_MulFunc(*(int *) ((char *) self + 0x1a8), _ffix(t)), 0x200000);
            w = *(int *) ((char *) self + 0x1a8);
            r = _s32_div_f(w, 0xa) * 0xa;
            if (w - r >= 5) {
                r += 0xa;
            }
            *(int *) ((char *) self + 0x1a8) = r;
            func_02015fb0(self, *(int *) ((char *) self + 0x1a8), 3, 0xa, 0, 0);
            k = 0;
            if (*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830) != 0) {
                tmp = 0xfff1;
                k = 0xa - func_0207f708(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), &tmp);
            }
            if (*(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x89c) == -1 || func_02099fe8() == -1 || k <= 3 ||
                func_0201b43c(*(void **) ((char *) self + 0x1a4), *(int *) ((char *) self + 0x1a8)) == 0) {
                func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                              data_ov004_02257d30, 0x28, data_ov004_02253ca4);
            } else {
                func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                              data_ov004_02257d30, 0x28, data_ov004_02253cb0);
            }
            out->unk_00 = data_ov004_02257d30;
            out->unk_04 = (u8) func_020644cc(3);
        } else {
            switch (*(u8 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0xa54)) {
                case 0:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253c98);
                    out->unk_04 = (u8) func_020644cc(3);
                    break;
                case 1:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253cbc);
                    out->unk_04 = (u8) func_020644cc(3);
                    break;
                case 2:
                    func_0200366c(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830)),
                                  data_ov004_02257d30, 0x28, data_ov004_02253c98);
                    out->unk_04 = (u8) (func_020644cc(3) + 6);
                    break;
            }
            out->unk_00 = data_ov004_02257d30;
        }
    }
}

int func_ov004_0221f448(u8 *self)
{
    unsigned int t;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t == 0 || self[0xa56] == 0) {
        return 1;
    }
    return 0;
}

void *func_ov004_0221f43c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa56) = 0x1;
    return self;
}

void func_ov004_0221f438(void) {}

void func_ov004_0221f334(char *self)
{
    u8 buf;
    int have;
    void *tbl;
    u8 state;
    u8 code;
    char *tblEarly;
    have = func_020ab504((void *) func_020160b4((void *) self));
    code = 0xff;
    if ((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 == 1) {
        state = *((u8 *) (self + 0x1e));
        tblEarly = &data_ov004_02257d08;
        if (state == 0) {
            goto mode1_ok;
        }
        if (state == 1) {
            goto mode1_ok;
        }
        if (state == 2) {
            goto mode1_ok;
        }
        goto tail;
    mode1_ok:
        tbl = tblEarly;

        code = (u8) func_020644cc(3);
        if (have == 0) {
            func_0200366c((void *) ((int) func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830)), tbl, 0x28, &data_ov004_02253c74);
            func_0208b520();
            (*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 = 2;
        } else {
            func_0200366c((void *) ((int) func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830)), tbl, 0x28, &data_ov004_02253c80);
        }
    } else if ((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 == 2) {
        state = *((u8 *) (self + 0x1e));
        if (state == 0) {
            goto mode2_ok;
        }
        if (state == 1) {
            goto mode2_ok;
        }
        if (state == 2) {
            goto mode2_ok;
        }
        goto tail;
    mode2_ok:
        if (have == 0) {
            func_0200366c((void *) ((int) func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830)), &data_ov004_02257d08, 0x28, &data_ov004_02253c88);
            func_ov004_0221f71c(self);
        } else {
            func_0200366c((void *) ((int) func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830)), &data_ov004_02257d08, 0x28, &data_ov004_02253c90);
        }

        tbl = &data_ov004_02257d08;
        code = (u8) func_020644cc(3);
    }
tail:
    if (code != 0xff) {
        buf = code;
        func_0206844c(*((int *) (self + 0x40)), &buf, tbl);
    }
}

int func_ov004_0221f308(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_ov004_0221ef70(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov004_0221f2e8(int arg0)
{
    int result;
    int ret;

    result = func_02014868((void *) (arg0 + 0x618));
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void func_ov004_0221f254(char *s, int sel)
{
    struct UnkStruct_0221f254 *o;
    u8 v;
    switch (sel) {
        case 1:
            o = (struct UnkStruct_0221f254 *) (s + 0x8a8);
            o->vt->unk_08(o);
            func_02016108(s + 0x8a8, func_0201c2a4(s, 4));
            v = *(u8 *) (s + 0xa54);
            if (v == 0) {
                func_ov004_0221fdf4(s, 1);
            } else if (v == 3) {
                func_ov004_0221fdf4(s, 3);
            } else {
                func_ov004_0221fdf4(s, 7);
            }
            break;
        case 0:
            o = (struct UnkStruct_0221f254 *) (s + 0x8a8);
            o->vt->unk_08(o);
            func_02016108(s + 0x8a8, func_0201c2a4(s, 4));
            func_ov004_0221fdf4(s, 1);
            break;
        case 8:
            func_ov004_0221fdf4(s, 4);
            break;
    }
}
