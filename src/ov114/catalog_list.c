/* catalog_list: 24 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229cde4 @ 0x0229cde4, 0x34 bytes, Thumb
 * func_ov114_0229cdcc @ 0x0229cdcc, 0x18 bytes, Thumb
 * func_ov114_0229cda0 @ 0x0229cda0, 0x2c bytes, Thumb
 * func_ov114_0229cd70 @ 0x0229cd70, 0x30 bytes, Thumb
 * func_ov114_0229ccc0 @ 0x0229ccc0, 0xb0 bytes, Thumb
 * func_ov114_0229cbe4 @ 0x0229cbe4, 0xdc bytes, Thumb
 * func_ov114_0229cb7c @ 0x0229cb7c, 0x68 bytes, Thumb
 * func_ov114_0229cadc @ 0x0229cadc, 0xa0 bytes, Thumb
 * func_ov114_0229ca50 @ 0x0229ca50, 0x8c bytes, Thumb
 * func_ov114_0229c9dc @ 0x0229c9dc, 0x74 bytes, Thumb
 * func_ov114_0229c924 @ 0x0229c924, 0xb8 bytes, Thumb
 * func_ov114_0229c8dc @ 0x0229c8dc, 0x48 bytes, Thumb
 * func_ov114_0229c8b4 @ 0x0229c8b4, 0x28 bytes, Thumb
 * func_ov114_0229c890 @ 0x0229c890, 0x24 bytes, Thumb
 * func_ov114_0229c7d0 @ 0x0229c7d0, 0xc0 bytes, Thumb
 * func_ov114_0229c720 @ 0x0229c720, 0xb0 bytes, Thumb
 * func_ov114_0229c6f8 @ 0x0229c6f8, 0x28 bytes, Thumb
 * func_ov114_0229c690 @ 0x0229c690, 0x68 bytes, Thumb
 * func_ov114_0229c628 @ 0x0229c628, 0x68 bytes, Thumb
 * func_ov114_0229c60c @ 0x0229c60c, 0x1c bytes, Thumb
 * func_ov114_0229c5f4 @ 0x0229c5f4, 0x18 bytes, Thumb
 * func_ov114_0229c410 @ 0x0229c410, 0x1e4 bytes, Thumb
 * func_ov114_0229c3ac @ 0x0229c3ac, 0x64 bytes, Thumb
 * func_ov114_0229c370 @ 0x0229c370, 0x3c bytes, Thumb
 */

#include "types.h"

struct Elem {
    char data[0x6c];
};

struct UnkStruct_0229cda0 {
    char pad_00[0x106c];
    struct Elem arr[4];
    char pad_121C[0x9a];
    unsigned char flag;
};

typedef struct UnkStruct_0229cbe4 {
    char pad_00[0x1000];
    struct {
        char data[12];
    } arr[9];
    char pad_106C[0x218];
    int unk_1284;
    int unk_1288;
    int unk_128C;
    int unk_1290;
    char pad_1294[0x25];
    u8 unk_12B9;
} UnkStruct_0229cbe4;

typedef struct {
    char pad_00[0x127c];
    int unk_127C;
    char pad_1280[4];
    int unk_1284;
    char pad_1288[4];
    int unk_128C;
    char pad_1290[8];
    int unk_1298;
} UnkStruct_0229cb7c;

typedef struct UnkStruct_0229cadc UnkStruct_0229cadc;

struct UnkStruct_0229cadc {
    u8 unk_00[0x128c];
    int unk_128C;
    int unk_1290;
    u8 p1[0x12b7 - 0x1294];
    u8 unk_12B7;
};

struct UnkStruct_0229ca50 {
    char pad_00[0x127c];
    int unk_127C;
    char pad_1280[0x14];
    int unk_1294;
    char pad_1298[0x21];
    unsigned char unk_12B9;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    int unk_08;
} UnkStruct_0229c9dc;

typedef struct {
    char pad_00[0x1000];
    UnkStruct_0229c9dc arr[9];
    char pad_106C[0x21C];
    int unk_1288;
} BigStruct;

