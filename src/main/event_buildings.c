/* event_buildings: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3038 @ 0x020b3038, 0xb0 bytes, Thumb
 * func_020b2fc4 @ 0x020b2fc4, 0x74 bytes, Thumb
 * func_020b2f38 @ 0x020b2f38, 0x8c bytes, Thumb
 * func_020b2f28 @ 0x020b2f28, 0x10 bytes, Thumb
 * func_020b2f18 @ 0x020b2f18, 0x10 bytes, Thumb
 * func_020b2f08 @ 0x020b2f08, 0x10 bytes, Thumb
 * func_020b2ef8 @ 0x020b2ef8, 0x10 bytes, Thumb
 * func_020b2ee8 @ 0x020b2ee8, 0x10 bytes, Thumb
 * func_020b2ed8 @ 0x020b2ed8, 0x10 bytes, Thumb
 * func_020b2ec8 @ 0x020b2ec8, 0x10 bytes, Thumb
 * func_020b2eb8 @ 0x020b2eb8, 0x10 bytes, Thumb
 * func_020b2e54 @ 0x020b2e54, 0x64 bytes, Thumb
 * func_020b2dc4 @ 0x020b2dc4, 0x90 bytes, Thumb
 * func_020b2d98 @ 0x020b2d98, 0x2a bytes, Thumb
 * func_020b2b8c @ 0x020b2b8c, 0x20c bytes, Thumb
 * func_020b2a90 @ 0x020b2a90, 0xfc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020b3038 {
    void *data;
    int x_limit;
    int y_limit;
} UnkStruct_020b3038;

struct UnkStruct_020b2fc4 {
    unsigned short unk_00;
};

typedef struct UnkStruct_020b2e54 {
    unsigned short id;
} UnkStruct_020b2e54;

typedef struct UnkStruct_020b2dc4 {
    unsigned short id;
} UnkStruct_020b2dc4;

typedef struct {
    char *base;
    unsigned int w;
    unsigned int h;
} Grid;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020b2b8c;

typedef struct {
    unsigned char *base;
    unsigned int width;
    unsigned int height;
} UnkStruct_020b2a90;

extern int func_0204f658(UnkStruct_020b3038 *s, int x, int y);
extern void func_0204f800(int *out0, int *out1, int x, int y, int w, int h);
extern int func_02037e0c(void *ptr, int a, int b, int c);
extern void *func_0204e414(void);
extern int func_0204e3f4(void *p, int a, int b, int c);
extern int func_0204e404(void *p, unsigned short *s, int a, int b);
extern int func_0204bcdc(void *);
extern int func_0204bc64(const unsigned short *ptr);
extern int func_02037d64(void *, int);
extern int func_02037e44(void *, u16 *, unsigned int, unsigned int, int);
extern unsigned int func_020644cc(int);
extern void func_020871b0(const char *s);
extern void func_02046640(int a);
extern const char data_021ebcd2[];
extern int func_02037da8(void *a, void *b, void *c, void *d, void *e, int f);
extern int func_0204e3bc(void *a, int b, int c, int d, int e, void *f);
extern void func_02085f48(void);
extern void __register_global_object(void *, void *, void *);
extern void func_020051b0(void *);
extern unsigned short data_021f4b20;
extern unsigned short data_021f4b24;
extern unsigned int data_021f4b38;
extern unsigned int data_021f4b4c;
extern unsigned char data_021f4b88;
extern unsigned char data_021f4b94;

int func_020b3038(int *out0, int *out1)
{
    int x, y;
    UnkStruct_020b3038 *s = (UnkStruct_020b3038 *) func_0204e414();
    int x_limit, y_limit;
    int found = 0;
    void *ptr;

    *out0 = 0;
    *out1 = 0;
    if (s == 0) {
        goto fail;
    }

    x_limit = s->x_limit;
    y_limit = s->y_limit;

    y = 0;
    for (; y < y_limit; y++) {
        for (x = 0; x < x_limit; x++) {
            if (func_0204f658(s, x, y) & 0x200) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found == 0) {
        goto fail;
    }

    func_0204f800(out0, out1, x, y, 10, 9);

    if ((unsigned) x < (unsigned) s->x_limit && (unsigned) y < (unsigned) s->y_limit && s->data != 0) {
        ptr = (char *) s->data + (x + y * s->x_limit) * 40;
    } else {
        ptr = 0;
    }
    if (ptr == 0) {
        goto fail;
    }

    return func_02037e0c(ptr, 10, 9, 0);
fail:
    return 0;
}

void func_020b2fc4(int param)
{
    unsigned short val;
    int a, b;
    struct UnkStruct_020b2fc4 *p;
    void *q;
    int cond, cond2;

    val = (unsigned short) param;
    cond = (val >= 0x5000 && val <= 0x5021);
    if (cond != 0) {
        p = (struct UnkStruct_020b2fc4 *) func_020b3038(&a, &b);
        if (p != 0) {
            q = func_0204e414();
            if (q != 0) {
                cond2 = (p->unk_00 >= 0x5000 && p->unk_00 <= 0x5021);
                if (cond2 != 0) {
                    func_0204e3f4(q, a, b, 0);
                }
                func_0204e404(q, &val, a, b);
            }
        }
    }
}

int func_020b2f38(int input)
{
    unsigned short arr[2];
    int out1, out2;
    int cond, res, r;
    int ret = 0;
    unsigned short *p;

    arr[0] = (unsigned short) input;
    cond = 0;
    if (arr[0] >= 0x5000u && arr[0] <= 0x5021u) {
        cond = 1;
    }
    if (cond == 0) {
        goto fail;
    }

    p = (unsigned short *) func_020b3038(&out1, &out2);
    if (p == 0) {
        goto fail;
    }

    if (func_0204bcdc(p) != 0) {
        arr[1] = (unsigned short) input;
        if (func_0204bc64(p) == func_0204bc64(&arr[1])) {
            res = 1;
        } else {
            res = 0;
        }
    } else {
        if (*p == input) {
            res = 1;
        } else {
            res = 0;
        }
    }
    if (res == 0) {
        goto fail;
    }

    r = (int) func_0204e414();
    if (r == 0) {
        goto fail;
    }

    ret = func_0204e3f4((void *) r, out1, out2, 0);
    goto end;

fail:
    ret = 0;
end:
    return ret;
}

void func_020b2f28(void)
{
    func_020b2fc4(20498);
}

int func_020b2f18(void)
{
    return func_020b2f38(0x5012);
}

void func_020b2f08(void)
{
    func_020b2fc4(0x5013);
}

void func_020b2ef8(void)
{
    func_020b2f38(0x5013);
}

void func_020b2ee8(void)
{
    func_020b2fc4(0x5021);
}

void func_020b2ed8(void)
{
    func_020b2f38(0x5021);
}

void func_020b2ec8(void)
{
    func_020b2fc4(0x501e);
}

void func_020b2eb8(void)
{
    func_020b2f38(0x501e);
}

int func_020b2e54(void *p)
{
    int count;
    unsigned int y;
    unsigned int start;
    int zero;
    unsigned int x;
    UnkStruct_020b2e54 *e;
    count = 0;
    if (p != 0) {
        if (func_02037d64(p, 0xe0) != 0 || func_02037d64(p, 0x10) != 0) {
            return 0;
        }
        y = 0;
        zero = 0;
        start = 0;
        for (; y < 0x10; y++) {
            for (x = start; x < 0x10; x++) {
                e = (UnkStruct_020b2e54 *) func_02037e0c(p, x, y, zero);
                if (e != 0 && e->id == 0x500a) {
                    count++;
                }
            }
        }
    }
    return count;
}

int func_020b2dc4(void *self, int arg1, int arg2)
{
    int count;
    unsigned int y;
    unsigned int start;
    int zero;
    int zero2;
    unsigned int x;
    UnkStruct_020b2dc4 *e;
    u16 local;

    count = 0;
    if (self != 0) {
        if (func_02037d64(self, 0xe0) != 0 || func_02037d64(self, 0x10) != 0) {
            return 0;
        }
        y = 0;
        start = 0;
        zero2 = 0;
        zero = 0;
        for (; y < 0x10; y++) {
            for (x = start; x < 0x10; x++) {
                e = (UnkStruct_020b2dc4 *) func_02037e0c(self, x, y, zero);
                if (e != 0 && e->id == 0x500a) {
                    if (arg1 == count) {
                        local = (u16) arg2;
                        if (func_02037e44(self, &local, x, y, zero2) != 0) {
                            return 1;
                        }
                    }
                    count++;
                }
            }
        }
    }
    return 0;
}

int func_020b2d98(int param1, int param2)
{
    int tested_value0;
    int result;
    int temp;

    if ((tested_value0 = (int) (func_020b2e54((void *) param1))) != 0) {
        temp = func_020644cc(tested_value0);
        result = func_020b2dc4((void *) param1, temp, param2);
    } else {
        result = 0;
    }
    return result;
}

static inline void *cell(Grid *g, unsigned int x, unsigned int y)
{
    if (x < g->w && y < g->h && g->base != 0) {
        return g->base + (x + y * g->w) * 0x28;
    }
    return 0;
}

int func_020b2b8c(UnkStruct_020b2b8c *self, int flag)
{
    Grid *g;
    int x;
    int y;
    int i;
    int j;

    g = (Grid *) func_0204e414();
    if (g == 0) {
        return 0;
    }

    x = self->unk_00 >> 17;
    y = self->unk_08 >> 17;

    if (flag != 0) {
        for (i = x - 1; i >= 1; i--) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98((int) (cell(g, i, j)), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    } else {
        for (i = x + 1; i <= 4; i++) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98((int) (cell(g, i, j)), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    }

    for (i = 1; i <= 4; i++) {
        if (i != y) {
            if (func_020b2d98((int) (cell(g, x, i)), 0x5020) != 0) {
                func_020871b0(data_021ebcd2);
                func_02046640(0x44);
                return 1;
            }
        }
    }

    if (flag != 0) {
        for (i = x + 1; i <= 4; i++) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98((int) (cell(g, i, j)), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    } else {
        for (i = x - 1; i >= 1; i--) {
            for (j = 1; j <= 4; j++) {
                if (func_020b2d98((int) (cell(g, i, j)), 0x5020) != 0) {
                    func_020871b0(data_021ebcd2);
                    func_02046640(0x44);
                    return 1;
                }
            }
        }
    }

    if (func_020b2d98((int) (cell(g, x, y)), 0x5020) != 0) {
        func_020871b0(data_021ebcd2);
        func_02046640(0x44);
        return 1;
    }
    return 0;
}

int func_020b2a90(void)
{
    UnkStruct_020b2a90 *self = (UnkStruct_020b2a90 *) func_0204e414();
    int r5;
    int a;
    int r4;
    int b;
    int c;
    int d;
    int e;
    unsigned char *ptr;
    if (self == 0) {
        return 0;
    }
    if ((data_021f4b38 & 1) == 0) {
        data_021f4b20 = 0x5020;
        __register_global_object((void *) (&data_021f4b20), (((void *) func_020051b0)), (void *) (&data_021f4b88));
        data_021f4b38 |= 1;
    }
    a = 1;
    b = 1;
    c = 1;
    for (r5 = 1; r5 <= 4; r5++) {
        for (r4 = a; r4 <= 4; r4++) {
            if (((r4 < self->width) && (r5 < self->height)) && (self->base != 0)) {
                ptr = self->base + ((r4 + (r5 * self->width)) * 0x28);
            } else {
                ptr = 0;
            }
            if (ptr != 0) {
                if (func_02037da8(ptr, &d, &e, &data_021f4b20, &data_021f4b20, 0) != 0) {
                    if ((data_021f4b4c & b) == 0) {
                        data_021f4b24 = 0x500a;
                        __register_global_object((void *) (&data_021f4b24), (((void *) func_020051b0)),
                                                 (void *) (&data_021f4b94));
                        data_021f4b4c |= c;
                    }
                    if (func_0204e3bc(self, r4, r5, d, e, &data_021f4b24) != 0) {
                        func_02085f48();
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}
