/* constellations_2: 26 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b16fc @ 0x020b16fc, 0x34 bytes, Thumb
 * func_020b15b8 @ 0x020b15b8, 0x144 bytes, Thumb
 * func_020b15b0 @ 0x020b15b0, 0x8 bytes, Thumb
 * func_020b1580 @ 0x020b1580, 0x30 bytes, Thumb
 * func_020b1558 @ 0x020b1558, 0x28 bytes, Thumb
 * func_020b1530 @ 0x020b1530, 0x28 bytes, Thumb
 * func_020b14ec @ 0x020b14ec, 0x44 bytes, Thumb
 * func_020b14c0 @ 0x020b14c0, 0x2c bytes, Thumb
 * func_020b1498 @ 0x020b1498, 0x28 bytes, Thumb
 * func_020b1444 @ 0x020b1444, 0x54 bytes, Thumb
 * func_020b141c @ 0x020b141c, 0x26 bytes, Thumb
 * func_020b13e4 @ 0x020b13e4, 0x36 bytes, Thumb
 * func_020b1394 @ 0x020b1394, 0x50 bytes, Thumb
 * func_020b1328 @ 0x020b1328, 0x6c bytes, Thumb
 * func_020b1310 @ 0x020b1310, 0x18 bytes, Thumb
 * func_020b12e0 @ 0x020b12e0, 0x30 bytes, Thumb
 * func_020b12b0 @ 0x020b12b0, 0x2e bytes, Thumb
 * func_020b120c @ 0x020b120c, 0xa4 bytes, Thumb
 * func_020b11fc @ 0x020b11fc, 0x10 bytes, Thumb
 * func_020b11ec @ 0x020b11ec, 0x10 bytes, Thumb
 * func_020b11a4 @ 0x020b11a4, 0x48 bytes, Thumb
 * func_020b1130 @ 0x020b1130, 0x74 bytes, Thumb
 * func_020b10b8 @ 0x020b10b8, 0x78 bytes, Thumb
 * func_020b1078 @ 0x020b1078, 0x40 bytes, Thumb
 * func_020b1068 @ 0x020b1068, 0x10 bytes, Thumb
 * func_020b1050 @ 0x020b1050, 0x18 bytes, Thumb
 */

#include "types.h"

struct Arr6 {
    u16 v[6];
};

struct Src {
    u16 unk_00;
    struct Arr6 unk_02;
    u16 unk_0E;
    struct Arr6 unk_10;
    s8 unk_1C;
    u8 unk_1D;
};

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

typedef struct {
    char pad_00[0x2a];
    unsigned short arr[16];
} WorkStruct;

extern unsigned int data_021f4b08[2];
extern void func_020b1758(void);
extern unsigned char *func_020b1768(unsigned short a);
extern void func_020b1730(unsigned char a);
extern int data_021f2b04;
extern int func_020b1974(int, int);
extern void func_020b19a0(char *ptr, int n);
extern void *func_020b1a0c(char *ptr, int n);
extern void func_020b198c(void *ptr, int x);
extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern void func_02051c08(int a, int b, int c);
extern void func_02051bf8(void *, int);
extern void *func_020b18fc(char *a);
extern void func_020a8874(char *dst, const char *src, int len);
extern int func_020a8a70(int a, char *b, int c, int d);
extern void *func_020b18e4(char *a);
extern void func_020ba3bc(void *param, int x, int y);
extern void func_0209e474(void *);
extern int func_020ba494(void);
extern int func_020ba488(void);
extern int SDK_OVERLAY_ov127_ID;
extern void func_0204f934(int);
extern void func_0204f8ec(int);
extern int func_ov127_022995a0(char *arg);
extern int data_021ee418;
extern void *func_020900e4(int *ptr);
extern void func_020b1a24(void *);
extern int func_020644cc(int n);
extern int func_02090158(WorkStruct *);
extern int func_02051bb4(void *a, char *b, int c);

int func_020b1078(void *arg0, int arg1);