typedef struct {
    unsigned char pad_00[0x12a4];
    unsigned int unk_12A4;
    unsigned int unk_12A8;
    unsigned char pad_12AC[0x0d];
    unsigned char unk_12B9;
    unsigned char unk_12BA;
} UnkStruct_0229c8dc;

struct UnkStruct_0229c890 {
    unsigned char pad_00[0x12b8];
    unsigned char unk_12B8;
    unsigned char unk_12B9;
};

typedef struct {
    unsigned char pad_00[0x1280];
    int unk_1280;
    unsigned char pad_1284[0x1294 - 0x1284];
    int unk_1294;
    unsigned char pad_1298[0x12bc - 0x1298];
    unsigned char st;
    unsigned char unk_12BD;
} UnkStruct_0229c410;

struct UnkStruct_0229c3ac {
    unsigned char pad_00[0x128c];
    int word_field;
    unsigned char pad_1290[0x2c];
    unsigned char byte_field;
};

typedef struct {
    unsigned char pad_00[0x127c];
    int unk_127C;
    unsigned char pad_1280[0x1294 - 0x127c - 4];
    int unk_1294;
} UnkNisB;

extern void func_020b9ccc(void *ptr);
extern void func_02070b84(struct Elem *);
extern void *func_02062fbc(void *);
extern void func_020a8c1c(void *);
extern int func_02062ea4(void *, void *);
extern void *func_02062f4c(void *);
extern void *func_020a8bb8(int, void *);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern int func_ov114_0229c1b8(UnkStruct_0229cbe4 *self, int value);
extern int func_020896b8(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern const unsigned char data_ov114_0229dac0[8];
extern int data_ov114_0229dae0;
extern int data_ov114_0229dad8;
struct UnkStruct_0229ca50;
extern void func_0200467c(int cmd);
extern u64 _s32_div_f(int, int);
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern int func_02088d94(const void *arg);
extern const char data_ov114_0229db20[];
extern u32 func_0204c6b8(u32);
extern u8 *func_ov094_0229b088(u8 *, u32);
extern int func_020b9a18(void *, void *, void *, int, u32, u32, u32, u32);
extern u32 func_ov094_0229b03c(u8 *, u32);
extern void func_ov114_0229ce18(void *, int, int);
extern void func_02001a04(unsigned int, unsigned int, int);
extern void func_020019f4(void);
extern void func_ov114_0229d088(void *);
extern int func_02064328(void *, void *, void *, int, int, int);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern int func_02002cd8(void *, void *, int, int, int);
extern u8 data_ov114_0229db68[];
extern u8 data_ov114_0229db78[];
extern u8 data_ov114_0229db88[];
extern u8 data_ov114_0229db9c[];
extern void *data_021fbe94;
extern void *data_ov114_0229dce0;
extern u8 data_ov114_0229dce8[];
extern void func_02002708(unsigned char);
extern void func_0200277c(unsigned char);
extern int func_ov090_022990b8(int value);
extern int func_ov002_0220a4f8(void *ptr);
extern int data_ov114_0229da94[];
extern int func_ov002_0220a4d4(void *p);
extern int data_ov114_0229daa4[];
extern const unsigned char data_ov114_0229da8c[];
extern const unsigned char data_ov114_0229da90[];
extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);

void func_ov114_0229c924(u8 *self, u32 arg1, int idx);
void func_ov114_0229c890(struct UnkStruct_0229c890 *p);
void func_ov114_0229c7d0(void *self);
void func_ov114_0229c6f8(unsigned char *obj, unsigned char val);
int func_ov114_0229c60c(unsigned char *p);
unsigned char func_ov114_0229c370(UnkNisB *self);

void func_ov114_0229cde4(void *arg)
{
    int i;
    for (i = 0; i < 9; i++) {
        func_020b9ccc((char *) arg + 0x0e08 + i * 0x38);
    }
    ((char *) arg)[0x12b4] = 0;
}

unsigned char func_ov114_0229cdcc(unsigned char *p)
{
    unsigned char v = p[0x12b4];
    if (v >= 9) {
        return 8;
    } else {
        p[0x12b4] = v + 1;
        return v;
    }
}

