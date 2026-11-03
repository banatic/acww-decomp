/* villager_outdoors: 27 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207a404 @ 0x0207a404, 0x48 bytes, Thumb
 * func_0207a340 @ 0x0207a340, 0xc4 bytes, Thumb
 * func_0207a338 @ 0x0207a338, 0x8 bytes, Thumb
 * func_0207a334 @ 0x0207a334, 0x2 bytes, Thumb
 * func_0207a318 @ 0x0207a318, 0x1c bytes, Thumb
 * func_0207a308 @ 0x0207a308, 0x10 bytes, Thumb
 * func_0207a2fc @ 0x0207a2fc, 0xc bytes, Thumb
 * func_0207a2d8 @ 0x0207a2d8, 0x24 bytes, Thumb
 * func_0207a2a4 @ 0x0207a2a4, 0x34 bytes, Thumb
 * func_0207a264 @ 0x0207a264, 0x40 bytes, Thumb
 * func_0207a254 @ 0x0207a254, 0x10 bytes, Thumb
 * func_0207a244 @ 0x0207a244, 0x10 bytes, Thumb
 * func_0207a210 @ 0x0207a210, 0x32 bytes, Thumb
 * func_0207a1e4 @ 0x0207a1e4, 0x2c bytes, Thumb
 * func_0207a1c8 @ 0x0207a1c8, 0x1c bytes, Thumb
 * func_0207a1c0 @ 0x0207a1c0, 0x8 bytes, Thumb
 * func_0207a188 @ 0x0207a188, 0x38 bytes, Thumb
 * func_0207a180 @ 0x0207a180, 0x8 bytes, Thumb
 * func_0207a118 @ 0x0207a118, 0x68 bytes, Thumb
 * func_0207a02c @ 0x0207a02c, 0xec bytes, Thumb
 * func_02079fc8 @ 0x02079fc8, 0x64 bytes, Thumb
 * func_02079f60 @ 0x02079f60, 0x66 bytes, Thumb
 * func_02079ef0 @ 0x02079ef0, 0x70 bytes, Thumb
 * func_02079e64 @ 0x02079e64, 0x8c bytes, Thumb
 * func_02079db8 @ 0x02079db8, 0xac bytes, Thumb
 * func_02079d38 @ 0x02079d38, 0x80 bytes, Thumb
 * func_02079cc4 @ 0x02079cc4, 0x74 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0207a404 {
    unsigned char *p;
    unsigned char n;
} UnkStruct_0207a404;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0207a318;

typedef struct {
    char pad_00[8];
    signed char arr[4];
} UnkStruct_0207a210;

typedef struct {
    unsigned char pad_00[8];
    signed char b[4];
} UnkStruct_0207a1e4;

typedef struct UnkStruct_0207a118 {
    unsigned char pad_00[0xc];
    long long v;
} UnkStruct_0207a118;

typedef struct {
    char pad_00[0x7ec];
} Entry;

typedef struct {
    char b[0x2c];
} UnkStruct_02079db8;

typedef struct {
    char b[8];
} UnkStruct_02079db8_2;

typedef struct {
    u8 data[0x7ec];
} BigStruct;

typedef struct {
    u8 data[0x2c];
} SmallStruct;

typedef struct {
    int a;
    int b;
} Pair;

extern void func_0209e474(void *);
extern void *func_020617d8(int);
extern char *func_02079350(void);
extern int func_020951bc(int);
extern int func_0208150c(const void *self);
extern int func_02003704(int);
extern int func_020807a8(const void *self, int a);
extern int func_0207f1d8(const void *self);
extern int func_020644cc(int n);
extern void MI_CpuFill8(int a, int b, int c);
extern void MI_CpuCopy8(int a, int b, int c);
extern int func_0207cf74(int);
extern int func_0209dffc(long long *);
extern int func_0209e3ac(void *, long long *, int);
extern int func_0209e350(void *, void *);
extern int func_0204c7c0(void);
extern int func_0207b3dc(int a);
extern int func_0207d6c4(void *p);
extern void func_020794d4(char *, int);
extern void func_02079540(char *, int);
extern int func_0207918c(void);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void *func_020036e8(void *);
extern int func_020821d4(void *, void *);
extern int func_02082240(void);
extern int func_0207cadc(void *a);

void func_0207a308(int a, int b);
void func_0207a254(void *r0);

int func_0207a404(void)
{
    int local[2];
    UnkStruct_0207a404 *b;
    unsigned char *q;
    int prev;
    int i;
    int n;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    b = (UnkStruct_0207a404 *) func_020617d8(((unsigned char *) local)[4] - 1);
    if (b != 0) {
        q = b->p;
        prev = 0;
        i = 0;
        n = b->n;
        while (i < n) {
            if (q[0] == 0x30) {
                return q[1] - prev;
            }
            prev = q[1];
            q += 2;
            i++;
        }
    }
    return 0;
}

void func_0207a340(const char *self, int a)
{
    unsigned char mask;
    int count;
    int i;
    int sel;
    int thr;

    func_02079350()[0x160] = -1;

    if (a == 0) {
        return;
    }
    if (func_020951bc(a) == 0) {
        return;
    }

    thr = func_0207a404();

    mask = 0;
    count = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(self)) != 0 && func_020807a8(self, a) != 0 && func_0207f1d8(self) == 0) {
            mask |= (1 << i);
            count++;
        }
        self += 0x7ec;
    }

    while (count > 0) {
        sel = func_020644cc(count);
        count--;
        for (i = 0; i < 8; i++) {
            if (((mask >> i) & 1) != 0) {
                if (sel == 0) {
                    if (func_020644cc(100) < thr) {
                        func_02079350()[0x160] = i;
                        count = 0;
                    }
                    mask &= ~(1 << i);
                    break;
                }
                sel--;
            }
        }
    }
}

void func_0207a338(int *p0)
{
    p0[3] = 0;
    p0[4] = 0;
}

void func_0207a334(void *object) {}

void func_0207a318(UnkStruct_0207a318 *p)
{
    func_0207a308((int) p, (int) p);
    func_0207a254((void *) p);
    p->unk_0C = 0;
    p->unk_10 = 0;
}

void func_0207a308(int a, int b)
{
    MI_CpuFill8(b, 0xff, 8);
}

void func_0207a2fc(int a, int b, int c)
{
    MI_CpuCopy8(c, b, 8);
}

int func_0207a2d8(int r0, int r1, int r2)
{
    int r4 = 0;
    int r5 = r1;
    int r6 = r0;
    int r7 = r2;

    if (func_0207cf74(r5) != 0) {
        *(unsigned char *) (r6 + r5) = (unsigned char) r7;
        r4 = 1;
    }

    return r4;
}

void func_0207a2a4(char *a, int b)
{
    if (func_0207cf74(b)) {
        int i;
        char *p = a;
        for (i = 0; i < 8; i++) {
            if (*p == -1) {
                *p = b;
                break;
            }
            p++;
        }
    }
}

void func_0207a264(char *s, int c)
{
    int i;

    if (func_0207cf74(c)) {
        for (i = 0; i < 8; i++) {
            if (c == s[i]) {
                while (i < 7) {
                    s[i] = s[i + 1];
                    i++;
                }
                s[7] = -1;
                return;
            }
        }
    }
}

void func_0207a254(void *r0)
{
    MI_CpuFill8((int) ((char *) r0 + 8), 0xff, 4);
}

int func_0207a244(char *arr, unsigned int index, char value)
{
    if (index < 4) {
        (arr + index)[8] = value;
        return 1;
    } else {
        return 0;
    }
}

int func_0207a210(UnkStruct_0207a210 *s, int b)
{
    int i;
    if (func_0207cf74(b) == 0) {
        goto fail;
    }
    for (i = 0; i < 4; i++) {
        if (b == s->arr[i]) {
            return i;
        }
    }
fail:
    return -1;
}

void func_0207a1e4(UnkStruct_0207a1e4 *p, int argument1)
{
    int i = func_0207a210((UnkStruct_0207a210 *) p, (int) argument1);
    if ((unsigned int) i < 4) {
        for (; i < 3; i = i + 1) {
            p->b[i] = p->b[i + 1];
        }
        p->b[3] = -1;
    }
}

void func_0207a1c8(int a, int b)
{
    func_0207a264((char *) a, b);
    func_0207a1e4((UnkStruct_0207a1e4 *) a, b);
}

int func_0207a1c0(void *argument0, int argument1)
{
    return func_0207a210((UnkStruct_0207a210 *) ((void *) argument0), (int) argument1);
}

void func_0207a188(char *arr, char *data)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c((const void *) data))) {
            arr[i] = i;
        } else {
            arr[i] = -1;
        }
        data += 0x7ec;
    }
}

void func_0207a180(int *p0)
{
    p0[3] = 0;
    p0[4] = 0;
}

int func_0207a118(UnkStruct_0207a118 *self, void *other)
{
    int r;
    int t;
    if (self->v == 0 || func_0209dffc(&self->v) != 0) {
        return 1;
    }
    r = 0;
    t = func_0209e3ac(other, &self->v, 0x3e);
    if (t == -1) {
        r = func_0209e350(other, &self->v);
    } else if (t == 1) {
        r = func_0209e350(&self->v, other);
    }
    if (r >= 0x3c) {
        return 1;
    }
    return 0;
}

void func_0207a02c(int p0, u8 *out, int *count, s8 *list, char *base, int limit)
{
    u8 mask;
    int n;
    s8 *p;
    int id;
    int self;
    int i;
    int k;
    s8 *q;
    int j;
    int t;
    int b;

    mask = 0;
    n = 0;
    self = func_0207b3dc(func_0204c7c0() + 0x9284);
    p = list;
    for (i = 0; i < 8; i++) {
        id = *p;
        if (func_0207cf74(id) != 0) {
            if (id != self) {
                id = id * 0x7ec;
                if (func_0207d6c4(base + id) != 0) {
                    mask = (u8) (mask | (1 << i));
                    n++;
                    if (n >= 6) {
                        break;
                    }
                }
            }
        }
        p++;
    }
    while (n > 0 && *count < limit) {
        k = func_020644cc(n);
        q = list;
        for (j = 0; j < 8; j++) {
            b = *q;
            t = mask;
            t = t >> j;
            t = t & 1;
            if (t != 0) {
                if (k == 0) {
                    out[*count] = (u8) b;
                    *count = *count + 1;
                    *q = -1;
                    mask = (u8) (mask & ~(1 << j));
                    break;
                }
                k--;
            }
            q++;
        }
        n--;
    }
}

void func_02079fc8(void *arg0, char *arg1, int *arg2, void *arg3)
{
    int i;
    char c;
    void *ptr;
    int zero = 0;
    int neg_one = -1;
    int idx = 0;

    for (i = 0; i < 8; i++) {
        c = arg1[idx];
        if (func_0207cf74((char) c) != 0) {
            if (func_0207a2d8((int) arg0, *arg2, (char) c) != 0) {
                (*arg2)++;
                ptr = (char *) arg3 + c * 44;
                func_020794d4((char *) ptr, 1);
                func_02079540((char *) ptr, zero);
                *arg1 = neg_one;
            }
        }
        arg1++;
    }
}

void func_02079f60(void *ptr, char *str, int *count, char *table, int n)
{
    char *elem;
    int zero1 = 0;
    int zero2 = 0;
    int i;

    for (i = 0; i < n; i++) {
        signed char c = str[zero2];
        if (func_0207a2d8((int) ptr, *count, (signed char) c)) {
            (*count)++;
            elem = table + c * 44;
            func_020794d4(elem, zero1);
            func_02079540(elem, 1);
            func_0207a244((char *) ptr, i, (signed char) c);
        }
        str++;
    }
}

void func_02079ef0(int unused, signed char *out, int *count, signed char *list, Entry *table)
{
    int neg = -1;
    int zero = 0;
    int i;
    int v;

    v = func_0207918c();
    if (func_0207cf74(v)) {
        for (i = 0; i < 8; i++) {
            signed char c = list[zero];
            if (func_0207cf74(c)) {
                if (c == v) {
                    if (func_02003704((int) ((void *) func_0208150c((const void *) (&table[c]))))) {
                        out[*count] = c;
                        *count = *count + 1;
                    }
                    *list = neg;
                }
            }
            list++;
        }
    }
}

void func_02079e64(void *a, char *b, void *c)
{
    void *h;
    int v;
    int flag;
    char *q;
    void *x;
    int i;
    int zero;

    h = func_020984e8();
    if (h != 0) {
        v = func_02099020(h, 1);
    } else {
        v = 0;
    }
    flag = (v != 0) ? 1 : 0;
    q = func_02079350();
    i = 0;
    zero = 0;
    for (; i < 8; i++) {
        x = (void *) func_0208150c((const void *) b);
        if (func_02003704((int) x) != 0) {
            if (flag == 0) {
                if (func_020821d4(func_020036e8(x), c) != 0) {
                    func_020794d4(q, 2);
                    func_02079540(q, zero);
                }
            }
        } else {
            func_020794d4(q, 3);
            func_02079540(q, 7);
        }
        b += 0x7ec;
        q += 0x2c;
    }
}

void func_02079db8(void *self, void *a1)
{
    int lim;
    int m;
    UnkStruct_02079db8 *base;
    UnkStruct_02079db8_2 A;
    UnkStruct_02079db8_2 B;
    int c;
    int d;
    int i;

    base = (UnkStruct_02079db8 *) func_02079350();
    c = 0;
    lim = func_02082240();
    m = func_0207cadc(a1);
    i = 0;
    d = 0;
    for (; i < 8; i++) {
        func_020794d4((char *) (&base[i]), 3);
    }
    func_0207a2fc((int) self, (int) (&A), (int) self);
    func_0207a308((int) self, (int) self);
    func_0207a308((int) self, (int) (&B));
    m = m * 3;
    if (lim > (m >> 2)) {
        lim = m >> 2;
    }
    func_0207a254(self);
    func_02079ef0((int) self, (signed char *) (&B), &c, (signed char *) (&A), (Entry *) a1);
    func_0207a02c((int) self, (u8 *) (&B), &c, (s8 *) (&A), (char *) a1, lim);
    func_02079fc8(self, (char *) (&A), &d, (void *) base);
    func_02079f60(self, (char *) (&B), &d, (char *) base, c);
}

void func_02079d38(unsigned int a, BigStruct *b)
{
    SmallStruct *p = (SmallStruct *) func_02079350();
    int i;
    int varB = 0;
    int varA = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c((const void *) b)) != 0) {
            if (func_0207a210((UnkStruct_0207a210 *) a, i) != -1) {
                func_020794d4((char *) p, varA);
                func_02079540((char *) p, 1);
            } else {
                func_020794d4((char *) p, 1);
                func_02079540((char *) p, varB);
            }
        } else {
            func_020794d4((char *) p, 3);
            func_02079540((char *) p, 7);
        }
        b++;
        p++;
    }
}

void func_02079cc4(void *p0, void *p1, int p2)
{
    Pair pr;
    char *base;
    int i;

    pr.a = 0;
    pr.b = 0;
    base = func_02079350();
    for (i = 0; i < 8; i++) {
        func_020794d4(base + 0x2c * i, 3);
    }
    func_0209e474((void *) (&pr));
    if (func_0207a118((UnkStruct_0207a118 *) p0, (void *) (&pr)) != 0) {
        func_02079db8(p0, p1);
        if (p2 != 0) {
            MI_CpuCopy8((int) (&pr), (int) ((char *) p0 + 0xc), 8);
        }
    } else {
        func_02079d38((unsigned int) p0, (BigStruct *) p1);
    }
    func_02079e64(p0, (char *) p1, (void *) (&pr));
}