int func_020b16fc(int arg0)
{
    unsigned int bitmask;
    unsigned int bits;
    int result;

    if (arg0 >= 0x20) {
        bits = data_021f4b08[1];
        bitmask = 1u << (arg0 - 0x20);
        if ((bits & bitmask) != 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        bits = data_021f4b08[0];
        bitmask = 1u << arg0;
        if ((bits & bitmask) != 0) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

void func_020b15b8(unsigned short *arr, int *out1, int *out2)
{
    int min;
    int i;
    unsigned char *p;
    int max;
    int zero;
    int k;
    unsigned char b0, b1;
    int r4;
    int r5;
    int r6;
    int val;
    int val2;
    int val3;
    int var1c;
    int val4;
    int var2c;

    func_020b1758();

    min = 0x20;
    i = 0;
    max = ~i;
    zero = i;

    for (; i < 0x10; i++) {
        if (arr[i] != 0xffff) {
            p = func_020b1768(arr[i]);
            k = zero;
            while (k < 4) {
                b0 = p[0];
                b1 = p[1];
                p += 2;
                if (b0 != 0xff) {
                    func_020b1730(b0);
                    if (min > b1) {
                        min = b1;
                    }
                    if (max < b1) {
                        max = b1;
                    }
                } else {
                    k = 4;
                }
                k++;
            }
        }
    }

    r4 = 0;
    goto loop2_check;
    do {
        r4++;
    loop2_check:
        if (r4 >= 0x40) {
            break;
        }
    } while (func_020b16fc(r4) == 0);

    r5 = (r4 - 1) & 0x3f;
    r6 = r4;
    val = 0;
    val2 = 0;
    val3 = 0;

    while (val == 0 && r5 != r6) {
        if (func_020b16fc(r5) != 0) {
            val2 = val3;
            r6 = r5;
        } else if (val2 != 0) {
            val = 1;
        } else {
            val2 = 1;
        }
        r5 = (r5 - 1) & 0x3f;
    }

    if (val != 0) {
        r5 = (r4 + 1) & 0x3f;
        var1c = 0;
        val4 = 0;
        var2c = 0;
        while (var1c == 0 && r5 != r4) {
            if (func_020b16fc(r5) != 0) {
                val4 = var2c;
                r4 = r5;
            } else if (val4 != 0) {
                var1c = 1;
            } else {
                val4 = 1;
            }
            r5 = (r5 + 1) & 0x3f;
        }
    } else {
        r4 = 0;
        r6 = r4;
    }

    if (r6 <= r4) {
        *out1 = (r6 + r4 + 1) << 2;
    } else {
        r6 += 0x41;
        *out1 = ((r6 + r4) << 2) & 0x1ff;
    }

    *out2 = ((min << 3) + ((max << 3) + 8)) >> 1;
}

int func_020b15b0(void)
{
    return (int) &data_021f2b04;
}

int func_020b1580(void)
{
    int handle;
    int i;
    handle = func_020b15b0();
    for (i = 0; i < 16; i++) {
        if (func_020b1974(handle, i) == 0) {
            return i;
        }
    }
    return -1;
}

int func_020b1558(void)
{
    int i;
    int count;
    int x;
    x = func_020b15b0();
    count = 0;
    i = count;
    do {
        if (func_020b1974(x, i) == 0) {
            count++;
        }
        i++;
    } while (i < 16);
    return count;
}

int func_020b1530(int arg)
{
    int x;
    x = func_020b15b0();
    if (func_020b1974(x, arg) == 0) {
        return 0;
    } else {
        return x + arg * 0x4A;
    }
}

void func_020b14ec(int param1, int param2, int param3)
{
    char *base;
    base = (char *) func_020b15b0();
    func_020b19a0(base, param2);
    func_020b1a0c(base + 0x4a * param2, param1);
    if (param3 != 0) {
        *(unsigned short *) (base + 0x4a2) |= (1 << param2);
    }
}

void func_020b14c0(int x)
{
    void *res;
    res = (void *) func_020b15b0();
    func_020b198c(res, x);
    *(unsigned short *) ((char *) res + 0x4A2) &= ~(1 << x);
}

int func_020b1498(int p)
{
    int a = func_020b15b0();
    if (func_020b1974(a, p) == 0) {
        return 0;
    } else {
        return a + 74 * p;
    }
}

void func_020b1444(struct Src *dest)
{
    struct Src *src;

    src = (struct Src *) func_02099870(func_020984e8());

    dest->unk_00 = src->unk_00;
    dest->unk_02 = src->unk_02;
    dest->unk_0E = src->unk_0E;
    dest->unk_10 = src->unk_10;
    dest->unk_1C = src->unk_1C;
    dest->unk_1D = src->unk_1D;
}

void func_020b141c(int a, int b)
{
    int t = func_020b15b0();
    func_02051c08(a, t + b * 74 + 30, 6);
}

void func_020b13e4(void *arg0, int arg1)
{
    char *base;
    int result;
    base = (char *) func_020b15b0();
    func_02051bf8(arg0, 6);
    result = func_020b1974((int) ((void *) base), arg1);
    if (result != 0) {
        func_02051c08((int) (base + arg1 * 74 + 30), (int) arg0, 6);
    }
    return;
}

int func_020b1394(int a0, int a1)
{
    char buf[0x1c];
    char *p;

    if (func_020b1974(func_020b15b0(), a1) == 0) {
        return 0;
    }

    p = (char *) func_020b1530(a1);
    func_020b18fc(buf);
    func_020a8874(buf, p + 0x1e, 6);
    func_020a8a70(a0, buf, 0, 0);
    func_020b18e4(buf);

    return 1;
}

int func_020b1328(int *out)
{
    void *p;
    int i;
    int flag;

    *out = -1;
    p = (void *) func_020b15b0();
    i = 0;
    flag = 0;
    while (i < 16) {
        int mask = 1 << i;
        if (*(unsigned short *) ((char *) p + 0x4A2) & mask) {
            if (func_020b1974((int) p, i)) {
                if (*out == ~flag) {
                    *out = i;
                } else {
                    return 2;
                }
            } else {
                *(unsigned short *) ((char *) p + 0x4A2) &= ~mask;
            }
        }
        i++;
    }
    if (*out == -1) {
        return 0;
    }
    return 1;
}

void func_020b1310(void)
{
    unsigned short *ptr;
    unsigned short value;

    ptr = (unsigned short *) func_020b15b0();
    value = 0;
    ptr[0x251] = value;
}

void func_020b12e0(void *a, int b)
{
    int local0, local1;
    func_020b15b8((unsigned short *) (func_020b1530(b) + 0x2a), &local0, &local1);
    local0 -= 0x80;
    local1 -= 0x60;
    func_020ba3bc(a, local0, local1);
}

int func_020b12b0(int a, int b, int c, int d)
{
    if (d < b + 0x10 || d > b + 0x88) {
        return 0;
    }
    if (c < a + 0x40 || c > a + 0xc0) {
        return 0;
    }
    return 1;
}

int func_020b120c(void)
{
    int lim;
    int base;
    int i;
    int best;
    void *p;
    int dx;
    int dy;
    int d;
    int bestDist;
    Pair a;
    struct {
        int x;
        int y;
    } v;

    a.unk_00 = 0;
    a.w1 = 0;
    func_0209e474(&a);
    if (((unsigned char *) &a)[2] >= 6 && ((unsigned char *) &a)[2] < 0x12) {
        return -1;
    }
    lim = func_020ba494();
    base = func_020ba488();
    best = -1;
    for (i = 0; i < 0x10; i++) {
        p = (void *) func_020b1530(i);
        if (p == 0) {
            continue;
        }
        func_020b15b8((unsigned short *) ((char *) p + 0x2a), &v.x, &v.y);
        if (v.x < lim) {
            v.x += 0x200;
        }
        if (func_020b12b0(lim, base, v.x, v.y) == 0) {
            continue;
        }
        dy = v.y - (base + 0x60);
        dx = v.x - (lim + 0x80);
        d = dx * dx + dy * dy;
        if (best == -1 || bestDist > d) {
            best = i;
            bestDist = d;
        }
    }
    return best;
}

void func_020b11fc(void)
{
    func_0204f934((int) &SDK_OVERLAY_ov127_ID);
}

void func_020b11ec(void)
{
    func_0204f8ec((int) &SDK_OVERLAY_ov127_ID);
}

int func_020b11a4(char *arg)
{
    int x;
    int result;
    x = func_020b1580();
    if (x == -1) {
        return 0;
    }
    if (func_020b1078((void *) (arg + 0x1e), -1) != 0) {
        return 0;
    }
    func_020b11fc();
    result = func_ov127_022995a0(arg);
    func_020b11ec();
    if (result != 0) {
        func_020b14ec((int) arg, x, 1);
    }
    return result;
}

void func_020b1130(void)
{
    void *obj;
    void *list;
    int count;
    int i;

    obj = func_020900e4(&data_021ee418);
    func_020b1a24(obj);
    count = 0;
    list = (void *) func_020b15b0();

    i = 0;
    do {
        if (func_020b1974((int) list, i) != 0) {
            count++;
        }
        i++;
    } while (i < 16);

    if (count == 0) {
        return;
    }

    count = func_020644cc(count);

    i = 0;
    while (i < 16) {
        if (func_020b1974((int) list, i) != 0) {
            if (count > 0) {
                count--;
            } else {
                func_020b1a0c((char *) obj, func_020b1530(i));
                return;
            }
        }
        i++;
    }
}

void func_020b10b8(void)
{
    WorkStruct *self = ((WorkStruct *) &data_021ee418);
    int i;
    int j;
    int found;
    if (!func_02090158(self)) {
        return;
    }
    self = (WorkStruct *) func_020900e4((int *) self);
    found = 0;
    for (i = 0; i < 16; i++) {
        if (self->arr[i] == 0xFFFF) {
            continue;
        }
        found++;
        for (j = 0; j < i; j++) {
            if (self->arr[i] == self->arr[j]) {
                func_020b1a24((void *) self);
                return;
            }
        }
    }

    if (found != 0) {
        if (func_020b11a4((char *) self)) {
            func_020b1a24((void *) self);
        }
    }
}

int func_020b1078(void *arg0, int arg1)
{
    int i;
    for (i = 0; i < 16; i++) {
        char *p;
        if (arg1 == i) {
            continue;
        }
        p = (char *) func_020b1530(i);
        if (p == 0) {
            continue;
        }
        if (func_02051bb4(arg0, p + 0x1e, 6)) {
            return 1;
        }
    }
    return 0;
}

int func_020b1068(int r0)
{
    if (r0 >= 0x13 && r0 <= 0x1f) {
        return 1;
    }
    return 0;
}

int func_020b1050(int r0, int r1)
{
    int r3 = 0;
    if (r0 >= 0x20) {
        r3 += 0x400;
        r0 -= 0x20;
    }
    r1 <<= 5;
    r0 += r1;
    return r3 + r0;
}