void func_ov114_0229cda0(struct UnkStruct_0229cda0 *self)
{
    int i = 0;
    self->flag = 0;
    for (; i < 4; i++) {
        func_02070b84(&self->arr[i]);
    }
}

unsigned char *func_ov114_0229cd70(unsigned char *p)
{
    if (p[0x12b6] >= 4) {
        return p + 0x11b0;
    }
    p[0x12b6]++;
    return p + 0x106c + (p[0x12b6] - 1) * 0x6c;
}

void func_ov114_0229ccc0(unsigned char *self, unsigned short param)
{
    unsigned short val;
    unsigned short v;
    unsigned int obj[0xb];
    int b;
    int x;

    func_02062fbc(obj);
    if (param == 0xff) {
        func_020a8c1c(obj);
    } else {
        b = self[0x12b7];
        switch (b) {
            case 0:
                if (param < 0x38) {
                    v = (unsigned short) (param + 0x12e8);
                } else {
                    v = 0x12e8;
                }
                break;
            case 1:
                if (param < 0x38) {
                    v = (unsigned short) (param + 0x12b0);
                } else {
                    v = 0x12b0;
                }
                break;
            default:
                func_02062f4c(obj);
                return;
        }
        val = v;
        func_02062ea4(obj, &val);
    }

    x = (int) func_ov114_0229cd70((unsigned char *) self);
    func_020a8bb8(x, obj);
    func_02070adc(x, self[0x12b1], 0xa1, 0x0d, 1, 3, 0);
    func_02070a04(x, 1, 0);
    func_02062f4c(obj);
}

void func_ov114_0229cbe4(UnkStruct_0229cbe4 *self, int arg1)
{
    int p6 = self->unk_1284;
    int vc = self->unk_1288 + arg1;
    int v10 = self->unk_1290;
    int i = 0;
    int neg_one = ~i;
    int v18, v1c, v20, reset;

    v1c = 0;
    v18 = 0;
    reset = 0;
    v20 = 0;

    do {
        int addr, v14;

        if (func_ov114_0229c1b8(self, self->unk_128C + i) != 0) {
            addr = (int) &self->arr[v10];
            v14 = neg_one;
        } else {
            addr = (int) ((int *) data_ov114_0229dac0);
            v14 = 4;
        }

        func_020896b8(1, addr, p6, vc, neg_one, 2, v18);

        if (self->unk_12B9 == (self->unk_128C + i)) {
            func_020896b8(1, (int) &data_ov114_0229dae0, p6, vc, neg_one, 2, v1c);
        }

        func_020896b8(1, (int) &data_ov114_0229dad8, p6, vc, v14, 2, v20);

        p6 += 0x1b;
        v10++;
        if (v10 >= 9) {
            v10 = reset;
        }
        i++;
    } while (i < 9);
}

int func_ov114_0229cb7c(UnkStruct_0229cb7c *self, int value)
{
    int clamped;
    int counter;
    clamped = value;
    if (clamped < 0) {
        clamped = 0;
    }
    if (clamped >= self->unk_1298) {
        clamped = self->unk_1298;
    }
    self->unk_127C = clamped;
    counter = self->unk_128C;
    self->unk_1284 = 0x22 - clamped;
    self->unk_128C = 0;
    while (self->unk_1284 < 8) {
        self->unk_1284 += 0x1b;
        self->unk_128C++;
    }
    return (counter == self->unk_128C) ? 0 : 1;
}

void func_ov114_0229cadc(UnkStruct_0229cadc *self)
{
    u16 h;
    int n;
    unsigned int k;
    int j;

    self->unk_1290 = self->unk_128C % 9;
    k = self->unk_128C;
    j = self->unk_1290;
    h = 0xfff1;
    for (n = 0; n < 9; n++) {
        switch (self->unk_12B7) {
            case 0:
                h = (k < 0x38) ? (u16) (k + 0x12e8) : 0x12e8;
                break;
            case 1:
                h = (k < 0x38) ? (u16) (k + 0x12b0) : 0x12b0;
                break;
            default:
                return;
        }
        func_ov114_0229c924((u8 *) self, (u32) (&h), j);
        j = j + 1;
        if (j >= 9) {
            j = 0;
        }
        k = k + 1;
        if (k >= 0x38) {
            return;
        }
    }
}

