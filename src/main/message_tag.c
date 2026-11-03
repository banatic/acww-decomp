/* message_tag: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a86a4 @ 0x020a86a4, 0x3e bytes, Thumb
 * func_020a8658 @ 0x020a8658, 0x4a bytes, Thumb
 * func_020a8630 @ 0x020a8630, 0x26 bytes, Thumb
 * func_020a861c @ 0x020a861c, 0x14 bytes, Thumb
 * func_020a85c4 @ 0x020a85c4, 0x58 bytes, Thumb
 * func_020a855c @ 0x020a855c, 0x66 bytes, Thumb
 * func_020a84e4 @ 0x020a84e4, 0x76 bytes, Thumb
 * func_020a8460 @ 0x020a8460, 0x84 bytes, Thumb
 * func_020a83ec @ 0x020a83ec, 0x72 bytes, Thumb
 * func_020a8370 @ 0x020a8370, 0x7a bytes, Thumb
 * func_020a835c @ 0x020a835c, 0x12 bytes, Thumb
 * func_020a8354 @ 0x020a8354, 0x6 bytes, Thumb
 * func_020a8328 @ 0x020a8328, 0x2c bytes, Thumb
 * func_020a8308 @ 0x020a8308, 0x20 bytes, Thumb
 * func_020a82f8 @ 0x020a82f8, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020a86a4 {
    unsigned char pad_00[12];
    void *x;
};

struct UnkStruct_020a8658 {
    unsigned char pad_00[0xc];
    void *unk_0C;
};

typedef struct {
    char pad_00[0xc];
    int val;
} UnkStruct_020a8630;

struct UnkStruct_020a861c {
    unsigned char pad_00[0xc];
    void *unk_0C;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
} ctx;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} node;

typedef struct UnkStruct_020a855c {
    int unk_00;
    int size;
} UnkStruct_020a855c;

typedef struct Hdr {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
} Hdr;

typedef struct {
    int x;
    int y;
} Ptr;

typedef struct {
    int pad_00;
    int pad_04;
    int a;
    int b;
} UnkStruct_020a84e4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Input;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a8460;

struct Something {
    char pad_00[4];
    unsigned int mode;
    int a;
    int b;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a8370;

typedef struct {
    char pad_00[8];
    int unk_08;
    int unk_0C;
} UnkStruct_020a8370_2;

typedef struct {
    int hdr;
    u8 b[8];
} Buf;

extern unsigned char func_020a87c8(void *arg, int idx);
extern unsigned short func_020a87a8(const void *arg0, int arg1);
extern void func_020a8718(ctx *p0, unsigned char *out1, unsigned char *out2);
extern int func_020a86e4(Hdr *h, unsigned char *p0, unsigned char *p1, unsigned char *p2);
extern int func_020a8a34(void *p, int base);
extern void *func_020ab8dc(void *);
extern void *func_020ab8c4(void *);
extern void func_020a873c(int, unsigned char *);
extern char data_020d1d70[];

void func_020a86a4(struct UnkStruct_020a86a4 *a, unsigned char *b, unsigned char *c, unsigned char *d, unsigned char *e)
{
    *b = func_020a87c8(a->x, 0);
    *c = func_020a87c8(a->x, 1);
    *d = func_020a87c8(a->x, 2);
    *e = func_020a87c8(a->x, 3);
}

void func_020a8658(struct UnkStruct_020a8658 *s, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                   unsigned char *e)
{
    *a = func_020a87c8(s->unk_0C, 0);
    *b = func_020a87c8(s->unk_0C, 1);
    *c = func_020a87c8(s->unk_0C, 2);
    *d = func_020a87c8(s->unk_0C, 3);
    *e = func_020a87c8(s->unk_0C, 4);
}

void func_020a8630(UnkStruct_020a8630 *s, unsigned char *dest, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = (int) func_020a87c8((void *) s->val, i);
    }
}

void func_020a861c(struct UnkStruct_020a861c *self, unsigned short *out)
{
    *out = func_020a87a8(self->unk_0C, 0);
}

unsigned int func_020a85c4(ctx *p0, unsigned char *p1, node *p2, unsigned char *p3, node *p4)
{
    unsigned char b0, b1;
    node *arr[2];
    unsigned int base;
    unsigned int sum;
    unsigned int i;

    func_020a8718(p0, &b0, &b1);
    *p1 = b0;
    *p3 = b1;

    arr[0] = p2;
    arr[1] = p4;

    base = p0->unk_0C + p0->unk_08 + 2;

    sum = 2;
    for (i = 0; i < 2; i++) {
        node *ptr = arr[i];
        unsigned int v;
        func_020a8a34((void *) ptr, base);
        v = ptr->unk_04 + 2;
        sum += v;
        base += v;
    }

    return sum;
}

int func_020a855c(Hdr *h, unsigned char *o0, UnkStruct_020a855c *e0, unsigned char *o1, UnkStruct_020a855c *e1,
                  unsigned char *o2, UnkStruct_020a855c *e2)
{
    unsigned char t[8];
    UnkStruct_020a855c *arr[3];
    int off;
    int total;
    int i;
    int n;

    func_020a86e4(h, &t[0], &t[1], &t[2]);
    *o0 = t[0];
    *o1 = t[1];
    *o2 = t[2];
    arr[0] = e0;
    arr[1] = e1;
    arr[2] = e2;
    off = h->unk_0C + h->unk_08 + 2;
    total = 2;
    for (i = 0; i < 3; i++) {
        func_020a8a34((void *) arr[i], off);
        n = arr[i]->size + 2;
        total = total + n;
        off = off + n;
    }
    return total;
}

int func_020a84e4(UnkStruct_020a84e4 *self, unsigned char *d1, Ptr *p1, unsigned char *d2, Ptr *p2, unsigned char *d3, Ptr *p3,
                  unsigned char *d4, Ptr *p4)
{
    unsigned char tmp[8];
    int base;
    Ptr *ptrs[4];
    int total;
    int i;
    int inc;
    func_020a86a4((struct UnkStruct_020a86a4 *) self, &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
    *d1 = tmp[0];
    *d2 = tmp[1];
    *d3 = tmp[2];
    *d4 = tmp[3];
    ptrs[0] = p1;
    ptrs[1] = p2;
    ptrs[2] = p3;
    ptrs[3] = p4;
    base = (self->b + self->a) + 2;
    total = 2;
    for (i = 0; i < 4; i++) {
        func_020a8a34(ptrs[i], base);
        inc = ptrs[i]->y + 2;
        total += inc;
        base += inc;
    }

    return total;
}

int func_020a8460(Input *input, unsigned char *out0, UnkStruct_020a8460 *pt0, unsigned char *out1, UnkStruct_020a8460 *pt1,
                  unsigned char *out2, UnkStruct_020a8460 *pt2, unsigned char *out3, UnkStruct_020a8460 *pt3,
                  unsigned char *out4, UnkStruct_020a8460 *pt4)
{
    unsigned char buf[9];
    UnkStruct_020a8460 *pts[5];
    int offset;
    int i;
    int sum;
    int d;

    func_020a8658((struct UnkStruct_020a8658 *) input, buf, buf + 1, buf + 2, buf + 3, buf + 4);

    *out0 = buf[0];
    *out1 = buf[1];
    *out2 = buf[2];
    *out3 = buf[3];
    *out4 = buf[4];

    pts[0] = pt0;
    pts[1] = pt1;
    pts[2] = pt2;
    pts[3] = pt3;
    pts[4] = pt4;

    offset = input->unk_0C + input->unk_08 + 2;
    sum = 2;
    i = 0;

    do {
        func_020a8a34(pts[i], offset);
        d = pts[i]->unk_04 + 2;
        sum += d;
        offset += d;
        i++;
    } while (i < 5);

    return sum;
}

unsigned int func_020a83ec(struct Something *p)
{
    unsigned int mode, count, i, sum;
    int next, delta;
    char buf[0x5c];

    mode = p->mode;
    count = 0;
    if (mode == 0 || mode == 4) {
        count = 2;
    } else if (mode == 1 || mode == 5) {
        count = 3;
    } else if (mode == 2 || mode == 6) {
        count = 4;
    } else if (mode == 3 || mode == 7) {
        count = 5;
    }

    func_020ab8dc(buf);
    sum = 2;
    next = p->b + p->a + 2;

    for (i = 0; i < count; i++) {
        func_020a8a34(buf, next);
        delta = *((int *) (buf + 4)) + 2;
        sum += delta;
        next += delta;
    }

    func_020ab8c4(buf);
    return sum;
}

int func_020a8370(UnkStruct_020a8370_2 *self, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f, u8 *g, u8 *h, UnkStruct_020a8370 *o0,
                  UnkStruct_020a8370 *o1)
{
    struct {
        Buf t;
        UnkStruct_020a8370 *arr[2];
    } L;
    int pos;
    int total;
    unsigned int i;
    int n;

    func_020a8630((UnkStruct_020a8630 *) self, (unsigned char *) L.t.b, 8);
    *a = L.t.b[0];
    *c = L.t.b[2];
    *e = L.t.b[4];
    *g = L.t.b[6];
    *b = L.t.b[1];
    *d = L.t.b[3];
    *f = L.t.b[5];
    *h = L.t.b[7];
    L.arr[0] = o0;
    L.arr[1] = o1;
    pos = self->unk_0C + self->unk_08 + 2;
    total = 2;
    for (i = 0; i < 2; i++) {
        UnkStruct_020a8370 *o = *(UnkStruct_020a8370 **) ((char *) L.arr + i * 4);
        func_020a8a34((void *) o, pos);
        n = o->unk_04 + 2;
        total = total + n;
        pos = pos + n;
    }
    return total;
}

int func_020a835c(int *p)
{
    int v = p[1];
    if (v < 15) {
        goto fail;
    }
    if (v > 25) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_020a8354(int *p)
{
    return p[1] - 0xf;
}

void func_020a8328(int *param0, int *param1, int *param2, int *param3)
{
    int temp;
    int val;
    int val2;

    temp = (int) func_020a87c8((void *) (*(int *) (param0 + 3)), 0);
    *param1 = temp;
    val = *(int *) (param0 + 3) + *(int *) (param0 + 2);
    *param2 = val;
    val2 = *(int *) (param0 + 3) + 1;
    *param3 = val2;
}

unsigned char func_020a8308(int arg)
{
    unsigned char val;
    func_020a873c(arg, &val);
    if (val == 6) {
        val = 5;
    }
    return val;
}

int func_020a82f8(int r0)
{
    return (int) (data_020d1d70 + r0 * 10);
}
