/* event_calendar_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02040164 @ 0x02040164, 0x1c bytes, Thumb
 * func_02040034 @ 0x02040034, 0x130 bytes, Thumb
 * func_02040010 @ 0x02040010, 0x24 bytes, Thumb
 * func_0203ff98 @ 0x0203ff98, 0x78 bytes, Thumb
 */

#include "types.h"

typedef union UnkStruct_02040034 {
    u32 v;
    u8 a;
} UnkStruct_02040034;

typedef struct Rec {
    u16 id;
    u16 kind;
    u32 lo;
    u32 hi;
} Rec;

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_02040010;

typedef struct {
    unsigned short h;
    char pad_02[3];
    unsigned char unk_05;
    unsigned char unk_06;
    char pad_07[2];
    unsigned char unk_09;
    unsigned char unk_0A;
} UnkStruct_02040010_2;

typedef struct {
    u32 v;
} UnkStruct_0203ff98;

typedef struct {
    u16 a;
    u16 b;
    unsigned char unk_04[12];
    unsigned char unk_10[12];
} Src;

typedef struct {
    u16 a;
    u16 b;
    UnkStruct_0203ff98 p1;
    UnkStruct_0203ff98 p2;
} Dst;

extern int func_02040a48(int id);
extern int func_020408e8(int id, int k);
extern int func_020883cc(void);
extern int func_02088394(void);
extern int func_020881c4(void *p);
extern int func_02040b20(UnkStruct_02040034 x);
extern int func_02040a90(UnkStruct_02040034 x);
extern int data_021f3278;
extern UnkStruct_0203ff98 func_0204019c(void *s, void *c, UnkStruct_0203ff98 p, int n);
extern UnkStruct_0203ff98 func_02040180(void *s, void *c, UnkStruct_0203ff98 p, int n);

void func_02040164(short *r0, int r1)
{
    int r4 = 0;
    short r3 = 0x63;
    short r2 = 5;
    while (r4 < r1) {
        *r0 = r3;
        *(r0 + 1) = r2;
        r0 += 6;
        r4++;
    }
}

int func_02040034(Rec *hdr, UnkStruct_02040034 x, Rec *a, Rec *b, int n, int f1, int f2)
{
    // DECLS
    u32 aLo;
    u32 aHi;
    u32 bLo;
    Rec *q;
    int i;
    u32 bHi;
    int kind;
    // ENDDECLS

    kind = hdr->kind;
    if (kind == 5) {
        return 0;
    }
    if (f1 == 0) {
        if (func_02040a48(a->id) != 0) {
            return 1;
        }
    }
    if (kind == 4) {
        if (f2 != 0) {
            if (func_020408e8(a->id, x.a) != 0) {
                return 1;
            }
        } else {
            if (func_020408e8(a->id, x.a) != 0) {
                if (func_020408e8(a->id, (u8) (x.a - 1)) != 0) {
                    return 1;
                }
            }
        }
        if (func_020883cc() != 0 || func_02088394() != 0) {
            return 1;
        }
        return 0;
    }

    aLo = a->lo & ~0xff;
    aHi = a->hi & ~0xff;
    q = b;
    for (i = 0; i < n; q = q + 1, i++) {
        if (q->kind == 5) {
            continue;
        }
        if (kind < q->kind) {
            continue;
        }
        bLo = q->lo & ~0xff;
        bHi = q->hi;
        bHi &= ~0xff;
        if ((aLo < bHi && aHi > bLo) || (bLo < aHi && bHi > aLo)) {
            return 1;
        }
    }
    if (kind >= 2) {
        if (func_020883cc() != 0 || func_02088394() != 0) {
            return 1;
        }
    }
    if (kind >= 3) {
        if (func_020881c4(&data_021f3278) != 0) {
            return 1;
        }
    }
    switch (a->id) {
        case 0x3c:
            return func_02040b20(x);
        case 0x3d:
            return func_02040a90(x);
    }
    return 0;
}

void func_02040010(UnkStruct_02040010_2 *p, UnkStruct_02040010 x, ...)
{
    unsigned char c = x.c;
    if (p->h == 0x16) {
        goto L;
    }
    if (p->h == 0x18) {
        goto L;
    }
    if (p->h != 0x19) {
        goto skip;
    }
L:
    p->unk_06 = c;
    p->unk_05 = 6;
    p->unk_0A = c;
    p->unk_09 = 0x18;
skip:;
}

int func_0203ff98(Dst *dst, Src *src, void *c, UnkStruct_0203ff98 p)
{
    UnkStruct_0203ff98 r1, r2;
    int ok = 0;
    u32 hi;
    int n;
    hi = p.v & 0xffff0000;
    n = src->a;
    dst->a = (u16) n;
    dst->b = src->b;
    r1 = func_0204019c(src->unk_04, c, p, n);
    dst->p1 = r1;
    if (dst->p1.v != 0 && (dst->p1.v & 0xffff0000) <= hi) {
        r2 = func_02040180(src->unk_10, c, p, n);
        dst->p2 = r2;
        if (dst->p2.v != 0 && (dst->p2.v & 0xffff0000) >= hi) {
            ok = 1;
        }
    }
    return ok;
}