int func_ov114_0229ca50(struct UnkStruct_0229ca50 *a, int b, int c)
{
    int v;
    int limit;
    int x;
    int r4;

    if (c < 0x90 || c >= 0xb0) {
        return 0;
    }
    if (b < 0x10 || b >= 0xf0) {
        return 0;
    }
    if (b < 0x18) {
        b = 0x18;
    }
    if (b > 0xe8) {
        b = 0xe8;
    }

    v = a->unk_127C;
    x = b - (0x15 - v);
    if (x < 0) {
        x = 0;
    }

    r4 = (int) _s32_div_f(x, 0x1b);

    limit = a->unk_1294;
    if (r4 >= limit) {
        r4 = limit - 1;
    }

    if (func_ov114_0229c1b8((UnkStruct_0229cbe4 *) a, r4) != 0) {
        if (a->unk_12B9 != r4) {
            func_0200467c(0x29);
        }
        func_ov114_0229c6f8((unsigned char *) a, (unsigned char) r4);
        return 1;
    }
    return 0;
}

void func_ov114_0229c9dc(BigStruct *base)
{
    int i = 0;
    UnkStruct_0229c9dc *arr = base->arr;
    int neg = ~i;
    do {
        UnkStruct_0229c9dc *elem = &arr[i];
        MI_CpuCopy8(data_ov114_0229dac0, elem, 8);
        elem->unk_04 = (elem->unk_04 & 0xfffffc00u) | (((i << 1) + 0xc0) & 0x3ffu);
        elem->unk_08 = neg;
        i++;
    } while (i < 9);
    base->unk_1288 = func_02088d94(data_ov114_0229db20) + 0x70;
    func_ov114_0229cb7c((UnkStruct_0229cb7c *) base, 0);
}

void func_ov114_0229c924(u8 *self, u32 arg1, int idx)
{
    struct {
        u32 unk0;
        unsigned int v : 10;
        unsigned int pad10_11 : 2;
        unsigned int code : 4;
        unsigned int pad16_31 : 16;
        u32 field8;
    } *e = (void *) (self + 0x1000 + idx * 0xc);
    u32 id = func_0204c6b8(arg1);

    if (id != e->field8) {
        u32 v;
        u8 *src;
        int slot;
        u8 *destA;
        u8 *destB;
        u32 args[4];

        e->field8 = id;
        v = e->v;
        src = func_ov094_0229b088(self, id);
        slot = (int) func_ov114_0229cdcc((unsigned char *) self);
        destA = self + 0x988 + (slot << 7);
        destB = destA + 0x40;
        MI_CpuCopy8(src, destA, (unsigned int) 0x40);
        MI_CpuCopy8(src + 0x400, destB, (unsigned int) 0x40);
        args[0] = v;
        args[1] = v + 1;
        args[2] = v + 0x20;
        args[3] = v + 0x21;
        func_020b9a18(self + 0xe08 + slot * 0x38, destA, destB, 8, args[0], args[1], args[2], args[3]);
        e->code = func_ov094_0229b03c(self, id);
    }
}

void func_ov114_0229c8dc(UnkStruct_0229c8dc *self)
{
    self->unk_12B9 = 0xff;
    self->unk_12BA = 0;
    func_ov114_0229ccc0((unsigned char *) self, 0xff);
    func_ov114_0229c890((struct UnkStruct_0229c890 *) self);
    func_ov114_0229ce18(self, 0, 0x10);
    func_02001a04(self->unk_12A8, self->unk_12A4, 0);
}

void func_ov114_0229c8b4(unsigned char *p)
{
    unsigned char v = p[0x12b8];
    p[0x12b9] = v;
    func_020019f4();
    p[0x12ba] = 0x10;
}

