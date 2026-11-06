/* outdoor_villager_watch: 12 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02266c1c @ 0x02266c1c, 0x18 bytes, Thumb
 * func_ov068_02266be4 @ 0x02266be4, 0x38 bytes, Thumb
 * func_ov068_02266bac @ 0x02266bac, 0x36 bytes, Thumb
 * func_ov068_02266b6c @ 0x02266b6c, 0x3e bytes, Thumb
 * func_ov068_02266b3c @ 0x02266b3c, 0x2e bytes, Thumb
 * func_ov068_02266b04 @ 0x02266b04, 0x38 bytes, Thumb
 * func_ov068_02266aa0 @ 0x02266aa0, 0x64 bytes, Thumb
 * func_ov068_02266a70 @ 0x02266a70, 0x30 bytes, Thumb
 * func_ov068_02266a24 @ 0x02266a24, 0x4c bytes, Thumb
 * func_ov068_02266a00 @ 0x02266a00, 0x22 bytes, Thumb
 * func_ov068_022669c4 @ 0x022669c4, 0x3c bytes, Thumb
 * func_ov068_02266968 @ 0x02266968, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x14];
    unsigned short count;
} UnkStruct_02266c1c;

struct UnkStruct_02266be4 {
    unsigned char pad_00[8];
    unsigned char unk_08;
};

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
} UnkStruct_02266b04;

struct UnkStruct_022669c4;

struct UnkStruct_022669c4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
};

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
} FuncStruct5;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x3b0];
    int unk_40C;
} FuncStruct4;

extern void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, unsigned char h);
extern int func_ov003_0222f458(int x, unsigned char y);
extern int func_020ea990(int x, int y);
extern int func_ov003_0222f524(u8 *, u8);
extern int data_020c814c;
extern void func_0201ad78(void *a, void *b);
extern void func_ov068_02266c70(void *a, void *b);
extern int func_ov003_02227608(int a, int b);
extern int func_ov003_02227638(int);

void func_ov068_02266c1c(UnkStruct_02266c1c *self)
{
    if (++self->count > 0x960) {
        self->count = 0x960;
    }
}

void func_ov068_02266be4(struct UnkStruct_02266be4 *out, char *base, unsigned char p3, int p4, int p5, int p6, int p7, int p8,
                         unsigned char p9)
{
    func_0201ad18((void *) (base + 0x3b0), p3, p4, p5, p6, p7, p8, p9);
    out->unk_08 = p3;
}

int func_ov068_02266bac(int a0, int a1, int a2, int a3, int a4)
{
    int res = func_ov003_0222f458(a1, (unsigned char) a2);
    if (res == -1) {
        goto fail;
    }
    if (func_020ea990(a3, a1) >= a4) {
        goto fail;
    }
    return res;
fail:
    return -1;
}

int func_ov068_02266b6c(int a, int b, int *out, int c, int d)
{
    int i;
    int res;
    for (i = 0; i < 8; i++) {
        res = func_ov068_02266bac(a, b, i, c, d);
        if (res == -1) {
            continue;
        }
        *out = i;
        return res;
    }
    return -1;
}

int func_ov068_02266b3c(int unused, int a1, int a2)
{
    u8 t;
    int res;

    if (a2 != -1) {
        t = 0;
        res = func_ov003_0222f524(&t, (u8) a1);
        if (res == a2) {
            return 1;
        }
    }
    return 0;
}

void func_ov068_02266b04(UnkStruct_02266b04 *p, int a, int b, int c, int d)
{
    p->unk_0C = b;
    p->unk_10 = c;
    func_ov068_02266be4((struct UnkStruct_02266be4 *) p, (char *) a, 3, 0, 0, d, 4, data_020c814c, 1);
    p->unk_04 = 0;
    p->unk_14 = 0;
}

void func_ov068_02266aa0(void *r5, void *r4)
{
    int r0;
    int r1;
    int r2;
    int r3;
    int sp[4];
    int *sp_ptr;

    r0 = func_ov068_02266b3c((int) r5, *(int *) ((char *) r5 + 0xc), *(int *) ((char *) r5 + 0x10));
    if (r0 != 0) {
        r0 = func_ov068_02266bac((int) r5, (int) sp, *(int *) ((char *) r5 + 0xc), (int) ((char *) r4 + 0x5c),
                                 *(int *) ((char *) r4 + 0x40c));
        r1 = -1;
        if (r0 != r1) {
            r1 = *(int *) ((char *) r5 + 0x10);
            if (r0 == r1) {
                func_0201ad78((char *) r4 + 0x3b0, sp);
                goto done;
            }
        }
        func_ov068_02266c70(r5, r4);
    } else {
        func_ov068_02266c70(r5, r4);
    }
done:
    return;
}

int func_ov068_02266a70(int unused, int p1, int p2, int p3, int p4)
{
    if (func_ov003_02227608(p1, p2) != 0 && func_020ea990(p3, p1) < p4) {
        return 1;
    }
    return 0;
}

int func_ov068_02266a24(int a, int b, int *out, int c, int d)
{
    int i = 0;
    int id = i;
    int ret;

    for (; i < 6; i++) {
        ret = func_ov003_02227638(i);
        if (ret != ~id) {
            if (func_ov068_02266a70(a, b, i, c, d)) {
                *out = i;
                return ret;
            }
        }
    }
    return -1;
}

int func_ov068_02266a00(int unused, int key, int value)
{
    int result = func_ov003_02227638(key);
    if (result != -1 && value == result) {
        return 1;
    }
    return 0;
}

void func_ov068_022669c4(struct UnkStruct_022669c4 *obj, int param1, int param2, int param3, int param4)
{
    obj->unk_0C = param2;
    obj->unk_10 = param3;
    func_ov068_02266be4((struct UnkStruct_02266be4 *) obj, (char *) param1, 3, 0, 0, param4, 4, data_020c814c, 1);
    obj->unk_04 = 1;
    obj->unk_14 = 0;
}

void func_ov068_02266968(FuncStruct5 *r5, FuncStruct4 *r4)
{
    unsigned char buf[0x10];

    if (func_ov068_02266a00((int) r5, r5->unk_0C, r5->unk_10)) {
        if (func_ov068_02266a70((int) r5, (int) buf, r5->unk_0C, (int) ((char *) r4 + 0x5c), r4->unk_40C)) {
            func_0201ad78((char *) r4 + 0x3b0, buf);
        } else {
            func_ov068_02266c70(r5, r4);
        }
    } else {
        func_ov068_02266c70(r5, r4);
    }
}
