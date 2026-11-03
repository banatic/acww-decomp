/* pockets_box: 23 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229ca5c @ 0x0229ca5c, 0x20 bytes, Thumb
 * func_ov100_0229ca3c @ 0x0229ca3c, 0x20 bytes, Thumb
 * func_ov100_0229ca1c @ 0x0229ca1c, 0x20 bytes, Thumb
 * func_ov100_0229c9e0 @ 0x0229c9e0, 0x3c bytes, Thumb
 * func_ov100_0229c994 @ 0x0229c994, 0x4c bytes, Thumb
 * func_ov100_0229c970 @ 0x0229c970, 0x24 bytes, Thumb
 * func_ov100_0229c940 @ 0x0229c940, 0x30 bytes, Thumb
 * func_ov100_0229c84c @ 0x0229c84c, 0xf4 bytes, Thumb
 * func_ov100_0229c758 @ 0x0229c758, 0xf4 bytes, Thumb
 * func_ov100_0229c6dc @ 0x0229c6dc, 0x7c bytes, Thumb
 * func_ov100_0229c60c @ 0x0229c60c, 0xd0 bytes, Thumb
 * func_ov100_0229c5e0 @ 0x0229c5e0, 0x2c bytes, Thumb
 * func_ov100_0229c5b0 @ 0x0229c5b0, 0x30 bytes, Thumb
 * func_ov100_0229c56c @ 0x0229c56c, 0x44 bytes, Thumb
 * func_ov100_0229c528 @ 0x0229c528, 0x44 bytes, Thumb
 * func_ov100_0229c4ec @ 0x0229c4ec, 0x3c bytes, Thumb
 * func_ov100_0229c3c0 @ 0x0229c3c0, 0x12c bytes, Thumb
 * func_ov100_0229c390 @ 0x0229c390, 0x30 bytes, Thumb
 * func_ov100_0229c324 @ 0x0229c324, 0x6c bytes, Thumb
 * func_ov100_0229c2d8 @ 0x0229c2d8, 0x4c bytes, Thumb
 * func_ov100_0229c2c0 @ 0x0229c2c0, 0x18 bytes, Thumb
 * func_ov100_0229c2b0 @ 0x0229c2b0, 0x10 bytes, Thumb
 * func_ov100_0229c2a0 @ 0x0229c2a0, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229c994 {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x20FE];
    unsigned char unk_218C;
    unsigned char pad_218D[0xE7];
    unsigned char unk_2274;
    unsigned char pad_2275[0x6AE];
    unsigned char unk_2923;
    unsigned char unk_2924;
};

typedef struct {
    unsigned char pad_00[0x2925];
    unsigned char flag;
} UnkStruct_0229c970;

typedef struct {
    unsigned char pad_00[0x2921];
    unsigned char b;
} UnkStruct_0229c6dc;

typedef struct {
    unsigned char pad_00[0x2274];
    char unk_2274;
    unsigned char pad_2275[0x6ac];
    unsigned char byte_field;
} UnkStruct_0229c60c;

typedef struct {
    char pad_00[0x2928];
    unsigned char unk_2928;
} UnkStruct_0229c4ec;

typedef struct {
    char pad_00[0x28dc];
    unsigned short a[15];
    unsigned short b[15];
    char pad_2918[0x2928 - 0x2918];
    unsigned char st;
} UnkStruct_0229c3c0;

typedef struct {
    unsigned char pad_00[0x291a];
    short unk_291A;
} Obj_0229c2d8;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov002_02207d24(void *p, int n);
extern void func_ov100_0229d8b0(UnkStruct_0229c970 *self);
extern void func_ov100_0229ca9c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_ov002_0220889c(void *self);
extern int func_ov002_022088bc(void *self);
extern int func_ov002_022088ac(void *self);
extern int func_ov002_022088cc(void *self);
extern int func_ov100_0229d630(UnkStruct_0229c60c *self, unsigned char byte);
extern int func_ov100_0229d620(UnkStruct_0229c60c *self, unsigned char byte);
extern int func_ov100_0229d60c(UnkStruct_0229c60c *self, unsigned char byte);
extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);
extern void func_02070b84(void *p);
extern void func_02070adc(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern int func_0207094c(int a0, int a1);
extern void func_02070a04(int a0, int a1, int a2);
extern void func_0200467c(int cmd);
extern void func_0206fc4c(int n);
extern void func_0206fb14(void);
extern int func_0206fca4(void);
extern void func_0206faf8(unsigned short *);
extern void func_0206fc80(int);
extern void MI_CpuCopy8(void *, const void *, int);
extern const unsigned short data_021f3a68[];
extern const unsigned short data_021f3a86[];
extern int data_020ccf94;
extern int func_02073d90(int g);
extern void func_02073820(int g);
extern void func_020737f0(int g, u8 *p, int n);
extern void func_02073770(int g, int a, int b);
extern int func_02073d80(int g);
extern int func_0206fc6c(void);
extern int func_02074fec(int);

int func_ov100_0229c390(int unused, unsigned short *arr);
void func_ov100_0229c324(char *self, int b);
int func_ov100_0229c2c0(unsigned int *ptr, unsigned int mask);
void func_ov100_0229c2b0(void *p, unsigned int mask);
void func_ov100_0229c2a0(unsigned char *ptr, unsigned int mask);

void func_ov100_0229ca5c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x2274);
    func_ov002_02208098((void *) (self), 9);
}

void func_ov100_0229ca3c(void *self)
{
    func_ov002_0220a164((char *) self + 0x2274);
    func_ov002_02208098((void *) (self), 10);
}

void func_ov100_0229ca1c(void *p)
{
    func_ov002_0220a374((char *) p + 0x2274, 4);
    func_ov002_02208098((void *) (p), 0xb);
}

void func_ov100_0229c9e0(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((unsigned char *) self)[0x2923] = val;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098((void *) (self), 0xd);
}

void func_ov100_0229c994(struct UnkStruct_0229c994 *a, unsigned char c)
{
    func_ov002_02207d24(&a->unk_218C, 1);
    a->unk_2924 = a->unk_8D;
    a->unk_2923 = c;
    func_ov002_0220a374(&a->unk_2274, 6);
    func_ov002_02208098((void *) (a), 14);
}

void func_ov100_0229c970(UnkStruct_0229c970 *self)
{
    switch (self->flag) {
        case 0:
            func_ov100_0229ca1c((void *) self);
            break;
        case 1:
        default:
            func_ov100_0229d8b0(self);
            break;
    }
}

void func_ov100_0229c940(void *self)
{
    ((unsigned char *) self)[0x2925] = 1;
    func_ov100_0229ca9c(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098((void *) (self), 0x13);
}

void func_ov100_0229c84c(void *self, void *other, int arg)
{
    unsigned char *p = (unsigned char *) self;
    unsigned char *q = (unsigned char *) other;
    int r4 = p[0x2921];
    int r6 = 0;
    int r7 = (int) q;

    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(q) != 0) {
        if (func_ov002_022088cc(q) != 0) {
            if (r6 != 0) {
                goto label_8f8;
            }
        }
        if (r4 == 0) {
            if (arg == 1) {
                p[0x2921] = p[0x2921] + 4;
            } else {
                p[0x2921] = 0x1f;
            }
            func_ov100_0229c2b0(self, 0x10);
            return;
        } else {
            p[0x2921] = p[0x2921] - 1;
            r4--;
            goto label_8f8;
        }
    } else {
        if (func_ov002_0220889c(q) != 0) {
            if (func_ov002_022088bc(q) == 0) {
                if (r4 == 4) {
                    if (arg == 1) {
                        p[0x2921] = p[0x2921] - 4;
                        func_ov100_0229c2b0(self, 0x20);
                        return;
                    } else {
                        p[0x2921] = 0x1f;
                        return;
                    }
                } else {
                    p[0x2921] = p[0x2921] + 1;
                    r4++;
                }
            }
        }
    }

label_8f8:
    if (func_ov002_022088cc(q) != 0) {
        if (r6 > 0) {
            p[0x2921] = p[0x2921] - 5;
            return;
        } else {
            p[0x2921] = r4 + 0x19;
            return;
        }
    } else {
        if (func_ov002_022088bc(q) != 0) {
            if (r6 < 2) {
                p[0x2921] = p[0x2921] + 5;
            }
        }
    }
}

void func_ov100_0229c758(unsigned char *s, void *obj, int mode)
{
    int r4;
    int r6;

    r4 = s[0x2921] - 15;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(obj)) {
        if (func_ov002_022088cc(obj) == 0 || r6 == 0) {
            if (r4 == 0) {
                if (mode == 1) {
                    s[0x2921] += 4;
                } else {
                    s[0x2921] = 0x1e;
                }
                func_ov100_0229c2b0(s, 0x10);
                return;
            } else {
                s[0x2921] -= 1;
                r4--;
            }
        }
    } else {
        if (func_ov002_0220889c(obj) != 0 && func_ov002_022088bc(obj) == 0) {
            if (r4 == 4) {
                if (mode == 1) {
                    s[0x2921] -= 4;
                    func_ov100_0229c2b0(s, 0x20);
                    return;
                } else {
                    s[0x2921] = 0x1e;
                    return;
                }
            } else {
                s[0x2921] += 1;
                r4++;
            }
        }
    }

    if (func_ov002_022088cc(obj)) {
        if (r6 > 0) {
            s[0x2921] -= 5;
            return;
        }
    } else {
        if (func_ov002_022088bc(obj)) {
            if (r6 < 2) {
                s[0x2921] += 5;
            } else {
                s[0x2921] = r4;
            }
        }
    }
}

void func_ov100_0229c6dc(UnkStruct_0229c6dc *r5, void *r4)
{
    if (func_ov002_022088cc(r4)) {
        r5->b = 0x1e;
    } else if (func_ov002_022088bc(r4)) {
        r5->b = 0x1f;
    }

    if (func_ov002_0220889c(r4)) {
        if (r5->b == 0x1e) {
            r5->b = 0x19;
        } else {
            r5->b = 0x00;
        }
        func_ov100_0229c2b0((void *) r5, 0x20);
    } else if (func_ov002_022088ac(r4)) {
        if (r5->b == 0x1e) {
            r5->b = 0x1d;
        } else {
            r5->b = 0x04;
        }
    }
}

int func_ov100_0229c60c(UnkStruct_0229c60c *self, int a, int b)
{
    unsigned char initial = self->byte_field;
    func_ov100_0229c2a0((unsigned char *) self, 0x30);
    func_ov100_0229c2a0((unsigned char *) self, 0x100);
    if (a == 0) {
        return 0;
    }
    if (func_ov100_0229d630(self, self->byte_field)) {
        func_ov100_0229c84c((void *) self, (void *) a, b);
    } else if (func_ov100_0229d620(self, self->byte_field)) {
        func_ov100_0229c758((unsigned char *) self, (void *) a, b);
    } else if (func_ov100_0229d60c(self, self->byte_field)) {
        func_ov100_0229c6dc((UnkStruct_0229c6dc *) self, (void *) a);
    }
    {
        int result1 = func_ov100_0229d60c(self, self->byte_field);
        int result2 = func_ov100_0229d60c(self, initial);
        if (result1 != result2) {
            if (func_ov100_0229d60c(self, self->byte_field) != 0) {
                func_ov002_0220a314(&self->unk_2274);
            } else {
                func_ov002_0220a2b4(&self->unk_2274);
            }
            func_ov100_0229c2b0((void *) self, 0x100);
        }
    }
    return (initial != self->byte_field) ? 1 : 0;
}

void func_ov100_0229c5e0(void *p)
{
    int i = 0;
    ((char *) p)[0x2927] = i;
    {
        char *base = (char *) p + 0x27e8;
        for (; i < 2; i++) {
            func_02070b84(base + i * 0x6c);
        }
    }
}

unsigned char *func_ov100_0229c5b0(unsigned char *p)
{
    if (p[0x2927] >= 2) {
        return p + 0x2854;
    }
    p[0x2927]++;
    return p + 0x27e8 + (p[0x2927] - 1) * 108;
}

void func_ov100_0229c56c(int a, int b)
{
    int r5;
    int x;

    r5 = 1;
    if (b) {
        r5 = 15;
    }
    x = (int) func_ov100_0229c5b0((unsigned char *) a);
    func_02070adc(x, 4, 0x1ca, 6, r5, 9, 0);
    func_0207094c(x, 0x21);
    func_02070a04(x, 1, 1);
}

void func_ov100_0229c528(int a, int b)
{
    int x = 1;
    int ret;
    if (b != 0) {
        x = 15;
    }
    ret = (int) func_ov100_0229c5b0((unsigned char *) a);
    func_02070adc(ret, 4, 0x1d6, 6, x, 9, 0);
    func_0207094c(ret, 101);
    func_02070a04(ret, 1, 1);
}

void func_ov100_0229c4ec(UnkStruct_0229c4ec *p)
{
    func_ov100_0229c2a0((unsigned char *) p, 8);
    func_0200467c(0x28);
    p->unk_2928 = 5;
    func_ov002_02208098((void *) (p), 21);
    func_ov100_0229c528((int) p, 1);
    func_0206fc4c(0);
    func_0206fb14();
}

void func_ov100_0229c3c0(UnkStruct_0229c3c0 *s)
{
    int r;
    int i, j;

    func_ov100_0229c2a0((unsigned char *) s, 8);
    func_0200467c(0x27);
    s->st = 5;
    func_ov002_02208098((void *) (s), 0x15);
    func_ov100_0229c56c((int) s, 1);
    r = func_ov100_0229c390((int) s, s->a);
    switch (func_0206fca4()) {
        case 0x1d:
        case 0x1e:
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206faf8(s->a);
            break;
        case 0x1f:
            for (i = 0; i < 15; i++) {
                if (s->a[i] == 0xfff1) {
                    continue;
                }
                for (j = 0; j < 15; j++) {
                    unsigned short *bp = (unsigned short *) ((char *) s + 2 * j + 0x28fa);
                    if (s->a[i] == s->b[j]) {
                        *bp = 0xfff1;
                        j = 15;
                    }
                }
            }
            r = func_ov100_0229c390((int) s, s->b);
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206fc80((unsigned char) r);
            func_0206faf8(s->b);
            MI_CpuCopy8(s->a, data_021f3a68, 0x1e);
            func_ov100_0229c324((char *) s, 3);
            break;
        case 0x20:
            MI_CpuCopy8(s->a, data_021f3a86, 0x1e);
            func_ov100_0229c324((char *) s, 4);
            func_0206fc4c(1);
            break;
    }
}

int func_ov100_0229c390(int unused, unsigned short *arr)
{
    int i = 0;
    int j = i;
    for (; i < 15; i++) {
        if (arr[i] != 0xFFF1) {
            if (i != j) {
                arr[j] = arr[i];
                arr[i] = 0xFFF1;
            }
            j++;
        }
    }
    return j;
}

void func_ov100_0229c324(char *self, int b)
{
    u8 buf[0x20];
    int g;

    if (func_02073d90(data_020ccf94) != 0) {
        func_ov100_0229c2b0((void *) self, 8);
        buf[0] = (u8) b;
        MI_CpuCopy8((void *) (self + 0x28dc), (const void *) (&buf[1]), 0x1e);
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, buf, 0x1f);
        func_02073770(g, 0x16, 4);
        *(u16 *) (self + 0x291a) = (u16) func_02073d80(g);
    }
}

int func_ov100_0229c2d8(Obj_0229c2d8 *obj)
{
    if (func_0206fc6c() == 0) {
        return 1;
    }
    if (func_ov100_0229c2c0((unsigned int *) obj, 8) == 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0 && func_02074fec(obj->unk_291A) == 0) {
        return 0;
    }
    return 1;
}

int func_ov100_0229c2c0(unsigned int *ptr, unsigned int mask)
{
    if (*(unsigned int *) ((char *) ptr + 0x28c0) & mask) {
        return 1;
    }
    return 0;
}

void func_ov100_0229c2b0(void *p, unsigned int mask)
{
    *(unsigned int *) ((char *) p + 0x28c0) |= mask;
}

void func_ov100_0229c2a0(unsigned char *ptr, unsigned int mask)
{
    *(unsigned int *) (ptr + 0x28c0) &= ~mask;
}