void func_ov114_0229c890(struct UnkStruct_0229c890 *p)
{
    p->unk_12B8 = p->unk_12B9;
    func_ov114_0229c7d0(p);
    func_ov114_0229d088(p);
}

void func_ov114_0229c7d0(void *self)
{
    unsigned char *s = (unsigned char *) self;
    u8 val = s[0x12b8];
    u8 sw;
    u64 res1, res2;
    u32 low;
    u8 rem;
    void *ptr;

    if (val == 0xff) {
        return;
    }

    res1 = _s32_div_f(val, 12);
    low = (u32) res1;
    ptr = data_021fbe94;

    sw = s[0x12b7];
    switch (sw) {
        case 0:
            data_ov114_0229dce0 = data_ov114_0229db68;
            break;
        case 1:
            data_ov114_0229dce0 = data_ov114_0229db78;
            break;
        default:
            return;
    }

    func_02064328(data_ov114_0229dce8, data_ov114_0229db88, data_ov114_0229dce0, low, low, val);
    func_02002c6c(data_ov114_0229dce8, ptr, s[0x12b3], 0x11, 0x11, 0xa0);
    func_02064328(data_ov114_0229dce8, data_ov114_0229db9c, data_ov114_0229dce0, low, low, val);

    res2 = _s32_div_f(val, 12);
    rem = (u8) ((u32) (res2 >> 32));
    func_02002cd8(data_ov114_0229dce8, ptr, s[0x12b3], rem, 5);
}

void func_ov114_0229c720(unsigned char *obj)
{
    unsigned char v = obj[0x12ba];
    unsigned char x = obj[0x12b8];
    unsigned char y = obj[0x12b9];

    if (x == y) {
        if (x != 0xff && v != 0x10) {
            if (v < 0xc) {
                if (v == 0) {
                    func_02002708(obj[0x12b3]);
                }
                obj[0x12ba] += 4;
                func_02001a04(*(unsigned int *) (obj + 0x12a8), *(unsigned int *) (obj + 0x12a4), obj[0x12ba]);
            } else {
                func_020019f4();
            }
        }
    } else {
        if (v == 0) {
            func_ov114_0229c890((struct UnkStruct_0229c890 *) obj);
        } else if (v > 4) {
            obj[0x12ba] = v - 4;
            func_02001a04(*(unsigned int *) (obj + 0x12a8), *(unsigned int *) (obj + 0x12a4), obj[0x12ba]);
        } else {
            obj[0x12ba] = 0;
            func_0200277c(obj[0x12b3]);
        }
    }

    if (v != obj[0x12ba]) {
        func_ov114_0229ce18((void *) obj, obj[0x12ba], 0x10);
    }
}

void func_ov114_0229c6f8(unsigned char *obj, unsigned char val)
{
    obj[0x12b9] = val;
    if (obj[0x12b9] != obj[0x12b8]) {
        func_ov114_0229ccc0(obj, (unsigned short) val);
    }
}

int func_ov114_0229c690(void *arg)
{
    if (func_ov114_0229c60c((unsigned char *) arg) != -1) {
        return func_ov090_022990b8(((unsigned char *) arg)[0x12bc] - 5);
    } else {
        unsigned char b = ((unsigned char *) arg)[0x12bc];
        if (b == 4) {
            return func_ov002_0220a4f8((char *) arg + 0x121c);
        } else if (b < 4) {
            return data_ov114_0229da94[b];
        } else {
            return 27 * (b - 13) + 34 - *(int *) ((char *) arg + 0x127c) - *(int *) ((char *) arg + 0x1280);
        }
    }
}

int func_ov114_0229c628(void *p)
{
    if (func_ov114_0229c60c((unsigned char *) p) != -1) {
        return 8;
    }
    {
        unsigned char type = ((unsigned char *) p)[0x12bc];
        if (type == 4) {
            return func_ov002_0220a4d4((char *) p + 0x121c);
        }
        if (type < 4) {
            int val = data_ov114_0229daa4[type];
            if (type == 2 && ((unsigned char *) p)[0x12bb] == 0) {
                return val + 2;
            }
            if (type == 3 && ((unsigned char *) p)[0x12bb] == 1) {
                return val + 2;
            }
            return val;
        } else {
            return 0x9e;
        }
    }
}

