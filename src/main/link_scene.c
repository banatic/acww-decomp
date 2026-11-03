/* link_scene: 31 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6890 @ 0x020a6890, 0x50 bytes, Thumb
 * func_020a6878 @ 0x020a6878, 0x16 bytes, Thumb
 * func_020a682c @ 0x020a682c, 0x4a bytes, Thumb
 * func_020a67d8 @ 0x020a67d8, 0x54 bytes, Thumb
 * func_020a6738 @ 0x020a6738, 0xa0 bytes, Thumb
 * func_020a669c @ 0x020a669c, 0x9c bytes, Thumb
 * func_020a6694 @ 0x020a6694, 0x6 bytes, Thumb
 * func_020a668c @ 0x020a668c, 0x6 bytes, Thumb
 * func_020a6688 @ 0x020a6688, 0x4 bytes, Thumb
 * func_020a6684 @ 0x020a6684, 0x4 bytes, Thumb
 * func_020a636c @ 0x020a636c, 0x318 bytes, Thumb
 * func_020a6368 @ 0x020a6368, 0x4 bytes, Thumb
 * func_020a6364 @ 0x020a6364, 0x4 bytes, Thumb
 * func_020a635c @ 0x020a635c, 0x8 bytes, Thumb
 * func_020a6354 @ 0x020a6354, 0x8 bytes, Thumb
 * func_020a6340 @ 0x020a6340, 0x12 bytes, Thumb
 * func_020a633c @ 0x020a633c, 0x4 bytes, Thumb
 * func_020a6338 @ 0x020a6338, 0x4 bytes, Thumb
 * func_020a6294 @ 0x020a6294, 0xa4 bytes, Thumb
 * func_020a6290 @ 0x020a6290, 0x4 bytes, Thumb
 * func_020a628c @ 0x020a628c, 0x4 bytes, Thumb
 * func_020a6288 @ 0x020a6288, 0x4 bytes, Thumb
 * func_020a6284 @ 0x020a6284, 0x4 bytes, Thumb
 * func_020a6280 @ 0x020a6280, 0x4 bytes, Thumb
 * func_020a627c @ 0x020a627c, 0x4 bytes, Thumb
 * func_020a6250 @ 0x020a6250, 0x2c bytes, Thumb
 * func_020a6248 @ 0x020a6248, 0x6 bytes, Thumb
 * func_020a6240 @ 0x020a6240, 0x6 bytes, Thumb
 * func_020a6238 @ 0x020a6238, 0x6 bytes, Thumb
 * func_020a6230 @ 0x020a6230, 0x6 bytes, Thumb
 * func_020a6188 @ 0x020a6188, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020a67d8 {
    u8 pad_00[0x64];
    u32 idx;
} UnkStruct_020a67d8;

typedef struct UnkStruct_020a67d8_2 {
    u8 pad_00[0x2c];
    void *arr[1];
} UnkStruct_020a67d8_2;

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned char unk_0C[0x20];
    int arr[16];
} UnkStruct_020a6738;

typedef struct {
    char pad_00[0x3c];
    unsigned char arr[4][8];
} UnkStruct_020a669c;

typedef struct {
    unsigned char pad_00[92];
    unsigned char unk_5C;
} UnkStruct_020a6694;

typedef struct {
    unsigned char pad_00[92];
    unsigned char unk_5C;
} UnkStruct_020a668c;

struct UnkStruct_020a636c_2;

struct UnkStruct_020a636c {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    unsigned char pad_00[124];
    unsigned char unk_7C;
} UnkStruct_020a6248;

typedef struct {
    unsigned char pad_00[124];
    unsigned char unk_7C;
} UnkStruct_020a6240;

typedef struct {
    unsigned char pad_00[128];
    unsigned long unk_80;
} UnkStruct_020a6238;

typedef struct {
    unsigned char pad_00[128];
    unsigned long unk_80;
} UnkStruct_020a6230;

typedef struct {
    char pad_00[0x64];
    int v;
} UnkStruct_020a6188;

extern int func_020a72d0(int);
extern void func_020a7394(int, int, int, int, int);
extern void func_020a7704(int *, int *, int *);
extern void MI_CpuCopy8(void *dst, const void *src, int n);
extern void func_020a76f8(void *p);
void func_020a76d8(void **p, u32 *out);
void func_020a76d0(void **p);
void func_020737f0(UnkStruct_020a67d8 *obj, u8 *data, int n);
extern int func_02073dd4(int a, int b);
extern int func_020a7330(int a);
extern void *data_020ccf94;
extern void func_020a7778(void *a0, void *a1, void *a2, void *a3, void *a4);
extern void *func_020a7820(void *a0);
extern void func_020a77f4(void *a0, int a1, unsigned char a2, unsigned char a3, unsigned char a4, int a5);
extern void func_02073820(void *a0);
extern void func_02073770(void *a0, int a1, int a2);
extern void func_020a7768(void *a0);
extern int func_020a7810(void *a0);
extern unsigned short data_020e3c80;
extern void func_020a6f88(void);
extern void func_020a6eb0(int a);
extern int func_020a7450(void);
extern int func_020a744c(void);
extern void func_020a6e4c(int a, unsigned char *p, unsigned char *q, unsigned char *r);
extern int func_020b65c4(void);
extern int func_020a6c98(int a);
extern int func_02073690(struct UnkStruct_020a636c *g);
extern int func_0207356c(struct UnkStruct_020a636c *g);
extern int func_020734a4(struct UnkStruct_020a636c *g);
extern void func_02073410(struct UnkStruct_020a636c *g);
extern int func_020a7300(int a);
extern int func_020b5e70(void);
extern void func_020733ac(struct UnkStruct_020a636c *g);
extern int func_02073394(struct UnkStruct_020a636c *g);
extern void func_020a7380(int a, int b);
extern int func_020a7258(void);
extern int func_02073918(void *g, int dir);

int func_020a6878(int *p);
void func_020a6368(int *p0, int p1);
int func_020a6364(int *p0);
int func_020a6354(int p0, int p1);
void func_020a6340(void *param);
void func_020a6290(int *p0, int p1);
int func_020a628c(int *p0);
void func_020a6248(UnkStruct_020a6248 *p, unsigned char v);
unsigned char func_020a6240(UnkStruct_020a6240 *p);

void func_020a6890(int a, int *out1, int *out2)
{
    int found = 4;
    int i;
    int x;

    for (i = 3; i >= 0; i--) {
        if (func_020a72d0(i)) {
            found = i;
            break;
        }
    }
    if (found < 4) {
        return;
    }
    x = func_020a6878((int *) a);
    if (x >= 4) {
        return;
    }
    func_020a7394(x, 0x3f, 0, 1, 4);
    *out1 = x;
    *out2 = 4;
}

int func_020a6878(int *p)
{
    int arr[3];
    func_020a7704(p + 3, &arr[1], &arr[0]);
    return arr[1];
}

void func_020a682c(void *param)
{
    int a, b;
    char *p;
    int i;

    if (func_020a6878((int *) param) < 4) {
        p = (char *) param + 12;
        for (i = 2; i >= 0; i--) {
            char *q = p + 8;
            func_020a7704((int *) q, &b, &a);
            if (b < 4) {
                MI_CpuCopy8(q, p, 8);
                p += 8;
            } else {
                break;
            }
        }
        func_020a76f8(p);
    }
}

/* FAKEMATCH: the empty if keeps the data_020ccf94->idx load chain before self + 0x2c is formed; without it the add comes first */
void func_020a67d8(UnkStruct_020a67d8_2 *self)
{
    u8 ch;
    u32 idx;
    u32 val;
    UnkStruct_020a67d8 *ptr;
    u32 *ptr2;
    UnkStruct_020a67d8 *obj;
    void **ptr3;
    UnkStruct_020a67d8 **ptr4;
    void **ptr5;
    void **p;
    idx = (*(UnkStruct_020a67d8 * *) &data_020ccf94)->idx;
    if ((!ptr3) && (!ptr3)) {
    }
    ptr5 = (void **) ((((char *) self) + 0x2c) + (idx * 4));
    p = ptr5;
    ptr3 = p;
    ptr2 = &val;
    func_020a76d8(ptr3, ptr2);
    if (val != 0) {
        ch = (u8) val;
        ptr4 = ((UnkStruct_020a67d8 * *) &data_020ccf94);
        obj = *ptr4;
        func_02073820((void *) obj);
        ptr = obj;
        func_020737f0(obj, &ch, 1);
        func_02073770((void *) ptr, 0xa, 0);
        func_020a76d0(ptr3);
    }
}

