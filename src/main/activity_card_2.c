/* activity_card_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a20b4 @ 0x020a20b4, 0x6c bytes, Thumb
 * func_020a1f4c @ 0x020a1f4c, 0x168 bytes, Thumb
 * func_020a1ee0 @ 0x020a1ee0, 0x6c bytes, Thumb
 * func_020a1e08 @ 0x020a1e08, 0xd8 bytes, Thumb
 * func_020a1d94 @ 0x020a1d94, 0x74 bytes, Thumb
 * func_020a1d54 @ 0x020a1d54, 0x40 bytes, Thumb
 * func_020a1cec @ 0x020a1cec, 0x68 bytes, Thumb
 * func_020a1c9c @ 0x020a1c9c, 0x50 bytes, Thumb
 * func_020a1c90 @ 0x020a1c90, 0xc bytes, Thumb
 * func_020a1bdc @ 0x020a1bdc, 0xb4 bytes, Thumb
 * func_020a1bd0 @ 0x020a1bd0, 0xc bytes, Thumb
 * func_020a1b68 @ 0x020a1b68, 0x68 bytes, Thumb
 * func_020a1acc @ 0x020a1acc, 0x9c bytes, Thumb
 * func_020a1a40 @ 0x020a1a40, 0x8c bytes, Thumb
 * func_020a19c0 @ 0x020a19c0, 0x80 bytes, Thumb
 * func_020a199c @ 0x020a199c, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1;
    unsigned char unk_A2;
    unsigned char pad_A3;
    short unk_A4;
    unsigned short pad_A6;
    unsigned int unk_A8;
    unsigned int pad_AC;
    unsigned int unk_B0;
} UnkStruct_020a20b4;

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x13];
    int int_b4;
} UnkStruct_020a1ee0;

struct UnkStruct_020a1e08 {
    u8 pad_00[0xa0]; // 0x00-0x9f
    u8 unk_A0;       // 0xa0
    u8 unk_A1;       // 0xa1
    u8 unk_A2;       // 0xa2
    u8 unk_A3;       // 0xa3
    s16 unk_A4;      // 0xa4
    u8 pad_A6[2];    // 0xa6-0xa7
    u32 unk_A8;      // 0xa8
    u8 pad_AC[4];    // 0xac-0xaf
    u32 unk_B0;      // 0xb0
    u32 unk_B4;      // 0xb4
};

struct UnkStruct_020a1d94 {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    char pad_A1[3];
    short unk_A4;
    char pad_A6[2];
    int unk_A8;
    char pad_AC[4];
    int unk_B0;
};

typedef struct {
    char pad_00[0xa0];
    unsigned char unk_A0;
    char pad_A1[0x0f];
    unsigned int unk_B0;
} UnkStruct_020a1d54;

struct UnkStruct_020a1b68 {
    char pad_00[0xb0];
    int unk_B0;
};

typedef struct UnkStruct_020a1acc {
    unsigned char pad_00[0xb4];
    int unk_B4;
} UnkStruct_020a1acc;

extern unsigned int func_020a1368(void);
extern void MI_CpuCopy8(unsigned int, unsigned int, unsigned int);
extern unsigned int data_020d1bf0[];
extern unsigned int data_020d1c08[];
extern unsigned char data_021dc7a8[];
extern int func_020508fc(u8 *p, int n, int v);
extern void func_0209fafc(u8 *p);
extern void func_0209fb70(int *p);
extern int func_020a1738(int a, int *p);
extern int func_0209faf4(int *p);
extern void func_0209faf8(u8 *p, int v);
extern void func_0209fb6c(int *p);
extern int func_0209015c(u8 *p);
extern void func_02090168(u8 *p, int v);
extern int func_0208ffe8(u8 *p);
extern void func_0208fff4(u8 *p, int v);
extern int func_02098844(u8 *p, int i);
extern u8 *func_02099664(int);
extern u8 *func_02099658(int);
extern int func_02077bb8(u8 *p);
extern void func_02077bc0(u8 *p, int v);
extern int func_02077c9c(u8 *p);
extern void func_02077ca8(u8 *p, int v);
extern int func_0209faec(u8 *p);
extern void func_0209faf0(u8 *p, int v);
extern unsigned short func_02050920(u8 *p, int n);
extern int func_02050974(void *p);
extern void func_02050948(void *p);
extern int func_020509a8(void *p, int a, int b, int c);
extern void MI_CpuFill8(int a, int b, int c);
extern int data_020d1c20[];
extern int func_02050a84(void *p, int a, int b, int c);
extern unsigned char data_021c8188[];
extern int func_020a16e0(void);
extern u8 **data_021f3c3c;
extern int func_0209f180(u8 *p);
extern int func_02050a10(void *, int, int, int);

int func_020a1c90(int a);
int func_020a1bdc(void *a0, void *a1);
void func_020a1bd0(int a);
int func_020a1b68(unsigned int a, int b);
int func_020a1acc(UnkStruct_020a1acc *self, int idx);
int func_020a199c(int unused, const unsigned char *a, const unsigned char *b, int n);

int func_020a20b4(UnkStruct_020a20b4 *self, int idx)
{
    unsigned int arr[3];

    arr[0] = (unsigned int) data_021dc7a8;
    arr[1] = (unsigned int) data_021dc7a8;
    arr[2] = func_020a1368();
    MI_CpuFill8(self->unk_B0, 0, data_020d1bf0[idx]);
    MI_CpuCopy8(arr[idx], self->unk_B0, data_020d1c08[idx]);
    self->unk_A2 = 0;
    self->unk_A4 = -1;
    self->unk_A8 = 0;
    self->unk_A0 = 1;
    return 3;
}

int func_020a1f4c(u8 *self, int a)
{
    u8 *b;
    u8 *c;
    int k;
    int i;
    u8 *p;
    int loc;

    if (a == 2) {
        c = *(u8 **) (self + 0xb0);
        *(u16 *) (c + 0xc802) = (u16) func_020508fc(c, 0xc804, *(u16 *) (c + 0xc802));
    } else {
        k = 0;
        if (a == 1) {
            k = func_020a1acc((UnkStruct_020a1acc *) self, 0);
        }
        if (k == 3) {
            return 3;
        }
        if (k == 1) {
            return 1;
        }
        b = *(u8 **) (self + 0xb0);
        if (a == 0) {
            func_0209fafc(b + 0x173f8);
        } else if (k == 0) {
            func_0209fb70(&loc);
            func_020a1738(0, &loc);
            func_0209faf8(b + 0x173f8, func_0209faf4(&loc));
            func_0209fb6c(&loc);
        }
        p = b + 0x11c70;
        func_02090168(p, func_020508fc(p, 0x950, func_0209015c(p)));
        p = b + 0x1704c;
        func_0208fff4(p, func_020508fc(p, 0x104, func_0208ffe8(p)));
        for (i = 0; i < 4; i++) {
            p = func_02099664((int) func_02098844(b + 0x14, i));
            func_02077bc0(p, func_020508fc(p, 0x50, func_02077bb8(p)));
            p = func_02099658((int) func_02098844(b + 0x14, i));
            func_02077ca8(p, func_020508fc(p, 0x484, func_02077c9c(p)));
        }
        func_0209faf0(b + 0x173f8, func_020508fc(b, 0x173fc, func_0209faec(b + 0x173f8)));
        func_02050920(b, 0x173fc);
        func_02050920(b, 0x173fc);
    }
    self[0xa0] = 2;
    return 3;
}

int func_020a1ee0(UnkStruct_020a1ee0 *base, int idx)
{
    int status = func_02050974(((char *) data_021c8188));
    int arr1 = data_020d1c20[idx];
    int arr2 = ((int *) data_020d1bf0)[idx];

    if (status == 1) {
        func_02050948(((char *) data_021c8188));
        return 1;
    } else if (status == 4) {
        MI_CpuFill8(base->int_b4, 0, arr2);
        func_020509a8(((char *) data_021c8188), base->int_b4, arr2, arr1);
    } else if (status == 3) {
        // nothing
    } else {
        func_02050948(((char *) data_021c8188));
        base->unk_A0 = 3;
    }
    return 3;
}

int func_020a1e08(struct UnkStruct_020a1e08 *p, int idx)
{
    s32 val, q, r, inc, res;

    val = ((s32 *) data_020d1bf0)[idx];
    q = val / 0x200;
    r = val % 0x200;

    while (p->unk_A2 <= q) {
        inc = 0x200;
        if (p->unk_A2 == q) {
            inc = r;
        }
        res = func_020a199c((int) p, (const unsigned char *) (p->unk_B0 + (s32) p->unk_A2 * 0x200), (const unsigned char *) (p->unk_B4 + (s32) p->unk_A2 * 0x200), inc);

        if (res == 0) {
            if (p->unk_A4 == -1) {
                p->unk_A4 = p->unk_A2;
            }
            p->unk_A8 += inc;
            if (p->unk_A2 == q) {
                p->unk_A0 = 4;
                p->unk_A2 = (u8) (p->unk_A2 + 1);
                return 3;
            }
        } else {
            if (p->unk_A8 != 0) {
                p->unk_A0 = 4;
                return 3;
            }
        }

        p->unk_A2 = (u8) (p->unk_A2 + 1);
    }

    if (p->unk_A2 > q) {
        p->unk_A0 = 5;
    }

    return 3;
}

int func_020a1d94(struct UnkStruct_020a1d94 *s, int idx)
{
    int status;
    int shift;
    int table_val;

    status = func_02050974((void *) data_021c8188);
    table_val = data_020d1c20[idx];

    if (status == 1) {
        func_02050948((void *) data_021c8188);
        return 1;
    }

    if (status == 4) {
        shift = s->unk_A4 << 9;
        func_02050a84((void *) data_021c8188, shift + table_val, s->unk_B0 + shift, s->unk_A8);
    } else if (status != 3) {
        func_02050948((void *) data_021c8188);
        s->unk_A4 = -1;
        s->unk_A8 = 0;
        s->unk_A0 = 3;
    }

    return 3;
}

int func_020a1d54(UnkStruct_020a1d54 *self, int idx)
{
    unsigned int arr[3];
    arr[0] = (unsigned int) data_021dc7a8;
    arr[1] = (unsigned int) data_021dc7a8;
    arr[2] = func_020a1368();
    MI_CpuCopy8(self->unk_B0, arr[idx], data_020d1c08[idx]);
    self->unk_A0 = 6;
    return 3;
}

int func_020a1cec(void *a, int b)
{
    int x = func_02050974((void *) (((int *) data_021c8188)));
    int v2 = data_020d1c20[b];
    int v1 = ((int *) data_020d1bf0)[b];

    if (x == 1) {
        func_02050948((void *) (((int *) data_021c8188)));
        return 1;
    }
    if (x == 4) {
        MI_CpuFill8(*(int *) ((char *) a + 0xb0), 0xff, v1);
        func_02050a84((void *) (((int *) data_021c8188)), v2, *(int *) ((char *) a + 0xb0), v1);
    } else if (x == 3) {
        // nothing
    } else {
        func_02050948((void *) (((int *) data_021c8188)));
        return 0;
    }
    return 3;
}

int func_020a1c9c(void)
{
    int a = func_020a1c90(0);
    int b = func_020a1c90(1);
    if (a == 1 || b == 1) {
        return 1;
    }
    if (a != 0 && b != 0) {
        return 4;
    }
    if (a != 0) {
        func_020a1bd0(1);
    } else {
        if (b != 0) {
            func_020a1bd0(0);
        } else {
            func_020a1bd0(func_020a16e0());
        }
    }
    return 0;
}

int func_020a1c90(int a)
{
    return func_020a1bdc((void *) a, 0);
}

int func_020a1bdc(void *a0, void *a1)
{
    volatile char pad[4];
    u8 *b;
    u8 *p;
    int r;
    int t;
    int i;

    if (a1 != 0 && data_021f3c3c == 0) {
        return 1;
    }
    r = func_020a1b68((unsigned int) a0, (int) a1);
    if (r != 0) {
        goto done;
    }
    if (a1 != 0) {
        b = *(u8 **) ((char *) data_021f3c3c + 0xb0);
    } else {
        b = ((u8 *) data_021dc7a8);
    }
    t = (int) func_02050920(b, 0x173fc);
    if (func_0209f180(b) == 0) {
        return 4;
    }
    if (t == 0) {
        func_02050920(b + 0x11c70, 0x950);
        i = 0;
        p = b + 0x14;
        do {
            func_02050920(func_02099664((int) func_02098844(p, i)), 0x50);
            func_02050920(func_02099658((int) func_02098844(b + 0x14, i)), 0x484);
            i++;
        } while (i < 4);
    } else {
        return 4;
    }
done:
    return r;
}

void func_020a1bd0(int a)
{
    func_020a1b68(a, 0);
}

int func_020a1b68(unsigned int a, int b)
{
    int arr[3];
    int v, w, x;
    struct UnkStruct_020a1b68 *p;

    arr[0] = (int) ((char *) data_021dc7a8);
    arr[1] = (int) ((char *) data_021dc7a8);
    arr[2] = (int) func_020a1368();

    v = arr[a];
    x = data_020d1c20[a];
    w = ((int *) data_020d1bf0)[a];

    if (b != 0 && a <= 1) {
        p = (*(struct UnkStruct_020a1b68 * *) &data_021f3c3c);
        if (p == 0) {
            return 1;
        }
        v = p->unk_B0;
    }

    return func_02050a10(((char *) data_021c8188), v, w, x) != 0;
}

int func_020a1acc(UnkStruct_020a1acc *self, int idx)
{
    int type;
    int a, b;

    type = func_02050974(((int *) data_021c8188));
    a = data_020d1c20[idx];
    b = ((int *) data_020d1bf0)[idx];

    if (type == 4) {
        MI_CpuFill8(self->unk_B4, 0, b);
        func_020509a8(((int *) data_021c8188), self->unk_B4, b, a);
        goto ret3;
    }
    if (type == 3) {
        goto case3;
    }

    func_02050948(((int *) data_021c8188));
    if (func_0209f180((u8 *) ((*(UnkStruct_020a1acc * *) &data_021f3c3c)->unk_B4)) == 0) {
        return 4;
    }
    if ((int) func_02050920((u8 *) self->unk_B4, ((int *) data_020d1c08)[idx]) != 0) {
        goto ret4b;
    }
    return 0;
ret4b:
    return 4;

case3:
    if (type == 1) {
        func_02050948(((int *) data_021c8188));
        return 1;
    }
ret3:
    return 3;
}

int func_020a1a40(int a, void *b)
{
    int r;
    int v7;
    int v6;
    int t;

    r = func_02050974(((int *) data_021c8188));
    v7 = data_020d1c20[a];
    v6 = ((int *) data_020d1bf0)[a];
    if (r == 4) {
        MI_CpuFill8((int) b, 0, v6);
        func_020509a8(((int *) data_021c8188), (unsigned int) b, v6, v7);
    } else {
        if (r != 3) {
            func_02050948(((int *) data_021c8188));
            t = func_02050920((u8 *) ((unsigned short *) b), ((int *) data_020d1c08)[a]);
            if (func_0209f180((u8 *) ((unsigned char *) b)) == 0) {
                return 4;
            }
            if (t == 0) {
                return 0;
            }
            return 4;
        }
        if (r == 1) {
            func_02050948(((int *) data_021c8188));
            return 1;
        }
    }
    return 3;
}

int func_020a19c0(int unused, int idx)
{
    void *local[3];
    void *p;
    int v, a, b;

    local[0] = ((char *) data_021dc7a8);
    local[1] = ((char *) data_021dc7a8);
    local[2] = (void *) func_020a1368();

    p = local[idx];
    v = func_02050974(((char *) data_021c8188));
    a = data_020d1c20[idx];
    b = ((int *) data_020d1bf0)[idx];

    if (v == 4) {
        func_020509a8(((char *) data_021c8188), (int) p, b, a);
    } else if (v == 1) {
        func_02050948(((char *) data_021c8188));
        return 1;
    } else if (v == 3) {
        // nothing
    } else {
        func_02050948(((char *) data_021c8188));
        if ((int) func_02050920((u8 *) p, ((int *) data_020d1c08)[idx]) == 0) {
            return 0;
        } else {
            return 4;
        }
    }
    return 3;
}

int func_020a199c(int unused, const unsigned char *a, const unsigned char *b, int n)
{
    while (n != 0) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
        n--;
    }
    return 1;
}