int func_ov114_0229c60c(unsigned char *p)
{
    unsigned char v = p[0x12bc];
    if (v >= 5 && v <= 12) {
        return v - 5;
    } else {
        return -1;
    }
}

int func_ov114_0229c5f4(unsigned char *p)
{
    int result = 1;
    if (p[0x12bc] != 0 && p[0x12bc] != 1) {
        result = 0;
    }
    return result;
}

int func_ov114_0229c410(UnkStruct_0229c410 *o, void *in)
{
    unsigned int st;
    unsigned int st2;
    int n;
    int v;

    if (in == 0) {
        return 0;
    }
    st = o->st;
    if (func_ov114_0229c60c((unsigned char *) o) != -1) {
        if (func_ov002_022088bc(in) != 0) {
            o->st = 0;
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->st > 5) {
                o->st = o->st - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 0xc) {
                o->st = o->st + 1;
            }
        }
    } else {
        st2 = o->st;
        if (st2 <= 1) {
            if (func_ov002_022088cc(in) != 0) {
                o->st = o->unk_12BD;
            } else if (func_ov002_022088bc(in) != 0) {
                o->st = (int) func_ov114_0229c370((UnkNisB *) o);
            } else if (func_ov002_022088ac(in) != 0) {
                o->st = 1;
            } else if (func_ov002_0220889c(in) != 0) {
                o->st = 0;
            }
        } else if (st2 >= 0xd) {
            n = st2 - 0xd;
            if (func_ov002_022088cc(in) != 0) {
                if (func_ov114_0229c690((void *) o) < 0x48) {
                    o->st = 1;
                } else {
                    o->st = 0;
                }
            } else if (func_ov002_022088bc(in) != 0) {
                v = func_ov114_0229c690((void *) o);
                if (v < 0x40) {
                    o->st = 2;
                } else if (v >= 0xc0) {
                    o->st = 3;
                } else {
                    o->st = 4;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                if (n < o->unk_1294 - 1) {
                    o->st = o->st + 1;
                    v = func_ov114_0229c690((void *) o);
                    if (v > 0xe0) {
                        o->unk_1280 = v - 0xe0;
                    }
                }
            } else if (func_ov002_022088ac(in) != 0) {
                if (n > 0) {
                    o->st = o->st - 1;
                    v = func_ov114_0229c690((void *) o);
                    if (v < 0x20) {
                        o->unk_1280 = v - 0x20;
                    }
                }
            }
        } else {
            n = st2 - 2;
            if (func_ov002_022088cc(in) != 0) {
                o->st = (int) func_ov114_0229c370((UnkNisB *) o);
            } else if (func_ov002_022088ac(in) != 0) {
                o->st = data_ov114_0229da90[n];
            } else if (func_ov002_0220889c(in) != 0) {
                o->st = data_ov114_0229da8c[n];
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}

void func_ov114_0229c3ac(struct UnkStruct_0229c3ac *p)
{
    int r;
    if (p->byte_field < 0x0d) {
        return;
    }
    r = func_ov114_0229c690((void *) p);
    if (r < 0x20) {
        p->byte_field = (unsigned char) (p->word_field + 0x0d);
        r = func_ov114_0229c690((void *) p);
        if (r < 0x20) {
            p->byte_field = p->byte_field + 1;
        }
    } else if (r > 0xe0) {
        p->byte_field = (unsigned char) (p->word_field + 0x14);
        r = func_ov114_0229c690((void *) p);
        if (r > 0xe0) {
            p->byte_field = p->byte_field - 1;
        }
    }
}

unsigned char func_ov114_0229c370(UnkNisB *self)
{
    int ret = func_ov114_0229c690((void *) self);
    ret = ret - (21 - self->unk_127C);
    if (ret < 0) {
        ret = 0;
    }
    ret = (int) _s32_div_f(ret, 27);
    if (ret >= self->unk_1294) {
        ret = self->unk_1294 - 1;
    }
    return (unsigned char) (ret + 13);
}
