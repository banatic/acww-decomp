/* town_day_3: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02047db8 @ 0x02047db8, 0x1c bytes, Thumb
 * func_02047c98 @ 0x02047c98, 0x120 bytes, Thumb
 * func_02047c1c @ 0x02047c1c, 0x7c bytes, Thumb
 * func_02047bf8 @ 0x02047bf8, 0x24 bytes, Thumb
 * func_02047bc8 @ 0x02047bc8, 0x2e bytes, Thumb
 * func_02047ac0 @ 0x02047ac0, 0x108 bytes, Thumb
 * func_02047a8c @ 0x02047a8c, 0x32 bytes, Thumb
 * func_02047a28 @ 0x02047a28, 0x64 bytes, Thumb
 * func_020479f0 @ 0x020479f0, 0x36 bytes, Thumb
 * func_020479e0 @ 0x020479e0, 0x10 bytes, Thumb
 * func_0204790c @ 0x0204790c, 0xd4 bytes, Thumb
 * func_02047898 @ 0x02047898, 0x74 bytes, Thumb
 * func_02047854 @ 0x02047854, 0x42 bytes, Thumb
 * func_020477e4 @ 0x020477e4, 0x70 bytes, Thumb
 * func_02047730 @ 0x02047730, 0xb2 bytes, Thumb
 * func_02047688 @ 0x02047688, 0xa8 bytes, Thumb
 * func_0204763c @ 0x0204763c, 0x4c bytes, Thumb
 * func_0204762c @ 0x0204762c, 0x10 bytes, Thumb
 * func_020475b0 @ 0x020475b0, 0x7c bytes, Thumb
 * func_02047500 @ 0x02047500, 0xb0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    u16 unk_00;
} Entry;

typedef struct UnkStruct_02047ac0 {
    u16 id;
} UnkStruct_02047ac0;

typedef struct Pair_02047ac0 {
    int a;
    int b;
} Pair_02047ac0;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0204790c;

typedef struct {
    unsigned short a;
    unsigned char b;
    unsigned char pad_03;
    unsigned int c;
    unsigned int d;
} Entry_020477e4;

typedef struct {
    unsigned int w[2];
} Slot;

typedef struct {
    unsigned int unk_00, w1;
} Pair_02047688;

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
} FieldStruct;

typedef struct {
    int x;
    int y;
} UnkStruct_0204763c;

extern int func_020644cc(int);
extern Entry *func_0204f5e0(int param1, int a, int b, int c, int d, int e);
extern int func_0204b910(Entry *e);
extern void func_0204f800(int *out0, int *out1, int a, int b, int c, int d);
extern void func_0204a25c(int param1, int x, int y, int z, int zero);
extern const u8 data_020ca57c[];
extern int func_02047dd4(int, int, int, int, int, int, int);
extern char data_021c7a08[];
extern void func_0204886c(int a, int b, int c, int d);
extern void func_020466a0(int, int);
extern void func_02046680(void);
extern int func_0204cb50(void *ptr, int);
extern unsigned char data_021f39fc[];
extern UnkStruct_0204790c *func_0203fc70(void);
extern void func_0209df7c(unsigned int *t);
extern int func_0209fa30(int v);
extern void func_020b2ec8(void);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, const void *, int);
extern int func_0203fc78(unsigned char, void *, int);
extern void func_020b2f28(void);
extern void func_020b2f08(void);
extern void func_020b2ee8(void);
extern unsigned char data_020db764[];
extern void func_020b2eb8(void);
extern void *func_0204cc04(int);
extern int func_0209dee8(void);
extern void func_0204cbc0(int, unsigned short);
extern int func_020b2f18(void);
extern void func_020b2ef8(void);
extern void func_020b2ed8(void);
extern int func_020b2a90(void);
extern unsigned char data_021f3a50[];
extern char data_021dc7a8[];
extern int func_0203fae4(void);
extern int func_020984e8(void);
extern void func_0209df38(Pair_02047688 *p);
extern void func_0209e100(Pair_02047688 *p, int n);
extern int data_021c79c4;
FieldStruct *func_0204e414(void);
int func_0204a3cc(int *g, FieldStruct *b);
extern unsigned char data_021c779c[];

unsigned short func_02047db8(int object)
{
    unsigned int x = 0x1542;
    x += func_020644cc(5);
    return (unsigned short) x;
}

void func_02047c98(int param0, int param1, int param2, int param3)
{
    Pair arr[256];
    Pair *p;
    int r5, r6;
    int count;
    int out0, out1;
    int local_y;
    int zero1;
    int zero2;

    p = arr;
    do {
        p->x = 0;
        p->y = 0;
        p++;
    } while (p != arr + 256);
    count = 0;

    for (r6 = 0; r6 < 16; r6++) {
        for (r5 = 0; r5 < 16; r5++) {
            Entry *e = func_0204f5e0(param1, param2 + 1, param3 + 1, r5, r6, 0);
            if (e != 0) {
                int valid = 0;
                u16 f = e->unk_00;
                if (f >= 0x26 && f <= 0x2a) {
                    valid = 1;
                }
                if (valid != 0 || (f >= 0x66 && f <= 0x68)) {
                    if (func_0204b910(e) != 0) {
                        func_0204f800(&out0, &out1, param2 + 1, param3 + 1, r5, r6);
                        arr[count].x = out0;
                        arr[count].y = out1;
                        count++;
                    }
                }
            }
        }
    }

    if (count > 0) {
        int idx = func_020644cc(count);
        Pair *base = &arr[idx];
        const u8 *table = data_020ca57c;
        int i;
        zero1 = 0;
        zero2 = 0;

        for (i = 0; i < 3; i++) {
            u8 b = *table;
            int x = base->x + ((b >> 4) - 8);
            int y = base->y + ((b & 0xf) - 8);
            int tile_x = x >> 4;
            int tile_y = y >> 4;
            int sub_y = y - (tile_y << 4);
            int sub_x = x - (tile_x << 4);
            Entry *e;
            local_y = y;
            e = func_0204f5e0(param1, tile_x, tile_y, sub_x, sub_y, zero2);
            if (e != 0 && e->unk_00 == 0xfff1) {
                int z = func_02047db8(param0);
                func_0204a25c(param1, x, local_y, z, zero1);
            }
            table++;
        }
    }
}

void func_02047c1c(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    int n = func_02047dd4(a0, 16, a2, a5, a6, a7, a8);
    int r5, r4;

    while (n != 0) {
        for (r4 = 0; r4 < a4; r4++) {
            int off = r4;
            off *= 36;
            for (r5 = 0; r5 < a3; r5++) {
                if (((int) (*(int *) ((char *) data_021c7a08 + r5 * 144 + off + 0x20)) << 20) >> 31) {
                    func_02047c98(a0, a1, r5, r4);
                }
            }
        }
        n--;
    }
}

void func_02047bf8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    func_02047c1c(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void func_02047bc8(int a, int b, int c, int d, int e, int f, int g)
{
    int x;
    x = func_02047dd4(a, 14, c, d, e, f, g);
    func_0204886c(a, b, 1, x);
}

void func_02047ac0(void *self, void *a1, int a2, int a3)
{
    int cnt;
    int o1;
    int o2;
    Pair_02047ac0 arr[256];
    Pair_02047ac0 *pp;
    int x;
    int y;
    int n;
    int k;
    int r;
    UnkStruct_02047ac0 *e;
    int t;

    pp = arr;
    do {
        pp->a = 0;
        pp->b = 0;
        pp++;
    } while (pp != arr + 256);
    n = 0;
    cnt = 0;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            e = (UnkStruct_02047ac0 *) func_0204f5e0((int) a1, a2 + 1, a3 + 1, x, y, 0);
            if (e) {
                t = (e->id >= 0x5d && e->id <= 0x61);
                if (t && func_0204b910((Entry *) e)) {
                    func_0204f800(&o1, &o2, a2 + 1, a3 + 1, x, y);
                    arr[n].a = o1;
                    arr[n].b = o2;
                    n++;
                } else if (e->id == 0x6d) {
                    cnt++;
                }
            }
        }
    }
    for (k = 3 - cnt; k != 0; k--) {
        if (n > 0) {
            r = func_020644cc(n);
            func_0204a25c((int) a1, arr[r].a, arr[r].b, 0x6d, 0);
            func_020466a0(arr[r].a, arr[r].b);
            arr[r].a = arr[n - 1].a;
            arr[r].b = arr[n - 1].b;
            n--;
        }
    }
}

void func_02047a8c(int a, int b, int count)
{
    int j, i;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < count; j++) {
            func_02047ac0((void *) a, (void *) b, j, i);
        }
    }
}

void func_02047a28(int p0, int p1, int p2, int p3)
{
    int z2 = 0;
    int z1 = 0;
    int inner = 0;
    int outer = 0;
    do {
        inner = 0;
        do {
            unsigned short *r = (unsigned short *) func_0204f5e0(p1, p2 + 1, p3 + 1, inner, outer, z1);
            if (r != 0 && *r == 0x6d) {
                int out1, out2;
                func_0204f800(&out1, &out2, p2 + 1, p3 + 1, inner, outer);
                func_0204a25c(p1, out1, out2, 0x61, z2);
            }
            inner++;
        } while (inner < 16);
        outer++;
    } while (outer < 16);
}

void func_020479f0(int a, int b, int c)
{
    int i, j;
    int k = 0;

    for (j = 0; j < 2; j++) {
        for (i = k; i < c; i++) {
            func_02047a28(a, b, i, j);
        }
    }
    func_02046680();
}

void func_020479e0(int argument0, int argument1)
{
    func_0204cb50((void *) data_021f39fc, (int) argument1);
}

void func_0204790c(void *a, int p1, int p2, int p3, int p4, int p5, int p6)
{
    unsigned int t;
    UnkStruct_0204790c *e;
    int i;
    int r;
    int ok;

    e = func_0203fc70();
    func_0209df7c(&t);
    r = func_0209fa30(p6 + 0x173dd);
    for (i = 0; i < 7; e++, i++) {
        unsigned short k = e->unk_00;
        if (k == 0x63) {
            continue;
        }
        if (e->unk_04 > t) {
            continue;
        }
        if (e->unk_08 <= t) {
            continue;
        }
        ok = 0;
        switch (k) {
            case 0x10:
                func_02047bf8((int) a, p1, (int) e, p2, p3, p4, p5, r, p6);
                ok = 1;
                break;
            case 0x11:
            case 0x61:
                func_02047a8c((int) a, p1, p2);
                ok = 1;
                break;
            case 0x62:
                func_020b2ec8();
                ok = 1;
                break;
            case 0xe:
                func_02047bc8((int) a, p1, (int) e, p4, p5, r, p6);
                ok = 1;
                break;
        }
        if (ok != 0) {
            func_020479e0((int) a, (unsigned short) e->unk_00);
        }
    }
}

void func_02047898(int a, int b, int c)
{
    char buf[20];
    int i;
    if (func_0209fa30((int) ((void *) (b + 0x173dd)))) {
        return;
    }
    ((int *) buf)[0] = 0;
    ((int *) buf)[1] = 0;
    func_0209e474(buf);
    for (i = 0; i < 3; i++) {
        MI_CpuCopy8(buf, buf + 8, 8);
        switch (func_0203fc78(data_020db764[i], buf + 8, c)) {
            case 2:
            case 3:
                switch (i) {
                    case 0:
                        func_020b2f28();
                        break;
                    case 1:
                        func_020b2f08();
                        break;
                    case 2:
                        func_020b2ee8();
                        break;
                }
                break;
        }
    }
}

int func_02047854(int a, unsigned short b, int c, int d, int extra)
{
    int result = 0;
    switch (b) {
        case 16:
            result = 1;
            break;
        case 17:
        case 97:
            func_020479f0(a, c, d);
            result = 1;
            break;
        case 98:
            func_020b2eb8();
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

void func_020477e4(int p1, int p2, int p3, int p4, int p5)
{
    Entry_020477e4 *p;
    unsigned int q;
    int i;
    unsigned short a;
    unsigned char b;

    func_0209df7c(&q);
    p = (Entry_020477e4 *) func_0204cc04(0);

    for (i = 0; i < 4; p++, i++) {
        a = p->a;
        if (a == 99) {
            continue;
        }
        b = p->b;
        if (b != func_0209dee8() || p->c > q || p->d < q) {
            if (func_02047854(p1, a, p2, p3, p4) != 0) {
                func_0204cbc0(p5 + 0x17254, a);
            }
        }
    }
}

void func_02047730(int unused, void *b)
{
    Slot slots[5];
    unsigned int flag;

    slots[0].w[0] = 0;
    slots[0].w[1] = 0;

    func_0209e474(&slots[0]);

    MI_CpuCopy8(&slots[0], &slots[1], 8);
    flag = (func_0203fc78(0x3d, &slots[1], (int) b) == 0);
    if (flag) {
        func_020b2f18();
    }

    MI_CpuCopy8(&slots[0], &slots[2], 8);
    flag = (func_0203fc78(0x3f, &slots[2], (int) b) == 0);
    if (flag) {
        func_020b2ef8();
    }

    MI_CpuCopy8(&slots[0], &slots[3], 8);
    flag = (func_0203fc78(0x60, &slots[3], (int) b) == 0);
    if (flag) {
        func_020b2ed8();
    }

    MI_CpuCopy8(&slots[0], &slots[4], 8);
    flag = (func_0203fc78(0x44, &slots[4], (int) b) == 0);
    if (flag) {
        func_020b2a90();
    }
}

void func_02047688(void *a0, void *a1, int a2, int a3, int a4, void *a5)
{
    Pair_02047688 a;
    unsigned char *g;

    if (func_0203fae4() != 0) {
        if (a5 == 0) {
            return;
        }
        if (func_020984e8() != 0) {
            return;
        }
    }
    a.unk_00 = 0;
    a.w1 = 0;
    func_0209df38(&a);
    func_0209e100(&a, 6);
    g = data_021f3a50;
    if (g[2] != ((unsigned char *) &a)[5] || g[1] != ((unsigned char *) &a)[4] || g[0] != ((unsigned char *) &a)[3]) {
        func_020477e4((int) a0, (int) a1, a2, a3, (int) data_021dc7a8);
        func_0204790c(a0, (int) a1, a2, a3, a4, (int) a5, (int) data_021dc7a8);
        g[2] = ((unsigned char *) &a)[5];
        g[1] = ((unsigned char *) &a)[4];
        g[0] = ((unsigned char *) &a)[3];
    }
    func_02047730((int) a0, a5);
    func_02047898((int) a0, (int) data_021dc7a8, (int) a5);
}

void func_0204763c(void *a, int b)
{
    UnkStruct_0204763c local;
    FieldStruct *p;
    int c, d;

    p = func_0204e414();
    if (p == 0) {
        return;
    }

    local.x = 0;
    local.y = 0;
    func_0209e474((void *) (&local));
    c = p->unk_04 - 2;
    d = p->unk_08 - 2;
    func_0204a3cc(&data_021c79c4, p);
    func_02047688(a, (void *) p, c, d, (int) (&local), (void *) b);
}

void func_0204762c(void)
{
    func_0204763c(&data_021c779c[0], 0);
}

unsigned short func_020475b0(int unused, unsigned short *p, int flag)
{
    unsigned short result = 0xfff1;
    int r6 = 1;
    int r5 = r6;
    int r4 = r6;
    int r3 = 0;
    unsigned int val = *p;

    if (val >= 0x6eu && val <= 0x73u) {
        r3 = r6;
    }
    if (!r3 && (val < 0x74u || val > 0x79u)) {
        r4 = 0;
    }
    if (!r4 && (val < 0x7au || val > 0x7fu)) {
        r5 = 0;
    }
    if (!r5 && (val < 0x80u || val > 0x87u)) {
        r6 = 0;
    }

    if (r6) {
        if (val == 0x86u && flag != 0) {
            result = 0xa5;
        } else {
            result = (unsigned short) (val + 0x1cu);
        }
    } else {
        if (val == 0x88u) {
            result = 0xa4;
        } else if (val >= 0xd4u && val <= 0xdau) {
            result = (unsigned short) (val + 7u);
        }
    }

    return result;
}

void func_02047500(int a, int ctx, int nz, int nx)
{
    int j, i, k;
    u16 *q;
    u16 v;
    int ox, oz;

    for (i = 0; i < nx; i++) {
        for (j = 0; j < nz; j++) {
            q = (u16 *) func_0204f5e0(ctx, j + 1, i + 1, 0, 0, 0);
            for (k = 0; k < 256; k++) {
                if (q != 0 && *q != 0xfff1) {
                    v = (u16) func_020475b0(a, (unsigned short *) q, 0);
                    if (v != 0xfff1) {
                        func_0204f800(&ox, &oz, j + 1, i + 1, k % 16, k / 16);
                        func_0204a25c(ctx, ox, oz, v, 0);
                    }
                }
                q++;
            }
        }
    }
}
