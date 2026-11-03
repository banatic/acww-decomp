/* public_box: 21 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229ca08 @ 0x0229ca08, 0x20 bytes, Thumb
 * func_ov110_0229c9e8 @ 0x0229c9e8, 0x20 bytes, Thumb
 * func_ov110_0229c9c8 @ 0x0229c9c8, 0x20 bytes, Thumb
 * func_ov110_0229c98c @ 0x0229c98c, 0x3c bytes, Thumb
 * func_ov110_0229c944 @ 0x0229c944, 0x48 bytes, Thumb
 * func_ov110_0229c920 @ 0x0229c920, 0x22 bytes, Thumb
 * func_ov110_0229c8f4 @ 0x0229c8f4, 0x2c bytes, Thumb
 * func_ov110_0229c7f0 @ 0x0229c7f0, 0x104 bytes, Thumb
 * func_ov110_0229c6ec @ 0x0229c6ec, 0x104 bytes, Thumb
 * func_ov110_0229c678 @ 0x0229c678, 0x74 bytes, Thumb
 * func_ov110_0229c5a0 @ 0x0229c5a0, 0xd8 bytes, Thumb
 * func_ov110_0229c574 @ 0x0229c574, 0x2c bytes, Thumb
 * func_ov110_0229c53c @ 0x0229c53c, 0x38 bytes, Thumb
 * func_ov110_0229c4f8 @ 0x0229c4f8, 0x44 bytes, Thumb
 * func_ov110_0229c3b8 @ 0x0229c3b8, 0x140 bytes, Thumb
 * func_ov110_0229c388 @ 0x0229c388, 0x30 bytes, Thumb
 * func_ov110_0229c324 @ 0x0229c324, 0x64 bytes, Thumb
 * func_ov110_0229c2dc @ 0x0229c2dc, 0x48 bytes, Thumb
 * func_ov110_0229c2c8 @ 0x0229c2c8, 0x12 bytes, Thumb
 * func_ov110_0229c2b8 @ 0x0229c2b8, 0xe bytes, Thumb
 * func_ov110_0229c2a8 @ 0x0229c2a8, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xf9];
    unsigned char type;
} UnkStruct_0229c920;

typedef struct {
    unsigned char pad_00[0xf5];
    unsigned char unk_F5;
} UnkStruct_0229c7f0;

typedef struct {
    u8 pad_00[0xf5];
    u8 unk_F5;
    u8 pad_F6[0x22e0 - 0xf6];
    u8 unk_22E0;
} UnkStruct_0229c5a0;

typedef struct {
    char pad_00[0xb0];
    unsigned short a[15];
    unsigned short b[15];
    char pad_EC[0xfc - 0xec];
    unsigned char st;
} UnkStruct_0229c3b8;

struct UnkStruct_0229c324;

struct UnkStruct_0229c324 {
    unsigned char pad_00[0xb0];
    unsigned char arr[30];
    unsigned char pad_CE[32];
    unsigned short unk_EE;
};

typedef struct {
    char pad_00[0xEE];
    short unk_EE;
} UnkStruct_0229c2dc;

typedef struct {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
} UnkStruct_0229c2a8;

extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *ptr);
extern void func_ov002_0220a374(void *, int);
extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov110_0229d840(UnkStruct_0229c920 *self);
extern void func_ov110_0229ca48(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_ov002_022088ac(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov110_0229d5e4(UnkStruct_0229c5a0 *self, u8 value);
extern int func_ov110_0229d5d4(UnkStruct_0229c5a0 *self, u8 value);
extern int func_ov110_0229d5c8(UnkStruct_0229c5a0 *self, u8 value);
extern void func_ov002_0220a314(void *arg);
extern void func_ov002_0220a2b4(void *arg);
extern void func_02070b84(void *);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern int func_0207094c(void *p, int x);
extern void func_02070a04(void *p, int x, int y);
extern int func_0206fca4(void);
extern void func_0200467c(int);
extern void func_0206fc4c(int);
extern void func_0206faf8(unsigned short *);
extern void func_0206fc80(int);
extern void MI_CpuCopy8(void *, const void *, int);
extern const unsigned short data_021f3a68[];
extern const unsigned short data_021f3a86[];
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern unsigned short func_02073d80(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, unsigned int);
extern void func_02073770(void *, int, int);
extern int func_0206fc6c(void);
extern int func_02074fec(short);

int func_ov110_0229c388(int unused, unsigned short *arr);
void func_ov110_0229c324(struct UnkStruct_0229c324 *self, unsigned char cmd);
int func_ov110_0229c2c8(int param1, int param2);
void func_ov110_0229c2b8(void *r0, unsigned int r1);
void func_ov110_0229c2a8(UnkStruct_0229c2a8 *obj, unsigned int mask);

void func_ov110_0229ca08(void *p)
{
    func_ov002_0220a1dc((char *) p + 0x22e0);
    func_ov002_02208098((void *) (p), 9);
}

void func_ov110_0229c9e8(void *arg)
{
    func_ov002_0220a164((char *) arg + 0x22e0);
    func_ov002_02208098((void *) (arg), 0xa);
}

void func_ov110_0229c9c8(void *arg0)
{
    func_ov002_0220a374((char *) arg0 + 0x22e0, 4);
    func_ov002_02208098((void *) (arg0), 0xb);
}

void func_ov110_0229c98c(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x21f8, 1);
    ((char *) self)[0xf7] = value;
    func_ov002_0220a374((char *) self + 0x22e0, 5);
    func_ov002_02208098((void *) (self), 0xd);
}

void func_ov110_0229c944(unsigned char *base, unsigned char param)
{
    unsigned char *src;
    unsigned char *dst;
    unsigned char *p;
    unsigned char val;

    func_ov002_02207d24(base + 0x21f8, 1);
    src = base + 0x8d;
    val = *src;
    dst = base + 0xf8;
    *dst = val;
    p = base + 0xf7;
    *p = param;
    func_ov002_0220a374(base + 0x22e0, 6);
    func_ov002_02208098((void *) (base), 14);
}

void func_ov110_0229c920(UnkStruct_0229c920 *self)
{
    switch (self->type) {
        case 0:
            func_ov110_0229c9c8((void *) self);
            break;
        case 1:
        default:
            func_ov110_0229d840(self);
            break;
    }
}

void func_ov110_0229c8f4(void *self)
{
    char *p = (char *) self + 0xf9;
    *p = 1;
    func_ov110_0229ca48(self);
    func_ov002_022096d8((char *) self + 0x2344, 0);
    func_ov002_02208098((void *) (self), 0x13);
}

void func_ov110_0229c7f0(UnkStruct_0229c7f0 *p, void *q, int mode)
{
    int r4;
    int r6;

    r4 = p->unk_F5;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(q)) {
        if (func_ov002_022088cc(q) && r6 != 0) {
            goto later;
        }
        if (r4 == 0) {
            if (mode == 1) {
                p->unk_F5 += 4;
            } else {
                p->unk_F5 = 30;
            }
            func_ov110_0229c2b8((void *) p, 16);
            goto end;
        } else {
            p->unk_F5--;
            r4--;
            goto later;
        }
    } else {
        if (func_ov002_0220889c(q) == 0 || func_ov002_022088bc(q) != 0) {
            goto later;
        }
        if (r4 == 4) {
            if (mode == 1) {
                p->unk_F5 -= 4;
                func_ov110_0229c2b8((void *) p, 32);
                goto end;
            } else {
                p->unk_F5 = 30;
                goto end;
            }
        } else {
            p->unk_F5++;
            r4++;
        }
    }

later:
    if (func_ov002_022088cc(q)) {
        if (r6 > 0) {
            p->unk_F5 -= 5;
        } else {
            r4 += 25;
            p->unk_F5 = r4;
        }
    } else {
        if (func_ov002_022088bc(q) && r6 < 2) {
            p->unk_F5 += 5;
        }
    }

end:
    return;
}

void func_ov110_0229c6ec(unsigned char *a, void *b, int c)
{
    int r4, r6;

    r4 = a[0xf5] - 15;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(b) != 0) {
        if (func_ov002_022088cc(b) != 0) {
            if (r6 != 0) {
                goto L7ac;
            }
        }
        // func2 == 0 or (func2 != 0 && r6 == 0)
        if (r4 == 0) {
            if (c == 1) {
                a[0xf5] = a[0xf5] + 4;
            } else {
                a[0xf5] = 30;
            }
            func_ov110_0229c2b8(a, 16);
            goto end;
        } else {
            a[0xf5] = a[0xf5] - 1;
            r4--;
            goto L7ac;
        }
    } else {
        if (func_ov002_0220889c(b) == 0) {
            goto L7ac;
        }
        if (func_ov002_022088bc(b) != 0) {
            goto L7ac;
        }
        if (r4 == 4) {
            if (c == 1) {
                a[0xf5] = a[0xf5] - 4;
                func_ov110_0229c2b8(a, 32);
                goto end;
            } else {
                a[0xf5] = 30;
                goto end;
            }
        } else {
            a[0xf5] = a[0xf5] + 1;
            r4++;
            goto L7ac;
        }
    }

L7ac:
    if (func_ov002_022088cc(b) != 0) {
        if (r6 > 0) {
            a[0xf5] = a[0xf5] - 5;
        }
    } else {
        if (func_ov002_022088bc(b) != 0) {
            if (r6 < 2) {
                a[0xf5] = a[0xf5] + 5;
            } else {
                a[0xf5] = r4;
            }
        }
    }

end:
    return;
}

void func_ov110_0229c678(void *r4, void *r5)
{
    if (func_ov002_0220889c(r5)) {
        if (func_ov002_022088cc(r5)) {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0x19;
        } else {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0;
        }
        func_ov110_0229c2b8(r4, 0x20);
    } else if (func_ov002_022088ac(r5)) {
        if (func_ov002_022088cc(r5)) {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0x1d;
        } else {
            *(unsigned char *) ((char *) r4 + 0xf5) = 4;
        }
    } else if (func_ov002_022088cc(r5)) {
        *(unsigned char *) ((char *) r4 + 0xf5) = 0x1d;
    }
}

int func_ov110_0229c5a0(UnkStruct_0229c5a0 *self, int arg1, int arg2)
{
    u8 initial = self->unk_F5;

    func_ov110_0229c2a8((UnkStruct_0229c2a8 *) self, 0x30);
    func_ov110_0229c2a8((UnkStruct_0229c2a8 *) self, 0x100);

    if (arg1 == 0) {
        return 0;
    }

    if (func_ov110_0229d5e4(self, self->unk_F5) != 0) {
        func_ov110_0229c7f0((UnkStruct_0229c7f0 *) self, (void *) arg1, arg2);
    } else if (func_ov110_0229d5d4(self, self->unk_F5) != 0) {
        func_ov110_0229c6ec((unsigned char *) self, (void *) arg1, arg2);
    } else if (func_ov110_0229d5c8(self, self->unk_F5) != 0) {
        func_ov110_0229c678((void *) self, (void *) arg1);
    }

    if (func_ov110_0229d5c8(self, self->unk_F5) != func_ov110_0229d5c8(self, initial)) {
        if (func_ov110_0229d5c8(self, self->unk_F5) != 0) {
            func_ov002_0220a314(&self->unk_22E0);
        } else {
            func_ov002_0220a2b4(&self->unk_22E0);
        }
        func_ov110_0229c2b8((void *) self, 0x100);
    }

    return (initial != self->unk_F5) ? 1 : 0;
}

void func_ov110_0229c574(void *param)
{
    int i;
    char *p;
    char *base;

    p = (char *) param + 0xfb;
    *p = 0;
    base = (char *) param + 0x2854;
    for (i = 0; i < 2; i++) {
        func_02070b84(base + i * 0x6c);
    }
}

unsigned char *func_ov110_0229c53c(unsigned char *p)
{
    if (p[0xfb] >= 2) {
        return p + 0x28c0;
    }
    p[0xfb]++;
    return p + 0x2854 + (p[0xfb] - 1) * 0x6c;
}

void func_ov110_0229c4f8(int a, int b)
{
    int flags;
    void *p;
    flags = 1;
    if (b) {
        flags = 0xf;
    }
    p = (void *) func_ov110_0229c53c((unsigned char *) a);
    func_02070adc(p, 4, 0x1ca, 6, flags, 9, 0);
    func_0207094c(p, 0x88);
    func_02070a04(p, 1, 1);
}

void func_ov110_0229c3b8(UnkStruct_0229c3b8 *s, int flag)
{
    int m;
    int r;
    int i, j;

    func_ov110_0229c2a8((UnkStruct_0229c2a8 *) s, 8);
    m = func_0206fca4();
    if (m == 0x20) {
        func_0200467c(0x28);
    } else {
        func_0200467c(0x27);
    }
    if (flag != 0) {
        s->st = 5;
    } else {
        s->st = 0;
    }
    func_ov002_02208098((void *) (s), 0x15);
    func_ov110_0229c4f8((int) s, 1);
    r = func_ov110_0229c388((int) s, s->a);
    switch (m) {
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
                    if (s->a[i] == s->b[j]) {
                        s->b[j] = 0xfff1;
                        j = 15;
                    }
                }
            }
            r = func_ov110_0229c388((int) s, s->b);
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206fc80((unsigned char) r);
            func_0206faf8(s->b);
            MI_CpuCopy8(s->a, data_021f3a68, 0x1e);
            func_ov110_0229c324((struct UnkStruct_0229c324 *) s, 3);
            break;
        case 0x20:
            MI_CpuCopy8(s->a, data_021f3a86, 0x1e);
            func_ov110_0229c324((struct UnkStruct_0229c324 *) s, 4);
            func_0206fc4c(1);
            break;
    }
}

int func_ov110_0229c388(int unused, unsigned short *arr)
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

void func_ov110_0229c324(struct UnkStruct_0229c324 *self, unsigned char cmd)
{
    if (func_02073d90(data_020ccf94) != 0) {
        unsigned char buf[31];
        void *p;

        func_ov110_0229c2b8((void *) self, 8);
        buf[0] = cmd;
        MI_CpuCopy8(self->arr, buf + 1, 30);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, buf, 31);
        func_02073770(p, 0x16, 4);
        self->unk_EE = func_02073d80(p);
    }
}

int func_ov110_0229c2dc(UnkStruct_0229c2dc *param)
{
    if (func_0206fc6c() == 0) {
        return 1;
    }
    if (func_ov110_0229c2c8((int) param, 8) == 0) {
        return 1;
    }
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0 && func_02074fec(param->unk_EE) == 0) {
        return 0;
    }
    return 1;
}

int func_ov110_0229c2c8(int param1, int param2)
{
    if ((*(int *) (param1 + 0x94) & param2) != 0) {
        return 1;
    }
    return 0;
}

void func_ov110_0229c2b8(void *r0, unsigned int r1)
{
    unsigned int *p;
    unsigned int v;

    p = (unsigned int *) ((char *) r0 + 0x94);
    v = *p;
    v |= r1;
    *((unsigned int *) ((char *) r0 + 0x94)) = v;
}

void func_ov110_0229c2a8(UnkStruct_0229c2a8 *obj, unsigned int mask)
{
    obj->unk_94 &= ~mask;
}
