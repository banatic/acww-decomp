/* system_packet_3: 27 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02075fc4 @ 0x02075fc4, 0x34 bytes, Thumb
 * func_02075f3c @ 0x02075f3c, 0x88 bytes, Thumb
 * func_02075e00 @ 0x02075e00, 0x13c bytes, Thumb
 * func_02075dcc @ 0x02075dcc, 0x34 bytes, Thumb
 * func_02075d9c @ 0x02075d9c, 0x30 bytes, Thumb
 * func_02075d40 @ 0x02075d40, 0x5c bytes, Thumb
 * func_02075cc4 @ 0x02075cc4, 0x7c bytes, Thumb
 * func_02075c64 @ 0x02075c64, 0x60 bytes, Thumb
 * func_02075c00 @ 0x02075c00, 0x64 bytes, Thumb
 * func_02075b98 @ 0x02075b98, 0x68 bytes, Thumb
 * func_02075b14 @ 0x02075b14, 0x84 bytes, Thumb
 * func_02075aa4 @ 0x02075aa4, 0x70 bytes, Thumb
 * func_020759e0 @ 0x020759e0, 0xc4 bytes, Thumb
 * func_02075978 @ 0x02075978, 0x68 bytes, Thumb
 * func_02075918 @ 0x02075918, 0x60 bytes, Thumb
 * func_020758ac @ 0x020758ac, 0x6c bytes, Thumb
 * func_02075848 @ 0x02075848, 0x64 bytes, Thumb
 * func_020757e0 @ 0x020757e0, 0x68 bytes, Thumb
 * func_020757ac @ 0x020757ac, 0x34 bytes, Thumb
 * func_02075774 @ 0x02075774, 0x38 bytes, Thumb
 * func_0207570c @ 0x0207570c, 0x68 bytes, Thumb
 * func_020756cc @ 0x020756cc, 0x40 bytes, Thumb
 * func_02075670 @ 0x02075670, 0x5c bytes, Thumb
 * func_0207560c @ 0x0207560c, 0x62 bytes, Thumb
 * func_020755b4 @ 0x020755b4, 0x58 bytes, Thumb
 * func_0207557c @ 0x0207557c, 0x38 bytes, Thumb
 * func_0207556c @ 0x0207556c, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02075dcc {
    char pad_00[0x68];
    void *unk_68;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} unk_struct;

extern int func_020a1350(void);
extern char *func_020a00fc(int x);
extern int func_02090040(int);
extern int func_02090158(void *object);
extern int func_02075ff8(int, int, int, int, int);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern void func_02077b3c(int, int, int);
extern void *data_020ccf94;
extern unsigned int func_02073044(void);
extern char *func_02137550(void *p, int n);
extern void MI_CpuCopy8(const void *s, void *d, int n);
unsigned char func_02096284(void *ptr);
extern int func_020738e4(int);
extern int func_02073d28(void *, int);
extern int func_0207332c(void *);
extern void *func_020740dc(void);
extern int func_02073918(void *, int);
extern int func_02073e30(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern void func_0209e474(int *);
extern void func_020a6e4c(int i, u8 *a, u8 *b, u8 *c);
extern int func_020a7880(u8 *o);
extern void func_020a7850(u8 *o, int a, int b, int c, int d);
extern int func_020a7870(u8 *o);
extern int func_0209847c(int arg);
extern int func_020989e0(int object);
extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1284(int x, unsigned short y);
extern void func_020a127c(int x, unsigned char y);
extern void *func_020a1338(void);
extern void func_020a003c(void *p, int a);
extern void func_02090174(char *param);
extern void func_020a242c(int param1, int param2, int param3);
extern void func_020962a4(int a, int b);
extern void func_020a6f74(int, unsigned char);

int func_02075fc4(int p0, int p1)
{
    int a;
    char *b;
    char *c;
    a = func_020a1350();
    b = func_020a00fc(a);
    if (b == 0) {
        c = (char *) 0x17400;
    } else {
        c = b + 4;
    }
    return func_02075ff8(p0, a, (int) c, 1, p1);
}

int func_02075f3c(int param)
{
    int a, b, res1, res2;

    a = func_02090040(4);
    if (func_02090158((void *) a) != 0) {
        return func_02075ff8(param, a, 0x950, 2, 1);
    }
    if (((int) func_02073044(), func_020ebf70()) && func_02077a8c(1)) {
        b = (*(int *) &data_020ccf94);
        res1 = func_02073d28((void *) b, 4);
        func_02077b3c(res1, 0, 2);
        res2 = func_02073d28((void *) b, 4);
        return func_02073e30((void *) b, res2, 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}

int func_02075e00(int k0, int b0, int k1, int b1, int k2, int b2)
{
    unsigned int i;
    int kind;
    void *h;
    u8 *p;
    u16 tag[3];
    int A[3];
    int B[3];
    u8 *C[3];
    int D[3];

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    A[0] = k0;
    A[1] = k1;
    A[2] = k2;
    B[0] = b0;
    B[1] = b1;
    B[2] = b2;
    func_02137550(C, 0xc);
    func_02137550(D, 0xc);
    func_02137550(tag, 6);
    i = 0;
    h = data_020ccf94;
    for (; i < 3; i++) {
        kind = A[i];
        if (kind == 3) {
            continue;
        }
        C[i] = (u8 *) func_02073d28(h, i + 1);
        p = C[i];
        func_02077b3c((int) p, 0, 3);
        D[i] = D[i] + 1;
        if (kind == 0) {
            p[1] = 0;
            D[i] = D[i] + 1;
        } else if (kind == 1) {
            p[1] = 1;
            D[i] = D[i] + 1;
        } else {
            MI_CpuCopy8((void *) func_02090040(B[i]), p + 1, 0x950);
            D[i] = D[i] + 0x950;
        }
        tag[i] = (u16) (1 << (i + 1));
    }
    if (k0 == 3 && k1 == 3 && k2 == 3) {
        goto ret1;
    }
    if (func_02077a8c((u16) (tag[2] | (tag[0] | tag[1]))) == 0) {
        goto ret0;
    }
    return func_02073e30(h, (int) C[0], D[0], tag[0], (int) C[1], D[1], tag[1], (int) C[2], D[2], tag[2]);
ret0:
    return 0;
ret1:
    return 1;
fail:
    return 0;
}

int func_02075dcc(unsigned int a, unsigned int b)
{
    return func_02075ff8(
        a, func_0209847c((int) ((void *) func_02096284((*(struct UnkStruct_02075dcc **) &data_020ccf94)->unk_68))), 0x249c, 4,
        b);
}

int func_02075d9c(int a, int b)
{
    return func_02075ff8(a, func_020738e4((*(int *) &data_020ccf94)), 0x6A0, 0xC, b);
}

int func_02075d40(void *arg)
{
    void *obj;
    int a, b;

    if (((int) func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c((int) arg) == 0) {
        goto fail;
    }

    obj = data_020ccf94;
    a = func_02073d28(obj, 4);
    b = func_0207332c(obj);

    return func_02073e30(obj, a, b, (int) arg, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}

int func_02075cc4(void)
{
    void *ptr;
    void *g;
    char *tmp;
    int tmp2;

    ptr = func_020740dc();
    if (ptr == 0) {
        goto ret1;
    }
    func_02073044();
    if ((__arm int) func_020ebf70() == 0) {
        goto ret0;
    }
    if (func_02077a8c((int) ptr) == 0) {
        goto ret0;
    }
    g = data_020ccf94;
    func_02073918(g, 0);
    tmp = (char *) func_02073d28(g, 4);
    func_02077b3c((int) tmp, 0, 8);
    tmp[1] = 1;
    tmp2 = (int) func_02073d28(g, 4);
    return func_02073e30((void *) ((int) g), tmp2, 2, (int) ptr, 0, 0, 0, 0, 0, 0);

ret0:
    return 0;
ret1:
    return 1;
}

int func_02075c64(void)
{
    func_02073044();
    if (func_020ebf70() && func_02077a8c(1)) {
        void *p = data_020ccf94;
        func_02077b3c(func_02073d28(p, 4), 0, 7);
        return func_02073e30(p, func_02073d28(p, 4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}

int func_02075c00(void *arg)
{
    void *p;
    int a;
    int b;

    func_02073044();
    if (func_020ebf70() && func_02077a8c((int) arg)) {
        p = data_020ccf94;
        a = func_02073d28(p, 4);
        func_02077b3c(a, 0, 11);
        b = func_02073d28(p, 4);
        return func_02073e30(p, b, 1, (int) arg, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}

int func_02075b98(void)
{
    void *obj;
    int ret;

    func_02073044();
    if (func_020ebf70() != 0 && func_02077a8c(1) != 0) {
        obj = data_020ccf94;
        func_02073918(obj, 0);
        func_02077b3c(func_02073d28(obj, 4), 0, 9);
        ret = func_02073d28(obj, 4);
        return func_02073e30(obj, ret, 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}

int func_02075b14(int arg)
{
    int *ptr;
    int val, temp;
    int local[2];

    if (((int) func_02073044(), func_020ebf70()) != 0 && func_02077a8c(arg) != 0) {
        ptr = (*(int **) &data_020ccf94);
        func_02073918((void *) ptr, 0);
        val = func_02073d28((void *) ptr, 4);
        func_02077b3c(val, 0, 10);
        local[0] = 0;
        local[1] = 0;
        func_0209e474(local);
        MI_CpuCopy8((const void *) local, (void *) (val + 1), 8);
        temp = func_02073d28((void *) ptr, 4);
        return func_02073e30((void *) ptr, temp, 9, arg, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}

int func_02075aa4(int a, void *p1)
{
    unsigned char *g;
    unsigned char *t;

    if (p1 == 0) {
        goto one;
    }
    func_02073044();
    if (func_020ebf70() == 0) {
        goto zero;
    }
    if (func_02077a8c((int) p1) == 0) {
        goto zero;
    }
    g = (*(unsigned char **) &data_020ccf94);
    t = (unsigned char *) func_02073d28((void *) g, 4);
    func_02077b3c((int) t, 0, 0xe);
    t[1] = (unsigned char) a;
    return func_02073e30((void *) g, (int) ((unsigned char *) func_02073d28((void *) g, 4)), 2, (int) p1, 0, 0, 0, 0, 0, 0);
zero:
    return 0;
one:
    return 1;
}

int func_020759e0(int bit)
{
    int mask;
    u8 *p;
    int n;
    unsigned int i;
    void *h;
    u8 buf[12];

    mask = (u16) (1 << bit);
    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(mask) == 0) {
        goto fail;
    }
    p = (u8 *) func_02073d28(data_020ccf94, 4);
    n = 0;
    func_02077b3c((int) p, n, 0xf);
    p++;
    n++;
    for (i = 0; i < 4; i++) {
        func_020a6e4c(i, &buf[0], &buf[1], &buf[2]);
        func_020a7880(&buf[3]);
        func_020a7850(&buf[3], buf[0], buf[1], buf[2], 7);
        MI_CpuCopy8(&buf[3], p, 2);
        p += 2;
        n += 2;
        func_020a7870(&buf[3]);
    }
    h = data_020ccf94;
    return func_02073e30(h, (int) ((u8 *) func_02073d28(h, 4)), n, mask, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}

int func_02075978(void)
{
    void *p;
    int v2;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }

    p = data_020ccf94;
    func_02073918(p, 0);
    func_02077b3c(func_02073d28(p, 4), 0, 16);
    v2 = func_02073d28(p, 4);
    return func_02073e30(p, v2, 1, 1, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}

int func_02075918(void)
{
    void *p;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }

    p = data_020ccf94;
    func_02077b3c(func_02073d28(p, 4), 0, 0x11);
    return func_02073e30(p, func_02073d28(p, 4), 1, 1, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}

int func_020758ac(void *a0)
{
    void *o;

    if (((int) func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c((int) a0) == 0) {
        goto fail;
    }
    o = data_020ccf94;
    func_02073918(o, 0);
    func_02077b3c(func_02073d28(o, 4), 0, 0x12);
    return func_02073e30(o, func_02073d28(o, 4), 1, (int) a0, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}

int func_02075848(void)
{
    void *o;
    if (((int) func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }
    o = data_020ccf94;
    func_02077b3c(func_02073d28(o, 4), 0, 0x13);
    func_020740dc();
    return func_02073e30(o, func_02073d28(o, 4), 1, 1, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}

int func_020757e0(void)
{
    int ret;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }
    {
        void *obj = data_020ccf94;
        func_02073918(obj, 0);
        func_02077b3c((int) ((void *) func_02073d28(obj, 4)), 0, 0x14);
        ret = func_02073e30(obj, (int) ((void *) func_02073d28(obj, 4)), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    goto exit;
fail:
    ret = 0;
exit:
    return ret;
}

int func_020757ac(void *param)
{
    int x;
    x = func_0209847c((int) func_02096284((*(struct UnkStruct_020757ac {
                                              char pad_00[0x68];
                                              void *unk_68;
                                          } **) &data_020ccf94)
                                              ->unk_68));
    return func_02075ff8((int) param, x, 0x249c, 0x15, 1);
}

int func_02075774(int param1)
{
    int ret;

    ret = func_020989e0(func_0209847c((int) func_02096284((*(struct UnkStruct_02075774 {
                                                              char pad_00[0x68];
                                                              void *unk_68;
                                                          } **) &data_020ccf94)
                                                              ->unk_68)));
    return func_02075ff8(param1, ret, 0x3200, 0x16, 1);
}

int func_0207570c(void)
{
    void *p;
    int v2;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }

    p = data_020ccf94;
    func_02073918(p, 0);
    func_02077b3c(func_02073d28(p, 4), 0, 23);
    v2 = func_02073d28(p, 4);
    return func_02073e30(p, v2, 1, 1, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}

void func_020756cc(unsigned char *payload, unsigned int length, int player)
{
    int a = func_020b65c4();
    if (a == 12) {
        int b = (a, func_020a132c());
        if (b != 0) {
            unsigned char c = *payload;
            int d = (b, func_020a132c());
            func_020a127c((((int) (func_020a1284(d, (unsigned short) (c & 0xf)), d)), func_020a132c()),
                          (unsigned char) ((c >> 6) & 3));
        }
    }
}

void func_02075670(unsigned char *payload, unsigned int length, int player)
{
    u32 local;
    void *base;
    u32 ret;
    u32 limit;

    if (func_020b65c4() != 0xc) {
        return;
    }

    MI_CpuCopy8(payload, &local, 4);

    base = (void *) func_020a1350();

    MI_CpuCopy8(payload + 4, (u8 *) base + local, length - 4);

    ret = (u32) func_020a00fc((int) base);

    if (ret == 0) {
        limit = 0x17400;
    } else {
        limit = ret + 4;
    }

    if (local + (length - 4) < limit) {
        return;
    }

    func_020a003c(func_020a1338(), 0);
}

void func_0207560c(unsigned char *payload, unsigned int length, int player)
{
    if (length != 0) {
        int local;
        char *val;
        MI_CpuCopy8((const void *) payload, (void *) (&local), 4);
        val = (char *) func_02090040(player);
        MI_CpuCopy8((const void *) (payload + 4), (void *) (val + local), length - 4);
    } else {
        func_02090174((char *) func_02090040(player));
    }
    if (func_020b65c4() == 13 || func_020b65c4() == 47) {
        if (func_020a132c() != 0) {
            func_020a242c(func_020a132c(), player, 1);
        }
    }
}

void func_020755b4(unsigned char *payload, unsigned int length, int player)
{
    if (length == 1) {
        if (*payload != 0) {
            func_02090174((char *) (func_02090040(4)));
        }
    } else {
        MI_CpuCopy8((const void *) payload, (void *) (func_02090040(4)), 0x950);
    }
    if (func_020b65c4() != 0x2e) {
        return;
    }
    if (func_020a132c() == 0) {
        return;
    }
    func_020a242c(func_020a132c(), (*(unk_struct **) &data_020ccf94)->unk_64, 1);
}

void func_0207557c(unsigned char *payload, unsigned int length, int player)
{
    int local;
    int p2_plus_3;
    int r;

    MI_CpuCopy8(payload, &local, 4);
    p2_plus_3 = player + 3;
    r = func_0209847c(p2_plus_3);
    MI_CpuCopy8(payload + 4, (void *) (r + local), length - 4);
    func_020962a4(player, p2_plus_3);
}

void func_0207556c(unsigned char *payload, unsigned int length, int player)
{
    func_020a6f74(player, *payload);
}
