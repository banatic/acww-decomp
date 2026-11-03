/* event_calendar_5: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204086c @ 0x0204086c, 0xe bytes, Thumb
 * func_02040868 @ 0x02040868, 0x2 bytes, Thumb
 * func_020407b0 @ 0x020407b0, 0xb8 bytes, Thumb
 * func_02040614 @ 0x02040614, 0x19a bytes, Thumb
 * func_020405e4 @ 0x020405e4, 0x30 bytes, Thumb
 * func_020405a8 @ 0x020405a8, 0x3a bytes, Thumb
 * func_02040548 @ 0x02040548, 0x60 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int lo, hi;
} Date;

typedef struct {
    u8 b[4];
} Rec;

typedef struct {
    unsigned int unk_00;
    int unk_04;
} UnkStruct_020407b0;

typedef struct {
    unsigned int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02040614;

typedef union {
    unsigned int all;
    struct {
        u8 b0;
        u8 b1;
        u8 b2;
        u8 b3;
    } b;
} UnkStruct_02040614_2;

struct UnkStruct_020405e4 {
    unsigned char pad_00[8];
    unsigned int unk_08;
};

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_02040548;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02040548_2;

extern void func_0209e29c(Date *, int);
extern int func_0209de24(int a, int b);
extern int func_0209de88(int a, int b, int c);
extern int func_020984e8(void);
extern void *func_020992e4(int);
extern int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_0207f150(int);
extern int func_0207f294(int);
extern char data_021dc7a8[];
extern void *func_0207cec0(void *tbl, int idx);
extern int func_0207b3dc(void *tbl);
extern unsigned char *func_02080a2c(void *h);

void func_0204086c(unsigned char *r0)
{
    r0[0] = 1;
    r0[1] = 1;
    r0[2] = 0;
    r0[3] = 0;
}

void func_02040868(void *object) {}

int func_020407b0(UnkStruct_020407b0 *p, int arg, Rec rec, int kind)
{
    Date t;
    int result;
    unsigned int w;
    int a;
    int b;
    u8 hi;
    u8 lo2;

    hi = rec.b[3];
    lo2 = rec.b[2];
    result = 0;
    w = p->unk_00;
    a = (w >> 4) & 0xf;
    b = (w >> 11) & 3;
    switch (b) {
        case 0:
            result = (u8) a;
            break;
        case 1:
            if (a == 0) {
                result = hi;
            } else {
                int n;
                t.lo = result;
                t.hi = result;
                if (kind == 0x48) {
                    n = -4;
                } else {
                    n = p->unk_04;
                }
                t.lo = 0;
                t.hi = 0;
                ((u8 *) &t)[5] = (u8) arg;
                ((u8 *) &t)[4] = hi;
                ((u8 *) &t)[3] = lo2;
                if (n < 0) {
                    n = -n;
                }
                func_0209e29c(&t, n);
                result = ((u8 *) &t)[4];
            }
            switch (kind) {
                case 0xb:
                case 0x29:
                case 0x2a:
                case 0x48:
                    if (result == 1 || result == 8) {
                        result = 2;
                    }
                    break;
            }
            break;
        case 2:
            if (a == 1) {
                result = (u8) ((hi & ~1) + 1);
            } else {
                result = (u8) ((hi + 1) & ~1);
            }
            break;
    }
    return result;
}

u8 func_02040614(UnkStruct_02040614 *p, int a1, UnkStruct_02040614_2 q, int a3, int a5)
{
    int t;
    int acc;
    int i;
    unsigned int v;
    unsigned int s;
    int r6;
    int x;
    int b3;
    int y;
    int r2;
    int j;
    int w;

    v = p->unk_00;
    t = v >> 8;
    t = t & 7;
    s = (v >> 1) & 7;
    r6 = func_0209de24(a1, a3);
    b3 = q.b.b3;
    x = func_0209de24(a1, b3);
    switch (t) {
        case 0:
            return (u8) p->unk_04;
        case 6: {
            y = func_0209de88((u8) a1, a3, (u8) r6);
            if (y < q.b.b0) {
                return (u8) ((r6 - 7) + (q.b.b0 - y));
            } else {
                return (u8) (r6 - (y - q.b.b0));
            }
        }
        case 7: {
            if (s < q.b.b0) {
                y = (u8) ((*(u8 *) &q.b.b2) + ((s - q.b.b0) + 7));
            } else {
                y = (u8) ((*(u8 *) &q.b.b2) + (s - q.b.b0));
            }
            if (b3 != a3 && y > x) {
                y = y - x;
            }
            return (u8) y;
        }
    }
    w = q.b.b0 - (((*(u8 *) &q.b.b2) - 1) % 7);
    if (w < 0) {
        w = w + 7;
    }
    if (a3 != b3) {
        acc = 0;
        i = a3;
        if (a3 == 1 && b3 == 0xc) {
            i = 0xd;
        }
        if ((unsigned int) i < (unsigned int) b3) {
            b3 = q.b.b3;
            for (; i < b3; i++) {
                acc = acc + func_0209de24(a1, (u8) i);
            }
            acc = acc % 7;
            w = ((w - acc) + 7) % 7;
        } else {
            for (j = b3; j < i; j++) {
                acc = acc + func_0209de24(a1, (u8) j);
            }
            w = (w + acc) % 7;
        }
    }
    if ((unsigned int) w <= s) {
        r2 = (s - w) + 1;
    } else {
        r2 = (s - w) + 8;
    }
    switch (a5) {
        case 9:
        case 0x14:
        case 0x25:
        case 0x26:
        case 0x46:
            if (a3 == 2 || a3 == 4 || a3 == 0xa) {
                t = 4;
            }
            break;
    }
    return (u8) (r2 + 7 * (t - 1));
}

void func_020405e4(struct UnkStruct_020405e4 *a, unsigned char *b)
{
    void *ptr;

    if (!func_020984e8()) {
        return;
    }
    ptr = func_020992e4(func_020984e8());
    if (!ptr) {
        return;
    }

    b[3] = ((unsigned char *) ptr)[1];
    b[2] = ((unsigned char *) ptr)[0];
    b[1] = (unsigned char) a->unk_08;
}

int func_020405a8(int r0, int r1)
{
    int r4 = 0;
    int r5 = r0;
    int r6 = r1;

    if (func_02003704((void *) func_0208150c(r0)) != 0) {
        if (func_0207f150(r5) == 3) {
            int r0 = func_0207f294(r5);
            int r1 = ~r4;
            if (r0 != r1 && r0 != r6) {
                r4 = 1;
            }
        }
    }
    return r4;
}

void func_02040548(UnkStruct_02040548_2 *p, UnkStruct_02040548 *out, int idx)
{
    char *base;
    void *h;
    unsigned char *e;

    base = (char *) data_021dc7a8;
    *(int *) out = 0;
    if (idx < 0 || idx > 7) {
        idx -= 0x4b;
    }
    h = func_0207cec0(base + 0x9284, idx);
    if (func_020405a8((int) h, func_0207b3dc(base + 0x9284))) {
        e = func_02080a2c(h);
        if (e) {
            out->unk_03 = e[0];
            out->unk_02 = e[1];
            out->unk_01 = (unsigned char) p->unk_08;
        }
    }
}
