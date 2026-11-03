/* giraffe_talk: 7 functions, module ov070
 * mwccarm 1.2/base -O4,s
 * func_ov070_02279550 @ 0x02279550, 0x104 bytes, Thumb
 * func_ov070_02279538 @ 0x02279538, 0x18 bytes, Thumb
 * func_ov070_0227944c @ 0x0227944c, 0xec bytes, Thumb
 * func_ov070_02279238 @ 0x02279238, 0x214 bytes, Thumb
 * func_ov070_02279224 @ 0x02279224, 0x14 bytes, Thumb
 * func_ov070_022790cc @ 0x022790cc, 0x158 bytes, Thumb
 * func_ov070_02278e30 @ 0x02278e30, 0x29c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xb0];
    int state;
    unsigned char *ptr;
} Object;

typedef struct {
    unsigned int word;
    unsigned char byte;
} Output;

typedef struct {
    unsigned char b[8];
} ByteEntry;

typedef struct {
    unsigned int w[2];
} WordEntry;

typedef struct UnkStruct_02279238 {
    char pad_00[0xc4];
    u16 unk_C4;
    u16 unk_C6;
    u16 unk_C8;
} UnkStruct_02279238;

typedef struct UnkStruct_022790cc_3 {
    char pad_00[0xc4];
    u16 unk_C4;
    u16 unk_C6;
    u16 unk_C8;
} UnkStruct_022790cc_3;

typedef struct UnkStruct_022790cc_2 {
    u16 h;
    u8 n;
} UnkStruct_022790cc_2;

typedef struct UnkStruct_022790cc {
    u16 a;
    u16 b;
    u16 c;
    UnkStruct_022790cc_2 q;
} UnkStruct_022790cc;

typedef struct UnkStruct_02278e30_2 {
    char pad_00[0xc0];
    int unk_C0;
    u16 h[3];
} UnkStruct_02278e30_2;

typedef struct UnkStruct_02278e30 {
    u16 ids[3];
    u8 flags[3];
    u8 thresh;
    u8 pad_0A[2];
    int unk_0C;
} UnkStruct_02278e30;

extern int func_020984e8(void);
extern int func_02099670(int);
extern int func_0202ea80(int, int);
extern int func_02088b64(int);
extern int func_0208602c(void);
extern int func_02086108(int, int);
extern ByteEntry data_ov070_02279bac[];
extern WordEntry data_ov070_02279ba8[];
extern void func_02088b50(unsigned char *object, unsigned char value);
extern int func_020644cc(int);
extern u16 *func_020996f8(int);
extern u16 *func_020996e0(int);
extern u16 *func_02099710(int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_0204c878(u16 *);
extern unsigned char func_02099f1c(void *flags, int (*callback)(void *));
extern UnkStruct_02278e30 data_ov070_02279be0[];
extern void func_020996d4(int, u16 *);
extern void func_020996ec(int, u16 *);
extern int func_02095b40(u16 *);
extern void func_02095b4c(u16 *);
extern int func_02095b58(u16 *);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(u16 *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern void func_02099704(int, u16 *);
extern void func_02015de4(UnkStruct_02278e30_2 *, u16 *, int, int);
extern int func_0209a000(u16 *, int);

void func_ov070_02279550(Object *p, Output *out)
{
    int r6;
    int a;
    r6 = func_02099670(func_020984e8());
    if (func_0202ea80(7, 1) == 0) {
        p->state = 0;
    } else {
        if (func_0202ea80(8, 0) != 0) {
            if (func_0202ea80(9, 0) != 0) {
                p->state = 6;
            } else {
                if ((unsigned int) p->ptr[0x738] < 3u) {
                    p->state = 2;
                } else {
                    if ((unsigned int) func_02088b64(r6) >= 0x3du) {
                        p->state = 3;
                    } else {
                        p->state = 4;
                    }
                }
            }
        } else {
            p->state = 1;
        }
    }
    a = func_0208602c();
    if (func_02086108(a, 10) != 0) {
        if ((unsigned int) (p->state - 2) <= 2u) {
            p->state = 5;
        }
    }
    if (p->state < 0 || p->state >= 7) {
        return;
    }

    out->byte = data_ov070_02279bac[p->state].b[0];
    if (p->state == 2) {
        out->byte = p->ptr[0x738] + 0x4c;
        p->ptr[0x738]++;
    }
    out->word = data_ov070_02279ba8[p->state].w[0];
}

void func_ov070_02279538(void *self, unsigned char value)
{
    unsigned char *object = (unsigned char *) func_02099670(func_020984e8());
    func_02088b50(object, value);
}

unsigned char func_ov070_0227944c(int unused, int r1, int r2)
{
    unsigned char result = 0;

    switch (r2) {
        case 0:
            if (r1 == 0) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 200) {
                result = (unsigned char) (func_020644cc(3) + 3);
            } else if (r1 < 1000) {
                result = (unsigned char) (func_020644cc(3) + 5);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        case 1:
            if (r1 == 0) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 160) {
                result = (unsigned char) (func_020644cc(3) + 3);
            } else if (r1 < 600) {
                result = (unsigned char) (func_020644cc(3) + 5);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        case 2:
            if (r1 < 350) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 400) {
                result = (unsigned char) (func_020644cc(3) + 4);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        default:
            break;
    }

    return result;
}

void func_ov070_02279238(UnkStruct_02279238 *self)
{
    u16 tmp[3];
    int g;
    int h;
    int t;
    int ok;
    int flag;
    int c;

    g = func_020984e8();
    h = func_02099670(g);

    self->unk_C4 = *func_020996f8(g);
    if (func_0204bcdc(&self->unk_C4) != 0) {
        tmp[0] = 0xfff1;
        t = func_0204bc64(&self->unk_C4);
        if (t == func_0204bc64(&tmp[0])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C4 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        flag = 0;
        if (self->unk_C4 >= 0x1429 && self->unk_C4 <= 0x1430) {
            flag = 1;
        }
        if (flag == 0) {
            func_02088b50((unsigned char *) h, (u8) ((u8) ((int) func_ov070_0227944c((int) self, func_0204c878(&self->unk_C4), 0) * 2)));
        } else {
            func_02088b50((unsigned char *) h, (u8) ((u8) ((func_020644cc(0xa) + 1) * 2)));
        }
    } else {
        c = func_020644cc(3);
        func_02088b50((unsigned char *) h, (u8) ((u8) ((u8) (c + 1) * 2)));
    }

    self->unk_C6 = *func_020996e0(g);
    if (func_0204bcdc(&self->unk_C6) != 0) {
        tmp[1] = 0xfff1;
        t = func_0204bc64(&self->unk_C6);
        if (t == func_0204bc64(&tmp[1])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C6 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        func_02088b50((unsigned char *) h, (u8) ((u8) ((int) func_ov070_0227944c((int) self, func_0204c878(&self->unk_C6), 1) * 2)));
    } else {
        c = func_020644cc(3);
        func_02088b50((unsigned char *) h, (u8) ((u8) ((u8) (c + 1) * 2)));
    }

    self->unk_C8 = *func_02099710(g);
    if (func_0204bcdc(&self->unk_C8) != 0) {
        tmp[2] = 0xfff1;
        t = func_0204bc64(&self->unk_C8);
        if (t == func_0204bc64(&tmp[2])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C8 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        flag = 0;
        if (self->unk_C4 >= 0x12a8 && self->unk_C4 <= 0x12af) {
            flag = 1;
        }
        if (flag == 0) {
            func_02088b50((unsigned char *) h, (u8) ((u8) ((int) func_ov070_0227944c((int) self, func_0204c878(&self->unk_C8), 2) * 2)));
        } else {
            func_02088b50((unsigned char *) h, (u8) ((u8) ((func_020644cc(0xa) + 1) * 2)));
        }
    }
}

int func_ov070_02279224(void *arg0)
{
    unsigned short val;
    val = *(unsigned short *) arg0;
    if (val == 0xfff1) {
        return 1;
    }
    return 0;
}

int func_ov070_022790cc(UnkStruct_022790cc_3 *self)
{
    UnkStruct_022790cc s;
    u8 count;
    int r;
    unsigned int ok;
    unsigned int in;

    func_02099f1c(&s.q, func_ov070_02279224);
    count = 0;
    func_ov070_02279238((UnkStruct_02279238 *) self);

    if (func_0204bcdc(&self->unk_C4) != 0) {
        s.a = 0xfff1;
        r = func_0204bc64(&self->unk_C4);
        ok = (r == func_0204bc64(&s.a)) ? 1 : 0;
    } else {
        ok = (self->unk_C4 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        in = 0;
        if (self->unk_C4 >= 0x1429 && self->unk_C4 <= 0x1430) {
            in = 1;
        }
        if (in == 0) {
            count++;
        }
    }

    if (func_0204bcdc(&self->unk_C6) != 0) {
        s.b = 0xfff1;
        r = func_0204bc64(&self->unk_C6);
        ok = (r == func_0204bc64(&s.b)) ? 1 : 0;
    } else {
        ok = (self->unk_C6 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        count++;
    }

    if (func_0204bcdc(&self->unk_C8) != 0) {
        s.c = 0xfff1;
        r = func_0204bc64(&self->unk_C8);
        ok = (r == func_0204bc64(&s.c)) ? 1 : 0;
    } else {
        ok = (self->unk_C8 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        in = 0;
        if (self->unk_C8 >= 0x12a8 && self->unk_C8 <= 0x12af) {
            in = 1;
        }
        if (in == 0) {
            count++;
        }
    }

    return (s.q.n >= count) ? 1 : 0;
}

int func_ov070_02278e30(UnkStruct_02278e30_2 *self)
{
    int ret;
    int t;
    u16 w[20];
    int o[2][2];
    u8 n;
    u8 k;
    int i;
    int j;
    int g;
    int ok;
    int flag;
    u16 id;
    int x;
    u16 *p;

    n = (u8) func_020644cc(4);
    k = 6;
    w[0] = 0xfff1;
    func_ov070_02279238((UnkStruct_02279238 *) self);
    for (i = 0; i < 7; i++) {
        if (data_ov070_02279be0[i].unk_0C >= self->unk_C0) {
            k = (u8) i;
            break;
        }
    }

    g = func_020984e8();
    if (n < 3) {
        w[1] = 0xfff1;
        func_020996d4(g, &w[1]);
        if (data_ov070_02279be0[k].flags[n] == 0) {
            id = data_ov070_02279be0[k].ids[n];
            w[2] = id;
            func_02095b40(&w[2]);
            w[3] = id;
            func_020996ec(g, &w[3]);
            w[4] = 0xfff1;
            func_02095b4c(&w[4]);
            w[5] = 0xfff1;
            func_020996d4(g, &w[5]);
        } else {
            id = data_ov070_02279be0[k].ids[n];
            w[6] = id;
            func_02095b4c(&w[6]);
            w[7] = id;
            func_020996d4(g, &w[7]);
            w[8] = 0xfff1;
            func_02095b40(&w[8]);
            w[9] = 0xfff1;
            func_020996ec(g, &w[9]);
        }
    } else {
        w[10] = 0xfff1;
        func_020996d4(g, &w[10]);
        w[11] = 0xfff1;
        func_020996ec(g, &w[11]);
        w[12] = 0xfff1;
        func_02095b4c(&w[12]);
        w[13] = 0xfff1;
        func_02095b40(&w[13]);
    }

    x = func_020644cc(0x65);
    if (data_ov070_02279be0[k].thresh >= (u8) x) {
        func_02063ccc(o[0], 2, 0x22);
        func_020638d4(&w[14], o[0], 0, 0, 1, 1, 0);
        w[0] = w[14];
        func_02063cc8(o[0]);
        ret = 1;
    } else {
        func_02063ccc(o[1], 2, 0);
        func_020638d4(&w[15], o[1], 0, 0, 1, 1, 0);
        w[0] = w[15];
        func_02063cc8(o[1]);
        ret = 0;
    }

    if (func_0204bcdc(&w[0]) != 0) {
        w[17] = 0xfff1;
        t = func_0204bc64(&w[0]);
        if (t == func_0204bc64(&w[17])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (w[0] == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        w[16] = w[0];
        func_02095b58(&w[16]);
        func_02099704(g, &w[0]);
        func_02015de4(self, &w[0], 0, 7);
    }

    for (j = 0; j < 3; j++) {
        p = &self->h[j];
        if (func_0204bcdc(p) != 0) {
            w[18] = 0xfff1;
            t = func_0204bc64(p);
            ok = (t == func_0204bc64(&w[18])) ? 1 : 0;
        } else {
            ok = (self->h[j] == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            flag = 0;
            if (self->h[j] >= 0x1429 && self->h[j] <= 0x1430) {
                flag = 1;
            }
            if (flag == 0) {
                if (self->h[j] < 0x12a8 || self->h[j] > 0x12af) {
                    func_0209a000(p, 0);
                }
            }
        }
    }
    return ret;
}
