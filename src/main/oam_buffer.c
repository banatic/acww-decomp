/* oam_buffer: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02088de8 @ 0x02088de8, 0x10 bytes, Thumb
 * func_02088dd8 @ 0x02088dd8, 0x10 bytes, Thumb
 * func_02088dc8 @ 0x02088dc8, 0x10 bytes, Thumb
 * func_02088db8 @ 0x02088db8, 0x10 bytes, Thumb
 * func_02088d9c @ 0x02088d9c, 0x1c bytes, Thumb
 * func_02088d94 @ 0x02088d94, 0x6 bytes, Thumb
 * func_02088d34 @ 0x02088d34, 0x60 bytes, Thumb
 * func_02088cf4 @ 0x02088cf4, 0x40 bytes, Thumb
 * func_02088c60 @ 0x02088c60, 0x94 bytes, Thumb
 * func_02088c14 @ 0x02088c14, 0x4c bytes, Thumb
 */

struct Elem {
    int x;
    int y;
};

typedef struct {
    int a, b, c, d;
} Quad;

typedef struct {
    char pad_00[6];
    short v;
} UnkStruct_02088c60;

typedef struct {
    UnkStruct_02088c60 unk_00, s1, s2, s3;
} Entry;

extern int data_020d0a04[];
extern int data_020d09d4[];
extern int data_021c8c9c;

int func_02088de8(int a, int b)
{
    return data_020d0a04[b + (a << 2)];
}

unsigned int func_02088dd8(unsigned int *p)
{
    unsigned int x = *p;
    return (unsigned int) func_02088de8((x << 16) >> 30, x >> 30);
}

int func_02088dc8(int a, int b)
{
    return data_020d09d4[a * 4 + b];
}

int func_02088db8(unsigned int *ptr)
{
    unsigned int val = *ptr;
    return func_02088dc8((val << 16) >> 30, val >> 30);
}

int func_02088d9c(unsigned int *p)
{
    unsigned int word = *p;
    int field = (int) ((word << 7) >> 23);
    if (field < 0x100) {
        return field;
    } else {
        return field - 0x200;
    }
}

int func_02088d94(signed char *p)
{
    return p[0];
}

int func_02088d34(void *self, int b, int c, int d, int e)
{
    int t;
    int h;
    int r;

    t = func_02088d9c((unsigned int *) self) - d;
    if (t > b) {
        return 0;
    }

    r = (int) func_02088dd8((unsigned int *) self);
    if ((d << 1) + r + t < b) {
        return 0;
    }

    h = func_02088d94((signed char *) self) - e;
    if (h > c) {
        return 0;
    }

    r = func_02088db8((unsigned int *) self);
    if ((e << 1) + r + h < c) {
        return 0;
    }

    return 1;
}

int func_02088cf4(struct Elem *p, int count, int a, int b, int c, int d)
{
    int i;
    for (i = 0; i < count; i++) {
        if (func_02088d34(p, a, b, c, d)) {
            return i;
        }
        p++;
    }
    return -1;
}

int func_02088c60(Entry *table, int *countp, Quad *q)
{
    unsigned int *qu = (unsigned int *) q;
    unsigned short c0 = (unsigned short) (qu[0] >> 4);
    unsigned short c1 = (unsigned short) (qu[1] >> 4);
    unsigned short c2 = (unsigned short) (qu[2] >> 4);
    unsigned short c3 = (unsigned short) (qu[3] >> 4);
    int i = 0;
    int count = *countp;

    for (; i < count; i += 4) {
        Entry *e = (Entry *) ((char *) table + i * 8);
        if (c0 != (unsigned short) e->unk_00.v) {
            continue;
        }
        if (c1 != (unsigned short) e->s1.v) {
            continue;
        }
        if (c2 != (unsigned short) e->s2.v) {
            continue;
        }
        if (c3 != (unsigned short) e->s3.v) {
            continue;
        }
        return i >> 2;
    }

    if (count < 0x80) {
        Entry *e = (Entry *) ((char *) table + count * 8);
        int ret;
        e->unk_00.v = (short) (q->a >> 4);
        e->s1.v = (short) (q->b >> 4);
        e->s2.v = (short) (q->c >> 4);
        e->s3.v = (short) (q->d >> 4);
        ret = *countp >> 2;
        *countp = *countp + 4;
        return ret;
    }
    return -1;
}

int func_02088c14(unsigned int n)
{
    switch (n) {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
            if (data_021c8c9c == 1) {
                return 1;
            } else {
                return 0;
            }
        case 3:
            if (data_021c8c9c == 0) {
                return 1;
            } else {
                return 0;
            }
        default:
            return 0;
    }
}
