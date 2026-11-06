/* acre_map_2: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204e6a4 @ 0x0204e6a4, 0x12 bytes, Thumb
 * func_0204e65c @ 0x0204e65c, 0x48 bytes, Thumb
 * func_0204e624 @ 0x0204e624, 0x38 bytes, Thumb
 * func_0204e52c @ 0x0204e52c, 0xf8 bytes, Thumb
 * func_0204e510 @ 0x0204e510, 0x1c bytes, Thumb
 * func_0204e4bc @ 0x0204e4bc, 0x54 bytes, Thumb
 * func_0204e42c @ 0x0204e42c, 0x90 bytes, Thumb
 * func_0204e420 @ 0x0204e420, 0xc bytes, Thumb
 * func_0204e414 @ 0x0204e414, 0xc bytes, Thumb
 * func_0204e404 @ 0x0204e404, 0xe bytes, Thumb
 * func_0204e3f4 @ 0x0204e3f4, 0xe bytes, Thumb
 * func_0204e3bc @ 0x0204e3bc, 0x36 bytes, Thumb
 * func_0204e328 @ 0x0204e328, 0x94 bytes, Thumb
 * func_0204e204 @ 0x0204e204, 0x124 bytes, Thumb
 * func_0204e188 @ 0x0204e188, 0x7c bytes, Thumb
 * func_0204e108 @ 0x0204e108, 0x80 bytes, Thumb
 * func_0204e08c @ 0x0204e08c, 0x7c bytes, Thumb
 * func_0204dfe0 @ 0x0204dfe0, 0xac bytes, Thumb
 * func_0204df68 @ 0x0204df68, 0x78 bytes, Thumb
 * func_0204df54 @ 0x0204df54, 0x12 bytes, Thumb
 * func_0204df30 @ 0x0204df30, 0x24 bytes, Thumb
 * func_0204df08 @ 0x0204df08, 0x26 bytes, Thumb
 * func_0204dea0 @ 0x0204dea0, 0x68 bytes, Thumb
 * func_0204de5c @ 0x0204de5c, 0x44 bytes, Thumb
 * func_0204de34 @ 0x0204de34, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[8];
    int unk_1C;
} UnkStruct_0204e6a4;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_0204e52c;

typedef struct {
    u8 d[0x28];
} UnkStruct_0204e52c_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_0204e52c_3;

typedef struct {
    unsigned char pad_00[0x28];
} UnkStruct_0204e4bc;

typedef struct {
    UnkStruct_0204e4bc *unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204e4bc_2;

typedef struct {
    char pad_00[0x28];
} Elem;

typedef struct {
    Elem *data;        // 0x00
    int width;         // 0x04
    int height;        // 0x08
    char pad_0C[0x10]; // 0x0c-0x1b
    int unk_1C;        // 0x1c
} UnkStruct_0204e42c;

struct UnkStruct_0204e420 {
    char pad_00[0x1c];
    void *unk_1C;
};

// The accumulator is updated in three separate statements.

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0204e204;

typedef struct {
    u16 a, b;
} UnkStruct_0204e204_2;

struct UnkStruct_0204df54 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
};

extern void func_0205c158(int);
extern void *func_020e9948(void *p, unsigned int size);
extern void *data_021c80c0;
extern void func_020e993c(void *param, void *p);
extern void func_0205c13c(void);
extern int data_021e9aac;
extern int data_020ca0ec;
extern int data_020ca0e8;
extern int func_02037e90(int a, int b, int c);
extern UnkStruct_0204e52c *func_0204e8c4(int *tbl, int key);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_02037eec(UnkStruct_0204e52c_2 *e, int a, int *blk, int b, int c, int d, int f, int g, int *ip, int h);
extern unsigned char *func_0204e724(int *);
extern void func_02037e88(UnkStruct_0204e4bc *, unsigned char);
extern int data_021c9ab0;
extern void func_020e9b9c(int);
extern int func_02030ddc(int, int, int, int);
extern int func_02037e84(Elem *);
extern int func_0203750c(void);
extern int func_020377d8(int, int);
extern void func_02037ecc(Elem *, int, int, int);
extern void func_02030bac(void *);
extern int func_0204ef24(int a, int b, int c, int d);
extern int func_0204eea4(int a, int b, int c, int d);
extern int func_0204f3e4(void *a, u32 *b, u32 *c, u32 *d, u32 *e, u16 *f, u16 *g, u32 h, int i);
extern void func_0204f794(u32 a, int b, int c);
extern u16 *func_0204f5e0(void *a, int b, int c, int d, int e, int f);
extern int func_0204bcdc(void *s);
extern int func_0204bc64(void *p);
extern void *func_020b3b50(void *s);
extern u32 func_020b3d90(void *h);
extern int func_020b3d04(void *h, UnkStruct_0204e204 *a, UnkStruct_0204e204 *b, UnkStruct_0204e204 *c, u32 i);
extern int FX_Div(int a, int b);
extern int func_020310c8(int a);
extern int func_02060f30(int);
extern int data_021c80e0[];
extern int func_020b67e8(unsigned int);
extern int func_020b6818(int);
extern void func_0205c10c(void *self);
extern int func_0204dcb8(void *p, int i, void *self);
extern void func_0204dd78(int);
extern void func_0204dc9c(int, int);
extern void func_0205c0f0(void);
extern void func_0204de14(int *object, int index);

int func_0204e52c(UnkStruct_0204e52c_3 *p, int key);
void func_0204e510(void *a, void *b);
void func_0204e420(struct UnkStruct_0204e420 *ptr);
void func_0204de5c(int param0);

void func_0204e6a4(UnkStruct_0204e6a4 *s)
{
    s->unk_04 = 0;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0;
    s->unk_00 = 0;
    s->unk_1C = 1;
}

int func_0204e65c(void *arg0)
{
    void *condition_value0;
    int result = 1;
    func_0205c158((int) arg0);
    if (data_021c80c0 != 0) {
        goto done;
    }
    data_021c80c0 = func_020e9948(arg0, 0x20);
    if (data_021c80c0 == 0) {
        goto done;
    }
    if ((condition_value0 = (void *) (data_021c80c0))) {
        func_0204e6a4((UnkStruct_0204e6a4 *) condition_value0);
    }
    result = func_0204e52c((UnkStruct_0204e52c_3 *) data_021c80c0, (int) arg0);
done:
    return result;
}

void func_0204e624(void *param)
{
    if (data_021c80c0) {
        func_0204e420((struct UnkStruct_0204e420 *) data_021c80c0);
        func_0204e510(data_021c80c0, param);
        func_020e993c(param, data_021c80c0);
        data_021c80c0 = 0;
    }
    func_0205c13c();
}

int func_0204e52c(UnkStruct_0204e52c_3 *p, int key)
{
    UnkStruct_0204e52c *r;
    UnkStruct_0204e52c *q;
    UnkStruct_0204e52c_2 *e;
    int arr[8];
    int result = 0;

    p->unk_1C = 1;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(0x24, key, 4);
    }
    q = func_0204e8c4(&data_021e9aac, key);
    if (p->unk_00 != 0 && q != 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        arr[3] = 0;
        arr[4] = 0;
        e = (UnkStruct_0204e52c_2 *) p->unk_00;
        r = q;
        p->unk_04 = 6;
        p->unk_08 = 6;
        p->unk_14 = p->unk_04 * data_020ca0ec;
        p->unk_18 = p->unk_08 * data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        for (arr[1] = 0; arr[1] < p->unk_08; arr[1]++) {
            for (arr[0] = 0; arr[0] < p->unk_04; arr[0]++) {
                arr[2] = *(volatile int *) arr << 0x11;
                arr[4] = arr[1] << 0x11;
                arr[5] = arr[2];
                arr[6] = arr[3];
                arr[7] = arr[4];
                func_02037eec(e, r->unk_00, &arr[5], r->unk_04, r->unk_08, r->unk_0C, 0, 0, arr, p->unk_1C);
                e++;
                r++;
            }
        }
        result = 1;
    }
    if (q != 0) {
        func_020e993c((void *) key, (void *) q);
    }
    return result;
}

void func_0204e510(void *a, void *b)
{
    void *p;
    void *q;

    p = *(void **) a;
    if (p != 0) {
        func_020e993c(b, p);
        *(void **) a = 0;
    }
}

void func_0204e4bc(UnkStruct_0204e4bc_2 *self)
{
    unsigned char *q;
    UnkStruct_0204e4bc *p;
    int j = 0;
    int k;
    int i = 0;

    q = func_0204e724(&data_021e9aac);
    if (q != 0) {
        p = self->unk_00;
        for (i = 0; i < self->unk_08; i++) {
            for (k = j; k < self->unk_04; k++) {
                if (p != 0) {
                    func_02037e88(p, *q);
                }
                p++;
                q++;
            }
        }
    }
}

void func_0204e42c(UnkStruct_0204e42c *self)
{
    int gv;         // [sp, #0]
    int init;       // [sp, #4]
    Elem *fallback; // [sp, #8]
    int a;          // [sp, #0xc]
    int arg;        // [sp, #0x10]
    int i, j;
    Elem *ptr;
    int b;

    func_020e9b9c(data_021c9ab0);
    func_02030ddc(self->width, self->height, 0, self->unk_1C);

    init = 0;
    fallback = 0;
    arg = 0;

    for (i = 0; i < self->height; i++) {
        for (j = init; j < self->width; j++) {
            if ((unsigned int) j < (unsigned int) self->width && (unsigned int) i < (unsigned int) self->height &&
                self->data != 0) {
                ptr = &self->data[i * self->width + j];
            } else {
                ptr = fallback;
            }
            if (ptr != 0) {
                a = func_02037e84(ptr);
                gv = data_021c9ab0;
                func_0203750c();
                b = func_020377d8(a, gv);
                func_02037ecc(ptr, arg, b, self->unk_1C);
            }
        }
    }
}

void func_0204e420(struct UnkStruct_0204e420 *ptr)
{
    func_02030bac(ptr->unk_1C);
}

unsigned int func_0204e414(void)
{
    return (*(unsigned int *) &data_021c80c0);
}

int func_0204e404(int a, int b, int c, int d)
{
    return func_0204ef24(a, b, c, d);
}

int func_0204e3f4(int a, int b, int c, int d)
{
    return func_0204eea4(a, b, c, d);
}

int func_0204e3bc(int a, int b, int c, int d, int e, int f)
{
    int local1;
    int local2;
    int local3;
    int local4;

    local1 = 0;
    local2 = 0;
    local3 = d;
    local4 = e;
    func_0204f800((int *) (&local1), (int *) (&local2), b, c, local3, local4);
    return func_0204e3f4(a, local1, local2, f);
}

void func_0204e328(u16 *out, void *arg, u32 p3, int *p4, int *p5, u16 a, u16 b, u32 c)
{
    u16 pair[2];
    u32 v[8];
    int p4_val, p5_val;
    int high4, high5, low4, low5;
    u16 *res;

    pair[0] = a;
    pair[1] = b;

    if (func_0204f3e4(arg, &v[2], &v[3], &v[0], &v[1], &pair[0], &pair[1], c, 0) != 0) {
        func_0204f800(p4, p5, v[2], v[3], v[0], v[1]);
        func_0204f794(p3, *p4, *p5);

        p4_val = *p4;
        p5_val = *p5;
        high4 = p4_val >> 4;
        high5 = p5_val >> 4;
        low5 = p5_val - (high5 << 4);
        low4 = p4_val - (high4 << 4);

        res = func_0204f5e0(arg, high4, high5, low4, low5, 0);
        if (res != 0) {
            *out = *res;
            return;
        }
    }
    *out = 0xfff1;
}

void func_0204e204(u16 *out, void *arg, int *dst, int *o4, int *o5, u16 a, u16 b, u32 c)
{
    UnkStruct_0204e204_2 s;
    int p4v, p5v;
    UnkStruct_0204e204 vec, A, B, C;
    void *h;
    u32 n, i;
    int sx, sy;
    int result;
    int qx, t, u, d;

    func_0204e328((u16 *) &s, arg, (u32) (&vec), &p4v, &p5v, a, b, c);
    if (func_0204bcdc(&s)) {
        s.b = 0xfff1;
        result = (func_0204bc64(&s) == func_0204bc64(&s.b));
    } else {
        result = (s.a == 0xfff1);
    }
    if (result) {
        goto fail;
    }
    h = func_020b3b50(&s);
    if (h == 0) {
        goto fail;
    }
    n = func_020b3d90(h);
    sx = 0;
    sy = 0;
    i = 0;
    while (i < n) {
        if (func_020b3d04(h, &A, &B, &C, i)) {
            sx = sx + A.unk_00;
            sx = sx + B.unk_00;
            sx = sx + C.unk_00;
            sy = sy + A.unk_08;
            sy = sy + B.unk_08;
            sy = sy + C.unk_08;
        }
        i++;
    }
    d = (3 * func_020b3d90(h)) << 12;
    qx = FX_Div(sx, d);
    t = vec.unk_08 + FX_Div(sy, d) + 0x1000;
    u = func_020310c8(0);
    dst[0] = vec.unk_00 + qx;
    dst[1] = u;
    dst[2] = t;
    if (o4 != 0) {
        *o4 = p4v;
    }
    if (o5 != 0) {
        *o5 = p5v;
    }
    *out = s.a;
    return;
fail:
    *out = 0xfff1;
}

int func_0204e188(int param1, int param2, int param3, int param4)
{
    struct {
        unsigned short a;
        unsigned short b;
    } s;
    int result;

    func_0204e204((u16 *) (&s), (void *) param1, (int *) param2, (int *) param3, (int *) param4, 0x5000, 0x5000, 0x200);
    if (func_0204bcdc(&s)) {
        s.b = 0xfff1;
        result = (func_0204bc64(&s) == func_0204bc64(&s.b));
    } else {
        result = (s.a == 0xfff1);
    }
    return !result;
}

int func_0204e108(int a0, int a1, int a2, int a3)
{
    struct {
        unsigned short x;
        unsigned short y;
    } s;
    int r;

    func_0204e204((u16 *) (&s), (void *) a0, (int *) a1, (int *) a2, (int *) a3, 0x5014, 0x501a, 1);
    if (func_0204bcdc(&s) != 0) {
        s.y = 0xfff1;
        if (func_0204bc64(&s) == func_0204bc64(&s.y)) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (s.x == 0xfff1) {
            r = 1;
        } else {
            r = 0;
        }
    }
    return !r;
}

int func_0204e08c(int p0, int p1, int p2, int p3)
{
    unsigned short local[4];
    int result;

    func_0204e204((u16 *) local, (void *) p0, (int *) p1, (int *) p2, (int *) p3, 0x500b, 0x500b, 0x400);

    if (func_0204bcdc(local) != 0) {
        local[1] = 0xfff1;
        if (func_0204bc64(local) == func_0204bc64(&local[1])) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (local[0] == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204dfe0(int a0, int *a1, int *a2, int *a3)
{
    unsigned short buf[2];
    int result;

    func_0204e204((u16 *) buf, (void *) a0, a1, a2, a3, 0x5000, 0x5000, 0x200);

    if (func_0204bcdc((void *) buf) != 0) {
        buf[1] = 0xfff1;
        if (func_0204bc64((void *) buf) == func_0204bc64((void *) (&buf[1]))) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (buf[0] == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result == 0) {
        *a1 -= 0x2000;
        a1[2] += 0x8000;
        if (a2) {
            (*a2)--;
        }
        if (a3) {
            (*a3) += 4;
        }
        return 1;
    } else {
        return 0;
    }
}

int func_0204df68(int a, int b)
{
    unsigned short buf[2];
    void *p2;
    void *p3;
    int result;

    func_0204e328((u16 *) buf, (void *) a, b, (int *) (&p2), (int *) (&p3), 0x5020, 0x5020, 0);

    if (func_0204bcdc(buf)) {
        buf[1] = 0xfff1;
        if (func_0204bc64(buf) == func_0204bc64(&buf[1])) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (buf[0] == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    return (result == 0) ? 1 : 0;
}

void func_0204df54(struct UnkStruct_0204df54 *r0)
{
    r0->unk_04 = 0;
    r0->unk_08 = 0;
    r0->unk_0C = 0;
    r0->unk_10 = 0;
    r0->unk_00 = 0;
    r0->unk_1C = 2;
}

int func_0204df30(int param)
{
    int result = 0;
    if (func_02060f30(param)) {
        result = data_021c80e0[param];
    }
    return result;
}

int func_0204df08(int param)
{
    int result;
    int temp;

    result = 0;
    if (func_020b67e8(param) != 0) {
        temp = func_020b6818(param);
        result = func_0204df30(temp);
    }
    return result;
}

int func_0204dea0(void *self)
{
    int i;
    int ok;

    ok = 1;
    func_0205c10c(self);
    for (i = 0; i < 5; i++) {
        if (((void **) data_021c80e0)[i] == 0) {
            ((void **) data_021c80e0)[i] = func_020e9948(self, 0x20);
            // Shared failure block, placed after the f3 test.
            if (((void **) data_021c80e0)[i] == 0) {
                goto fail;
            }
            if (((void **) data_021c80e0)[i] != 0) {
                func_0204df54((struct UnkStruct_0204df54 *) (((void **) data_021c80e0)[i]));
            }
            if (func_0204dcb8(((void **) data_021c80e0)[i], i, self) == 0) {
                ok = 0;
                break;
            }
        }
        continue;
    fail:
        ok = 0;
        break;
    }
    if (ok == 0) {
        func_0204de5c((int) self);
    }
    return ok;
}

void func_0204de5c(int param0)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204dd78(data_021c80e0[i]);
            func_0204dc9c(data_021c80e0[i], param0);
            func_020e993c((void *) param0, (void *) data_021c80e0[i]);
            data_021c80e0[i] = 0;
        }
    }
    func_0205c0f0();
}

void func_0204de34(void)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204de14((int *) data_021c80e0[i], i);
        }
    }
}