void func_020a6738(UnkStruct_020a6738 *self, int *out1, int *out2)
{
    int count;
    int data_val;
    int *ptr;
    unsigned char byte14;
    int local18;
    int local1c;
    int pad;
    int i;
    int flag;

    count = func_020a6878((int *) self);
    if (count >= 4) {
        return;
    }

    ptr = &self->arr[count];
    func_020a76d8((void **) ptr, (u32 *) (&local18));
    if (local18 != 1) {
        return;
    }

    flag = 1;
    func_020a7704((int *) self->unk_0C, (int *) ((unsigned char *) &local1c), (int *) (&byte14));

    i = 3;
    data_val = (*(int *) &data_020ccf94);
    for (; i >= 0; i--) {
        if (count == i) {
            continue;
        }
        if (func_02073dd4(data_val, i) == 0) {
            continue;
        }
        if (func_020a7330(i) != byte14) {
            continue;
        }
        flag = 0;
        break;
    }

    func_020a7394(count, byte14, flag, 0, 7);

    func_020a76d0((void **) ptr);
    func_020a682c((void *) self);

    *out1 = count;
    *out2 = 7;
}

void func_020a669c(UnkStruct_020a669c *self)
{
    unsigned char local[8];
    int val;
    unsigned int i = 0;
    void *r4 = data_020ccf94;
    void *ptr;

    do {
        ptr = &self->arr[i];
        func_020a7778(ptr, &local[0], &local[1], &local[2], &val);
        if (val != 0) {
            func_020a7394(i, (unsigned char) local[0], (unsigned char) local[1], (unsigned char) local[2], val);
            func_020a7820(&local[3]);
            func_020a77f4(&local[3], i, local[0], local[1], local[2], val);
            func_02073820(r4);
            func_020737f0((UnkStruct_020a67d8 *) r4, (u8 *) (&local[3]), 2);
            func_02073770(r4, 9, 4);
            func_020a7768(ptr);
            func_020a7810(&local[3]);
        }
        i++;
    } while (i < 4);
}

