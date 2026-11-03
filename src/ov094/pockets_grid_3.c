/* pockets_grid_3: 29 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229b000 @ 0x0229b000, 0x3c bytes, Thumb
 * func_ov094_0229afe0 @ 0x0229afe0, 0x20 bytes, Thumb
 * func_ov094_0229afb8 @ 0x0229afb8, 0x28 bytes, Thumb
 * func_ov094_0229af40 @ 0x0229af40, 0x78 bytes, Thumb
 * func_ov094_0229af20 @ 0x0229af20, 0x20 bytes, Thumb
 * func_ov094_0229af18 @ 0x0229af18, 0x8 bytes, Thumb
 * func_ov094_0229aee8 @ 0x0229aee8, 0x2e bytes, Thumb
 * func_ov094_0229aeb8 @ 0x0229aeb8, 0x2e bytes, Thumb
 * func_ov094_0229aea8 @ 0x0229aea8, 0x10 bytes, Thumb
 * func_ov094_0229ae54 @ 0x0229ae54, 0x54 bytes, Thumb
 * func_ov094_0229ae10 @ 0x0229ae10, 0x44 bytes, Thumb
 * func_ov094_0229ad64 @ 0x0229ad64, 0xac bytes, Thumb
 * func_ov094_0229ad20 @ 0x0229ad20, 0x42 bytes, Thumb
 * func_ov094_0229ace4 @ 0x0229ace4, 0x3c bytes, Thumb
 * func_ov094_0229acb0 @ 0x0229acb0, 0x34 bytes, Thumb
 * func_ov094_0229abf8 @ 0x0229abf8, 0xb8 bytes, Thumb
 * func_ov094_0229abb8 @ 0x0229abb8, 0x40 bytes, Thumb
 * func_ov094_0229aba4 @ 0x0229aba4, 0x14 bytes, Thumb
 * func_ov094_0229ab90 @ 0x0229ab90, 0x14 bytes, Thumb
 * func_ov094_0229ab7c @ 0x0229ab7c, 0x14 bytes, Thumb
 * func_ov094_0229ab68 @ 0x0229ab68, 0x14 bytes, Thumb
 * func_ov094_0229ab5c @ 0x0229ab5c, 0xc bytes, Thumb
 * func_ov094_0229ab1c @ 0x0229ab1c, 0x40 bytes, Thumb
 * func_ov094_0229ab0c @ 0x0229ab0c, 0x10 bytes, Thumb
 * func_ov094_0229aafc @ 0x0229aafc, 0x10 bytes, Thumb
 * func_ov094_0229aaac @ 0x0229aaac, 0x50 bytes, Thumb
 * func_ov094_0229aa84 @ 0x0229aa84, 0x28 bytes, Thumb
 * func_ov094_0229aa58 @ 0x0229aa58, 0x2c bytes, Thumb
 * func_ov094_0229aa14 @ 0x0229aa14, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229afe0 {
    char *unk_00;
    char pad_04[0x180];
    char sub;
};

typedef struct UnkStruct_0229ad64 UnkStruct_0229ad64;

typedef struct UnkStruct_0229ad64_2 UnkStruct_0229ad64_2;

struct UnkStruct_0229ad64 {
    u8 unk_00[0x184];
    u8 unk_184[0xa38 - 0x184];
    u8 unk_A38[4];
};

struct UnkStruct_0229ad64_2 {
    int unk_00;
    unsigned int b0 : 10;
    unsigned int b10 : 2;
    unsigned int b12 : 4;
    unsigned int b16 : 16;
};

struct UnkStruct_0229ace4;

struct UnkStruct_0229ace4 {
    char pad_00[0xa34];
    unsigned short *unk_A34;
};

extern void func_ov094_0229b104(void *p);
extern void *func_020b9af4(void *p);
extern char data_ov094_0229bf90[];
extern void func_ov094_0229b0f8(char *);
extern void func_020edb3c(void *);
extern void func_ov094_0229b0d4(void *);
extern void func_ov094_0229a38c(void *);
extern void func_ov094_0229a4d8(unsigned char *);
extern int func_02088d9c(int);
extern int func_02088d94(int);
extern void func_ov094_0229a34c(u8 *, int);
extern void func_ov094_0229a36c(u8 *, int);
extern UnkStruct_0229ad64_2 *func_ov094_0229a524(UnkStruct_0229ad64 *, int);
extern int func_ov094_0229b088(u8 *, int);
extern int func_ov094_0229b03c(u8 *, int);
extern int func_02002a88(int, int, int, int, int);
extern void *func_02099734(void *);
extern short *func_02098f48(void *, int);
extern int func_02098e8c(void *, int);
extern int func_ov094_02299a90(unsigned short x);
extern int func_0204c6b8(void *p);
extern void *func_02070c08(void *);
extern void *func_0208aecc(void *);
extern void *func_02062fbc(void *);
extern void *func_02094fd4(void *);
extern int func_0207094c(void *, int);
extern void func_02051a78(void *, void *);
extern int func_02062ea4(void *, void *);
extern void func_02099e7c(void *, void *);
extern void *func_020b496c(int, void *);
extern int func_ov094_02299a70(int);
extern void func_0208aa48(void *, void *);
extern void *func_02094fbc(void *);
extern void *func_02062f4c(void *);
extern void func_0208aeb8(void *);
extern int **func_02070be8(void *);
extern void *data_ov094_0229bc58[];
extern int func_ov094_0229a8bc(void *p, unsigned char c);
extern int func_020984e8(void);
extern void func_0209a088(void *p, int a, int b);

unsigned char func_ov094_0229ae54(int p0, int p1, int p2, int p3, int p4, unsigned char p5, unsigned char p6);
int func_ov094_0229ae10(int a0, int a1, int a2, int a3);
int func_ov094_0229acb0(int arg0, void *p, int sel);
unsigned short func_ov094_0229aaac(void *obj, int val);
unsigned char func_ov094_0229aa84(int a, int idx);
void func_ov094_0229aa14(unsigned int p1, int p2, int p3, int p4);

void *func_ov094_0229b000(void *obj)
{
    char *p;
    char *end;

    *(int *) obj = (int) ((int *) data_ov094_0229bf90);
    func_ov094_0229b104((char *) obj + 0x184);
    p = (char *) obj + 0x98c;
    end = (char *) obj + 0xa34;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);

    return obj;
}

struct UnkStruct_0229afe0 *func_ov094_0229afe0(struct UnkStruct_0229afe0 *self)
{
    self->unk_00 = data_ov094_0229bf90;
    func_ov094_0229b0f8(&self->sub);
    return self;
}

void *func_ov094_0229afb8(void *param)
{
    *(void **) param = (void *) ((char *) data_ov094_0229bf90);
    func_ov094_0229b0f8((char *) ((char *) param + 0x184));
    func_020edb3c(param);
    return param;
}

void func_ov094_0229af40(void *self, int param)
{
    func_ov094_0229b0d4((char *) self + 0x184);
    func_ov094_0229a38c((char *) self + 0xa38);
    func_ov094_0229a38c((char *) self + 0xa40);
    func_ov094_0229a38c((char *) self + 0xa48);
    ((char *) self)[0xa56] = 0x23;
    ((char *) self)[0xa57] = 0;
    *(int *) ((char *) self + 0xa50) = param;
    *(int *) ((char *) self + 0xa34) = 0;
    ((char *) self)[0xa59] = 0xa;
    ((char *) self)[0xa5c] = 1;
}

void func_ov094_0229af20(unsigned char *param)
{
    func_ov094_0229a4d8(param);
    if (param[0xa57] != 0) {
        --param[0xa57];
    }
}

void func_ov094_0229af18(unsigned char *arg0)
{
    func_ov094_0229a4d8((unsigned char *) arg0);
}

int func_ov094_0229aee8(int a, int b, int c)
{
    if (c < 0x68) {
        return 0x23;
    } else {
        return (int) func_ov094_0229ae54(a, b - 0x94, c - 0x74, b - 0x7c, c - 0x5c, 0, 0xe);
    }
}

int func_ov094_0229aeb8(int a, int b, int c)
{
    if (c > 0x68) {
        return 0x23;
    }
    return (int) func_ov094_0229ae54(a, b - 0x94, c - 0x74, b - 0x7c, c - 0x5c, 0xf, 0x1d);
}

int func_ov094_0229aea8(int a, int b, int c)
{
    return func_ov094_0229ae10(a, b, c, 0x21);
}

unsigned char func_ov094_0229ae54(int p0, int p1, int p2, int p3, int p4, unsigned char p5, unsigned char p6)
{
    int i;
    for (i = p5; i <= p6; i++) {
        int x;
        int y;
        int z;
        x = (int) func_ov094_0229a524((UnkStruct_0229ad64 *) p0, i);
        y = func_02088d9c(x);
        if (p1 >= y || y >= p3) {
            continue;
        }
        z = func_02088d94(x);
        if (p2 >= z || z >= p4) {
            continue;
        }
        return (unsigned char) i;
    }
    return 0x23;
}

int func_ov094_0229ae10(int a0, int a1, int a2, int a3)
{
    int base1;
    int high1;
    int low2;
    int high2;
    int v;
    int c1;
    int c2;

    base1 = a1;
    high1 = base1 - 0x7c;
    low2 = a2 - 0x74;
    high2 = a2 - 0x5c;
    v = (int) func_ov094_0229a524((UnkStruct_0229ad64 *) a0, a3);
    c1 = func_02088d9c(v);
    if (base1 - 0x94 < c1 && c1 < high1) {
        c2 = func_02088d94(v);
        if (low2 < c2 && c2 < high2) {
            return 1;
        }
    }
    return 0;
}

void func_ov094_0229ad64(UnkStruct_0229ad64 *self, int a, u16 *p2, int c)
{
    UnkStruct_0229ad64_2 *e;
    int idx;
    int t;
    int res;

    if (*p2 == 0xfff1) {
        func_ov094_0229a34c(self->unk_A38, a);
        return;
    }
    func_ov094_0229a36c(self->unk_A38, a);
    idx = func_ov094_0229acb0((int) self, (void *) p2, c);
    e = func_ov094_0229a524(self, a);
    t = e->b0;
    res = func_ov094_0229b088(self->unk_184, idx);
    func_02002a88(res, 8, t, t, t + 1);
    t += 0x20;
    func_02002a88(res + 0x400, 8, t, t, t + 1);
    e->b12 = func_ov094_0229b03c(self->unk_184, idx);
}

void func_ov094_0229ad20(void *p)
{
    void *x;
    short *base;
    int i, j;

    x = func_02099734((void *) func_020984e8());
    base = func_02098f48(x, 0);
    for (j = 0, i = 0; i < 15; j++, i++) {
        func_ov094_0229ad64((UnkStruct_0229ad64 *) p, j, (u16 *) (base + i), func_02098e8c(x, i));
    }
}

void func_ov094_0229ace4(struct UnkStruct_0229ace4 *p, unsigned short *arr)
{
    int i;
    int param = 15;
    int zero = 0;
    unsigned short val;

    for (i = 0; i < 15; i++) {
        val = arr[i];
        func_ov094_0229ad64((UnkStruct_0229ad64 *) p, param, (u16 *) (&val), zero);
        param++;
    }
    p->unk_A34 = arr;
}

int func_ov094_0229acb0(int arg0, void *p, int sel)
{
    switch (sel) {
        case 1:
            return 0xb3;
        case 2:
            if (func_ov094_02299a90(*(unsigned short *) p) != 0) {
                return func_0204c6b8(p);
            } else {
                return 0xb4;
            }
        default:
            return func_0204c6b8(p);
    }
}

void func_ov094_0229abf8(int a0, void *arg1, u16 *arg2, int mode)
{
    struct {
        u8 unk0[0x30];
        u8 unk30[0x28];
        u8 unk58[0x20];
        u8 unk78[0x70];
    } buf;

    func_02070c08(buf.unk78);
    func_0208aecc(buf.unk0);
    func_02062fbc(buf.unk30);
    func_02094fd4(buf.unk58);

    switch (mode) {
        case 1:
            func_0207094c(buf.unk78, 0x18);
            func_02051a78(buf.unk0, buf.unk78);
            break;
        case 2:
            if (func_ov094_02299a70(*arg2) != 0) {
                func_02062ea4(buf.unk30, arg2);
                func_02051a78(buf.unk0, buf.unk30);
            } else {
                func_02099e7c(buf.unk58, arg2);
                func_020b496c(0, buf.unk58);
                func_0207094c(buf.unk78, 0x40);
                func_02051a78(buf.unk0, buf.unk78);
            }
            break;
        case 0:
        default:
            func_02062ea4(buf.unk30, arg2);
            func_02051a78(buf.unk0, buf.unk30);
            break;
    }

    func_0208aa48(arg1, buf.unk0);
    func_02094fbc(buf.unk58);
    func_02062f4c(buf.unk30);
    func_0208aeb8(buf.unk0);
    func_02070be8(buf.unk78);
}

void func_ov094_0229abb8(int a, int b, int c)
{
    unsigned short x;
    int ret;

    ret = (int) func_ov094_0229aaac((void *) a, c);
    x = 0xfff1;
    x = (unsigned short) ret;
    if (x == 0xfff1) {
        return;
    }

    func_ov094_0229abf8(a, (void *) b, (u16 *) (&x), (int) func_ov094_0229aa84(a, c));
}

int func_ov094_0229aba4(int arg0, int arg1)
{
    return func_02088d9c((int) ((unsigned int *) (void *) func_ov094_0229a524((UnkStruct_0229ad64 *) arg0, arg1))) + 0x80;
}

int func_ov094_0229ab90(int forwarded0, int arg1)
{
    return func_02088d94((int) func_ov094_0229a524((UnkStruct_0229ad64 *) forwarded0, arg1)) + 0x60;
}

int func_ov094_0229ab7c(unsigned char *arr, unsigned char c)
{
    if (c == arr[0xa56]) {
        return 1;
    }
    return 0;
}

void *func_ov094_0229ab68(void *self)
{
    return data_ov094_0229bc58[((unsigned char *) self)[0x0a57]];
}

void func_ov094_0229ab5c(unsigned char *p)
{
    p[0xa56] = 0x23;
}

void func_ov094_0229ab1c(void *p, int b)
{
    if (func_ov094_0229a8bc(p, (unsigned char) b)) {
        func_ov094_0229ab5c((unsigned char *) p);
    } else {
        if (*(unsigned char *) ((char *) p + 0xa56) != b) {
            *(unsigned char *) ((char *) p + 0xa56) = (unsigned char) b;
            *(unsigned char *) ((char *) p + 0xa57) = 2;
        }
    }
}

void func_ov094_0229ab0c(int arg)
{
    func_ov094_0229a38c((void *) (arg + 0xa40));
}

void func_ov094_0229aafc(int p0, int p1)
{
    func_ov094_0229a36c((u8 *) ((p0 + 2624)), p1);
}

unsigned short func_ov094_0229aaac(void *obj, int val)
{
    void *tmp;
    void **field;
    unsigned short *list;

    tmp = func_02099734((void *) ((int) func_020984e8()));

    if (val >= 0 && val <= 14) {
        list = (unsigned short *) func_02098f48(tmp, 0);
        return list[val];
    }

    if (val >= 15 && val <= 29) {
        field = (void **) ((char *) obj + 0xa34);
        if (*field != 0) {
            return ((unsigned short *) *field)[val - 15];
        }
    }
    return 0xfff1;
}

unsigned char func_ov094_0229aa84(int a, int idx)
{
    if (idx >= 0 && idx <= 14) {
        return (unsigned char) func_02098e8c((void *) ((int) func_02099734((void *) (func_020984e8()))), idx);
    }
    return 0;
}

void func_ov094_0229aa58(void *a, void *b)
{
    func_ov094_0229aa14((unsigned int) a, (int) b, 0xfff1, 0);
    func_ov094_0229a34c((u8 *) ((char *) a + 0xa38), (int) b);
}

void func_ov094_0229aa14(unsigned int p1, int p2, int p3, int p4)
{
    volatile unsigned short local;
    local = 0xfff1;
    local = p3;
    if (p2 >= 0 && p2 <= 14) {
        func_0209a088((unsigned short *) &local, p4, p2);
    } else if (p2 >= 15 && p2 <= 29) {
        ((unsigned short *) (*(unsigned int *) ((char *) p1 + 0xa34)))[p2 - 15] = p3;
    }
}
