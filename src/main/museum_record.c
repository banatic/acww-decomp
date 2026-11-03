/* museum_record: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02071490 @ 0x02071490, 0x10 bytes, Thumb
 * func_0207148c @ 0x0207148c, 0x2 bytes, Thumb
 * func_02071450 @ 0x02071450, 0x3c bytes, Thumb
 * func_02071424 @ 0x02071424, 0x2a bytes, Thumb
 * func_020713ec @ 0x020713ec, 0x36 bytes, Thumb
 * func_02071318 @ 0x02071318, 0xd4 bytes, Thumb
 * func_020712ec @ 0x020712ec, 0x2a bytes, Thumb
 * func_020712b0 @ 0x020712b0, 0x3c bytes, Thumb
 * func_02071298 @ 0x02071298, 0x18 bytes, Thumb
 * func_0207122c @ 0x0207122c, 0x6c bytes, Thumb
 * func_02071188 @ 0x02071188, 0xa4 bytes, Thumb
 * func_02071110 @ 0x02071110, 0x76 bytes, Thumb
 * func_02071028 @ 0x02071028, 0xe8 bytes, Thumb
 * func_02070fe4 @ 0x02070fe4, 0x44 bytes, Thumb
 * func_02070fa0 @ 0x02070fa0, 0x42 bytes, Thumb
 * func_02070f5c @ 0x02070f5c, 0x44 bytes, Thumb
 * func_02070f1c @ 0x02070f1c, 0x40 bytes, Thumb
 * func_02070edc @ 0x02070edc, 0x40 bytes, Thumb
 * func_02070e98 @ 0x02070e98, 0x44 bytes, Thumb
 * func_02070dc0 @ 0x02070dc0, 0xd8 bytes, Thumb
 * func_02070d74 @ 0x02070d74, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char a[0x1b];
    unsigned char b[0x1d];
    unsigned char c[0x1d];
    unsigned char d[0xb];
} UnkStruct_02071450;

typedef struct UnkStruct_02071110 {
    char pad_00[0x60];
    unsigned char unk_60;
    unsigned char unk_61;
    unsigned char unk_62;
    unsigned char unk_63;
} UnkStruct_02071110;

extern int func_020984d4(void);
extern int func_020988d8(unsigned int);
extern int func_0209f150(void *, int);
extern void func_0209e474(void *);
extern void func_0209f128(void *, int);
extern unsigned char data_021dc7a8;
extern void *func_020641c8(void *p);
extern void func_02064210(void *a, void *b);
extern int func_0203d7c4(int a, void *b);
extern void *func_02098844(const char *s, int idx);
extern int func_02099a28(unsigned int);
extern void func_02066694(void *p);
extern int func_02099870(void *p);
extern void func_02066024(void *a, void *b, void *c, void *d, void *e, int f);
extern unsigned short func_02065ed0(void *a, int b, int c);
extern int func_02097a54(void *p);
extern void func_02066688(void *p);
extern void *func_020641b0(void *p);
extern char data_021dc7aa[];
extern char data_021dc7bc[];
extern int data_020e17ac;
extern int data_020e17b0;
extern int data_020e17b4;
extern int func_02095074(int a, int b);
extern int FX_Div(int a, int b);
extern int func_020535f0(unsigned short *t);

void func_02071450(UnkStruct_02071450 *p);
int func_02071318(int base, unsigned short *pid, int *out);
int func_02071188(void *object);
int func_02070fa0(int arg0);
int func_02070f5c(void *p);
int func_02070f1c(int param);
unsigned int func_02070edc(int param);
int func_02070e98(void *p);

void *func_02071490(void *p)
{
    func_02071450((UnkStruct_02071450 *) p);
    return p;
}

void func_0207148c(void *object) {}

void func_02071450(UnkStruct_02071450 *p)
{
    unsigned int i;
    for (i = 0; i < 0x1b; i++) {
        p->a[i] = 0;
    }
    for (i = 0; i < 0x1d; i++) {
        p->b[i] = 0;
    }
    for (i = 0; i < 0x1d; i++) {
        p->c[i] = 0;
    }
    for (i = 0; i < 0xb; i++) {
        p->d[i] = 0;
    }
}

void func_02071424(int a, int b)
{
    int out;
    unsigned char *p = (unsigned char *) func_02071318(a, (unsigned short *) b, &out);
    if (p) {
        p[out >> 1] &= ~(0xF << ((out & 1) << 2));
    }
}

void func_020713ec(int param0, int param1)
{
    int local;
    unsigned char *p;
    p = (void *) func_02071318(param0, (unsigned short *) param1, &local);
    if (p) {
        int bitpos = (local & 1) << 2;
        int offset = local >> 1;
        p[offset] &= ~(0xF << bitpos);
        p[offset] |= (5 << bitpos);
    }
}

int func_02071318(int base, unsigned short *pid, int *out)
{
    unsigned int ok = 0;
    unsigned short id = *pid;
    int v;

    if (id >= 0x450c && id <= 0x45db) {
        ok = 1;
    }
    if (ok != 0) {
        if (out != 0) {
            if (id >= 0x450c && id <= 0x45db) {
                v = (id - 0x450c) >> 2;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base;
    }
    if (id >= 0x3894 && id <= 0x38e3) {
        if (out != 0) {
            if (id >= 0x3894 && id <= 0x38e3) {
                v = (id - 0x3894) >> 2;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x55;
    }
    if (id >= 0x12b0 && id <= 0x12e7) {
        if (out != 0) {
            if (id >= 0x12b0 && id <= 0x12e7) {
                v = id - 0x12b0;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x38;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        if (out != 0) {
            if (id >= 0x12e8 && id <= 0x131f) {
                v = id - 0x12e8;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x1b;
    }
    return 0;
}

int func_020712ec(int a, int b)
{
    int temp;
    unsigned char *p;
    int idx;
    int shift;
    int result;

    p = (unsigned char *) func_02071318(a, (unsigned short *) b, &temp);
    if (p != 0) {
        idx = temp >> 1;
        shift = (temp & 1) << 2;
        result = (p[idx] >> shift) & 0xf;
    } else {
        result = 0;
    }
    return result;
}

int func_020712b0(int r4, int r5)
{
    int r0;

    r4 = func_020712ec(r4, r5);
    if (r4 == 0) {
        return 3;
    }
    if (r4 == 5) {
        return 2;
    }
    r5 = func_020984d4();
    r0 = func_020988d8(r5);
    if (r0 == 1 && r4 == r5 + 1) {
        return 0;
    }
    return 1;
}

int func_02071298(int argument0, int argument1)
{
    if (func_020712ec((int) argument0, (int) argument1) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_0207122c(unsigned char *param)
{
    unsigned char local[8];
    if (func_0209f150(&data_021dc7a8, 3) != 0) {
        return;
    }
    if (func_02070fa0((int) param) == 0) {
        return;
    }
    *((unsigned int *) local) = 0;
    *((unsigned int *) local + 1) = 0;
    func_0209e474(local);
    if ((param[0x62] == local[5]) && (param[0x61] == local[4])) {
        if (param[0x60] == local[3]) {
            return;
        }
    }
    if (func_02071188(param) == 0) {
        return;
    }
    func_0209f128(&data_021dc7a8, 3);
}

int func_02071188(void *object)
{
    char c8;
    u32 buf1[8];
    u32 buf2[0x40];
    int result;
    int i;

    func_020641c8(buf1);
    func_02064210(data_021dc7aa, buf1);
    func_0203d7c4(2, buf1);

    result = 0;

    for (i = 0; i < 4; i++) {
        void *p;
        int q;

        p = func_02098844(data_021dc7bc, i);
        if (p == 0) {
            continue;
        }
        if (func_02099a28((unsigned int) p) == 0) {
            continue;
        }

        func_02066694(buf2);
        c8 = 0;
        q = func_02099870(p);
        func_02066024(buf2, &c8, &data_020e17b4, &data_020e17ac, &data_020e17b0, q);
        func_02065ed0(buf2, 0x3870, 1);
        if (func_02097a54(buf2) != 0) {
            result = 1;
        }
        func_02066688(buf2);
    }

    func_020641b0(buf1);
    return result;
}

void func_02071110(UnkStruct_02071110 *self, void *other)
{
    int idx;
    unsigned int data[2];
    unsigned char *ptr;

    func_02071424((int) self, (int) other);
    ptr = (unsigned char *) func_02071318((int) self, (unsigned short *) other, &idx);
    if (ptr) {
        int v = func_020984d4() & 3;
        v += 1;
        ptr[idx >> 1] |= v << ((idx & 1) << 2);
    }
    if (func_02070fa0((int) self)) {
        data[0] = 0;
        data[1] = 0;
        func_0209e474((void *) data);
        self->unk_62 = ((unsigned char *) data)[5];
        self->unk_61 = ((unsigned char *) data)[4];
        self->unk_60 = ((unsigned char *) data)[3];
        self->unk_63 = 0;
    }
}

void func_02071028(void *ctx, int k)
{
    unsigned short vals[4];
    unsigned int i;
    int want;

    i = 0;
    want = (k & 3) + 1;
    do {
        vals[0] = (i < 0x34) ? (i * 4 + 0x450c) : 0x450c;
        if (func_020712ec((int) ctx, (int) (&vals[0])) == want) {
            func_020713ec((int) ctx, (int) (&vals[0]));
        }
        i++;
    } while (i < 0x34);
    i = 0;
    do {
        vals[1] = (i < 0x38) ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_020712ec((int) ctx, (int) (&vals[1])) == want) {
            func_020713ec((int) ctx, (int) (&vals[1]));
        }
        i++;
    } while (i < 0x38);
    i = 0;
    do {
        vals[2] = (i < 0x38) ? (unsigned short) (i + 0x12b0) : 0x12b0;
        if (func_020712ec((int) ctx, (int) (&vals[2])) == want) {
            func_020713ec((int) ctx, (int) (&vals[2]));
        }
        i++;
    } while (i < 0x38);
    i = 0;
    do {
        vals[3] = (i < 0x14) ? (i * 4 + 0x3894) : 0x3894;
        if (func_020712ec((int) ctx, (int) (&vals[3])) == want) {
            func_020713ec((int) ctx, (int) (&vals[3]));
        }
        i++;
    } while (i < 0x14);
}

int func_02070fe4(void *self, int p1, int p2)
{
    int forwarded_value;

    int masked;
    if ((unsigned int) func_020712b0((int) self, p2) > 1) {
        goto fail;
    }
    masked = (func_020712ec((int) self, p2) - 1) & 3;
    if ((forwarded_value = (int) (int) func_02098844((const char *) (((char *) data_021dc7bc)), masked)) == 0) {
        goto fail;
    }
    func_02095074(func_02099870((void *) ((int) forwarded_value)), p1);
    return 1;
fail:
    return 0;
}

int func_02070fa0(int arg0)
{
    int result;
    if ((int) func_02070edc(arg0) == 0) {
        result = 0;
    } else if (func_02070e98((void *) arg0) == 0) {
        result = 0;
    } else if (func_02070f5c((void *) arg0) == 0) {
        result = 0;
    } else if (func_02070f1c(arg0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02070f5c(void *p)
{
    unsigned int i;
    unsigned short val;
    for (i = 0; i < 56; i++) {
        val = (i < 56) ? (unsigned short) (i + 0x12b0) : 0x12b0;
        if (func_02071298((int) p, (int) (&val)) == 0) {
            return 0;
        }
    }
    return 1;
}

int func_02070f1c(int param)
{
    unsigned int i;
    short val;
    int base = 0x450c;
    for (i = 0; i < 52; i++) {
        val = (i < 52) ? base + i * 4 : base;
        if (func_02071298(param, (int) (&val)) == 0) {
            return 0;
        }
    }
    return 1;
}

unsigned int func_02070edc(int param)
{
    unsigned int i;
    unsigned short val;
    for (i = 0; i < 20; i++) {
        val = (i < 20) ? (0x3894 + i * 4) : 0x3894;
        if (func_02071298(param, (int) (&val)) == 0) {
            return 0;
        }
    }
    return 1;
}

int func_02070e98(void *p)
{
    unsigned int i;
    unsigned short val;
    for (i = 0; i < 56; i++) {
        val = (i < 56) ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_02071298((int) p, (int) (&val)) == 0) {
            return 0;
        }
    }
    return 1;
}

int func_02070dc0(void *ctx)
{
    unsigned short vals[4];
    unsigned int r5;
    int r4 = 0;

    r5 = 0;
    do {
        vals[0] = (r5 < 20) ? (r5 * 4 + 0x3894) : 0x3894;
        if (func_02071298((int) ctx, (int) (&vals[0]))) {
            r4++;
        }
        r5++;
    } while (r5 < 20);

    r5 = 0;
    do {
        vals[1] = (r5 < 56) ? (unsigned short) (r5 + 0x12e8) : 0x12e8;
        if (func_02071298((int) ctx, (int) (&vals[1]))) {
            r4++;
        }
        r5++;
    } while (r5 < 56);

    r5 = 0;
    do {
        vals[2] = (r5 < 56) ? (unsigned short) (r5 + 0x12b0) : 0x12b0;
        if (func_02071298((int) ctx, (int) (&vals[2]))) {
            r4++;
        }
        r5++;
    } while (r5 < 56);

    r5 = 0;
    do {
        vals[3] = (r5 < 52) ? (r5 * 4 + 0x450c) : 0x450c;
        if (func_02071298((int) ctx, (int) (&vals[3]))) {
            r4++;
        }
        r5++;
    } while (r5 < 52);

    return FX_Div((100 * r4) << 12, 0x000b8000);
}

int func_02070d74(void *a, int b)
{
    int n = 0;
    unsigned int i;
    for (i = 0; i < 0x34; i++) {
        unsigned short id;
        id = (unsigned short) (i < 0x34 ? 0x450c + i * 4 : 0x450c);
        if (b == func_020535f0(&id)) {
            if (func_02071298((int) a, (int) (&id)) != 0) {
                n++;
            }
        }
    }
    return n;
}
