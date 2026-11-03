/* friend_roster_page_2: 9 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229aacc @ 0x0229aacc, 0x170 bytes, Thumb
 * func_ov119_0229aa18 @ 0x0229aa18, 0xb4 bytes, Thumb
 * func_ov119_0229a968 @ 0x0229a968, 0xb0 bytes, Thumb
 * func_ov119_0229a8ec @ 0x0229a8ec, 0x7c bytes, Thumb
 * func_ov119_0229a764 @ 0x0229a764, 0x188 bytes, Thumb
 * func_ov119_0229a714 @ 0x0229a714, 0x50 bytes, Thumb
 * func_ov119_0229a69c @ 0x0229a69c, 0x78 bytes, Thumb
 * func_ov119_0229a650 @ 0x0229a650, 0x4a bytes, Thumb
 * func_ov119_0229a5d8 @ 0x0229a5d8, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229aacc UnkStruct_0229aacc;

struct UnkStruct_0229aacc {
    unsigned char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_0229a714 {
    unsigned char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char pad_9D[0x12];
    unsigned char unk_AF;
    unsigned char pad_B0[2];
    unsigned char unk_B2;
    unsigned char unk_B3;
};

typedef struct {
    unsigned char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char unk_9D;
    unsigned char pad_9E[0xe0c - 0x9e];
    unsigned char sub_a[0x160c - 0xe0c];
    unsigned char sub_b[0x1e0c - 0x160c];
    void *unk_1E0C;
} UnkStruct_0229a69c;

extern UnkStruct_0229aacc *data_020ccf94;
extern void *func_020641c8(void *);
extern void *func_020641b0(void *);
extern void func_02064210(int, void *);
extern void *func_02094fd4(void *);
extern void *func_02094fbc(void *);
extern int func_02095040(void *object);
extern void *func_02095074(int, void *);
extern void *func_ov119_0229bb44(void *);
extern int func_02073d90(UnkStruct_0229aacc *);
extern void *func_020984fc(int);
extern int func_02099870(void *);
extern void *func_020b496c(int, void *);
extern int func_0207094c(void *, int);
extern void *func_020a8bb8(void *, void *);
extern void func_020a8c1c(void *);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void *func_020984e8(void);
extern void *func_02099664(void *);
extern int func_02077bd8(void *);
extern int func_02077bd0(void *);
extern int func_020b4980(void *, unsigned char *, int);
extern int func_020a7bf4(void *, int);
extern int func_020a8a34(void *, int);
extern const unsigned char data_021f43ec;
extern void *func_02064170(void *);
extern void *func_02064158(void *);
extern void *func_ov119_0229ae50(void *receiver);
extern void *func_02077c3c(void *object);
extern int func_02077e50(void *friend_data);
extern int func_02077c34(void *);
extern int func_02077c38(void *);
extern int func_02077d6c(void *friend_data);
extern void func_020a8874(void *, int, int);
extern int func_020a8a70(void *, void *, int, int);
extern void func_020708e4(void *, int, int);
extern void func_ov119_0229a46c(void *);
extern void func_ov119_0229a410(void *, int);
extern void func_ov119_0229bacc(void *self, int kind);
extern unsigned long long func_02077be0(void *);

void func_ov119_0229a8ec(int unused, unsigned short *p, unsigned short val);

void func_ov119_0229aacc(unsigned char *self)
{
    int i;
    int n;
    int incA, incB;
    int j;
    UnkStruct_0229aacc *g;
    void *entry;
    int limit;
    void *objA, *objB;
    int tmp;
    int buf1[8];
    int buf2[8];

    incA = 0x1ce;
    incB = 0x14e;
    j = 0xc3;
    g = data_020ccf94;
    limit = g->unk_64;
    n = 0;
    func_020641c8(buf1);
    func_02094fd4(buf2);

    for (i = 0; i < 8; i++) {
        objA = func_ov119_0229bb44(self);
        objB = func_ov119_0229bb44(self);
        entry = 0;
        if (func_02073d90(g) != 0) {
            if (limit == n) {
                n++;
            }
            if (n < 4) {
                entry = func_020984fc(n);
                n++;
            }
        }
        if (entry != 0) {
            tmp = func_02099870(entry);
            func_02064210(func_02095040((void *) tmp), buf1);
            func_020b496c(0, buf1);
            func_0207094c(objA, 0x66);
            func_02095074(tmp, buf2);
            func_020a8bb8(objB, buf2);
            func_ov119_0229a8ec((int) self, (unsigned short *) ((unsigned short *) (self + 0xe0c) + j), 0x58);
            self[0xb2] |= 1 << i;
        } else {
            func_020a8c1c(objA);
            func_020a8c1c(objB);
            func_ov119_0229a8ec((int) self, (unsigned short *) ((unsigned short *) (self + 0xe0c) + j), 0x10);
        }

        func_02070adc(objA, 4, incA, 0xa, 0xf, 0, 0);
        func_02070a04(objA, 0, 0);
        func_02070adc(objB, 4, incB, 8, 0xf, 0, 0);
        func_02070a04(objB, 0, 0);

        incA += 0x14;
        incB += 0x10;
        j += 0x40;
    }

    func_0206fdd4(self + 0xe0c, 5, 6, 0x17, 0x15, 5);
    func_02094fbc(buf2);
    func_020641b0(buf1);
}

void func_ov119_0229aa18(u32 p)
{
    u32 loc0[8];
    u32 loc1[8];
    u32 b;
    u32 a;

    b = (u32) func_02099870((void *) ((int) (int) func_020984e8()));
    a = (u32) func_ov119_0229bb44((void *) p);
    func_020641c8(loc0);
    func_02064210((u32) func_02095040((void *) b), loc0);
    func_020b496c(0, loc0);
    func_0207094c((void *) a, 0x66);
    func_02070adc((void *) a, 4, 0x102, 0xa, 0xf, 0, 0);
    func_02070a04((void *) a, 0, 0);

    a = (u32) func_ov119_0229bb44((void *) p);
    func_02094fd4(loc1);
    func_02095074(b, loc1);
    func_020a8bb8((void *) a, loc1);
    func_02070adc((void *) a, 4, 0x116, 8, 0xf, 0, 0);
    func_02070a04((void *) a, 0, 0);

    func_02094fbc(loc1);
    func_020641b0(loc0);
}

void func_ov119_0229a968(void *obj)
{
    int z1, z2;
    unsigned char b;
    void *h, *p;
    int i;

    b = data_021f43ec;
    h = func_020984e8();
    if (func_02077bd8(func_02099664(h)) == 0) {
        b = 0xd4;
    } else if (func_02077bd0(func_02099664(h)) == 0) {
        b = 0xec;
    } else {
        b = 0xd5;
    }
    func_020b4980((char *) obj + 0xcd4, &b, 0);
    z1 = 0;
    z2 = 0;
    for (i = 0; i < 3; i++) {
        p = func_ov119_0229bb44(obj);
        func_020a8a34(p, func_020a7bf4((char *) obj + 0xce6, i));
        func_02070adc(p, 4, i * 0x28 + 0x8a, 0x14, 0xf, z1, z1);
        func_02070a04(p, z2, z2);
    }
}

void func_ov119_0229a8ec(int unused, unsigned short *p, unsigned short val)
{
    *p &= 0xfffffc00;
    *p |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *(p + 1) &= 0xfffffc00;
    *(p + 1) |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *((unsigned short *) ((char *) p + 0x40)) &= 0xfffffc00;
    *((unsigned short *) ((char *) p + 0x40)) |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *((unsigned short *) ((char *) p + 0x42)) &= 0xfffffc00;
    *((unsigned short *) ((char *) p + 0x42)) |= val;
}

void func_ov119_0229a764(unsigned char *self)
{
    int k;
    int i;
    void *base, *objA, *objB, *entry;
    int incA, incB;
    int j;
    int idx;
    int buf1[8];
    int buf2[7];

    base = func_ov119_0229ae50((void *) self);
    k = self[0x9c] << 3;
    incA = 0x1ce;
    incB = 0x14e;
    j = 0xc3;
    func_020641c8(buf1);
    func_02064170(buf2);

    for (i = 0; i < 8; i++) {
        objA = func_ov119_0229bb44(self);
        objB = func_ov119_0229bb44(self);

        idx = (self + k)[0xbc];
        if (idx < 0x20) {
            entry = (unsigned char *) base + idx * 0x24;
        } else {
            entry = 0;
        }

        if (entry != 0 && func_02077e50(func_02077c3c(entry)) != 0) {
            func_020a8874(buf2, func_02077c34(entry), 6);
            func_020a8a70(buf1, buf2, 0, 0);
            func_020b496c(0, buf1);
            func_0207094c(objA, 0x66);
            func_020708e4(objB, func_02077c38(entry), 6);
            self[0xaf]++;

            if (func_02077d6c(func_02077c3c(entry)) != 0) {
                func_ov119_0229a8ec((int) self, (unsigned short *) ((unsigned short *) (self + 0xe0c) + j), 0x50);
            } else {
                func_ov119_0229a8ec((int) self, (unsigned short *) ((unsigned short *) (self + 0xe0c) + j), 0x54);
            }
        } else {
            func_020a8c1c(objA);
            func_020a8c1c(objB);
            func_ov119_0229a8ec((int) self, (unsigned short *) ((unsigned short *) (self + 0xe0c) + j), 0x10);
        }

        func_02070adc(objA, 4, incA, 0xa, 0xf, 0, 0);
        func_02070a04(objA, 0, 0);
        func_02070adc(objB, 4, incB, 8, 0xf, 0, 0);
        func_02070a04(objB, 0, 0);

        incA += 0x14;
        incB += 0x10;
        k++;
        j += 0x40;
    }

    func_02064158(buf2);
    func_020641b0(buf1);
}

void func_ov119_0229a714(struct UnkStruct_0229a714 *self)
{
    self->unk_B2 = 0;
    self->unk_B3 = 0;
    func_ov119_0229a46c(self);
    self->unk_AF = 0;
    if (self->unk_9C == 4) {
        goto case4;
    }
    if (self->unk_9C == 5) {
        func_ov119_0229aacc((unsigned char *) self);
        goto end;
    } else {
        goto other;
    }
case4:
    func_ov119_0229aa18((u32) self);
    goto end;
other:
    func_ov119_0229a410(self, 4);
    func_ov119_0229a764((unsigned char *) self);
end:;
}

void func_ov119_0229a69c(UnkStruct_0229a69c *self, unsigned char val)
{
    if (val == self->unk_9C) {
        return;
    }
    self->unk_9D = val;
    self->unk_9C = val;
    if (self->unk_9C == 5) {
        func_ov119_0229bacc(self, 0xeb);
        self->unk_1E0C = self->sub_a;
    } else if (self->unk_9C == 4) {
        func_ov119_0229bacc(self, 0xea);
        self->unk_1E0C = self->sub_b;
    } else {
        func_ov119_0229bacc(self, 0xcd);
        self->unk_1E0C = self->sub_a;
    }
    func_ov119_0229a410(self, 2);
    func_ov119_0229a714((struct UnkStruct_0229a714 *) self);
}

int func_ov119_0229a650(void *a, int limit)
{
    char *base;
    int count;
    int i;

    base = (char *) func_ov119_0229ae50((void *) a);
    count = 0;
    i = count;
    for (; i < 0x20; i++) {
        if (func_02077e50((void *) ((int) func_02077c3c((void *) (base + i * 0x24))))) {
            count++;
            if (i >= limit) {
                i = 0x20;
            }
        }
    }
    if (count > 0) {
        return ((count - 1) * 0x200000u) >> 24;
    } else {
        return 0;
    }
}

void func_ov119_0229a5d8(unsigned char *dst)
{
    void *h;
    int i;
    unsigned long long v;

    h = func_020984e8();
    if ((func_02077bd8(func_02099664(h)) & func_02077bd0(func_02099664(h))) == 0) {
        for (i = 0; i < 0xc; i++) {
            (dst + i)[0xa1] = 0xa;
        }
    } else {
        v = func_02077be0(func_02099664(h));
        for (i = 0xb; i >= 0; i--) {
            (dst + i)[0xa1] = (unsigned char) (v % 10);
            v /= 10;
        }
    }
}
