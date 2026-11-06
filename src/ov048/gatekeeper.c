/* gatekeeper: 8 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02260750 @ 0x02260750, 0x2c bytes, Thumb
 * func_ov048_02260714 @ 0x02260714, 0x3c bytes, Thumb
 * func_ov048_0226056c @ 0x0226056c, 0x1a8 bytes, Thumb
 * func_ov048_022604c8 @ 0x022604c8, 0xa4 bytes, Thumb
 * func_ov048_022604ac @ 0x022604ac, 0x1c bytes, Thumb
 * func_ov048_02260474 @ 0x02260474, 0x38 bytes, Thumb
 * func_ov048_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov048_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02260714 {
    unsigned char pad_00[0x563];
    unsigned char unk_563;
    unsigned char pad_564[0xb4];
    unsigned char unk_618;
};

struct VT2;

struct UnkStruct_0226056c_2 {
    struct VT2 *vt;
};

struct VT2 {
    void (*fn[8])(struct UnkStruct_0226056c_2 *);
};

struct UnkStruct_0226056c_3 {
    u8 pad_00[0x560];
    u8 unk_560;
    u8 pad_561[0x658 - 0x561];
    struct UnkStruct_0226056c_2 unk_658;
};

struct UnkStruct_0226056c {
    u8 pad_00[0x64];
    int unk_64;
};

typedef struct {
    int a, b, c;
} Tri;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x654];
    unsigned char unk_658;
} UnkStruct_02260448;

struct UnkStruct_02260420 {
    unsigned int unk_00;
};

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern struct UnkStruct_0226056c *data_020ccf94;
extern void func_0201c054(struct UnkStruct_0226056c_3 *self, int a, int b, int c);
extern int func_0201c0e0(struct UnkStruct_0226056c_3 *self);
extern int func_0201c040(struct UnkStruct_0226056c_3 *self, int *a, int *b);
extern int func_0201c2a4(struct UnkStruct_0226056c_3 *self, int a);
extern void func_ov048_022635f4(struct UnkStruct_0226056c_3 *self, int a);
extern void func_02016108(struct UnkStruct_0226056c_2 *s, int a);
extern void func_ov048_02262678(struct UnkStruct_0226056c_2 *s, int a);
extern int func_020a7278(void);
extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_0203ec98(void);
extern int func_02073dd4(void *, int);
extern Tri *func_02095794(int);
extern void *func_020984e8(void);
extern int func_0203e0a8(void *, int);
extern const Tri data_ov048_02263968;
extern int func_0202ebcc(int);
extern int func_0201a3e4(int);
extern int func_020c18c4(void);
extern char data_ov048_02264298;
extern void *func_ov048_022626f0(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

int func_ov048_02260750(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov048_02260714(struct UnkStruct_02260714 *self)
{
    if (self->unk_563) {
        return 1;
    }
    if (func_02014868(&self->unk_618) != 0) {
        goto ret0;
    }
    if (func_0201c014(self) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov048_0226056c(struct UnkStruct_0226056c_3 *self, int sel, int v)
{
    switch (sel) {
        case 3:
            self->unk_560 = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov048_022635f4(self, 0x10);
            } else if (func_0201c0e0(self) != 0) {
                int k = data_020ccf94->unk_64;
                func_0201c054(self, 1, k, k);
                func_ov048_022635f4(self, 0x10);
            }
            break;
        case 1:
            self->unk_658.vt->fn[2](&self->unk_658);
            func_02016108(&self->unk_658, func_0201c2a4(self, 4));
            func_ov048_022635f4(self, 2);
            break;
        case 0:
            self->unk_560 = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov048_022635f4(self, 0x11);
            } else {
                if (func_0201c0e0(self) != 0) {
                    int k = data_020ccf94->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    func_ov048_022635f4(self, 2);
                }
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov048_022635f4(self, 4);
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov048_022635f4(self, 0xf);
                }
            }
            func_ov048_02262678(&self->unk_658, 0xb);
            break;
        case 4: {
            int a;
            int b;
            if (func_0201c014((void *) self) == 0) {
                break;
            }
            if (func_0201c0e0(self) == 0) {
                break;
            }
            a = 4;
            b = 4;
            if (func_0201c040(self, &a, &b) == 0) {
                break;
            }
            if (v != 4) {
                if (v == b) {
                    goto ok;
                }
            }
            if (v != 4) {
                break;
            }
        ok:
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov048_022635f4(self, 1);
            break;
        }
    }
}

int func_ov048_022604c8(void *obj)
{
    void *g;
    int v;
    volatile Tri t;
    Tri *p;

    g = (*(void **) &data_020ccf94);
    if (func_02073d90(g) != 0) {
        return 0;
    }
    v = func_020b65c4();
    if (v == 0x2f) {
        return 0;
    }
    if (func_0203ec98() != 0) {
        return 0;
    }
    if (func_02073dd4((*(void **) &data_020ccf94), *(int *) ((char *) (*(void **) &data_020ccf94) + 0x64)) == 0) {
        return 0;
    }
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    if (p->c <= data_ov048_02263968.c) {
        func_020984e8();
        if (func_02073d90(g) != 0) {
            func_ov048_02262678((struct UnkStruct_0226056c_2 *) ((char *) obj + 0x658), 9);
        } else {
            func_ov048_02262678((struct UnkStruct_0226056c_2 *) ((char *) obj + 0x658), 0xa);
        }
        func_0203e0a8(obj, 0);
        return 1;
    }
    return 0;
}

int func_ov048_022604ac(int param)
{
    if (func_020b65c4() == 12) {
        return 0;
    }
    return func_0202ebcc(param);
}

int func_ov048_02260474(int param)
{
    int r4;
    int r0;

    r4 = param;
    r0 = func_0201a3e4(r4 + 0x2ac);
    if (r0 == 0xba) {
        if (func_020c18c4() != 0) {
            r0 = *(int *) (*(int *) (r4 + 0x698) + 4);
            if (r0 == 2) {
                return 1;
            }
        }
    }
    return 0;
}

void *func_ov048_02260448(UnkStruct_02260448 *self)
{
    self->unk_00 = &data_ov048_02264298;
    func_ov048_022626f0(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

struct UnkStruct_02260420 *func_ov048_02260420(struct UnkStruct_02260420 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov048_02264298);
    func_ov048_022626f0((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