void func_020a6694(UnkStruct_020a6694 *p, unsigned char v)
{
    p->unk_5C = v;
}

unsigned char func_020a668c(UnkStruct_020a668c *p)
{
    return p->unk_5C;
}

void func_020a6688(int *p0, int p1)
{
    p0[24] = p1;
}

int func_020a6684(int *p0)
{
    return p0[24];
}

void func_020a636c(struct UnkStruct_020a636c_2 *self)
{
    int sel1;
    int ok;
    int v;
    int sel2;
    int tmp;
    unsigned char a[3];
    unsigned char b[3];
    int j;
    int n;
    struct UnkStruct_020a636c *g;
    struct UnkStruct_020a636c *h;

    g = (*(struct UnkStruct_020a636c * *) &data_020ccf94);
    n = g->unk_64;

    switch (func_020a6684((int *) self)) {
        case 16:
            if (data_020e3c80 != 5) {
                return;
            }
            func_020a6f88();
            func_020a6340((void *) self);
            func_020a6248((UnkStruct_020a6248 *) self, 0);
            func_020a6eb0(0);
            return;

        case 0:
            if (!func_020a72d0(n)) {
                return;
            }
            func_020a6688((int *) self, 1);
            return;

        case 1:
            if (func_020a7450()) {
                return;
            }
            if (func_020a744c()) {
                return;
            }
            func_020a6e4c(n, &a[0], &a[1], &a[2]);
            if (a[1]) {
                sel1 = 4;
                for (j = 0; j < 4; j++) {
                    if (j != n && func_02073dd4((int) g, j) && func_020a7330(j) == a[0]) {
                        sel1 = j;
                        break;
                    }
                }
                if (sel1 < 4) {
                    func_020a6368((int *) self, sel1);
                    func_020a6688((int *) self, 2);
                } else {
                    func_020a6368((int *) self, 4);
                    func_020a6688((int *) self, 5);
                }
            } else {
                func_020a6368((int *) self, 4);
                func_020a6688((int *) self, 4);
            }
            return;

        case 2:
            ok = 1;
            if (!func_020a6c98(func_020b65c4())) {
                for (j = 3; j >= 0; j--) {
                    if (j == n) {
                        continue;
                    }
                    if (!func_02073dd4((int) g, j)) {
                        continue;
                    }
                    tmp = func_020a7330(j);
                    if (tmp != func_020b65c4()) {
                        continue;
                    }
                    if (func_020a6354((int) self, j)) {
                        continue;
                    }
                    ok = 0;
                    break;
                }
            }
            if (!ok) {
                return;
            }
            if (func_02073690(g)) {
                return;
            }
            if (func_0207356c(g)) {
                return;
            }
            if (func_020734a4(g)) {
                return;
            }
            if (func_020a744c()) {
                return;
            }
            func_020a6340((void *) self);
            func_02073410(g);
            func_020a6688((int *) self, 3);
            return;

        case 4:
            if (!(int) func_020a6240((UnkStruct_020a6240 *) self) && !func_020a6c98(func_020b65c4())) {
                return;
            }
            func_020a6248((UnkStruct_020a6248 *) self, 0);
            func_020a6688((int *) self, 5);
            return;

        case 8:
            // != 4 with the equal case in the else branch.
            if (func_020a6364((int *) self) != 4) {
                if (!func_020a7300(func_020a6364((int *) self)) && !func_020a6c98(func_020b65c4())) {
                    return;
                }
                func_020a6688((int *) self, 9);
            } else {
                func_020a6688((int *) self, 9);
            }
            return;

        case 9:
            v = func_020b5e70();
            sel2 = 4;
            for (j = 3; j >= 0; j--) {
                if (j == n) {
                    continue;
                }
                if (!func_02073dd4((int) g, j)) {
                    continue;
                }
                func_020a6e4c(j, &b[0], &b[1], &b[2]);
                if (b[0] == v && b[1]) {
                    sel2 = j;
                    break;
                }
            }
            if (sel2 < 4) {
                func_020a6290((int *) self, sel2);
                func_020a6694((UnkStruct_020a6694 *) self, 0);
                func_020733ac(g);
                if (!func_020a6c98(func_020b5e70())) {
                    h = (*(struct UnkStruct_020a636c * *) &data_020ccf94);
                    func_02073820((void *) h);
                    func_02073770((void *) h, 0xe, func_020a628c((int *) self));
                }
                func_020a6688((int *) self, 0xa);
            } else {
                func_020a6290((int *) self, 4);
                func_020a6694((UnkStruct_020a6694 *) self, 1);
                func_020a6688((int *) self, 0xb);
            }
            return;

        case 10:
            if (!func_02073394(g) && !func_020a6c98(func_020b5e70())) {
                return;
            }
            func_020a6688((int *) self, 0xb);
            return;

        case 14:
            func_020a7380(g->unk_64, 1);
            func_020a6688((int *) self, 0xf);
            return;

        case 15:
            if (func_020a7258()) {
                return;
            }
            func_020a6688((int *) self, 0x10);
            return;
    }
}

