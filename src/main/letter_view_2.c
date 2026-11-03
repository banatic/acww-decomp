/* letter_view_2: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206e344 @ 0x0206e344, 0x18 bytes, Thumb
 * func_0206e2ec @ 0x0206e2ec, 0x58 bytes, Thumb
 * func_0206e2e4 @ 0x0206e2e4, 0x8 bytes, Thumb
 * func_0206e2d0 @ 0x0206e2d0, 0x14 bytes, Thumb
 * func_0206e230 @ 0x0206e230, 0x9e bytes, Thumb
 * func_0206e224 @ 0x0206e224, 0xc bytes, Thumb
 * func_0206e1d8 @ 0x0206e1d8, 0x4c bytes, Thumb
 * func_0206e114 @ 0x0206e114, 0xc4 bytes, Thumb
 * func_0206e03c @ 0x0206e03c, 0xd8 bytes, Thumb
 * func_0206dff8 @ 0x0206dff8, 0x44 bytes, Thumb
 * func_0206dfe0 @ 0x0206dfe0, 0x16 bytes, Thumb
 * func_0206df58 @ 0x0206df58, 0x88 bytes, Thumb
 * func_0206df40 @ 0x0206df40, 0x18 bytes, Thumb
 * func_0206df1c @ 0x0206df1c, 0x22 bytes, Thumb
 * func_0206de88 @ 0x0206de88, 0x92 bytes, Thumb
 * func_0206de7c @ 0x0206de7c, 0xc bytes, Thumb
 * func_0206de70 @ 0x0206de70, 0xc bytes, Thumb
 * func_0206de38 @ 0x0206de38, 0x38 bytes, Thumb
 * func_0206de0c @ 0x0206de0c, 0x2c bytes, Thumb
 * func_0206ddd4 @ 0x0206ddd4, 0x38 bytes, Thumb
 * func_0206ddd0 @ 0x0206ddd0, 0x4 bytes, Thumb
 * func_0206ddcc @ 0x0206ddcc, 0x4 bytes, Thumb
 * func_0206dd8c @ 0x0206dd8c, 0x40 bytes, Thumb
 * func_0206dd6c @ 0x0206dd6c, 0x20 bytes, Thumb
 * func_0206dd48 @ 0x0206dd48, 0x24 bytes, Thumb
 * func_0206dd44 @ 0x0206dd44, 0x4 bytes, Thumb
 * func_0206dd08 @ 0x0206dd08, 0x3c bytes, Thumb
 * func_0206dd04 @ 0x0206dd04, 0x4 bytes, Thumb
 * func_0206dcec @ 0x0206dcec, 0x18 bytes, Thumb
 * func_0206dc1c @ 0x0206dc1c, 0xce bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x44];
    unsigned short arr44[10];
    unsigned char pad_58[0xf8 - 0x58];
    unsigned char unk_F8;
} Arg1T;

typedef struct {
    unsigned char pad_00[0x320];
    int unk_320;
} SelfT;

typedef struct {
    unsigned char pad_00[0x74];
} UnkStruct_0206e03c;

typedef struct {
    unsigned char pad_00[0xe8];
    UnkStruct_0206e03c arr[4];
    unsigned char pad_2B8[0x308 - 0x2b8];
    int unk_308[5];
    int unk_31C;
} UnkStruct_0206e03c_2;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x60];
} Buffer;

typedef struct {
    unsigned char pad_00[0x308];
    int arr[5];
    int count;
} UnkStruct_0206de38;

typedef struct UnkStruct_0206dd8c {
    void *unk_00;
    char pad_04[0x60];
    int unk_64;
    unsigned short unk_68;
    char pad_6A[3];
    char unk_6D;
    char unk_6E;
    char pad_6F;
    char unk_70;
    char unk_71;
} UnkStruct_0206dd8c;

typedef struct {
    void *unk_00;
} Obj_t;

typedef struct {
    char pad_00[0x68];
    unsigned short unk_68;
    unsigned char unk_6A;
    unsigned char unk_6B;
    unsigned char unk_6C;
} UnkStruct_0206dd08;

struct UnkStruct_0206dc1c;

struct UnkStruct_0206dc1c_2;

typedef struct UnkStruct_0206dc1c UnkStruct_0206dc1c;

typedef struct UnkStruct_0206dc1c_2 UnkStruct_0206dc1c_2;

struct UnkStruct_0206dc1c {
    u8 pad_00[0x2c];
    u32 unk_2C;
    u8 pad1[0x8];
    u8 unk_38;
    u8 unk_39;
    u8 pad_3A[0x16];
    u32 unk_50;
    u8 pad_54[0x1];
    u8 unk_55;
};

struct UnkStruct_0206dc1c_2 {
    u8 pad_00[0x64];
    UnkStruct_0206dc1c *unk_64;
    u16 unk_68;
    u8 unk_6A;
    u8 unk_6B;
    u8 pad1[0x1];
    u8 unk_6D;
    u8 unk_6E;
    u8 unk_6F;
    u8 unk_70;
    u8 unk_71;
};

extern void *data_021fbe94;
extern int func_02002ca4(void *a, void *b, int c);
extern unsigned char data_020df280[];
extern void func_0200277c(unsigned char *p);
extern void func_020029e8(unsigned char *p, int v);
extern void func_020028bc(unsigned char *p, int a, int b, int c);
extern void func_0200284c(unsigned char *p, int a, int b);
extern unsigned char *func_02066648(unsigned char *p);
extern void func_ov002_0220a448(unsigned char *p, unsigned char *q);
extern void func_02051bf8(void *p, int n);
extern int func_02065f4c(void *dst, void *src);
extern void *func_02051c8c_unk(void *p, int n);
extern void *func_02051d08(void *p, int n);
extern void func_0206db74(void *);
extern void func_0206db50(SelfT *self, unsigned char v, unsigned char n);
extern void *func_020a88ec(void *listObj);
extern void func_020a8874(void *listObj, unsigned short *arr, int n);
extern void func_0206dbc0(SelfT *self, void *listObj);
extern void *func_020a887c(void *listObj);
extern void func_0206dba8(UnkStruct_0206e03c *e, void *o, int m);
extern char data_020df270[];
extern void func_0206db5c(void *, unsigned char, unsigned char, int);
extern int func_02051c14(const unsigned short *src, int min, int mode, int *out, int flag);
extern void func_0206dbd8(int, int);
extern void *func_020a8cac(void *self);
extern void func_020a8c1c(void *self);
extern char data_020df258[];
extern void *func_020a8c38(void *p);
extern void func_020edb3c(Obj_t *);
extern int func_02002e04(void *arg);
extern int func_02002dc8(void *arg);
extern void func_020a8fb8(void *);
extern UnkStruct_0206dc1c *func_020a9034(u16 a, int b, int c);
extern void func_020515cc(UnkStruct_0206dc1c *a, int b, int c, u8 d, u8 e, int f, int g, u8 h, u8 i);
extern void func_02051608(UnkStruct_0206dc1c *a, int b, int c, u8 d, u8 e);

void func_0206e1d8(void *self, void *other);
void func_0206e114(SelfT *self, Arg1T *arg1, unsigned short *outArg);
void func_0206e03c(UnkStruct_0206e03c_2 *s, unsigned short *p1, int flag);
void func_0206dff8(char *obj, const void *data);
void func_0206df1c(int a, int b, int c, int d);
int func_0206de88(const unsigned short *src, int *out, int *count, int total, int min_init, int mode, int lim);
void func_0206de0c(char *p);
void func_0206ddd4(int r0);
void func_0206dd08(UnkStruct_0206dd08 *p, unsigned short val, void *arg);
void func_0206dcec(void *arg0);

void func_0206e344(int param1, int param2)
{
    func_02002ca4((void *) data_020df280, data_021fbe94, param2);
}

void func_0206e2ec(char *s, int p2)
{
    int i;

    func_0206dd08((UnkStruct_0206dd08 *) s, 0x75, (void *) p2);
    func_0206dd08((UnkStruct_0206dd08 *) (s + 0x74), 0x180, (void *) p2);

    for (i = 0; i < 4; i++) {
        func_0206dd08((UnkStruct_0206dd08 *) (s + 0xe8 + i * 0x74), (unsigned short) (i * 0x28 + 0x9d), (void *) p2);
    }

    *(int *) (s + 0x320) = 0;
}

void func_0206e2e4(char *argument0)
{
    func_0206de0c((char *) argument0);
}

void func_0206e2d0(unsigned int arg)
{
    func_0206de0c((char *) arg);
    func_0206ddd4(arg);
}

void func_0206e230(unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d, int e)
{
    int zero = 0;
    unsigned char *p = b + 0x58;

    func_0200277c(d);
    func_020029e8(d, 1);
    func_020028bc(d, zero, zero, zero);
    func_ov002_0220a448(func_02066648(b), d);
    func_0200284c(d, zero, zero);
    func_0200277c(c);
    func_020029e8(c, e);
    func_020028bc(c, zero, zero, zero);
    func_0206e1d8((void *) a, (void *) b);
    func_0206e114((SelfT *) a, (Arg1T *) b, 0);
    func_0206e03c((UnkStruct_0206e03c_2 *) a, (unsigned short *) p, 0);
    b += 0xd8;
    func_0206dff8((char *) a, (const void *) b);
    func_0206e344((int) a, (int) c);
    func_0206e2d0((unsigned int) a);
    func_0200284c(c, zero, zero);
}

unsigned int func_0206e224(void *ptr)
{
    return *(unsigned int *) ((char *) ptr + 0x320);
}

void func_0206e1d8(void *self, void *other)
{
    func_02051bf8((char *) self + 0x2b8, 0x28);
    func_02065f4c(other, (char *) self + 0x2b8);
    *(void **) ((char *) self + 0x320) = func_02051c8c_unk((char *) self + 0x2b8, 0x28);
    *(void **) ((char *) self + 0x324) = func_02051d08((char *) self + 0x2b8, 0x28);
}

void func_0206e114(SelfT *self, Arg1T *arg1, unsigned short *outArg)
{
    unsigned short out[0x28];
    unsigned char localB[0x64];
    unsigned short *o;
    int i, j;

    func_0206db74(self);

    o = outArg ? outArg : out;

    i = 0;
    j = 0;
    for (; i < arg1->unk_F8; i++, j++) {
        o[i] = arg1->arr44[j];
    }

    {
        int k;
        for (k = 0; k < self->unk_320; i++, k++) {
            o[i] = *(unsigned short *) ((char *) self + 0x2b8 + k * 2);
        }
    }

    for (; i < 0x28; i++, j++) {
        if (j < 10) {
            o[i] = arg1->arr44[j];
        } else {
            unsigned short zero = 0;
            o[i] = zero;
        }
    }

    if (self->unk_320 > 0) {
        func_0206db50(self, arg1->unk_F8, (unsigned char) self->unk_320);
    }

    func_020a88ec(&localB[0]);
    *(void **) &localB[0] = ((int *) data_020df270);
    func_020a8874(&localB[0], o, 0x28);
    func_0206dbc0(self, &localB[0]);
    *(void **) &localB[0] = ((int *) data_020df270);
    func_020a887c(&localB[0]);
}

void func_0206e03c(UnkStruct_0206e03c_2 *s, unsigned short *p1, int flag)
{
    unsigned char obj[0x60];
    unsigned short buf[42];
    int i;
    int len;
    UnkStruct_0206e03c *e;
    int zero;

    func_0206df1c((int) s, (int) p1, (int) s->unk_308, (int) (&s->unk_31C));
    func_020a88ec(obj);
    *(void **) obj = ((void * *) data_020df270);
    buf[0] = 0;
    zero = 0;
    for (i = 0; i < 4; i++) {
        len = s->unk_308[i + 1] - s->unk_308[i];
        e = &s->arr[i];
        func_0206db74((void *) e);
        if (len != 0) {
            func_020a8874(obj, (unsigned short *) (p1 + s->unk_308[i]), len);
            if (flag != 0) {
                int m;
                if (i == s->unk_31C) {
                    m = 1;
                } else {
                    m = zero;
                }
                func_0206dba8(e, obj, m);
            } else {
                func_0206dbc0((SelfT *) e, obj);
            }
        } else {
            if (flag != 0 && i == s->unk_31C) {
                func_020a8874(obj, (unsigned short *) buf, 1);
                func_0206dba8(e, obj, 1);
            } else {
                func_0206db74((void *) e);
            }
        }
    }
    *(void **) obj = ((void * *) data_020df270);
    func_020a887c(obj);
}

void func_0206dff8(char *obj, const void *data)
{
    Buffer buf;
    func_020a88ec(&buf);
    buf.unk_00 = data_020df270;
    func_0206db74((char *) obj + 0x74);
    func_020a8874(&buf, (unsigned short *) data, 0x10);
    obj = (char *) obj + 0x74;
    func_0206dbc0((SelfT *) obj, &buf);
    buf.unk_00 = data_020df270;
    func_020a887c(&buf);
}

void func_0206dfe0(void *p, int a, int b, int c)
{
    func_0206db5c(p, a, b, c);
}

void func_0206df58(void *a, unsigned int b, unsigned int c, int d)
{
    int i;
    int j;
    unsigned int s;
    int t;
    int delta;

    j = 0;
    i = j;
    while (i < 4) {
        delta = *(int *) ((char *) a + (i + 1) * 4 + 0x308) - *(int *) ((char *) a + i * 4 + 0x308);
        if (delta == 0) {
            break;
        }
        if (b >= j && b < (t = j + delta)) {
            if (t > b + c) {
                s = c;
            } else {
                s = delta - (b - j);
            }
            func_0206db5c((void *) ((char *) a + 0xe8 + i * 0x74), (u8) (b - j), (u8) s, d);
            b = (u8) t;
            c -= s;
            if (c == 0) {
                break;
            }
        }
        j += delta;
        i++;
    }
}

void func_0206df40(char *p, int a, int b, int c)
{
    func_0206db5c(p + 0x74, a, b, c);
}

void func_0206df1c(int a, int b, int c, int d)
{
    func_0206de88((const unsigned short *) b, (int *) c, (int *) d, 0x40, 40, 160, 4);
}

int func_0206de88(const unsigned short *src, int *out, int *count, int total, int min_init, int mode, int lim)
{
    int acc, i, min, tmp, ret;

    acc = 0;
    min = min_init;
    *count = 0;
    i = acc;

    while (i < lim) {
        if (min > total - acc) {
            min = total - acc;
        }
        ret = func_02051c14(src + acc, min, mode, &tmp, 1);
        out[i] = acc;
        acc += tmp;
        if (ret != 0) {
            if (ret == 3 && i == lim - 1) {
                out[i + 1] = acc;
                return 0;
            }
            (*count)++;
        }
        i++;
    }

    out[i] = acc;
    if (acc == total) {
        goto ret1;
    }
    if (src[acc] != 0) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

unsigned int func_0206de7c(unsigned int r0)
{
    return r0 + 0x308;
}

unsigned int func_0206de70(unsigned int *param0)
{
    return param0[0x31c / 4];
}

int func_0206de38(UnkStruct_0206de38 *self, int value)
{
    int i = 0;
    int n = self->count;
    while (i < n) {
        if (value < self->arr[i + 1]) {
            return i;
        }
        i++;
    }
    if (n < 4) {
        return n;
    }
    return 3;
}

void func_0206de0c(char *p)
{
    int i;
    func_0206dcec((void *) p);
    func_0206dcec((void *) (p + 0x74));
    p += 0xe8;
    for (i = 0; i < 4; i++) {
        func_0206dcec((void *) (p + i * 0x74));
    }
}

void func_0206ddd4(int r0)
{
    int r4;
    int r5;
    int r6;
    int r7;

    r5 = r0;
    func_0206dbd8(r5, 0);
    func_0206dbd8(r5 + 0x74, 1);
    r4 = 0;
    r5 += 0xe8;
    r6 = r4;
    r7 = 0x74;
    do {
        func_0206dbd8(r5 + r4 * r7, r6);
        r4++;
    } while (r4 < 4);
}

int func_0206ddd0(void)
{
    return 40;
}

int func_0206ddcc(int p0)
{
    return ((int) (p0) + (14));
}

UnkStruct_0206dd8c *func_0206dd8c(UnkStruct_0206dd8c *self)
{
    func_020a8cac(self);
    self->unk_00 = ((char *) data_020df258);
    func_020a8c1c(self);
    self->unk_64 = 0;
    self->unk_68 = 0;
    self->unk_6D = 0;
    self->unk_6E = 0;
    self->unk_70 = 0;
    self->unk_71 = 0;
    return self;
}

void *func_0206dd6c(void *p)
{
    *(void **) p = (void *) data_020df258;
    func_0206dcec(p);
    func_020a8c38(p);
    return p;
}

Obj_t *func_0206dd48(Obj_t *obj)
{
    obj->unk_00 = ((char *) data_020df258);
    func_0206dcec((void *) obj);
    func_020a8c38((void *) obj);
    func_020edb3c(obj);
    return obj;
}

int func_0206dd44(void)
{
    return 82;
}

void func_0206dd08(UnkStruct_0206dd08 *p, unsigned short val, void *arg)
{
    p->unk_68 = val;
    p->unk_6C = 0;
    p->unk_6B = !func_02002e04(arg);
    p->unk_6A = func_02002dc8(arg);
}

int func_0206dd04(int p0)
{
    return ((int) (p0) + (18));
}

void func_0206dcec(void *arg0)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg0 + 0x64))) != 0) {
        func_020a8fb8(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x64) = 0;
    }
}

void func_0206dc1c(UnkStruct_0206dc1c_2 *self)
{
    int arg1;
    int arg2;
    u8 f6e_val;

    if (self->unk_64 != 0) {
        return;
    }

    self->unk_64 = func_020a9034(self->unk_68, 20, 2);
    if (self->unk_64 == 0) {
        return;
    }

    self->unk_64->unk_2C = self->unk_6A;

    if (self->unk_6B != 0) {
        self->unk_64->unk_50 = 1;
    } else {
        self->unk_64->unk_50 = 2;
    }

    self->unk_64->unk_55 = 0;
    self->unk_64->unk_39 = 0;
    self->unk_64->unk_38 = 0xf;

    if (self->unk_6F != 0) {
        arg1 = 0xb;
        arg2 = 0;
    } else {
        arg1 = 0xe;
        arg2 = 0xd;
    }

    f6e_val = self->unk_6E;
    if (f6e_val != 0) {
        if (self->unk_71 != 0) {
            func_020515cc(self->unk_64, arg1, arg2, self->unk_6D, f6e_val, 12, 0, self->unk_70, self->unk_71);
        } else {
            func_02051608(self->unk_64, arg1, arg2, self->unk_6D, f6e_val);
        }
    } else {
        if (self->unk_71 != 0) {
            func_02051608(self->unk_64, 12, 0, self->unk_70, self->unk_71);
        }
    }
}
