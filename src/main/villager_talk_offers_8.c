/* villager_talk_offers_8: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202a4d8 @ 0x0202a4d8, 0x110 bytes, Thumb
 * func_0202a2ec @ 0x0202a2ec, 0x1ec bytes, Thumb
 * func_0202a1cc @ 0x0202a1cc, 0x120 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0202a4d8 {
    u16 unk_00;
    u8 nm[12];
    u8 unk_0E;
    u8 unk_0F;
} UnkStruct_0202a4d8;

typedef struct UnkStruct_0202a4d8_2 {
    s32 w[8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
} UnkStruct_0202a4d8_2;

typedef struct UnkStruct_0202a4d8_3 {
    s32 a, b;
} UnkStruct_0202a4d8_3;

typedef struct UnkStruct_0202a4d8_4 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x11c];
    void *unk_160;
} UnkStruct_0202a4d8_4;

struct Pair {
    int a;
    int b;
};

struct ST {
    int pad_00[8];
    u8 a;
    signed char b;
    u8 pad_22[2];
};

struct UnkStruct_0202a2ec {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x11c];
    int unk_160;
};

typedef struct UnkStruct_0202a1cc {
    u8 pad_00[0x20];
    u8 a;
    u8 b;
    u8 pad_22[6];
} UnkStruct_0202a1cc;

typedef struct UnkStruct_0202a1cc_2 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x160 - 0x44];
    void *unk_160;
} UnkStruct_0202a1cc_2;

typedef struct UnkStruct_0202a1cc_3 {
    int a;
    int b;
} UnkStruct_0202a1cc_3;

extern UnkStruct_0202a4d8_3 data_020d8f48;
extern u8 data_020c8928[];
extern u8 data_020c8924[];
extern u8 data_021c2ee4[];
extern u8 data_021c1e14[];
extern u8 data_021c1d6c[];
extern void *func_0209ad9c(int, int);
extern void *func_0209b4d4(void *);
extern int func_0209bd44(void *);
extern int func_0209bba8(void *);
extern UnkStruct_0202a4d8 *func_0209b4cc(void *, int);
extern UnkStruct_0202a4d8 *func_0208150c(UnkStruct_0202a4d8 *);
extern int memcmp(const void *, const void *, int);
extern int func_0209b414(void *);
extern int func_0209bc40(void *);
extern void func_0201cfb4(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *);
extern void func_0202d9d0(UnkStruct_0202a4d8_4 *, void *);
extern void func_0201cf90(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *, int, int, int, void *);
extern void func_0201cf74(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *, int, void *, void *);
extern void func_0201cec8(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *);
extern void func_0202da74(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_3);
extern void func_02068388(void *, int);
extern int data_020c8920;
extern int data_020c8930;
extern struct Pair data_020d8f20;
extern int func_0209ad2c(int a, int b, int c);
extern int func_020984e8(void);
extern void func_0209e474(void *p);
extern void func_02015e10(struct UnkStruct_0202a2ec *a, int b, int c);
extern void *func_0202d9c4(struct UnkStruct_0202a2ec *a);
extern int func_0209bb70(int a);
extern void func_02015de4(struct UnkStruct_0202a2ec *a, int b, int c, int d);
extern void *func_0209bc20(void *record);
extern int func_0209e3ac(int a, void *b, int c);
extern int func_02099734(int a);
extern int func_0202d794(int a, int b);
extern unsigned char data_021c2ac4[];
extern unsigned char data_021c2b0c[];
extern void *func_0209bbf8(int a);
extern u8 data_021c2be4[];
extern u8 data_021c2bcc[];
extern UnkStruct_0202a1cc_3 data_020d9490;

int func_0202a4d8(UnkStruct_0202a4d8_4 *p, UnkStruct_0202a4d8 *b, int c)
{
    void *h;
    void *t;
    int ret;
    UnkStruct_0202a4d8 *x;
    UnkStruct_0202a4d8_2 s;

    h = func_0209ad9c(c, 0);
    t = func_0209b4d4((void *) h);
    ret = 0;
    if (func_0209bd44(t)) {
        if (func_0209bba8(t) == 1) {
            x = func_0209b4cc(h, 1);
            b = func_0208150c(b);
            if (b->unk_00 == x->unk_00 && memcmp(b->nm, x->nm, 12) == 0 && b->unk_0F == x->unk_0F && func_0209b414(h) == 0) {
                switch (func_0209bc40(t)) {
                    case 0xe:
                    case 0x10:
                    case 0x11:
                        func_0201cfb4(p, &s);
                        p->unk_160 = h;
                        func_0202d9d0(p, t);
                        func_0201cf90(p, &s, 0, 0x1d, 0x1d, data_021c2ee4);
                        func_0201cf74(p, &s, 1, data_020c8928, data_021c1e14);
                        func_0201cf74(p, &s, 2, data_020c8924, data_021c1d6c);
                        s.unk_20 = 3;
                        s.unk_21 = s.unk_20 - 1;
                        func_0201cec8(p, &s);
                        func_0202da74(p, data_020d8f48);
                        func_02068388(p->unk_40, 1);
                        ret = 1;
                        break;
                }
            }
        }
    }
    return ret;
}

int func_0202a2ec(struct UnkStruct_0202a2ec *self, int param1, int param2)
{
    int a;
    int b;
    int mode;
    int ret;
    u8 idx;
    int p10;
    int t;
    u8 n;
    int buf[2];
    struct ST st;

    a = func_0209ad2c(param2, (int) func_0208150c((UnkStruct_0202a4d8 *) param1), 1);
    if (a != 0) {
        b = (int) func_0209b4d4((void *) a);
    } else {
        b = 0;
    }
    if (b != 0) {
        mode = func_0209bba8((void *) b);
    } else {
        mode = 4;
    }
    ret = 0;
    switch (mode) {
        case 0:
        case 2:
            if (func_0209b414((void *) a) != 0) {
                break;
            }
            idx = 0;
            buf[0] = idx;
            buf[1] = idx;
            p10 = func_020984e8();
            func_0209e474(buf);
            func_0201cfb4((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st));
            self->unk_160 = a;
            func_0202d9d0((UnkStruct_0202a4d8_4 *) self, (void *) b);
            func_02015e10(self, (int) func_0209b4cc((void *) self->unk_160, idx), idx);
            func_02015e10(self, (int) func_0209b4cc((void *) self->unk_160, 1), 1);
            func_02015de4(self, func_0209bb70((int) func_0202d9c4(self)), idx, 7);
            if (func_0209e3ac((int) func_0209bc20((void *) func_0202d9c4(self)), buf, 0x3f) == -1) {
                switch (mode) {
                    case 2:
                        func_0201cf90((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), idx, 0x2b, 0x2b,
                                      (void *) data_021c2ac4);
                        idx++;
                        ret = 1;
                        break;
                    case 0:
                        func_0201cf90((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), idx, 0x27, 0x27,
                                      (void *) data_021c2ac4);
                        idx++;
                        ret = 1;
                        break;
                }
            } else {
                switch (mode) {
                    case 2:
                        func_0201cf74((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), idx, &data_020c8920,
                                      (void *) data_021c2b0c);
                        idx++;
                        ret = 1;
                        break;
                    case 0:
                        t = func_02099734(p10);
                        if (func_0202d794(t, func_0209bb70((int) func_0209b4d4((void *) self->unk_160))) != -1) {
                            func_0201cf74((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), idx, &data_020c8930,
                                          (void *) data_021c2b0c);
                            idx++;
                            ret = 1;
                        }
                        break;
                }
            }
            if (ret != 0) {
                func_0201cf74((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), idx, ((int *) data_020c8928),
                              (void *) ((unsigned char *) data_021c1e14));
                func_0201cf74((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st), (u8) (idx + 1),
                              ((int *) data_020c8924), (void *) ((unsigned char *) data_021c1d6c));
                n = idx + 2;
                st.a = n;
                st.b = n - 1;
                func_0201cec8((UnkStruct_0202a4d8_4 *) self, (UnkStruct_0202a4d8_2 *) (&st));
                func_0202da74((UnkStruct_0202a4d8_4 *) self, *(UnkStruct_0202a4d8_3 *) &data_020d8f20);
                func_02068388((void *) self->unk_40, 1);
            }
            break;
    }
    return ret;
}

int func_0202a1cc(UnkStruct_0202a1cc_2 *p, int a2, int a3, int a4)
{
    int ok;
    UnkStruct_0202a1cc loc;

    ok = 0;
    p->unk_160 = func_0209ad9c(a3, (int) (func_0209bbf8(a4)));
    if (p->unk_160 != 0) {
        func_0201cfb4((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc));
        func_0202d9d0((UnkStruct_0202a4d8_4 *) p, func_0209b4d4(p->unk_160));
        func_02015e10((struct UnkStruct_0202a2ec *) p, (int) ((void *) func_0209b4cc(p->unk_160, 0)), 0);
        func_02015e10((struct UnkStruct_0202a2ec *) p, (int) ((void *) func_0209b4cc(p->unk_160, 1)), 1);
        func_02015de4((struct UnkStruct_0202a2ec *) p,
                      (int) ((void *) func_0209bb70((int) (unsigned int) func_0202d9c4((struct UnkStruct_0202a2ec *) p))), 0,
                      7);
        if (func_0209b414(p->unk_160)) {
            func_0201cf90((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc), 0, 0x23, 0x23, data_021c2be4);
        } else {
            func_0201cf90((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc), 0, 0x1e, 0x1e, data_021c2bcc);
        }
        func_0201cf74((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc), 1, data_020c8928, data_021c1e14);
        func_0201cf74((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc), 2, data_020c8924, data_021c1d6c);
        loc.a = 3;
        loc.b = (u8) (loc.a - 1);
        func_0201cec8((UnkStruct_0202a4d8_4 *) p, (UnkStruct_0202a4d8_2 *) (&loc));
        func_0202da74((UnkStruct_0202a4d8_4 *) p, *(UnkStruct_0202a4d8_3 *) &data_020d9490);
        func_02068388(p->unk_40, 1);
        ok = 1;
    }
    return ok;
}
