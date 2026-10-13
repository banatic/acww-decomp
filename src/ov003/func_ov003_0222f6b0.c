/* func_ov003_0222f6b0 @ 0x0222f6b0, 0x2a8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    u8 a;
    u8 pad_01;
    u16 b;
    u16 c;
} UnkStruct_0222f6b0;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x18 - 0xc];
    int *unk_18;
    char pad_1C[0xf4 - 0x1c];
    unsigned int unk_F4;
    char pad_F8[0x170 - 0xf8];
    void (*unk_170)(void *self);
    char pad_174[0x204 - 0x174];
    Vec3 unk_204;
    char pad_210[0x21c - 0x210];
    int unk_21C;
    char pad_220[0x234 - 0x220];
    s16 unk_234;
    char pad_236[0x23a - 0x236];
    s16 unk_23A;
    char pad_23C[0x249 - 0x23c];
    u8 unk_249;
    char pad_24A[0x24d - 0x24a];
    char unk_24D;
    char pad_24E[2];
    u8 unk_250;
    u8 unk_251;
    char pad_252[0x258 - 0x252];
    u8 unk_258;
} UnkStruct_0222f6b0_2;

typedef struct {
    char pad_00[0x40];
} Box;

extern UnkStruct_0222f6b0 data_ov003_0223c144[];
extern void *data_020ccf94;
extern int func_02073dd4(void *g, int a);
extern int func_020a7278(void);
extern void func_ov003_0222f958(void *a, UnkStruct_0222f6b0_2 *self);
extern void func_ov003_0222d68c(UnkStruct_0222f6b0_2 *self);
extern void func_ov003_0222f570(void *a, UnkStruct_0222f6b0_2 *self);
extern int func_ov003_0222eb94(void *a, UnkStruct_0222f6b0_2 *self);
extern void func_02034270(Box *b, Vec3 *p, int x, int y);
extern int func_020341c8(Box *b, int k);
extern void func_0203423c(Box *b);
extern void func_02031288(char *o, Vec3 *a, Vec3 *b, int h, int d, int e, int f);
extern void func_02089aa8(char *q, Vec3 *w, int t, int u, u8 fl);
extern void func_02055124(char *p);
extern void func_02056ffc(UnkStruct_0222f6b0_2 *self);
extern void func_ov003_0222fe18(void *a, UnkStruct_0222f6b0_2 *self, int mode);
extern void func_ov003_0222e0ec(void *a, UnkStruct_0222f6b0_2 *self, int k);
extern void func_020042c0(char *p, Vec3 *v);

void func_ov003_0222f6b0(void *a, UnkStruct_0222f6b0_2 *self, int flags, int mode)
{
    int cond;
    char *q;
    Vec3 v1c;
    Vec3 w;
    Vec3 z;
    Box box;
    Vec3 *p;
    int r;
    int hot;
    char kind;
    int st;
    unsigned int t;
    s16 *pc;

    hot = self->unk_249;
    r = func_02073dd4(data_020ccf94, *(int *) ((char *) data_020ccf94 + 0x64));
    if (r != 0) {
        if (self->unk_258 != 0) {
            hot = 1;
        }
    }
    if (hot == 0) {
        func_ov003_0222f958(a, self);
    }
    if (mode == 1) {
        if (r == 0 || func_020a7278() != 0) {
            pc = &self->unk_234;
            if (hot != 0) {
                *pc = 0x4b0;
            } else if (*pc > 0) {
                *pc = *pc - 1;
                if (*pc == 0) {
                    self->unk_250 = 4;
                    return;
                }
            }
        }
    }
    if (self->unk_170 == 0) {
        return;
    }
    if (hot == 0) {
        if ((unsigned int) (mode - 2) > 1) {
            return;
        }
    }
    kind = self->unk_24D;
    st = self->unk_251;
    func_ov003_0222d68c(self);
    if (st == 0x10 || kind < 0) {
        goto L8a8;
    }
    if (st == 0xa) {
        goto L876;
    }

    p = &self->unk_204;
    v1c.x = p->x;
    v1c.y = p->y;
    v1c.z = p->z;
    q = (char *) self + 0x108;
    func_ov003_0222f570(a, self);
    self->unk_170(self);
    if (func_ov003_0222eb94(a, self) != 0) {
        if (mode == 3) {
            func_02034270(&box, &self->unk_204, 0, 0);
            if (func_020341c8(&box, 0) > 0x4000) {
                cond = 1;
            } else {
                cond = 0;
            }
            func_0203423c(&box);
            if (cond != 0) {
                func_02031288((char *) self + 0x20, &self->unk_204, &v1c, self->unk_23A, data_ov003_0223c144[kind].b, 0, 0xa);
                goto after;
            }
        }
        func_02031288((char *) self + 0x20, &self->unk_204, &v1c, self->unk_23A, data_ov003_0223c144[kind].b, 0, 0xb);
    }
after:
    if (self->unk_24D == 0x33) {
        if (flags == 0) {
            self->unk_21C = 1;
        }
    }
    flags = flags | (1 << (mode + 3));
    p = &self->unk_204;
    w.x = p->x;
    w.y = p->y;
    w.z = p->z;
    if (self->unk_24D == 0x35) {
        t = (self->unk_F4 << 4) >> 16;
        if (t >= 0x1e && t < 0x28) {
            w.y = w.y - 0x1800;
        }
    }
    func_02089aa8(q, &w, data_ov003_0223c144[kind].c, 0xd48, (u8) flags);

L876:
    if (data_ov003_0223c144[kind].a == 0) {
        func_02055124((char *) self + 0x50);
        kind -= 0x3a;
        if ((u8) kind <= 1) {
            func_02056ffc(self);
            *self->unk_18 = self->unk_08;
        }
    }
    goto L8b8;

L8a8:
    if (kind == 0x14 || kind == 0x37) {
        func_02055124((char *) self + 0x50);
    }

L8b8:
    if (st == 0xa) {
        func_ov003_0222fe18(a, self, mode);
        return;
    }
    if (mode == 3 && st == 0x10) {
        func_ov003_0222e0ec(a, self, 1);
    } else {
        func_ov003_0222e0ec(a, self, 0);
    }
    p = &self->unk_204;
    z.x = p->x;
    z.y = p->y;
    z.z = p->z;
    func_020042c0((char *) self + 0x174, &z);
}