void func_020a6368(int *p0, int p1)
{
    p0[25] = p1;
}

int func_020a6364(int *p0)
{
    return p0[25];
}

void func_020a635c(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (104))) + (0)) = p2;
}

int func_020a6354(int p0, int p1)
{
    return *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (104))) + (0));
}

void func_020a6340(void *param)
{
    unsigned char *ptr;
    int i;

    ptr = (unsigned char *) param + 0x68;
    for (i = 3; i >= 0; i--) {
        *ptr = 0;
        ptr++;
    }
}

void func_020a633c(int *p0, int p1)
{
    p0[27] = p1;
}

int func_020a6338(int *p0)
{
    return p0[27];
}

void func_020a6294(void *self)
{
    int best = 4;
    int dir = 3;
    void *g = data_020ccf94;

    for (; dir >= 0; dir--) {
        if (func_02073dd4((int) g, dir) != 0 && func_020a72d0(dir) != 0) {
            best = dir;
            break;
        }
    }

    if (best != func_020a6338((int *) self)) {
        if (best < 4) {
            if (func_02073918(g, best) == 0) {
                int v = func_020a7330(best);
                if (v == func_020b65c4()) {
                    int r = func_020a7300(best);
                    if (r != 0) {
                        if (func_020a6c98(func_020b65c4()) == 0) {
                            void *g2 = data_020ccf94;
                            func_02073820(g2);
                            func_02073770(g2, 0xd, best);
                        }
                    }
                }
            }
            func_020a633c((int *) self, best);
        } else {
            func_020a633c((int *) self, 4);
        }
    }
}

void func_020a6290(int *p0, int p1)
{
    p0[28] = p1;
}

int func_020a628c(int *p0)
{
    return p0[28];
}

void func_020a6288(int *p0, int p1)
{
    p0[29] = p1;
}

int func_020a6284(int *p0)
{
    return p0[29];
}

void func_020a6280(int *p0, int p1)
{
    p0[30] = p1;
}

int func_020a627c(int *p0)
{
    return p0[30];
}

void func_020a6250(int arg0)
{
    int tested_value0;
    int val;
    int val2;

    if ((tested_value0 = (int) (func_020a627c((int *) arg0))) < 4) {
        val = func_020a7330(tested_value0);
        val2 = func_020b65c4();
        if (val == val2) {
            func_020a6280((int *) arg0, 4);
        }
    }
    return;
}

void func_020a6248(UnkStruct_020a6248 *p, unsigned char v)
{
    p->unk_7C = v;
}

unsigned char func_020a6240(UnkStruct_020a6240 *p)
{
    return p->unk_7C;
}

void func_020a6238(UnkStruct_020a6238 *p, unsigned long v)
{
    p->unk_80 = v;
}

unsigned long func_020a6230(UnkStruct_020a6230 *p)
{
    return p->unk_80;
}

void func_020a6188(int arg0)
{
    int best;
    int saved;
    int i;
    UnkStruct_020a6188 *obj;
    UnkStruct_020a6188 *p2;

    best = 4;
    obj = (*(UnkStruct_020a6188 * *) &data_020ccf94);
    saved = obj->v;
    i = 3;

    while (i >= 0) {
        if (func_02073dd4((int) obj, i) != 0 && func_020a72d0(i) != 0) {
            best = i;
            break;
        }
        i--;
    }

    if (best == (int) func_020a6230((UnkStruct_020a6230 *) arg0)) {
        return;
    }

    if (best < 4) {
        if (func_02073918((void *) obj, best) == 0 && func_020a7300(saved) != 0) {
            i = func_020a7330(best);
            if (i == func_020b65c4()) {
                if (func_020a6c98((int) func_020b65c4()) == 0) {
                    p2 = (*(UnkStruct_020a6188 * *) &data_020ccf94);
                    func_02073820((void *) p2);
                    func_02073770((void *) p2, 0x11, best);
                }
            }
        }
        func_020a6238((UnkStruct_020a6238 *) arg0, best);
    } else {
        func_020a6238((UnkStruct_020a6238 *) arg0, 4);
    }
}
